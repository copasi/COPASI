#!/bin/bash

major=`gawk -- '$2 ~ "VERSION_MAJOR" {print $3}' copasi/copasiversion.h`
minor=`gawk -- '$2 ~ "VERSION_MINOR" {print $3}' copasi/copasiversion.h`
build=`gawk -- '$2 ~ "VERSION_BUILD" {print $3}' copasi/copasiversion.h`

license=`gawk -- ' BEGIN {license = "US"} $0 ~ "USE_LICENSE=DE" {license = "DE"} END {print license} ' copasi/Makefile`

test -d copasi-${build}-src && rm -rf copasi-${build}-src

cd copasi
make src_distribution
cd ..

mv copasi_src copasi-${build}-src

cp acinclude.m4 copasi-${build}-src

cp README.Linux copasi-${build}-src
cp README.SunOS copasi-${build}-src
cp README.Win32 copasi-${build}-src
cp README_MAC.rtf copasi-${build}-src

cp COPASI_License_${license}.txt copasi-${build}-src/COPASI_License.txt

cp --parent admin/flex.sh copasi-${build}-src
cp --parent admin/install-sh copasi-${build}-src
cp --parent admin/missing copasi-${build}-src
sed -e 's/_${license}//g' admin/mkbuild.sh \
  > copasi-${build}-src/admin/mkbuild.sh
