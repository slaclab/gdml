#
# CMake configuration for GDML package.
#
# FIXME: Currently does not build the examples.
#
# @author Jeremy McCormick <jeremym@slac.stanford.edu>
#

# minimum cmake version
CMAKE_MINIMUM_REQUIRED( VERSION 3.5 )

# project name
PROJECT( GDML )

# project version
SET( GDML_VERSION_MAJOR 4 )
SET( GDML_VERSION_MINOR 0 )
SET( GDML_VERSION_PATCH 0 )

# require CXX-11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add path containing CMake macros for this project
LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

# find Xerces C++
FIND_PACKAGE( XercesC REQUIRED )
IF( NOT XercesC_FOUND )
	MESSAGE( FATAL_ERROR "XercesC was not found!  Define XercesC_INCLUDE_DIR and XercesC_LIBRARY when calling cmake." )
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
MACRO( GDML_COLLATE_APPLICATION_SOURCES source_dest_var source_dir )
    FILE( GLOB_RECURSE local_source ${source_dir}/src/*.cpp )
    LIST( APPEND ${source_dest_var} ${local_source} )
    INCLUDE_DIRECTORIES( ${source_dir} )    
ENDMACRO()

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
INCLUDE_DIRECTORIES( ${XercesC_INCLUDE_DIR} ${Geant4_INCLUDE_DIRS} )

# libraries
LINK_LIBRARIES( ${XercesC_LIBRARY} ${Geant4_LIBRARIES} )

# output shared library
ADD_LIBRARY( gdml SHARED ${library_sources} )

# install library
SET( GDML_LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib )
INSTALL( TARGETS gdml DESTINATION ${GDML_LIB_INSTALL_DIR} )

# install header files
FOREACH( src_dir ${library_source_dirs} )
    GET_FILENAME_COMPONENT( base_src_dir ${src_dir} NAME )
    FILE( GLOB header_files ${src_dir}/${base_src_dir}/*.h )
    FOREACH( header_file ${header_files} )
        GET_FILENAME_COMPONENT( header_file_name ${header_file} NAME )
        INSTALL( FILES ${src_dir}/${base_src_dir}/${header_file_name} DESTINATION include/${base_src_dir} )
    ENDFOREACH()
ENDFOREACH()
