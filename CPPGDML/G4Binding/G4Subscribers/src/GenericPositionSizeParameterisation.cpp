#include "G4Subscribers/GenericPositionSizeParameterisation.h"


GenericPositionSizeParameterisation::GenericPositionSizeParameterisation(int n)
{
  rotation = new G4RotationMatrix[n];
  translation = new G4ThreeVector[n];

  d1 = new double[n];
  d2 = new double[n];
  d3 = new double[n];
  d4 = new double[n];
  d5 = new double[n];
}

void GenericPositionSizeParameterisation::SetTransformation(int n, G4RotationMatrix& rot, G4ThreeVector& trans)
{
  rotation[n-1] = rot;
  translation[n-1] = trans;
}

void GenericPositionSizeParameterisation::SetDimensions(int n, double dim1, double dim2, double dim3,
                                            double dim4, double dim5)
{
  d1[n-1] = dim1;
  d2[n-1] = dim2;
  d3[n-1] = dim3;
  d4[n-1] = dim4;
  d5[n-1] = dim5;
}


void GenericPositionSizeParameterisation::ComputeTransformation(int copyNo, G4VPhysicalVolume* physVol) const
{
  physVol->SetTranslation(translation[copyNo]);
  physVol->SetRotation(&(rotation[copyNo]));
}

void GenericPositionSizeParameterisation::ComputeDimensions(G4Box& box,
                                                int copyNo,
                                                const G4VPhysicalVolume*) const
{
  box.SetXHalfLength(d1[copyNo]);
  box.SetYHalfLength(d2[copyNo]);
  box.SetZHalfLength(d3[copyNo]);
}

void GenericPositionSizeParameterisation::ComputeDimensions(G4Tubs& tubs,
                                                int copyNo,
                                                const G4VPhysicalVolume*) const
{
  tubs.SetDeltaPhiAngle(d1[copyNo]);
  tubs.SetInnerRadius(d2[copyNo]);
  tubs.SetOuterRadius(d3[copyNo]);
  tubs.SetStartPhiAngle(d4[copyNo]);
  tubs.SetZHalfLength(d5[copyNo]);
}
