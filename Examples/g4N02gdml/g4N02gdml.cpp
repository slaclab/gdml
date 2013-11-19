//
#include <stdexcept>

#include "DetectorConstruction.hh"
#include "ExN02PhysicsList.hh"
#include "ExN02PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4TransportationManager.hh"
#include "G4UImanager.hh"
#include "G4SolidStore.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"

//g4 writer
#include "G4Writer/G4GDMLWriter.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int,char**) {

  // Run manager
  G4RunManager * runManager = new G4RunManager;
  
  // UserInitialization classes (mandatory)
  runManager->SetUserInitialization(new DetectorConstruction);
  runManager->SetUserInitialization(new ExN02PhysicsList);
  runManager->SetUserAction(new ExN02PrimaryGeneratorAction);

  //Initialize G4 kernel
  runManager->Initialize();

  //scaning geometry tree
  G4VPhysicalVolume* g4wv = G4TransportationManager::GetTransportationManager()->
    GetNavigatorForTracking()->GetWorldVolume();
  
  G4GDMLWriter g4writer("http://service-spi.web.cern.ch/service-spi/app/releases/GDML/GDML_2_10_0/src/GDMLSchema/gdml.xsd", 
                        "geo.gdml");

  try
  {
    g4writer.DumpGeometryInfo(g4wv);
  }
  catch(std::logic_error &lerr)
  {
    std::cout << "Caught an exception: " 
              << lerr.what () << std::endl;
  }
  
  G4UImanager * UI = G4UImanager::GetUIpointer();  
  
  UI->ApplyCommand("/control/execute run.mac");
  
  delete runManager;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


