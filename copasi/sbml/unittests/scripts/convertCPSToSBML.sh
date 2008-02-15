#!/bin/bash

# the script uses COPASISE to convert a COPASI model to an SBML model

COPASISE=$1
FILENAME=$2
OUTFILE=$3
LOGFILE=$4

if [ -e $COPASISE ];then
  if [ -e $FILENAME ];then
    $COPASISE --oldExportSBML ${OUTFILE} ${FILENAME} 2>&1 | sed '1,4d' > ${LOGFILE}
  fi
fi
