#
# CMake configuration for GDML package.
#
# FIXME: Currently does not build the examples.
#
# @author Jeremy McCormick <jeremym@slac.stanford.edu>
#

# minimum cmake version
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# project name
PROJECT( GDML )

# project version
SET( GDML_VERSION_MAJOR 3 )
SET( GDML_VERSION_MINOR 1 )
SET( GDML_VERSION_PATCH 1 )

# find ilcutil
FIND_PACKAGE( ILCUTIL COMPONENTS ILCSOFT_CMAKE_MODULES REQUIRED )

# load default settings from ILCSOFT_CMAKE_MODULES
INCLUDE( ilcsoft_default_settings )
INCLUDE( ExternalProject )

# add path containing CMake macros for this project
LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

# macro for generating configuration output
INCLUDE( MacroGeneratePackageConfigFiles )

# find Xerces C++
FIND_PACKAGE( XERCES REQUIRED )
IF( NOT XERCES_FOUND )
	MESSAGE( FATAL_ERROR "Xerces was not found!  Define XERCES_DIR when calling cmake." )
ENDIF()

# find Geant4
FIND_PACKAGE( Geant4 REQUIRED )
if ( NOT Geant4_FOUND )
    MESSAGE( FATAL_ERROR "Geant4 was not found!  Define Geant4_DIR when calling cmake." )
ELSE()
    MESSAGE( STATUS "Found Geant4: ${Geant4_DIR}" )
ENDIF()

# make a list of source directories
SET( library_source_dirs 
	${PROJECT_SOURCE_DIR}/Common/Processes 
	${PROJECT_SOURCE_DIR}/Common/Saxana 
	${PROJECT_SOURCE_DIR}/Common/Schema 
	${PROJECT_SOURCE_DIR}/Common/Writer 
	${PROJECT_SOURCE_DIR}/G4Binding/G4Evaluator 
	${PROJECT_SOURCE_DIR}/G4Binding/G4Processor 
	${PROJECT_SOURCE_DIR}/G4Binding/G4Subscribers 
	${PROJECT_SOURCE_DIR}/G4Binding/G4Writer
)

# macro for collating sources
macro(GDML_COLLATE_APPLICATION_SOURCES source_dest_var source_dir )
    FILE( GLOB_RECURSE local_source ${source_dir}/src/*.cpp )
    LIST( APPEND ${source_dest_var} ${local_source} )
    INCLUDE_DIRECTORIES( ${source_dir} )    
endmacro()

# add application sources and include directories
FOREACH( src ${library_source_dirs} )
    GDML_COLLATE_APPLICATION_SOURCES( library_sources ${src} )
ENDFOREACH()
    
# default compilation flags
ADD_DEFINITIONS( "-Wall -ansi -pedantic" )
ADD_DEFINITIONS( "-Wno-long-long" )

# additional compilation flags
ADD_DEFINITIONS( ${Geant4_DEFINITIONS} )

# include directories
INCLUDE_DIRECTORIES( ${XERCES_INCLUDE_DIR} ${Geant4_INCLUDE_DIRS} )

# libraries
LINK_LIBRARIES( ${XERCES_LIBRARY} ${Geant4_LIBRARIES} )

# output shared library
ADD_LIBRARY( gdml SHARED ${library_sources} )

# install library
SET( GDML_LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib )
INSTALL( TARGETS gdml DESTINATION ${GDML_LIB_INSTALL_DIR} )

# generate package configuration
GENERATE_PACKAGE_CONFIGURATION_FILES( GDMLConfig.cmake GDMLConfigVersion.cmake GDMLLibDeps.cmake )
