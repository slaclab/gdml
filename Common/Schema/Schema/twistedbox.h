//
#ifndef TWISTEDBOX_H
#define TWISTEDBOX_H 1

#include "Saxana/SAXObject.h"
#include "Schema/SolidType.h"

class twistedbox : public SolidType {
public:
  twistedbox() {
  }
  virtual ~twistedbox() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const std::string& get_pDx() const {
    return m_pDx;
  }
  const std::string& get_pDy() const {
    return m_pDy;
  }
  const std::string& get_pDz() const {
    return m_pDz;
  }
  const std::string& get_pPhiTwist() const {
    return m_pPhiTwist;
  }
  
  void set_pDx( const std::string& pDx ) {
    m_pDx = pDx;
  }
  void set_pDy( const std::string& pDy ) {
    m_pDy = pDy;
  }
  void set_pDz( const std::string& pDz ) {
    m_pDz = pDz;
  }
  void set_pPhiTwist( const std::string& pPhiTwist ) {
    m_pPhiTwist = pPhiTwist;
  }
  
private:
  std::string m_pDx;
  std::string m_pDy;
  std::string m_pDz;
  std::string m_pPhiTwist;
};



#endif // TWISTEDBOX_H
