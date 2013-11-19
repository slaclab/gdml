// -*- C++ -*-
// $Id: volume.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#ifndef GDML_SCHEMA_VOLUME_H
#define GDML_SCHEMA_VOLUME_H 1

#include "Saxana/SAXObject.h"
#include "Schema/VolumeType.h"

class volume : public SAXObject, public VolumeType
{
  public:
    volume() { }
    ~volume() { }
    virtual SAXObject::Type type() { return SAXObject::element; }
};

#endif // GDML_SCHEMA_VOLUME_H
