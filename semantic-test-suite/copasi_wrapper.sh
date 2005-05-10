#!/bin/bash

SBMLFILE=$1
CONVERTER=/home/sven/copasi/copasi_dev/sbml2copasi
COPASI_OUTFILE=${SBMLFILE%%.xml}.cps
ADD_INFO_SCRIPT=/home/sven/copasi/copasi_dev/addTestSuiteInfo.py
shift 1
TASK_ARGS=${*}
COPASI="/home/sven/copasi/copasi_dev/copasi/CopasiSE/CopasiSE -c ."

#echo $TASK_ARGS

# convert sbml file
#$CONVERTER $SBMLFILE $COPASI_OUTFILE
rm $COPASI_OUTFILE
$COPASI --importSBML $SBMLFILE --save $COPASI_OUTFILE

#add task and report information to copasi file
$ADD_INFO_SCRIPT $COPASI_OUTFILE $TASK_ARGS

# run copasi command line version
$COPASI $COPASI_OUTFILE
