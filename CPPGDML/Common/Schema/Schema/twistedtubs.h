//
#ifndef TWISTEDTUBS_H
#define TWISTEDTUBS_H 1

#include "Saxana/SAXObject.h"

#include "Schema/SolidType.h"

class twistedtubs : public SolidType
{
public:
  twistedtubs() {
  }
  virtual ~twistedtubs() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const std::string& get_PhiTwist() const {
    return m_PhiTwist;
  }
  const std::string& get_InnerRadius() const {
    return m_InnerRadius;
  }
  const std::string& get_OuterRadius() const {
    return m_OuterRadius;
  }
  const std::string& get_ZHalfLength() const {
    return m_ZHalfLength;
  }
  const std::string& get_DPhi() const {
    return m_DPhi;
  }
  
  void set_PhiTwist( const std::string& PhiTwist ) {
    m_PhiTwist = PhiTwist;
  }
  void set_InnerRadius( const std::string& InnerRadius ) {
    m_InnerRadius = InnerRadius;
  }
  void set_ZHalfLength( const std::string& ZHalfLength ) {
    m_ZHalfLength = ZHalfLength;
  }
  void set_OuterRadius( const std::string& OuterRadius ) {
    m_OuterRadius = OuterRadius;
  }
  void set_DPhi( const std::string& DPhi ) {
    m_DPhi = DPhi;
  }
  
private:
  std::string m_PhiTwist;
  std::string m_InnerRadius;
  std::string m_OuterRadius;
  std::string m_ZHalfLength;
  std::string m_DPhi;
};


#endif // TWISTEDTUBS_H
