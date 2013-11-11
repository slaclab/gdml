//
#ifndef DIMENSIONS_H
#define DIMENSIONS_H 1

#include "Saxana/SAXObject.h"

#include "Schema/DimensionsType.h"

class dimensions : public SAXObject, public DimensionsType
{
public:
  dimensions() {
  }
  virtual ~dimensions() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // DIMENSIONS_H
