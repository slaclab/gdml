// -*- C++ -*-
// $Id: StructureCursor.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_STRUCTURECURSOR_H
#define GDML_WRITER_STRUCTURECURSOR_H 1

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
     * @class StructureCursor StructureCursor.h Writer/StructureCursor.h
     * The cursor allowing to insert GDML definitions of volumes into the Document object.
     * In addition to adding theem it registers them with the registry associated with
     * the current document.
     *
     * @author Radovan Chytracek, CERN IT/DB, LCG AA
     * @date 18/06/2004
     */
    class StructureCursor : public Cursor
    {
    public:
      /// Constructor
      /// @param solidsElement The GDML materials tag reference in the document
      /// @param edReg         The document registry of unique IDs
      StructureCursor( Element& solidsElement, EditableDocumentRegistry& edReg );

      /// Find a volume in the current document, the returned volume can be either
      /// an ordinary volume or assembly volume, what matters is the right name.
      /// @param id          The volume name
      /// @throws std::logic_error Exception if volume by the ID does not exist in the
      ///                          document
      Element& findVolume( const std::string& id );
        
      /// Add GDML empty volume
      /// Returns reference to the just added volume. This reference is valid
      /// until another volume is added.
      /// @param id          The volume name
      /// @param materialRef The material IDREF reference
      /// @param solidRef    The solid IDREF reference
      /// @throws std::logic_error Exception if volume by the ID already exists in the
      ///                          document
      /// @throws std::logic_error Exception if either material or solid can't be found
      ///                          in the current document
      Element& addVolume( const std::string& id,
                          const std::string& materialRef,
                          const std::string& solidRef );
      /// Add GDML empty assembly volume.
      /// Returns reference to the just added assembly volume. This reference is valid
      /// until another volume is added.
      /// BEWARE! An empty assembly volume make no sense so the result of reading it back
      /// by GDML reader is not defined!
      /// One should always add at least one child volume into an assembly.
      /// @param id          The assembly volume name
      /// @throws std::logic_error Exception if volume by the ID already exists in the
      ///                          document
      Element& addAssembly( const std::string& id );
      /// Add a child with name volumeRef into a mother volume with name motherVolumeRef.
      /// The names must be different otherwise an exception is thrown. The mother volume
      /// can be either an ordinary volume or assembly volume.
      /// @param motherVolumeRef The IDREF of the mother volume
      /// @param volumeRef       The IDREF of the volume to become a child volume
      /// @param positionRef     The IDREF of the position definition
      /// @param rotationRef     The IDREF of the rotation definition
      /// @throws std::logic_error Exception if motherVolumeRef or volumeRef does not exist in the
      ///                          document
      /// @throws std::logic_error Exception if either of the position or rotation can't be found
      /// @throws std::logic_error Exception if the both volume references are the same
      void addChild( const std::string& motherVolumeRef,
                     const std::string& volumeRef,
                     const std::string& positionRef,
                     const std::string& rotationRef,
		     const std::string& scaleRef );
      /// Add a child defined in a external module (GDML file) into a mother volume with name 
      /// motherVolumeRef. The mother volume can ONLY be either an ordinary volume.
      /// @param motherVolumeRef The IDREF of the mother volume
      /// @param file            The filename where the definition of the child volume is
      /// @param positionRef     The IDREF of the position definition
      /// @param rotationRef     The IDREF of the rotation definition
      /// @throws std::logic_error Exception if motherVolumeRef does not exist in the document
      /// @throws std::logic_error Exception if either of the position or rotation can't be found
      /// @throws std::logic_error Exception if the both volume references are the same
      void addChildFile( const std::string& motherVolumeRef,
                         const std::string& file,
                         const std::string& positionRef,
                         const std::string& rotationRef,
			 const std::string& scaleRef );
      /// Add a child with name volumeRef into a mother volume with name motherVolumeRef.
      /// The names must be different otherwise an exception is thrown.
      /// This method creates children volumes with inlined position and rotation defintions.
      /// @param motherVolumeRef The IDREF of the mother volume
      /// @param volumeRef       The IDREF of the volume to become a child volume
      /// @param x               The position along X dimension
      /// @param y               The position along Y dimension
      /// @param z               The position along Z dimension
      /// @param rx              The rotation around X axis
      /// @param ry              The rotation around Y axis
      /// @param rz              The rotation around Z axis
      /// @throws std::logic_error Exception if motherVolumeRef or volumeRef does not exist in the
      ///                          document
      /// @throws std::logic_error Exception if either of the position or rotation can't be found
      /// @throws std::logic_error Exception if the both volume references are the same
      void addChild( const std::string& motherVolumeRef,
                     const std::string& volumeRef,
                     double             x=0.0,
                     double             y=0.0,
                     double             z=0.0,
                     double             rx=0.0,
                     double             ry=0.0,
                     double             rz=0.0 );
      /// Add a child with name volumeRef into the motherVolume Element.
      /// The mother voluem can be obtained by calling findVolume() method.
      /// @param motherVolume    The mother volume Element reference
      /// @param volumeRef       The IDREF of the volume to become a child volume
      /// @param positionRef     The IDREF of the position definition
      /// @param rotationRef     The IDREF of the rotation definition
      /// @throws std::logic_error Exception if volumeRef does not exist in the document
      /// @throws std::logic_error Exception if either of the position or rotation can't be found
      void addChild( Element&           motherVolume,
                     const std::string& volumeRef,
                     const std::string& positionRef,
                     const std::string& rotationRef,
		     const std::string& scaleRef );
      /// Add a child with name volumeRef into the motherVolume Element.
      /// The mother voluem can be obtained by calling findVolume() method.
      /// @param motherVolume    The mother volume Element reference
      /// @param volumeRef       The IDREF of the volume to become a child volume
      /// @param x               The position along X dimension
      /// @param y               The position along Y dimension
      /// @param z               The position along Z dimension
      /// @param rx              The rotation around X axis
      /// @param ry              The rotation around Y axis
      /// @param rz              The rotation around Z axis
      /// @throws std::logic_error Exception if volumeRef does not exist in the document
      /// @throws std::logic_error Exception if either of the position or rotation can't be found
      void addChild( Element&           motherVolume,
                     const std::string& volumeRef,
                     double             x=0.0,
                     double             y=0.0,
                     double             z=0.0,
                     double             rx=0.0,
                     double             ry=0.0,
                     double             rz=0.0 );

      /// Add a replica with name volumeRef into the motherVolume Element.
      /// The mother volume can be obtained by calling findVolume() method.
      /// @param motherVolume    The mother volume Element reference
      /// @param volumeRef       The IDREF of the volume to become a child volume
      /// @param ncopies         The number of copies
      /// @param axis            Axis of replication (x:1, y:2, z:3)
      /// @param width           Width of slices
      /// @param offset          Offset of slices
      /// @throws std::logic_error Exception if volumeRef does not exist in the document
      Element& addReplica(const std::string& motherVolume,
                          const std::string& volumeRef,
                          int ncopies, int axis, 
                          double width, double offset);

      //Add a division with name volumeRef into the motherVolume Element.
      /// The mother volume can be obtained by calling findVolume() method.
      /// @param motherVolume    The mother volume Element reference
      /// @param volumeRef       The IDREF of the volume to become a child volume
      /// @param ncopies         The number of copies
      /// @param axis            Axis of replication (x:1, y:2, z:3)
      /// @param width           Width of slices
      /// @param offset          Offset of slices
      /// @throws std::logic_error Exception if volumeRef does not exist in the document
      Element& addDivision(const std::string& motherVolume,
                           const std::string& volumeRef,
                           int ncopies, int axis, 
                           double width, double offset,
                           const std::string& unit);

      /// Add a parameterised with name volumeRef into the motherVolume Element.
      /// The mother volume can be obtained by calling findVolume() method.
      /// @param motherVolume    The mother volume Element reference
      /// @param volumeRef       The IDREF of the volume to become a child volume
      /// @param ncopies         The number of copies
      /// @throws std::logic_error Exception if volumeRef does not exist in the document
      Element& addParameterised(const std::string& motherVolume,
                                const std::string& volumeRef,
                                int ncopies);

      /// Add the parameterisation data for volume with name volumeRef.
      /// @param pVolume    The parameterised volume
      /// @param ncopy      The copy number
      /// @param x          The x coordinate
      /// @param y          The y coordinate
      /// @param z          The z coordinate
      /// @param phi        The phi rotation angle
      /// @param theta      The theta rotation angle
      /// @param psi        The psi rotation angle
      void addBoxParameterisation( const std::string& vol,
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
                                   double hz);

      /// Add the parameterisation data for volume with name volumeRef.
      /// @param pVolume    The parameterised volume
      /// @param ncopy      The copy number
      /// @param x          The x coordinate
      /// @param y          The y coordinate
      /// @param z          The z coordinate
      /// @param phi        The phi rotation angle
      /// @param theta      The theta rotation angle
      /// @param psi        The psi rotation angle
      void addTubeParameterisation( const std::string& vol,
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
                                    double DeltaPhi);

    private:
      Element buildChild( const std::string& idRef,
                          const std::string& positionRef,
                          const std::string& rotationRef,
                          const std::string& scaleRef,
                          const std::string& uniqueHint="" );
      Element buildChildFile( const std::string& file,
                              const std::string& positionRef,
                              const std::string& rotationRef,
                              const std::string& scaleRef,
                              const std::string& uniqueHint="" );
      Element buildChild( const std::string& idRef,
                          double             x=0.0,
                          double             y=0.0,
                          double             z=0.0,
                          double             rx=0.0,
                          double             ry=0.0,
                          double             rz=0.0,
                          const std::string& uniqueHint="" );

      void buildParameters(const std::string& vol,
                           Element& pars,
                           int ncopy,
                           double x,
                           double y,
                           double z,
                           double rx,
                           double ry,
                           double rz);
    };
  }
}

#endif // GDML_WRITER_STRUCTURECURSOR_H
