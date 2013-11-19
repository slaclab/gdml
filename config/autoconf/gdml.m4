dnl
dnl GDML m4 macros
dnl

# Macro that calls all the GDML setup macros in the correct sequence.
AC_DEFUN(GDML_SETUP_GDML, [

GDML_CHECK_OS

GDML_CHECK_COMPILER

GDML_ENABLE_COMPILE_VERBOSE

GDML_WITH_PLATFORM

GDML_ENABLE_SHARED
GDML_ENABLE_STATIC
GDML_ENABLE_SINGLE
GDML_ENABLE_GRANULAR

GDML_WITH_LIBNAME_PREFIX

GDML_SETUP_INSTALL_DIRS

GDML_ENABLE_GDML_VERBOSE

GDML_ENABLE_BUILD_STEPWRT

GDML_ENABLE_FLAT_INCLUDE

GDML_ENABLE_EXAMPLES

])

# Macro to check whether to use shared libraries.
AC_DEFUN(GDML_ENABLE_SHARED, [

AC_MSG_CHECKING(whether to use shared libraries)

AC_ARG_ENABLE([shared],
              AC_HELP_STRING([--enable-shared],
                             [Enable or disable building of shared libraries. (Default is enable.)])
             )

if test "$enable_shared" != "no"; then
  GDML_USE_SHARED_LIB=1
  AC_MSG_RESULT(yes)
else  
  AC_MSG_RESULT(no)
fi

AC_SUBST(GDML_USE_SHARED_LIB)

])

# Macro to check whether to use static libs.
AC_DEFUN(GDML_ENABLE_STATIC, [

AC_MSG_CHECKING(whether to use static libraries)

AC_ARG_ENABLE([static],
              AC_HELP_STRING([--enable-static],
                             [Enable or disable building of static libraries. (Default is enable.)])
             )

if test "$enable_static" != "no"; then
  GDML_USE_STATIC_LIB=1
  AC_MSG_RESULT(yes)
else  
  AC_MSG_RESULT(no)
fi

AC_SUBST(GDML_USE_STATIC_LIB)

])

# Macro to check whether to use granular libs.
AC_DEFUN(GDML_ENABLE_GRANULAR, [

AC_MSG_CHECKING(whether to use granular libraries)

AC_ARG_ENABLE([granular],
              AC_HELP_STRING([--enable-granular],
                             [Enable or disable usage of granular libraries. (Default is disable.)])
             )

if test "$enable_granular" == "yes"; then
  GDML_USE_GRANULAR_LIB=1
  AC_MSG_RESULT(yes)
else  
  AC_MSG_RESULT(no)
fi

AC_SUBST(GDML_USE_GRANULAR_LIB)

])

# Macro to check whether to use single libs.
AC_DEFUN(GDML_ENABLE_SINGLE, [

AC_MSG_CHECKING(whether to use single GDML library)

AC_ARG_ENABLE([single],
              AC_HELP_STRING([--enable-single],
                             [Enable or disable usage of single libraries. (Default is enable.)])
             )

if test "$enable_single" != "no"; then
  GDML_USE_SINGLE_LIB=1
  AC_MSG_RESULT(yes)
else  
  AC_MSG_RESULT(no)
fi

AC_SUBST(GDML_USE_SINGLE_LIB)

])

# Macro to set lib name prefix.
AC_DEFUN(GDML_WITH_LIBNAME_PREFIX, [

AC_MSG_CHECKING(for libname prefix)

AC_ARG_WITH(libname-prefix,
	AC_HELP_STRING([--with-libname-prefix=<prefix>], [prefix target libs with a string identifier, e.g. 'lcg_']),
	[TARGET_LIB_PREFIX=$with_libname_prefix],
	[TARGET_LIB_PREFIX=])

if test "${with_libname_prefix}" = "no"; then
  TARGET_LIB_PREFIX=
fi

if test -n "${TARGET_LIB_PREFIX}"; then
  AC_MSG_RESULT($TARGET_LIB_PREFIX)
else
  AC_MSG_RESULT(none)
fi

AC_SUBST(TARGET_LIB_PREFIX)

])

