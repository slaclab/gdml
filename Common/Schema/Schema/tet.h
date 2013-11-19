//
#ifndef TET_H
#define TET_H 1

#include "Saxana/SAXObject.h"

#include "Schema/SolidType.h"

class tet : public SolidType
{
  public:
    tet() {
    }
    virtual ~tet() {
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
  
  private:
    std::string m_vertex1;
    std::string m_vertex2;
    std::string m_vertex3;
    std::string m_vertex4;
};

#endif // TET_H
