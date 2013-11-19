// -*- C++ -*-
// $Id: MaterialsCursor.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_MATERIALSCURSOR_H
#define GDML_WRITER_MATERIALSCURSOR_H 1

#include "Writer/Cursor.h"

#include <string>
#include <vector>

namespace gdml
{
  namespace writer
  {
    // Forward declarations
    class Element;
    class EditableDocumentRegistry;
    
    /** Vector of material fraction composites, where item is defined as std::pair of:
     *  first  - composite ID (name)
     *  second - fraction or relative abundance
     */
    typedef std::vector< std::pair< std::string, double> > FractionsVector;    

    /** Vector of material atom composites, where item is defined as std::pair of:
     *  first  - composite ID (name)
     *  second - number of atoms
     */
    typedef std::vector< std::pair< std::string, unsigned int> > AtomsVector;    
    
    /**
     * @class MaterialsCursor MaterialsCursor.h Writer/MaterialsCursor.h
     * The cursor allowing to insert GDML definitions into the Document object.
     * In addition to adding the new constants, quantities, positions and rotations
     * it registers them with the registry associated with the current document
     * in order to use them later when building GDML volume structures and setups.
     *
     * @author Radovan Chytracek, CERN IT/DB, LCG AA
     * @date 08/06/2004
     */
    class MaterialsCursor : public Cursor
    {
      public:
        /// Constructor
        /// @param defElement The GDML materials tag reference in the document
        /// @param edReg      The document registry of unique IDs
        MaterialsCursor( Element& defElement, EditableDocumentRegistry& edReg );

        /// Add GDML material isotope
        /// @param id Name of the isotope
        /// @param z  Atomic number
        /// @param n  Number of nucleons
        /// @param a  Mass of mole, expected unit g/mole
        /// @throws std::logic_error Exception if the isotope with the same id
        ///                          already exists in the document
        void addIsotope( const std::string& id,      
                         int                z,       
                         int                n,       
                         double             a );     
        /// Add GDML material element in a simple way
        /// @param id Name of the material element
        /// @param s  GDML element symbol name
        /// @param z  Effective atomic number
        /// @param a  Effective mass of mole, expected unit g/mole
        /// @throws std::logic_error Exception if the element with the same id
        ///                          already exists in the document
        void addElement( const std::string& id,     
                         const std::string& s,      
                         int                z,      
                         double             a );    
        /// Add GDML material element via composition by isotopes
        /// @param id Name of the material element
        /// @param cv Vector of pairs (isotopeId, fraction) and the isotopes
        ///           must be defined in the GDML document
        /// @param s  GDML element symbol name, ignored if empty
        /// @throws std::logic_error Exception if the element with the same id
        ///                          already exists in the document
        void addElement( const std::string&     id, 
                         const FractionsVector& cv, 
                         const std::string&     s="" ); 
        /// Add GDML material using implicit definition a la GDML element
        /// @param id      Name of the material
        /// @param formula Chemical formula of the material
        /// @param z       Effective atomic number
        /// @param a       Effective mass of mole,  expected unit g/mole
        /// @param d       Density of the material, expected unit g/cm3
        /// @param t       Temperature,             expected unit K
        /// @param p       Pressure,                expected unit P
        /// @param state   Material state,          one of: gas,solid,liquid,unknown
        /// @throws std::logic_error Exception if the material with the same id
        ///                          already exists in the document
        void addMaterial( const std::string& id,         
                          const std::string& formula,    
                          double             z,          
                          double             a,          
                          double             d,          
                          double             t,          
                          double             p,          
                          const std::string& state="" ); 
        /// Add GDML material using implicit definition a la GDML element.
        /// This is simplified version inserting automatically defaults for
        /// temperature, pressure and state
        /// @param id      Name of the material
        /// @param formula Chemical formula of the material
        /// @param z       Effective atomic number
        /// @param a       Effective mass of mole,  expected unit g/mole
        /// @param d       Density of the material, expected unit g/cm3
        /// @throws std::logic_error Exception if the material with the same id
        ///                          already exists in the document
        void addMaterial( const std::string& id,      
                          const std::string& formula, 
                          double             z,       
                          double             a,       
                          double             d );     
        /// Add GDML composite material from element constituents
        /// specified by number of number of atoms.
        /// @param id      Name of the material
        /// @param formula Chemical formula of the material
        /// @param d       Density of the material, expected unit g/cm3
        /// @param av      Vector of pairs as (element_ref,atom_count) the element_ref
        ///                is ID of an already defined GDML element.
        /// @param t       Temperature,             expected unit K
        /// @param p       Pressure,                expected unit P
        /// @param state   Material state,          one of: gas,solid,liquid,unknown
        /// @throws std::logic_error Exception if the material with the same id
        ///                          already exists in the document
        void addMaterial( const std::string& id,         
                          const std::string& formula,    
                          double             d,          
                          AtomsVector&       av,         
                          double             t,          
                          double             p,          
                          const std::string& state="" ); 
        /// Add GDML composite material from element constituents
        /// specified by number of number of atoms. This is simplified version
        /// inserting defaults for temperature, pressure and state properties.
        /// @param id      Name of the material
        /// @param formula Chemical formula of the material
        /// @param d       Density of the material, expected unit g/cm3
        /// @param av      Vector of pairs as (element_ref,atom_count) the element_ref
        ///                is ID of an already defined GDML element.
        /// @throws std::logic_error Exception if the material with the same id
        ///                          already exists in the document
        void addMaterial( const std::string& id,         
                          const std::string& formula,    
                          double             d,          
                          AtomsVector&       av);        
        /// Add GDML composite material from element or other mixture constituents
        /// specified by fractional mass.
        /// @param id      Name of the material
        /// @param formula Chemical formula of the material
        /// @param d       Density of the material, expected unit g/cm3
        /// @param fv      Vector of pairs as (element_ref,fraction) the element_ref
        ///                is ID of an already defined GDML element.
        /// @param t       Temperature,             expected unit K
        /// @param p       Pressure,                expected unit P
        /// @param state   Material state,          one of: gas,solid,liquid,unknown
        /// @throws std::logic_error Exception if the material with the same id
        ///                          already exists in the document
        void addMaterial( const std::string& id,         
                          const std::string& formula,    
                          double             d,          
                          FractionsVector&  fv,          
                          double             t,          
                          double             p,          
                          const std::string& state="" ); 
        /// Add GDML composite material from element or other mixture constituents
        /// specified by fractional mass. This is simplified version
        /// inserting defaults for temperature, pressure and state properties.
        /// @param id      Name of the material
        /// @param formula Chemical formula of the material
        /// @param d       Density of the material, expected unit g/cm3
        /// @param fv      Vector of pairs as (element_ref,fraction) the element_ref
        ///                is ID of an already defined GDML element.
        /// @throws std::logic_error Exception if the material with the same id
        ///                          already exists in the document
        void addMaterial( const std::string& id,       
                          const std::string& formula,  
                          double             d,        
                          FractionsVector&  fv );      
        
      private:
        /// Build the fraction element from a FractionVector item
        /// @param fit FractionsVector item iterator
        Element buildFraction( FractionsVector::const_iterator& fit );
        
        /// Build the composite element from an AtomsVector item
        /// @param ait AtomsVector item iterator
        Element buildComposite( AtomsVector::const_iterator& ait );
    };
  }
}

#endif // GDML_WRITER_MATERIALSCURSOR_H
