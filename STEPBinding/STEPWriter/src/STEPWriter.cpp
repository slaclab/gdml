#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "STEPWriter/STEPWriter.h"

/*
  @class STEPWriter STEPWriter.cpp
  

  @author Daniele Francesco KRUSE
  @date   2006-06-16
  
  Write me for any question regarding this code: k.master@fastwebnet.it
*/

/*
  STEPWriter()
  
  Constructor:
  Initialises to 0 all the variables used in the processVertex and in the processRotation methods (vertixCount and rotationCount)
  Initialises to 0 all the variables used in the calcWorldDim method (maxAbsVertexValue, maxAbsTraslValue and maxAbsPosValue)
*/
STEPWriter::STEPWriter()
{
 vertixCount=0; //counter used to generate vertices' names
 rotationCount=0; //counter used to generate rotations' names
 maxAbsVertexValue=0;
 maxAbsTraslValue=0;
 maxAbsPosValue=0;
}

/*
  ~STEPWriter()
  
  Destructor
*/
STEPWriter::~STEPWriter()
{
}

/*
  DumpSolids()
  
  Private function used to add tessellated solids to the solid cursor
  (only tessellated solids are contained in STEP files)
*/
void STEPWriter::DumpSolids()
{
 //std::cout << "[DUMPING SOLIDS] ..." << std::endl;
 double worldBoxDim = calcWorldDim();
 solcur->addBox("WorldBox", worldBoxDim, worldBoxDim, worldBoxDim, "mm"); //WorldBox always present
 for(unsigned int i=0; i<tessellatedSolids.size(); i++)
 {
  solcur->addTessellated(tessellatedSolids[i].getName(), tessellatedSolids[i].getFacets());                         
 }
 //std::cout << "[SOLIDS DUMPED]" << std::endl;
}

/*
  DumpMaterials()
  
  Private function used to add standard materials to the material cursor:
  1) Air for the World
  2) Alluminium for every other solid contained in the World
  
  This function may be expanded in the future when a materials' file is available for the corresponding geometry.
  Clearly every input file (also this virtual materials' file) must be parsed before the first dumping function is called.
  This function will then contain the necessary code to explore the materials' vector
  (which will be the result of the parsing of the materials' file) and to dump each material in the gdml file.
*/
void STEPWriter::DumpMaterials()
{
 //std::cout << "[DUMPING MATERIALS] ..." << std::endl;
 gdml::writer::FractionsVector* frvect = new gdml::writer::FractionsVector();

 matcur->addElement("Oxygen", "O", 8, 16.0);
 frvect->push_back(std::pair<std::string, double>("Oxygen",0.3));
 matcur->addElement("Nitrogen", "N", 7, 14.01);
 frvect->push_back(std::pair<std::string, double>("Nitrogen",0.7));	
 matcur->addMaterial("Air", "noFormula", 1.290, *frvect);
    
 matcur->addMaterial("Alluminium", "noFormula", 13, 26.98, 2.70);  
 //std::cout << "[MATERIALS DUMPED]" << std::endl;
}

/*
  DumpGeoTree()
  
  Private function used to create the geometry structure using the structure cursor.
  The number of logical volumes equals to the number of lines which start with a 'f' in the .geom file.
  The number of physical volumes equals to the number of lines which start with a 'g' in the .tree file.
  There should be some kind of level info in the tree file (should be the 1st number right after the 'g')
  however this value is not used here because it is not clear whether it is really that or something else.
  
  So the following assumptions are taken:
  1) The World contains everything
  2) There is only one level
  3) No logical volume, except the World itself, can contain physical volumes
*/
void STEPWriter::DumpGeoTree()
{
 //std::cout << "[DUMPING GEOMETRY TREE] ..." << std::endl;
 for(unsigned int i=0; i<logicalVolumes.size(); i++)
 {
  strcur->addVolume(logicalVolumes[i].getName(), logicalVolumes[i].getMaterialRef(), logicalVolumes[i].getSolidRef());
 }
  
 strcur->addVolume("World", "Air", "WorldBox");
 
 for(unsigned int i=0; i<physicalVolumes.size(); i++)
 {
  strcur->addChild("World", physicalVolumes[i].getLogicalVolumeRef(), physicalVolumes[i].getPositionRef(), physicalVolumes[i].getRotationRef(),physicalVolumes[i].getScaleRef());
 }
 //std::cout << "[GEOMETRY TREE DUMPED]" << std::endl;
}
		    
