#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"
#include <iomanip>

RunAction::RunAction()
 : G4UserRunAction(),
   fEdepTotal(0.)
{
  // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName("mscScattering");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);

  // Creating histograms
  analysisManager->CreateH1("Edep","Energy deposition (MeV)", 100, 0., 10000.);
  analysisManager->CreateH1("TrackLength","Track length (m)", 100, 0., 50.);
  analysisManager->CreateH1("EnergyLoss","Energy loss per step (MeV)", 100, 0., 100.);
  analysisManager->CreateH1("AbsorptionProfile","Absorption along detector (m)", 100, -25., 25.);
  analysisManager->CreateH2("EnergyVsPosition","Energy vs Position", 
                            50, -25., 25., 50, 0., 10000.);
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Print histogram statistics
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic "
           << analysisManager->GetFileName() << G4endl;

    G4cout << " EnergyDeposition : mean = "
           << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy")
           << " rms = "
           << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;

    G4cout << " TrackLength : mean = "
           << G4BestUnit(analysisManager->GetH1(1)->mean(), "Length")
           << " rms = "
           << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Length") << G4endl;
  }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();

  G4cout << "\n ----> Histograms and ntuples are saved in: "
         << analysisManager->GetFileName() << ".root"
         << G4endl;
}
