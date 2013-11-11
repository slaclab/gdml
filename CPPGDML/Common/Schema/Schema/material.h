// -*- C++ -*-
// $Id: material.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_ELEMENT_H
#define GDML_SCHEMA_ELEMENT_H 1

#include "MaterialMixtureType.h"

class material : public SAXObject,
                 public MaterialMixtureType
{
  public:
    material()
    {
    }
    ~material()
    {
    }
    virtual SAXObject::Type type()
    {
      return SAXObject::element;
    }
};

#endif // ELEMENT_H
