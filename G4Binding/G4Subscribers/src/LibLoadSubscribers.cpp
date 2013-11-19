#include "Saxana/SAXComponentFactory.h"

void GDMLSubscriberLibLoad() {
    LOAD_COMPONENT(defineSubscriber)
    LOAD_COMPONENT(isotopeSubscriber)
    LOAD_COMPONENT(elementSubscriber)
    LOAD_COMPONENT(materialSubscriber)
    LOAD_COMPONENT(unionSubscriber)
    LOAD_COMPONENT(subtractionSubscriber)
    LOAD_COMPONENT(intersectionSubscriber)
    LOAD_COMPONENT(reflectedSolidSubscriber)
    LOAD_COMPONENT(boxSubscriber)
    LOAD_COMPONENT(sphereSubscriber)
    LOAD_COMPONENT(tubeSubscriber)
    LOAD_COMPONENT(paraSubscriber)
    LOAD_COMPONENT(coneSubscriber)
    LOAD_COMPONENT(polyconeSubscriber)
    LOAD_COMPONENT(trdSubscriber)
    LOAD_COMPONENT(trapSubscriber)
    LOAD_COMPONENT(torusSubscriber)
    LOAD_COMPONENT(orbSubscriber)
    LOAD_COMPONENT(hypeSubscriber)
    LOAD_COMPONENT(eltubeSubscriber)
    LOAD_COMPONENT(polyhedraSubscriber)
    LOAD_COMPONENT(volumeSubscriber)
    LOAD_COMPONENT(assemblySubscriber)
    LOAD_COMPONENT(setupSubscriber)
    LOAD_COMPONENT(opticalsurfaceSubscriber)
    LOAD_COMPONENT(skinsurfaceSubscriber)
    LOAD_COMPONENT(bordersurfaceSubscriber)
    LOAD_COMPONENT(loopSubscriber)

// Following subscribers are only enabled if the Geant4 version supports them.

#ifdef HAVE_G4EXTRUDEDSOLID
    LOAD_COMPONENT(xtruSubscriber)    
#endif

#ifdef HAVE_G4ELLIPSOID
    LOAD_COMPONENT(ellipsoidSubscriber)
#endif

#ifdef HAVE_G4TESSELLATEDSOLID
    LOAD_COMPONENT(tessellatedSubscriber)
#endif

#ifdef HAVE_G4TET
    LOAD_COMPONENT(tetSubscriber)
#endif

#ifdef HAVE_G4TWISTEDBOX
    LOAD_COMPONENT(twistedboxSubscriber)
#endif

#ifdef HAVE_G4TWISTEDTUBS
    LOAD_COMPONENT(twistedtubsSubscriber)
#endif

#ifdef HAVE_G4TWISTEDTRAP
    LOAD_COMPONENT(twistedtrapSubscriber)
#endif

#ifdef HAVE_G4TWISTEDTRD
    LOAD_COMPONENT(twistedtrdSubscriber)
#endif
}
