#!/bin/bash

SBMLFILE=$1

BASEDIR=/home/ralph/workspace/copasi_work/

COPASI_OUTFILE=${SBMLFILE%%.xml}.cps
ADD_INFO_SCRIPT=$BASEDIR/semantic-test-suite/addTestSuiteInfo.py
shift 1
TASK_ARGS=${*}
COPASI="$BASEDIR/copasi/CopasiSE/CopasiSE -c ."

#echo $TASK_ARGS

# convert sbml file
if [ -e $COPASI_OUTFILE ];then rm $COPASI_OUTFILE; fi
echo -e "$COPASI --importSBML $SBMLFILE --save $COPASI_OUTFILE\n"

$COPASI --importSBML $SBMLFILE --save $COPASI_OUTFILE &> /dev/null

if [ -e $COPASI_OUTFILE ];then
  #add task and report information to copasi file
  echo -e "$ADD_INFO_SCRIPT $COPASI_OUTFILE $TASK_ARGS\n" 

  $ADD_INFO_SCRIPT $COPASI_OUTFILE $TASK_ARGS 

  # run copasi command line version
  echo -e "$COPASI $COPASI_OUTFILE\n"
  $COPASI $COPASI_OUTFILE &> /dev/null
else
  echo -e "ERROR: Failed to create Copasi file \"$COPASI_OUTFILE\".\n"
fi
