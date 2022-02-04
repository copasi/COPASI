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


PYTHON_VERSION="$("$(cygpath "$PYTHON_EXECUTABLE")" --version 2>&1)"
PYTHON_VERSION=${PYTHON_VERSION#Python }
PYTHON_VERSION=${PYTHON_VERSION:0:3}

PACKAGE_NAME="COPASI-${MyAppVersion}-Python-${PYTHON_VERSION}-Bindings-Windows-${Arch}"

echo mkdir -p "${SETUP_DIR}"
mkdir -p "${SETUP_DIR}"
pushd "${SETUP_DIR}"

echo rm -rf "COPASI-${MyAppVersion}-Python-${PYTHON_VERSION}-Bindings-Windows-${Arch}"*
rm -rf "COPASI-${MyAppVersion}-Python-${PYTHON_VERSION}-Bindings-Windows-${Arch}"*

echo mkdir -p "${PACKAGE_NAME}"
mkdir -p "${PACKAGE_NAME}"
pushd "${PACKAGE_NAME}"

PYTHON_PACKAGE="build/lib.${PythonArch}-${PYTHON_VERSION}/COPASI"


echo mkdir -p "${PYTHON_PACKAGE}"
mkdir -p "${PYTHON_PACKAGE}"

# Create directory structure
echo mkdir -p "${PYTHON_PACKAGE}"/examples
mkdir -p "${PYTHON_PACKAGE}"/examples
chmod -R 755 "${PYTHON_PACKAGE}"/examples

# Copy license
echo cp "${SOURCE}"/copasi/ArtisticLicense.txt "${PYTHON_PACKAGE}"/LICENSE
cp "${SOURCE}"/copasi/ArtisticLicense.txt "${PYTHON_PACKAGE}"/LICENSE
chmod 644 "${PYTHON_PACKAGE}"/LICENSE

# Copy COPASI.py
echo cp "${BINARY_DIR}"/copasi/bindings/python/COPASI.py "${PYTHON_PACKAGE}"/__init__.py
cp "${BINARY_DIR}"/copasi/bindings/python/COPASI.py "${PYTHON_PACKAGE}"/__init__.py
chmod 644 "${PYTHON_PACKAGE}"/__init__.py

# Copy _COPASI.pyd
echo cp "${BINARY_DIR}"/copasi/bindings/python/_COPASI.pyd "${PYTHON_PACKAGE}"/_COPASI.pyd
cp "${BINARY_DIR}"/copasi/bindings/python/_COPASI.pyd "${PYTHON_PACKAGE}"/_COPASI.pyd
chmod 644  "${PYTHON_PACKAGE}"/_COPASI.pyd

# Copy examples
echo cp "${SOURCE}"/copasi/bindings/python/examples/*.py "${PYTHON_PACKAGE}"/examples
cp "${SOURCE}"/copasi/bindings/python/examples/*.py "${PYTHON_PACKAGE}"/examples
chmod 644 "${PYTHON_PACKAGE}"/examples/*

# Use Python distutils
# Create the customized setup.py file
echo sed -e 's/%COPASI_VERSION%/'${MyAppVersion}'/g' ${SOURCE}/InnoSetup/setup.py '>' setup.py
sed -e 's/%COPASI_VERSION%/'${MyAppVersion}'/g' ${SOURCE}/InnoSetup/setup.py > setup.py

echo "$(cygpath "$PYTHON_EXECUTABLE")" setup.py bdist_wininst --user-access-control force --skip-build --target-version="${PYTHON_VERSION}" --bitmap "$(cygpath -w "${SOURCE}"/InnoSetup/COPASI-python-installer-graphic.bmp)"
"$(cygpath "$PYTHON_EXECUTABLE")" setup.py bdist_wininst --user-access-control force --skip-build --target-version="${PYTHON_VERSION}" --bitmap "$(cygpath -w "${SOURCE}"/InnoSetup/COPASI-python-installer-graphic.bmp)"

echo cp "dist/COPASI-${MyAppVersion}.${PythonArch}-py${PYTHON_VERSION}.exe" "../${PACKAGE_NAME}.exe"
cp "dist/COPASI-${MyAppVersion}.${PythonArch}-py${PYTHON_VERSION}.exe" "../${PACKAGE_NAME}.exe"

popd
