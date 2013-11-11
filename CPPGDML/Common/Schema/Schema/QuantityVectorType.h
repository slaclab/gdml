//
#ifndef QUANTITYVECTORTYPE_H
#define QUANTITYVECTORTYPE_H 1


#include "ThreeVectorType.h"


class QuantityVectorType : public ThreeVectorType {
public:
  QuantityVectorType() {
  }
  ~QuantityVectorType() {
  }
  void set_unit( const std::string& s ) {
    m_unit = s;
  }
  void set_unit( const char* s ) {
    m_unit = s;
  }
  std::string get_unit() const {
    return m_unit;
  }
  void set_type( const std::string& s ) {
    m_type = s;
  }
  void set_type( const char* s ) {
    m_type = s;
  }
  std::string get_type() const {
    return m_type;
  }
private:
  // string
  std::string m_unit;
  // string
  std::string m_type;
};


#endif // QUANTITYVECTORTYPE_H
