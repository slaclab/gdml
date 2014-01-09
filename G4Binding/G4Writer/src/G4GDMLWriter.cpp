// $Id: G4GDMLWriter.cpp,v 1.2 2012/02/01 12:10:54 jeremy Exp $
// Include files
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <stdexcept>

// Geant4
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4VPVParameterisation.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4VSolid.hh"
#include "G4SolidStore.hh"
#include "G4PVDivision.hh"
#include "G4PVParameterised.hh"

#include "G4Cons.hh"
#include "G4Box.hh"

#ifdef HAVE_G4TWISTEDBOX
#include "G4TwistedBox.hh"
#endif

#ifdef HAVE_G4TWISTEDTRAP
#include "G4TwistedTrap.hh"
#endif

#ifdef HAVE_G4TWISTEDTRD
#include "G4TwistedTrd.hh"
#endif

#include "G4Sphere.hh"
#include "G4Tubs.hh"

#ifdef HAVE_G4TWISTEDTUBS
#include "G4TwistedTubs.hh"
#endif

#include "G4Polycone.hh"
#include "G4Para.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"

#ifdef HAVE_G4TET
#include "G4Tet.hh"
#endif

#include "G4Hype.hh"
#include "G4Torus.hh"
#include "G4Orb.hh"
#include "G4Polyhedra.hh"
#include "G4EllipticalTube.hh"

#ifdef HAVE_G4TESSELLATEDSOLID
#include "G4TessellatedSolid.hh"
#endif

#include "G4ReflectedSolid.hh"

#include "G4BooleanSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4DisplacedSolid.hh"

#ifdef HAVE_G4EXTRUDEDSOLID
#include "G4ExtrudedSolid.hh"
#endif

// local
#include "G4Writer/G4GDMLWriter.h"

// common
#include "Writer/Facet.h"

//-----------------------------------------------------------------------------
// Implementation file for class : G4GDMLWriter
//
// 2004-06-23 : Witold POKORSKI
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
G4GDMLWriter::G4GDMLWriter(int format)
  : schemaLocation("gdml.xsd"),
    outputFile("g4geo.gdml")
{
  currentFormat = format;
  ut = new Utils(format);
  vertixCount=0;
}
G4GDMLWriter::G4GDMLWriter(std::string schema,
                           std::string output,
			   int format)
  : schemaLocation(schema),
    outputFile(output)
{
  currentFormat = format;
  ut = new Utils(format);
  vertixCount=0;
}
//=============================================================================
// Destructor
//=============================================================================
G4GDMLWriter::~G4GDMLWriter()
{
}
//============================================================================
void G4GDMLWriter::DumpMaterials()
{
  int howmany=0;

  // writing out materials
  const G4MaterialTable* mattable = G4Material::GetMaterialTable();
  int matsize = mattable->size();
  std::cout << "Dumping " << matsize << " materials"<< std::endl;

  for( G4MaterialTable::const_iterator it=mattable->begin();
       it!=mattable->end();
       it++ )
  {
    DumpMaterial(*it);
    howmany++;    
    if(!(howmany%100)) std::cout << howmany << "/" << matsize << " materials done" << std::endl;
  }
}

#ifdef HAVE_G4TESSELLATEDSOLID
std::string G4GDMLWriter::processTessSolidVertex(double x, double y, double z) // with searching
{ 
 std::string vertexName;
 Vertex temp(x,y,z);
 std::vector<Vertex>::iterator i = find(tessellatedSolidsVertices.begin(),tessellatedSolidsVertices.end(),temp);
 if(i!=tessellatedSolidsVertices.end()) // Vertex found
 {
  return i->getName();
 }
 else // Vertex not found
 {
  std::stringstream ss;
  std::string str;
  ss << vertixCount;
  ss >> str;
  vertexName = "v" + str;
  temp.setName(vertexName);
  vertixCount++;
  tessellatedSolidsVertices.push_back(temp);
  return vertexName;
 }  
}
#endif

std::string G4GDMLWriter::processTetVertex(double x, double y, double z) // without searching
{ 
 std::string vertexName;
 Vertex temp(x,y,z);
 std::stringstream ss;
 std::string str;
 ss << vertixCount;
 ss >> str;
 vertexName = "v" + str;
 temp.setName(vertexName);
 vertixCount++;
 tetrahedronSolidsVertices.push_back(temp);
 return vertexName; 
}

void G4GDMLWriter::DumpSolids()
{
  // writing out solids
  G4SolidStore* solidstr = G4SolidStore::GetInstance();
  int howmany = 0;
  int solsize = solidstr->size();

  std::cout << "Dumping " << solsize << " solids"<< std::endl;

  for(G4SolidStore::const_iterator sit = solidstr->begin();
      sit!=solidstr->end();
      sit++)
  {
    howmany++;
    if(!(howmany%100)) std::cout << howmany << "/" << solsize << " solids done" << std::endl;
    G4VSolid* tempsol = *sit;    
    DumpSolid(tempsol);    
  }
}

void G4GDMLWriter::getXYZ( const G4RotationMatrix* r, double& a, double& b, double& c) const
{
  double cosb = sqrt( r->xx()*r->xx() + r->yx()*r->yx() );

  if (cosb > 16*FLT_EPSILON)
  {
    a = atan2(  r->zy(), r->zz() );
    b = atan2( -r->zx(), cosb    );
    c = atan2(  r->yx(), r->xx() );
  }
  else
  {
    a = atan2( -r->yz(), r->yy() );
    b = atan2( -r->zx(), cosb    );
    c = 0.;
  }
}

