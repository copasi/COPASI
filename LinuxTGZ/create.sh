#!/bin/bash
# Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 


SCP=${COPASI_SCP:-scp}
AWK=${COPASI_AWK:-gawk}
SORT=${COPASI_SORT:-sort}
PACKAGE=${COPASI_PACKAGE:-Linux}

COMMON_ENVIRONMENT=${COPASI_COMMON_ENVIRONMENT:-"/home/shoops/environment"}
SOURCE=${COPASI_SOURCE:-"${COMMON_ENVIRONMENT}/COPASI"}
BUILD=${COPASI_BUILD_32:-"${COMMON_ENVIRONMENT}/package"}
SETUP_DIR=${COPASI_SETUP_DIR:-"${COMMON_ENVIRONMENT}/setup"}

major=`${AWK} -- '$2 ~ "COPASI_VERSION_MAJOR" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
minor=`${AWK} -- '$2 ~ "COPASI_VERSION_MINOR" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
build=`${AWK} -- '$2 ~ "COPASI_VERSION_BUILD" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
modified=`${AWK} -- '$2 ~ "COPASI_VERSION_MODIFIED" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
comment=`${AWK} -- '$2 ~ "COPASI_VERSION_COMMENT" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
buildname=${build}

if [ $modified == true ]; then
  buildname=${buildname}+
fi

MyAppVersion=${major}.${minor}.${build}

if [ x"${comment}" = x\"Snapshot\" ]; then
  MyAppVersion=${major}.
  [ ${#minor} = 1 ] && MyAppVersion=${MyAppVersion}0
  MyAppVersion=${MyAppVersion}${minor}.
  [ ${#build} = 1 ] && MyAppVersion=${MyAppVersion}0
  MyAppVersion=${MyAppVersion}${build}
fi

PACKAGE_NAME="COPASI-${MyAppVersion}-${PACKAGE}"

[ -e ${SETUP_DIR} ] && rm -rf ${SETUP_DIR}/*
echo mkdir -p "${SETUP_DIR}/${PACKAGE_NAME}"
mkdir -p "${SETUP_DIR}/${PACKAGE_NAME}"

pushd "${SETUP_DIR}"
pushd "${PACKAGE_NAME}"

# Create directory structure
echo mkdir bin
mkdir bin
echo mkdir share
mkdir share
echo mkdir share/copasi
mkdir share/copasi
echo mkdir share/copasi/config
mkdir share/copasi/config
echo mkdir share/copasi/doc
mkdir share/copasi/doc
echo mkdir share/copasi/doc/html
mkdir share/copasi/doc/html
echo mkdir share/copasi/doc/html/figures
mkdir share/copasi/doc/html/figures
echo mkdir share/copasi/examples
mkdir share/copasi/examples
echo mkdir share/copasi/icons
mkdir share/copasi/icons
echo mkdir share/copasi/lib
mkdir share/copasi/lib
chmod -R 755 *

# Copy README
echo cp "${SOURCE}/README.Linux" share/copasi/README
cp "${SOURCE}/README.Linux" share/copasi/README
chmod 644 share/copasi/README

# Copy license
echo cp "${SOURCE}/copasi/ArtisticLicense.txt" share/copasi/LICENSE
cp "${SOURCE}/copasi/ArtisticLicense.txt" share/copasi/LICENSE
chmod 644 share/copasi/LICENSE

# Copy CopasiUI startup script
echo cp "${SOURCE}/LinuxTGZ/CopasiUI" bin
cp "${SOURCE}/LinuxTGZ/CopasiUI" bin
chmod 755 bin/CopasiUI

# Copy executables 
echo cp "${BUILD}/copasi/CopasiUI/CopasiUI"  share/copasi/lib
cp "${BUILD}/copasi/CopasiUI/CopasiUI"  share/copasi/lib
chmod 755 share/copasi/lib/CopasiUI

echo cp "${BUILD}/copasi/CopasiSE/CopasiSE"  bin
cp "${BUILD}/copasi/CopasiSE/CopasiSE"  bin
chmod 755 bin/CopasiSE

# Copy configuration resources    
echo cp "${SOURCE}/copasi/MIRIAM/MIRIAMResources.xml" share/copasi/config
cp "${SOURCE}/copasi/MIRIAM/MIRIAMResources.xml" share/copasi/config
chmod 444 share/copasi/config/*

# Copy examples
echo cp "${SOURCE}/TestSuite/distribution/"* share/copasi/examples
cp "${SOURCE}/TestSuite/distribution/"* share/copasi/examples
chmod 444 share/copasi/examples/*
chmod 777 share/copasi/examples

# Copy icons
echo cp "${SOURCE}"/copasi/CopasiUI/icons/Copasi??-Alpha.xpm share/copasi/icons
cp "${SOURCE}"/copasi/CopasiUI/icons/Copasi??-Alpha.xpm share/copasi/icons
echo cp "${SOURCE}"/copasi/CopasiUI/icons/CopasiDoc??-Alpha.xpm share/copasi/icons
cp "${SOURCE}"/copasi/CopasiUI/icons/CopasiDoc??-Alpha.xpm share/copasi/icons
chmod 644 share/copasi/icons/*

# Copy wizard resource
echo cp "${SOURCE}"/copasi/wizard/help_html/*.html share/copasi/doc/html
cp "${SOURCE}"/copasi/wizard/help_html/*.html share/copasi/doc/html
chmod 644 share/copasi/doc/html/*.html

echo cp "${SOURCE}"/copasi/wizard/help_html/figures/*.png share/copasi/doc/html/figures
cp "${SOURCE}"/copasi/wizard/help_html/figures/*.png share/copasi/doc/html/figures
chmod 644 share/copasi/doc/html/figures/*.png

# Copy Qt 4.8 libraries
echo cp `ldd share/copasi/lib/CopasiUI | awk -- '$0 ~ /libQt/ {print $3}'` share/copasi/lib
cp `ldd share/copasi/lib/CopasiUI | awk -- '$0 ~ /libQt/ {print $3}'` share/copasi/lib
chmod 644 share/copasi/lib/libQt*

popd

echo tar -cvzf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}
tar -czvf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}

popd
