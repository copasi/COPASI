#!/bin/bash

PATH=$PATH:/bin:/usr/bin:/usr/local/bin

SCP=${COPASI_SCP:-scp}
AWK=${COPASI_AWK:-gawk}

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

  rm Copasi-$build-$1*.*

  case x"$1" in 
  xWIN32)
    . admin/mkWIN32.sh
    ;;

  xDarwin)
    . admin/mkDarwin.sh
    ;;

  xLinux|xSunOS)
    [ -e $build-$1 ] && rm -rf $build-$1
    mkdir $build-$1
    cd $build-$1

    mkdir copasi
    mkdir copasi/bin
    mkdir copasi/share
    mkdir copasi/share/copasi
    mkdir copasi/share/copasi/doc
    mkdir copasi/share/copasi/doc/html
    mkdir copasi/share/copasi/doc/html/figures
    mkdir copasi/share/copasi/examples
    mkdir copasi/share/copasi/icons
    mkdir copasi/share/copasi/config
    chmod -R 755 copasi

    cp ../README.$1 copasi/README
    chmod 644 copasi/README

    cp ../copasi/ArtisticLicense.txt copasi/LICENSE
    chmod 644 copasi/LICENSE

    cp ../copasi/CopasiUI/CopasiUI  copasi/bin
    chmod 755 copasi/bin/CopasiUI

    cp ../copasi/CopasiSE/CopasiSE  copasi/bin
    chmod 755 copasi/bin/CopasiSE

    cp ../copasi/MIRIAM/MIRIAMResources.xml copasi/share/copasi/config
    chmod 444 copasi/share/copasi/config/*

    cp ../TestSuite/distribution/* copasi/share/copasi/examples
    chmod 444 copasi/share/copasi/examples/*

    cp ../copasi/CopasiUI/icons/Copasi??-Alpha.xpm copasi/share/copasi/icons
    cp ../copasi/CopasiUI/icons/CopasiDoc??-Alpha.xpm copasi/share/copasi/icons
    chmod 644 copasi/share/copasi/icons/*

    cp ../copasi/wizard/help_html/*.html copasi/share/copasi/doc/html
    chmod 644 copasi/share/copasi/doc/html/*.html

    cp ../copasi/wizard/help_html/figures/*.png \
       copasi/share/copasi/doc/html/figures
    chmod 644 copasi/share/copasi/doc/html/figures/*.png

    tar -czf ../Copasi-$build-$1.tar.gz copasi

    if [ x"$license" = xUS ]; then
      UPLOAD copasi/bin/CopasiSE \
        $license/Copasi-AllSE/$1/CopasiSE-$build
    fi

    cp ../copasi/CopasiUI/CopasiUI-dynamic  copasi/bin/CopasiUI
    chmod 755 copasi/bin/CopasiUI

    cp ../copasi/CopasiSE/CopasiSE-dynamic  copasi/bin/CopasiSE
    chmod 755 copasi/bin/CopasiSE

    tar -czf ../Copasi-$build-$1-Dynamic.tar.gz copasi

    if [ x"$license" = xUS ]; then
      UPLOAD copasi/bin/CopasiSE \
        $license/Copasi-AllSE/$1-Dynamic/CopasiSE-$build
    fi
    
    cd ..
    ;;
  esac

  UPLOAD Copasi-$build-$1*.* \
    $license

else
  echo usage: mkbuild.sh BUILD_OS
fi
popd
