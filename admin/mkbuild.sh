#!/bin/bash

if [ x"$#" = x1 ]; then
  build=`gawk -- '$2 ~ "VERSION_BUILD" {print $3}' ../copasiversion.h`
  
  if [ x"$1" = xWIN32 ]; then
    zip CopasiUI-$build.zip CopasiUI.exe 
  else
    tar -czf CopasiUI-$build.tar.gz CopasiUI
  fi

  scp CopasiUI-$build.* calvin.bioinformatics.vt.edu:/usr/local/apache/htdocs/calvin/copasi/$1
else
  echo usage: mkbuild.sh BUILD_OS
fi
