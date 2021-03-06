//
#include "Processes/MaterialTypeProcess.h"

#include "Schema/element.h"

#include <cstdlib>
#include <iostream>

class elementProcess : public MaterialTypeProcess
{
public:
  elementProcess( const ProcessingContext* context = 0 )
  : MaterialTypeProcess( context ) {
  }
  
  virtual ~elementProcess() {
  }
  
  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs )
  {    
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
    std::string ename = attrs.getValue( "name" );
    std::string ef    = attrs.getValue( "formula" );
    std::string en    = attrs.getValue( "N" );
    std::string ez    = attrs.getValue( "Z" );

    SAXObject** obj = Context()->GetTopObject();

    element* el = new element;
    
    el->set_name( ename );
    el->set_formula( ef );
    
    if( !en.empty() )
      el->set_N( en );
    if( !ez.empty() )
      el->set_Z( ez );
    
    m_obj = el;
    *obj  = el;
  }
  
  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name )
  {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
    try
    {
      SAXObject** obj = Context()->GetTopObject();
      element* saxobj = dynamic_cast<element*>( *obj );
      
      if( saxobj != 0 ) {
        //std::cout << "PROCESS END OF TAG:: element " << saxobj->get_name()
        //          << " looks OK" << std::endl;
      } else {
        std::cerr << "PROCESS END OF TAG::element GOT ZERO DATA POINTER! " << std::endl;
      }
    }
    catch( ... )
    {
      std::cerr << "PROCESS END OF TAG " << name << " ERROR: "
                << " Cannot cast properly the data object!" << std::endl;
    }
  }
  
  // Analogical to SAX characters callback, it's called for ignorableWhitespace too!
  virtual void Characters( const std::string& ) {
  }
  
  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name )
  {
    //std::cout << "PROCESS::element NOTIFIED AFTER THE TAG: " << name << std::endl;
       
    SAXObject** obj = Context()->GetTopObject();
    
		if( name == "atom" || name == "fraction" ) {
		  element* el = dynamic_cast<element*>( m_obj );
      el->set_AtomOrFraction( name, *obj );
		}	else if( name == "D" || name == "Dref" ) {
      element* saxobj = dynamic_cast<element*>( m_obj );
      saxobj->set_DorDref( name, *obj );
    } else {
      MaterialTypeProcess::StackPopNotify( name );
    }
  }
  
  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "element";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(elementProcess)

