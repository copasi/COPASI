#!/bin/bash

if [ x"$#" = x1 ]; then
  build=`gawk -- '$2 ~ "VERSION_BUILD" {print $3}' ../copasiversion.h`

  case x"$1" in 
  xWIN32)
    zip CopasiUI-$build.zip CopasiUI.exe 
    ;;

  xDarwin)
    tar -czf CopasiUI-$build.tar.gz CopasiUI.app
    ;;

  xLinux|xSunOS)
    tar -czf CopasiUI-$build.tar.gz CopasiUI
    ;;
  esac

  scp CopasiUI-$build.* calvin.bioinformatics.vt.edu:/usr/local/apache/htdocs/calvin/copasi/$1
else
  echo usage: mkbuild.sh BUILD_OS
fi
