#!/bin/bash

SCP=${COPASI_SCP:-scp}

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

major=`gawk -- '$2 ~ "VERSION_MAJOR" {print $3}' copasi/copasiversion.h`
minor=`gawk -- '$2 ~ "VERSION_MINOR" {print $3}' copasi/copasiversion.h`
build=`gawk -- '$2 ~ "VERSION_BUILD" {print $3}' copasi/copasiversion.h`

license="US"

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

cp copasi/ArtisticLicense.txt copasi-${build}-src/LICENSE.txt

cp --parent admin/flex.sh copasi-${build}-src
cp --parent admin/install-sh copasi-${build}-src
cp --parent admin/missing copasi-${build}-src
cp --parent admin/mkbuild.sh copasi-${build}-src
cp --parent admin/yacc.sh copasi-${build}-src
chmod 755 copasi-${build}-src/admin/*

cp --parent cvs_admin/c++style copasi-${build}-src
chmod 755 copasi-${build}-src/cvs_admin/*

cp configure.in copasi-${build}-src
cp admin/configure.bat copasi-${build}-src

cd copasi-${build}-src
aclocal
autoconf
automake
rm -rf autom4te.cache

#remove any reference to CROSSVALIDATION
CleanFiles=`find . -type f -exec grep -Hq '#ifdef COPASI_CROSSVALIDATION' {} \; -exec echo {} \; | sort -u`
for file in $CleanFiles; do
  gawk -- ' BEGIN {keep = 1} $0 ~ "#ifdef COPASI_CROSSVALIDATION" {keep = 0} {if (keep == 1) {print $0}} $0 ~ "#endif // COPASI_CROSSVALIDATION" {keep = 1}' $file > $$.tmp && mv $$.tmp $file;
done;

#include GL/glext.h
mkdir copasi/GL
cp ../copasi/GL/glext.h

cd ..

tar -czf Copasi-${build}-SRC.tar.gz copasi-${build}-src 
 
UPLOAD Copasi-${build}-SRC*.* $license

