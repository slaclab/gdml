// -*- C++ -*-
// $Id: SolidsCursor.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_SOLIDSCURSOR_H
#define GDML_WRITER_SOLIDSCURSOR_H 1

#include "Writer/Cursor.h"
#include "Writer/Facet.h"
#include <vector>

namespace gdml
{
  namespace writer
  {
    /// Forward declaration of Element class
    class Element;
    /// Forward declaration of EditableDocumentRegistry class
    class EditableDocumentRegistry;

    /**
     * @class SolidsCursor SolidsCursor.h Writer/SolidsCursor.h
     * The cursor allowing to insert GDML definitions of solids into the Document object.
     * In addition to adding the new constants, quantities, positions and rotations
     * it registers them with the registry associated with the current document
     * in order to use them later when building GDML volume structures and setups.
     *
     * @author Radovan Chytracek, CERN IT/DB, LCG AA
     * @date 15/06/2004
     */
    class SolidsCursor : public Cursor
    {
    public:
      /// Constructor
      /// @param solidsElement The GDML materials tag reference in the document
      /// @param edReg         The document registry of unique IDs
      SolidsCursor( Element& solidsElement, EditableDocumentRegistry& edReg );
      
      /// Add GDML tessellated solid
      /// @param id    Name of the solid
      /// @param facet Vector containing all the facets
      /// @param lunit Length unit, default [mm]
      /// @param aunit Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document
      void addTessellated( const std::string&  id,
                           std::vector<Facet>& facet, 
                           const std::string& lunit="mm",      
                           const std::string& aunit="radian");
			   
      /// Add GDML tetrahedron solid
      /// @param id      Name of the solid
      /// @param vertex1 String containing the name of the first vertex constant defined in the "define" section
      /// @param vertex2 String containing the name of the second vertex constant defined in the "define" section
      /// @param vertex3 String containing the name of the third vertex constant defined in the "define" section
      /// @param vertex4 String containing the name of the fourth vertex constant defined in the "define" section
      /// @param lunit   Length unit, default [mm]
      /// @param aunit   Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document
      void addTetrahedron( const std::string& id,
                           const std::string& vertex1,
		           const std::string& vertex2,
			   const std::string& vertex3,
			   const std::string& vertex4, 
                           const std::string& lunit="mm",      
                           const std::string& aunit="radian");

      /// Add GDML box solid
      /// @param id    Name of the solid
      /// @param x     Dimension along X axis
      /// @param y     Dimension along Y axis
      /// @param z     Dimension along Z axis
      /// @param lunit Length unit, default [mm]
      /// @param aunit Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document
      void addBox( const std::string& id,              
                   double             x,               
                   double             y,               
                   double             z,               
                   const std::string& lunit="mm",      
                   const std::string& aunit="radian" );

  /// Add GDML twistedbox solid
      /// @param id    Name of the solid
      /// @param pDx     Dimension along X axis
      /// @param pDy     Dimension along Y axis
      /// @param pDz     Dimension along Z axis
      /// @param pPhiTwist  Twist Angle
      /// @param lunit Length unit, default [mm]
      /// @param aunit Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document
      void addTwistedBox( const std::string& id,              
                   double             x,               
                   double             y,               
                   double             z,    
		   double             Tw,
                   const std::string& lunit="mm",      
                   const std::string& aunit="radian" );

      /// Add GDML twistedTrap solid
      /// @param id    Name of the solid
      /// @param pDx1     Dimension along x1 axis
      /// @param pDx2     Dimension along x2 axis  
      /// @param pDx3     Dimension along x3 axis  
      /// @param pDx4     Dimension along x4 axis
      /// @param pDy1     Dimension along y1 axis
      /// @param pDy2     Dimension along y2 axis
      /// @param pDz      Dimension along z axis
      /// @param pPhiTwist Twist Angle
      /// @param pTheta   between planes polar angle
      /// @param pPhi     azimuthal angle
      /// @param pAlph    tilt angle
      /// @param lunit Length unit, default [mm]
      /// @param aunit Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document

