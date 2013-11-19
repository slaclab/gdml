//
#ifndef TWISTEDTRD_H
#define TWISTEDTRD_H 1

#include "Saxana/SAXObject.h"
#include "Schema/SolidType.h"

class twistedtrd : public SolidType {
public:
  twistedtrd() {
  }
  virtual ~twistedtrd() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const std::string& get_pPhiTwist() const {
    return m_pPhiTwist;
  }
  const std::string& get_pDz() const {
    return m_pDz;
  }
  const std::string& get_pDy1() const {
    return m_pDy1;
  }
  const std::string& get_pDx1() const {
    return m_pDx1;
  }
  const std::string& get_pDx2() const {
    return m_pDx2;
  }
  const std::string& get_pDy2() const {
    return m_pDy2;
  }
  
 void set_pPhiTwist( const std::string& pPhiTwist ) {
    m_pPhiTwist = pPhiTwist;
  }
  void set_pDz( const std::string& pDz ) {
    m_pDz = pDz;
  }
 void set_pDy1( const std::string& pDy1 ) {
    m_pDy1 = pDy1;
  }
 void set_pDx1( const std::string& pDx1 ) {
    m_pDx1 = pDx1;
  }
 void set_pDx2( const std::string& pDx2 ) {
    m_pDx2 = pDx2;
  }
 void set_pDy2( const std::string& pDy2 ) {
    m_pDy2 = pDy2;
  }

  
private:
  std::string m_pPhiTwist;
  std::string m_pDz;
  std::string m_pDy1;
  std::string m_pDx1;
  std::string m_pDx2;
  std::string m_pDy2;

};



#endif // TWISTEDTRD_H
