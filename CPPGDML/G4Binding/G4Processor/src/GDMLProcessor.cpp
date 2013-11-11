#include "G4Processor/GDMLProcessor.h"

// Declare the external component system initialization routines
//extern "C" 
void GDMLProcessLibLoad();
//extern "C" 
void GDMLSubscriberLibLoad();

const double defaultTemp  = STP_Temperature;
const double defaultPress = STP_Pressure;

static GDMLProcessor* sProcessor = 0;

GDMLProcessor* GDMLProcessor::GetInstance()
{
  if( sProcessor == 0 )
  {
    sProcessor = new GDMLProcessor();
    std::string no_filename = "";
    sProcessor->currentlyParsing(no_filename);
  }  
  return sProcessor;
}

void GDMLProcessor::SetDuplicationWarning(const std::string& firstFileName)
{
 file_name_stack.pop(); //removing no_filename entry
 currentlyParsing(firstFileName); //It's not nice to call this method here, this is due to backward compatibility issues
 duplicationWarning = true;
}

void GDMLProcessor::UnsetDuplicationWarning()
{
 duplicationWarning = false;
}

GDMLExpressionEvaluator* GDMLProcessor::GetEvaluator()
{
  return fCalc;
}
  
GDMLProcessor::~GDMLProcessor() {

	if( fCalc != 0 ) {

		delete fCalc;
		fCalc = 0;
	}
	
	GDMLProcessor::Vectors::iterator         pit;
	GDMLProcessor::Rotations::iterator       rit;
	GDMLProcessor::Vectors::iterator        scit;
	GDMLProcessor::Solids::iterator          sit;
	GDMLProcessor::LogicalVolumes::iterator  lvit;
	GDMLProcessor::AssemblyVolumes::iterator avit;
	GDMLProcessor::PhysicalVolumes::iterator pvit;
  
  for( pit = fPTable.begin(); pit != fPTable.end(); pit++ )
  {
    G4ThreeVector* victim = (*pit).second;
    if( victim != 0 )
    {
      delete victim;
    }
  }

  for( rit = fRTable.begin(); rit != fRTable.end(); rit++ )
  {
    G4RotationMatrix* victim = (*rit).second;
    if( victim != 0 )
    {
      delete victim;
    }
  }

	for( scit = fSTable.begin(); scit != fSTable.end(); scit++ ) {
		
		G4ThreeVector* victim = (*scit).second;
		if( victim != 0 ) delete victim;
	}

  for( sit = fSolids.begin(); sit != fSolids.end(); sit++ )
  {
    G4VSolid* victim = (*sit).second;
    if( victim != 0 )
    {
      delete victim;
    }
  }
  for( lvit = fLVolumes.begin(); lvit != fLVolumes.end(); lvit++ )
  {
    G4LogicalVolume* victim = (*lvit).second;
    if( victim != 0 )
    {
      delete victim;
    }
  }
  for( avit = fAVolumes.begin(); avit != fAVolumes.end(); avit++ )
  {
    G4AssemblyVolume* victim = (*avit).second;
    if( victim != 0 )
    {
      delete victim;
    }
  }
  for( pvit = fPVolumes.begin(); pvit != fPVolumes.end(); pvit++ )
  {
    G4VPhysicalVolume* victim = (*pvit).second;
    if( victim != 0 )
    {
      delete victim;
    }
  }
}

void GDMLProcessor::AddPosition( const std::string& name, G4ThreeVector* p )
{
  fPTable[name+file_name_stack.top()] = p;
}

void GDMLProcessor::AddPosition( const char* name, G4ThreeVector* p )
{
  std::string key = name;
  AddPosition( key, p );
}

void GDMLProcessor::AddRotation( const std::string& name, G4RotationMatrix* p )
{
  fRTable[name+file_name_stack.top()] = p;
}

void GDMLProcessor::AddRotation( const char* name, G4RotationMatrix* p )
{
  std::string key = name;
  AddRotation( key, p );
}

void GDMLProcessor::AddScale( const std::string& name, G4ThreeVector* p )
{
  fSTable[name+file_name_stack.top()] = p;
}

void GDMLProcessor::AddScale( const char* name, G4ThreeVector* p )
{
  std::string key = name;
  AddScale( key, p );
}

void GDMLProcessor::AddMatrix( const std::string& name, MatrixType& p )
{
  fMTable[name+file_name_stack.top()] = p;
}

void GDMLProcessor::AddMatrix( const char* name, MatrixType& p )
{
  std::string key = name;
  AddMatrix( key, p );
}

void GDMLProcessor::AddSolid( const std::string& name, G4VSolid* p )
{
  fSolids[name+file_name_stack.top()] = p;
  if(duplicationWarning)
  {
   checkDuplication(name);
  }
}
void GDMLProcessor::AddSolid( const char* name, G4VSolid* p )
{
  std::string key = name;
  AddSolid( key, p );
}

void GDMLProcessor::AddSurfaceProperty( const std::string& name, G4SurfaceProperty* p )
{
  fSurfaces[name] = p;
  if(duplicationWarning)
  {
   checkDuplication(name);
  }
}
void GDMLProcessor::AddSurfaceProperty( const char* name, G4SurfaceProperty* p )
{
  std::string key = name;
  AddSurfaceProperty( key, p );
}

void GDMLProcessor::AddLogicalVolume( const std::string& name, G4LogicalVolume* p )
{
  fLVolumes[name+file_name_stack.top()] = p;
}
void GDMLProcessor::AddLogicalVolume( const char* name, G4LogicalVolume* p )
{
  std::string key = name;
  AddLogicalVolume( key, p );
}

