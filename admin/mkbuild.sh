#!/bin/bash

PATH=$PATH:/bin:/usr/bin:/usr/local/bin

SCP=${COPASI_SCP:-scp}
AWK=${COPASI_AWK:-gawk}

PACKAGE=${COPASI_PACKAGE:-$1}

echo $PACKAGE

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
  major=`${AWK} -- '$2 ~ "VERSION_MAJOR" {print $3}' copasi/copasiversion.h`
  minor=`${AWK} -- '$2 ~ "VERSION_MINOR" {print $3}' copasi/copasiversion.h`
  build=`${AWK} -- '$2 ~ "VERSION_BUILD" {print $3}' copasi/copasiversion.h`

  license="US"

  rm Copasi-$build-${PACKAGE}.*

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

  UPLOAD Copasi-$build-${PACKAGE}.* \
    $license

else
  echo usage: mkbuild.sh BUILD_OS
fi
popd
