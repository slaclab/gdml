// -*- C++ -*-
// $Id: EditableDocumentRegistry.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_EDITABLEDOCUMENTREGISTRY_H
#define GDML_WRITER_EDITABLEDOCUMENTREGISTRY_H 1

#include <string>
#include <set>

namespace gdml
{
  namespace writer
  {
    typedef std::set< std::string > IDTable;

    // Forward declaration(s)
    class Element;
    
    /** @class EditableDocumentRegistry EditableDocumentRegistry.h Writer/EditableDocumentRegistry.h
     *
     * This class keeps cached entries which were inserted during @see EditableDocument updates.
     * The entries map XML ID of the element to its element reference.
     */
    class EditableDocumentRegistry
    {
      public:
        /// Constructor
        EditableDocumentRegistry();

        /// Checks if an ID already exists in the registry
        bool has( const std::string& ) const;

        /// Inserts an ID into the registry
        bool add( const std::string& );

        /// Return size of the registry
        size_t size() const
        {
          return m_ids.size();
        }

      private:
        IDTable m_ids; ///< Mapping of unique XML IDs into elements locations
    };
  }
}

#endif // GDML_WRITER_EDITABLEDOCUMENTREGISTRY_H
