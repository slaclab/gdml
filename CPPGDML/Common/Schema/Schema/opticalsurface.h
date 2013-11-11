//
#ifndef OPTICALSURFACE_H
#define OPTICALSURFACE_H 1

#include "Saxana/SAXObject.h"
#include "Schema/SurfacePropertyType.h"

class opticalsurface : public SAXObject, public SurfacePropertyType {
public:
  opticalsurface() {
  }
  virtual ~opticalsurface() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const std::string& get_model() const {
    return m_model;
  }
  const std::string& get_finish() const {
    return m_finish;
  }
  const std::string& get_value() const {
    return m_value;
  }
  
  void set_model( const std::string& model ) {
    m_model = model;
  }
  void set_finish( const std::string& finish ) {
    m_finish = finish;
  }
  void set_value( const std::string& value ) {
    m_value = value;
  }
  
private:
  std::string m_model;
  std::string m_finish;
  std::string m_value;
};



#endif // OPTICALSURFACE_H
