#include "Writer/SolidsCursor.h"

#include "Writer/Element.h"
#include "Writer/EditableDocumentRegistry.h"

#include <sstream>
#include <stdexcept>

namespace gdml
{
  namespace writer
  {
    SolidsCursor::SolidsCursor( Element& solidsElement, EditableDocumentRegistry& edReg )
      : Cursor( solidsElement, edReg )
    {
    }
    
    void SolidsCursor::addTessellated( const std::string&  id,
                                       std::vector<Facet>& facet, 
                                       const std::string& lunit,      
                                       const std::string& aunit)
    {
      if( ok( id ) )
      {
        add( id );
	
        Element s( "tessellated" );

        s.addAttribute( "name"    , id        );
        s.addAttribute( "lunit"   , lunit     );
        s.addAttribute( "aunit"   , aunit     );
        
        for (unsigned int i=0;i<facet.size();i++)
        {
          if(facet[i].isTriangular())
          {
            Element tess("triangular");
            
            tess.addAttribute("vertex1", facet[i].v1());
            tess.addAttribute("vertex2", facet[i].v2());
            tess.addAttribute("vertex3", facet[i].v3());
            
            s.appendChild(tess);
          }
          else
          {
            Element tess("quadrangular");
            
            tess.addAttribute("vertex1", facet[i].v1());
            tess.addAttribute("vertex2", facet[i].v2());
            tess.addAttribute("vertex3", facet[i].v3());
            tess.addAttribute("vertex4", facet[i].v4());
            
            s.appendChild(tess);
          }
        }
        m_cursor.appendChild( s );
      }
    }
    
    void SolidsCursor::addTetrahedron( const std::string& id,
                                       const std::string& vertex1,
                                       const std::string& vertex2,
                                       const std::string& vertex3,
                                       const std::string& vertex4, 
                                       const std::string& lunit,      
                                       const std::string& aunit)
    {
      if( ok( id ) )
      {
        add( id );
	
        Element s( "tet" );
        
        s.addAttribute( "name"      , id          );
        s.addAttribute( "vertex1"   , vertex1     );
        s.addAttribute( "vertex2"   , vertex2     );
        s.addAttribute( "vertex3"   , vertex3     );
        s.addAttribute( "vertex4"   , vertex4     );
        s.addAttribute( "lunit"     , lunit       );
        s.addAttribute( "aunit"     , aunit       );
        
        m_cursor.appendChild( s );
      }
    }
    
    void SolidsCursor::addBox( const std::string& id,              
                               double             x, double             y, double             z,
                               const std::string& lunit,
                               const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);
      os << x;      
      std::string sx = os.str(); os.str("");
      os << y;      
      std::string sy = os.str(); os.str("");
      os << z;      
      std::string sz = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid box " + id;
        //        msg             += " X:" + sx + " Y:" + sy + " Z:" + sz + "[" + lunit + "]";
        //        throw std::logic_error( msg );
        //      }

      Element s( "box" );

      s.addAttribute( "name" , id    );
      s.addAttribute( "x"    , sx    );
      s.addAttribute( "y"    , sy    );
      s.addAttribute( "z"    , sz    );
      s.addAttribute( "lunit", lunit );
      s.addAttribute( "aunit", aunit );

