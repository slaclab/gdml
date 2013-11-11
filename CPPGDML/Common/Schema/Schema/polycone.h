#ifndef POLYCONE_H
#define POLYCONE_H 1

#include "ContentGroup.h"
#include "Saxana/SAXObject.h"
#include "Schema/SolidType.h"

class polycone : public SolidType {
public:
  polycone() {
  }
  virtual ~polycone() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const std::string& get_startphi() const {
    return m_startphi;
  }
  const std::string& get_deltaphi() const {
    return m_deltaphi;
  }
  
  void set_startphi( const std::string& startphi ) {
    m_startphi = startphi;
  }
  void set_deltaphi( const std::string& deltaphi ) {
    m_deltaphi = deltaphi;
  }
  
  const ContentSequence* get_content() const {
    return &m_sequence;
  }
  
  void add_content( const std::string& tag, SAXObject* so ) {
    ContentGroup::ContentItem ci = { tag, so };
    m_sequence.add_content( ci );
  }  
  
private:
  std::string m_startphi;
  std::string m_deltaphi;
  
  ContentSequence m_sequence;
};


#endif // POLYCONE_H
