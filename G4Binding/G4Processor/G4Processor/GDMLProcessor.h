//
#ifndef GDML_PROCESSOR_H
#define GDML_PROCESSOR_H 1

// G4 includes
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

// Change GDMLExpressionEvaluator package. --JM Mar-27-2006
#include "G4Evaluator/GDMLExpressionEvaluator.h"

#include "G4VSolid.hh"
#include "G4SurfaceProperty.hh"
#include "G4AssemblyVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

#include <string>
#include <stack>
#include <map>

#include "Schema/MatrixType.h"

// Added here in order to resolve properly link dependecies if G4 build system
#include "G4BooleanSolid.hh"
#include "G4CSGSolid.hh"

// Workaround for SUN linker
extern const double defaultTemp;
extern const double defaultPress;

class GDMLProcessor
{
public:
  typedef std::map<std::string,G4ThreeVector*>     Vectors;
  typedef std::map<std::string,G4RotationMatrix*>  Rotations;
  typedef std::map<std::string,MatrixType>         Matrices;
  typedef std::map<std::string,G4VSolid*>          Solids;
  typedef std::map<std::string,G4SurfaceProperty*> Surfaces;
  typedef std::map<std::string,G4LogicalVolume*>   LogicalVolumes;
  typedef std::map<std::string,G4AssemblyVolume*>  AssemblyVolumes;
  typedef std::map<std::string,G4VPhysicalVolume*> PhysicalVolumes;
  typedef std::map<G4LogicalVolume*, std::vector< std::pair<std::string, std::string> > > AuxiliaryPairs;

  static GDMLProcessor* GetInstance();
  void SetDuplicationWarning(const std::string& firstFileName);
  void UnsetDuplicationWarning();

  GDMLExpressionEvaluator* GetEvaluator();

  ~GDMLProcessor();

  void AddPosition( const std::string& name, G4ThreeVector* p );
  void AddPosition( const char* name, G4ThreeVector* p );

  void AddRotation( const std::string& name, G4RotationMatrix* p );
  void AddRotation( const char* name, G4RotationMatrix* p );

  void AddScale( const std::string& name, G4ThreeVector* p );
  void AddScale( const char* name, G4ThreeVector* p );

  void AddMatrix( const std::string& name, MatrixType& m );
  void AddMatrix( const char* name, MatrixType& m );

  void AddSolid( const std::string& name, G4VSolid* p );
  void AddSolid( const char* name, G4VSolid* p );

  void AddSurface( const std::string& name, G4SurfaceProperty* p );
  void AddSurface( const char* name, G4SurfaceProperty* p );

  void AddSurfaceProperty( const std::string& name, G4SurfaceProperty* p );
  void AddSurfaceProperty( const char* name, G4SurfaceProperty* p );

  void AddLogicalVolume( const std::string& name, G4LogicalVolume* p );
  void AddLogicalVolume( const char* name, G4LogicalVolume* p );

  void AddAssemblyVolume( const std::string& name, G4AssemblyVolume* p );
  void AddAssemblyVolume( const char*        name, G4AssemblyVolume* p );

  void AddPhysicalVolume( const std::string& name, G4VPhysicalVolume* p );
  void AddPhysicalVolume( const char* name, G4VPhysicalVolume* p );
  
  void AddParsedFile( const std::string& name, G4VPhysicalVolume* p );
  void AddParsedFile( const char* name, G4VPhysicalVolume* p );

  void AddAuxiliaryVector(G4LogicalVolume* auxvol, std::vector< std::pair<std::string, std::string> >& auxpairs);
  void AddLoopNum(std::string loopnumber);

  const G4ThreeVector*    GetPosition( const std::string& name );
  const G4ThreeVector*    GetPosition( const char* name );

  const G4RotationMatrix* GetRotation( const std::string& name );
  const G4RotationMatrix* GetRotation( const char* name );

  const G4ThreeVector*    GetScale( const std::string& name );
  const G4ThreeVector*    GetScale( const char* name );

  const MatrixType& GetMatrix( const std::string& name );
  const MatrixType& GetMatrix( const char* name );

  const G4VSolid* GetSolid( const std::string& name );
  const G4VSolid* GetSolid( const char* name );

  G4SurfaceProperty* GetSurfaceProperty( const std::string& name );
  G4SurfaceProperty* GetSurfaceProperty( const char* name );

