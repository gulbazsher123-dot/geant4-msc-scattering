#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
 : fScoringVolume(0)
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // World
  G4double world_sizeX = 100*m;
  G4double world_sizeY = 100*m;
  G4double world_sizeZ = 100*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
        0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      true);                 //overlaps checking

  // Detector - Long detector 50 m without gaps
  G4double detectorLength = 50*m;
  G4double detectorWidth = 1*m;
  G4double detectorHeight = 1*m;

  G4Material* detector_mat = nist->FindOrBuildMaterial("G4_Si");

  G4Box* solidDetector =
    new G4Box("Detector",
        0.5*detectorWidth, 0.5*detectorHeight, 0.5*detectorLength);

  G4LogicalVolume* logicDetector =
    new G4LogicalVolume(solidDetector,       //its solid
                        detector_mat,        //its material
                        "Detector");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0., 0., 0.),  //at center
                    logicDetector,           //its logical volume
                    "Detector",              //its name
                    logicWorld,              //its mother volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    true);                   //overlaps checking

  // Set Detector as scoring volume
  fScoringVolume = logicDetector;

  //always return the physical World
  return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
}
