#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

/// Modular physics list for MSC scattering studies
/// Includes EM physics with multiple MSC models for comparison

class PhysicsList : public G4VModularPhysicsList
{
  public:
    PhysicsList();
    virtual ~PhysicsList();

    virtual void SetCuts();
    
    void SetPhysics(const G4String& name);

  private:
    void AddPhysics(const G4String& name);
};

#endif
