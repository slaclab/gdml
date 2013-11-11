#ifndef TESSELLATED_H
#define TESSELLATED_H 1

#include "ContentGroup.h"
#include "Saxana/SAXObject.h"
#include "Schema/SolidType.h"

class tessellated : public SolidType {
public:
  tessellated() {
  }
  virtual ~tessellated() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const ContentSequence* get_content() const {
    return &m_sequence;
  }
  
  void add_content( const std::string& tag, SAXObject* so ) {
    ContentGroup::ContentItem ci = { tag, so };
    m_sequence.add_content( ci );
  }  
  
private:
  ContentSequence m_sequence;
};


#endif // TESSELLATED_H
