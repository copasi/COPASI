#!/bin/bash
# Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

#
# This script expects up to three arguments: 
#
# 1: the version to create (defaults to 4.14.92)
# 2: the source dir (defaults to ../COPASI)
# 3: the binary dir (defaults to ../package)
# 4: the dependency dir (defaults to /mnt/hgfs/share
#
DIRECTORY=$(cd `dirname $0` && pwd)

DEP_DIR=$4
if [ "_$DEP_DIR" = "_" ]; then
DEP_DIR=/mnt/hgfs/share
fi

OS=LINUX
DEP_SUFFIX=-32
VERSION=$1

if [ "_$VERSION" = "_" ]; then
VERSION=4.15.93
fi

ARCH=`uname -m`
if [ $ARCH = "x86_64" ]; then
DEP_SUFFIX=-64
fi

if [ -d "/Applications/" ]; then
OS=DARWIN
DEP_SUFFIX=
fi

DEP_DIR_NAME=dependencies$DEP_SUFFIX

SRC_DIR=$2
if [ "_$SRC_DIR" = "_" ]; then
SRC_DIR=$DIRECTORY/../COPASI
fi

BIN_DIR=$3
if [ "_$BIN_DIR" = "_" ]; then
BIN_DIR=$DIRECTORY/../package
fi

if [ ! -d $BIN_DIR/copasi ]; then

  echo invalid bin dir
  exit 1;

fi

if [ ! -d $BIN_DIR/copasi/bindings/python ]; then

  echo copasi has not been configured with python. 
  exit 1;

fi

if [ ! -f $BIN_DIR/copasi/bindings/python/copasi_wrapper.cpp ]; then

  echo swig bindings have not been created. Please build copasi with python bindings.  
  exit 1;

fi


PKG_DIR=$DIRECTORY/python-copasi-$VERSION
if [ -d "$PKG_DIR" ]; then

  echo Already have a dir for $VERSION;
  exit 1;

fi;

mkdir $PKG_DIR
mkdir $PKG_DIR/cpp-api
mkdir $PKG_DIR/common
mkdir $PKG_DIR/COPASI
mkdir $PKG_DIR/script
mkdir $PKG_DIR/src
mkdir $PKG_DIR/LINUX
mkdir $PKG_DIR/LINUX/dependencies-32
mkdir $PKG_DIR/LINUX/dependencies-64
mkdir $PKG_DIR/DARWIN

# create the files
sed 's/@VERSION@/$VERSION/g' $DIRECTORY/PKG-INFO    > $PKG_DIR/PKG-INFO
sed 's/@VERSION@/$VERSION/g' $DIRECTORY/setup.py.in > $PKG_DIR/setup.py

# copy cpp headers
(cd $SRC_DIR && find -name '*.h' -print | tar --create --files-from -) | (cd $PKG_DIR/cpp-api && tar xfp -)


# copy SWIG files
cp $SRC_DIR/copasi/bindings/common/*.cpp $PKG_DIR/common
cp $SRC_DIR/copasi/bindings/python/*.cpp $PKG_DIR/src
cp $BIN_DIR/copasi/bindings/python/*.cpp $PKG_DIR/src
cp $BIN_DIR/copasi/bindings/python/*.py  $PKG_DIR/script

# copy dependencies
pushd $PKG_DIR/LINUX/dependencies-32
tar zxf $DEP_DIR/LINUX/dependencies-32.tar.gz
cd $PKG_DIR/$OS/dependencies-32/lib
tar zxf $DEP_DIR/LINUX/se-32.tar.gz

popd
pushd $PKG_DIR/LINUX/dependencies-64
tar zxf $DEP_DIR/LINUX/dependencies-64.tar.gz
cd $PKG_DIR/$OS/dependencies-64/lib
tar zxf $DEP_DIR/LINUX/se-64.tar.gz
popd


# copy se libraries
cp $BIN_DIR/copasi/libCOPASISE.a $PKG_DIR/$OS/dependencies$DEP_SUFFIX/lib

cd $DIRECTORY
if [ -d $PKG_DIR/build ]; then
rm -rf $PKG_DIR/build
fi

tar -cf python-copasi-$VERSION.tar python-copasi-$VERSION
gzip python-copasi-$VERSION.tar



# test build
pushd $PKG_DIR
python setup.py build
popd