void G4GDMLWriter::DumpGeoTree(G4VPhysicalVolume* physvol)
{
  std::stack<G4VPhysicalVolume*> volstack;

  G4LogicalVolume* logvol = physvol->GetLogicalVolume();
  int nbofdaughters = logvol->GetNoDaughters();

  for (int licz = 0; licz < nbofdaughters; licz++)
  {
    G4VPhysicalVolume* pv = logvol->GetDaughter(licz);
    G4LogicalVolume* dlv = pv->GetLogicalVolume();

    std::vector<G4LogicalVolume*>::const_reverse_iterator itlv = lvlist.rbegin();
    std::vector<G4LogicalVolume*>::const_reverse_iterator enditlv = lvlist.rend();

    while(itlv!=enditlv && (*itlv)!=dlv) itlv++;
 
    if(itlv==enditlv)
    {
      lvlist.push_back(dlv);
      DumpGeoTree(pv);
    }
    volstack.push( pv );
  }

  std::string lvname = ut->name(logvol);

  G4VSolid* ts = logvol->GetSolid();

  if (dynamic_cast<const G4DisplacedSolid*>(ts)) 
     G4Exception("GDML Writer", "", FatalException, "Displaced solid should not be used in a logical volume!");

  strcur->addVolume(lvname,ut->name(logvol->GetMaterial()),ut->name(ts));

  while( !volstack.empty() )
  {
    G4VPhysicalVolume* pv = volstack.top();
    
    if(pv->IsParameterised())
    {
      if(dynamic_cast<G4PVParameterised*>(pv))
      {
        gdml::writer::Element& param =
          strcur->addParameterised(lvname,// mother volume
                                   ut->name(pv->GetLogicalVolume()),// parametrised volume
                                   pv->GetMultiplicity());// number of copies
      
        G4VSolid* solid = logvol->GetSolid();
      
        for(int cpiter=1;cpiter!=pv->GetMultiplicity()+1;cpiter++)
        {
        
          pv->GetParameterisation()->ComputeTransformation(cpiter-1,pv);
        
          const G4RotationMatrix* r = pv->GetFrameRotation();
        
          double rx=0.0, ry=0.0, rz=0.0; // axis rotation angles
          if(r) getXYZ( r, rx, ry, rz );
        
          if( G4Box* box = dynamic_cast<G4Box*>(solid) )
          {
            pv->GetParameterisation()->ComputeDimensions(*box,cpiter-1,pv);
          
            strcur->addBoxParameterisation(ut->name(pv->GetLogicalVolume()),
                                           param,  // volume
                                           cpiter,                            // copy number
                                           pv->GetObjectTranslation().getX(), // position
                                           pv->GetObjectTranslation().getY(),
                                           pv->GetObjectTranslation().getZ(),
                                           rx, ry, rz, // rotation
                                           box->GetXHalfLength(),
                                           box->GetYHalfLength(),
                                           box->GetZHalfLength()); // half-lengths
          }
          else if( G4Tubs* tubs = dynamic_cast<G4Tubs*>(solid) )
          {
            pv->GetParameterisation()->ComputeDimensions(*tubs,cpiter-1,pv);
          
            strcur->addTubeParameterisation(ut->name(pv->GetLogicalVolume()),
                                            param,// volume
                                            cpiter,// copy number
                                            pv->GetObjectTranslation().getX(),// position
                                            pv->GetObjectTranslation().getY(),
                                            pv->GetObjectTranslation().getZ(),
                                            rx, ry, rz,// rotation
                                            tubs->GetInnerRadius(),
                                            tubs->GetOuterRadius(),
                                            2*tubs->GetZHalfLength(),
                                            tubs->GetStartPhiAngle()/deg,
                                            tubs->GetDeltaPhiAngle()/deg);
          }
          else
          {
            std::cout << "Trying to parameterise unknown solid - it will not work!"
                      << std::endl;
          }
        }
      }
      else if(dynamic_cast<G4PVDivision*>(pv))
      {
      EAxis ax;
      int nDiv;
      double width;
      double offset;
      bool cons;

      pv->GetReplicationData(ax, nDiv, width, offset, cons);

      int axi=0;
      
      if(ax==kXAxis)
      {
        axi=1;
      }
      else if(ax==kYAxis)
      {
        axi=2;
      }
      else if(ax==kZAxis)
      {
        axi=3;
      }
      else if(ax==kRho)
      {
        axi=4;
      }
      else if(ax==kPhi)
      {
        axi=5;
      }

      std::string unit("mm");

      // converting into degrees      
      if(axi==4 || axi==5)
      {
        width = width/deg;
        offset = offset/deg;
        unit = "degree";
      }      
      strcur->addDivision(lvname,// mother volume
                          ut->name(pv->GetLogicalVolume()),// divided volume
                          nDiv, axi, width, offset, unit);
      }
    }
    else if(pv->IsReplicated())
    {
      EAxis ax;
      int nrep;
      double width;
      double offset;
      bool cons;

      pv->GetReplicationData(ax, nrep, width, offset, cons);

      int axi=0;
      
      if(ax==kXAxis)
      {
        axi=1;
      }
      else if(ax==kYAxis)
      {
        axi=2;
      }
      else if(ax==kZAxis)
      {
        axi=3;
      }

      strcur->addReplica(lvname,// mother volume
                         ut->name(pv->GetLogicalVolume()),// replicated volume
                         nrep, axi, width, offset);
    }
    else { // Normal volume
    
      std::string pvname = ut->name(pv);
      G4VSolid* tsol = pv->GetLogicalVolume()->GetSolid();

      if (dynamic_cast<const G4DisplacedSolid*>(tsol))
         G4Exception("GDML Writer", "", FatalException, "Displaced solid should not be used in a logical volume!");
      
      G4ThreeVector pos = pv->GetObjectTranslation();
      double dx = pos.getX();
      double dy = pos.getY();
      double dz = pos.getZ();

      G4RotationMatrix rotation = pv->GetObjectRotationValue().inverse();
      double rx,ry,rz;
      getXYZ(&rotation,rx,ry,rz);

      std::string posname("");
      std::string rotname("");
      std::string sclname("");

      if (dx != 0.0 || dy != 0.0 || dz != 0.0) {
      
         posname = pvname+"in"+lvname+"p";
         defcur->addPosition(posname,dx/mm,dy/mm,dz/mm,"mm");
      }

      if (rx != 0.0 || ry != 0.0 || rz != 0.0) {
      
         rotname = pvname+"in"+lvname+"r";
         defcur->addRotation(rotname,rx/deg,ry/deg,rz/deg,"degree");
      }

      strcur->addChild(lvname,ut->name(pv->GetLogicalVolume()),posname,rotname,sclname);
    }
    volstack.pop();
  }
}

#ifdef HAVE_G4TESSELLATEDSOLID
void G4GDMLWriter::DumpTessellatedSolidsDefinitions()
{
 for(unsigned int i=0; i<tessellatedSolidsVertices.size(); i++)
 {
  defcur->addPosition(tessellatedSolidsVertices[i].getName(), tessellatedSolidsVertices[i].getX(), tessellatedSolidsVertices[i].getY(), tessellatedSolidsVertices[i].getZ());
 }
}
#endif

