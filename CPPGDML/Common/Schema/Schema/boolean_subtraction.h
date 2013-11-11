//
#ifndef BOOLEAN_SUBTRACTION_H
#define BOOLEAN_SUBTRACTION_H 1

#include "Saxana/SAXObject.h"

#include "Schema/BooleanSolidType.h"

class boolean_subtraction : public BooleanSolidType
{
  public:
    boolean_subtraction() {
    }
    virtual ~boolean_subtraction() {
    }
    virtual SAXObject::Type type() {
      return SAXObject::element;
    }
};

#endif // BOOLEAN_SUBTRACTION_H
