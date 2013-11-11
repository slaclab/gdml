#!/bin/sh

#
# CERN example.
#
# -- Witek Pokorski 
#

export LCGEXT=/afs/cern.ch/sw/lcg/external

# set the platform
if [ ! $PLATFORM ]; then
    export PLATFORM=slc4_ia32_gcc34
fi


# rebuild configure from current configure.in (optional)
./ac.sh

# run configure with options
./configure --with-platform=${PLATFORM} \
	    --with-xercesc=${LCGEXT}/XercesC/2.7.0/${PLATFORM} \
            --with-clhep=${LCGEXT}/clhep/2.0.3.1/${PLATFORM} \
            --with-geant4=${LCGEXT}/geant4/9.0/${PLATFORM} \
            --with-geant4-include=${LCGEXT}/geant4/9.0/share/include \
            --with-geant4-libdir=${LCGEXT}/geant4/9.0/${PLATFORM}/lib \
            --enable-shared=yes \
	    --enable-static=no \
	    --enable-granular=yes \
 	    --enable-gdml-verbose=no \
	    --enable-compile-verbose=no 

# print results
echo
echo
echo "****************** Local Settings from Autoconf ******************"
cat ./config/make/local_settings.gmk
