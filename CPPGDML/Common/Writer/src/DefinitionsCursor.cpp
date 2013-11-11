#include "Writer/DefinitionsCursor.h"

#include "Writer/Element.h"
#include "Writer/EditableDocumentRegistry.h"

#include <sstream>
#include <stdexcept>

namespace gdml
{
  namespace writer
  {
    DefinitionsCursor::DefinitionsCursor(  Element& defElement, EditableDocumentRegistry& edReg )
      : Cursor( defElement, edReg )
    {
    }

    void DefinitionsCursor::addConstant( const std::string& id, double value )
    {
      std::ostringstream os;
      os.precision(15);

      os << value;
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate constant " + id;
        //        msg             += " " + os.str();
        //        throw std::logic_error( msg );
        //      }

      Element c( "constant" );

      c.addAttribute( "name", id );
      c.addAttribute( "value", os.str() );

      m_cursor.appendChild( c );
      }
    }
    
    void DefinitionsCursor::addQuantity( const std::string& id   , const std::string& type,
                                         double             value, const std::string& unit )
    {
      std::ostringstream os;
      os.precision(15);

      os << value;
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate quantity " + id;
        //        msg             += " " + type + " " + os.str() + " " + unit;
        //        throw std::logic_error( msg );
        //      }

      Element q( "quantity" );

      q.addAttribute( "name" , id       );
      q.addAttribute( "type" , type     );
      q.addAttribute( "value", os.str() );
      q.addAttribute( "unit" , unit     );

      m_cursor.appendChild( q );
      }
    }
    
    
    void DefinitionsCursor::addPosition( const std::string& id  ,
                                         double x,
                                         double y,
                                         double z,
                                         const std::string& unit )
    {
      std::ostringstream os;
      os.precision(15);

      os << x; std::string sx = os.str(); os.str("");
      os << y; std::string sy = os.str(); os.str("");
      os << z; std::string sz = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate position " + id;
        //        msg             += " [" + sx + "," + sy + "," + sz + "] in " + unit;
        //        throw std::logic_error( msg );
        //      }

      Element p( "position" );

      p.addAttribute( "name" , id       );
      p.addAttribute( "x", sx );
      p.addAttribute( "y", sy );
      p.addAttribute( "z", sz );
      p.addAttribute( "unit" , unit     );

      m_cursor.appendChild( p );
      }
    }
    
    void DefinitionsCursor::addRotation( const std::string& id  ,
                                         double x,
                                         double y,
                                         double z,
                                         const std::string& unit )
    {
      std::ostringstream os;
      os.precision(15);

      os << x; std::string sx = os.str(); os.str("");
      os << y; std::string sy = os.str(); os.str("");
      os << z; std::string sz = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate rotation " + id;
        //        msg             += " [" + sx + "," + sy + "," + sz + "] in " + unit;
        //        throw std::logic_error( msg );
        //      }

      Element p( "rotation" );

      p.addAttribute( "name" , id       );
      p.addAttribute( "x", sx );
      p.addAttribute( "y", sy );
      p.addAttribute( "z", sz );
      p.addAttribute( "unit" , unit     );

      m_cursor.appendChild( p );
      }
    }
    
    void DefinitionsCursor::addScale(const std::string& id,double x,double y, double z) {

        std::ostringstream os;
        os.precision(15);

        os << x; std::string sx = os.str(); os.str("");
        os << y; std::string sy = os.str(); os.str("");
        os << z; std::string sz = os.str(); os.str("");
      
        if(ok(id)) {
            
	    add(id);

            Element p("scale");
            p.addAttribute("name",id);
            p.addAttribute("x",sx);
            p.addAttribute("y",sy);
            p.addAttribute("z",sz);

            m_cursor.appendChild( p );
        }
    }
    
  }
}
