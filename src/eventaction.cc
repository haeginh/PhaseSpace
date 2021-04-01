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
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "eventaction.hh"
#include "meshsd.hh"
#include "pshit.hh"
#include "g4root.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>



EventAction::EventAction()
 : G4UserEventAction(),
   fHCID(-1)
{}



EventAction::~EventAction()
{}

PSHitsCollection*
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection
    = static_cast<PSHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Get hits collections IDs (only once)
  if ( fHCID == -1 ) {
    fHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("pshit");
  }

  // Get hits collections
  auto psHC = GetHitsCollection(fHCID, event);
  if(psHC->entries()==0) return;
  auto analysisManager = G4AnalysisManager::Instance();
  for(size_t i=0;i<psHC->entries();i++){
      auto psHit = (*psHC)[i];
      analysisManager->FillNtupleDColumn(0, psHit->GetEnergy());
      analysisManager->FillNtupleDColumn(1, psHit->GetPos().x());
      analysisManager->FillNtupleDColumn(2, psHit->GetPos().y());
      analysisManager->FillNtupleDColumn(3, psHit->GetPos().z());
      analysisManager->AddNtupleRow();
  }

  // Fill histograms, ntuple
  //

  // get analysis manager

  // fill histograms
//  analysisManager->FillH1(0, psHit->GetEnergy());
//  analysisManager->FillH1(1, psHit->GetPos().x());
//  analysisManager->FillH1(2, psHit->GetPos().y());
//  analysisManager->FillH1(3, psHit->GetPos().z());

  // fill ntuple

}


