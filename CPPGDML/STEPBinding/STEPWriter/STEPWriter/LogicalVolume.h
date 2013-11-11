#ifndef STEP_WRITER_LOGICVOL_H
#define STEP_WRITER_LOGICVOL_H 1

#include <string>

#include "STEPWriter/PhysicalVolume.h"

class LogicalVolume
{
 private:
  std::string name;
  std::string materialRef;
  std::string solidRef;
 public:
  LogicalVolume(std::string materialRefSet, std::string solidRefSet)
  {  
   materialRef = materialRefSet;
   solidRef = solidRefSet;
   name = solidRefSet;
  }
  std::string getName()
  {
   return name;
  }
  std::string getMaterialRef()
  {
   return materialRef;
  }
  std::string getSolidRef()
  {
   return solidRef;
  }
};

#endif // STEP_WRITER_LOGICVOL_H
