// -*- C++ -*-
// $Id: SetupCursor.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_SETUPCURSOR_H
#define GDML_WRITER_SETUPCURSOR_H 1

#include "Writer/Cursor.h"

namespace gdml
{
  namespace writer
  {
    /// Forward declaration of Element class
    class Element;
    /// Forward declaration of EditableDocumentRegistry class
    class EditableDocumentRegistry;
    
    /**
     * @class SetupCursor SetupCursor.h Writer/SetupCursor.h
     * The cursor allowing to insert GDML definitions of geometry setups into the Document object.
     *
     * @author Radovan Chytracek, CERN IT/DB, LCG AA
     * @date 19/06/2004
     */
    class SetupCursor : public Cursor
    {
      public:
        /// Constructor
        /// @param setupElement The GDML materials tag reference in the document
        /// @param edReg        The document registry of unique IDs
        SetupCursor( Element& setupElement, EditableDocumentRegistry& edReg );

        /// Add GDML setup
        /// @param id      The name os the setup
        /// @param version The version of the setup
        /// @param worldRef The IDREF reference to a previously defined volume
        ///                 which becomes the top-level volume in this geometry setup
        /// @throws std::logic_error Exception if the setup with same name exists in the document or
        ///                          if world volume reference is not valid
        void addSetup( const std::string& id,
                       const std::string& version,
                       const std::string& worldRef );
    };
  }
}

#endif // GDML_WRITER_SETUPCURSOR_H
