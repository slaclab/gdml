//
#ifndef TWISTEDTRAP_H
#define TWISTEDTRAP_H 1

#include "Saxana/SAXObject.h"
#include "Schema/SolidType.h"

class twistedtrap : public SolidType {
public:
  twistedtrap() {
  }
  virtual ~twistedtrap() {
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
  const std::string& get_pTheta() const {
    return m_pTheta;
  }
  const std::string& get_pPhi() const {
    return m_pPhi;
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
  const std::string& get_pDx3() const {
    return m_pDx3;
  }
  const std::string& get_pDx4() const {
    return m_pDx4;
  }
  const std::string& get_pAlph() const {
    return m_pAlph;
  }
  
 void set_pPhiTwist( const std::string& pPhiTwist ) {
    m_pPhiTwist = pPhiTwist;
  }
  void set_pDz( const std::string& pDz ) {
    m_pDz = pDz;
  }
 void set_pTheta( const std::string& pTheta ) {
    m_pTheta = pTheta;
  }
 void set_pPhi( const std::string& pPhi ) {
    m_pPhi = pPhi;
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
 void set_pDx3( const std::string& pDx3 ) {
    m_pDx3 = pDx3;
  }
  void set_pDx4( const std::string& pDx4 ) {
    m_pDx4 = pDx4;
  }
  void set_pAlph( const std::string& pAlph ) {
    m_pAlph = pAlph;
  }
  
private:
  std::string m_pPhiTwist;
  std::string m_pDz;
  std::string m_pTheta;
  std::string m_pPhi;
  std::string m_pDy1;
  std::string m_pDx1;
  std::string m_pDx2;
  std::string m_pDy2;
  std::string m_pDx3;
  std::string m_pDx4;
  std::string m_pAlph;
};



#endif // TWISTEDTRAP_H