void G4GDMLWriter::DumpTetrahedronSolidsDefinitions()
{
 for(unsigned int i=0; i<tetrahedronSolidsVertices.size(); i++)
 {
  defcur->addPosition(tetrahedronSolidsVertices[i].getName(), tetrahedronSolidsVertices[i].getX(), tetrahedronSolidsVertices[i].getY(), tetrahedronSolidsVertices[i].getZ());
 }
}

void G4GDMLWriter::DumpGeometryInfo(G4VPhysicalVolume* worldPV)
{
  std::cout << "Dumping geometry description into GDML file."
            << std::endl;

  gdml::writer::DocumentBuilder db(outputFile);
  db.OpenDocument();
  db.setSchemaLocation( schemaLocation );

  matcur = &db.getMaterialsCursor();
  solcur = &db.getSolidsCursor();
  defcur = &db.getDefinitionsCursor();
  strcur = &db.getStructureCursor();
  stpcur = &db.getSetupCursor();

  DumpMaterials();
  DumpSolids();
#ifdef HAVE_G4TESSELLATEDSOLID
  DumpTessellatedSolidsDefinitions();
#endif
  DumpTetrahedronSolidsDefinitions();

  // Traverse the geometry hierarchy and write it down to the file
  //std::cout << "Examining the logical tree" << std::endl;
  DumpGeoTree(worldPV);

  // Finalize with the setup pointing to the world volume
  stpcur->addSetup( "Default",                                // Setup ID
                    "1.0",                                    // Setup version
                    ut->name(worldPV->GetLogicalVolume()) ); // World vol. ref.

  db.WriteDocument();
  db.CloseDocument();
  std::cout << "Written out GDML file: " << outputFile << std::endl;
}

void G4GDMLWriter::DumpGeometryInfo(G4VPhysicalVolume* worldPV, std::vector<int> levels, int currentLevel)
{
  gdml::writer::DocumentBuilder db(outputFile);
  db.OpenDocument();
  db.setSchemaLocation( schemaLocation );

  matcur = &db.getMaterialsCursor();
  solcur = &db.getSolidsCursor();
  strcur = &db.getStructureCursor();
  defcur = &db.getDefinitionsCursor();
  stpcur = &db.getSetupCursor();  

  // Traverse the geometry hierarchy and write it down to the file
  //std::cout << "Examining the logical tree" << std::endl;
  DumpGeoTree2(worldPV, levels, currentLevel);
#ifdef HAVE_G4TESSELLATEDSOLID
  DumpTessellatedSolidsDefinitions();
#endif
  DumpTetrahedronSolidsDefinitions();

  // Finalize with the setup pointing to the world volume
  stpcur->addSetup( "Default",                                // Setup ID
                    "1.0",                                    // Setup version
                    ut->name(worldPV->GetLogicalVolume()) );  // World vol. ref.

  db.WriteDocument();
  db.CloseDocument();
  std::cout << "Written out GDML file: " << outputFile << std::endl;  
}

void G4GDMLWriter::DumpMaterial(G4Material* mat)
{ 
    int nbofele = mat->GetNumberOfElements();

    if(nbofele > 1)
    {
      gdml::writer::FractionsVector*
        frvect = new gdml::writer::FractionsVector();

      for(int ii=0; ii!=nbofele; ii++)
	    {
	      const G4Element*
          ele = mat->GetElement(ii);

	      matcur->addElement(ut->name(ele),
                           ele->GetSymbol(),
                           (int)ele->GetZ(),
                           ele->GetA()*mole/g);
	      frvect->push_back(std::pair<std::string, double>
                          (ut->name(mat->GetElement(ii)),
                           mat->GetFractionVector()[ii]));
	    }
      matcur->addMaterial(ut->name(mat),
                          mat->GetChemicalFormula(),
                          mat->GetDensity()*cm3/g,
                          *frvect);
    } 
    else
    {
      matcur->addMaterial(ut->name(mat),
                          mat->GetChemicalFormula(),
                          mat->GetZ(),
                          mat->GetA()*mole/g,
                          mat->GetDensity()*cm3/g);
    }
}

