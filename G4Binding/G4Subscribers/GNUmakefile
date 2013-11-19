# -*-Makefile-*-
# G4Subscribers

# Define external dependencies
#REQUIRE_CLHEP  := any
REQUIRE_GEANT4  := any

# Define package dependencies inside project
# Make sure that the required packages get built before
# and no circular requirement is written here
REQUIRED_PACKAGES := Common/Saxana G4Binding/G4Evaluator G4Binding/G4Processor

PROJECT_INCLUDES  += -I$(PROJECT_TOP)/Common/Schema

all: $(PACKAGE_NAME)_target

# Build this package
include $(PROJECT_TOP)/config/make/package.gmk

