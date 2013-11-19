#include "Writer/Facet.h"
#include <string>

namespace gdml
{
 namespace writer
 {
  Facet::Facet(std::string vx1, std::string vx2, std::string vx3)
  {
   shapeType = triangular;
   coorType = absolute;
   vertex[0]=vx1;
   vertex[1]=vx2;
   vertex[2]=vx3;
  }
    
  Facet::Facet(std::string vx1, std::string vx2, std::string vx3, std::string vx4)
  {
   shapeType = quadrangular;
   coorType = absolute;
   vertex[0]=vx1;
   vertex[1]=vx2;
   vertex[2]=vx3;
   vertex[3]=vx4;
  }
  
  bool Facet::isTriangular()
  {
   if(shapeType==triangular) return true;
   else return false;
  }
  
  bool Facet::isQuadrangular()
  {
   if(shapeType==quadrangular) return true;
   else return false;
  }
  
  void Facet::setAbsolute()
  {
   coorType = absolute;
  }
  
  void Facet::setRelative()
  {
   coorType = relative;
  }
  
  bool Facet::isAbsolute()
  {
   if(coorType==absolute) return true;
   else return false;
  }
    
  Facet::~Facet()
  {
  }   
 }
}
