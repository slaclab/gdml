//
#ifndef IDENTIFIABLEVARIABLETYPE_H
#define IDENTIFIABLEVARIABLETYPE_H 1

#include "VariableType.h"

class IdentifiableVariableType : public VariableType
{
public:
  IdentifiableVariableType() {
  }
  IdentifiableVariableType( std::string& s ) : m_name( s ) {
  }
  IdentifiableVariableType( char* s ) {
    m_name = s;
  }
  ~IdentifiableVariableType() {
  }
  void set_name( std::string& s ) {
    m_name = s;
  }
  void set_name( char* s ) {
    m_name = s;
  }
  std::string get_name() const {
    return m_name;
  }
private:
  // ID required
  std::string m_name;    
};

#endif // IDENTIFIABLEVARIABLETYPE_H
