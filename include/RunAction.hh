#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class
/// In EndOfRunAction(), it calculates the dose averaged over the selected
/// volume of a given event and event-by-event those passed randomness tests.
/// It prints the results only if an event modifies the energy deposition
/// histogram.
///
/// The histograms are saved in the output file specified in a macro file or
/// by the default filename set here.

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);

    void AddEdep(G4double edep) { fEdepTotal += edep; }

  private:
    G4double fEdepTotal;
};

#endif
