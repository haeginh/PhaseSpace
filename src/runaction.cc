//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//

#include "runaction.hh"
#include "primarygeneratoraction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
//#include "g4root.hh"
RunAction::RunAction()
 : G4UserRunAction()
{
    const G4double milligray = 1.e-3*gray;
    const G4double microgray = 1.e-6*gray;
    const G4double nanogray  = 1.e-9*gray;
    const G4double picogray  = 1.e-12*gray;

    new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
    new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
    new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
    new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

//    auto analysisManager = G4AnalysisManager::Instance();
//    G4cout << "Using " << analysisManager->GetType() << G4endl;
//    analysisManager->SetVerboseLevel(1);
//    analysisManager->SetNtupleMerging(true);

//    analysisManager->CreateNtuple("Phase-space", "phase-space file");
//    analysisManager->CreateNtupleDColumn("KE");
//    analysisManager->CreateNtupleDColumn("posX");
//    analysisManager->CreateNtupleDColumn("posY");
//    analysisManager->CreateNtupleDColumn("posZ");
//    analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{}

G4Run* RunAction::GenerateRun()
{
    // generate run***
    fRun = new Run();
    return fRun;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
  nps=run->GetNumberOfEventToBeProcessed();
  G4RunManager::GetRunManager()->SetPrintProgress(int(nps*0.1));
// G4cout<<"2"<<G4endl;
//  // Get analysis manager
//  auto analysisManager = G4AnalysisManager::Instance();
//  G4cout<<"2"<<G4endl;

  // Open an output file
  //
//  G4String fileName = "Phase-space";
//  analysisManager->OpenFile(fileName);
//  G4cout<<"3"<<G4endl;

  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* )
{
    if(!IsMaster()) return;
    G4cout<<std::scientific<<fRun->GetDapDose()<<G4endl;
    G4cout<<"DAP dose is "<<G4BestUnit(fRun->GetDapDose()/nps,"Dose")<<G4endl;
    std::ofstream ofs("phase-base.txt", std::ios::out | std::ios::binary);
    G4int num = fRun->GetParticles()->size();
    ofs.write((char*) &num, sizeof(G4int));
    ofs.write((char*) &(*fRun->GetParticles())[0], num*sizeof(G4int));
    ofs.write((char*) &(*fRun->GetEnergies())[0], num*sizeof(G4double));
    ofs.write((char*) &(*fRun->GetPositions())[0], num*sizeof(G4ThreeVector));
    ofs.write((char*) &(*fRun->GetDirections())[0], num*sizeof(G4ThreeVector));
    ofs.close();

    G4cout<<"Printed "<<num<<" events"<<G4endl;
//    auto analysisManager = G4AnalysisManager::Instance();

//    analysisManager->Write();
//    analysisManager->CloseFile();
}
