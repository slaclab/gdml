#include "SimpleExtensionProcessor.h"

SimpleExtensionProcessor* SimpleExtensionProcessor::m_instance=0;

SimpleExtensionProcessor::SimpleExtensionProcessor()
{}

SimpleExtensionProcessor::~SimpleExtensionProcessor()
{}

SimpleExtensionProcessor* SimpleExtensionProcessor::instance()
{
  if ( m_instance == 0 ) {
    m_instance = new SimpleExtensionProcessor;
  }
  return m_instance;
}

void SimpleExtensionProcessor::addVisAttributes(const std::string& name, G4VisAttributes*vis)
{
  m_visAttributes[name]=vis;
}


G4VisAttributes* SimpleExtensionProcessor::getVisAttributes(const std::string& name)
{
  return m_visAttributes[name];
}

G4VisAttributes* SimpleExtensionProcessor::getVisAttributes(const char* name)
{
  return getVisAttributes(std::string(name));
}
