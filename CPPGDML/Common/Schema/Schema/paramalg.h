//
#ifndef PARAMALG_H
#define PARAMALG_H 1

#include "Saxana/SAXObject.h"

#include "Schema/ParameterisationAlgorithmType.h"

class paramalg : public SAXObject, public ParameterisationAlgorithmType
{
public:
  paramalg() {
  }
  virtual ~paramalg() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // PARAMALG_H