void GDMLProcessor::AddParsedFile( const std::string& name, G4VPhysicalVolume* p )
{
  Files_Volumes_Map[name] = p;
  std::string::size_type loc = name.find_last_of('.');
  std::string new_name = name.substr(0,loc);
  if(new_name!=file_name_stack.top())
  {
   std::cout<<"[ERROR] FILE NAME STACK !!! file_name_stack.top(): " << file_name_stack.top() << " name: " << new_name <<std::endl;
   return;
  }
  file_name_stack.pop();
  fCalc->setFileCurrentlyParsed(file_name_stack.top());
}
void GDMLProcessor::AddParsedFile( const char* name, G4VPhysicalVolume* p )
{
  std::string key = name;
  AddParsedFile( key, p );
}

void GDMLProcessor::AddAssemblyVolume( const std::string& name, G4AssemblyVolume* p )
{
  fAVolumes[name+file_name_stack.top()] = p;
}
void GDMLProcessor::AddAssemblyVolume( const char* name, G4AssemblyVolume* p )
{
  std::string key = name;
  AddAssemblyVolume( key, p );
}

void GDMLProcessor::AddPhysicalVolume( const std::string& name, G4VPhysicalVolume* p )
{
  fPVolumes[name+file_name_stack.top()] = p;
}
void GDMLProcessor::AddPhysicalVolume( const char* name, G4VPhysicalVolume* p )
{
  std::string key = name;
  AddPhysicalVolume( key, p );
}

void GDMLProcessor::AddAuxiliaryVector(G4LogicalVolume* auxvol, std::vector< std::pair<std::string, std::string> >& auxpairs)
{
  fAux[auxvol] = auxpairs;
}

void GDMLProcessor::AddLoopNum(std::string loopnumber)
{
  loopnum = loopnumber;
}

const G4ThreeVector*    GDMLProcessor::GetPosition( const std::string& name )
{
  return fPTable[name+file_name_stack.top()];
}

const G4ThreeVector*    GDMLProcessor::GetPosition( const char* name )
{
  std::string key = name;
  return GetPosition( key );
}

const G4RotationMatrix* GDMLProcessor::GetRotation( const std::string& name )
{
  return fRTable[name+file_name_stack.top()];
}

const G4RotationMatrix* GDMLProcessor::GetRotation( const char* name )
{
  std::string key = name;
  return GetRotation( key );
}

const G4ThreeVector*    GDMLProcessor::GetScale( const std::string& name )
{
  return fSTable[name+file_name_stack.top()];
}

const G4ThreeVector*    GDMLProcessor::GetScale( const char* name )
{
  std::string key = name;
  return GetScale( key );
}

const MatrixType& GDMLProcessor::GetMatrix( const std::string& name )
{
  return fMTable[name+file_name_stack.top()];
}

const MatrixType& GDMLProcessor::GetMatrix( const char* name )
{
  std::string key = name;
  return GetMatrix( key );
}

const G4VSolid* GDMLProcessor::GetSolid( const std::string& name )
{
  return fSolids[name+file_name_stack.top()];
}

const G4VSolid* GDMLProcessor::GetSolid( const char* name )
{
  std::string key = name;
  return GetSolid( key );
}

G4SurfaceProperty* GDMLProcessor::GetSurfaceProperty( const std::string& name )
{
  return fSurfaces[name];
}

G4SurfaceProperty* GDMLProcessor::GetSurfaceProperty( const char* name )
{
  std::string key = name;
  return GetSurfaceProperty( key );
}

const G4LogicalVolume* GDMLProcessor::GetLogicalVolume( const std::string& name )
{
  return fLVolumes[name+file_name_stack.top()];
}

const G4LogicalVolume* GDMLProcessor::GetLogicalVolume( const char* name )
{
  std::string key = name;
  return GetLogicalVolume( key );
}

const G4AssemblyVolume* GDMLProcessor::GetAssemblyVolume( const std::string& name )
{
  return fAVolumes[name+file_name_stack.top()];
}

const G4AssemblyVolume* GDMLProcessor::GetAssemblyVolume( const char* name )
{
  std::string key = name;
  return GetAssemblyVolume( key );
}

const G4VPhysicalVolume* GDMLProcessor::GetPhysicalVolume( const std::string& name )
{
  return fPVolumes[name+file_name_stack.top()];
}

const G4VPhysicalVolume* GDMLProcessor::GetPhysicalVolume( const char* name )
{
  std::string key = name;
  return GetPhysicalVolume( key );
}

const G4VPhysicalVolume* GDMLProcessor::GetWorldVolumeOfParsedFile( const std::string& name )
{
  return Files_Volumes_Map[name];
}

const G4VPhysicalVolume* GDMLProcessor::GetWorldVolumeOfParsedFile( const char* name )
{
  std::string key = name;
  return GetWorldVolumeOfParsedFile( key );
}

GDMLProcessor::AuxiliaryPairs* GDMLProcessor::GetAuxiliaryMap()
{
  return &fAux;
}

const std::vector< std::pair<std::string, std::string> >* GDMLProcessor::GetAuxiliaryVector(G4LogicalVolume* auxvol)
{
  return &fAux[auxvol];
}

std::string GDMLProcessor::GetLoopNum()
{
  return loopnum;
}

GDMLProcessor::GDMLProcessor()
: fCalc( 0 ), fWorldVolume( 0 )
{
  fCalc = new GDMLExpressionEvaluator();
  duplicationWarning = false;
  
  // We need to initialize our component system
  GDMLProcessLibLoad();
  GDMLSubscriberLibLoad();
}


