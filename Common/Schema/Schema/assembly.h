// -*- C++ -*-
// $Id: assembly.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#ifndef GDML_SCHEMA_ASSEMBLY_H
#define GDML_SCHEMA_ASSEMBLY_H 1

#include "Saxana/SAXObject.h"
#include "Schema/AssemblyVolumeType.h"

class assembly : public SAXObject, public AssemblyVolumeType
{
public:
  assembly() {
  }
  virtual ~assembly() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};

#endif // GDML_SCHEMA_ASSEMBLY_H