      m_cursor.appendChild( s );
      }
    }
    

  void SolidsCursor::addTwistedBox( const std::string& id,              
					 double             x, double             y, double             z, double Tw,
                               const std::string& lunit,
                               const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(16);
      os << x;      
      std::string sx = os.str(); os.str("");
      os << y;      
      std::string sy = os.str(); os.str("");
      os << z;      
      std::string sz = os.str(); os.str("");
      os << Tw;      
      std::string sTw = os.str(); os.str("");

      if( ok( id ) )
      {
        add( id );

      Element s( "twistedbox" );

      s.addAttribute( "name" , id    );
      s.addAttribute( "x"    , sx    );
      s.addAttribute( "y"    , sy    );
      s.addAttribute( "z"    , sz    );
      s.addAttribute( "PhiTwist", sTw    );
      s.addAttribute( "lunit", lunit );
      s.addAttribute( "aunit", aunit );

      m_cursor.appendChild( s );
      }
    }


 void SolidsCursor::addTwistedTrap( const std::string& id,              
				    double x1, double y1, double x2, double y2, double x3, 
				    double x4, double z, double Tw, double Th, double Phi, double Alph,
				    const std::string& lunit,
				    const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(16);
      os << x1;      
      std::string sx1 = os.str(); os.str("");
      os << y1;      
      std::string sy1 = os.str(); os.str("");
      os << x2;      
      std::string sx2 = os.str(); os.str("");
      os << y2;      
      std::string sy2 = os.str(); os.str("");
      os << x3;      
      std::string sx3 = os.str(); os.str("");
      os << x4;      
      std::string sx4 = os.str(); os.str("");
      os << z;      
      std::string sz = os.str(); os.str("");
      os << Tw;      
      std::string sTw = os.str(); os.str("");
      os << Th;      
      std::string sTh = os.str(); os.str("");
      os << Phi;      
      std::string sPhi = os.str(); os.str("");
      os << Alph;      
      std::string sAlph = os.str(); os.str("");

      if( ok( id ) )
      {
        add( id );

      Element s( "twistedtrap" );

      s.addAttribute( "name" , id    );
      s.addAttribute( "PhiTwist"    , sTw    );
      s.addAttribute( "Theta"    , sTh    );
      s.addAttribute( "Phi"    , sPhi    );
      s.addAttribute( "y1", sy1    );
      s.addAttribute( "x1", sx1    );
      s.addAttribute( "y2", sy2    );
      s.addAttribute( "x2", sx2    );
      s.addAttribute( "x3", sx3    );
      s.addAttribute( "x4", sx4    );
      s.addAttribute( "Alph", sAlph    );
      s.addAttribute( "lunit", lunit );
      s.addAttribute( "aunit", aunit );

      m_cursor.appendChild( s );
      }
    }

    void SolidsCursor::addTwistedTrd( const std::string& id,              
				      double x1, double x2, double y1, double y2, double z, double Tw,
				    const std::string& lunit,
				    const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(16);
      os << x1;      
      std::string sx1 = os.str(); os.str("");
      os << x2;      
      std::string sx2 = os.str(); os.str("");
      os << y1;      
      std::string sy1 = os.str(); os.str("");
      os << y2;      
      std::string sy2 = os.str(); os.str("");
      os << z;      
      std::string sz = os.str(); os.str("");
      os << Tw;      
      std::string sTw = os.str(); os.str("");

      if( ok( id ) )
      {
        add( id );

      Element s( "twistedtrd" );

      s.addAttribute( "name" , id    );
      s.addAttribute( "x1", sx1    );
      s.addAttribute( "x2", sx2    );
      s.addAttribute( "y1", sy1    );
      s.addAttribute( "y2", sy2    );
      s.addAttribute( "z", sz      );
      s.addAttribute( "PhiTwist"    , sTw    );
      s.addAttribute( "lunit", lunit );
      s.addAttribute( "aunit", aunit );

      m_cursor.appendChild( s );
      }
    }    



    void SolidsCursor::addSphere( const std::string& id,
                                  double             rmin      , double             rmax,
                                  double             startphi  , double             deltaphi,
                                  double             starttheta, double             deltatheta,
                                  const std::string& lunit,
                                  const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);

      os << rmin;      
      std::string srmin = os.str(); os.str("");
      os << rmax;      
      std::string srmax = os.str(); os.str("");
      os << startphi;      
      std::string sstartphi = os.str(); os.str("");
      os << deltaphi;      
      std::string sdeltaphi = os.str(); os.str("");
      os << starttheta;      
      std::string sstarttheta = os.str(); os.str("");
      os << deltatheta;      
      std::string sdeltatheta = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid sphere " + id;
        //        msg             += " rmin:" + srmin + " rmax:" + srmax + "[" + lunit + "]";
        //        msg             += " startphi:" + sstartphi + " deltaphi:" + sdeltaphi;
        //        msg             += " starttheta:" + sstarttheta + " deltatheta:" + sdeltatheta;
        //        msg             += "[" + aunit + "]";
        //        
        //        throw std::logic_error( msg );
        //      }

      Element s( "sphere" );

      s.addAttribute( "name"      , id          );
      s.addAttribute( "rmin"      , srmin       );
      s.addAttribute( "rmax"      , srmax       );
      s.addAttribute( "startphi"  , sstartphi   );
      s.addAttribute( "deltaphi"  , sdeltaphi   );
      s.addAttribute( "starttheta", sstarttheta );
      s.addAttribute( "deltatheta", sdeltatheta );
      s.addAttribute( "lunit"     , lunit       );
      s.addAttribute( "aunit"     , aunit       );

      m_cursor.appendChild( s );
      }
    }
    
    void SolidsCursor::addTorus( const std::string& id,
                                 double rmin, double rmax, double rtor,
                                 double startphi, double deltaphi,
                                 const std::string& lunit,
                                 const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);

      os << rmin;      
      std::string srmin = os.str(); os.str("");
      os << rmax;      
      std::string srmax = os.str(); os.str("");
      os << rtor;      
      std::string srtor = os.str(); os.str("");
      os << startphi;      
      std::string sstartphi = os.str(); os.str("");
      os << deltaphi;      
      std::string sdeltaphi = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        
        Element s( "torus" );
        
        s.addAttribute( "name"      , id          );
        s.addAttribute( "rmin"      , srmin       );
        s.addAttribute( "rmax"      , srmax       );
        s.addAttribute( "rtor"      , srtor       );
        s.addAttribute( "startphi"  , sstartphi   );
        s.addAttribute( "deltaphi"  , sdeltaphi   );
        s.addAttribute( "lunit"     , lunit       );
        s.addAttribute( "aunit"     , aunit       );
        
        m_cursor.appendChild( s );
      }
    }
    
    void SolidsCursor::addHype( const std::string& id,
                                double rmin, double rmax, 
                                double inst, double outst, 
                                double z,
                                const std::string& lunit,
                                const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);

      os << rmin;      
      std::string srmin = os.str(); os.str("");
      os << rmax;      
      std::string srmax = os.str(); os.str("");
      os << inst;      
      std::string sinst = os.str(); os.str("");
      os << outst;      
      std::string soutst = os.str(); os.str("");
      os << z;      
      std::string sz = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        
        Element s( "hype" );
        
        s.addAttribute( "name"      , id          );
        s.addAttribute( "rmin"      , srmin       );
        s.addAttribute( "rmax"      , srmax       );
        s.addAttribute( "inst"      , sinst       );
        s.addAttribute( "outst"     , soutst      );
        s.addAttribute( "z"         , sz          );
        s.addAttribute( "lunit"     , lunit       );
        s.addAttribute( "aunit"     , aunit       );
        
        m_cursor.appendChild( s );
      }
    }
    
    void SolidsCursor::addOrb( const std::string& id,
                               double r,
                               const std::string& lunit )
    {
      std::ostringstream os;
      os.precision(15);
      
      os << r;      
      std::string sr = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        
        Element s( "orb" );
        
        s.addAttribute( "name", id );
        s.addAttribute( "r", sr );
        s.addAttribute( "lunit"     , lunit );
        
        m_cursor.appendChild( s );
      }
    }
    
    void SolidsCursor::addTube( const std::string& id,
                                double             rmin    , double             rmax,
                                double             z       ,
                                double             startphi, double             deltaphi,
                                const std::string& lunit,
                                const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);

      os << z;      
      std::string sz = os.str(); os.str("");
      os << rmin;      
      std::string srmin = os.str(); os.str("");
      os << rmax;      
      std::string srmax = os.str(); os.str("");
      os << startphi;      
      std::string sstartphi = os.str(); os.str("");
      os << deltaphi;      
      std::string sdeltaphi = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid tube " + id;
        //        msg             += " Z:" + sz + "[" + lunit + "]";
        //        msg             += " rmin:" + srmin + " rmax:" + srmax + "[" + lunit + "]";
        //        msg             += " startphi:" + sstartphi + " deltaphi:" + sdeltaphi;
        //        msg             += "[" + aunit + "]";
        //        throw std::logic_error( msg );
        //      }

      Element s( "tube" );

      s.addAttribute( "name"    , id        );
      s.addAttribute( "z"       , sz        );
      s.addAttribute( "rmin"    , srmin     );
      s.addAttribute( "rmax"    , srmax     );
      s.addAttribute( "startphi", sstartphi );
      s.addAttribute( "deltaphi", sdeltaphi );
      s.addAttribute( "lunit"   , lunit     );
      s.addAttribute( "aunit"   , aunit     );

      m_cursor.appendChild( s );
      }
    }


 void SolidsCursor::addTwistedTubs( const std::string& id,
                                double             phitwist, double rinner, double router,
                                double             halfz,
                                double             dphi,
                                const std::string& lunit,
                                const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(100);

      os << phitwist;      
      std::string sphitwist = os.str(); os.str("");
      os << rinner;      
      std::string srinner = os.str(); os.str("");
      os << router;      
      std::string srouter = os.str(); os.str("");
      os << halfz;      
      std::string shalfz = os.str(); os.str("");
      os << dphi;      
      std::string sdphi = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );

      Element s( "twistedtubs" );

      s.addAttribute( "name" , id);
      s.addAttribute( "twistedangle"    , sphitwist        );
      s.addAttribute( "endinnerrad"       , srinner        );
      s.addAttribute( "endouterrad"    , srouter     );
      s.addAttribute( "zlen"    , shalfz     );
      s.addAttribute( "phi", sdphi );
      s.addAttribute( "lunit"   , lunit     );
      s.addAttribute( "aunit"   , aunit     );

      m_cursor.appendChild( s );
      }
    }


    void SolidsCursor::addElTube( const std::string& id,              
                                  double dx, double dy, double dz,
                                  const std::string& lunit)
    {
      std::ostringstream os;
      os.precision(15);
      
      os << dx;      
      std::string sdx = os.str(); os.str("");
      os << dy;      
      std::string sdy = os.str(); os.str("");
      os << dz;      
      std::string sdz = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );

        Element s( "eltube" );
        
        s.addAttribute( "name" , id    );
        s.addAttribute( "dx"    , sdx    );
        s.addAttribute( "dy"    , sdy    );
        s.addAttribute( "dz"    , sdz    );
        s.addAttribute( "lunit", lunit );
        
        m_cursor.appendChild( s );
      }
    }
    
    
    void SolidsCursor::addCone( const std::string& id,
                                double             rmin1   , double             rmax1,
                                double             rmin2   , double             rmax2,
                                double             z       ,
                                double             startphi, double             deltaphi,
                                const std::string& lunit,
                                const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);

      os << z;      
      std::string sz = os.str(); os.str("");
      os << rmin1;      
      std::string srmin1 = os.str(); os.str("");
      os << rmax1;      
      std::string srmax1 = os.str(); os.str("");
      os << rmin2;      
      std::string srmin2 = os.str(); os.str("");
      os << rmax2;      
      std::string srmax2 = os.str(); os.str("");
      os << startphi;      
      std::string sstartphi = os.str(); os.str("");
      os << deltaphi;      
      std::string sdeltaphi = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid cone " + id;
        //        msg             += " Z:" + sz + "[" + lunit + "]";
        //        msg             += " rmin1:" + srmin1 + " rmax1:" + srmax1;
        //        msg             += " rmin2:" + srmin2 + " rmax2:" + srmax2 + "[" + lunit + "]";
        //        msg             += " startphi:" + sstartphi + " deltaphi:" + sdeltaphi;
        //        msg             += "[" + aunit + "]";
        
        //        throw std::logic_error( msg );
        //      }

      Element s( "cone" );

      s.addAttribute( "name"    , id        );
      s.addAttribute( "z"       , sz        );
      s.addAttribute( "rmin1"   , srmin1    );
      s.addAttribute( "rmax1"   , srmax1    );
      s.addAttribute( "rmin2"   , srmin2    );
      s.addAttribute( "rmax2"   , srmax2    );
      s.addAttribute( "startphi", sstartphi );
      s.addAttribute( "deltaphi", sdeltaphi );
      s.addAttribute( "lunit"   , lunit     );
      s.addAttribute( "aunit"   , aunit     );

      m_cursor.appendChild( s );
      }
    }
    
    void SolidsCursor::addPolyCone( const std::string& id,
                                    int numberofz,
                                    double startphi, 
                                    double deltaphi,
                                    double* z,
                                    double* rmin,   
                                    double* rmax,
                                    const std::string& lunit,
                                    const std::string& aunit )
    {
      std::ostringstream os;      
      os.precision(15);

      os << startphi;
      std::string sstartphi = os.str(); os.str("");
      os << deltaphi;      
      std::string sdeltaphi = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid cone " + id;
        //        msg             += " startphi:" + sstartphi + " deltaphi:" + sdeltaphi;
        //        msg             += "[" + aunit + "]";        
        //        throw std::logic_error( msg );
        //      }

      Element s( "polycone" );

      s.addAttribute( "name"    , id        );
      s.addAttribute( "startphi", sstartphi );
      s.addAttribute( "deltaphi", sdeltaphi );
      s.addAttribute( "lunit"   , lunit     );
      s.addAttribute( "aunit"   , aunit     );

      for (int i=0;i<numberofz;i++)
      {
        Element zpl("zplane");


        os << z[i];      
        std::string sz = os.str(); os.str("");
        os << rmin[i];      
        std::string srmin = os.str(); os.str("");
        os << rmax[i];
        std::string srmax = os.str(); os.str("");

        zpl.addAttribute("z",sz);
        zpl.addAttribute("rmin",srmin);
        zpl.addAttribute("rmax",srmax);

        s.appendChild(zpl);        
      }
      m_cursor.appendChild( s );
      }
    }

    void SolidsCursor::addPolyhedra( const std::string& id,
                                     int numberofz,
                                     double startphi, 
                                     double deltaphi,
                                     int numsides,
                                     double* z,
                                     std::vector<double>& rmin,
                                     std::vector<double>& rmax, 
                                     const std::string& lunit,
                                     const std::string& aunit )
    {
      std::ostringstream os;      
      os.precision(15);

      os << startphi;
      std::string sstartphi = os.str(); os.str("");
      os << deltaphi;      
      std::string sdeltaphi = os.str(); os.str("");
      os << numsides;      
      std::string snumsides = os.str(); os.str("");
 
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid cone " + id;
        //        msg             += " startphi:" + sstartphi + " deltaphi:" + sdeltaphi;
        //        msg             += "[" + aunit + "]";        
        //        throw std::logic_error( msg );
        //      }

      Element s( "polyhedra" );

      s.addAttribute( "name"    , id        );
      s.addAttribute( "startphi", sstartphi );
      s.addAttribute( "deltaphi", sdeltaphi );
      s.addAttribute( "numsides", snumsides );
      s.addAttribute( "lunit"   , lunit     );
      s.addAttribute( "aunit"   , aunit     );

      for (int i=0;i<numberofz;i++)
      {
        Element rzel("zplane");

        os << z[i];      
        std::string sz = os.str(); os.str("");
        os << rmin[i];      
        std::string srmin = os.str(); os.str("");
        os << rmax[i];      
        std::string srmax = os.str(); os.str("");

        rzel.addAttribute("z",sz);
        rzel.addAttribute("rmin",srmin);
        rzel.addAttribute("rmax",srmax);

        s.appendChild(rzel);        
      }
      m_cursor.appendChild( s );
      }
    }

    
    void SolidsCursor::addPara( const std::string& id,
                                double x, double y, double z,
                                double alpha, double theta, double phi,
                                const std::string& lunit,
                                const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);

      os << x;      
      std::string sx = os.str(); os.str("");
      os << y;      
      std::string sy = os.str(); os.str("");
      os << z;      
      std::string sz = os.str(); os.str("");
      os << alpha;      
      std::string salpha = os.str(); os.str("");
      os << theta;      
      std::string stheta = os.str(); os.str("");
      os << phi;      
      std::string sphi = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid para " + id;
        //        msg             += " X:" + sx + " Y:" + sy + " Z:" + sz + "[" + lunit + "]";
        //        msg             += " alpha:" + salpha + " theta:" + stheta + " phi:" + sphi + "[" + aunit + "]";        
        //        throw std::logic_error( msg );
        //      }

      Element s( "para" );

      s.addAttribute( "name" , id     );
      s.addAttribute( "x"    , sx     );
      s.addAttribute( "y"    , sy     );
      s.addAttribute( "z"    , sz     );
      s.addAttribute( "alpha", salpha );
      s.addAttribute( "theta", stheta );
      s.addAttribute( "phi"  , sphi   );
      s.addAttribute( "lunit", lunit  );
      s.addAttribute( "aunit", aunit  );

      m_cursor.appendChild( s );
      }
    }
    
    
    void SolidsCursor::addTrd( const std::string& id,
                               double             x1,
                               double             x2,
                               double             y1,
                               double             y2,
                               double             z,
                               const std::string& lunit,
                               const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);

      os << x1;
      std::string sx1 = os.str(); os.str("");
      os << y1;
      std::string sy1 = os.str(); os.str("");
      os << x2;
      std::string sx2 = os.str(); os.str("");
      os << y2;
      std::string sy2 = os.str(); os.str("");
      os << z;      
      std::string sz  = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid trd " + id;
        //        msg             += " X1:" + sx1 + " Y1:" + sy1;
        //        msg             += " X2:" + sx2 + " Y2:" + sy2 + " Z:" + sz + "[" + lunit + "]";
        //        throw std::logic_error( msg );
        //      }

      Element s( "trd" );

      s.addAttribute( "name" , id    );
      s.addAttribute( "x1"   , sx1   );
      s.addAttribute( "y1"   , sy1   );
      s.addAttribute( "x2"   , sx2   );
      s.addAttribute( "y2"   , sy2   );
      s.addAttribute( "z"    , sz    );
      s.addAttribute( "lunit", lunit );
      s.addAttribute( "aunit", aunit );

      m_cursor.appendChild( s );
      }
    }
    
    
    void SolidsCursor::addTrap( const std::string& id,
                                double             x1,
                                double             x2,
                                double             y1,
                                double             alpha1,
                                double             x3,
                                double             x4,
                                double             y2,
                                double             alpha2,
                                double             theta,
                                double             z,
                                double             phi,
                                const std::string& lunit,
                                const std::string& aunit )
    {
      std::ostringstream os;
      os.precision(15);

      os << x1;
      std::string sx1 = os.str(); os.str("");
      os << x2;
      std::string sx2 = os.str(); os.str("");
      os << y1;
      std::string sy1 = os.str(); os.str("");
      os << x3;
      std::string sx3 = os.str(); os.str("");
      os << x4;
      std::string sx4 = os.str(); os.str("");
      os << y2;
      std::string sy2 = os.str(); os.str("");
      os << z;      
      std::string sz  = os.str(); os.str("");
      os << alpha1;      
      std::string salpha1 = os.str(); os.str("");
      os << alpha2;      
      std::string salpha2 = os.str(); os.str("");
      os << theta;      
      std::string stheta = os.str(); os.str("");
      os << phi;      
      std::string sphi = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate solid trap " + id;
        //        msg             += " X1:" + sx1 + " X2:" + sx2 + " Y1:" + sy1;
        //        msg             += " X3:" + sx3 + " X4:" + sx4 + " Y2:" + sy2 + "[" + lunit + "]";
        //        msg             += " alpha1:" + salpha1 + " alpha2:" + salpha2;
        //        msg             += " theta:" + stheta + " phi:" + sphi + "[" + aunit + "]";
        //        throw std::logic_error( msg );
        //      }

      Element s( "trap" );

      s.addAttribute( "name"  , id      );
      s.addAttribute( "x1"    , sx1     );
      s.addAttribute( "x2"    , sx2     );
      s.addAttribute( "y1"    , sy1     );
      s.addAttribute( "x3"    , sx3     );
      s.addAttribute( "x4"    , sx4     );
      s.addAttribute( "y2"    , sy2     );
      s.addAttribute( "z"     , sz      );
      s.addAttribute( "alpha1", salpha1 );
      s.addAttribute( "alpha2", salpha2 );
      s.addAttribute( "theta" , stheta  );
      s.addAttribute( "phi"   , sphi    );
      s.addAttribute( "lunit" , lunit   );
      s.addAttribute( "aunit" , aunit   );

      m_cursor.appendChild( s );
      }
    }



    void SolidsCursor::addReflected(const std::string& id,
                                     const std::string& solid,
                                     double xx, double yy, double zz,
                                     double rx, double ry, double rz,
                                    double dx, double dy, double dz,
                                    const std::string& lunit,
                                    const std::string& aunit )

    {
      
      std::ostringstream os;
      os.precision(15);
      
      os << xx;
      std::string sxx = os.str(); os.str("");
      os << yy;
      std::string syy = os.str(); os.str("");
      os << zz;
      std::string szz = os.str(); os.str("");
      os << rx;
      std::string srx = os.str(); os.str("");
      os << ry;
      std::string sry = os.str(); os.str("");
      os << rz;
      std::string srz = os.str(); os.str("");
      os << dx;      
      std::string sdx = os.str(); os.str("");
      os << dy;      
      std::string sdy = os.str(); os.str("");
      os << dz;      
      std::string sdz = os.str(); os.str("");
      
      if( ok( id ) )
      {
        add( id );
        Element s( "reflectedSolid" );
        
        s.addAttribute( "name", id);
        s.addAttribute( "solid", solid);
        s.addAttribute( "sx", sxx);
        s.addAttribute( "sy", syy);
        s.addAttribute( "sz", szz);
        s.addAttribute( "rx", srx);
        s.addAttribute( "ry", sry);
        s.addAttribute( "rz", srz);
        s.addAttribute( "dx", sdx);
        s.addAttribute( "dy", sdy);
        s.addAttribute( "dz", sdz);
        s.addAttribute( "lunit" , lunit   );
        s.addAttribute( "aunit" , aunit   );
        
        m_cursor.appendChild( s );
      }      
    }
    
    
    void SolidsCursor::addBoolean( const std::string& id,
                                   const std::string& typ,
                                   const std::string& first,
                                   const std::string& second,
                                   const std::string& positionRef,
                                   const std::string& rotationRef )
    {
      if( typ.empty() || ( typ != "union" && typ != "subtraction" && typ != "intersection" ) )
      {
        std::string msg = "Attempt to add invalid boolean solid " + id + " with operation: " + typ;
        throw std::logic_error( msg );
      }
          
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate boolean solid " + typ + id;            
        //        throw std::logic_error( msg );
        //      }

      // FIXME! One should check if the IDREFs passed in already exist.
      // FIXME! This is relaxed in this first version.

      Element bs( typ );

      bs.addAttribute( "name", id );

      // Now constituents
      Element firstbs( "first" );
      firstbs.addAttribute( "ref", first );
      bs.appendChild( firstbs );
          
      Element secondbs( "second" );
      secondbs.addAttribute( "ref", second );
      bs.appendChild( secondbs );

      if( ! positionRef.empty() )
      {
        Element pref( "positionref" );
        pref.addAttribute( "ref", positionRef );
        bs.appendChild( pref );
      }
          
      if( ! rotationRef.empty() )
      {
        Element rotref( "rotationref" );
        rotref.addAttribute( "ref", rotationRef );
        bs.appendChild( rotref );
      }          

      m_cursor.appendChild( bs );
      }
    }
    
    
    void SolidsCursor::addBoolean( const std::string& id,
                                   const std::string& typ,
                                   const std::string& first,
                                   const std::string& second,
                                   double             x1,
                                   double             y1,
                                   double             z1,
                                   double             rx1,
                                   double             ry1,
                                   double             rz1,
                                   double             x0,
                                   double             y0,
                                   double             z0,
                                   double             rx0,
                                   double             ry0,
                                   double             rz0 )
    {
      if( typ.empty() || ( typ != "union" && typ != "subtraction" && typ != "intersection" ) )
      {
        std::string msg = "Attempt to add invalid boolean solid " + id + " with operation: " + typ;
        throw std::logic_error( msg );
      }
          
      if( ok( id ) )
      {
        add( id );
        //      else
        //      {
        //        std::string msg  = "Attempt to add duplicate boolean solid " + typ + id;            
        //        throw std::logic_error( msg );
        //      }

      // FIXME! One should check if the IDREFs passed in already exist.
      // FIXME! This is relaxed in this first version.

      Element bs( typ );

      bs.addAttribute( "name", id );

      // Now constituents
      Element firstbs( "first" );
      firstbs.addAttribute( "ref", first );
      bs.appendChild( firstbs );
          
      Element secondbs( "second" );
      secondbs.addAttribute( "ref", second );
      bs.appendChild( secondbs );
      
      if( x1 != 0.0 || y1 != 0.0 || z1 != 0.0 )
      {
        std::ostringstream os;
        os.precision(15);
      
        os << x1;
        std::string sx = os.str(); os.str("");
        os << y1;
        std::string sy = os.str(); os.str("");
        os << z1;
        std::string sz = os.str(); os.str("");

        os << m_reg.size();

        std::string pID =  id+"pos"+os.str();

        add( pID );
        
        Element pref( "position" );
        pref.addAttribute( "name", pID );
        pref.addAttribute( "x", sx );
        pref.addAttribute( "y", sy );
        pref.addAttribute( "z", sz );
        pref.addAttribute( "unit" , "mm");
            
        bs.appendChild( pref );
      }

      if( x0 != 0.0 || y0 != 0.0 || z0 != 0.0 )
      {
        std::ostringstream os;
        os.precision(15);

        os << x0;
        std::string sx = os.str(); os.str("");
        os << y0;
        std::string sy = os.str(); os.str("");
        os << z0;
        std::string sz = os.str(); os.str("");

        os << m_reg.size();

        std::string pID =  id+"pos"+os.str();

        add( pID );
        
        Element pref( "firstposition" );
        pref.addAttribute( "name", pID );
        pref.addAttribute( "x", sx );
        pref.addAttribute( "y", sy );
        pref.addAttribute( "z", sz );
        pref.addAttribute( "unit" , "mm");
            
        bs.appendChild( pref );
      }
          
      if( rx1 != 0.0 || ry1 != 0.0 || rz1 != 0.0 )
      {
        std::ostringstream os;
        os.precision(15);
              
        os << rx1;
        std::string srx = os.str(); os.str("");
        os << ry1;
        std::string sry = os.str(); os.str("");
        os << rz1;
        std::string srz = os.str(); os.str("");
            
        os << m_reg.size();

        std::string rID =  id+"rot"+os.str();
        
        add( rID );

        Element rref( "rotation" );
        rref.addAttribute( "name", rID );
        rref.addAttribute( "x", srx );
        rref.addAttribute( "y", sry );
        rref.addAttribute( "z", srz );
        rref.addAttribute( "unit", "degree" );
                
        bs.appendChild( rref );
      }

      if( rx0 != 0.0 || ry0 != 0.0 || rz0 != 0.0 )
      {
        std::ostringstream os;
        os.precision(15);
              
        os << rx0;
        std::string srx = os.str(); os.str("");
        os << ry0;
        std::string sry = os.str(); os.str("");
        os << rz0;
        std::string srz = os.str(); os.str("");
            
        os << m_reg.size();

        std::string rID =  id+"rot"+os.str();
        
        add( rID );

        Element rref( "firstrotation" );
        rref.addAttribute( "name", rID );
        rref.addAttribute( "x", srx );
        rref.addAttribute( "y", sry );
        rref.addAttribute( "z", srz );
        rref.addAttribute( "unit", "degree" );
                
        bs.appendChild( rref );
      }
      
      m_cursor.appendChild( bs );
      }
    }

    void SolidsCursor::addXtru(const std::string& id,
                               const std::string& lunit,
                               int numVertex,
                               double* vertex,
			       int numSection,
                               double* section) {
		 
        if (!ok(id)) {

            std::string msg = "Attempt to add duplicated solid xtru " + id;
            throw std::logic_error(msg);	
	    return;
	}

        add(id);

        std::ostringstream os;
        os.precision(15);

        Element elementXtru("xtru");
        elementXtru.addAttribute("name",id);
        elementXtru.addAttribute("lunit",lunit);

        for (int i=0;i<numVertex;i++) {

	    Element elementVertex("twoDimVertex");

            os.str(""); os << vertex[2*i+0]; elementVertex.addAttribute("x",os.str());
            os.str(""); os << vertex[2*i+1]; elementVertex.addAttribute("y",os.str());

            elementXtru.appendChild(elementVertex);
	}
    
        for (int i=0;i<numSection;i++) {
	
	    Element elementSection("section");

            os.str(""); os << i; elementSection.addAttribute("zOrder",os.str());	// zOrder is the zero-based index for every section

            os.str(""); os << section[4*i+0]; elementSection.addAttribute("zPosition",os.str());
            os.str(""); os << section[4*i+1]; elementSection.addAttribute("xOffset",os.str());
            os.str(""); os << section[4*i+2]; elementSection.addAttribute("yOffset",os.str());
            os.str(""); os << section[4*i+3]; elementSection.addAttribute("scalingFactor",os.str());

            elementXtru.appendChild(elementSection);
        }
    
        m_cursor.appendChild(elementXtru);
    }
  }
}
