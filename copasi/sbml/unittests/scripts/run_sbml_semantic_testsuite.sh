#!/bin/bash

if [ -x /bin/uname ];then
  UNAME=/bin/uname
else
  UNAME=/usr/bin/uname
fi

SYSTEM=`${UNAME} -s`

if [ ${SYSTEM} == "Darwin" ];then
  GREP=/usr/bin/grep
  # the testsuite does not work with apple sed without modifications
  # so we have to somehow make sure gsed is called
  # I haven't found a way to do this in this script yet
  SED=/usr/bin/sed
else
  GREP=/bin/grep
  SED=/bin/sed
fi


VALGRIND_NUMCALLERS=30
VALGRIND=/usr/bin/valgrind
TPUT=/usr/bin/tput
READ=/usr/bin/read
CAT=/bin/cat

if [ -z $TMP_DIR ];then
  TMP_DIR=/tmp/
fi

if [ -z $USE_VALGRIND ];then
  USE_VALGRIND=no
fi

if [ -z $DO_LEAKCHECK ];then
  DO_LEAKCHECK=no
fi

if [ -z $SBML_SEMANTIC_TESTSUITE_WRAPPER ];then
  if [ "$SYSTEM" == "Darwin" ];then
    SBML_SEMANTIC_TESTSUITE_WRAPPER=../../../../semantic-test-suite/semantic-test-suite.app/Contents/MacOS/semantic-test-suite
  else
    SBML_SEMANTIC_TESTSUITE_WRAPPER=../../../../semantic-test-suite/semantic-test-suite
  fi
fi

# if the wrapper has a relative path, we have to convert it to an absolute path
if [ ${SBML_SEMANTIC_TESTSUITE_WRAPPER:0:1} != "/" ];then
  SBML_SEMANTIC_TESTSUITE_WRAPPER=`pwd`/${SBML_SEMANTIC_TESTSUITE_WRAPPER}
fi

if [ -z ${SBML_SEMANTIC_TESTSUITE_DIR} ];then
 SBML_SEMANTIC_TESTSUITE_DIR=../../../../semantic-test-suite
fi

if [ -z ${SBML_SEMANTIC_TESTSUITE_LIST} ];then
    SBML_SEMANTIC_TESTSUITE_LIST=../../../../semantic-test-suite/copasitestlist.txt
fi

if [ ${SBML_SEMANTIC_TESTSUITE_LIST:0:1} != "/" ];then
  SBML_SEMANTIC_TESTSUITE_LIST=`pwd`/${SBML_SEMANTIC_TESTSUITE_LIST}
fi  

VALGRIND_OPTIONS="--num-callers=${VALGRIND_NUMCALLERS} ${VALGRIND_OPTIONS}"

source ./utilities.sh

