#ifndef DETECTORCONSTRUCTION_H
#define DETECTORCONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"

#include "Saxana/SAXProcessor.h"
#include "Saxana/ProcessingConfigurator.h"

class DetectorConstruction : public G4VUserDetectorConstruction
{
 public:
  DetectorConstruction(const std::string& filename);
  virtual ~DetectorConstruction();
  
 public:
  G4VPhysicalVolume* Construct();
  
 private:
  SAXProcessor sxp;
  ProcessingConfigurator config;
  G4VPhysicalVolume* fWorld;  
};

#endif
