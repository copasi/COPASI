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

PACKAGE_NAME="COPASI-${MyAppVersion}-C#-Bindings-Darwin"

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
echo cp "${BINARY_DIR}"/copasi/bindings/csharp/copasicsP.dll  .
cp "${BINARY_DIR}"/copasi/bindings/csharp/copasicsP.dll .
chmod 644 copasicsP.dll

# Copy libcopasics.dylib
echo cp "${BINARY_DIR}"/copasi/bindings/csharp/libcopasics.dylib  .
cp "${BINARY_DIR}"/copasi/bindings/csharp/libcopasics.dylib .
chmod 644 libcopasics.dylib

# Copy examples
echo cp "${SOURCE}"/copasi/bindings/csharp/examples/*.cs examples
cp "${SOURCE}"/copasi/bindings/csharp/examples/*.cs examples
chmod 644 examples/*

popd

echo tar -cvzf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}
tar -czvf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}

popd