function analyse_single_test
{
    if [ $# -ne 4 ];then
      echo "Error. analyse_single_run takes exactly 4 arguments."
      return 1
    fi
    RESULT_FILE=$1
    ERROR_FILE=$2
    VALGRIND_LOG=$3
    OUTPUT_DIR=$4
    # check if the output file is there
    if [ ! -f ${OUTPUT_DIR}/${RESULT_FILE} ];then
        echo "Error. No result file found at \"${OUTPUT_DIR}/${RESULT_FILE}\"."
        return 1;
    fi
    # check if the error file is there
    if [ ! -f ${OUTPUT_DIR}/${ERROR_FILE} ];then
        echo "Error. No result file found at \"${OUTPUT_DIR}/${ERROR}\"."
        return 1;
    fi
    # check if the error file is empty
    if [ -s ${OUTPUT_DIR}/${ERROR_FILE} ];then
        return 2;
    fi
    
    # check if valgrind was used and make the valgrind checks
    if [ -z "$USE_VALGRIND" ];then
      check_valgrind_errors ${OUTPUT_DIR}/${VALGRIND_LOG}
      return $?
    fi
    return 0
}

function analyse_complete_testrun
{
    if [ ! -s ${OUTPUT_DIR}/${OUTPUT_FILE} ];then
        return 1;
    fi
    # TODO get a summary from the result file
    # valgrind doesn't make a lot of sense here
    #if [ "$USE_VALGRIND" == "yes" ];then
    #  # additional valgrind checks
    #  check_valgrind_errors ${OUTPUT_DIR}/${VALGRIND_LOG}
    #  return $?
    #fi
}

function run-single-test
{
    if [ $# != 2 ];then
        echo "Error. run-single-test expects exactly two arguments.";
        return 1;
    fi
    TESTFILE=$1
    OUTPUT_DIR=$2
    # check if the test exists
    if [ ! -f ${SBML_SEMANTIC_TESTSUITE_DIR}/${TESTFILE} ];then
      echo "Error. Could not find testfile at \"${SBML_SEMANTIC_TESTSUITE_DIR}/${TESTFILE}\""
      return 1
    fi
    NAME=${TESTFILE##*/}
    NAME=${NAME%%.test}
    DIR=${TESTFILE%/*}
    OUTPUT_FILE=${NAME}.testsuite.out
    COMMAND_FILE=${NAME}.testsuite.sh
    ERROR_FILE=${NAME}.testsuite.err
    VALGRIND_LOG=${NAME}.testsuite.log
    OLD_PWD=`pwd`
    if [ "$USE_VALGRIND" == "yes" ];then
       # since test.bsh expects a single argument for the wrapper, passing al
       # the valgrind stuff directly does not work. We have to have a script
       # that does this
       VALGRIND_WRAPPER_SCRIPT=${OLD_PWD}/run_sbml_testsuite_wrapper_in_valgrind.sh
       export VALGRIND=${VALGRIND}
       if [ ${OUTPUT_DIR} == "/" ];then
         export VALGRIND_ALL_OPTIONS="${VALGRIND_OPTIONS} --log-file-exactly=${OUTPUT_DIR}/${VALGRIND_LOG}"
       else
         export VALGRIND_ALL_OPTIONS="${VALGRIND_OPTIONS} --log-file-exactly=${OLD_PWD}/${OUTPUT_DIR}/${VALGRIND_LOG}"
       fi
       export REAL_WRAPPER=$SBML_SEMANTIC_TESTSUITE_WRAPPER
       COMMAND="test.bsh ${VALGRIND_WRAPPER_SCRIPT} ${TESTFILE}"
    else   
       COMMAND="test.bsh "${SBML_SEMANTIC_TESTSUITE_WRAPPER}" ${TESTFILE}"
    fi
    # run the test
    cd ${SBML_SEMANTIC_TESTSUITE_DIR}
    # remove an existing result file 
    rm -rf ${DIR}/testout.csv
    if [ ${OUTPUT_DIR:0:1} == "/" ];then
      echo "$COMMAND" > ${OUTPUT_DIR}/${COMMAND_FILE}
      $COMMAND > ${OUTPUT_DIR}/${OUTPUT_FILE} 2> ${OUTPUT_DIR}/${ERROR_FILE}
      if [ $? -ne 0 ];then
       cd ${OLD_PWD}
       return 1
      fi 
    else
      echo "$COMMAND" > ${OLD_PWD}/${OUTPUT_DIR}/${COMMAND_FILE}
      $COMMAND > ${OLD_PWD}/${OUTPUT_DIR}/${OUTPUT_FILE} 2> ${OLD_PWD}/${OUTPUT_DIR}/${ERROR_FILE}
      if [ $? -ne 0 ];then
       cd ${OLD_PWD}
       return 1
      fi 
    fi  
    cd ${OLD_PWD}
    analyse_single_test ${OUTPUT_FILE} ${ERROR_FILE} ${VALGRIND_LOG} ${OUTPUT_DIR}
    return $? 
}

function run-sbml-semantic-testsuite
{
    if [ $# != 1 ];then
        echo "Error. run-sbml-semantic-testsuite expects exactly one argument.";
        return 1;
    fi
    OUTPUT_DIR=$1
    # we only need one output file since we want to see to which test the
    # errors belong
    OUTPUT_FILE=${NAME}.testsuite.out
    VALGRIND_LOG=${NAME}.testsuite.log
    # run the tests
    COMMAND="runthroughtests.awk -v wrapper=\"${SBML_SEMANTIC_TESTSUITE_WRAPPER}\" ${SBML_SEMANTIC_TESTSUITE_LIST}"
    OLD_PWD=`pwd`
    cd ${SBML_SEMANTIC_TESTSUITE_DIR}
    $COMMAND &> ${OUTPUT_DIR}/${OUTPUT_FILE}
    # check if the output file has been generated and has a size different from 0
    cd ${OLD_PWD}
    analyse_complete_testrun;
    return $?
}

function run_testlist
{
   if [ $# -ne 2 ];then
      echo "Error. run_testlist takes exactly two arguments."
      return 1
   fi
   TESTLIST=$1
   OUTPUT_DIR=$2
   # go through the testlist line by line
   # each line that start with TEST is a test
   # each line that start with CATEGORY is a new category
   # all other lines are ignored
   CATEGORY_NAME="" 
   CATEGORY_COUNT=0 
   CATEGORY_FAILED=0 
   CATEGORY_PASSED=0 
   CATEGORY_SUCCEEDED=0 
   COUNT=0 
   NUM_PASSED=0 
   NUM_FAILED=0 
   NUM_SUCCEEDED=0 
   while read LINE; do
      if [ "${LINE:0:5}" == "TEST " ];then
        CATEGORY_COUNT=$(($CATEGORY_COUNT + 1));
        TESTNAME=${LINE:5}
        NAME=${TESTNAME##*/}
        NAME=${NAME%%.test}
        ERROR_FILE=${NAME}.testsuite.err
        VALGRIND_LOG=${NAME}.testsuite.log
        echo -n "Running test ${TESTNAME} ... "
        run-single-test $TESTNAME $OUTPUT_DIR
        # generate output according to result from run-single-test
        case $? in
        0 )
            echo -n -e '\E[32;47mOK';
            ${TPUT} sgr0;
            echo -n -e "\n";
            CATEGORY_PASSED=$((${CATEGORY_PASSED} + 1));
            ;;
        1 )
            echo -n -e '\E[31;47mFAILED';
            ${TPUT} sgr0;
            echo -n -e  "\n";
            CATEGORY_FAILED=$((${CATEGORY_FAILED} + 1));
            ;;
        2 )
            echo -n -e '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nThere was additional output from the test. Check ${OUTPUT_DIR}/${ERROR_FILE} for details.";
            CATEGORY_SUCCEEDED=$((${CATEGORY_SUCCEEDED} + 1));
            ;;
        102 ) 
            echo -n -e '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported errors. Check ${OUTPUT_DIR}/${VALGRIND_LOG} for details.";
            CATEGORY_SUCCEEDED=$((${CATEGORY_SUCCEEDED} + 1));
            ;;
        103 ) 
            echo -n -e '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported errors and memory leaks. Check ${OUTPUT_DIR}/${VALGRIND_LOG}.";
            CATEGORY_SUCCEEDED=$((${CATEGORY_SUCCEEDED} + 1));
            ;;
        104 ) 
            echo -e -n '\E[33;47mSUCCEDED';
            ${TPUT} sgr0;
            echo -e "\nValgrind reported memory leaks. Check ${OUTPUT_DIR}/${VALGRIND_LOG} for details.";
            CATEGORY_SUCCEEDED=$((${CATEGORY_SUCCEEDED} + 1));
            ;;
        * )
            echo -n -e '\E[31;47mFAILED';
            ${TPUT} sgr0;
            echo -e "\nAn unknown error code was reported from run-single-test.";
            CATEGORY_FAILED=$((${CATEGORY_FAILED} + 1));
            ;;
        esac
      fi
      if [ "${LINE:0:9}" == "CATEGORY " ];then
        if [ ! -z "${CATEGORYNAME}" ];then
          NUM_PASSED=$((${NUM_PASSED} + ${CATEGORY_PASSED}));
          NUM_FAILED=$((${NUM_FAILED} + ${CATEGORY_FAILED}));
          NUM_SUCCEEDED=$((${NUM_SUCCEEDED} + ${CATEGORY_SUCCEEDED}));
          COUNT=$((${COUNT} + ${CATEGORY_COUNT})); 
          echo -e "\nOut of ${CATEGORY_COUNT} tests in category ${CATEGORYNAME} ${CATEGORY_PASSED} passed, ${CATEGORY_SUCCEEDED} succeeded and ${CATEGORY_FAILED} failed."
        fi
        CATEGORY_PASSED=0;
        CATEGORY_FAILED=0;
        CATEGORY_SUCCEEDED=0;
        CATEGORY_COUNT=0;
        CATEGORYNAME=${LINE:9}
        echo -e "\nRunning tests in category $CATEGORYNAME ..."
      fi
    done <${TESTLIST}
    NUM_PASSED=$((${NUM_PASSED} + ${CATEGORY_PASSED}));
    NUM_FAILED=$((${NUM_FAILED} + ${CATEGORY_FAILED}));
    NUM_SUCCEEDED=$((${NUM_SUCCEEDED} + ${CATEGORY_SUCCEEDED}));
    COUNT=$((${COUNT} + ${CATEGORY_COUNT})); 
    echo -e "\nOut of ${CATEGORY_COUNT} tests in category ${CATEGORYNAME} ${CATEGORY_PASSED} passed, ${CATEGORY_SUCCEEDED} succeeded and ${CATEGORY_FAILED} failed."
    echo -e "\nOut of ${COUNT} tests ${NUM_PASSED} passed, ${NUM_SUCCEEDED} succeeded and ${NUM_FAILED} failed.\n\n"
}

