#ifndef STEP_WRITER_VERTEX_H
#define STEP_WRITER_VERTEX_H 1

#include <string>

class Vertex
{
 private:
  double x;
  double y;
  double z;
  std::string name;
 public:
  Vertex(const double setX, const double setY, const double setZ)
  {
   x = setX;
   y = setY;
   z = setZ;
   name = "temp";
  }
  void setName(const std::string& set)
  {
   name = set;
  }
  std::string getName()
  {
   return name;
  }
  double getX()
  {
   return x;
  }
  double getY()
  {
   return y;
  }
  double getZ()
  {
   return z;
  }
  /*
    Operators overloading. Feature needed by the find() algorithm in the
    processVertex() and processRotation() functions (methods of class STEPWriter).
  */  
  const bool operator==(const Vertex& other) const
  {
   if(x==other.x && y==other.y && z==other.z) return true;
   else return false;
  }
  const bool operator>(const Vertex& other) const
  {
   if(x>other.x) return true;
   else if(x==other.x && y>other.y) return true;
   else if(x==other.x && y==other.y && z>other.z) return true;
   else return false;
  }
  const bool operator<(const Vertex& other) const
  {
   if(x<other.x) return true;
   else if(x==other.x && y<other.y) return true;
   else if(x==other.x && y==other.y && z<other.z) return true;
   else return false;
  }
  const bool operator>=(const Vertex& other) const
  {
   if(x>other.x) return true;
   else if(x==other.x && y>other.y) return true;
   else if(x==other.x && y==other.y && z>other.z) return true;
   else if(x==other.x && y==other.y && z==other.z) return true;
   else return false;
  }
  const bool operator<=(const Vertex& other) const
  {
   if(x<other.x) return true;
   else if(x==other.x && y<other.y) return true;
   else if(x==other.x && y==other.y && z<other.z) return true;
   else if(x==other.x && y==other.y && z==other.z) return true;
   else return false;
  }
  const bool operator!=(const Vertex& other) const
  {
   if(x!=other.x || y!=other.y || z!=other.z) return true;
   else return false;
  }
};

#endif // STEP_WRITER_VERTEX_H
