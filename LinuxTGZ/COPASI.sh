#!/bin/bash
# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

PACKAGE_NAME="COPASI-${MyAppVersion}-${PACKAGE}"

echo mkdir -p "${SETUP_DIR}/${PACKAGE_NAME}"
mkdir -p "${SETUP_DIR}/${PACKAGE_NAME}"

pushd "${SETUP_DIR}"
pushd "${PACKAGE_NAME}"
rm -rf *

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
echo cp "${BUILD_ROOT}/copasi/CopasiUI/CopasiUI"  share/copasi/lib
cp "${BUILD_ROOT}/copasi/CopasiUI/CopasiUI"  share/copasi/lib
chmod 755 share/copasi/lib/CopasiUI

echo cp "${BUILD_ROOT}/copasi/CopasiSE/CopasiSE"  bin
cp "${BUILD_ROOT}/copasi/CopasiSE/CopasiSE"  bin
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

echo cp -r "${SETUP_DIR}"/src/share/copasi/lib share/copasi
cp -r "${SETUP_DIR}"/src/share/copasi/lib share/copasi

# Copy Qt libraries
echo cp `ldd share/copasi/lib/CopasiUI | awk -- '$0 ~ /libQt/ {print $3}'` share/copasi/lib
cp `ldd share/copasi/lib/CopasiUI | awk -- '$0 ~ /libQt/ {print $3}'` share/copasi/lib
chmod 644 share/copasi/lib/libQt*


echo
popd

echo tar -cvzf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}
tar -czvf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}

popd
