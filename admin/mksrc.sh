#!/usr/bin/env bash
# Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 


SCP=${COPASI_SCP:-scp}
AWK=${COPASI_AWK:-gawk}

if [ x"$COPASI_UPLOAD" != x ]; then
  function UPLOAD () {
    SRC=""
    while [ x"$2" != x ]; do
      SRC="$SRC $1"
      shift
    done
    ${SCP} ${SRC} ${COPASI_UPLOAD}/$1
  }
else
  function UPLOAD () {
    echo "Skipping upload (environment variable COPASI_UPLOAD not set)."
  }
fi

SAVEIFS=$IFS
IFS=$(echo -en "\n\b")

major=`${AWK} -- '$2 ~ "COPASI_VERSION_MAJOR" {print $3}' copasi/CopasiVersion.h`
minor=`${AWK} -- '$2 ~ "COPASI_VERSION_MINOR" {print $3}' copasi/CopasiVersion.h`
build=`${AWK} -- '$2 ~ "COPASI_VERSION_BUILD" {print $3}' copasi/CopasiVersion.h`
modified=`${AWK} -- '$2 ~ "COPASI_VERSION_MODIFIED" {print $3}' copasi/CopasiVersion.h`
compatibility=`${AWK} -- '$2 ~ "COPASI_VERSION_COMPATIBILITY" {print $3}' copasi/CopasiVersion.h`
comment="Source"
creator=""

buildname=${build}

if [ $modified == true ]; then
  buildname=${buildname}+
fi

license="US"

test -d copasi-${buildname}-src && rm -rf copasi-${buildname}-src

cd copasi
make src_distribution
cd ..

mv copasi_src copasi-${buildname}-src

sed -e 's/COPASI_VERSION_MAJOR.*/COPASI_VERSION_MAJOR '${major}'/' \
    -e 's/COPASI_VERSION_MINOR.*/COPASI_VERSION_MINOR '${minor}'/' \
    -e 's/COPASI_VERSION_BUILD.*/COPASI_VERSION_BUILD '${build}'/' \
    -e 's/COPASI_VERSION_MODIFIED.*/COPASI_VERSION_MODIFIED '${modified}'/' \
    -e 's/COPASI_VERSION_COMPATIBILITY.*/COPASI_VERSION_COMPATIBILITY '${compatibility}'/' \
    -e 's/COPASI_VERSION_COMMENT.*/COPASI_VERSION_COMMENT "'${comment}'"/' \
    -e 's/COPASI_VERSION_CREATOR.*/COPASI_VERSION_CREATOR "'${creator}'"/' \
    copasi/CopasiVersion.h.in > copasi-${buildname}-src/copasi/CopasiVersion.h

cp copasi-${buildname}-src/copasi/CopasiVersion.h copasi-${buildname}-src/copasi/CopasiVersion.h.in
    
IFS=$SAVEIFS

cp acinclude.m4 copasi-${buildname}-src

cp README.Linux copasi-${buildname}-src
cp README.SunOS copasi-${buildname}-src
cp README.Win32 copasi-${buildname}-src
cp README_MAC.rtf copasi-${buildname}-src
cp copasi/ArtisticLicense.txt copasi-${buildname}-src/LICENSE.txt

cp CMakeLists.txt copasi-${buildname}-src
cp *.cmake copasi-${buildname}-src
mkdir copasi-${buildname}-src/CMakeModules
cp CMakeModules/*.cmake copasi-${buildname}-src/CMakeModules

mkdir copasi-${buildname}-src/admin
cp admin/flex.sh copasi-${buildname}-src/admin
cp admin/install-sh copasi-${buildname}-src/admin
cp admin/missing copasi-${buildname}-src/admin
cp admin/mkbuild.sh copasi-${buildname}-src/admin
cp admin/yacc.sh copasi-${buildname}-src/admin
cp admin/include.sh copasi-${buildname}-src/admin
cp admin/libs.sh copasi-${buildname}-src/admin
chmod 755 copasi-${buildname}-src/admin/*

mkdir copasi-${buildname}-src/cvs_admin
cp cvs_admin/c++style copasi-${buildname}-src/cvs_admin
chmod 755 copasi-${buildname}-src/cvs_admin/*

cp admin/configure.in copasi-${buildname}-src
cp admin/configure.bat copasi-${buildname}-src
cp admin/Makefile.am copasi-${buildname}-src

#include GL/glext.h
mkdir copasi-${buildname}-src/copasi/GL
cp copasi/GL/glext.h copasi-${buildname}-src/copasi/GL

cd copasi-${buildname}-src

aclocal
autoconf
automake
rm -rf autom4te.cache

cd ..

tar -czf Copasi-${buildname}-SRC.tar.gz copasi-${buildname}-src 
 
UPLOAD Copasi-${buildname}-SRC*.* $license

