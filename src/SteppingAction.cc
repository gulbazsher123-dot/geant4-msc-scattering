#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "g4root.hh"

SteppingAction::SteppingAction(
      const DetectorConstruction* detectorConstruction,
      EventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fDetConstruction || !fEventAction) return;

  // get volume of the current step
  G4LogicalVolume* volume = 
    step->GetPreStepPoint()->GetTouchableHandle()->GetLogicalVolume();

  // check if we are in detector
  if(volume != fDetConstruction->GetScoringVolume())
    return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  G4double trackLength = step->GetStepLength();
  analysisManager->FillH1(1, trackLength/CLHEP::m);

  G4double energyLoss = step->GetTotalEnergyDeposit()/CLHEP::MeV;
  if(energyLoss > 0.) {
    analysisManager->FillH1(2, energyLoss);
  }

  // Position along z-axis
  G4double posZ = step->GetPreStepPoint()->GetPosition().z()/CLHEP::m;
  analysisManager->FillH1(3, posZ);

  // Energy vs position
  G4double preEnergy = step->GetPreStepPoint()->GetTotalEnergy()/CLHEP::MeV;
  analysisManager->FillH2(0, posZ, preEnergy);
}
