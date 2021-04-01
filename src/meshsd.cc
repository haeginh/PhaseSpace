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
/// \file MeshSD.cc
/// \brief Implementation of the MeshSD class

#include "meshsd.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

MeshSD::MeshSD(const G4String& name, const G4String& hcname)
 : G4VSensitiveDetector(name), fHitsCollection(0)
{
  collectionName.insert(hcname);
    gamma
    = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    e
    = G4ParticleTable::GetParticleTable()->FindParticle("e-");
}

MeshSD::~MeshSD()
{
}

void MeshSD::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new PSHitsCollection(SensitiveDetectorName, collectionName[0]);
    G4int hcID
      = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection( hcID, fHitsCollection );
}

G4bool MeshSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
 if(step->GetPostStepPoint()->GetTouchable()->GetCopyNumber()>0) return false;
//    if(step->GetTrack()->GetParticleDefinition()!=gamma){
//      G4cout<<step->GetTrack()->GetParticleDefinition()->GetParticleDefinitionID()<<":"<<step->GetTrack()->GetKineticEnergy()/keV<<"!"<<G4endl;
//      return false;
//  }
  // energy deposit
  PSHit* newHit = new PSHit();

  newHit->SetParticleID(step->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
  newHit->SetEenergy(step->GetTrack()->GetKineticEnergy());
  newHit->SetPos (step->GetPreStepPoint()->GetPosition());
  newHit->SetDirection(step->GetTrack()->GetMomentumDirection());

  fHitsCollection->insert( newHit );

  //newHit->Print();

  return true;
}

void MeshSD::EndOfEvent(G4HCofThisEvent*)
{
  if ( verboseLevel>1 ) {

  }
}

