//
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "gogdmlDetectorConstruction.h"

#include "G4Processor/GDMLProcessor.h"

// Added here just to help resolve properly dependencies
#include "G4BooleanSolid.hh"
#include "G4CSGSolid.hh"

gogdmlDetectorConstruction::gogdmlDetectorConstruction()
{
  sxp.Initialize();
  config.SetURI( "opticalsurfaces.gdml" );
  config.SetSetupName( "Default" );
  sxp.Configure( &config );

}

gogdmlDetectorConstruction::gogdmlDetectorConstruction(std::string& filename)
{
  sxp.Initialize();
  config.SetURI(filename);
  config.SetSetupName( "Default" );
  sxp.Configure( &config );
}

gogdmlDetectorConstruction::~gogdmlDetectorConstruction()
{
  sxp.Finalize();
}

G4VPhysicalVolume* gogdmlDetectorConstruction::Construct()
{ 
  sxp.Run();
  
  fWorld =  (G4VPhysicalVolume *)GDMLProcessor::GetInstance()->GetWorldVolume();

//  fWorld->GetLogicalVolume()->SetVisAttributes (G4VisAttributes::Invisible);
  
  if( fWorld == 0 ) {
    G4Exception("", "", FatalException, "GDML failed to setup the world volume.");
  }
  return fWorld;
}

