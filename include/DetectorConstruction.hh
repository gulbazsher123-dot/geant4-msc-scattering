#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.
/// A long detector (50 m) without gaps for MSC scattering studies.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // Get methods
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  private:
    // Logical volumes
    G4LogicalVolume*  fScoringVolume;
};

#endif