      void addTwistedTrap( const std::string& id,              
		    double x1, 
	   	    double y1, 
		    double x2, 
		    double y2, 
		    double x3, 
		    double x4, 
		    double z, 
		    double Tw, 
		    double Th, 
		    double Phi, 
		    double Alph,
		    const std::string& lunit="mm",
 		    const std::string& aunit="radian"  );

      /// Add GDML twistedTrp solid
      /// @param id    Name of the solid
      /// @param pDx1     Dimension along x1 axis
      /// @param pDx2     Dimension along x2 axis  
      /// @param pDy1     Dimension along y1 axis
      /// @param pDy2     Dimension along y2 axis
      /// @param pDz      Dimension along z axis
      /// @param pPhiTwist Twist Angle
      /// @param lunit Length unit, default [mm]
      /// @param aunit Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document

    void addTwistedTrd( const std::string& id,              
			double x1, double x2, double y1, double y2, double z, double Tw,
				    const std::string& lunit="mm",
			const std::string& aunit="rad" );

      /// Add GDML sphere solid
      /// @param id          Name of the solid
      /// @param rmin        Inner radius
      /// @param rmax        Outer radius
      /// @param startphi    Starting angle of the segment in radians(0 &lt;= phi &lt;= 2*PI)
      /// @param deltaphi    Delta angle of the segment in radians
      /// @param starttheta  Starting angle of the segment in radians
      ///                    (0 &lt;= theta &lt;= PI)
      /// @param deltatheta  Delta angle of the segment in radians
      /// @param lunit       Length unit, default [mm]
      /// @param aunit       Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document
      void addSphere( const std::string& id,
                      double             rmin,
                      double             rmax,
                      double             startphi,
                      double             deltaphi,
                      double             starttheta,
                      double             deltatheta,
                      const std::string& lunit="mm",   
                      const std::string& aunit="radian" );
      /// Add GDML tube solid
      /// @param id          Name of the solid
      /// @param rmin        Inner radius
      /// @param rmax        Outer radius
      /// @param z           Length along Z axis
      /// @param startphi    The starting phi angle in radians, adjusted such that
      ///                    (startphi+deltaphi &lt;= 2PI, startphi &gt; -2PI)
      /// @param deltaphi    Delta angle of the segment in radians
      /// @param lunit       Length unit, default [mm]
      /// @param aunit       Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document
      void addTube( const std::string& id,
                    double             rmin,
                    double             rmax,
                    double             z,
                    double             startphi,
                    double             deltaphi,
                    const std::string& lunit="mm",   
                    const std::string& aunit="radian" );
  ///Add GDML twisted tube segment solid
      ///@param phitwist             twist angle of tube
      ///@param rinner               inner radius of tube
      ///@param router               outer radius of tube
      ///@param halfz                z length / 2
      ///@param dphi                 angle of segment.
      void addTwistedTubs( const std::string& id,
                    double             phitwist, double rinner, double router,
                    double             halfz,
                    double             dphi,
                    const std::string& lunit="mm",
		    const std::string& aunit="deg" );


      /// Add GDML cone solid
      /// @param id          Name of the solid
      /// @param rmin1       Inner radius at z/2
      /// @param rmax1       Outer radius at z/2
      /// @param rmin2       Inner radius at z/2
      /// @param rmax2       Outer radius at z/2
      /// @param z           Length along Z axis
      /// @param startphi    The starting phi angle in radians, adjusted such that
      ///                    (startphi+deltaphi &lt;= 2PI, startphi &gt; -2PI)
      /// @param deltaphi    Delta angle of the segment in radians
      /// @param lunit       Length unit, default [mm]
      /// @param aunit       Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document
      void addCone( const std::string& id,
                    double             rmin1,
                    double             rmax1,
                    double             rmin2,
                    double             rmax2,
                    double             z,
                    double             startphi,
                    double             deltaphi,
                    const std::string& lunit="mm",   
                    const std::string& aunit="radian" );
      /// Add GDML PolyCone solid
      /// @param id          Name of the solid
      /// @param numberofz   number of z
      /// @param startphi    The starting phi angle in radians, adjusted such that
      ///                    (startphi+deltaphi &lt;= 2PI, startphi &gt; -2PI)
      /// @param deltaphi    Delta angle of the segment in radians
      /// @param z           array of z 
      /// @param rmin        array of rmin
      /// @param rmax        array of rmax
      /// @param lunit       Length unit, default [mm]
      /// @param aunit       Angle unit, default [radian]
      /// @throws std::logic_error Exception if the box with the same id
      ///                          already exists in the document
      void addPolyCone( const std::string& id,
                        int numberofz,
                        double             startphi, 
                        double             deltaphi,
                        double*             z,
                        double*             rmin,   
                        double*             rmax,
                        const std::string& lunit="mm",
                        const std::string& aunit="radian" );
        
