#!/bin/bash
# Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 


# PATH=$PATH:/bin:/usr/bin:/usr/local/bin

SCP=${COPASI_SCP:-scp}
AWK=${COPASI_AWK:-gawk}
SORT=${COPASI_SORT:-sort}
PACKAGE=${COPASI_PACKAGE:-Windows}

COMMON_ENVIRONMENT=${COPASI_COMMON_ENVIRONMENT:-"/Users/shoops/environment/10.6/"}
BUILD=${COPASI_BUILD:-"${COMMON_ENVIRONMENT}/package"}
SOURCE=${COPASI_SOURCE:-"${COMMON_ENVIRONMENT}/COPASI"}
SETUP_DIR=${COPASI_SETUP_DIR:-"${COMMON_ENVIRONMENT}/setup"}

PACKAGE_MAKER=${COPASI_PACKAGE_MAKER:-"/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker"}

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
  MyAppVersion=${MyAppVersion}${buildname}
fi

[ -e ${SETUP_DIR} ] && rm -rf ${SETUP_DIR}/*
mkdir -p ${SETUP_DIR}/package
pushd ${SETUP_DIR}/package

mkdir -p Applications/COPASI/

# Copy CopasiUI
cp -r "${BUILD}/copasi/CopasiUI/CopasiUI.app" Applications/COPASI/

# copy the icon into the Resources directory
echo "Creating Resources directory."
mkdir -p Applications/COPASI/CopasiUI.app/Contents/Resources

echo "Copy the icon file to the bundle."
cp ${SOURCE}/copasi.icns Applications/COPASI/CopasiUI.app/Contents/Resources/

# copy the files for the wizard into the Resources directory
echo "Making directory for wizard."
mkdir -p Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html
echo "Copying files for wizard."
cp ${SOURCE}/copasi/wizard/help_html/*.html \
  Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html/
cp -r ${SOURCE}/copasi/wizard/help_html/figures \
  Applications/COPASI/CopasiUI.app/Contents/Resources/doc/html/

# add the readme to the image
echo "Copying readme file."
cp ${SOURCE}/README_MAC.rtf Applications/COPASI/COPASI-README.rtf

# add the license to the image
echo "Copying license file."
cp ${SOURCE}/copasi/ArtisticLicense.txt Applications/COPASI/LICENSE.txt

# copy the examples into the Resources directory
echo "Make example directory."
mkdir -p Applications/COPASI/examples
echo "Copy examples to example directory."
cp ${SOURCE}/TestSuite/distribution/* Applications/COPASI/examples/
chmod 444 Applications/COPASI/examples/*
chmod 777 Applications/COPASI/examples

# copy default configuration
echo "Make directory for default configuration"
mkdir -p Applications/COPASI/config
echo "Copy default configuration files"
cp ${SOURCE}/copasi/MIRIAM/MIRIAMResources.xml Applications/COPASI/config
chmod 444 Applications/COPASI/config/*
chmod 777 Applications/COPASI/config

# copy the commandline version if it exists
cp ${BUILD}/copasi/CopasiSE/CopasiSE Applications/COPASI/
strip Applications/COPASI/CopasiSE
chmod 755 Applications/COPASI/CopasiSE

popd

mkdir -p ${SETUP_DIR}/Resources
cp ${SOURCE}/copasi/ArtisticLicense.txt ${SETUP_DIR}/Resources/License.txt


# Run PackageMaker to create package
pushd ${SETUP_DIR}
echo Running PackageMaker ...
"${PACKAGE_MAKER}" \
  --root "${SETUP_DIR}/package" \
  --info "${SETUP_DIR}/package/Applications/COPASI/CopasiUI.app/Contents/Info.plist"

mv package.pkg "COPASI-${MyAppVersion}.pkg"

echo Creating disk image
hdiutil create -volname COPASI-${MyAppVersion}-Darwin -srcfolder "COPASI-${MyAppVersion}.pkg" -ov -format UDZO COPASI-${MyAppVersion}-Darwin
popd

# Move the package to its final location
# cp COPASI-${buildname}-Darwin.exe "${SETUP_DIR}/package"
# chmod 755 "${SETUP_DIR}"/package/COPASI-${buildname}-${PACKAGE}.exe
