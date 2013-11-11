#include "Writer/EditableDocumentRegistry.h"

namespace gdml
{
  namespace writer
  {
    EditableDocumentRegistry::EditableDocumentRegistry()
    {
    }

    bool EditableDocumentRegistry::has( const std::string& id ) const
    {
      return( m_ids.find( id ) != m_ids.end() );
    }

    bool EditableDocumentRegistry::add( const std::string& id )
    {
      // The retruened value is pair where second signals successful insert
      // and false means an id already stored in the registry
      return( m_ids.insert( id ).second );
    }
  }
}
