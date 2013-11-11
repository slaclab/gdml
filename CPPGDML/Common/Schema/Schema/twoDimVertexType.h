#ifndef TWODIMVERTEXTYPE_H
#define TWODIMVERTEXTYPE_H 1

#include "Saxana/SAXObject.h"

class twoDimVertexType : public SAXObject {
public:
  twoDimVertexType() {}
  ~twoDimVertexType() {}
  
  virtual SAXObject::Type type()  { return SAXObject::element; }

  void set_x( const std::string& s ) { m_x = s; }
  void set_y( const std::string& s ) { m_y = s; }

  std::string get_x() const { return m_x; }
  std::string get_y() const { return m_y; }

private:
  std::string m_x;
  std::string m_y;
};


#endif
