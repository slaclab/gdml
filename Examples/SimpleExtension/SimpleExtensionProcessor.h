#ifndef SIMPLEEXTENSIONPROCESSOR_H
#define SIMPLEEXTENSIONPROCESSOR_H 1

#include "G4VisAttributes.hh"

#include <string>
#include <map>

class SimpleExtensionProcessor
{
 public:
  static SimpleExtensionProcessor* instance();
  virtual ~SimpleExtensionProcessor();

 private:
  SimpleExtensionProcessor();

 public:
  typedef std::map<std::string,G4VisAttributes*> VisAttributes;

 public:

  void addVisAttributes(const std::string&, G4VisAttributes*);
  G4VisAttributes* getVisAttributes(const std::string& name);
  G4VisAttributes* getVisAttributes(const char* name);

 private:
  static SimpleExtensionProcessor* m_instance;
  SimpleExtensionProcessor::VisAttributes m_visAttributes;
  
};

#endif
