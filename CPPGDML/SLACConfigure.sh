#!/bin/sh

#
# Example site-specific usage of the configure script
# for SLAC Linux on noric, iris, and yakut machines. 
#
# --Jeremy McCormick, SLAC/ILC 
#

# rebuild configure from current configure.in (optional)
./ac.sh

# run configure with site options
./configure --with-xercesc=$PRJ_EXTERN/xerces-c/v2-6-0 \
            --with-clhep=$PRJ_EXTERN/clhep/v1-9-1-2 \
            --with-geant4=$PRJ_EXTERN/geant4/geant4.7.1.p01 \
            --enable-shared=no \
	    --enable-static=yes \
            --enable-geant4-vis=no \
            --enable-geant4-ui=no \
	    --enable-geant4-granular-libs=yes \
 	    --enable-gdml-verbose=yes 
#\
#	    --enable-compile-verbose=yes 

# print results
#echo
#echo
#echo "****************** Local Settings from Autoconf ******************"
#cat ./config/make/local_settings.gmk
#echo
#cat ./config/make/geant4_settings.gmk
