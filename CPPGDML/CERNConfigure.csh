#!/bin/csh

#
# CERN example.
#
# -- Witek Pokorski 
#

setenv LCGEXT /afs/cern.ch/sw/lcg/external

# set the platform
if !(${?PLATFORM}) then
    setenv PLATFORM slc4_ia32_gcc34
endif


# rebuild configure from current configure.in (optional)
./ac.sh

# run configure with options
./configure --with-platform=${PLATFORM} \
	    --with-xercesc=${LCGEXT}/XercesC/2.7.0/${PLATFORM} \
            --with-clhep=${LCGEXT}/clhep/2.0.3.1/${PLATFORM} \
            --with-geant4=${LCGEXT}/geant4/9.1/share \
            --with-geant4-include=${LCGEXT}/geant4/9.1/share/include \
            --with-geant4-libdir=${LCGEXT}/geant4/9.1/${PLATFORM}/lib \
            --enable-shared=no \
	    --enable-static=yes \
	    --enable-granular=yes \
            --enable-gdml-verbose=no \
	    --enable-compile-verbose=no 

# print results
echo
echo
echo "****************** Local Settings from Autoconf ******************"
cat ./config/make/local_settings.gmk
