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

AC_ARG_ENABLE([debug],
  AS_HELP_STRING([--enable-debug],
                 [enable debug build (default: enabled)]),
  [ENABLE_DEBUG=\$enable_debug],
  [ENABLE_DEBUG="no"])

AC_ARG_ENABLE([release],
  AS_HELP_STRING([--enable-release],
                 [enable release build (disables debug, default: disabled)]),
  [ENABLE_RELEASE=\$enable_release],
  [ENABLE_RELEASE="no"])
  
AC_ARG_ENABLE([static],
  AS_HELP_STRING([--enable-static],
                 [enable static linkage (default: disabled)]),
  [ENABLE_STATIC=\$enable_static],
  [ENABLE_STATIC="no"])
  
AC_ARG_WITH([expat],
  AC_HELP_STRING([--with-expat=PATH],
                 [Path to Expat XML Library ]),
  [EXPAT_PATH=\$withval])

AC_ARG_WITH([sbml],
  AS_HELP_STRING([--with-sbml=PATH],
                 [Path to SBML Library ]),
  [SBML_PATH=\$withval])

dnl LAPACK library alternatives
AC_ARG_WITH([clapack],
  AS_HELP_STRING([--with-clapack=PATH],
                 [Path to CLAPACK Library ]),
  [CLAPACK_PATH=\$withval])

AC_ARG_WITH([lapack],
  AS_HELP_STRING([--with-lapack=PATH],
                 [Path to LAPACK Library ]),
  [LAPACK_PATH=\$withval])

AC_ARG_WITH([mkl],
  AS_HELP_STRING([--with-mkl=PATH],
                 [Path to MKL Library ]),
  [MKL_PATH=\$withval])


AC_ARG_WITH([qwt],
  AS_HELP_STRING([--with-qwt=PATH],
                 [Path to QWT Library ]),
  [QWT_PATH=\$withval])

AC_ARG_WITH([build-parser],
  AS_HELP_STRING([--with-build-parser],
                 [Specify whether to build lex and yacc sources.]),
  [BUILD_PARSER=\$withval])

QMAKE_ARG="COPASI_SRC_PACKAGE=true"

if test "x\$prefix" = "xNONE"; then
  prefix=\$ac_default_prefix
  ac_configure_args="\$ac_configure_args --prefix \$prefix"
fi

if test x"\${COPASI_LICENSE}" = x"DE" -o x"\${COPASI_LICENSE}" = x"US"; then
  QMAKE_ARG="USE_LICENSE=\$COPASI_LICENSE"
fi

if test x"\$BUILD_PARSER" = x"yes"; then
  QMAKE_ARG="\$QMAKE_ARG BUILD_PARSER=yes"
fi

if test x"\${ENABLE_RELEASE}" != x"yes" -a x"\${ENABLE_DEBUG}" != x"no"; then
  QMAKE_ARG="\$QMAKE_ARG CONFIG+=debug CONFIG-=release"
else
  QMAKE_ARG="\$QMAKE_ARG CONFIG+=release CONFIG-=debug"
fi

if test x"\${ENABLE_STATIC}" != x"yes"; then
  QMAKE_ARG="\$QMAKE_ARG STATIC_LINKAGE=no"
else
  QMAKE_ARG="\$QMAKE_ARG STATIC_LINKAGE=yes"
fi

dnl if test x"\${enable_thread}" != x"no"; then
dnl   QMAKE_ARG="\$QMAKE_ARG CONFIG+=thread"
dnl else
dnl   QMAKE_ARG="\$QMAKE_ARG CONFIG-=thread"
dnl fi

if test x"\${MKL_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG MKL_PATH=\$MKL_PATH"
fi

if test x"\${CLAPACK_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG CLAPACK_PATH=\$CLAPACK_PATH"
fi

if test x"\${LAPACK_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG LAPACK_PATH=\$LAPACK_PATH"
fi

if test x"\${EXPAT_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG EXPAT_PATH=\$EXPAT_PATH"
fi

if test x"\${QWT_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG QWT_PATH=\$QWT_PATH"
fi

if test x"\${SBML_PATH}" != x""; then
  QMAKE_ARG="\$QMAKE_ARG SBML_PATH=\$SBML_PATH"
fi


(
dnl to prevent calling aclocal, automake and configure again
 touch configure.in
 touch aclocal.m4 
 touch Makefile.in
 touch configure

 cd copasi && \\
 echo executing in \`pwd\`: && \\
 rm -f .qmake.internal.cache */.qmake.internal.cache && \\
 rm -f Makefile */Makefile && \\
 echo "  qmake \$QMAKE_ARG" && \\
 \$QTDIR/bin/qmake \$QMAKE_ARG && \\
 cat Makefile | \\
 sed -e 's/(MAKEFILE): *\$/(MAKEFILE): Makefile/' \\
     -e 'sxQMAKE.*=.*qmakexQMAKE = \\\$(QTDIR)/bin/qmakex'> \$\$.tmp && \\
 mv \$\$.tmp Makefile && \\
 echo depend:  >> Makefile && \\
 echo "	touch Makefile" >> Makefile && \\
 rm -f CopasiSE/CopasiSE.o CopasiUI/main.o && \ 
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
cd ..

tar -czf Copasi-${build}-SRC.tar.gz copasi-${build}-src 
scp Copasi-$build-SRC*.* \
  calvin.bioinformatics.vt.edu:/usr/local/apache/htdocs/calvin/copasi/alpha-test/SRC/$license

