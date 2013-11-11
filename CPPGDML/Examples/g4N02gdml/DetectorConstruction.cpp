// 
#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVDivision.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4ReflectedSolid.hh"
#include "G4UserLimits.hh"

//#include "G4TessellatedSolid.hh"
#include "G4QuadrangularFacet.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

 
DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{
}

 
G4VPhysicalVolume* DetectorConstruction::Construct()
{
//--------- Material definition ---------

  G4double a, z;
  G4double density;
  G4int nel;

  //Air
  G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);
   
  G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
  Air->AddElement(N, 70*perCent);
  Air->AddElement(O, 30*perCent);

  G4VSolid*  solidWorld= new G4Box("world",5000,5000,5000);
  G4LogicalVolume* logicWorld= new G4LogicalVolume( solidWorld, Air, "World", 0, 0, 0);
  G4VPhysicalVolume* physiWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);              
  
  G4VSolid* solidDet = new G4Box("det",1000,1000,1000);

  /*
  G4ThreeVector* v1 = new G4ThreeVector(10,10,0);
  G4ThreeVector* v2 = new G4ThreeVector(-10,10,0);
  G4ThreeVector* v3 = new G4ThreeVector(-10,-10,0);
  G4ThreeVector* v4 = new G4ThreeVector(10,-10,0);
  G4ThreeVector* v5 = new G4ThreeVector(0,0,20);

  G4TessellatedSolid* solidDet = new G4TessellatedSolid("det");
  solidDet->AddFacet(new G4TriangularFacet(*v1, *v2, *v5, ABSOLUTE));
  solidDet->AddFacet(new G4TriangularFacet(*v2, *v3, *v5 , ABSOLUTE));
  solidDet->AddFacet(new G4TriangularFacet(*v3, *v4, *v5, ABSOLUTE));
  solidDet->AddFacet(new G4TriangularFacet(*v4, *v1, *v5, ABSOLUTE));
  solidDet->AddFacet(new G4QuadrangularFacet(*v4, *v3, *v2, *v1, ABSOLUTE));
  */

  G4LogicalVolume* logicDet = new G4LogicalVolume(solidDet , Air, "Detector",0,0,0);  
  //G4VPhysicalVolume* physiDet = 
  new G4PVPlacement(0, G4ThreeVector(0,0,0), logicDet, "det", logicWorld, false, 0); 
  
  return physiWorld;
}

 
