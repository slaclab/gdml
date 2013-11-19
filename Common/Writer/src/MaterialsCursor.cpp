#include "Writer/Element.h"
#include "Writer/EditableDocumentRegistry.h"
#include "Writer/MaterialsCursor.h"

#include <sstream>
#include <stdexcept>

namespace gdml
{
  namespace writer
  {
    MaterialsCursor::MaterialsCursor(  Element& defElement, EditableDocumentRegistry& edReg )
      : Cursor( defElement, edReg )
    {
    }
    
    void MaterialsCursor::addIsotope( const std::string& id,    
                                      int                z,       
                                      int                n,      
                                      double             a )     
    {
      std::ostringstream os;
      os.precision(15);

      os << z;      
      std::string sz = os.str(); os.str("");
      os << n;
      std::string sn = os.str(); os.str("");
      os << a;
      std::string sa = os.str(); os.str("");
      
      if( ok( id ) )
        add( id );
      else
      {
        std::string msg  = "Attempt to add duplicate isotope " + id;
        msg             += " Z:" + sz + " N:" + sn + " A:" + sa + "[g/mole]";
        throw std::logic_error( msg );
      }

      Element i( "isotope" );

      Element atom( "atom" );
      atom.addAttribute( "value", sa );
      
      i.appendChild( atom );

      i.addAttribute( "name" , id );
      i.addAttribute( "Z"    , sz );
      i.addAttribute( "N"    , sn );

      m_cursor.appendChild( i );
    }

    void MaterialsCursor::addElement( const std::string& id,   
                                      const std::string& s,     
                                      int                z,     
                                      double             a )    
    {
      std::ostringstream os;
      ;

      os << z;
      std::string sz = os.str(); os.str("");
      os << a;
      std::string sa = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        // }      else
        // {
        // std::string msg  = "Attempt to add duplicate element " + id;
        // msg             += " (" + s + ") Z:" + sz + " A:" + sa + "[g/mole]";
        // throw std::logic_error( msg );
        // }
        
        Element e( "element" );
        
        Element atom( "atom" );
        atom.addAttribute( "value", sa );
        
        e.appendChild( atom );
        
        e.addAttribute( "name"    , id );
        e.addAttribute( "formula" , s );
        e.addAttribute( "Z"       , sz );
        
        m_cursor.appendChild( e );
      }
    }
    
    void MaterialsCursor::addElement( const std::string&     id, 
                                      const FractionsVector& cv, 
                                      const std::string&     s )  
    {
      if( ok( id ) )
        add( id );
      else
      {
        std::string msg  = "Attempt to add duplicate element composed by isotopes " + id;
        throw std::logic_error( msg );
      }

      Element e( "element" );

      for( FractionsVector::const_iterator fit = cv.begin();
           fit != cv.end();
           ++fit )
      {
         e.appendChild( buildFraction(fit) );
      }

      e.addAttribute( "name"    , id );

      if( ! s.empty() )
        e.addAttribute( "formula"    , s );

      m_cursor.appendChild( e );
    }

