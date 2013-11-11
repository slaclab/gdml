//
#ifndef gogdmlDetectorConstruction_H
#define gogdmlDetectorConstruction_H 1

class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

#include "Saxana/SAXProcessor.h"
#include "Saxana/ProcessingConfigurator.h"

class gogdmlDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    gogdmlDetectorConstruction();
    gogdmlDetectorConstruction(std::string& filename);
    ~gogdmlDetectorConstruction();

  public:
    G4VPhysicalVolume* Construct();

  private:
    SAXProcessor sxp;
    ProcessingConfigurator config;
    G4VPhysicalVolume* fWorld;
};

#endif

