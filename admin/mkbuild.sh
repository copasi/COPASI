#!/usr/bin/env bash
# Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 


PATH=$PATH:/bin:/usr/bin:/usr/local/bin

SCP=${COPASI_SCP:-scp}
AWK=${COPASI_AWK:-gawk}
SORT=${COPASI_SORT:-sort}
PACKAGE=${COPASI_PACKAGE:-$1}

if [ x"$COPASI_UPLOAD" != x ]; then
  function UPLOAD () {
    SRC=""
    while [ x"$2" != x ]; do
      SRC="$SRC $1"
      shift
    done
    echo ${SCP} ${SRC} ${COPASI_UPLOAD}/$1
    ${SCP} ${SRC} ${COPASI_UPLOAD}/$1
  }
else
  function UPLOAD () {
    echo "Skipping upload (environment variable COPASI_UPLOAD not set)."
  }
fi

pushd ../..

if [ x"$#" = x1 ]; then
  major=`${AWK} -- '$2 ~ "COPASI_VERSION_MAJOR" {print $3}' copasi/CopasiVersion.h`
  minor=`${AWK} -- '$2 ~ "COPASI_VERSION_MINOR" {print $3}' copasi/CopasiVersion.h`
  build=`${AWK} -- '$2 ~ "COPASI_VERSION_BUILD" {print $3}' copasi/CopasiVersion.h`
  modified=`${AWK} -- '$2 ~ "COPASI_VERSION_MODIFIED" {print $3}' copasi/CopasiVersion.h`
  comment=`${AWK} -- '$2 ~ "COPASI_VERSION_COMMENT" {print $3}' copasi/CopasiVersion.h`
  buildname=${build}

  if [ $modified == true ]; then
    buildname=${buildname}+
  fi
  
  license="US"

  rm Copasi-${buildname}-${PACKAGE}.*

  case x"$1" in 
  xWIN32)
    . admin/mkWIN32.sh
    ;;

  xDarwin)
    . admin/mkDarwin.sh
    ;;

  xLinux|xSunOS)
    . admin/mkLinux.sh
    ;;
  esac

  UPLOAD Copasi-${buildname}-${PACKAGE}.* \
    $license

else
  echo usage: mkbuild.sh BUILD_OS
fi
popd