cp --parent admin/yacc.sh copasi-${build}-src
chmod 755 copasi-${build}-src/admin/*

cp --parent cvs_admin/c++style copasi-${build}-src
chmod 755 copasi-${build}-src/cvs_admin/*

cat  > copasi-${build}-src/configure.in << E_O_F
dnl Process this file with autoconf to produce a configure script.

AC_INIT(acinclude.m4) dnl a source file from your sub dir

dnl This is so we can use kde-common
AC_CONFIG_AUX_DIR(admin)

dnl Perform program name transformation
AC_ARG_PROGRAM

dnl Automake doc recommends to do this only here. (Janos)
AM_INIT_AUTOMAKE(copasi,${major}.${minor}.${build})

dnl make /usr/local the default for the installation
AC_PREFIX_DEFAULT(/usr/local)

QMAKE_ARG="\$QMAKE_ARG COPASI_SRC_PACKAGE=true"

dnl determine whether we build release or debug binaries
AC_ARG_ENABLE([debug],
  AS_HELP_STRING([--enable-debug],
                 [enable debug build (default: enabled)]),
  [ENABLE_DEBUG=\$enable_debug],
  [ENABLE_DEBUG="yes"])

AC_ARG_ENABLE([release],
  AS_HELP_STRING([--enable-release],
                 [enable release build (disables debug, default: disabled)]),
  [ENABLE_RELEASE=\$enable_release],
  [ENABLE_RELEASE="no"])
  
AC_ARG_ENABLE([package],
  AS_HELP_STRING([--enable-package],
                 [enable package build (disables debug, enables release default: disabled)]),
  [ENABLE_PACKAGE=\$enable_package],
  [ENABLE_PACKAGE="no"])

if test x"\${ENABLE_PACKAGE}" != x"no"; then
  ENABLE_RELEASE=\${ENABLE_PACKAGE}
  QMAKE_ARG="\$QMAKE_ARG PACKAGE=\${ENABLE_PACKAGE}"
fi;

if test x"\${ENABLE_RELEASE}" != x"yes" -a x"\${ENABLE_DEBUG}" != x"no"; then
  QMAKE_ARG="\$QMAKE_ARG CONFIG+=debug CONFIG-=release"
else
  QMAKE_ARG="\$QMAKE_ARG CONFIG+=release CONFIG-=debug"
fi


dnl determine whether we link against static libraries
AC_ARG_ENABLE([static],
  AS_HELP_STRING([--enable-static],
                 [enable static linkage (default: disabled)]),
  [ENABLE_STATIC=\$enable_static],
  [ENABLE_STATIC="no"])
  
if test x"\${ENABLE_STATIC}" != x"yes"; then
  QMAKE_ARG="\$QMAKE_ARG STATIC_LINKAGE=no"
else
  QMAKE_ARG="\$QMAKE_ARG STATIC_LINKAGE=yes"
fi

dnl enable or disable build of GUI
AC_ARG_ENABLE([gui],
  AS_HELP_STRING([--enable-gui],
                 [enable build of GUI (default: enabled)]),
  [ENABLE_GUI=\$enable_gui],
  [ENABLE_GUI="yes"])
QMAKE_ARG="\$QMAKE_ARG BUILD_GUI=\$ENABLE_GUI"


dnl qwt library
AC_ARG_WITH([qwt],
  AS_HELP_STRING([--with-qwt=PATH],
                 [Path to QWT Library ]),
  [QWT_PATH=\$withval])

if test x"\${QWT_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG QWT_PATH=\$QWT_PATH"
fi


dnl qwt3d library
AC_ARG_WITH([qwt3d],
  AS_HELP_STRING([--with-qwt3d=PATH],
                 [Path to QWT3D Library ]),
  [QWT3D_PATH=\$withval])

if test x"\${QWT3D_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG QWT3D_PATH=\$QWT3D_PATH"
fi


dnl expat library   
AC_ARG_WITH([expat],
  AC_HELP_STRING([--with-expat=PATH],
                 [Path to Expat XML Library ]),
  [EXPAT_PATH=\$withval])

if test x"\${EXPAT_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG EXPAT_PATH=\$EXPAT_PATH"
fi


dnl raptor library   
AC_ARG_WITH([raptor],
  AC_HELP_STRING([--with-raptor=PATH],
                 [Path to raptor RDF Library ]),
  [RAPTOR_PATH=\$withval])

if test x"\${RAPTOR_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG RAPTOR_PATH=\$RAPTOR_PATH"
fi


dnl cppunit library
AC_ARG_WITH([cppunit],
  AS_HELP_STRING([--with-cppunit=PATH],
                 [Path to CPPUNIT Library ]),
  [CPPUNIT_PATH=\$withval])

if test x"\${CPPUNIT_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG CPPUNIT_PATH=\$CPPUNIT_PATH"
fi

dnl sbw library
AC_ARG_WITH([sbw],
  AS_HELP_STRING([--with-sbw=PATH],
                 [Path to SBW Library ]),
  [SBW_PATH=\$withval])

if test x"\${SBW_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG SBW_PATH=\$SBW_PATH"
fi


dnl sbml library
AC_ARG_WITH([sbml],
  AS_HELP_STRING([--with-sbml=PATH],
                 [Path to SBML Library ]),
  [SBML_PATH=\$withval])

if test x"\${SBML_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG SBML_PATH=\$SBML_PATH"
fi


dnl LAPACK library alternatives
AC_ARG_WITH([clapack],
  AS_HELP_STRING([--with-clapack=PATH],
                 [Path to CLAPACK Library ]),
  [CLAPACK_PATH=\$withval])

if test x"\${CLAPACK_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG CLAPACK_PATH=\$CLAPACK_PATH"
fi


AC_ARG_WITH([lapack],
  AS_HELP_STRING([--with-lapack=PATH],
                 [Path to LAPACK Library ]),
  [LAPACK_PATH=\$withval])

if test x"\${LAPACK_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG LAPACK_PATH=\$LAPACK_PATH"
fi


AC_ARG_WITH([mkl],
  AS_HELP_STRING([--with-mkl=PATH],
                 [Path to MKL Library ]),
  [MKL_PATH=\$withval])

if test x"\${MKL_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG MKL_PATH=\$MKL_PATH"
fi


dnl bindings
AC_ARG_WITH([swig],
  AS_HELP_STRING([--with-swig=PATH],
                 [Path to swig]),
  [SWIG_PATH=\$withval])

if test x"\${SWIG_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG SWIG_PATH=\$SWIG_PATH"
fi


AC_ARG_ENABLE([python],
  AS_HELP_STRING([--enable-python],
                 [build python wrappers (default: disabled)]),
  [ENABLE_PYTHON=\$enable_python],
  [ENABLE_PYTHON="no"])

if test x"\${ENABLE_PYTHON}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG ENABLE_PYTHON=\$ENABLE_PYTHON"
fi


AC_ARG_WITH([python],
  AS_HELP_STRING([--with-python=PATH],
                 [Path to python]),
  [PYTHON_PATH=\$withval;PYTHON_INCLUDE_PATH=\$PYTHON_PATH/include;PYTHON_LIB_PATH=\$PYTHON_PATH/lib])


AC_ARG_WITH([python-includes],
  AS_HELP_STRING([--with-python-includes=PATH],
                 [Path to python include files]),
  [PYTHON_INCLUDE_PATH=\$withval])

if test x"\${PYTHON_INCLUDE_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG PYTHON_INCLUDE_PATH=\$PYTHON_INCLUDE_PATH"
fi


AC_ARG_WITH([python-libs],
  AS_HELP_STRING([--with-python-libs=PATH],
                 [Path to python library files]),
  [PYTHON_LIB_PATH=\$withval])

if test x"\${PYTHON_LIB_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG PYTHON_LIB_PATH=\$PYTHON_LIB_PATH"
fi


AC_ARG_ENABLE([java],
  AS_HELP_STRING([--enable-java],
                 [build java wrappers (default: disabled)]),
  [ENABLE_JAVA=\$enable_java],
  [ENABLE_JAVA="no"])

if test x"\${ENABLE_JAVA}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG ENABLE_JAVA=\$ENABLE_JAVA"
fi


AC_ARG_WITH([java],
  AS_HELP_STRING([--with-java=PATH],
                 [Path to Java]),
  [JAVA_PATH=\$withval;JAVA_HOME=\$withval;JAVA_INCLUDE_PATH=\$JAVA_PATH/include;JAVA_LIB_PATH=\$JAVA_PATH/lib])

if test x"\${JAVA_HOME}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG JAVA_HOME=\$JAVA_HOME"
fi


AC_ARG_WITH([java-includes],
  AS_HELP_STRING([--with-java-includes=PATH],
                 [Path to Java include files]),
  [JAVA_INCLUDE_PATH=\$withval])

if test x"\${JAVA_INCLUDE_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG JAVA_INCLUDE_PATH=\$JAVA_INCLUDE_PATH"
fi


AC_ARG_WITH([java-libs],
  AS_HELP_STRING([--with-java-libs=PATH],
                 [Path to Java libraries]),
  [JAVA_LIB_PATH=\$withval])

if test x"\${JAVA_LIB_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG JAVA_LIB_PATH=\$JAVA_LIB_PATH"
fi

AC_ARG_WITH([junit],
  AS_HELP_STRING([--with-junit=PATH],
                 [Path to junit]),
  [JUNIT_PATH=\$withval;])

if test x"\${JUNIT_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG JUNIT_PATH=\$JUNIT_PATH"
fi



dnl Handle COPASI license
AC_ARG_WITH([copasi-license],
  AS_HELP_STRING([--with-copasi-license],
                 [Specify whether to use the German (DE), US (US) or Commercial (COM) license.]),
  [COPASI_LICENSE=\$withval])

if test x"\${COPASI_LICENSE}" = x"DE" -o x"\${COPASI_LICENSE}" = x"COM"; then
  QMAKE_ARG="\$QMAKE_ARG USE_LICENSE=\$COPASI_LICENSE"
else
  QMAKE_ARG="\$QMAKE_ARG USE_LICENSE=US"
fi


AC_ARG_ENABLE([lex-yacc],
  AS_HELP_STRING([--enable-lex-yacc],
                 [Specify whether to compile lex and yacc sources (default: no).]),
  [ENABLE_LEX_YACC=\$enable_lex_yacc],
  [ENABLE_LEX_YACC="no"])
  
if test x"\$ENABLE_LEX_YACC" = x"yes"; then
  QMAKE_ARG="\$QMAKE_ARG BUILD_PARSER=yes"
fi


if test "x\$prefix" = "xNONE"; then
  prefix=\$ac_default_prefix
  ac_configure_args="\$ac_configure_args --prefix \$prefix"
fi



(
dnl to prevent calling aclocal, automake and configure again
 touch configure.in
 touch aclocal.m4 
 touch Makefile.in
 touch configure

 find copasi -type f -name Makefile -exec rm {} \\;

 cd copasi && \\
 echo executing in \`pwd\`: && \\
 rm -f .qmake.internal.cache */.qmake.internal.cache && \\
 echo "  qmake \$QMAKE_ARG" && \\
 \$QTDIR/bin/qmake \$QMAKE_ARG && \\
 cat Makefile | \\
 sed -e 's/(MAKEFILE): *\$/(MAKEFILE): Makefile/' \\
     -e 'sxQMAKE.*=.*qmakexQMAKE = \\\$(QTDIR)/bin/qmakex'> \$\$.tmp && \\
 mv \$\$.tmp Makefile && \\
 echo depend:  >> Makefile && \\
 echo "	touch Makefile" >> Makefile && \\
 cd ..
)

