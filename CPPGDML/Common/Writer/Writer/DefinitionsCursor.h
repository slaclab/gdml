// -*- C++ -*-
// $Id: DefinitionsCursor.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_DEFINITIONSCURSOR_H
#define GDML_WRITER_DEFINITIONSCURSOR_H 1

#include "Writer/Cursor.h"

namespace gdml
{
  namespace writer
  {
    class Element;
    class EditableDocumentRegistry;
    
    /** @class DefinitionsCursor DefinitionsCursor.h Writer/DefinitionsCursor.h
     * The cursor allowing to insert GDML definitions into the Document object.
     * In addition to adding the new constants, quantities, positions and rotations
     * it registers them with the registry associated with the current document
     * in order to use them later when building GDML volume structures and setups.
     *
     * @author Radovan Chytracek, CERN IT/DB, LCG AA
     * @date 08/06/2004
     */
    class DefinitionsCursor : public Cursor
    {
      public:
        /// Constructor
        DefinitionsCursor( Element& defElement, EditableDocumentRegistry& edReg );

        /// Add a GDML constant
        void addConstant( const std::string& id, double value );
        /// Add a GDML quantity
        void addQuantity( const std::string& id   , const std::string& type,
                          double             value, const std::string& unit );
        /// Add GDML position
        void addPosition( const std::string& id  ,
                          double x=0.0,
                          double y=0.0,
                          double z=0.0,
                          const std::string& unit="mm" );
        /// Add GDML rotation
        void addRotation( const std::string& id  ,
                          double x=0.0,
                          double y=0.0,
                          double z=0.0,
                          const std::string& unit="radian" );

        void addScale(const std::string& id,double x=1.0,double y=1.0,double z=1.0);
    };
  }
}

#endif // GDML_WRITER_DEFINITIONSCURSOR_H
