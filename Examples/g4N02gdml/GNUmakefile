# -*-Makefile-*-

# Define external dependencies
REQUIRE_XERCESC  := any
#REQUIRE_CLHEP    := any
REQUIRE_GEANT4   := any

# Define package dependencies inside project
# Make sure that the required packages get built before
# and no circular requirement is written here
REQUIRED_PACKAGES := Common/Saxana Common/Processes Common/Writer \
                     G4Binding/G4Evaluator G4Binding/G4Processor G4Binding/G4Subscribers G4Binding/G4Writer

PROJECT_INCLUDES  += -I$(PROJECT_TOP)/Common/Schema

all: $(APP_NAME)_target

# Build this package
include $(PROJECT_TOP)/config/make/application.gmk

