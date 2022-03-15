#!/bin/bash
# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 


SCP=${COPASI_SCP:-scp}
AWK=${COPASI_AWK:-gawk}
SORT=${COPASI_SORT:-sort}
PACKAGE=${COPASI_PACKAGE:-Linux}

COMMON_ENVIRONMENT=${BUILD_ROOT:-$HOME/build-system}
SOURCE="$(dirname "$(dirname "$(readlink -f "$0")")")"
SETUP_DIR=${COPASI_SETUP_DIR:-"${COMMON_ENVIRONMENT}/setup"}

major=`${AWK} -- '$2 ~ "COPASI_VERSION_MAJOR" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
minor=`${AWK} -- '$2 ~ "COPASI_VERSION_MINOR" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
build=`${AWK} -- '$2 ~ "COPASI_VERSION_BUILD" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
modified=`${AWK} -- '$2 ~ "COPASI_VERSION_MODIFIED" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
comment=`${AWK} -- '$2 ~ "COPASI_VERSION_COMMENT" {print $3}' "${SOURCE}/copasi/CopasiVersion.h"`
buildname=${build}

if [ $modified == true ]; then
  buildname=${buildname}+
fi

MyAppVersion=${major}.${minor}.${build}

if [ x"${comment}" = x\"Snapshot\" ]; then
  MyAppVersion=${major}.
  [ ${#minor} = 1 ] && MyAppVersion=${MyAppVersion}0
  MyAppVersion=${MyAppVersion}${minor}.
  [ ${#build} = 1 ] && MyAppVersion=${MyAppVersion}0
  MyAppVersion=${MyAppVersion}${build}
fi

echo mkdir -p "${SETUP_DIR}"
mkdir -p "${SETUP_DIR}"

case $1 in
  'COPASI')
    . ${SOURCE}/LinuxTGZ/COPASI.sh
    ;;

  'Java-Bindings')
    . ${SOURCE}/LinuxTGZ/Java-Bindings.sh
    ;;

  'C#-Bindings')
    . ${SOURCE}/LinuxTGZ/C#-Bindings.sh
    ;;

  'Python-Bindings')
    . ${SOURCE}/LinuxTGZ/Python-Bindings.sh
    ;;
esac

