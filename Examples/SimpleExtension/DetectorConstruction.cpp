#include "DetectorConstruction.h"

#include "G4Processor/GDMLProcessor.h"

extern "C" void SimpleExtensionLibLoad();

DetectorConstruction::DetectorConstruction(const std::string& filename)
{
  sxp.Initialize();

  // Load extension processes and subscribers.
  SimpleExtensionLibLoad();

  config.SetURI(filename);
  config.SetSetupName("Default");
  sxp.Configure(&config);
}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  sxp.Run();
  fWorld = (G4VPhysicalVolume*)GDMLProcessor::GetInstance()->GetWorldVolume();
  if (fWorld == 0) {
    G4Exception("", "", FatalException, "GDML failed to setup the world volume.");
  }
  return fWorld;
}