void G4GDMLWriter::DumpSolid(const G4VSolid* tempsol)
{
    while(const G4DisplacedSolid* disp = dynamic_cast<const G4DisplacedSolid*>(tempsol))
    {
      tempsol = disp->GetConstituentMovedSolid();
    }

    if( const G4Box* box = dynamic_cast<const G4Box*>(tempsol) )
    {
      solcur->addBox( ut->name(box),
                      2*box->GetXHalfLength()/mm,
                      2*box->GetYHalfLength()/mm,
                      2*box->GetZHalfLength()/mm,"mm" );
    }    
#ifdef HAVE_G4EXTRUDEDSOLID
    else if (const G4ExtrudedSolid *xtru = dynamic_cast<const G4ExtrudedSolid*>(tempsol)) 
    {
        G4int numVertex = xtru->GetNofVertices();
	G4int numSection = xtru->GetNofZSections();

        double *vertex_ptr = new double[numVertex*2];
        double *section_ptr = new double[numSection*4];

        for (int i=0;i<numVertex;i++) {
	
	    G4TwoVector V = xtru->GetVertex(i);

           vertex_ptr[2*i+0] = V.x()/mm;
	   vertex_ptr[2*i+1] = V.y()/mm;
	}

        for (int i=0;i<numSection;i++) {
	
	    G4ExtrudedSolid::ZSection zsect = xtru->GetZSection(i);
	
            section_ptr[4*i+0] = zsect.fZ/mm;
            section_ptr[4*i+1] = zsect.fOffset.x()/mm;
            section_ptr[4*i+2] = zsect.fOffset.y()/mm;
            section_ptr[4*i+3] = zsect.fScale;			// Scaling factor is without dimension!!!
	}

        solcur->addXtru(ut->name(xtru),"mm",numVertex,vertex_ptr,numSection,section_ptr);

        if (section_ptr!=NULL) delete [] section_ptr;
	if (vertex_ptr!=NULL) delete [] vertex_ptr;
    }
#endif
#ifdef HAVE_G4TESSELLATEDSOLID
    else if( const G4TessellatedSolid* tessSolid = dynamic_cast<const G4TessellatedSolid*>(tempsol) )
    {
      int numberOfFacets = tessSolid->GetNumberOfFacets();
      //std::cout << "numberOfFacets: " << numberOfFacets << std::endl;
      std::vector<gdml::writer::Facet> facets;
      for(int i=0; i<numberOfFacets; i++)
      {
        G4VFacet *tempG4Facet = tessSolid->GetFacet(i);
        int numberOfVertices = tempG4Facet->GetNumberOfVertices();
        //std::cout << "numberOfVertices: " << numberOfVertices << std::endl;
        std::vector<std::string> verticesNames;
        for(int j=0; j<numberOfVertices; j++)
        {
          G4ThreeVector currentVertex = tempG4Facet->GetVertex(j);
          //std::cout << "X: " << currentVertex.x()  << " Y: " << currentVertex.y()  << " Z: " << currentVertex.z() << std::endl;
          verticesNames.push_back(processTessSolidVertex(currentVertex.x(),currentVertex.y(), currentVertex.z()));
        }       
        if(verticesNames.size()==3) //triangular facet
        {
          gdml::writer::Facet newFacet(verticesNames[0], verticesNames[1], verticesNames[2]);
          facets.push_back(newFacet);
        }
        else if(verticesNames.size()==4) //quadrangular facet
        {
          gdml::writer::Facet newFacet(verticesNames[0], verticesNames[1], verticesNames[2], verticesNames[3]);
          facets.push_back(newFacet);
        }
      }
      solcur->addTessellated( ut->name(tessSolid),
                              facets,
                              "mm","degree");
    }    
#endif
#ifdef HAVE_G4TET
    else if( const G4Tet* tet = dynamic_cast<const G4Tet*>(tempsol) )
    {
      std::vector<G4ThreeVector> tetVertices = tet->GetVertices();
      std::string vertex1 = processTetVertex(tetVertices[0].x(),tetVertices[0].y(),tetVertices[0].z());
      std::string vertex2 = processTetVertex(tetVertices[1].x(),tetVertices[1].y(),tetVertices[1].z());
      std::string vertex3 = processTetVertex(tetVertices[2].x(),tetVertices[2].y(),tetVertices[2].z());
      std::string vertex4 = processTetVertex(tetVertices[3].x(),tetVertices[3].y(),tetVertices[3].z());
      
      solcur->addTetrahedron( ut->name(tet),
                              vertex1,
                              vertex2,
                              vertex3,
                              vertex4,
                              "mm","degree");
    }
#endif
    else if( const G4Sphere* sphere = dynamic_cast<const G4Sphere*>(tempsol) )
    {
      solcur->addSphere( ut->name(sphere),
                         sphere->GetInsideRadius()/mm,
                         sphere->GetOuterRadius()/mm,
                         sphere->GetStartPhiAngle()/deg,
                         sphere->GetDeltaPhiAngle()/deg,
                         sphere->GetStartThetaAngle()/deg,
                         sphere->GetDeltaThetaAngle()/deg,
                         "mm","degree");
    }
#ifdef HAVE_G4TWISTEDTRAP
      else if( const G4TwistedTrap* twistedtrap = dynamic_cast<const G4TwistedTrap*>(tempsol) )
    {
      solcur->addTwistedTrap( ut->name(twistedtrap),
		      2*twistedtrap->GetY1HalfLength()/mm,
                      2*twistedtrap->GetX1HalfLength()/mm,
		      2*twistedtrap->GetX2HalfLength()/mm,
                      2*twistedtrap->GetY2HalfLength()/mm,
		      2*twistedtrap->GetX3HalfLength()/mm,
		      2*twistedtrap->GetX4HalfLength()/mm,
                      2*twistedtrap->GetZHalfLength()/mm,
		      twistedtrap->GetPhiTwist()/deg, 
		      twistedtrap->GetTiltAngleAlpha()/deg,
		      twistedtrap->GetPolarAngleTheta()/deg,
		      twistedtrap->GetAzimuthalAnglePhi()/deg, "mm", "degree");
    }
#endif
#ifdef HAVE_G4TWISTEDTRD
    else if( const G4TwistedTrd* twistedtrd = dynamic_cast<const G4TwistedTrd*>(tempsol) )
    {
      solcur->addTwistedTrd( ut->name(twistedtrd),
	
		      2*twistedtrd->GetX1HalfLength()/mm,
                      2*twistedtrd->GetX2HalfLength()/mm,
		      2*twistedtrd->GetY1HalfLength()/mm,
                      2*twistedtrd->GetY2HalfLength()/mm,
                      2*twistedtrd->GetZHalfLength()/mm,
		      twistedtrd->GetPhiTwist()/deg,"mm", "rad");
    }
#endif
#ifdef HAVE_G4TWISTEDBOX
    else if( const G4TwistedBox* twistedbox = dynamic_cast<const G4TwistedBox*>(tempsol) )
    {
      solcur->addTwistedBox( ut->name(twistedbox),
                      2*twistedbox->GetXHalfLength()/mm,
                      2*twistedbox->GetYHalfLength()/mm,
                      2*twistedbox->GetZHalfLength()/mm,
		      twistedbox->GetPhiTwist()/deg, "mm", "degree");
    }
#endif

    else if( const G4Tubs* tubs = dynamic_cast<const G4Tubs*>(tempsol) )
    {
      solcur->addTube(ut->name(tubs),
                      tubs->GetInnerRadius()/mm,
                      tubs->GetOuterRadius()/mm,
                      2*tubs->GetZHalfLength()/mm,
                      tubs->GetStartPhiAngle()/deg,
                      tubs->GetDeltaPhiAngle()/deg
                      ,"mm","degree");
    }
#ifdef HAVE_G4TWISTEDTUBS
       else if( const G4TwistedTubs* twistedtubs = dynamic_cast<const G4TwistedTubs*>(tempsol) )
    {
      solcur->addTwistedTubs(ut->name(twistedtubs),
			     twistedtubs->GetPhiTwist()/deg,
                      twistedtubs->GetInnerRadius()/mm,
                      twistedtubs->GetOuterRadius()/mm,
                      2*twistedtubs->GetZHalfLength()/mm,
                      twistedtubs->GetDPhi()/deg,"mm","degree");
    }
#endif
    else if( const G4Cons* cons = dynamic_cast<const G4Cons*>(tempsol) )
    {
      solcur->addCone(ut->name(cons),
                      cons->GetInnerRadiusMinusZ()/mm,
                      cons->GetOuterRadiusMinusZ()/mm,
                      cons->GetInnerRadiusPlusZ()/mm,
                      cons->GetOuterRadiusPlusZ()/mm,
                      2*cons->GetZHalfLength()/mm,
                      cons->GetStartPhiAngle()/deg,
                      cons->GetDeltaPhiAngle()/deg,
                      "mm","degree");
    }
    else if( const G4Polycone* polycone = dynamic_cast<const G4Polycone*>(tempsol) )
    {
      solcur->addPolyCone(ut->name(polycone),
                          polycone->GetOriginalParameters()->Num_z_planes,
                          polycone->GetOriginalParameters()->Start_angle/deg,
                          polycone->GetOriginalParameters()->Opening_angle/deg,
                          polycone->GetOriginalParameters()->Z_values,
                          polycone->GetOriginalParameters()->Rmin,
                          polycone->GetOriginalParameters()->Rmax,
                          "mm","degree");
    }
    else if( const G4Para* para = dynamic_cast<const G4Para*>(tempsol) )
    {
      double phi;
      if(para->GetSymAxis().z()!=1.0)
        phi = atan(para->GetSymAxis().y()/para->GetSymAxis().x());
      else
        phi = 0;

      solcur->addPara(ut->name(para),
                      2*para->GetXHalfLength()/mm,
                      2*para->GetYHalfLength()/mm,
                      2*para->GetZHalfLength()/mm,
                      atan(para->GetTanAlpha())/deg,
                      acos(para->GetSymAxis().z())/deg,
                      phi/deg,"mm","degree");
    }
    else if( const G4Trap* trap = dynamic_cast<const G4Trap*>(tempsol) )
    {
      double phi;
      if(trap->GetSymAxis().z()!=1.0)
        phi = atan(trap->GetSymAxis().y()/trap->GetSymAxis().x());
      else
        phi = 0;

      solcur->addTrap(ut->name(trap),
                      2*trap->GetXHalfLength1()/mm,
                      2*trap->GetXHalfLength2()/mm,
                      2*trap->GetYHalfLength1()/mm,
                      atan(trap->GetTanAlpha1())/deg,
                      2*trap->GetXHalfLength3()/mm,
                      2*trap->GetXHalfLength4()/mm,
                      2*trap->GetYHalfLength2()/mm,
                      atan(trap->GetTanAlpha2())/deg,
                      acos(trap->GetSymAxis().z())/deg,
                      2*trap->GetZHalfLength()/mm,
                      phi/deg,"mm","degree");


    }
    else if( const G4Trd* trd = dynamic_cast<const G4Trd*>(tempsol) )
    {
      solcur->addTrd(ut->name(trd),
                     2*trd->GetXHalfLength1()/mm,
                     2*trd->GetXHalfLength2()/mm,
                     2*trd->GetYHalfLength1()/mm,
                     2*trd->GetYHalfLength2()/mm,
                     2*trd->GetZHalfLength()/mm,"mm");
    }
    else if( const G4Orb* orb = dynamic_cast<const G4Orb*>(tempsol) )
    {
      solcur->addOrb(ut->name(orb),
                     orb->GetRadius()/mm,
                     "mm");
    }
    else if( const G4Hype* hype = dynamic_cast<const G4Hype*>(tempsol) )
    {
      solcur->addHype(ut->name(hype),
                      hype->GetInnerRadius()/mm,
                      hype->GetOuterRadius()/mm,
                      hype->GetInnerStereo()/deg,
                      hype->GetOuterStereo()/deg,
                      2*hype->GetZHalfLength()/mm,"mm","degree");
    }
    else if( const G4EllipticalTube* eltu = dynamic_cast<const G4EllipticalTube*>(tempsol) )
    {
      solcur->addElTube(ut->name(eltu),
                        eltu->GetDx()/mm,
                        eltu->GetDy()/mm,
                        eltu->GetDz()/mm,"mm");
    }
    else if( const G4Torus* torus = dynamic_cast<const G4Torus*>(tempsol) )
    {
      solcur->addTorus(ut->name(torus),
                       torus->GetRmin()/mm,
                       torus->GetRmax()/mm,
                       torus->GetRtor()/mm,
                       torus->GetSPhi()/degree,
                       torus->GetDPhi()/degree,"mm","degree");
    }
    else if( const G4Polyhedra* polyh = dynamic_cast<const G4Polyhedra*>(tempsol) )
    {
      
      std::vector<double> rIn;
      std::vector<double> rOut;
      rIn.resize(polyh->GetOriginalParameters()->Num_z_planes);
      rOut.resize(polyh->GetOriginalParameters()->Num_z_planes);

      double convertRad = std::cos(0.5*polyh->GetOriginalParameters()->Opening_angle/
                                   polyh->GetOriginalParameters()->numSide);

      for (int i=0;i<polyh->GetOriginalParameters()->Num_z_planes;i++)
      {
        rIn[i] = (polyh->GetOriginalParameters()->Rmin)[i] * convertRad;
        rOut[i] = (polyh->GetOriginalParameters()->Rmax)[i] * convertRad;          
      }
      
      solcur->addPolyhedra(ut->name(polyh),
                           polyh->GetOriginalParameters()->Num_z_planes,
                           polyh->GetOriginalParameters()->Start_angle/deg,
                           polyh->GetOriginalParameters()->Opening_angle/deg,
                           polyh->GetOriginalParameters()->numSide,
                           polyh->GetOriginalParameters()->Z_values,
                           rIn,
                           rOut,
                           "mm",
                           "degree");
    }
    else if(const G4ReflectedSolid* refl = dynamic_cast<const G4ReflectedSolid*>(tempsol) )
    {
      double rx, ry, rz;
      G4Scale3D  scale;
      G4Rotate3D rotation;
      G4Translate3D  translation;

      refl->GetTransform3D().getDecomposition(scale, rotation, translation);
      G4RotationMatrix rrr = rotation.getRotation();

      getXYZ( &rrr, rx, ry, rz );
      
      solcur->addReflected(ut->name(refl),
                           ut->name(refl->GetConstituentMovedSolid()),
                           scale.xx(), scale.yy(), scale.zz(),
                           rx/deg, ry/deg, rz/deg,
                           translation.dx()/mm, translation.dy()/mm, translation.dz()/mm,
                           "mm","degree");      
    }
    else if( const G4BooleanSolid* boo = dynamic_cast<const G4BooleanSolid*>(tempsol) )
    {
      std::string btype("unknown");
      if(boo->GetEntityType()=="G4SubtractionSolid") btype = "subtraction";
      else if(boo->GetEntityType()=="G4UnionSolid") btype = "union";
      else if(boo->GetEntityType()=="G4IntersectionSolid") btype = "intersection";

      G4VSolid* constit0 = const_cast <G4VSolid*> (boo->GetConstituentSolid(0));
      DumpSolid(constit0);
      G4VSolid* constit1 = const_cast <G4VSolid*> (boo->GetConstituentSolid(1));
      DumpSolid(constit1);

      double dx0=0;
      double dy0=0;
      double dz0=0;
      double drx0=0;
      double dry0=0;
      double drz0=0;

      double dx1=0;
      double dy1=0;
      double dz1=0;
      double drx1=0;
      double dry1=0;
      double drz1=0;

      while(const G4DisplacedSolid* disp =
            dynamic_cast<const G4DisplacedSolid*>(constit0))
	    {
	      dx0 += disp->GetObjectTranslation().x()/mm;
	      dy0 += disp->GetObjectTranslation().y()/mm;
	      dz0 += disp->GetObjectTranslation().z()/mm;

	      const G4RotationMatrix r = disp->GetObjectRotation();
	      double tdrx=0; double tdry=0; double tdrz=0;
	      getXYZ( &r, tdrx, tdry, tdrz );
	      drx0+=tdrx; dry0+=tdry; drz0+=tdrz;

	      constit0 = disp->GetConstituentMovedSolid();
	    }

      while(const G4DisplacedSolid* disp =
            dynamic_cast<const G4DisplacedSolid*>(constit1))
	    {
	      dx1 += disp->GetObjectTranslation().x()/mm;
	      dy1 += disp->GetObjectTranslation().y()/mm;
	      dz1 += disp->GetObjectTranslation().z()/mm;

	      const G4RotationMatrix r = disp->GetObjectRotation();
	      double tdrx=0; double tdry=0; double tdrz=0;
	      getXYZ( &r, tdrx, tdry, tdrz );
	      drx1+=tdrx; dry1+=tdry; drz1+=tdrz;

	      constit1 = disp->GetConstituentMovedSolid();
	    }

      solcur->addBoolean(ut->name(boo),
                         btype,
                         ut->name(constit0),
                         ut->name(constit1),
                         dx1/mm, dy1/mm, dz1/mm,
                         drx1/deg, dry1/deg, drz1/deg,
                         dx0/mm, dy0/mm, dz0/mm,
                         drx0/deg, dry0/deg, drz0/deg);
    }
    else
    {
      // (tempsol)->DumpInfo();

      std::cout << "Unknown solid: " << (tempsol)->GetName() << std::endl;
      std::cout << "The corresponding volume will have a null reference to solid!!" << std::endl;
    }  
}


