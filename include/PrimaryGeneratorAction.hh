#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

/// The primary generator action class with particle gun.
/// Generates muons with configurable energy (100 MeV - 10 GeV)

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* event);

    // Set methods
    void SetParticleEnergy(G4double energy) { fParticleEnergy = energy; }
    void SetParticleType(const G4String& name);

    // Get methods
    G4ParticleGun* GetParticleGun() { return fParticleGun; }

  private:
    G4ParticleGun*  fParticleGun; 
    G4double        fParticleEnergy;
};

#endif
