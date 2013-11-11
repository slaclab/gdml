#include "Writer/DocumentBuilder.h"

#include "Writer/DefinitionsCursor.h"
#include "Writer/MaterialsCursor.h"
#include "Writer/SolidsCursor.h"
#include "Writer/StructureCursor.h"
#include "Writer/SetupCursor.h"

#include "Writer/Element.h"

#include <iostream>
#include <exception>

void testConstructors(void);
void testDefines( gdml::writer::DocumentBuilder& );
void testMaterials( gdml::writer::DocumentBuilder& );
void testSolids( gdml::writer::DocumentBuilder& );
void testStructure( gdml::writer::DocumentBuilder& );
void testSetup( gdml::writer::DocumentBuilder& );

int main( int , char** )
{
  try
  {
    try
    {
      testConstructors();

      // Set up the proper path to the GDML schema file
      gdml::writer::DocumentBuilder db("testWriter.gdml");

      db.OpenDocument();
      
      //db.setSchemaLocation( "../../GDMLSchema/gdml_1.0.xsd" );
      db.setSchemaLocation( "./GDMLSchema/gdml_1.1.xsd" );

      testDefines( db );
      testMaterials( db );
      testSolids( db );
      testStructure( db );
      testSetup( db );

      db.WriteDocument();
      db.CloseDocument();
    }
    catch( const std::exception& ex )
    {
      std::cerr << "Caught std::exception: " << ex.what()
                << std::endl << std::endl << std::endl;
    }
  }
  catch( ... )
  {
    std::cerr << "Caught unknown exception: "
              << std::endl << std::endl << std::endl;
  }

  return 0;
}

void testConstructors(void)
{
  // This create according to valgrind a memory leak of 700 bytes.
  gdml::writer::DocumentBuilder db1;
      
  db1.OpenDocument();
  db1.ResetDocument();
  db1.WriteDocument();
  db1.CloseDocument();

  db1.OpenDocument();
  db1.WriteDocument( "file1.gdml" );
  db1.CloseDocument();

  db1.OpenDocument();
  db1.WriteDocument( std::cerr );
  db1.CloseDocument();      

  gdml::writer::DocumentBuilder db2("test2.gdml");
  db2.OpenDocument();
  db2.ResetDocument();
  db2.WriteDocument();
  db2.CloseDocument();

  db2.OpenDocument();
  db2.WriteDocument( "file3.gdml" );
  db2.CloseDocument();

  db2.OpenDocument();
  db2.WriteDocument( std::cerr );
  db2.CloseDocument();      

  gdml::writer::DocumentBuilder db3( std::clog );
  db3.OpenDocument();
  db3.ResetDocument();
  db3.WriteDocument();
  db3.CloseDocument();

  db3.OpenDocument();
  db3.WriteDocument( "file4.gdml" );
  db3.CloseDocument();

  db3.OpenDocument();
  db3.WriteDocument( std::cerr );
  db3.CloseDocument();

  std::cerr << std::endl;
  std::cerr << std::endl;  
}

void testDefines( gdml::writer::DocumentBuilder& dbd )
{
  gdml::writer::DefinitionsCursor& defcur = dbd.getDefinitionsCursor();
  defcur.addConstant( "PI", 3.14 );
  defcur.addConstant( "TWOPI", 2*3.14 );

  // Generate duplicate entry
  try
  {
    defcur.addConstant( "PI", 3.14 );
  }
  catch( const std::exception& ex )
  {
    std::cerr << "The bad try handled, was: " << ex.what()
              << std::endl << std::endl << std::endl;
  }
  defcur.addQuantity( "xdim", "length", 4.0, "cm" );
  defcur.addPosition( "center" );
  defcur.addRotation( "identity" );
}

void testMaterials( gdml::writer::DocumentBuilder& dbm )
{	
  gdml::writer::MaterialsCursor& matcur = dbm.getMaterialsCursor();

  /* We're going to insert unit test material data
     <isotope Z="92" N="235" name="U235">
     <atom type="A" value="235.01"/>
     </isotope>
     <isotope name="U238" Z="92.0" N="238">
     <atom type="A" value="238.03"/>
     </isotope>
     <element name="enriched_Uranium">
     <fraction ref="U235" n="0.9"/>
     <fraction ref="U238" n="0.1"/>
     </element>
     <element name="Hydrogen" formula="H"  Z="1.">  <atom value="1.01"/>   </element>
     <element name="Oxygen"   formula="O"  Z="8.">  <atom value="16.0"/>   </element>
     <element name="Nitrogen" formula="N"  Z="7.">  <atom value="14.01"/>  </element>
     <element name="Hydrogen" formula="H"  Z="1.">
     <atom value="1.01"/>
     </element>
     <material name="Al" Z="13.0"> <D value="2.70"/> <atom value="26.98"/> </material>
     <material name="Water" formula="H20">
     <D value="1.0"/>
     <composite n="2" ref="Hydrogen"/>
     <composite n="1" ref="Oxygen"/>
     </material>
     <material name="Air">
     <D value="1.290" unit="mg/cm3"/>
     <fraction n="0.7" ref="Nitrogen"/>
     <fraction n="0.3" ref="Oxygen"/>
     </material>
  </materials>   */
  matcur.addIsotope( "U235", 92, 235, 235.01 );

  // Generate duplicate entry
  try
  {
    matcur.addIsotope( "U235", 92, 235, 235.01 );
  }
  catch( const std::exception& ex )
  {
    std::cerr << "The bad try handled, was: " << ex.what()
              << std::endl << std::endl << std::endl;
  }
  matcur.addIsotope( "U238", 92, 238, 238.03 );

  gdml::writer::FractionsVector cv;
  cv.push_back( std::make_pair( "U235", 0.9 ) );
  cv.push_back( std::make_pair( "U238", 0.1 ) );

  matcur.addElement( "enrichedUranium", cv );
  matcur.addElement( "Hydrogen", "H", 1, 1.01 );
  matcur.addElement( "Oxygen"  , "O", 8, 16.0 );
  
  matcur.addMaterial( "Al", "", 13.0, 26.98, 2.70, 293.15, 101325.0, "solid" );
  matcur.addMaterial( "Nitrogen", "N", 7.0, 14.01, 2.70 );


  gdml::writer::AtomsVector wav;
  wav.push_back( std::make_pair( "Oxygen"   ,1 ) );
  wav.push_back( std::make_pair( "Hydrogen" ,2 ) );
  
  matcur.addMaterial( "Water", "H2O", 1.0, wav, 293.15, 101325.0, "liquid" );

  gdml::writer::FractionsVector afv;
  afv.push_back( std::make_pair( "Oxygen"   , 0.3 ) );
  afv.push_back( std::make_pair( "Nitrogen" , 0.7 ) );
  
  matcur.addMaterial( "Air", "", 0.001290, afv );  
}

