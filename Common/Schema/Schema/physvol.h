//
#ifndef PHYSVOL_H
#define PHYSVOL_H 1

#include "Saxana/SAXObject.h"

#include "Schema/SinglePlacementType.h"

class physvol : public SAXObject, public SinglePlacementType
{
public:
  physvol() {
  }
  virtual ~physvol() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // PHYSVOL_H