dnl add here all your Makefiles. These will be created by configure
AC_OUTPUT(Makefile)
E_O_F

cat  > copasi-${build}-src/Makefile.am << E_O_F
SUBDIRS = copasi

AUTOMAKE_OPTIONS = foreign 1.4

.PHONY: depend

depend:
	touch copasi/Makefile

E_O_F

cat  > copasi-${build}-src/configure.bat << E_O_F
@echo off 

echo @echo off > config.status.bat
echo echo running: configure.bat %1 %2 %3 %4 %5 %6 %7 %8 %9 >> config.status.bat
echo configure.bat %1 %2 %3 %4 %5 %6 %7 %8 %9 >> config.status.bat

if '%1' == '--enable-debug'        goto DEBUG
if '%1' == '--disable-debug'       goto RELEASE
if '%1' == '--enable-release'      goto RELEASE
if '%1' == '--disable-release'     goto DEBUG
set cps_plus=debug
set cps_minus=release
goto QMAKE

:DEBUG
shift
set cps_plus=debug
set cps_minus=release
goto QMAKE

:RELEASE
shift
set cps_plus=release
set cps_minus=debug

:QMAKE
cd copasi

echo executing in copasi:
rem  echo   for %%d in (%subdirs%) do del %%d\\.qmake.internal.cache
for %%d in (%subdirs%) do del %%d\\.qmake.internal.cache
echo   qmake "COPASI_SRC_PACKAGE=true" "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2 %3 %4 %5 %6 %7 %8 %9
%QTDIR%\\bin\\qmake "COPASI_SRC_PACKAGE=true" "CONFIG+=%cps_plus%" "CONFIG-=%cps_minus%" %1 %2 %3 %4 %5 %6 %7 %8 %9

