#!/bin/bash

# TODO add the possibility to run the tests in valgrind by having a method that
# runs a single test

#VALGRIND_NUMCALLERS=30
#GREP=/bin/grep
#VALGRIND=/usr/bin/valgrind
UNAME=/bin/uname
#TPUT=/usr/bin/tput

SYSTEM=`${UNAME} -s`

if [ -z $TMP_DIR ];then
  TMP_DIR=/tmp/
fi

#if [ -z $USE_VALGRIND ];then
#  USE_VALGRIND=no
#fi

#if [ -z $DO_LEAKCHECK ];then
#  DO_LEAKCHECK=no
#fi

if [ -z $SBML_SEMANTIC_TESTSUITE_WRAPPER ];then
  if [ "$SYSTEM" == "Darwin" ];then
    SBML_SEMANTIC_TESTSUITE_WRAPPER=../../../../semantic-test-suite/semantic-test-suite.app/Contents/MacOS/semantic-test-suite
  else
    SBML_SEMANTIC_TESTSUITE_WRAPPER=../../../../semantic-test-suite/semantic-test-suite
  fi
fi

if [ -z ${SBML_SEMANTIC_TESTSUITE_DIR} ];then
 SBML_SEMANTIC_TESTSUITE_DIR=../../../../semantic-test-suite
fi

if [ -z ${SBML_SEMANTIC_TESTSUITE_LIST} ];then
    SBML_SEMANTIC_TESTSUITE_LIST=../../../../semantic-test-suite/copasitestlist.txt
fi

#VALGRIND_OPTIONS="--num-callers=${VALGRIND_NUMCALLERS} ${VALGRIND_OPTIONS}"

source ./utilities.sh

function analyse_testrun
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

function run-sbml-semantic-testsuite
{
    # we pass all the commands as parameters so we don't have to check
    # for their existence in each call. Thoses checks have to be done by the
    # caller
    if [ $# != 1 ];then
        echo "Error. test_import_single_file expects exactly one argument.";
        return 1;
    fi
    OUTPUT_DIR=$1
    # we only need one output file since we want to see to which test the
    # errors belong
    OUTPUT_FILE=${NAME}.testsuite.out
    VALGRIND_LOG=${NAME}.testsuite.log
    # run the tests
    COMMAND="runthroughtests.awk -vwrapper=\"${SBML_SEMANTIC_TESTSUITE_WRAPPER}\" ${SBML_SEMANTIC_TESTSUITE_LIST}"
    # valgrind doesn't make much sense in this context
    #if [ "$USE_VALGRIND" == "yes" ];then
    #   COMMAND="${VALGRIND} ${VALGRIND_OPTIONS} --log-file=${OUTPUT_DIR}/${VALGRIND_LOG} ${COMMAND}"
    #fi
    $COMMAND &> ${OUTPUT_DIR}/${OUTPUT_FILE}
    # check if the output file has been generated and has a size different from 0
    analyse_testrun;
    return $?
}

# enable leak checking in valgrind if requested
#if [ "${DO_LEAKCHECK}" == "yes" ];then
#    VALGRIND_OPTIONS="${VALGRIND_OPTIONS} --leak-check=full"
#fi

# check if valgrind is there if needed
#if [ ${USE_VALGRIND} == "yes" ]; then
#   # todo check if the valgrind executable exists
#   check_executable $VALGRIND || exit 1; 
#fi

# check if tput is there
#check_executable $TPUT || exit 1;

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
if [! -d ${SBML_SEMANTIC_TESTSUITE_DIR} ];then
    echo "Error. Testsuite directory not found at ${SBML_SEMANTIC_TESTSUITE_DIR}.";
    return 1;
fi
# check if it contains the directory with the scripts
if [! -d ${SBML_SEMANTIC_TESTSUITE_DIR}/AUTOMATION ];then
    echo "Error. Testsuite scripts directory not found at ${SBML_SEMANTIC_TESTSUITE_DIR}/AUTOMATION.";
    return 1;
fi
# check if the testlist is there and readable
if [ -f ${SBML_SEMANTIC_TESTSUITE_LIST} ];then
    if[ -r ${SBML_SEMANTIC_TESTSUITE_LIST} ];then
        if [! -s ${SBML_SEMANTIC_TESTSUITE_LIST} ];then
            echo "Error. Testlist at ${SBML_SEMANTIC_TESTSUITE_LIST} is empty.";
            return 1;
        fi
    else
      echo "Error. Testlist at ${SBML_SEMANTIC_TESTSUITE_LIST} not readable.";
      return 1;
    fi
else
  echo "Error. Testlist not found at ${SBML_SEMANTIC_TESTSUITE_LIST} or it is not a regular file."
  return 1
fi
# extend the path to include the scripts directory
PATH=$PATH:${SBML_SEMANTIC_TESTSUITE_DIR}/AUTOMATION

run-sbml-semantic-testsuite

