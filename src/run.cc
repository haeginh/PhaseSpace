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

#include "run.hh"

Run::Run()
:G4Run(), dapDose(0)
{
    fHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("pshit");
    fHCID_dap
      = G4SDManager::GetSDMpointer()->GetCollectionID("dap/dose");
}

Run::~Run()
{}

PSHitsCollection*
Run::GetHitsCollection(G4int hcID,
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
void Run::RecordEvent(const G4Event* event)
{
    // Get hits collections
    auto psHC = GetHitsCollection(fHCID, event);
    if(psHC->entries()==0) return;
    auto psHit = (*psHC)[0];
    particles.push_back(psHit->GetPaarticleID());
    energies.push_back(psHit->GetEnergy());
    positions.push_back(psHit->GetPos());
    directions.push_back(psHit->GetDirection());

    G4THitsMap<G4double>* hc_dap =
            static_cast<G4THitsMap<G4double>*> (event->GetHCofThisEvent()->GetHC(fHCID_dap));
    auto dapDoseMap = *hc_dap->GetMap();
    if(dapDoseMap.find(1000)!=dapDoseMap.end()){
        dapDose+=*dapDoseMap[1000];
    }
}

void Run::Merge(const G4Run* run)
{
    const Run* localRun = static_cast<const Run*>(run);
    // merge the data from each thread
    auto parVec = localRun->particles;
    auto eVec = localRun->energies;
    auto pVec = localRun->positions;
    auto dVec = localRun->directions;

    particles.insert(particles.end(),parVec.begin(),parVec.end());
    energies.insert(energies.end(),eVec.begin(),eVec.end());
    positions.insert(positions.end(),pVec.begin(),pVec.end());
    directions.insert(directions.end(), dVec.begin(),dVec.end());
 //   dapDose+=localRun->dapDose;
    G4Run::Merge(run);
}