void G4GDMLWriter::DumpGeoTree2(G4VPhysicalVolume* physvol, std::vector<int> levels, int currentLevel)
{
  currentLevel++;
  bool modularize = false;
  std::vector<int>::iterator i = find(levels.begin(),levels.end(),currentLevel);
  if(i!=levels.end()) // found
  {
   modularize = true;
  }
  
  std::stack<G4VPhysicalVolume*> volstack;

  G4LogicalVolume* logvol = physvol->GetLogicalVolume();
  DumpSolid(logvol->GetSolid());
  DumpMaterial(logvol->GetMaterial());
  int nbofdaughters = logvol->GetNoDaughters();

  for (int licz = 0; licz < nbofdaughters; licz++)
  {
    G4VPhysicalVolume* pv = logvol->GetDaughter(licz);
    G4LogicalVolume* dlv = pv->GetLogicalVolume();

    std::vector<G4LogicalVolume*>::const_reverse_iterator itlv = lvlist.rbegin();
    std::vector<G4LogicalVolume*>::const_reverse_iterator enditlv = lvlist.rend();

    while(itlv!=enditlv && (*itlv)!=dlv) itlv++;
 
    if(itlv==enditlv)
    {
      lvlist.push_back(dlv);
      if(!modularize)
      {
       DumpGeoTree2(pv, levels, currentLevel);
      }
      else
      {
       G4GDMLWriter g4writer(schemaLocation, (ut->name(pv->GetLogicalVolume()))+".gdml", currentFormat);
       try
       {
        g4writer.DumpGeometryInfo(pv, levels, currentLevel);
       }
       catch(std::logic_error &lerr)
       {
        std::cout << "Caught an exception: " << lerr.what () << std::endl;
       }
      }
    }
    volstack.push( pv );
  }

  std::string lvname = ut->name(logvol);

  G4VSolid* ts = logvol->GetSolid();

  if (dynamic_cast<const G4DisplacedSolid*>(ts)) 
     G4Exception("GDML Writer", "", FatalException, "Displaced solid should not be used in a logical volume!");

  strcur->addVolume(lvname,ut->name(logvol->GetMaterial()),ut->name(ts));

  while( !volstack.empty() )
  {
    G4VPhysicalVolume* pv = volstack.top();
    
    if(pv->IsParameterised())
    {
      if(dynamic_cast<G4PVParameterised*>(pv))
      {
        gdml::writer::Element& param =
          strcur->addParameterised(lvname,// mother volume
                                   ut->name(pv->GetLogicalVolume()),// parametrised volume
                                   pv->GetMultiplicity());// number of copies
      
        G4VSolid* solid = logvol->GetSolid();
      
        for(int cpiter=1;cpiter!=pv->GetMultiplicity()+1;cpiter++)
        {
        
          pv->GetParameterisation()->ComputeTransformation(cpiter-1,pv);
        
          const G4RotationMatrix* r = pv->GetFrameRotation();
        
          double rx=0.0, ry=0.0, rz=0.0; // axis rotation angles
          if(r) getXYZ( r, rx, ry, rz );
        
          if( G4Box* box = dynamic_cast<G4Box*>(solid) )
          {
            pv->GetParameterisation()->ComputeDimensions(*box,cpiter-1,pv);
          
            strcur->addBoxParameterisation(ut->name(pv->GetLogicalVolume()),
                                           param,  // volume
                                           cpiter,                            // copy number
                                           pv->GetObjectTranslation().getX(), // position
                                           pv->GetObjectTranslation().getY(),
                                           pv->GetObjectTranslation().getZ(),
                                           rx, ry, rz, // rotation
                                           box->GetXHalfLength(),
                                           box->GetYHalfLength(),
                                           box->GetZHalfLength()); // half-lengths
          }
          else if( G4Tubs* tubs = dynamic_cast<G4Tubs*>(solid) )
          {
            pv->GetParameterisation()->ComputeDimensions(*tubs,cpiter-1,pv);
          
            strcur->addTubeParameterisation(ut->name(pv->GetLogicalVolume()),
                                            param,// volume
                                            cpiter,// copy number
                                            pv->GetObjectTranslation().getX(),// position
                                            pv->GetObjectTranslation().getY(),
                                            pv->GetObjectTranslation().getZ(),
                                            rx, ry, rz,// rotation
                                            tubs->GetInnerRadius(),
                                            tubs->GetOuterRadius(),
                                            2*tubs->GetZHalfLength(),
                                            tubs->GetStartPhiAngle()/deg,
                                            tubs->GetDeltaPhiAngle()/deg);
          }
          else
          {
            std::cout << "Trying to parameterise unknown solid - it will not work!"
                      << std::endl;
          }
        }
      }
      else if(dynamic_cast<G4PVDivision*>(pv))
      {
      EAxis ax;
      int nDiv;
      double width;
      double offset;
      bool cons;

      pv->GetReplicationData(ax, nDiv, width, offset, cons);

      int axi=0;
      
      if(ax==kXAxis)
      {
        axi=1;
      }
      else if(ax==kYAxis)
      {
        axi=2;
      }
      else if(ax==kZAxis)
      {
        axi=3;
      }
      else if(ax==kRho)
      {
        axi=4;
      }
      else if(ax==kPhi)
      {
        axi=5;
      }

      std::string unit("mm");

      // converting into degrees      
      if(axi==4 || axi==5)
      {
        width = width/deg;
        offset = offset/deg;
        unit = "degree";
      }      
      strcur->addDivision(lvname,// mother volume
                          ut->name(pv->GetLogicalVolume()),// divided volume
                          nDiv, axi, width, offset, unit);
      }
    }
    else if(pv->IsReplicated())
    {
      EAxis ax;
      int nrep;
      double width;
      double offset;
      bool cons;

      pv->GetReplicationData(ax, nrep, width, offset, cons);

      int axi=0;
      
      if(ax==kXAxis)
      {
        axi=1;
      }
      else if(ax==kYAxis)
      {
        axi=2;
      }
      else if(ax==kZAxis)
      {
        axi=3;
      }

      strcur->addReplica(lvname,// mother volume
                         ut->name(pv->GetLogicalVolume()),// replicated volume
                         nrep, axi, width, offset);
    }
    else //normal volume
    {
      std::string pvname = ut->name(pv);
      G4VSolid* tsol = pv->GetLogicalVolume()->GetSolid();

      if (dynamic_cast<const G4DisplacedSolid*>(tsol)) 
         G4Exception("GDML Writer", "", FatalException, "Displaced solid should not be used in a logical volume!");

      G4ThreeVector pos = pv->GetObjectTranslation();
      double dx = pos.getX();
      double dy = pos.getY();
      double dz = pos.getZ();

      G4RotationMatrix rotation = pv->GetObjectRotationValue().inverse();
      double rx,ry,rz;
      getXYZ(&rotation,rx,ry,rz);

      std::string posname("");
      std::string rotname("");
      std::string sclname("");

      if (dx != 0.0 || dy != 0.0 || dz != 0.0) {
      
         posname = pvname+"in"+lvname+"p";
         defcur->addPosition(posname,dx/mm,dy/mm,dz/mm,"mm");
      }

      if (rx != 0.0 || ry != 0.0 || rz != 0.0) {
      
         rotname = pvname+"in"+lvname+"r";
         defcur->addRotation(rotname,rx/deg,ry/deg,rz/deg,"degree");
      }

      if(!modularize) {
       
          strcur->addChild(lvname,ut->name(pv->GetLogicalVolume()),posname,rotname,sclname);
      }
      else {
       
          std::string filename = (ut->name(pv->GetLogicalVolume()))+".gdml";
          strcur->addChildFile(lvname,filename,posname,rotname,sclname);
      }      
    }
    volstack.pop();
  }
}

