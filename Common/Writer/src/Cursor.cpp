#include "Writer/Cursor.h"

#include "Writer/Element.h"
#include "Writer/EditableDocumentRegistry.h"

#include <stdexcept>

namespace gdml
{
  namespace writer
  {
    Cursor::Cursor(  Element& element, EditableDocumentRegistry& registry )
      : m_cursor( element ),
        m_reg( registry )
    {
    }

    Cursor::~Cursor()
    {
    }

    bool Cursor::ok( const std::string& id ) const
    {
      return(! m_reg.has(id) );
    }

    bool Cursor::add( const std::string& id )
    {
      return( m_reg.add(id) );
    }    
  }
}
