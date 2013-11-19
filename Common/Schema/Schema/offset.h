//
#ifndef OFFSET_H
#define OFFSET_H 1

#include "Saxana/SAXObject.h"

#include "Schema/DimensionsType.h"

class offset : public SAXObject, public QuantityType
{
public:
  offset() {
  }
  virtual ~offset() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // OFFSET_H