# enable leak checking in valgrind if requested
if [ "${DO_LEAKCHECK}" == "yes" ];then
    VALGRIND_OPTIONS="${VALGRIND_OPTIONS} --leak-check=full"
fi

# check if valgrind is there if needed
if [ ${USE_VALGRIND} == "yes" ]; then
   # todo check if the valgrind executable exists
   check_executable $VALGRIND || exit 1; 
fi

# check if tput is there
check_executable $TPUT || exit 1;

# check if grep is there
#check_executable $GREP || exit 1;

# check if the testsuite wrapper is there
check_executable ${SBML_SEMANTIC_TESTSUITE_WRAPPER} || exit 1;

# check if TMP_DIR is present, a directry and writable
if [ -d $TMP_DIR ];then
    touch ${TMP_DIR}/test.test
    if [ $? != 0 ];then
        echo "Error. Can not write to ${TMP_DIR}."
        exit 1
    else
      rm ${TMP_DIR}/test.test
    fi
else
    echo "Error. ${TMP_DIR} is not a directory."
    exit 1;
fi

# check if the testuite directory is there
if [ ! -d ${SBML_SEMANTIC_TESTSUITE_DIR} ];then
    echo "Error. Testsuite directory not found at ${SBML_SEMANTIC_TESTSUITE_DIR}.";
    exit 1;
