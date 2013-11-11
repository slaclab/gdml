# -*-Makefile-*-
# $Id: GNUmakefile,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#
# /\/\/\/\ C++ GDML Build System /\/\/\/\
#
#
# Original system by Radovan Chytracek with Autoconf support by Jeremy McCormick.
#
# We loop over the directories and build in each separately.
#

# Include default definition for PROJECT_TOP and derived settings.
include $(CURDIR)/config/make/project.gmk

# Include all vars defined by the Autoconf configure script.
include $(PROJECT_CONFIG)/local_settings.gmk

# Define the list of all packages we have
ifeq ($(BUILDSTEP), yes)
GDML_PACKAGES = Common/Saxana Common/Processes Common/Writer G4Binding/G4Evaluator G4Binding/G4Processor G4Binding/G4Subscribers G4Binding/G4Writer STEPBinding/STEPWriter
else
GDML_PACKAGES = Common/Saxana Common/Processes Common/Writer G4Binding/G4Evaluator G4Binding/G4Processor G4Binding/G4Subscribers G4Binding/G4Writer
endif

COMMON_INC = Schema Saxana Writer Processes
G4BIND_INC = G4Processor G4Subscribers G4Writer G4Evaluator

# Function to build a package.
define MakePackage
	@echo
#	@echo "Starting at $(PROJECT_TOP)"
#	@echo "Build area  $(PROJECT_BUILD_AREA)"
	@(cd $(1);make PROJECT_TOP=$(PROJECT_TOP) PLATFORM=$(PLATFORM) SUBSYSTEM=$(subst /,,$(dir $(1))) PACKAGE_NAME=$(notdir $(1)))
	@echo
#
endef

# Define the list of all examples we have
gdml_examples = Examples/g4gogdml Examples/g4N02gdml Examples/SimpleExtension

# Function to build an application.
define MakeApp
	@echo
#	@echo "Starting at $(PROJECT_TOP)"
#	@echo "Build area  $(PROJECT_BUILD_AREA)"
	@(cd $(1);make PROJECT_TOP=$(PROJECT_TOP) PLATFORM=$(PLATFORM) SUBSYSTEM=$(subst /,,$(dir $(1))) APP_NAME=$(notdir $(1)))
	@echo

endef

gdml_build_targets := build_gdml_prolog build_gdml_libs build_gdml_lib

ifdef GDML_BUILD_EXAMPLES
gdml_build_targets := $(gdml_build_targets) build_gdml_examples 
endif

# Build Targets
.PHONY: build_gdml
build_gdml: $(gdml_build_targets)

.PHONY: build_gdml_libs
build_gdml_libs:
	@$(foreach package,$(GDML_PACKAGES),$(call MakePackage,$(package)))

.PHONY: build_gdml_examples
build_gdml_examples:
	@$(foreach example,$(gdml_examples),$(call MakeApp,$(example)))

.PHONY: build_gdml_prolog
build_gdml_prolog:
	@echo
	@echo "Building CPPGDML for $(PLATFORM)"
	@echo "with the following packages:"
	@echo
	@echo $(GDML_PACKAGES)
	@echo

# all object files from package dirs
OBJ = $(foreach package,$(GDML_PACKAGES),$(wildcard $(PROJECT_TOP)/build/$(PLATFORM)/$(package)/*.o))

gdml_lib_target=

ifdef GDML_USE_SHARED_LIB
gdml_lib_target += build_gdml_lib_shared
endif

ifdef GDML_USE_STATIC_LIB
gdml_lib_target += build_gdml_lib_static
endif

# wrapper to lib targets for user selections
build_gdml_lib: $(gdml_lib_target)

# build a single GDML static library
build_gdml_lib_static:
	@echo "Building GDML static library ..."
	@echo GDML_USE_STATIC_LIB=$(GDML_USE_STATIC_LIB)
	ar crvs $(PROJECT_TOP)/build/$(PLATFORM)/lib/$(PLATFORM_LIB_PREFIX)gdml$(PLATFORM_LIB_SUFFIX) $(OBJ)

# build a single GDML shared library
build_gdml_lib_shared:
	@echo "Building GDML shared library ..."
	$(CXX) -o $(PROJECT_TOP)/build/$(PLATFORM)/lib/$(PLATFORM_SHLIB_PREFIX)gdml$(PLATFORM_SHLIB_SUFFIX) $(PLATFORM_SHLIB_FLAGS) $(CXXFLAGS) $(OBJ) $(LDFLAGS)

# Clean Targets
.PHONY: clean cleanall
clean:
	@$(foreach package,$(GDML_PACKAGES),\
	(cd $(package);make -s PROJECT_TOP=$(PROJECT_TOP) PLATFORM=$(PLATFORM) SUBSYSTEM=$(subst /,,$(dir $(package))) PACKAGE_NAME=$(notdir $(package)) $(notdir $(package))_clean);)
	@$(foreach example,$(gdml_examples),\
	(cd $(example);make -s PROJECT_TOP=$(PROJECT_TOP) PLATFORM=$(PLATFORM) SUBSYSTEM=$(subst /,,$(dir $(example))) APP_NAME=$(notdir $(example)) $(notdir $(example))_clean);)


cleanall:
	@$(foreach package,$(GDML_PACKAGES),\
    (cd $(package);make -s PROJECT_TOP=$(PROJECT_TOP) PLATFORM=$(PLATFORM) SUBSYSTEM=$(subst /,,$(dir $(package))) PACKAGE_NAME=$(notdir $(package)) $(notdir $(package))_cleanall);)
	@$(foreach example,$(gdml_examples),\
	(cd $(example);make -s PROJECT_TOP=$(PROJECT_TOP) PLATFORM=$(PLATFORM) SUBSYSTEM=$(subst /,,$(dir $(example))) APP_NAME=$(notdir $(example)) $(notdir $(example))_cleanall);)
	@rm -rf $(PROJECT_BUILD_AREA)/$(PLATFORM)

# Install Targets

# top-level install target
install: install_lib install_bin install_include

# install libraries
install_lib:
	@if [ ! -d $(libdir) ]; then mkdir -p $(libdir); fi
	cp $(PROJECT_BUILD_AREA)/$(PLATFORM)/lib/*lib* $(libdir)

# install binaries
install_bin:
	@if [ ! -d $(bindir) ]; then mkdir -p $(bindir); fi
	cp -vR $(PROJECT_BUILD_AREA)/$(PLATFORM)/bin/* $(bindir)

# install includes
install_headers := $(shell find . -name *.h)

install_include:

ifeq ($(FLATINCLUDE), yes)

	@echo "FLAT INCLUDE COPY SELECTED..."

	test -d "$(includedir)" || mkdir -p $(includedir)

	cd ${PROJECT_TOP} ; \

	for pak in $(COMMON_INC); do \
	  echo $$pak ;\
	  cp -f -r Common/$$pak/$$pak $(includedir) ;\
	done

	cd ${PROJECT_TOP} ; \
	for pak in $(G4BIND_INC);  do \
	  cp -f -r G4Binding/$$pak/$$pak $(includedir) ;\
	done
endif

ifeq ($(FLATINCLUDE), no)
	@echo "NON-FLAT INCLUDE COPY SELECTED..."
	for i in $(install_headers); do \
		i_dir=`dirname $$i`; \
		mkdir -p $(includedir)/$$i_dir; \
		install $$i $(includedir)/$$i_dir; \
	done
endif
