#!/bin/bash

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
    
IFS=$SAVEIFS

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

# remove any reference to CROSSVALIDATION
# CleanFiles=`find . -type f -exec grep -Hq '#ifdef COPASI_CROSSVALIDATION' {} \; -exec echo {} \; | sort -u`
# 
# for file in $CleanFiles; do
#   gawk -- ' BEGIN {keep = 1} $0 ~ "#ifdef COPASI_CROSSVALIDATION" {keep = 0} {if (keep == 1) {print $0}} $0 ~ "#endif // COPASI_CROSSVALIDATION" {keep = 1}' $file > $$.tmp && mv $$.tmp $file;
# done;

cd ..

tar -czf Copasi-${buildname}-SRC.tar.gz copasi-${buildname}-src 
 
UPLOAD Copasi-${buildname}-SRC*.* $license