void G4GDMLWriter::DumpGeometryInfo(G4VPhysicalVolume* worldPV, std::vector<std::string> volnames)
{
  gdml::writer::DocumentBuilder db(outputFile);
  db.OpenDocument();
  db.setSchemaLocation( schemaLocation );

  matcur = &db.getMaterialsCursor();
  solcur = &db.getSolidsCursor();
  strcur = &db.getStructureCursor();
  defcur = &db.getDefinitionsCursor();
  stpcur = &db.getSetupCursor();  

  // Traverse the geometry hierarchy and write it down to the file
  //std::cout << "Examining the logical tree" << std::endl;
  DumpGeoTree2(worldPV, volnames);
#ifdef HAVE_G4TESSELLATEDSOLID
  DumpTessellatedSolidsDefinitions();
#endif
  DumpTetrahedronSolidsDefinitions();

  // Finalize with the setup pointing to the world volume
  stpcur->addSetup( "Default",                                // Setup ID
                    "1.0",                                    // Setup version
                    ut->name(worldPV->GetLogicalVolume()) );  // World vol. ref.

  db.WriteDocument();
  db.CloseDocument();
  std::cout << "Written out GDML file: " << outputFile << std::endl; 
}

void G4GDMLWriter::DumpGeoTree2(G4VPhysicalVolume* physvol, std::vector<std::string> volnames)
{
  bool modularize = false;  
  std::stack<G4VPhysicalVolume*> volstack;

  G4LogicalVolume* logvol = physvol->GetLogicalVolume();
  DumpSolid(logvol->GetSolid());
  DumpMaterial(logvol->GetMaterial());
  int nbofdaughters = logvol->GetNoDaughters();

  for (int licz = 0; licz < nbofdaughters; licz++)
  {
    G4VPhysicalVolume* pv = logvol->GetDaughter(licz);
    G4LogicalVolume* dlv = pv->GetLogicalVolume();
    std::string name_of_logical_vol = pv->GetLogicalVolume()->GetName();
    std::vector<std::string>::iterator i = find(volnames.begin(),volnames.end(),name_of_logical_vol);
    if(i!=volnames.end()) // found
    {
     modularize = true;
    }
    else
    {
     modularize = false;
    }

    std::vector<G4LogicalVolume*>::const_reverse_iterator itlv = lvlist.rbegin();
    std::vector<G4LogicalVolume*>::const_reverse_iterator enditlv = lvlist.rend();

    while(itlv!=enditlv && (*itlv)!=dlv) itlv++;
 
    if(itlv==enditlv)
    {
      lvlist.push_back(dlv);
      if(!modularize)
      {
       DumpGeoTree2(pv, volnames);
      }
      else
      {
       G4GDMLWriter g4writer(schemaLocation, (ut->name(pv->GetLogicalVolume()))+".gdml", currentFormat);
       try
       {
        g4writer.DumpGeometryInfo(pv, volnames);
       }
       catch(std::logic_error &lerr)
       {
        std::cout << "Caught an exception: " << lerr.what () << std::endl;
       }
      }
    }
    volstack.push( pv );
  }

  std::string lvname = ut->name(logvol);

  G4VSolid* ts = logvol->GetSolid();

  if (dynamic_cast<const G4DisplacedSolid*>(ts)) 
     G4Exception("GDML Writer", "", FatalException, "Displaced solid should not be used in a logical volume!");

  strcur->addVolume(lvname,ut->name(logvol->GetMaterial()),ut->name(ts));

  while( !volstack.empty() )
  {
    G4VPhysicalVolume* pv = volstack.top();
    std::string name_of_logical_vol = pv->GetLogicalVolume()->GetName();
    std::vector<std::string>::iterator i = find(volnames.begin(),volnames.end(),name_of_logical_vol);
    if(i!=volnames.end()) // found
    {
     modularize = true;
    }
    else
    {
     modularize = false;
    }
    
    if(pv->IsParameterised())
    {
      if(dynamic_cast<G4PVParameterised*>(pv))
      {
        gdml::writer::Element& param =
          strcur->addParameterised(lvname,// mother volume
                                   ut->name(pv->GetLogicalVolume()),// parametrised volume
                                   pv->GetMultiplicity());// number of copies
      
        G4VSolid* solid = logvol->GetSolid();
      
        for(int cpiter=1;cpiter!=pv->GetMultiplicity()+1;cpiter++)
        {
        
          pv->GetParameterisation()->ComputeTransformation(cpiter-1,pv);
        
          const G4RotationMatrix* r = pv->GetFrameRotation();
        
          double rx=0.0, ry=0.0, rz=0.0; // axis rotation angles
          if(r) getXYZ( r, rx, ry, rz );
        
          if( G4Box* box = dynamic_cast<G4Box*>(solid) )
          {
            pv->GetParameterisation()->ComputeDimensions(*box,cpiter-1,pv);
          
            strcur->addBoxParameterisation(ut->name(pv->GetLogicalVolume()),
                                           param,  // volume
                                           cpiter,                            // copy number
                                           pv->GetObjectTranslation().getX(), // position
                                           pv->GetObjectTranslation().getY(),
                                           pv->GetObjectTranslation().getZ(),
                                           rx, ry, rz, // rotation
                                           box->GetXHalfLength(),
                                           box->GetYHalfLength(),
                                           box->GetZHalfLength()); // half-lengths
          }
          else if( G4Tubs* tubs = dynamic_cast<G4Tubs*>(solid) )
          {
            pv->GetParameterisation()->ComputeDimensions(*tubs,cpiter-1,pv);
          
            strcur->addTubeParameterisation(ut->name(pv->GetLogicalVolume()),
                                            param,// volume
                                            cpiter,// copy number
                                            pv->GetObjectTranslation().getX(),// position
                                            pv->GetObjectTranslation().getY(),
                                            pv->GetObjectTranslation().getZ(),
                                            rx, ry, rz,// rotation
                                            tubs->GetInnerRadius(),
                                            tubs->GetOuterRadius(),
                                            2*tubs->GetZHalfLength(),
                                            tubs->GetStartPhiAngle()/deg,
                                            tubs->GetDeltaPhiAngle()/deg);
          }
          else
          {
            std::cout << "Trying to parameterise unknown solid - it will not work!"
                      << std::endl;
          }
        }
      }
      else if(dynamic_cast<G4PVDivision*>(pv))
      {
      EAxis ax;
      int nDiv;
      double width;
      double offset;
      bool cons;

      pv->GetReplicationData(ax, nDiv, width, offset, cons);

      int axi=0;
      
      if(ax==kXAxis)
      {
        axi=1;
      }
      else if(ax==kYAxis)
      {
        axi=2;
      }
      else if(ax==kZAxis)
      {
        axi=3;
      }
      else if(ax==kRho)
      {
        axi=4;
      }
      else if(ax==kPhi)
      {
        axi=5;
      }

      std::string unit("mm");

      // converting into degrees      
      if(axi==4 || axi==5)
      {
        width = width/deg;
        offset = offset/deg;
        unit = "degree";
      }      
      strcur->addDivision(lvname,// mother volume
                          ut->name(pv->GetLogicalVolume()),// divided volume
                          nDiv, axi, width, offset, unit);
      }
    }
    else if(pv->IsReplicated())
    {
      EAxis ax;
      int nrep;
      double width;
      double offset;
      bool cons;

      pv->GetReplicationData(ax, nrep, width, offset, cons);

      int axi=0;
      
      if(ax==kXAxis)
      {
        axi=1;
      }
      else if(ax==kYAxis)
      {
        axi=2;
      }
      else if(ax==kZAxis)
      {
        axi=3;
      }

      strcur->addReplica(lvname,// mother volume
                         ut->name(pv->GetLogicalVolume()),// replicated volume
                         nrep, axi, width, offset);
    }
    else //normal volume
    {
      std::string pvname = ut->name(pv);
      G4VSolid* tsol = pv->GetLogicalVolume()->GetSolid();

      if (dynamic_cast<const G4DisplacedSolid*>(tsol)) 
         G4Exception("GDML Writer", "", FatalException, "Displaced solid should not be used in a logical volume!");

      G4ThreeVector pos = pv->GetObjectTranslation();
      double dx = pos.getX();
      double dy = pos.getY();
      double dz = pos.getZ();

      G4RotationMatrix rotation = pv->GetObjectRotationValue().inverse();
      double rx,ry,rz;
      getXYZ(&rotation,rx,ry,rz);

      std::string posname("");
      std::string rotname("");
      std::string sclname("");

      if (dx != 0.0 || dy != 0.0 || dz != 0.0) {
      
         posname = pvname+"in"+lvname+"p";
         defcur->addPosition(posname,dx/mm,dy/mm,dz/mm,"mm");
      }

      if (rx != 0.0 || ry != 0.0 || rz != 0.0) {
      
         rotname = pvname+"in"+lvname+"r";
         defcur->addRotation(rotname,rx/deg,ry/deg,rz/deg,"degree");
      }

      if(!modularize) {
       
          strcur->addChild(lvname,ut->name(pv->GetLogicalVolume()),posname,rotname,sclname);
      }
      else {
       
          std::string filename = (ut->name(pv->GetLogicalVolume()))+".gdml";
          strcur->addChildFile(lvname,filename,posname,rotname,sclname);
      }      
    }
    volstack.pop();
  }
}
