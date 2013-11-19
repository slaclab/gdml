// -*- C++ -*-
// $Id: boolean_union.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#ifndef GDML_SCHEMA_BOOLEAN_UNION_H
#define GDML_SCHEMA_BOOLEAN_UNION_H 1

#include "Saxana/SAXObject.h"

#include "Schema/BooleanSolidType.h"

class boolean_union : public BooleanSolidType
{
  public:
    boolean_union() {
    }
    virtual ~boolean_union() {
    }
    virtual SAXObject::Type type() {
      return SAXObject::element;
    }
};

#endif // GDML_SCHEMA_BOOLEAN_UNION_H
