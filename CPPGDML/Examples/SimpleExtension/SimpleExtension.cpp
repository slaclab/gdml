#include <stdexcept>

#include "globals.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIsession.hh"

#include "DetectorConstruction.h"
#include "PhysicsList.h"
#include "PrimaryGeneratorAction.h"

int main(int argc, char** argv)
{
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  std::string filename("test.gdml");
  if (argc>1) filename = argv[1];

  // set mandatory initialization classes
  runManager->SetUserInitialization(new DetectorConstruction(filename));
  runManager->SetUserInitialization(new PhysicsList);

  // set mandatory user action class
  runManager->SetUserAction(new PrimaryGeneratorAction);

  // Initialize G4 kernel
  runManager->Initialize();  
  
  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();  
  UI->ApplyCommand("/control/execute run.mac"); 

  // start a run
  int numberOfEvent = 1;
  runManager->BeamOn(numberOfEvent);

  // job termination
  delete runManager;
  
  return 0;
}


