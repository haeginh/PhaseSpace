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

#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "G4Event.hh"
#include "G4THitsMap.hh"
#include "G4SDManager.hh"
#include "pshit.hh"

class Run : public G4Run
{
public:
    Run();
    virtual ~Run();

    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);

    std::vector<G4int>* GetParticles() {return &particles;}
    std::vector<G4double>* GetEnergies() {return &energies;}
    std::vector<G4ThreeVector>* GetPositions() {return &positions;}
    std::vector<G4ThreeVector>* GetDirections() {return &directions;}

    G4double GetDapDose(){return dapDose;}
private:
    // methods
    PSHitsCollection* GetHitsCollection(G4int hcID,
                                              const G4Event* event) const;
    G4int   fHCID, fHCID_dap;
    std::vector<G4int>    particles;
    std::vector<G4double> energies;
    std::vector<G4ThreeVector> positions, directions;
    G4double dapDose;
};

#endif
