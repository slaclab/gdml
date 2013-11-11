//
#ifndef AUXILIARY_H
#define AUXILIARY_H 1

#include "Saxana/SAXObject.h"
#include "Schema/SolidType.h"

class auxiliary : public SolidType {
public:
  auxiliary() {
  }
  virtual ~auxiliary() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
  
  const std::string& get_auxtype() const {
    return m_auxtype;
  }
  const std::string& get_auxval() const {
    return m_auxval;
  }
  
  void set_auxtype( const std::string& auxtype ) {
    m_auxtype = auxtype;
  }
  void set_auxval( const std::string& auxval ) {
    m_auxval = auxval;
  }
  
private:
  std::string m_auxtype;
  std::string m_auxval;

};



#endif // AUXILIARY_H
