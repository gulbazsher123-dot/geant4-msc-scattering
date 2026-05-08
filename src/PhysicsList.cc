#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4Decay.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{
  G4int verbosity = 0;
  SetVerboseLevel(verbosity);

  // Default physics
  RegisterPhysics(new G4DecayPhysics(verbosity));

  // EM physics - Standard option for MSC studies
  RegisterPhysics(new G4EmStandardPhysics_option3(verbosity));
}

PhysicsList::~PhysicsList()
{
}

void PhysicsList::SetCuts()
{
  G4double cutForGamma = 1*mm;
  G4double cutForElectron = 1*mm;
  G4double cutForPositron = 1*mm;
  G4double cutForProton = 1*mm;

  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");
  SetCutValue(cutForProton, "proton");

  G4cout << "Physics cuts are set to:"
         << "\n\tGamma: " << G4BestUnit(cutForGamma,"Length")
         << "\n\tElectron: " << G4BestUnit(cutForElectron,"Length")
         << "\n\tPositron: " << G4BestUnit(cutForPositron,"Length")
         << "\n\tProton: " << G4BestUnit(cutForProton,"Length")
         << G4endl;
}

void PhysicsList::SetPhysics(const G4String& name)
{
  if (verboseLevel > 0) {
    G4cout << "PhysicsList::SetPhysics() - "
           << "EM Physics type <" << name << "> is requested" << G4endl;
  }
}
