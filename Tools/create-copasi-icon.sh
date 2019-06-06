#!/bin/bash
# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

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

TARGET=${DEST_DIR}/COPASI.desktop

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

if [ ! -d "${DEST_DIR}" ]
then
  mkdir ${DEST_DIR}
fi

echo "[Desktop Entry]" > ${TARGET}
echo "Version=1.0" >> ${TARGET}
echo "Terminal=false" >> ${TARGET}
echo "Type=Application" >> ${TARGET}
echo "Name=COPASI" >> ${TARGET}
echo "Exec=${COPASI_DIR}/bin/CopasiUI %u" >> ${TARGET}
echo "NoDisplay=false"  >> ${TARGET}
echo "MimeType=x-scheme-handler/copasi" >> ${TARGET}
if [ -f "${COPASI_DIR}/share/copasi/icons/Copasi48-Alpha.xpm" ]
then
  echo "Icon=${COPASI_DIR}/share/copasi/icons/Copasi48-Alpha.xpm" >> ${TARGET}
fi

echo "The desktop file has now been created in:"
echo " ${TARGET}"
echo ""
echo "Now register the copasi URL scheme with: " 
echo ""
echo "xdg-settings set default-url-scheme-handler copasi COPASI.desktop"
echo ""
