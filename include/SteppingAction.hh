#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class EventAction;

/// Stepping action class
/// In UserSteppingAction() there are collected the energy deposit and track
/// parameters step by step in event and saved the information of all events
/// in a ElectronBeam class object.

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(DetectorConstruction* detectorConstruction,
                   EventAction* eventAction);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step* step);

  private:
    DetectorConstruction*  fDetConstruction;
    EventAction*           fEventAction;
};

#endif
