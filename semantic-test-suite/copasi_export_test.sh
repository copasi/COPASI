#!/bin/bash


BASEDIR=/Users/ralph/eclipse/workspace/copasi_work/
SBMLFILE=$1
COPASI_OUTFILE=${SBMLFILE%%.xml}.cps
ADD_INFO_SCRIPT=$BASEDIR/semantic-test-suite/addTestSuiteInfo.py
shift 1
TASK_ARGS=${*}
COPASI="$BASEDIR/copasi/CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE -c ."

#echo $TASK_ARGS

# convert sbml file
echo -e "\n"

if [ -e $COPASI_OUTFILE ];then rm $COPASI_OUTFILE; fi
if [ -e ./tmp.cps ];then rm ${COPASI_OUTFILE}-tmp.cps; fi
if [ -e ./tmp.xml ];then rm ${SBMLFILE}-tmp.xml; fi


echo -e "$COPASI --importSBML $SBMLFILE --save $COPASI_OUTFILE\n"
$COPASI --importSBML $SBMLFILE --save ${COPASI_OUTFILE}-tmp.cps  &> /dev/null

#add task and report information to copasi file
if [ -e ${COPASI_OUTFILE}-tmp.cps ];then
  $COPASI --exportSBML ${SBMLFILE}-tmp.xml ${COPASI_OUTFILE}-tmp.cps &> /dev/null
else
  echo -e "ERROR: Could not create copasi file from \"$SBMLFILE\"\n";
  exit 1;	
fi
if [ -e ${SBMLFILE}-tmp.xml ];then
  $COPASI --importSBML ${SBMLFILE}-tmp.xml --save $COPASI_OUTFILE &> /dev/null
else
  echo -e "ERROR: Could not reimport exported SBML file. ($SBMLFILE)\n";
  exit 1;	  
fi
if [ -e $COPASI_OUTFILE ];then

  echo -e "$ADD_INFO_SCRIPT $COPASI_OUTFILE $TASK_ARGS\n" 
  $ADD_INFO_SCRIPT $COPASI_OUTFILE $TASK_ARGS 

  # run copasi command line version
  echo -e "$COPASI $COPASI_OUTFILE\n"
  $COPASI $COPASI_OUTFILE &> /dev/null
else
  echo -e "ERROR: Failed to create Copasi file \"$COPASI_OUTFILE\".\n"
fi
