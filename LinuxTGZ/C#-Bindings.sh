#!/bin/bash
# Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

PACKAGE_NAME="COPASI-${MyAppVersion}-C#-Bindings-${PACKAGE}"

echo mkdir -p "${SETUP_DIR}/${PACKAGE_NAME}"
mkdir -p "${SETUP_DIR}/${PACKAGE_NAME}"

pushd "${SETUP_DIR}"
pushd "${PACKAGE_NAME}"
rm -rf *

# Create directory structure
echo mkdir examples
mkdir examples
chmod -R 755 *

# Copy license
echo cp "${SOURCE}"/copasi/ArtisticLicense.txt LICENSE
cp "${SOURCE}"/copasi/ArtisticLicense.txt LICENSE
chmod 644 LICENSE

# Copy copasicsP.dll
echo cp "${BUILD}"/copasi/bindings/csharp/copasicsP.dll  .
cp "${BUILD}"/copasi/bindings/csharp/copasicsP.dll .
chmod 644 copasicsP.dll

# Copy libcopasics.so
echo cp "${BUILD}"/copasi/bindings/csharp/libcopasics.so  .
cp "${BUILD}"/copasi/bindings/csharp/libcopasics.so .
chmod 644 libcopasics.so

# Copy examples
echo cp "${SOURCE}"/copasi/bindings/csharp/examples/*.cs examples
cp "${SOURCE}"/copasi/bindings/csharp/examples/*.cs examples
chmod 644 examples/*

popd

echo tar -cvzf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}
tar -czvf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}

popd
