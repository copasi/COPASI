#!/bin/bash
# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Echo all bash commands to ease debugging
set -x

INNO_SETUP=${COPASI_INNO_SETUP:-"/cygdrive/c/Program Files (x86)/Inno Setup 5/ISCC.exe"}
INNO_FILE=${COPASI_INNO_FILE:-"${SOURCE}/InnoSetup/copasi-universal.iss"}

# Create the unique product code based on version and application name
GUID=$(md5sum << EOF
#define MyAppName "COPASI"
#define MyAppVersion "${MyAppVersion}"
#define MyAppPublisher "copasi.org"
#define MyAppURL "http://www.copasi.org/"
#define MyAppExeName "bin\CopasiUI.exe"
EOF
) 
GUID=$(echo $GUID | sed 'y/abcdef/ABCDEF/')
productcode=${GUID:0:8}-${GUID:8:4}-${GUID:12:4}-${GUID:16:4}-${GUID:20:12}

[ -e ${SETUP_DIR}/package ] && rm -rf ${SETUP_DIR}/package
mkdir ${SETUP_DIR}/package
pushd ${SETUP_DIR}/package

# Create directory structure
tar -xvf ${BUILD_ROOT}/src/windows.tgz

# Copy README
cp ${SOURCE}/README.Win32 README.txt
chmod 644 README.txt

# Copy license
cp ${SOURCE}/copasi/ArtisticLicense.txt LICENSE.txt
chmod 644 LICENSE.txt

# Copy configuration resources
mkdir -p share/copasi/config
cp ${SOURCE}/copasi/MIRIAM/MIRIAMResources.xml share/copasi/config
chmod 444 share/copasi/config/*

# Copy examples
mkdir -p share/copasi/examples
cp ${SOURCE}/TestSuite/distribution/* share/copasi/examples
chmod 444 share/copasi/examples/*
chmod 777 share/copasi/examples

# Copy icons
mkdir -p share/copasi/icons
cp ${SOURCE}/copasi/UI/icons/Copasi.ico share/copasi/icons
cp ${SOURCE}/copasi/UI/icons/CopasiDoc.ico share/copasi/icons
chmod 644 share/copasi/icons/*

# Copy wizard resource
mkdir -p share/copasi/doc/html
cp ${SOURCE}/copasi/wizard/help_html/*.html share/copasi/doc/html
chmod 644 share/copasi/doc/html/*.html

mkdir -p share/copasi/doc/html/figures
cp ${SOURCE}/copasi/wizard/help_html/figures/*.png \
    share/copasi/doc/html/figures
chmod 644 share/copasi/doc/html/figures/*.png

# 32 bit files
cp "${BUILD_32_MD}/build/COPASI.${DIR_SUFFIX}/copasi/CopasiUI/CopasiUI.exe"  bin/32
chmod 755 bin/32/CopasiUI.exe
cp "${BUILD_32_MT}/build/COPASI.${DIR_SUFFIX}/copasi/CopasiSE/CopasiSE.exe"  bin/32
chmod 755 bin/32/CopasiSE.exe
cp ${SOURCE}/InnoSetup/qt.conf bin/32
chmod 644 bin/32/qt.conf

# 64 bit files
cp "${BUILD_64_MD}/build/COPASI.${DIR_SUFFIX}/copasi/CopasiUI/CopasiUI.exe"  bin/64
chmod 755 bin/64/CopasiUI.exe
cp "${BUILD_64_MT}/build/COPASI.${DIR_SUFFIX}/copasi/CopasiSE/CopasiSE.exe"  bin/64
chmod 755 bin/64/CopasiSE.exe
cp ${SOURCE}/InnoSetup/qt.conf bin/64
chmod 644 bin/64/qt.conf

# Execute InnoSetup to create Installation package
cd ${SOURCE}/InnoSetup

workdir=$(cygpath -wa .)
workdir=${workdir//\\/\\\\}

stagedir=$(cygpath -wa "${SETUP_DIR}/package")
stagedir=${stagedir//\\/\\\\}

#   modify product code, product version, and package name
sed -e '/#define MyAppVersion/s/".*"/"'${MyAppVersion}'"/' \
    -e '/#define MyBuild/s/".*"/"'${buildname}'"/' \
    -e '/#define MyAppId/s/".*"/"{{'${productcode}'}"/' \
    -e '/#define MyWorkDir/s/".*"/"'${workdir}'"/' \
    -e '/#define MyWorkDir/s/".*"/"'${workdir}'"/' \
    -e '/#define MyStageDir/s/".*"/"'${stagedir}'"/' \
    ${INNO_FILE} > tmp.iss

# Run Inno Setup to create package
"${INNO_SETUP}" tmp.iss && rm tmp.iss

# Move the package to its final location
mv COPASI-*-${PACKAGE}.exe "${SETUP_DIR}/package"
chmod 755 "${SETUP_DIR}"/package/COPASI-*-${PACKAGE}.exe

popd
