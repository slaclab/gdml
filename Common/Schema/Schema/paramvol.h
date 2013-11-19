//
#ifndef PARAMVOL_H
#define PARAMVOL_H 1

#include "Saxana/SAXObject.h"

#include "Schema/ParameterisedPlacementType.h"

class paramvol : public SAXObject, public ParameterisedPlacementType
{
public:
  paramvol() {
  }
  virtual ~paramvol() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // PARAMVOL_H
