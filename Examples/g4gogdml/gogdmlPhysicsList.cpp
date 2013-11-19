//
#include "G4ParticleTypes.hh"

#include "gogdmlPhysicsList.h"

gogdmlPhysicsList::gogdmlPhysicsList()
{;}

gogdmlPhysicsList::~gogdmlPhysicsList()
{;}

void gogdmlPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  G4Geantino::GeantinoDefinition();
}

void gogdmlPhysicsList::ConstructProcess()
{
  // Define transportation process

  AddTransportation();
}

void gogdmlPhysicsList::SetCuts()
{
  // uppress error messages even in case e/gamma/proton do not exist            
  G4int temp = GetVerboseLevel(); 
  SetVerboseLevel(0);
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types 
  SetCutsWithDefault();   

  // Retrieve verbose level
  SetVerboseLevel(temp);  
}

