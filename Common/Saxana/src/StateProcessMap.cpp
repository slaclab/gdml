//
#include "Saxana/StateProcessMap.h"
#include "Saxana/SAXComponentFactoryTable.h"
#include "Saxana/SAXComponentFactory.h"

#include <iostream>

StateProcessMap::StateProcessMap()
{
#ifdef GDML_VERBOSE
  std::cout << "State process map created" << std::endl;
#endif
}

StateProcessMap::~StateProcessMap()
{
  Reset();
}

void StateProcessMap::Initialize()
{
  SAXComponentFactoryTable* FTable = SAXComponentFactoryTable::GetInstance();
  const SAXComponentFactoryTable::Components* factories;
  
  factories = FTable->GetComponents( SAXComponentObject::eProcess );
  
  SAXComponentFactoryTable::Components::const_iterator pit;
  
  StateProcessMap::Process process;
  for( pit = factories->begin(); pit != factories->end(); pit++ )
  {
    process = dynamic_cast<SAXStateProcess*>( (*pit)->Build() );
    
#ifdef GDML_VERBOSE
    std::cout << "Adding state process for tag: " << process->State() << std::endl;
#endif
    
    AddProcess( process->State(), process );
  }
#ifdef GDML_VERBOSE
  std::cout << "========================================================" << std::endl;
#endif
}

void StateProcessMap::Reset()
{
  fMap.clear();
}

void StateProcessMap::AddProcess( const std::string& tag, StateProcessMap::Process process )
{
  fMap[tag] = process;
}

void StateProcessMap::AddProcess( char* tag, StateProcessMap::Process process )
{
  std::string key = tag;
  AddProcess( key, process );
}

bool StateProcessMap::Check( const std::string& tag )
{
  return( ( fMap.find( tag ) != fMap.end() ) ? true : false );
}

bool StateProcessMap::Check( char*        tag )
{
  std::string key = tag;
  return( Check( key ) );
}

StateProcessMap::Process StateProcessMap::GetProcess( const std::string& tag )
{
  return( fMap[tag] );
}

StateProcessMap::Process StateProcessMap::GetProcess( char*        tag )
{
  std::string key = tag;
  return( GetProcess( key ) );
}


