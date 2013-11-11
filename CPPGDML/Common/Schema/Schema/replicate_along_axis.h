#ifndef REPLICATE_ALONG_AXIS_H
#define REPLICATE_ALONG_AXIS_H 1

#include "Saxana/SAXObject.h"

#include "Schema/ReplicationAlgorithmType.h"

class replicate_along_axis : public SAXObject, public ReplicationAlgorithmType
{
public:
  replicate_along_axis() {
  }
  virtual ~replicate_along_axis() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
};



#endif // REPLICATE_ALONG_AXIS_H