nmake qmake_all

rem force relink
del CopasiUI\\main.obj CopasiSE\\CopasiSE.obj


cd ..
E_O_F

cd copasi-${build}-src
aclocal
autoconf
automake
rm -rf autom4te.cache

mv copasi/License${license}.txt.h copasi/copasilicense.h
rm copasi/License*.txt.h

#remove any reference to commercial license code
CleanFiles=`find . -type f -exec grep -Hq '#ifdef COPASI_LICENSE_COM' {} \; -exec echo {} \; | sort -u`
for file in $CleanFiles; do
  gawk -- ' BEGIN {keep = 1} $0 ~ "#ifdef COPASI_LICENSE_COM" {keep = 0} {if (keep == 1) {print $0}} $0 ~ "#endif // COPASI_LICENSE_COM" {keep = 1}' $file > $$.tmp && mv $$.tmp $file;
done;

#remove any reference to CROSSVALIDATION
CleanFiles=`find . -type f -exec grep -Hq '#ifdef COPASI_CROSSVALIDATION' {} \; -exec echo {} \; | sort -u`
for file in $CleanFiles; do
  gawk -- ' BEGIN {keep = 1} $0 ~ "#ifdef COPASI_CROSSVALIDATION" {keep = 0} {if (keep == 1) {print $0}} $0 ~ "#endif // COPASI_CROSSVALIDATION" {keep = 1}' $file > $$.tmp && mv $$.tmp $file;
done;

cd ..

tar -czf Copasi-${build}-SRC.tar.gz copasi-${build}-src 
 
scp Copasi-${build}-SRC*.* \
  copasi@gorbag.bioinformatics.vt.edu:www/integrator/snapshots/$license