    /// Add GDML parallelpiped solid
    /// @param id          Name of the solid
    /// @param x           Dimension along X axis
    /// @param y           Dimension along Y axis
    /// @param z           Dimension along Z axis
    /// @param alpha       Angle formed by the y axis and by the plane
    ///                    joining the centre of the faces parallel
    ///                    to the z-x plane at -y and +y
    /// @param theta       Polar angle of the line joining the centres of
    ///                    the faces at -z and +z in z
    /// @param phi         Azimuthal angle of the line joining the centres
    ///                    of the faces at -z and +z in z
    /// @param lunit       Length unit, default [mm]
    /// @param aunit       Angle unit, default [radian]
    /// @throws std::logic_error Exception if the box with the same id
    ///                          already exists in the document
    void addPara( const std::string& id,
                  double             x,
                  double             y,
                  double             z,
                  double             alpha,
                  double             theta,
                  double             phi,
                  const std::string& lunit="mm",
                  const std::string& aunit="radian" );
    /// Add GDML trapezoid solid
    /// @param id          Name of the solid
    /// @param x1          Length along x at the surface positioned at -z
    /// @param x2          Length along x at the surface positioned at +z
    /// @param y1          Length along y at the surface positioned at -z
    /// @param y2          Length along y at the surface positioned at +z
    /// @param z           Dimension along Z axis
    /// @param lunit       Length unit, default [mm]
    /// @param aunit       Angle unit, default [radian]
    /// @throws std::logic_error Exception if the box with the same id
    ///                          already exists in the document
    void addTrd( const std::string& id,
                 double             x1,
                 double             x2,
                 double             y1,
                 double             y2,
                 double             z,
                 const std::string& lunit="mm",
                 const std::string& aunit="radian" );
    /// Add GDML general trapezoid solid
    /// @param id          Name of the solid
    /// @param x1          Length along x of the side at y = -y1 of the face at -z
    /// @param x2          Length along x of the side at y = +y1 of the face at -z
    /// @param y1          Length along y at the surface positioned at -z
    /// @param alpha1      Angle with respect to the y axis from the centre
    ///                    of the side at y =- y1 to the centre at y = +y1
    ///                    of the face at -z
    /// @param x3          Length along x of the side at y = -y2 of the face at +z
    /// @param x4          Length along x of the side at y = +y2 of the face at +z
    /// @param y2          Length along y at the surface positioned at +z
    /// @param alpha2      Angle with respect to the y axis from the centre of the 
    ///                    side at y = -y2 to the centre at y = +y2
    ///                    of the face at +z
    /// @param z           Dimension along Z axis
    /// @param theta       Polar angle of the line joining the centres of
    ///                    the faces at -z and +z in z
    /// @param phi         Azimuthal angle of the line joining the centres
    ///                    of the faces at -z and +z in z
    /// @param lunit       Length unit, default [mm]
    /// @param aunit       Angle unit, default [radian]
    /// @throws std::logic_error Exception if the box with the same id
    ///                          already exists in the document
    void addTrap( const std::string& id,
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
                  const std::string& lunit="mm",
                  const std::string& aunit="radian" );

      // Add elitical tube
      /// @param dx          x size
      /// @param dy          y size
      /// @param dz          z size

