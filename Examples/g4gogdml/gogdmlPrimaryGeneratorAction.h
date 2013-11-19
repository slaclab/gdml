//
#ifndef gogdmlPrimaryGeneratorAction_h
#define gogdmlPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;

class gogdmlPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    gogdmlPrimaryGeneratorAction();
    ~gogdmlPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* particleGun;
};

#endif


