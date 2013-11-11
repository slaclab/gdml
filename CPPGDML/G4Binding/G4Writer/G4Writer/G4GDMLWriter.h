// -*- C++ -*-
// $Id: G4GDMLWriter.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef INCLUDE_G4GDMLWRITER_H 
#define INCLUDE_G4GDMLWRITER_H 1

// Include files
#include "G4RotationMatrix.hh"
#include "G4VSolid.hh"
#include "G4Material.hh"

// GDML
#include "Writer/DocumentBuilder.h"
#include "Writer/DefinitionsCursor.h"
#include "Writer/StructureCursor.h"
#include "Writer/MaterialsCursor.h"
#include "Writer/SolidsCursor.h"
#include "Writer/SetupCursor.h"

#include "G4Writer/Utils.h"
#include "Writer/Vertex.h"

#include "Writer/Element.h"

#include <vector>
#include <string>

// Forward declaration
class G4VPhysicalVolume;

/** @class G4GDMLWriter G4GDMLWriter.h include/G4GDMLWriter.h
 *  
 *
 *  @author Witold POKORSKI
 *  @author Radovan Chytracek
 *  @date   2004-06-23
 */
class G4GDMLWriter
{
public: 
  /// Standard constructor
  G4GDMLWriter( int format=0); 
  G4GDMLWriter( std::string, std::string, int format=0); 
		
  virtual ~G4GDMLWriter(); ///< Destructor
		
  void DumpGeometryInfo( G4VPhysicalVolume* );
  void DumpGeometryInfo( G4VPhysicalVolume*, std::vector<int>, int=0);
  void DumpGeometryInfo( G4VPhysicalVolume*, std::vector<std::string>);
		
private:
  void DumpMaterials();
  void DumpSolids();
  void DumpTessellatedSolidsDefinitions();
  void DumpTetrahedronSolidsDefinitions();
  void DumpGeoTree( G4VPhysicalVolume* );
  void getXYZ( const G4RotationMatrix* , double&, double&, double& ) const;
  std::string processTessSolidVertex(double x, double y, double z);
  std::string processTetVertex(double x, double y, double z);
  
  void DumpMaterial(G4Material* mat);
  void DumpSolid(const G4VSolid* tempsol);
  void DumpGeoTree2(G4VPhysicalVolume* physvol, std::vector<int> levels, int currentLevel);
  void DumpGeoTree2(G4VPhysicalVolume* physvol, std::vector<std::string> volnames);
  
private:
  std::string                      schemaLocation;
  std::string                      outputFile;
  gdml::writer::MaterialsCursor*   matcur;
  gdml::writer::SolidsCursor*      solcur;
  gdml::writer::StructureCursor*   strcur;
  gdml::writer::DefinitionsCursor* defcur;
  gdml::writer::SetupCursor*       stpcur;
  
  int currentFormat;
  
  std::vector<G4LogicalVolume*> lvlist;
  std::vector<Vertex> tessellatedSolidsVertices;
  std::vector<Vertex> tetrahedronSolidsVertices;
  unsigned long int vertixCount;

  Utils* ut;
};

#endif // INCLUDE_G4GDMLWRITER_H
