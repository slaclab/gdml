//
#ifndef WIDTH_H
#define WIDTH_H 1

#include "Saxana/SAXObject.h"

#include "Schema/DimensionsType.h"

class width : public SAXObject, public QuantityType
{
public:
  width() {
  }
  virtual ~width() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // WIDTH_H
