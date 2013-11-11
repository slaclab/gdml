#ifndef DIRECTION_H
#define DIRECTION_H 1

#include "Saxana/SAXObject.h"

#include "Schema/directionType.h"

class direction : public SAXObject, public directionType
{
public:
  direction() {
  }
  virtual ~direction() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // DIRECTION_H