# Macro to check the OS and set host_os var.
AC_DEFUN(GDML_CHECK_OS, [

AC_MSG_CHECKING(for supported OS)

# to lowercase
host_os=`uname | tr [[:upper:]] [[:lower:]]`

# default to okay
supported_os=yes

# set platform var
case "$host_os" in
linux*  ) host_os="Linux";;
cygwin* ) host_os="WIN32";;
darwin* ) host_os="Darwin";;
*       ) supported_os=no;;
esac

AC_MSG_RESULT([$supported_os])

if test "$supported_os" = "no"; then
  AC_MSG_ERROR( [$host_os is not in the list of supported operating systems] )
fi

])

# Macro to check the compiler.
AC_DEFUN(GDML_CHECK_COMPILER, [

AC_MSG_CHECKING(the compiler setting)

if test -n $CXX; then
  host_compiler=$CXX
# Don't know why this would happen, but we will default to g++ if CXX is not set.
else
  host_compiler=g++
fi

COMPILER=$host_compiler

AC_MSG_RESULT([$COMPILER])

AC_MSG_CHECKING([for the compiler gmk file])

COMPILER_GMK_FILE=${make_compiler_dir}/${COMPILER}.gmk

if ! test -e $COMPILER_GMK_FILE; then
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([$COMPILER_GMK_FILE does not exist for compiler $COMPILER])
else
  AC_MSG_RESULT($COMPILER_GMK_FILE)
fi

AC_SUBST(COMPILER)
AC_SUBST(COMPILER_GMK_FILE)

])

# Macro to set whether compile should be verbose.
AC_DEFUN( GDML_ENABLE_COMPILE_VERBOSE, [

AC_SUBST(COMPILE_VERBOSE_USE)

AC_MSG_CHECKING(whether to compile and link in verbose mode)

AC_ARG_ENABLE([compile-verbose],
	AC_HELP_STRING([--enable-compile-verbose=<setting>], [set compile verbose to on or off]),
	[COMPILE_VERBOSE_USE=$enable_compile_verbose],
	[COMPILE_VERBOSE_USE=no])

AC_MSG_RESULT($COMPILE_VERBOSE_USE)

if test "${COMPILE_VERBOSE_USE}" != yes && test "${COMPILE_VERBOSE_USE}" != no; then
  AC_MSG_ERROR([$COMPILE_VERBOSE_USE is not a valid setting for --enable-compile-verbose])
fi

if test "${COMPILE_VERBOSE_USE}" = yes; then
  CXXFLAGS="${CXXFLAGS} -v -Wl,--verbose"
fi

])

# Macro to set whether to build STEPWriter.
AC_DEFUN(GDML_ENABLE_BUILD_STEPWRT, [

AC_MSG_CHECKING(whether to build STEPWriter)

AC_ARG_ENABLE(build-stepwrt,
	AC_HELP_STRING([--enable-build-stepwrt=<setting>], [set building of STEPWriter to on or off]),
	[BUILD_STEPWRT=$enable_build_stepwrt],
	[BUILD_STEPWRT=no])

if test "$BUILD_STEPWRT" != yes && test "$BUILD_STEPWRT" != no; then
  AC_MSG_ERROR([$BUILD_STEPWRT is not a valid setting for --enable-build-stepwrt])
fi

AC_MSG_RESULT($BUILD_STEPWRT)
AC_SUBST(BUILD_STEPWRT)

])

# Macro to set whether to build flat includes.
AC_DEFUN(GDML_ENABLE_FLAT_INCLUDE, [

AC_MSG_CHECKING(whether to copy includes in a flat structure)

AC_ARG_ENABLE(flat-include,
	AC_HELP_STRING([--enable-flat-include=<setting>], [Enable the copying of includes without full original path, yes or no]),
	[FLAT_INCLUDE=$enable_flat_include],
	[FLAT_INCLUDE=no])

if test "$FLAT_INCLUDE" != yes && test "$FLAT_INCLUDE" != no; then
  AC_MSG_ERROR([$FLAT_INCLUDE is not a valid setting for --enable-flat-include])
fi

AC_MSG_RESULT($FLAT_INCLUDE)
AC_SUBST(FLAT_INCLUDE)

])

