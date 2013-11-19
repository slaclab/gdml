#ifndef QUADRANGULAR_H
#define QUADRANGULAR_H 1

#include "ContentGroup.h"
#include "Saxana/SAXObject.h"
#include "Schema/FacetType.h"

class quadrangular : public SAXObject, public FacetType {
public:
  quadrangular() {
  }
  virtual ~quadrangular() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const std::string& get_vertex1() const {
    return m_vertex1;
  }

  const std::string& get_vertex2() const {
    return m_vertex2;
  }

  const std::string& get_vertex3() const {
    return m_vertex3;
  }
  
  const std::string& get_vertex4() const {
    return m_vertex4;
  }
  
  const std::string& get_type() const {
    return m_type;
  }
  
  void set_vertex1( const std::string& vertex1 ) {
    m_vertex1 = vertex1;
  }
  
  void set_vertex2( const std::string& vertex2 ) {
    m_vertex2 = vertex2;
  }
  
  void set_vertex3( const std::string& vertex3 ) {
    m_vertex3 = vertex3;
  }
  
  void set_vertex4( const std::string& vertex4 ) {
    m_vertex4 = vertex4;
  }
  
  void set_type( const std::string& type ) {
    m_type = type;
  }
  
  const ContentSequence* get_content() const {
    return &m_sequence;
  }
  
  void add_content( const std::string& tag, SAXObject* so ) {
    ContentGroup::ContentItem ci = { tag, so };
    m_sequence.add_content( ci );
  }  
  
private:
  std::string m_vertex1;
  std::string m_vertex2;
  std::string m_vertex3;
  std::string m_vertex4;
  std::string m_type;
  
  ContentSequence m_sequence;
};


#endif // QUADRANGULAR_H