void testSolids( gdml::writer::DocumentBuilder& dbs )
{
  gdml::writer::SolidsCursor& sldcur = dbs.getSolidsCursor();

  /*
  <box name="WorldBox" x="10000.0" y="10000.0" z="10000.0"/>
  <box name="b100" x="100.0" y="100.0" z="100.0"/>
  <box name="b500" x="500.0" y="500.0" z="500.0"/>
  */
  sldcur.addBox( "WorldBox", 10000.0, 10000.0, 10000.0 );
  sldcur.addBox( "b100", 100.0, 100.0, 100.0 );
  sldcur.addBox( "b500", 500.0, 500.0, 500.0 );
  
  /*
  <cone name="c1" z="111.0" rmax1="22.0" rmax2="33.0" deltaphi="TWOPI"/>
  */
  sldcur.addCone( "c1", 0, 22.0, 0, 33.0, 111.0, 0, 360, "mm", "deg" ); // FIXME! Use CLHEP constants!
  
  /*
  <para name="p1" x="10.0" y="10.0" z="10.0" alpha="30.0" theta="30.0" phi="30.0"/>
  */
  sldcur.addPara( "p1", 10.0, 10.0, 10.0, 30.0, 30.0, 30.0, "mm", "deg" ); 

  /*
    <sphere name="s1" rmax="200.0" deltaphi="TWOPI" deltatheta="PI"/>
  */
  sldcur.addSphere( "s1", 0, 20.0, 0, 360, 0, 180, "mm", "deg" );
  
  /*
  <trap name="trap1" z="100.0" theta="60.0" phi="60.0"
                             y1="10.0"    x1="10.0" x2="10.0"
                             alpha1="30.0"  y2="10.0" x3="10.0"
                             x4="10.0"    alpha2="30.0"/>
  <trd name="trd1" x1="10.0" x2="10.0" y1="10.0" y2="20.0" z="30.0"/>
  <tube name="t1000" z="1000.0" rmax="100.0" deltaphi="TWOPI"/>
  <tube name="t900" z="900.0" rmax="100.0" deltaphi="TWOPI"/>
  <tube name="t100" z="100.0" rmax="10.0" deltaphi="TWOPI"/>
  */
  /*
  <union name="u1">
   <first ref="b500"/>  <second ref="b100"/>
   <position name="unionidentitypos"/>  <rotation name="unionidentityrot"/>
   </union>
  */
  sldcur.addBoolean( "u1", "union", "b500", "b100", "center", "identity" );
  
  /*
  <union name="u2">
   <first ref="b500"/>  <second ref="t100"/>
   <positionref ref="shiftbyx"/>
   </union>
  */

  /*
  <subtraction name="sub1">
   <first ref="b500"/> <second ref="b100"/>
   <positionref ref="center"/> <rotationref ref="identity"/>
   </subtraction>
  */
  sldcur.addBoolean( "sub1", "subtraction", "b500", "b100", 1.0 );
  
  /*
  <subtraction name="sub2">
   <first ref="t900"/> <second ref="b100"/>
   <positionref ref="center"/> <rotationref ref="identity"/>
  </subtraction>
  <intersection name="intersec1">
   <first ref="b100"/> <second ref="b100"/>
   <positionref ref="identity"/> <rotationref ref="rotatebyx"/>
  </intersection>    
   */
}

void testStructure( gdml::writer::DocumentBuilder& dbs )
{
  gdml::writer::StructureCursor& volcur = dbs.getStructureCursor();

  volcur.addVolume( "v1", "Al", "b100" );
  volcur.addVolume( "ac1", "Air", "s1" );

//   gdml::writer::Element& av = volcur.addAssembly( "a1" );
  // Lazy way of doing it but less error prone though it is slower as we're looking up
  // the assembly volume each time we need a reference to it
  volcur.addAssembly( "a1" );
  volcur.addChild( volcur.findVolume( "a1" ), "ac1", -40, 0, 0 );
  volcur.addChild( volcur.findVolume( "a1" ), "ac1"            );
  volcur.addChild( volcur.findVolume( "a1" ), "ac1",  40, 0, 0 );
  
  // Make sure its reference and not a value because addChild will act on a copy the volume
  // and not on the volume itself. 
  gdml::writer::Element& v2 = volcur.addVolume( "v2", "Al", "b500" );
  volcur.addChild( v2, "v1"             );
  volcur.addChild( v2, "a1", 0, 200        );  
}

void testSetup( gdml::writer::DocumentBuilder& dbs )
{
  gdml::writer::SetupCursor& setcur = dbs.getSetupCursor();

  setcur.addSetup( "Default", "1.0", "v2" );
}
