#include <stdexcept>
#include <iostream>
#include "globals.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIsession.hh"
#include "G4TransportationManager.hh"

#include "gogdmlDetectorConstruction.h"
#include "gogdmlPhysicsList.h"
#include "gogdmlPrimaryGeneratorAction.h"
#include "G4Processor/GDMLProcessor.h"

int main(int argc, char** argv)
{
  // Construct the default run manager

  G4RunManager* runManager = new G4RunManager;

  std::string filename("geo.gdml");
  if (argc>1) filename = argv[1];

  // set mandatory initialization classes
  runManager->SetUserInitialization(new gogdmlDetectorConstruction(filename));
  runManager->SetUserInitialization(new gogdmlPhysicsList);

  // set mandatory user action class
  runManager->SetUserAction(new gogdmlPrimaryGeneratorAction);

  // Initialize G4 kernel
  runManager->Initialize();  
  
  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();  
  UI->ApplyCommand("/control/execute run.mac"); 

  // start a run
  int numberOfEvent = 50;
  runManager->BeamOn(numberOfEvent);



  /////////////////////////////////////AUXILIARY EXAMPLE/////////////////////////////////////////////
  //////////////////////////////AUXILIARY INFORMATION RETRIEVAL//////////////////////////////////////

  GDMLProcessor* processor = GDMLProcessor::GetInstance();
  typedef GDMLProcessor::AuxiliaryPairs::const_iterator auxiter;
  typedef std::vector< std::pair<std::string, std::string> >::const_iterator vect_iter;
  
  //This line retrieves the Map
  const GDMLProcessor::AuxiliaryPairs* auxmap = processor->GetAuxiliaryMap();
  
  std::cout << std::endl << "The following volumes have auxiliary tags:" << std::endl << std::endl;

  for(auxiter a = auxmap->begin(); a != auxmap->end(); a++)
    {
      std::cout << "Volume: " << a->first << " has aux values." << std::endl;
    }
  
  std::cout << std::endl;

  std::cout << "The aux tags matching 'SensDet':" << std::endl << std::endl;

  for(auxiter a = auxmap->begin(); a != auxmap->end(); a++)
    {
      for(vect_iter b = a->second.begin(); b != a->second.end(); b++)
	{
	  std::pair<std::string, std::string> pairvar = *b;
	  
	  const char* auxname = "";
	  auxname = pairvar.second.c_str();

	  if((strcmp("SensDet", auxname)) == 0)
	    {
	      std::cout << "Volume Pointer: " << a->first << ", Aux Value:" << pairvar.first << std::endl; 
	    }

	}
    }
  
  std::cout << std::endl;

  /////////////////////////////////////END OF AUXILIARY EXAMPLE///////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  // job termination
  delete runManager;
  
  return 0;
}
