#!/usr/bin/env bash
# Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 


function includepath ()
{
  _c1plus=`gcc -print-prog-name=cc1plus`
  $_c1plus -Wp, -v /dev/null 2>&1 | grep '^ /'
}

function findSubdir ()
{
  _i="$1"
  shift

  _found=false

  for _c in $@; do
    for _d in $_i; do
      if [ -e $_d/$_c ]; then
        _found=true 
        (cd $_d/$_c; pwd)
        break
      fi
    done

    [ $_found = true ] && break;
  done

  [ $_found = false -a -e "$_i" ] && (cd $_i/; pwd)
}

if [ x"$1" = x-i ]; then
  IncludePath=$2
  shift
  shift
else
  IncludePath=`includepath`
fi

findSubdir "$IncludePath" $@


