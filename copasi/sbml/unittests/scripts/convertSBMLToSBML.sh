#!/bin/bash

# the script uses COPASISE to import an SBML file 
# and reexport it

COPASISE=$1
FILENAME=$2
OUTFILE=$3
LOGFILE=$4

if [ -e $COPASISE ];then
  if [ -e $FILENAME ];then
    $COPASISE --importSBML ${FILENAME} --oldExportSBML ${OUTFILE} 2>&1 | sed '1,4d' > ${LOGFILE}
  fi
fi
