#!/usr/bin/env bash
# Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 


function libpath ()
{
  _l=`g++ -print-search-dirs | grep libraries | sed -e 's?^[^/]*??'`
  _l=`echo ${_l//:/ }`

  for _d in $_l; do
    [ -e $_d ] && (cd $_d; pwd)
  done
}

function findLib ()
{
  _i="$1"
  shift

  _found=false

  for _c in $@; do
    for _d in $_i; do
      if `ls ${_d} | grep -q lib${_c}'\.\(a\|so\|dylib\)'`; then
        _found=true 
        echo -l${_c}
        break
      fi
    done

    [ $_found = true ] && break;
  done
}

if [ x"$1" = x-l ]; then
  LibPath=$2
  shift
  shift
else
  LibPath=`libpath`
fi

findLib "$LibPath" $@



