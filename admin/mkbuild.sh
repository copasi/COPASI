#!/bin/bash

if [ x"$#" = x1 ]; then
  build=`gawk -- '$2 ~ "VERSION_BUILD" {print $3}' ../copasiversion.h`

  case x"$1" in 
  xWIN32)
    zip CopasiUI-$build-$1.zip CopasiUI.exe 
    ;;

  xDarwin)
    tar -czf CopasiUI-$build-$1.tar.gz CopasiUI.app
    ;;

  xLinux|xSunOS)
    tar -czf CopasiUI-$build-$1.tar.gz CopasiUI
    ;;
  esac

  scp CopasiUI-$build-$1.* calvin.bioinformatics.vt.edu:/usr/local/apache/htdocs/calvin/copasi/$1
else
  echo usage: mkbuild.sh BUILD_OS
fi
