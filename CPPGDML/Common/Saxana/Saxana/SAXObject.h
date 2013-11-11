// -*- C++ -*-
// $Id: SAXObject.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#ifndef GDML_SAXANA_SAXOBJECT_H
#define GDML_SAXANA_SAXOBJECT_H 1

#include "SAXObjectBase.h"

#include <string>

class SAXObject : virtual public SAXObjectBase
{
public:
  typedef enum {
    element,             // element
    contentGroup,        // choice, sequence, all
    attributeGroup,      // reusable group of attributes
    elementGroup         // reusable group of elements
  } Type;
    
public:
  virtual ~SAXObject() {
  }

  virtual bool IsCacheable() const
  {
    return false;
  }
  
  virtual Type type() = 0;
};

#endif // GDML_SAXANA_SAXOBJECT_H

