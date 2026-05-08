#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0),
   fParticleEnergy(1000*MeV)  // Default 1 GeV muon
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleDefinition* particleDefinition =
    G4ParticleTable::GetParticleTable()->FindParticle("mu-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(fParticleEnergy);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of ecah event
  // Distribution of primaries is uniform in a plane

  G4double z0 = -24.5*m;  // Start at one end of 50m detector
  G4double x0 = 0.;
  G4double y0 = 0.;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));
  fParticleGun->SetParticleEnergy(fParticleEnergy);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::SetParticleType(const G4String& name)
{
  G4ParticleDefinition* particleDefinition =
    G4ParticleTable::GetParticleTable()->FindParticle(name);
  fParticleGun->SetParticleDefinition(particleDefinition);
}
