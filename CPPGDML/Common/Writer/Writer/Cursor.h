// -*- C++ -*-
// $Id: Cursor.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_CURSOR_H
#define GDML_WRITER_CURSOR_H 1

#include <string>

namespace gdml
{  
  namespace writer
  {
    class Element;
    class EditableDocumentRegistry;
    
    /** @class Cursor Cursor.h Writer/Cursor.h
     * The cursor allowing to insert GDML definitions into the Document object.
     * In addition to adding the new constants, quantities, positions and rotations
     * it registers them with the registry associated with the current document
     * in order to use them later when building GDML volume structures and setups.
     *
     * @author Radovan Chytracek, CERN IT/DB, LCG AA
     * @date 10/06/2004
     */
    class Cursor
    {
      public:
        /// Constructor
        Cursor( Element& element, EditableDocumentRegistry& registry );
        virtual ~Cursor();

      protected:
        /// Check if the definition already exists, return true if it does not
        bool ok( const std::string& id ) const;
        /// Adds a given ID into the document registry, return the flag from called
        /// EditableDocumentRegistry::add() method
        bool add( const std::string& id );

      protected:
        Element&                  m_cursor;  ///< The GDML document area where cursor operates
        EditableDocumentRegistry& m_reg;     ///< The registry for caching XML IDs
    };
  }
}

#endif // GDML_WRITER_CURSOR_H
