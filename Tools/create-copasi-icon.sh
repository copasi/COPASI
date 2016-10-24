#!/bin/bash
# Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

#
# This scripts creates a desktop file in the users local 
# applications directory
#
# usage: 
#    create-copasi-icon.sh <copasi release dir> 
#
# example:
#    create-copasi-icon.sh ~/COPASI-4.16.104-Linux-64bit
#
THIS_DIR=$(cd `dirname $0` && pwd)
DEST_DIR=~/.local/share/applications
COPASI_DIR=$1
# bail if desktop icon exists
if [ -f "${TARGET}" ]
then
  echo "A COPASI desktop icon already exists. Remove it first before continuing"
  echo "full path: ${TARGET}"
  exit 1
fi

# ensure we have COPASI dir
if [ "${COPASI_DIR}" == "" ]
then
  echo "Need the COPASI directory as unzipped from the distribution"
  echo "archive as argument. "
  echo ""
  echo "if you have not downloaded COPASI you can get it from"
  echo "http://copasi.org/Download"
  exit 1
fi

# ensure that we have COPASI UI in there
if [ ! -f "${COPASI_DIR}/bin/CopasiUI" ]
then
  echo "The specified COPASI directory has no CopasiUI application"
  echo "in the specified location."
  exit 1
fi

# get full path to it
COPASI_DIR=$(cd $1 && pwd)

if [ ! -d "${DEST_DIR}"]
then
  mkdir ${DEST_DIR}
fi

TARGET=${DEST_DIR}/COPASI.desktop

echo "[Desktop Entry]" > ${TARGET}
echo "Version=1.0" >> ${TARGET}
echo "Terminal=false" >> ${TARGET}
echo "Type=Application" >> ${TARGET}
echo "Name=COPASI" >> ${TARGET}
echo "Exec=${COPASI_DIR}/bin/CopasiUI %f" >> ${TARGET}
echo "NoDisplay=false"  >> ${TARGET}
if [ -f "${COPASI_DIR}/share/copasi/icons/Copasi48-Alpha.xpm" ]
then
  echo "Icon=${COPASI_DIR}/share/copasi/icons/Copasi48-Alpha.xpm" >> ${TARGET}
fi

echo "The desktop file has now been created in:"
echo " ${TARGET}"


