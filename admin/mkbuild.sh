#!/bin/bash
pushd ../..

if [ x"$#" = x1 ]; then
  build=`gawk -- '$2 ~ "VERSION_BUILD" {print $3}' copasi/copasiversion.h`

  case x"$1" in 
  xWIN32)
    zip CopasiUI-$build-$1.zip CopasiUI.exe 
    ;;

  xDarwin)
    tar -czf CopasiUI-$build-$1.tar.gz CopasiUI.app
    ;;

  xLinux|xSunOS)
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
    chmod -R 755 copasi

    cp ../README.$1 copasi/README
    chmod 644 copasi/README

    cp ../copasi/CopasiUI/CopasiUI  copasi/bin
    chmod 755 copasi/bin/CopasiUI

    cp ../TestSuite/distribution/* copasi/share/copasi/examples
    chmod 644 copasi/share/doc/copasi/examples/*

    cp ../copasi/wizard/help_html/*.html copasi/share/copasi/doc/html
    chmod 644 copasi/share/copasi/doc/html/*.html

    cp ../copasi/wizard/help_html/figures/*.jpg \
       copasi/share/copasi/doc/html/figures
    chmod 644 copasi/share/copasi/doc/html/figures/*.jpg

    tar -czf ../Copasi-$build-$1.tar.gz copasi
  
    cd ..
    rm -rf $build-$1
    ;;
  esac

  scp Copasi-$build-$1.* \
      calvin.bioinformatics.vt.edu:/usr/local/apache/htdocs/calvin/copasi/alpha-test/$1
  rm Copasi-$build-$1.*
else
  echo usage: mkbuild.sh BUILD_OS
fi
popd
