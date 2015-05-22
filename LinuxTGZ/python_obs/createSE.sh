#!/bin/bash
# Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

#

DIRECTORY=$(cd `dirname $0` && pwd)

BIN_DIR=$1
if [ "_$BIN_DIR" = "_" ]; then
 echo need bin dir!
 exit 1;
fi

ARCH=`uname -m`
DEP_SUFFIX=-32
if [ $ARCH = "x86_64" ]; then
DEP_SUFFIX=-64
fi

if [ -d "/Applications/" ]; then
OS=DARWIN
DEP_SUFFIX=
fi

if [ ! -d $BIN_DIR/copasi ]; then
  echo binary dir does not exist
  exit 1;
fi

if [ ! -f $BIN_DIR/copasi/libCOPASISE.a ]; then
  echo libCOPASISE not present
  exit 1;
fi


cd $BIN_DIR/copasi

tar -cf se$DEP_SUFFIX.tar libCOPASISE.a
gzip se$DEP_SUFFIX.tar
mv se$DEP_SUFFIX.tar.gz $DIRECTORY
cd $DIRECTORY

echo created se$DEP_SUFFIX.tar.gz


