#include "stackingaction.hh"
#include "G4Track.hh"
#include "G4Gamma.hh"

StackingAction::StackingAction()
{}
StackingAction::~StackingAction()
{}
G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track *track)
{
    if(track->GetDefinition() == G4Gamma::Gamma()) return fUrgent;
    else return fKill;
}
