#ifndef INCLUDE_STEPWRITER_H 
#define INCLUDE_STEPWRITER_H 1

#include "Writer/DocumentBuilder.h"
#include "Writer/DefinitionsCursor.h"
#include "Writer/StructureCursor.h"
#include "Writer/MaterialsCursor.h"
#include "Writer/SolidsCursor.h"
#include "Writer/SetupCursor.h"
#include "Writer/Element.h"
#include "Writer/Facet.h"

#include "Writer/Vertex.h"
#include "STEPWriter/TessellatedSolid.h"
#include "STEPWriter/LogicalVolume.h"
#include "STEPWriter/PhysicalVolume.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "G4RotationMatrix.hh"

/*
  @class STEPWriter STEPWriter.h include/STEPWriter.h
  

  @author Daniele Francesco KRUSE
  @date   2006-06-16
  
  Write me for any question regarding this code: k.master@fastwebnet.it
  Please read all the comments in STEPWriter.cpp
*/

class STEPWriter
{
 private:
  std::vector<Vertex> vertices;
  std::vector<Vertex> rotations;
  unsigned long int vertixCount;
  unsigned long int rotationCount;
  double maxAbsVertexValue;
  double maxAbsTraslValue;
  double maxAbsPosValue;
  std::vector<TessellatedSolid> tessellatedSolids;
  std::vector<LogicalVolume> logicalVolumes;
  std::vector<PhysicalVolume> physicalVolumes;
  std::string schemaLocation;
  gdml::writer::MaterialsCursor* matcur;
  gdml::writer::SolidsCursor* solcur;
  gdml::writer::StructureCursor* strcur;
  gdml::writer::DefinitionsCursor* defcur;
  gdml::writer::SetupCursor* stpcur;
  
 public: 
  STEPWriter(); 
  ~STEPWriter();		
  void parse(const char* geomFilePath, const char* treeFilePath, const bool dummy);
  void dump(const char* gdmlFilePath, const char* gdmlSchemaPath = "gdml.xsd");
  
 private:
  std::string processVertex(double x, double y, double z, bool dummy, bool secondStage, std::string prefix);
  std::string processRotation(double x, double y, double z, bool dummy);
  double calcWorldDim();
  void getXYZ(const G4RotationMatrix* r, double& x, double& y, double& z) const;
  void DumpMaterials();
  void DumpSolids();
  void DumpGeoTree();
  void DumpDefinitions();
  std::string getLogicalVolumeReference(const std::string tessellatedSolidName);
};

#endif // INCLUDE_STEPWRITER_H