      void addElTube( const std::string& id,              
                                    double dx, double dy, double dz,
                                    const std::string& lunit="mm");
      
      // Add polyhedra
      void addPolyhedra( const std::string& id,
                         int numberofz,
                         double startphi, 
                         double totalphi,
                         int numsides,
                         double* z,
                         std::vector<double>& rmin,   
                         std::vector<double>& rmax,   
                         const std::string& lunit="mm",
                         const std::string& aunit="radian" );
      
      // Add orb (sphere with min radius equal 0 and full angles
      // @param r radius
      void addOrb(const std::string& id,
                  double r,
                  const std::string& lunit );      
      
      // Add hype
      void addHype( const std::string& id,
                    double rmin, double rmax, 
                    double inst, double outst, 
                    double z,
                    const std::string& lunit="mm",
                    const std::string& aunit="radian" );
      
      // Add torus
      // @param rmin inner radius
      // @param rmax outer radius
      // @param rtor radius of the torus
      // @param startphi begining of phi angle 
      // @param deltaphi phi angle
      void addTorus( const std::string& id,
                     double rmin, double rmax, double rtor,
                     double startphi, double deltaphi,
                     const std::string& lunit="mm",
                     const std::string& aunit="radian" );

      // Add reflected solid

      void addReflected(const std::string& id,
                        const std::string& solid,
                        double xx, double yy, double zz,
                        double rx, double ry, double rz,
                        double dx, double dy, double dz,
                        const std::string& lunit="mm",
                        const std::string& aunit="radian" );

    /// Add GDML boolean solid using references only.
    /// The position and rotation references can be empty which results into
    /// centered identity boolean operation, for example a little sphere is removed from
    /// a center of a bigger box if subtraction boolean solid is created using sphere and box.
    /// @param id          Name of the boolean solid
    /// @param type        Boolean solid operation type one of: union, subtraction, intersection
    /// @param first       IDREF of the reference solid, first constituent
    /// @param second      IDREF of the second boolean operation constituent
    /// @param positionRef IDREF of a position already defined somewhere in the define section
    /// @param rotationRef IDREF of a rotation already defined somewhere in the define section
    /// @throws std::logic_error Exception if the solid with the same id
    ///                          already exists in the document
    /// @throws std::logic_error Exception if the boolean solid type is not valid
    void addBoolean( const std::string& id,
                     const std::string& type,
                     const std::string& first,
                     const std::string& second,
                     const std::string& positionRef="",
                     const std::string& rotationRef="" );
    /// Add GDML boolean solid and define position and rotation inlined.
    /// If position and rotation values are left as defaults they result into center or identity
    /// transaltion or rotation.
    /// @param id          Name of the boolean solid
    /// @param type        Boolean solid operation type one of: union, subtraction, intersection
    /// @param first       IDREF of the reference solid, first constituent
    /// @param second      IDREF of the second boolean operation constituent
    /// @param x           Translation along X axis
    /// @param y           Translation along Y axis
    /// @param z           Translation along Z axis
    /// @param rx          Rotation around X axis
    /// @param ry          Rotation around Y axis
    /// @param rz          Rotation around Z axis
    /// @throws std::logic_error Exception if the solid with the same id
    ///                          already exists in the document
    /// @throws std::logic_error Exception if the boolean solid type is not valid
    void addBoolean( const std::string& id,
                     const std::string& type,
                     const std::string& first,
                     const std::string& second,
                     double             x1=0.0,
                     double             y1=0.0,
                     double             z1=0.0,
                     double             rx1=0.0,
                     double             ry1=0.0,
                     double             rz1=0.0,
                     double             x0=0.0,
                     double             y0=0.0,
                     double             z0=0.0,
                     double             rx0=0.0,
                     double             ry0=0.0,
                     double             rz0=0.0 );

    void addXtru(const std::string& id,
                 const std::string& lunit,
                 int numVertex,
                 double* vertex,
                 int numSection,
                 double* section);
  };
}
}

#endif // GDML_WRITER_SOLIDSCURSOR_H
