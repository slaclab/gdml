//
#ifndef DIVISIONVOL_H
#define DIVISIONVOL_H 1

#include "Saxana/SAXObject.h"

#include "Schema/DivisionPlacementType.h"

class divisionvol : public SAXObject, public DivisionPlacementType
{
public:
  divisionvol() {
  }
  virtual ~divisionvol() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // DIVISIONVOL_H
