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
comment=`gawk -- '$2 ~ "VERSION_COMMENT" {print $3}' copasi/copasiversion.h`
buildname=${build}

if [ x"${comment}" = x\"Snapshot\" ]; then
  buildname=${major}
  [ ${#minor} = 1 ] && buildname=${buildname}0
  buildname=${buildname}${minor}
  [ ${#build} = 1 ] && buildname=${buildname}0
  buildname=${buildname}${build}
fi

license="US"

test -d copasi-${buildname}-src && rm -rf copasi-${buildname}-src

cd copasi
make src_distribution
cd ..

mv copasi_src copasi-${buildname}-src

cp acinclude.m4 copasi-${buildname}-src

cp README.Linux copasi-${buildname}-src
cp README.SunOS copasi-${buildname}-src
cp README.Win32 copasi-${buildname}-src
cp README_MAC.rtf copasi-${buildname}-src

cp copasi/ArtisticLicense.txt copasi-${buildname}-src/LICENSE.txt

cp --parent admin/flex.sh copasi-${buildname}-src
cp --parent admin/install-sh copasi-${buildname}-src
cp --parent admin/missing copasi-${buildname}-src
cp --parent admin/mkbuild.sh copasi-${buildname}-src
cp --parent admin/yacc.sh copasi-${buildname}-src
chmod 755 copasi-${buildname}-src/admin/*

cp --parent cvs_admin/c++style copasi-${buildname}-src
chmod 755 copasi-${buildname}-src/cvs_admin/*

cp configure.in copasi-${buildname}-src
cp admin/configure.bat copasi-${buildname}-src

#include GL/glext.h
cp --parent copasi/GL/glext.h copasi-${buildname}-src

cd copasi-${buildname}-src

aclocal
autoconf
automake
rm -rf autom4te.cache

#remove any reference to CROSSVALIDATION
CleanFiles=`find . -type f -exec grep -Hq '#ifdef COPASI_CROSSVALIDATION' {} \; -exec echo {} \; | sort -u`

for file in $CleanFiles; do
  gawk -- ' BEGIN {keep = 1} $0 ~ "#ifdef COPASI_CROSSVALIDATION" {keep = 0} {if (keep == 1) {print $0}} $0 ~ "#endif // COPASI_CROSSVALIDATION" {keep = 1}' $file > $$.tmp && mv $$.tmp $file;
done;

cd ..

tar -czf Copasi-${buildname}-SRC.tar.gz copasi-${buildname}-src 
 
UPLOAD Copasi-${buildname}-SRC*.* $license

