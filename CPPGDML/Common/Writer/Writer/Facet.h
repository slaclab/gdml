#ifndef GDML_WRITER_FACET_H
#define GDML_WRITER_FACET_H 1

#include <string>

namespace gdml
{
 namespace writer
 {
  class Facet
  {
   private:
    enum ShapeType{triangular, quadrangular} shapeType;
    enum CoorType{absolute, relative} coorType;
    std::string vertex[4];
   
   public:
    /*
      triangular case
    */
    Facet(std::string vx1, std::string vx2, std::string vx3);
    /*
      quadrangular case
    */
    Facet(std::string vx1, std::string vx2, std::string vx3, std::string vx4);
    /*
      destructor
    */
    ~Facet();
    /*
      returns true if triangular, false otherwise
    */
    bool isTriangular();
    /*
      returns true if quadrangular, false otherwise
    */
    bool isQuadrangular();
    /*
      set the facet to have all absolute coordinates
    */
    void setAbsolute();
    /*
      set the facet to have all relative coordinates
      except the the coordinates of the first vertex
      which will be absolute.
    */  
    void setRelative();
    /*
      check to see if coordinates are absolute or relative,
      returns true in the former case and false in the latter
    */  
    bool isAbsolute();
    /*
      inline methods to get coordinates of vertices
    */
    std::string v1() {return vertex[0];}
    std::string v2() {return vertex[1];}
    std::string v3() {return vertex[2];}
    std::string v4() {return vertex[3];}
  };
 }
}

#endif // GDML_WRITER_FACET_H
