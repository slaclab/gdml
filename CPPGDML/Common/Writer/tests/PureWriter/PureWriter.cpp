#include "Writer/Element.h"
#include "Writer/Document.h"

#include <iostream>
#include <exception>

int
main( int, char**)
{
  // Empty tag
  try
  {
    // Empty tag
    gdml::writer::Element e;
    e.toXml( std::cout );
  }
  catch( std::exception& ex )
  {
    std::cerr << "std::exception has been caught!" << std::endl;
    std::cerr << ex.what() << std::endl;

    // Simple tag only
    gdml::writer::Element esimple( "aTag" );

    std::cout << std::endl;    
    esimple.toXml( std::cout );
    std::cout << std::endl;

    // Tag with attrs only
    gdml::writer::Attributes attrs;

    attrs["attr1"] = "val1";
    attrs["attr2"] = "val2";
    attrs["attr3"] = "val3";
    
    gdml::writer::Element eattrs( "aTag", attrs );

    std::cout << std::endl;    
    eattrs.toXml( std::cout );
    std::cout << std::endl;

    // Tag with content only
    gdml::writer::ElementContent children;

    children.push_back( gdml::writer::Element( "child1" ) );
    children.push_back( gdml::writer::Element( "child2", attrs ) );    
    
    gdml::writer::Element ecnts( "cTag", children );

    std::cout << std::endl;    
    ecnts.toXml( std::cout );
    std::cout << std::endl;

    // Complete element
    gdml::writer::Element ecomplet( "completeTag", attrs, children );

    std::cout << std::endl;    
    ecomplet.toXml( std::cout );
    std::cout << std::endl;

    ecomplet.addChild( eattrs, 2 );
    
    std::cout << std::endl;    
    ecomplet.toXml( std::cout );
    std::cout << std::endl;

    ecomplet.addChild( eattrs, 0 );
    
    std::cout << std::endl;    
    ecomplet.toXml( std::cout );
    std::cout << std::endl;
    
    ecomplet.addChildren( children );
    
    std::cout << std::endl;    
    ecomplet.toXml( std::cout );
    std::cout << std::endl;
    
    ecomplet.addAttribute( "attradded", "0.77666" );
    
    std::cout << std::endl;    
    ecomplet.toXml( std::cout );
    std::cout << std::endl;

    std::cout << std::endl;
    // Create and empty GDML document and stream it out to COUT
    gdml::writer::Document doc( std::cout );
    doc.Write();
    std::cout << std::endl;
    std::cout << std::endl;
    // Now write only relevant tags
    doc.Write( false );
    std::cout << std::endl;

    // Test writing non-initialized document
    try
    {
      doc.Release();
      doc.Write();
    }
    catch( const std::exception& e )
    {
      std::cerr << std::endl << "std::exception caught: " << e.what() << std::endl;
      // Now handle the problem and re-initialize the doc
      doc.Initialize();
    }
    
    std::cout << std::endl;
    // Now write again
    doc.Write();
    std::cout << std::endl;
  }
  catch( ... )
  {
    std::cerr << "Uknown exception has been caught!" << std::endl;
  }

  std::cout << std::flush;
  
  return 0;
}

