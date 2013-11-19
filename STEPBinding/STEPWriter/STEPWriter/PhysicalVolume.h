#ifndef STEP_WRITER_PHYSVOL_H
#define STEP_WRITER_PHYSVOL_H 1

#include <string>

class PhysicalVolume
{
 private:
  std::string logicalVolumeRef;
  std::string positionRef;
  std::string rotationRef;
  std::string scaleRef;
 public:
  PhysicalVolume(std::string setLogicalVolumeRef, std::string setPositionRef, std::string setRotationRef)
  {
   logicalVolumeRef = setLogicalVolumeRef;
   positionRef = setPositionRef;
   rotationRef = setRotationRef;
   scaleRef = "";                 // Set 'scaleRef' to empty string, so that no scaling is added***
  }
  std::string getLogicalVolumeRef()
  {
   return logicalVolumeRef;
  }
  std::string getPositionRef()
  {
   return positionRef;
  }
  std::string getRotationRef()
  {
   return rotationRef;
  }
  std::string getScaleRef()
  {
   return scaleRef;
  }
};

// *** I have not added scaleRef to the constructor in order to keep compatibility but I added it to the class
// to indicate that scaling is added to GDML 2.10.0

#endif // STEP_WRITER_PHYSVOL_H
