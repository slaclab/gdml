#include "Writer/SetupCursor.h"

#include "Writer/Element.h"
#include "Writer/EditableDocumentRegistry.h"

#include <string>
#include <stdexcept>

namespace gdml
{
  namespace writer
  {
    SetupCursor::SetupCursor( Element& setupElement, EditableDocumentRegistry& edReg )
      : Cursor( setupElement, edReg )
    {
    }
    
    void SetupCursor::addSetup( const std::string& id,
                                const std::string& version,
                                const std::string& worldRef )
    {
      if( ok( id ) )
        add( id );
      else
        throw std::logic_error( "Attempt to insert duplicite setup " + id );

      //      if( ok( worldRef ) )
      //        throw std::logic_error( "The world volume with name " + worldRef + " is not defined!" );

      Element setup( "setup" );
      setup.addAttribute( "name"   , id      );
      setup.addAttribute( "version", version );

      Element world( "world" );
      world.addAttribute( "ref", worldRef );

      setup.appendChild( world );

      m_cursor.appendChild( setup );
    }
  }
}
