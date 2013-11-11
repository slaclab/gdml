#ifndef PHYSVOLREF_H
#define PHYSVOLREF_H 1

#include "ContentGroup.h"
#include "ReferenceType.h"
    
class physvolref : public SAXObject, public ReferenceType {
public:
  physvolref() {
  }
  virtual ~physvolref() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};
  

#endif // PHYSVOLREF_H
