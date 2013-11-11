//
#ifndef ATOM_HH
#define ATOM_HH 1

#include "Saxana/SAXObject.h"

#include "Schema/AtomType.h"

class atom : public SAXObject, public AtomType
{
public:
  atom() {
  }
  virtual ~atom() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};

#endif // ATOM_HH
