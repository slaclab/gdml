//
#ifndef BORDERSURFACE_H
#define BORDERSURFACE_H 1

#include "Saxana/SAXObject.h"
#include "Schema/LogicalSurfaceType.h"
#include "Schema/ReferenceType.h"
#include "Schema/ContentGroup.h"

class bordersurface : public SAXObject, public LogicalSurfaceType {
public:
    
  bordersurface() {
  }
  virtual ~bordersurface() {
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



#endif // BORDERSURFACE_H