/*
  DumpDefinitions()
  
  Private function used to create all the definitions (positions, rotations and traslations) using the definition cursor.
*/  
void STEPWriter::DumpDefinitions()
{
 //std::cout << "[DUMPING DEFINITIONS] ..." << std::endl;
 for(unsigned int i=0; i<vertices.size(); i++)
 {
  defcur->addPosition(vertices[i].getName(), vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
 }
  
 for(unsigned int i=0; i<rotations.size(); i++)
 {
  defcur->addRotation(rotations[i].getName(), rotations[i].getX(), rotations[i].getY(), rotations[i].getZ(), "radian");
 }
 //std::cout << "[DEFINITIONS DUMPED]" << std::endl;
}

/*
  calcWorldDim()
  
  Private function used to calculate world dimensions.
*/
double STEPWriter::calcWorldDim()
{
 double worldDim;
 maxAbsPosValue=maxAbsVertexValue+maxAbsTraslValue;
 worldDim=2*(maxAbsPosValue+((maxAbsPosValue/100)*10));
 //std::cout << "maxAbsVertexValue= " << maxAbsVertexValue << " maxAbsTraslValue= " << maxAbsTraslValue << " maxAbsPosValue= " << maxAbsPosValue << " worldDim= " << worldDim << std::endl;
 return worldDim;
}

/* 
  processVertex(double x, double y, double z, bool dummy, bool secondStage, std::string prefix)
  
  In !dummy mode searches for the vertex (given by the xyz parameters) in the existing vertices vector,
  if this is found returns the string containing the name of the existing vertex, otherwise
  pushes the new vertex in the vertices vector and returns its new name.
  In dummy mode no search is done, the new vertex is pushed in the vertices vector and a string
  containing its new name is returned.
  
  @param x             X coordinate of vertex
  @param y             Y coordinate of vertex
  @param z             Z coordinate of vertex
  @param dummy         bool variable specifying the dummy mode (explained above)
  @param secondStage   bool variable specifying if we're computing vertices of facets (false) or traslated positions (true)
  @param prefix        prefix for names ("v" for vertices and "t" for traslations)      
*/
std::string STEPWriter::processVertex(double x, double y, double z, bool dummy, bool secondStage, std::string prefix)
{
 if(std::abs(x)>maxAbsVertexValue && !secondStage) maxAbsVertexValue=std::abs(x);
 if(std::abs(y)>maxAbsVertexValue && !secondStage) maxAbsVertexValue=std::abs(y);
 if(std::abs(z)>maxAbsVertexValue && !secondStage) maxAbsVertexValue=std::abs(z);
 if(std::abs(x)>maxAbsTraslValue && secondStage) maxAbsTraslValue=std::abs(x);
 if(std::abs(y)>maxAbsTraslValue && secondStage) maxAbsTraslValue=std::abs(y);
 if(std::abs(z)>maxAbsTraslValue && secondStage) maxAbsTraslValue=std::abs(z);
 if(!dummy)
 {
  std::string vertexName;
  Vertex temp(x,y,z);
  std::vector<Vertex>::iterator i = find(vertices.begin(),vertices.end(),temp);
  if(i!=vertices.end()) // Vertex found
  {
   return i->getName();
  }
  else // Vertex not found
  {
   std::stringstream ss;
   std::string str;
   ss << vertixCount;
   ss >> str;
   vertexName = prefix + str;
   temp.setName(vertexName);
   vertixCount++;
   vertices.push_back(temp);
   return vertexName;
  }
 }
 else
 {
  std::string vertexName;
  Vertex temp(x,y,z);
  std::stringstream ss;
  std::string str;
  ss << vertixCount;
  ss >> str;
  vertexName = prefix + str;
  temp.setName(vertexName);
  vertixCount++;
  vertices.push_back(temp);
  return vertexName;  
 }  
}

/* 
  processRotation(double x, double y, double z, bool dummy)
  
  Similar to processVertex()
  In !dummy mode searches for the rotation (given by the xyz parameters) in the existing rotations vector,
  if this is found returns the string containing the name of the existing rotation, otherwise
  pushes the new rotation in the rotations vector and returns its new name.
  In dummy mode no search is done, the new rotation is pushed in the rotations vector and a string
  containing its new name is returned.
  
  @param x             value of rotation in the X axis
  @param y             value of rotation in the Y axis
  @param z             value of rotation in the Z axis
  @param dummy         bool variable specifying the dummy mode (explained above)      
*/
std::string STEPWriter::processRotation(double x, double y, double z, bool dummy)
{
 if(!dummy)
 {
  std::string vertexName;
  Vertex temp(x,y,z);
  std::vector<Vertex>::iterator i = find(rotations.begin(),rotations.end(),temp);
  if(i!=rotations.end()) // Vertex found
  {
   return i->getName();
  }
  else // Vertex not found
  {
   std::stringstream ss;
   std::string str;
   ss << rotationCount;
   ss >> str;
   vertexName = "r" + str;
   temp.setName(vertexName);
   rotationCount++;
   rotations.push_back(temp);
   return vertexName;
  }
 }
 else
 {
  std::string vertexName;
  Vertex temp(x,y,z);
  std::stringstream ss;
  std::string str;
  ss << rotationCount;
  ss >> str;
  vertexName = "r" + str;
  temp.setName(vertexName);
  rotationCount++;
  rotations.push_back(temp);
  return vertexName;  
 }  
}

/*
  getXYZ(const G4RotationMatrix* r, double& x, double& y, double& z) const
  
  Takes a rotation matrix as input and converts it to the corresponding rotations values in the X, Y and Z axis.
  
  @param r             (input) rotation matrix
  @param x             (output) reference to the variable that will contain the value of rotation in the X axis
  @param y             (output) reference to the variable that will contain the value of rotation in the Y axis
  @param z             (output) reference to the variable that will contain the value of rotation in the Z axis
*/
void STEPWriter::getXYZ(const G4RotationMatrix* r, double& x, double& y, double& z) const
{
 double cosb = sqrt(r->xx()*r->xx() + r->yx()*r->yx());
 if (cosb > 16*FLT_EPSILON)
 {
  x = atan2(r->zy(), r->zz());
  y = atan2(-r->zx(), cosb);
  z = atan2(r->yx(), r->xx());
 }
 else
 {
  x = atan2(-r->yz(), r->yy());
  y = atan2(-r->zx(), cosb);
  z = 0.;
 }
}

/*
  dump(const char* gdmlFilePath, const char* gdmlSchemaPath)
  
  Public function used to dump all the data in the gdml file. First of all initialises the document writer
  setting the output file and the GDML Schema location then calls the private functions DumpDefinitions(),
  DumpMaterials(), DumpSolids() and DumpGeoTree() to do the job.
  
  @param gdmlFilePath    path to the output file
  @param gdmlSchemaPath  path to the GDML Schema file ("gdml.xsd")
*/
void STEPWriter::dump(const char* gdmlFilePath, const char* gdmlSchemaPath)
{
 std::string outputFile(gdmlFilePath);
 schemaLocation = gdmlSchemaPath;
 std::cout << "[WRITING GDML FILE] ..." << std::endl;
 gdml::writer::DocumentBuilder db(outputFile);
 db.OpenDocument();
 db.setSchemaLocation(schemaLocation);

 matcur = &db.getMaterialsCursor();
 solcur = &db.getSolidsCursor();
 defcur = &db.getDefinitionsCursor();
 strcur = &db.getStructureCursor();
 stpcur = &db.getSetupCursor();

 DumpDefinitions();
 DumpMaterials();
 DumpSolids();
 DumpGeoTree();

 stpcur->addSetup("Default", "1.0", "World");

 db.WriteDocument();
 db.CloseDocument();
 std::cout << "[GDML FILE COMPLETED]" << std::endl << std::endl;
 //std::cout << "OK, it works!" << std::endl << std::endl;
}

/*
  parse(const char* geomFilePath, const char* treeFilePath, const bool dummy)
  
  Main parsing function, used to parse both the .geom and .tree file. There are certain features
  of these files that remain unclear:
  1) In the .geom file the lines starting with "p" (defining a facet) are always followed by a "3"
     this has been interpreted here as a TRIANGULAR facet definition, assuming that if the "3" was a
     "4" then it would have been a QUADRANGULAR facet definition. This of course may not be the case,
     so whoever finds out shall change the third "else if" condition (tessType == '4').
  2) In the .geom file the lines starting with "g" (defining surfaces and their properties)
     are discarded. When someone finds out more about them, then maybe some code should be added.
  3) In the .tree file the lines starting with "n" are discarded as they indicate a level with no
     associated geometry.
  4) In the .tree file the lines starting with g indicate everything we need (or almost):
     a) level of assembly (discarded because of the lack of info regarding mother volume)
     b) reference to the logical volume contained in the .geom file
     c) copy number of the physical volume, discarded because not used in GDML
        (if there's only one physical volume for each logical volume then this number is always 1)
     d) elements of the 3 x 3 rotation matrix (rotation of the physical volume)
     e) x, y and z coordinates of the physical volume's traslation
     f) other values (indicated with n1, n2, n3, n4, and n5 in the code) which their meaning is
        completely obscure, therefore they are discarded by default.
  5) There's no info about materials so alluminium and air are used as explained above
  
  So the levels and copy numbers are discarded but they are stored in the variables "level" and "copy_no",
  so that, if one really wants, they can be used as desired.
  
  @param geomFilePath   path to the .geom input file
  @param treeFilePath   path to the .tree input file
  @param dummy          bool variable used to set the dummy mode explained above (in the processVertex() function)
*/
void STEPWriter::parse(const char* geomFilePath, const char* treeFilePath, const bool dummy)
{
 
 std::ifstream geomFileIn(geomFilePath);
 if(!geomFileIn)
 {
  std::cout << "ERROR: could not open " << geomFilePath << std::endl;
  exit(1);
 }
 std::ifstream treeFileIn(treeFilePath);
 if(!treeFileIn)
 {
  std::cout << "ERROR: could not open " << treeFilePath << std::endl;
  exit(1);
 } 
  
 std::string line;
 char lineType; 
 bool isFirstSolid = true;
 std::string vertex1Name, vertex2Name, vertex3Name, vertex4Name;
 std::string tessellatedSolidName; 
 double x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4; 
 TessellatedSolid *tempTessSolid = NULL;
 LogicalVolume *tempLogVolume = NULL;
 std::cout << std::endl << "[PROCESSING GEOM FILE] ..." << std::endl;
 while(getline(geomFileIn,line))
 {
  lineType = line[0];
  if(lineType == 'f'&& isFirstSolid)
  {
   isFirstSolid = false;
   std::istringstream lineStream(line.substr(2));
   lineStream >> tessellatedSolidName;
   tempTessSolid = new TessellatedSolid(tessellatedSolidName);
   //std::cout << "Processing Tessellated Solid: " << tessellatedSolidName << std::endl;
  }
  else if(lineType == 'f'&& !isFirstSolid)
  {
   tessellatedSolids.push_back(*tempTessSolid);
   tempLogVolume = new LogicalVolume("Alluminium", tempTessSolid->getName());
   logicalVolumes.push_back(*tempLogVolume);
   //std::cout << "Finished Tessellated Solid: " << tempTessSolid->getName() << std::endl;
   std::istringstream lineStream(line.substr(2));
   lineStream >> tessellatedSolidName;
   tempTessSolid = new TessellatedSolid(tessellatedSolidName);
   //std::cout << "Processing Tessellated Solid: " << tessellatedSolidName << std::endl;
  }
  else if(lineType == 'p')
  {
   char tessType = line[2];
   if(tessType == '3') // triangular facet
   {
    std::istringstream lineStream(line.substr(4));
    lineStream >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
    vertex1Name = processVertex(x1,y1,z1,dummy, false, "v");
    vertex2Name = processVertex(x2,y2,z2,dummy, false, "v");
    vertex3Name = processVertex(x3,y3,z3,dummy, false, "v");
    gdml::writer::Facet *newFacet = new gdml::writer::Facet(vertex1Name, vertex2Name, vertex3Name);
    tempTessSolid->addFacet(newFacet);
   }
   else if(tessType == '4') // quadrangular facet
   {
    std::istringstream lineStream(line.substr(4));
    lineStream >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> x4 >> y4 >> z4;
    vertex1Name = processVertex(x1,y1,z1,dummy, false, "v");
    vertex2Name = processVertex(x2,y2,z2,dummy, false, "v");
    vertex3Name = processVertex(x3,y3,z3,dummy, false, "v");
    vertex4Name = processVertex(x4,y4,z4,dummy, false, "v");
    gdml::writer::Facet *newFacet = new gdml::writer::Facet(vertex1Name, vertex2Name, vertex3Name, vertex4Name);
    tempTessSolid->addFacet(newFacet);
   }
  }
 }
 tessellatedSolids.push_back(*tempTessSolid);
 tempLogVolume = new LogicalVolume("Alluminium", tempTessSolid->getName());
 logicalVolumes.push_back(*tempLogVolume);
 //std::cout << "Finished Tessellated Solid: " << tempTessSolid->getName() << std::endl;
 std::cout << "[GEOM FILE PROCESSING COMPLETE]" << std::endl << std::endl;
 
 unsigned int level; //level really?? what is the mother of the objects?
 unsigned int copy_no; //is it really copy number??
 std::string tessellatedSolidName_withCopyNo;
 std::string tessellatedSolidName_withoutCopyNo;
 double r1,r2,r3,n1,r4,r5,r6,n2,r7,r8,r9,n3,pX,pY,pZ,n4,n5; //r* denotes rotation info, p* denotes position info, n* denotes unknown info
 double rotX, rotY, rotZ;
 std::string traslName;
 std::string rotName;
 PhysicalVolume *tempPhVolume = NULL;
 std::cout << "[PROCESSING TREE FILE] ..." << std::endl;
 while(getline(treeFileIn,line))
 {
  lineType = line[0];
  if(lineType == 'g')
  {
   std::istringstream lineStream(line.substr(2));
   lineStream >> level >> tessellatedSolidName_withCopyNo >> r1 >> r2 >> r3 >> n1 >> r4 >> r5 >> r6 >> n2 >> r7 >> r8 >> r9 >> n3 >> pX >> pY >> pZ >> n4 >> n5;
   //TODO: What to do with these funny objects?? :)
   int copy_index = tessellatedSolidName_withCopyNo.rfind("_");
   std::istringstream copyStream(tessellatedSolidName_withCopyNo.substr(++copy_index));
   copyStream >> copy_no;
   tessellatedSolidName_withoutCopyNo = tessellatedSolidName_withCopyNo.substr(0, --copy_index);
   std::string logicalVolumeReference = getLogicalVolumeReference(tessellatedSolidName_withoutCopyNo);
   G4RotationMatrix rm(G4ThreeVector(r1,r2,r3),G4ThreeVector(r4,r5,r6),G4ThreeVector(r7,r8,r9));
   getXYZ(&rm, rotX, rotY, rotZ);
   //std::cout << "X: " << rotX << "Y: " << rotY << "Z: " << rotZ << std::endl;
   traslName = processVertex(pX,pY,pZ,dummy, true, "t");
   rotName = processRotation(rotX, rotY, rotZ, dummy);
   tempPhVolume = new PhysicalVolume(logicalVolumeReference, traslName, rotName);
   physicalVolumes.push_back(*tempPhVolume);
   //std::cout << rotName << " : " << rotX << " , " << rotY << " , " << rotZ << std::endl;
  }
 }
 std::cout << "[TREE FILE PROCESSING COMPLETE]" << std::endl << std::endl;
 return;
}

/*
  getLogicalVolumeReference(const std::string tessellatedSolidName)
  
  Private function used while parsing the tree file to get the logical volume reference corresponding
  to the tessellated solid name taken as argument.
  
  @param tessellatedSolidName   tessellated solid name for which we need to find the corresponding
                                logical volume reference
*/
std::string STEPWriter::getLogicalVolumeReference(const std::string tessellatedSolidName)
{
 for(unsigned int i=0; i<logicalVolumes.size(); i++)
 {
  if(logicalVolumes[i].getSolidRef()==tessellatedSolidName) return logicalVolumes[i].getName();
 }
 return "UnknownLogicalVolumeReference";
}