    void MaterialsCursor::addMaterial( const std::string& id,      
                                       const std::string& formula,  
                                       double             z,        
                                       double             a,         
                                       double             d,         
                                       double             t,         
                                       double             p,         
                                       const std::string& state    ) 
    {
      std::ostringstream os;
      ;

      os << z; std::string sz = os.str(); os.str("");
      os << a; std::string sa = os.str(); os.str("");
      os << d; std::string sd = os.str(); os.str("");
      os << t; std::string st = os.str(); os.str("");
      os << p; std::string sp = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //        std::string msg  = "Attempt to add duplicate material " + id;
        //        msg             += " Z:" + sz + " D:" + sd + " A:" + sa + "[g/mole]";
        //        throw std::logic_error( msg );
        //      }

      Element m( "material" );
			
      Element temperature( "T" );
      temperature.addAttribute( "value", st );
      m.appendChild( temperature );

      Element pressure( "P" );
      pressure.addAttribute( "value", sp );
      m.appendChild( pressure );

			// The density and atom must be after the set of material group of properties
      Element density( "D" );
      density.addAttribute( "value", sd );
      m.appendChild( density );
      
      Element atom( "atom" );
      atom.addAttribute( "value", sa );
      m.appendChild( atom );

			// Attach the attributes as well
      m.addAttribute( "name" , id    );
      m.addAttribute( "Z"    , sz    );
      m.addAttribute( "state", state );

      if( ! formula.empty() )
        m.addAttribute( "formula" , formula );

      m_cursor.appendChild( m );
      }
    }
    
    void MaterialsCursor::addMaterial( const std::string& id,        
                                       const std::string& formula,   
                                       double             z,         
                                       double             a,         
                                       double             d )        
    {
      std::ostringstream os;
      ;

      os << z; std::string sz = os.str(); os.str("");
      os << a; std::string sa = os.str(); os.str("");
      os << d; std::string sd = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate material " + id;
        //        msg             += " Z:" + sz + " D:" + sd + " A:" + sa + "[g/mole]";
        //        throw std::logic_error( msg );
        //      }

      Element m( "material" );

      Element density( "D" );
      density.addAttribute( "value", sd );
      m.appendChild( density );
      
      Element atom( "atom" );
      atom.addAttribute( "value", sa );
      m.appendChild( atom );

      m.addAttribute( "name" , id    );
      m.addAttribute( "Z"    , sz    );

      if( ! formula.empty() )
        m.addAttribute( "formula" , formula );

      m_cursor.appendChild( m );
      }
    }

    void MaterialsCursor::addMaterial( const std::string& id,        
                                       const std::string& formula,   
                                       double             d,         
                                       AtomsVector&       av,        
                                       double             t,         
                                       double             p,         
                                       const std::string& state    ) 
    {
      std::ostringstream os;
      os.precision(15);

      os << d; std::string sd = os.str(); os.str("");
      os << t; std::string st = os.str(); os.str("");
      os << p; std::string sp = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add material composition by atoms " + id + formula ;
        //        msg             += " D:" + sd + "[g/cm3]";
        //        throw std::logic_error( msg );
        //      }

      Element m( "material" );


      Element temperature( "T" );
      temperature.addAttribute( "value", st );
      m.appendChild( temperature );

      Element pressure( "P" );
      pressure.addAttribute( "value", sp );
      m.appendChild( pressure );

      Element density( "D" );
      density.addAttribute( "value", sd );
      m.appendChild( density );      

			// Attach its attributes
      m.addAttribute( "name" , id    );
      m.addAttribute( "state", state );

      if( ! formula.empty() )
        m.addAttribute( "formula" , formula );

      // Add element constituents
      for( AtomsVector::const_iterator ait = av.begin();
           ait != av.end();
           ++ait )
      {
         m.appendChild( buildComposite(ait) );
      }

      m_cursor.appendChild( m );
      } 
    }

    void MaterialsCursor::addMaterial( const std::string& id,        
                                       const std::string& formula,   
                                       double             d,         
                                       AtomsVector&       av)        
    {
      std::ostringstream os;
      ;

      os << d; std::string sd = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add material composition by atoms " + id + formula ;
        //        msg             += " D:" + sd + "[g/cm3]";
        //        throw std::logic_error( msg );
        //      }

      Element m( "material" );
			
      m.addAttribute( "name" , id    );

      if( ! formula.empty() )
        m.addAttribute( "formula" , formula );

      Element density( "D" );
      density.addAttribute( "value", sd );
      m.appendChild( density );

      // Add element constituents
      for( AtomsVector::const_iterator ait = av.begin();
           ait != av.end();
           ++ait )
      {
         m.appendChild( buildComposite(ait) );
      }

      m_cursor.appendChild( m );
      }
    }

    void MaterialsCursor::addMaterial( const std::string& id,        
                                       const std::string& formula,   
                                       double             d,         
                                       FractionsVector&  fv,          
                                       double             t,         
                                       double             p,         
                                       const std::string& state    ) 
    {
      std::ostringstream os;
      ;

      os << d; std::string sd = os.str(); os.str("");
      os << t; std::string st = os.str(); os.str("");
      os << p; std::string sp = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate material composition by fractional mass " + id;
        //        msg             += " " + formula + " D:" + sd + "[g/cm3]";
        //        throw std::logic_error( msg );
        //      }

      Element m( "material" );

      Element temperature( "T" );
      temperature.addAttribute( "value", st );
      m.appendChild( temperature );

      Element pressure( "P" );
      pressure.addAttribute( "value", sp );
      m.appendChild( pressure );

      m.addAttribute( "name" , id    );
      m.addAttribute( "state", state );

      if( ! formula.empty() )
        m.addAttribute( "formula" , formula );

      Element density( "D" );
      density.addAttribute( "value", sd );
      m.appendChild( density );      

      // Add element constituents
      for( FractionsVector::const_iterator fit = fv.begin();
           fit != fv.end();
           ++fit )
      {
         m.appendChild( buildFraction(fit) );
      }

      m_cursor.appendChild( m );
      }
    }

    void MaterialsCursor::addMaterial( const std::string& id,       
                                       const std::string& formula,   
                                       double             d,         
                                       FractionsVector&  fv )        
    {
      std::ostringstream os;
      ;

      os << d; std::string sd = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate material composition by fractional mass " + id;
        //        msg             += " " + formula + " D:" + sd + "[g/cm3]";
        //        throw std::logic_error( msg );
        //      }

      Element m( "material" );

      m.addAttribute( "name" , id    );

      if( ! formula.empty() )
        m.addAttribute( "formula" , formula );

      Element density( "D" );
      density.addAttribute( "value", sd );
      m.appendChild( density );

      // Add element constituents
      for( FractionsVector::const_iterator fit = fv.begin();
           fit != fv.end();
           ++fit )
      {
         m.appendChild( buildFraction(fit) );
      }

      m_cursor.appendChild( m );
      }
    }
    
    //////////////////////   Private methods
    
    Element MaterialsCursor::buildFraction( FractionsVector::const_iterator& fit )
    {
      std::ostringstream os;
      ;

      os << (*fit).second;
      
      Element fraction( "fraction" );

      fraction.addAttribute( "ref" , (*fit).first );
      fraction.addAttribute( "n", os.str()     );

      return fraction;
    }

    Element MaterialsCursor::buildComposite( AtomsVector::const_iterator& ait )
    {
      std::ostringstream os;
      os.precision(15);

      os << (*ait).second;
      
      Element composite( "composite" );

      composite.addAttribute( "ref" , (*ait).first );
      composite.addAttribute( "n", os.str()     );

      return composite;
    }
  }
}
