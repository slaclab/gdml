// $Id: GenericPositionSizeParameterisation.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef INCLUDE_GENERICPOSITIONSIZEPARAMETERISATION_H 
#define INCLUDE_GENERICPOSITIONSIZEPARAMETERISATION_H 1

#include "G4VPVParameterisation.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Para.hh"
#include "G4Hype.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"


/** @class GenericPositionSizeParameterisation GenericPositionSizeParameterisation.h 
 *  Processor/GenericPositionSizeParameterisation.h
 *  
 *
 *  @author Witold POKORSKI
 *  @date   2004-08-31
 */

class G4VPhysicalVolume;
class G4Box;

// Dummy declarations to get rid of warnings ...
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;


class GenericPositionSizeParameterisation : public G4VPVParameterisation
{
public: 
  /// Standard constructor
  GenericPositionSizeParameterisation( ){}; 
  GenericPositionSizeParameterisation(int); 
  
  virtual ~GenericPositionSizeParameterisation( ){}; ///< Destructor
  
  void SetTransformation(int, G4RotationMatrix&, G4ThreeVector&);
  void SetDimensions(int, double, double, double, double, double);

  void ComputeTransformation(const G4int, G4VPhysicalVolume*) const;
  void ComputeDimensions(G4Box&, const G4int, const G4VPhysicalVolume*) const;
  void ComputeDimensions (G4Tubs&, const G4int, const G4VPhysicalVolume*) const;
  
private:  // Dummy declarations to get rid of warnings ...
  void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}

private:

  G4RotationMatrix* rotation;
  G4ThreeVector* translation;
  double* d1;
  double* d2;
  double* d3;
  double* d4;
  double* d5;

};
#endif
