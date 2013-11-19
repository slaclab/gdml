//
#ifndef SKINSURFACE_H
#define SKINSURFACE_H 1

#include "Saxana/SAXObject.h"
#include "Schema/LogicalSurfaceType.h"
#include "Schema/ReferenceType.h"
#include "Schema/ContentGroup.h"

class skinsurface : public SAXObject, public LogicalSurfaceType {
public:
  
  class volumeref : public SAXObject, public ReferenceType {
  public:
    volumeref() {
    }
    virtual ~volumeref() {
    }
    virtual SAXObject::Type type() {
      return SAXObject::element;
    }
  };
  
  skinsurface() {
  }
  virtual ~skinsurface() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;  
  }
  
  const ContentSequence* get_content() const
  {
    return &m_sequence;
  }
  void add_content( const std::string& tag, SAXObject* so )
  {
    ContentGroup::ContentItem ci = { tag, so };
    m_sequence.add_content( ci );
  }
  
private:
  ContentSequence m_sequence;
};



#endif // SKINSURFACE_H
