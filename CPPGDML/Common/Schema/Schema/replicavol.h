//
#ifndef REPLICAVOL_H
#define REPLICAVOL_H 1

#include "Saxana/SAXObject.h"

#include "Schema/ReplicaPlacementType.h"

class replicavol : public SAXObject, public ReplicaPlacementType
{
public:
  replicavol() {
  }
  virtual ~replicavol() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // REPLICAVOL_H
