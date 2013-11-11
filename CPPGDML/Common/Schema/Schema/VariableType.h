//
#ifndef VARIABLETYPE_H
#define VARIABLETYPE_H 1

#include <string>

class VariableType {
  public:
    VariableType() {
    }
    VariableType( std::string& s ) : m_value( s ) {
    }
    VariableType( char* s ) {
      m_value = s;
    }
    ~VariableType() {
    }
    void set_value( std::string& s ) {
      m_value = s;
    } 
    std::string get_value() const {
      return m_value;
    }
  private:
    // double    
    std::string m_value;
};

#endif // VARIABLETYPE_H
