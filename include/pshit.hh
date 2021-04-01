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
/// \file PSHit.hh
/// \brief Definition of the PSHit class

#ifndef PSHit_h
#define PSHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class PSHit : public G4VHit
{
  public:
    PSHit();
    PSHit(const PSHit&);
    virtual ~PSHit();

    // operators
    const PSHit& operator=(const PSHit&);
    G4bool operator==(const PSHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
    void SetParticleID(G4int id) {fParticleID = id;}
    void SetEenergy     (G4double e)      { fEnergy = e; }
    void SetPos      (G4ThreeVector xyz){ fPos = xyz; }
    void SetDirection(G4ThreeVector xyz) {fDirection = xyz;}

    // Get methods
    G4int GetPaarticleID() {return fParticleID;}
    G4double GetEnergy() const     { return fEnergy; }
    G4ThreeVector GetPos() const { return fPos; }
    G4ThreeVector GetDirection() const {return fDirection;}

  private:

      G4int         fParticleID;
      G4double      fEnergy;
      G4ThreeVector fPos;
      G4ThreeVector fDirection;
};



typedef G4THitsCollection<PSHit> PSHitsCollection;

extern G4ThreadLocal G4Allocator<PSHit>* PSHitAllocator;



inline void* PSHit::operator new(size_t)
{
  if(!PSHitAllocator)
      PSHitAllocator = new G4Allocator<PSHit>;
  return (void *) PSHitAllocator->MallocSingle();
}



inline void PSHit::operator delete(void *hit)
{
  PSHitAllocator->FreeSingle((PSHit*) hit);
}



#endif
