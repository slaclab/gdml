#ifndef STEP_WRITER_TESSSOLID_H
#define STEP_WRITER_TESSSOLID_H 1

#include <string>

#include "Writer/Facet.h"

class TessellatedSolid
{
 private:
  std::string name;
  std::vector<gdml::writer::Facet> facets;
 public:
  TessellatedSolid(std::string setName)
  {
   name = setName;
  }
  void addFacet(gdml::writer::Facet* newFacet)
  {
   facets.push_back(*newFacet);
  }
  const std::string& getName()
  {
   return name;
  }
  std::vector<gdml::writer::Facet>& getFacets()
  {
   return facets;
  }  
};

#endif // STEP_WRITER_TESSSOLID_H
