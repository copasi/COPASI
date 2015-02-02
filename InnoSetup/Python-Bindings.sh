#!/bin/bash
# Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

PACKAGE_NAME="COPASI-${MyAppVersion}-Python-Windows-${Arch}"

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

# Copy COPASI.py
echo cp copasi/bindings/python/COPASI.py  .
cp copasi/bindings/python/COPASI.py .
chmod 644 COPASI.py

# Copy _COPASI.pyd
echo cp copasi/bindings/python/_COPASI.pyd  .
cp copasi/bindings/python/_COPASI.pyd .
chmod 644 _COPASI.pyd

# Copy examples
echo cp "${SOURCE}"/copasi/bindings/python/examples/*.py examples
cp "${SOURCE}"/copasi/bindings/python/examples/*.py examples
chmod 644 examples/*

popd

echo tar -cvzf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}
tar -czvf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}

popd