  const G4LogicalVolume* GetLogicalVolume( const std::string& name );
  const G4LogicalVolume* GetLogicalVolume( const char* name );

  const G4AssemblyVolume* GetAssemblyVolume( const std::string& name );
  const G4AssemblyVolume* GetAssemblyVolume( const char* name );

  const G4VPhysicalVolume* GetPhysicalVolume( const std::string& name );
  const G4VPhysicalVolume* GetPhysicalVolume( const char* name );
  
  const G4VPhysicalVolume* GetWorldVolumeOfParsedFile( const std::string& name );
  const G4VPhysicalVolume* GetWorldVolumeOfParsedFile( const char* name );

  const G4VPhysicalVolume* GetWorldVolume()
  {
    return WorldVolumes.at(WorldVolumes.size()-1);
  }
  
  const G4VPhysicalVolume* GetTempWorldVolume()
  {
    return fWorldVolume;
  }
  
  G4VPhysicalVolume* GetWorldVolume(int i)
  {
    return WorldVolumes.at(i);
  }

  GDMLProcessor::AuxiliaryPairs* GetAuxiliaryMap();

  const std::vector< std::pair<std::string, std::string> >* GetAuxiliaryVector(G4LogicalVolume* auxvol);

  std::string GetLoopNum();

  void SetWorldVolume( G4VPhysicalVolume* newWorldVolume )
  {
    fWorldVolume = newWorldVolume;
    WorldVolumes.push_back(newWorldVolume);
  }

  G4ThreeVector* getIdentityPosition()
  {
    return &fIdentityPos;
  }
  
  
  bool alreadyParsed(const std::string& name)
  {
   std::map<std::string,G4VPhysicalVolume*>::iterator i = Files_Volumes_Map.find(name);
   if(i!=Files_Volumes_Map.end()) // found
   {
    return true;
   }
   else
   {
    return false;
   }  
  }
  
  void checkDuplication(const std::string& solidName)
  {
   std::map<std::string,std::string>::iterator i = SolidNames_FileNames_Map.find(solidName);
   if(i!=SolidNames_FileNames_Map.end()) // found
   {
    if(i->second == fileCurrentlyParsed)
    {
     //Should not happen
    }
    else
    {
     std::cout << "Warning!!! Solid named: " << i->first << " was already defined in file: " 
               << i->second << ". It will be instantiated twice!" << std::endl;
    }
   }
   else
   {
    SolidNames_FileNames_Map[solidName] = fileCurrentlyParsed;
   }
  }
  
  bool isDuplicationWarningOn()
  {
   return duplicationWarning;
  }
  
  void currentlyParsing(const std::string& name)
  {
   //std::cout << "PARSING : " << name << std::endl;
   fileCurrentlyParsed = name;
   std::string::size_type loc = name.find_last_of('.');
   std::string new_name = name.substr(0,loc);
   //std::cout<<"pushing: "<<new_name<<std::endl;
   file_name_stack.push(new_name);
   fCalc->setFileCurrentlyParsed(new_name);
  }
  
protected:
  GDMLProcessor();

private:
  GDMLExpressionEvaluator*       fCalc;
  GDMLProcessor::Vectors         fPTable;
  GDMLProcessor::Rotations       fRTable;
  GDMLProcessor::Vectors         fSTable;
  GDMLProcessor::Matrices        fMTable;
  GDMLProcessor::Solids          fSolids;
  GDMLProcessor::AuxiliaryPairs  fAux;
  GDMLProcessor::Surfaces        fSurfaces;
  GDMLProcessor::LogicalVolumes  fLVolumes;
  GDMLProcessor::AssemblyVolumes fAVolumes;
  GDMLProcessor::PhysicalVolumes fPVolumes;
  G4VPhysicalVolume*             fWorldVolume;
  std::string loopnum;
  
  bool duplicationWarning;
  std::map<std::string,std::string> SolidNames_FileNames_Map;
  std::string fileCurrentlyParsed;
  
  std::vector<G4VPhysicalVolume*> WorldVolumes;
  std::map<std::string,G4VPhysicalVolume*> Files_Volumes_Map;
  std::stack<std::string> file_name_stack;

  G4ThreeVector fIdentityPos;
};

#endif // GDML_PROCESSOR_H

