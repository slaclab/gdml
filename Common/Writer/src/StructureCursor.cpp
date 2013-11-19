#include "Writer/StructureCursor.h"

#include "Writer/Element.h"
#include "Writer/EditableDocumentRegistry.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace gdml
{
  namespace writer
  {
    StructureCursor::StructureCursor( Element& solidsElement, EditableDocumentRegistry& edReg )
      : Cursor( solidsElement, edReg )
    {
    }
    Element& StructureCursor::findVolume( const std::string& id )
    {
      const ElementContent& ec = m_cursor.getContent();
      ElementContent::const_reverse_iterator ecit;
      
      for( ecit  = ec.rbegin(); ecit != ec.rend(); ++ecit )
      {
        if( (*ecit).name() == "volume" || (*ecit).name() == "assembly" )
        {
          if( (*(*ecit).getAttributes().find( "name" )).second == id )
            break;
        }
      }
      if( ecit == ec.rend() )
      {
        std::string msg = "The volume with name " + id + " not defined!";
        throw std::logic_error( msg );
      }

      return( const_cast<Element&>( *ecit ) );
    }   

    Element& StructureCursor::addVolume( const std::string& id,
                                         const std::string& materialRef,
                                         const std::string& solidRef )
    {
      // I assume here that I am calling the method with unique names
      // i.e. that they are always different for different volumes 
      // and that I am never calling this method more than once 
      // for the same volume

      //      if( ok( id ) )
      //	{
      //      add( id );
	  //     else
	  //      {
	  //        std::string
	  //          msg  = "Attempt to add duplicate volume " + id + "(" + materialRef + "," + solidRef + ")";
	  //        throw std::logic_error( msg );
	  //      }
      /*
      	  if( ok( materialRef ) )
	    {
	      // Looks weird, but ok(id)=true means that the unique id
	      // is not already in the document registry.
	      std::string msg = materialRef + " not yet defined!";
	      throw std::logic_error( msg );
	    }
	  
	  if(ok(solidRef))
	    {
	      std::cout << "WARNING: " << solidRef <<" not defined!" << std::endl;
	      std::cout << "Probably it's an unknown solid..." << std::endl;
	      std::cout << "solidRef for " << id << " be will wrong!" << std::endl;
	    }
      */  
	  Element v( "volume" );
	  v.addAttribute( "name", id );
	  
	  Element mref( "materialref" );
	  mref.addAttribute( "ref", materialRef );
	  Element sref( "solidref" );
	  sref.addAttribute( "ref", solidRef );
	  
	  v.appendChild( mref );
	  v.appendChild( sref );
	  
	  return( *(m_cursor.appendChild( v )) );
	  //	}
	  //      return;
    }

    Element& StructureCursor::addAssembly( const std::string& id )
    {
      if( ok( id ) )
        add( id );
      else
      {
        std::string msg  = "Attempt to add duplicate assembly volume " + id;
        throw std::logic_error( msg );
      }
      
      Element av( "assembly" );
      av.addAttribute( "name", id );
      
      return( *(m_cursor.appendChild( av )) );
    }
    void StructureCursor::addChild( const std::string& motherVolumeRef,
                                    const std::string& volumeRef,
                                    const std::string& positionRef,
                                    const std::string& rotationRef,
				    const std::string& scaleRef )
    {
      Element& mvol = findVolume( motherVolumeRef );

      /*
      if( ok( volumeRef ) || ok( positionRef ) || ok( rotationRef ) )
      {
        // Looks weird, but ok(id)=true means that the unique id
        // is not already in the document registry.
        std::string msg = volumeRef + " or " + positionRef + " or " + rotationRef + " not yet defined!";
        throw std::logic_error( msg );
      }
      */
      mvol.appendChild(buildChild(volumeRef,positionRef,rotationRef,scaleRef,motherVolumeRef));
    }
    void StructureCursor::addChild( const std::string& motherVolumeRef,
                                    const std::string& volumeRef,
                                    double             x,
                                    double             y,
                                    double             z,
                                    double             rx,
                                    double             ry,
                                    double             rz )
    {
      Element& mvol = findVolume( motherVolumeRef );
      /*
      if( ok( volumeRef ) )
      {
        // Looks weird, but ok(id)=true means that the unique id
        // is not already in the document registry.
        std::string msg = "Volume " + volumeRef + " not yet defined!";
        throw std::logic_error( msg );
      }
      */
      mvol.appendChild( buildChild( volumeRef, x, y, z, rx, ry, rz, motherVolumeRef ) );
    }
    void StructureCursor::addChild( Element&           motherVolume,
                                    const std::string& volumeRef,
                                    const std::string& positionRef,
                                    const std::string& rotationRef,
				    const std::string& scaleRef )
    {
      /*
      if( ok( volumeRef ) || ok( positionRef ) || ok( rotationRef ) )
      {
        // Looks weird, but ok(id)=true means that the unique id
        // is not already in the document registry.
        std::string msg = volumeRef + " or " + positionRef + " or " + rotationRef + " not yet defined!";
        throw std::logic_error( msg );
      }
      */
      
      motherVolume.appendChild(buildChild(volumeRef,positionRef,rotationRef,scaleRef));
    }
    void StructureCursor::addChildFile( const std::string& motherVolumeRef,
                                        const std::string& file,
                                        const std::string& positionRef,
                                        const std::string& rotationRef,
					const std::string& scaleRef )
    {
      Element& motherVolume = findVolume( motherVolumeRef );
      /*
      if( ok( volumeRef ) || ok( positionRef ) || ok( rotationRef ) )
      {
        // Looks weird, but ok(id)=true means that the unique id
        // is not already in the document registry.
        std::string msg = volumeRef + " or " + positionRef + " or " + rotationRef + " not yet defined!";
        throw std::logic_error( msg );
      }
      */
      motherVolume.appendChild(buildChildFile(file,positionRef,rotationRef,scaleRef));
    }
    void StructureCursor::addChild( Element&           motherVolume,
                                    const std::string& volumeRef,
                                    double             x,
                                    double             y,
                                    double             z,
                                    double             rx,
                                    double             ry,
                                    double             rz )
    {
      /*
      if( ok( volumeRef ) )
      {
        // Looks weird, but ok(id)=true means that the unique id
        // is not already in the document registry.
        std::string msg = "Volume " + volumeRef + " not yet defined!";
        throw std::logic_error( msg );
      }
      */
      // This STL gymnastics looks weird.
      // An Element::getAttributeValue( const std::string& attrName ) method
      // would get rid of this, but let's save some work for the future :-)
      const Attributes& mvolAttrs = motherVolume.getAttributes();
      std::string uhint           = (*mvolAttrs.find( "name" )).second;
      std::stringstream  os;
      os.precision(15);

      os << m_reg.size();
      uhint += os.str();
      
      motherVolume.appendChild( buildChild( volumeRef, x, y, z, rx, ry, rz, uhint ) );
    }
    Element StructureCursor::buildChild( const std::string& idRef,
                                         const std::string& positionRef,
                                         const std::string& rotationRef,
                                         const std::string& scaleRef,
				         const std::string& /* uniquenessHint */ )
    {

      Element child("physvol");

      Element vref("volumeref");
      vref.addAttribute("ref",idRef);
      child.appendChild(vref);

      if (positionRef != "") {
      
         Element pref("positionref");
         pref.addAttribute("ref",positionRef);
         child.appendChild(pref);
      }

      if (rotationRef != "") {

         Element rref("rotationref");
         rref.addAttribute("ref",rotationRef);
         child.appendChild(rref);
      }

      if (scaleRef != "") {
      
         Element sref("scaleref");
	 sref.addAttribute("ref",scaleRef);
         child.appendChild(sref);
      }

      return child;
    }

    Element StructureCursor::buildChildFile( const std::string& file,
                                             const std::string& positionRef,
                                             const std::string& rotationRef,
                                             const std::string& scaleRef,
                                             const std::string& /* uniquenessHint */ )
    {
      Element child( "physvol" );

      Element vref("file");
      vref.addAttribute("name",file);
      child.appendChild( vref );

      if (positionRef != "") {
      
         Element pref("positionref");
         pref.addAttribute("ref",positionRef);
         child.appendChild(pref);
      }

      if (rotationRef !="") {

        Element rref( "rotationref" );
        rref.addAttribute( "ref", rotationRef );
        child.appendChild( rref );
      }

      if (scaleRef != "") {
      
         Element sref("scaleref");
	 sref.addAttribute("ref",scaleRef);
         child.appendChild(sref);
      }

      return child;
    }

    Element StructureCursor::buildChild( const std::string& idRef,
                                         double             x,
                                         double             y,
                                         double             z,
                                         double             rx,
                                         double             ry,
                                         double             rz,
                                         const std::string& uniquenessHint )
    {
      std::stringstream os;
      os.precision(15);
      
      Element vref( "volumeref" );
      vref.addAttribute( "ref", idRef );

      os << x;     std::string sx     = os.str(); os.str( "" );
      os << y;     std::string sy     = os.str(); os.str( "" );
      os << z;     std::string sz     = os.str(); os.str( "" );
      os << rx;    std::string srx    = os.str(); os.str( "" );
      os << ry;    std::string sry    = os.str(); os.str( "" );
      os << rz;    std::string srz    = os.str(); os.str( "" );

      std::string pID =  idRef + "in" + uniquenessHint + "pos";

      // Append into registry
      add( pID );

      Element p( "position" );
      p.addAttribute( "name", pID );
      
      if( x != 0.0 || y != 0.0 || z != 0.0 )
      {
        p.addAttribute( "x", sx );
        p.addAttribute( "y", sy );
        p.addAttribute( "z", sz );
      }
      
      std::string rID =  idRef + "in" + uniquenessHint + "rot";

      // Append into registry
      add( rID );

      Element r( "rotation" );
      r.addAttribute( "name", rID );
      
      if( rx != 0.0 || ry != 0.0 || rz != 0.0 )
      {
        r.addAttribute( "x", srx );
        r.addAttribute( "y", sry );
        r.addAttribute( "z", srz );
      }

      Element child( "physvol" );
      child.appendChild( vref );
      child.appendChild( p );
      child.appendChild( r );

      return child;
    }

    Element& StructureCursor::addReplica(const std::string& motherVolume,
                                         const std::string& volumeRef,
                                         int ncopies, int axis,
                                         double width, double offset)
    {
      Element& mvol = findVolume( motherVolume );      
      
      Element replica("replicavol");
      std::stringstream os; 
      os.precision(15);

      os << ncopies;     
      std::string sncopies = os.str(); 
      os.str( "" );
      
      replica.addAttribute("number", sncopies);
      
      Element vref("volumeref");
      vref.addAttribute("ref", volumeRef);  
      replica.appendChild(vref);
      
      Element replicaalg("replicate_along_axis");
      Element dir("direction");
      if(axis==1)
      {
        dir.addAttribute("x", "1");
      }
      else if (axis==2)
      {
        dir.addAttribute("y", "1");
      }
      else if (axis==3)
      {
        dir.addAttribute("z", "1");
      } 

      replicaalg.appendChild(dir);

      Element wid("width");

      os << width;     
      std::string swidth = os.str(); 
      os.str( "" );

      wid.addAttribute("value", swidth);
      wid.addAttribute("unit", "mm");
      replicaalg.appendChild(wid);

      Element offs("offset");
      os << offset;     
      std::string soffset = os.str(); 

      offs.addAttribute("value", soffset);
      offs.addAttribute("unit", "mm");
      replicaalg.appendChild(offs);

      replica.appendChild(replicaalg);
      
      return *(mvol.appendChild(replica));
    }
    
    Element& StructureCursor::addDivision(const std::string& motherVolume,
                                          const std::string& volumeRef,
                                          int ncopies, int axis,
                                          double width, double offset,
                                          const std::string& unit)
    {
      Element& mvol = findVolume( motherVolume );      
      
      Element division("divisionvol");
      std::stringstream os; 
      os.precision(15);

      os << ncopies;     
      std::string sncopies = os.str(); 
      os.str( "" );

      os << width;     
      std::string swidth = os.str(); 
      os.str( "" );

      os << offset;     
      std::string soffset = os.str(); 
      
      division.addAttribute("number", sncopies);
      division.addAttribute("width", swidth);
      division.addAttribute("offset", soffset);

      std::string saxis;

      if(axis==1)
      {
        saxis = "kXAxis";
      }
      else if (axis==2)
      {
        saxis = "kYAxis";
      }
      else if (axis==3)
      {
        saxis = "kZAxis";
      } 
      else if (axis==4)
      {
        saxis = "kRho";
      } 
      else if (axis==5)
      {
        saxis = "kPhi";
      } 

      division.addAttribute("axis", saxis);      

      division.addAttribute("unit", unit);      

      Element vref("volumeref");
      vref.addAttribute("ref", volumeRef);  
      division.appendChild(vref);
            
      return *(mvol.appendChild(division));
    }
    
    Element& StructureCursor::addParameterised(const std::string& motherVolume,
                                               const std::string& volumeRef,
                                               int ncopies)
    {
      Element& mvol = findVolume( motherVolume );
      
      //      if(ok(volumeRef))
      //      {
        // Looks weird, but ok(id)=true means that the unique id
        // is not already in the document registry.
      //        std::string msg = volumeRef + " not yet defined!";
      //        throw std::logic_error( msg );
      //      }
      
      Element parameterised("paramvol");
      std::stringstream os; 
      os.precision(15);

      os << ncopies;     
      std::string sncopies = os.str(); 
      
      parameterised.addAttribute("ncopies", sncopies);
      
      Element vref("volumeref");
      vref.addAttribute("ref", volumeRef);  
      parameterised.appendChild(vref);
      
      Element parameterisation("parameterised_position_size");
      
      parameterised.appendChild(parameterisation);
      
      return *(mvol.appendChild(parameterised));

    }
    
    void StructureCursor::addBoxParameterisation(const std::string& volref, 
                                                 Element& param,
                                                 int ncopy,
                                                 double x,
                                                 double y,
                                                 double z,
                                                 double rx,
                                                 double ry,
                                                 double rz,
                                                 double hx,
                                                 double hy, 
                                                 double hz)
    {
      std::stringstream os;
      os.precision(15);

      os << hx;    std::string shx    = os.str(); os.str( "" );
      os << hy;    std::string shy    = os.str(); os.str( "" );
      os << hz;    std::string shz    = os.str(); os.str( "" );

      Element pars("parameters");
      buildParameters(volref, pars, ncopy, x, y, z, rx, ry, rz);
      
      Element bdim("box_dimensions");
      bdim.addAttribute("x",shx);
      bdim.addAttribute("y",shy);
      bdim.addAttribute("z",shz);
      pars.appendChild(bdim);

      Element& paralg = const_cast<Element&>(param.getElementByName("parameterised_position_size"));
      paralg.appendChild(pars);

    }
    
    void StructureCursor::addTubeParameterisation(const std::string& volref,
                                                  Element& param,
                                                  int ncopy,
                                                  double x,
                                                  double y,
                                                  double z,
                                                  double rx,
                                                  double ry,
                                                  double rz,
                                                  double InR,
                                                  double OutR,
                                                  double hz,
                                                  double StartPhi,
                                                  double DeltaPhi)
    {
      std::stringstream os;
      os.precision(15);

      os << InR;    std::string sInR    = os.str(); os.str( "" );
      os << OutR;    std::string sOutR    = os.str(); os.str( "" );
      os << hz;    std::string shz    = os.str(); os.str( "" );
      os << StartPhi;    std::string sStartPhi    = os.str(); os.str( "" );
      os << DeltaPhi;    std::string sDeltaPhi    = os.str(); os.str( "" );
      
      Element pars("parameters");
      buildParameters(volref, pars, ncopy, x, y, z, rx, ry, rz);

      Element tdim("tube_dimensions");
      tdim.addAttribute("InR",sInR);
      tdim.addAttribute("OutR",sOutR);
      tdim.addAttribute("hz",shz);
      tdim.addAttribute("StartPhi",sStartPhi+"*deg");
      tdim.addAttribute("DeltaPhi",sDeltaPhi+"*deg");
      pars.appendChild(tdim);

      Element& paralg = const_cast<Element&>(param.getElementByName("parameterised_position_size"));
      paralg.appendChild(pars);
    }

    void StructureCursor::buildParameters(const std::string& volref,
                                          Element& pars,
                                          int ncopy,
                                          double x,
                                          double y,
                                          double z,
                                          double rx,
                                          double ry,
                                          double rz)
      
    {
      std::stringstream os;
      os.precision(15);
      
      os << ncopy;
      std::string sncopy = os.str();
      os.str("");
      pars.addAttribute("number",sncopy);
      
      Element pos("position");
      pos.addAttribute("name",volref+"copy"+sncopy+"pos");

      os << x;     std::string sx     = os.str(); os.str( "" );
      os << y;     std::string sy     = os.str(); os.str( "" );
      os << z;     std::string sz     = os.str(); os.str( "" );
      os << rx;    std::string srx    = os.str(); os.str( "" );
      os << ry;    std::string sry    = os.str(); os.str( "" );
      os << rz;    std::string srz    = os.str(); os.str( "" );
      
      pos.addAttribute("x",sx);
      pos.addAttribute("y",sy);
      pos.addAttribute("z",sz);

      pars.appendChild(pos);

      
      if( rx != 0.0 || ry != 0.0 || rz != 0.0 )
      {
        Element r( "rotation" );
        r.addAttribute( "name", "copy"+sncopy+"rot");
        
        r.addAttribute( "x", srx );
        r.addAttribute( "y", sry );
        r.addAttribute( "z", srz );
        
        pars.appendChild(r);
      }
    }
    // end of namespaces
  }  
}
