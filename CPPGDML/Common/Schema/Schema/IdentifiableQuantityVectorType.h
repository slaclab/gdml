//
#ifndef IDENTIFIABLEQUANTITYVECTORTYPE_H
#define IDENTIFIABLEQUANTITYVECTORTYPE_H 1


#include "QuantityVectorType.h"


class IdentifiableQuantityVectorType : public QuantityVectorType {
public:
  IdentifiableQuantityVectorType() {
  }
  ~IdentifiableQuantityVectorType() {
  }
  void set_name( const std::string& s ) {
    m_name = s;
  }
  void set_name( const char* s ) {
    m_name = s;
  }
  std::string get_name() const {
    return m_name;
  }
private:
  // ID required
  std::string m_name;    
};


#endif // IDENTIFIABLEQUANTITYVECTORTYPE_H