fi
# check if it contains the directory with the scripts
if [ ! -d ${SBML_SEMANTIC_TESTSUITE_DIR}/AUTOMATION ];then
    echo "Error. Testsuite scripts directory not found at ${SBML_SEMANTIC_TESTSUITE_DIR}/AUTOMATION.";
    exit 1;
fi
# delete the temp dir in case the last run was interupted
rm -rf ${SBML_SEMANTIC_TESTSUITE_DIR}/temp

# check if the testlist is there and readable
if [ -f ${SBML_SEMANTIC_TESTSUITE_LIST} ];then
    if [ -r ${SBML_SEMANTIC_TESTSUITE_LIST} ];then
        if [ ! -s ${SBML_SEMANTIC_TESTSUITE_LIST} ];then
            echo "Error. Testlist at ${SBML_SEMANTIC_TESTSUITE_LIST} is empty.";
            exit 1;
        fi
    else
      echo "Error. Testlist at ${SBML_SEMANTIC_TESTSUITE_LIST} not readable.";
      exit 1;
    fi
else
  echo "Error. Testlist not found at ${SBML_SEMANTIC_TESTSUITE_LIST} or it is not a regular file."
  exit 1
fi
# extend the path to include the scripts directory
# the path needs to be an absolute path
if [ ${SBML_SEMANTIC_TESTSUITE_DIR:0:1} != "/" ];then
  PATH=$PATH:`pwd`/${SBML_SEMANTIC_TESTSUITE_DIR}/AUTOMATION
else
  PATH=$PATH:${SBML_SEMANTIC_TESTSUITE_DIR}/AUTOMATION
fi

run_testlist ${SBML_SEMANTIC_TESTSUITE_LIST} ${TMP_DIR}
exit $?
