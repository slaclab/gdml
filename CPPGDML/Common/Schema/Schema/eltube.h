//
#ifndef ELTUBE_H
#define ELTUBE_H 1

#include "Saxana/SAXObject.h"
#include "Schema/SolidType.h"

class eltube : public SolidType {
public:
  eltube() {
  }
  virtual ~eltube() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const std::string& get_dx() const {
    return m_dx;
  }
  const std::string& get_dy() const {
    return m_dy;
  }
  const std::string& get_dz() const {
    return m_dz;
  }
  
  void set_dx( const std::string& dx ) {
    m_dx = dx;
  }
  void set_dy( const std::string& dy ) {
    m_dy = dy;
  }
  void set_dz( const std::string& dz ) {
    m_dz = dz;
  }
  
private:
  std::string m_dx;
  std::string m_dy;
  std::string m_dz;
};



#endif // ELTUBE_H
