# Geant4 MSC Scattering Simulation

A comprehensive Geant4 program for studying Multiple Scattering Coulomb (MSC) effects in electromagnetic physics using muons.

## Overview

This simulation studies the behavior of muons as they travel through a long detector (50 m) with continuous material (no gaps). The program allows comparison of different MSC models across the muon energy range where model characteristics overlap (100 MeV - 10 GeV).

## Features

- **Long Detector Geometry**: 50 m silicon detector with no gaps
- **Muon Beam**: Configurable energy (100 MeV - 10 GeV)
- **Multiple MSC Models**: Standard EM physics implementations for model comparison
- **Comprehensive Analysis**:
  - Energy loss distributions
  - Absorption profiles along detector
  - Track length analysis
  - Energy vs position 2D histograms
- **Histogram Output**: ROOT-based analysis with automatic plot generation

## Physics

### MSC Models Studied
- Urban MSC (default, option 3)
- Wentzel MSC (via G4UrbanMscModel variants)
- Penelope MSC (available via PhysicsList modifications)

### Particle
- Muons (μ⁻)

### Energy Range
- 100 MeV to 10 GeV (region of model overlap)

## Building

### Prerequisites
- Geant4 (version 10.7 or later recommended)
- CMake (3.16 or later)
- C++11 compiler

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

Optional: Build with visualization support
```bash
cmake -DWITH_GEANT4_UIVIS=ON ..
```

## Running

### Interactive Mode
```bash
./mscScattering
# Then in the Geant4 prompt:
/control/execute run.mac
```

### Batch Mode
```bash
./mscScattering run.mac
```

## Macro Files

- **init_vis.mac**: Initialization with visualization
- **run.mac**: Simulation configuration and beam parameters
- **vis.mac**: Detailed visualization settings

## Output

The simulation produces:
- **mscScattering.root**: ROOT file containing histograms:
  - Edep: Total energy deposition (MeV)
  - TrackLength: Track length distribution (m)
  - EnergyLoss: Energy loss per step (MeV)
  - AbsorptionProfile: Absorption distribution along z-axis (m)
  - EnergyVsPosition: 2D correlation histogram

## Analysis

Histograms can be analyzed using ROOT:

```bash
root -l mscScattering.root
root> Edep->Draw()
root> EnergyVsPosition->Draw("colz")
```

## Customization

### Change Particle Energy
Edit `src/PrimaryGeneratorAction.cc`:
```cpp
fParticleEnergy = 500*MeV;  // Change to desired energy
```

### Change Number of Events
Edit `run.mac`:
```
/run/beamOn 1000  # Change event count
```

### Switch EM Physics Models
Edit `src/PhysicsList.cc` to select different physics:
```cpp
RegisterPhysics(new G4EmStandardPhysics_option1(verbosity));  // Different option
RegisterPhysics(new G4EmLivermorePhysics(verbosity));         // Livermore
RegisterPhysics(new G4EmPenelopePhysics(verbosity));          // Penelope
```

### Modify Detector Geometry
Edit `src/DetectorConstruction.cc`:
```cpp
G4double detectorLength = 50*m;    // Change detector length
G4double detectorWidth = 1*m;      // Change width
G4double detectorHeight = 1*m;     // Change height
```

## File Structure

```
.
├── CMakeLists.txt                 # Build configuration
├── README.md                       # This file
├── mscScattering.cc               # Main program
├── include/
│   ├── DetectorConstruction.hh     # Geometry definition
│   ├── PhysicsList.hh              # Physics selection
│   ├── PrimaryGeneratorAction.hh   # Particle gun
│   ├── RunAction.hh                # Run-level analysis
│   ├── EventAction.hh              # Event-level analysis
│   └── SteppingAction.hh           # Step-by-step analysis
├── src/
│   ├── DetectorConstruction.cc
│   ├── PhysicsList.cc
│   ├── PrimaryGeneratorAction.cc
│   ├── RunAction.cc
│   ├── EventAction.cc
│   └── SteppingAction.cc
├── init_vis.mac                   # Interactive visualization setup
├── run.mac                        # Standard run configuration
└── vis.mac                        # Visualization macro

```

## References

- [Geant4 Official Documentation](https://geant4.kek.jp/)
- [Geant4 EM Physics](https://geant4.kek.jp/Reference/current/classG4EmStandardPhysics.html)
- [Multiple Scattering in Geant4](https://geant4.kek.jp/Reference/current/classG4UrbanMscModel.html)

## License

This example follows the Geant4 software license.

## Contact & Support

For issues or questions about this implementation, please refer to the Geant4 user forum and documentation.
