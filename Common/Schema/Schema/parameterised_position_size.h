//
#ifndef PARAMETERISED_POSITION_SIZE_H
#define PARAMETERISED_POSITION_SIZE_H 1

#include "Saxana/SAXObject.h"

#include "Schema/ParameterisationAlgorithmType.h"

class parameterised_position_size : public SAXObject, public ParameterisationAlgorithmType
{
public:
  parameterised_position_size() {
  }
  virtual ~parameterised_position_size() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // PARAMETERISED_POSITION_SIZE_H