# Macro for PLATFORM with arg or env var.
AC_DEFUN(GDML_WITH_PLATFORM, [

AC_MSG_CHECKING([for PLATFORM setting])

AC_ARG_WITH([platform],
	AC_HELP_STRING([--with-platform=<platform>],[description of platform, e.g. Linux-g++, Win32-g++, or Darwin-g++]),
	[PLATFORM=${with_platform}],
	[PLATFORM=${host_os}"-"${host_compiler}])

# check for gmk file
AC_MSG_RESULT($PLATFORM)

AC_MSG_CHECKING([for the PLATFORM gmk file])

PLATFORM_GMK_FILE=${make_platform_dir}/${PLATFORM}.gmk

# invalid platform gmk or user failed to create it
if ! test -e $PLATFORM_GMK_FILE; then
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([$PLATFORM_GMK_FILE does not exist for PLATFORM=$PLATFORM])
else
  AC_MSG_RESULT($PLATFORM_GMK_FILE)
fi

# substitute to output
AC_SUBST(PLATFORM)
AC_SUBST(PLATFORM_GMK_FILE)

])

# Macro to initialize some "global" variables.
AC_DEFUN(GDML_INIT, [

# make includes directories
make_inc_dir=config/make
make_platform_dir=${make_inc_dir}/platform
make_compiler_dir=${make_inc_dir}/compiler
make_ext_dir=${make_inc_dir}/ext

])

# Macro to set the build dir.
AC_DEFUN(GDML_WITH_BUILDDIR, [

AC_MSG_CHECKING(for build directory)

AC_ARG_WITH([build-dir],
	AC_HELP_STRING([--with-build-dir=<path>],[target directory for base build]),
	[TARGET_BUILD_DIR=$with_build_dir],
	[TARGET_BUILD_DIR=${srcdir}/build/${PLATFORM}])

AC_SUBST(TARGET_BUILD_DIR)

])

# Macro to set the installation dirs.
AC_DEFUN(GDML_SETUP_INSTALL_DIRS, [

AC_MSG_CHECKING(for prefix)

if test "${prefix}" = "NONE"; then
  prefix=/usr/local
fi

exec_prefix=${prefix}

AC_MSG_RESULT($prefix)

AC_SUBST(prefix)
AC_SUBST(exec_prefix)
AC_SUBST(libdir)
AC_SUBST(includedir)

])

# Macro to enable/disable info messages from GDML.
AC_DEFUN(GDML_ENABLE_GDML_VERBOSE, [

AC_MSG_CHECKING(whether to enable GDML diagnostic output)

AC_ARG_ENABLE([gdml-verbose],
	AC_HELP_STRING([--enable-gdml-verbose=<setting>], [Turn GDML diagnostic output on or off.]),
	[GDML_VERBOSE_USE=$enable_gdml_verbose],
	[GDML_VERBOSE_USE=no])

if test "${GDML_VERBOSE_USE}" = "yes"; then
  AC_DEFINE(GDML_VERBOSE)
fi

AC_MSG_RESULT($GDML_VERBOSE_USE)

])

# Macro to enable/disable compilation of examples.  Enabled by default.
AC_DEFUN(GDML_ENABLE_EXAMPLES, [

AC_MSG_CHECKING(whether to compile the examples)

AC_ARG_ENABLE([examples],
    AC_HELP_STRING([--enable-examples=<setting>], [Turn off compilation of examples.]))

if test "$enable_examples" != "no"; then
  AC_MSG_RESULT(yes)
  GDML_BUILD_EXAMPLES=1
else
  AC_MSG_RESULT(no)
fi

AC_SUBST(GDML_BUILD_EXAMPLES)

])
