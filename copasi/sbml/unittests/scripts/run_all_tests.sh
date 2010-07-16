#!/bin/bash

# common parameters

if [ -x /bin/uname ];then
  UNAME=/bin/uname
else
  UNAME=/usr/bin/uname
fi

SYSTEM=`${UNAME} -s`

DATE=/bin/date
MKDIR=/bin/mkdir

# set TMP_DIR to HOME so that we don't fill up /tmp by accident
TMP_DIR=${TMP_DIR:="$HOME"}

USE_VALGRIND=${USE_VALGRIND:="no"}

DO_LEACKCHECK=${DO_LEAKCHECK:="no"}

DO_NONCURATED=${DO_NONCURATED:="yes"}
TARGET_SBML_VERSION=${TARGET_SBML_VERSION:=""} # use the defaul export version

if [ -z $COPASISE ];then
  if [ "$SYSTEM" == "Darwin" ];then
    COPASISE=../../../CopasiSE/CopasiSE.app/Contents/MacOS/CopasiSE
  else
    COPASISE=../../../CopasiSE/CopasiSE
  fi
fi

COPASISE_OPTIONS=${COPASISE_OPTIONS:="--nologo --verbose"}

# parameters for import test
BIOMODELS_DIR=${BIOMODELS_DIR:=${HOME}/workspace/release_21August2008_sbmls}
MODEL_DIR=${MODEL_DIR:=${BIOMODELS_DIR}/curated/}

# parameters for export test
CPS_DIR=${CPS_DIR:=""}

# parameters for roundtripping test


# parameters for semantic testsuite test


# parameters for stochastic testsuite test
if [ -z $SBML_SEMANTIC_TESTSUITE_WRAPPER ];then
  if [ "$SYSTEM" == "Darwin" ];then
    SBML_SEMANTIC_TESTSUITE_WRAPPER=../../../../semantic-test-suite/semantic-test-suite.app/Contents/MacOS/semantic-test-suite
  else
    SBML_SEMANTIC_TESTSUITE_WRAPPER=../../../../semantic-test-suite/semantic-test-suite
  fi
fi

SBML_SEMANTIC_TESTSUITE_DIR=${SBML_SEMANTIC_TESTSUITE_DIR:="../../../../semantic-test-suite/semantic-test-suite"}

SBML_SEMANTIC_TESTSUITE_LIST=${SBML_SEMANTIC_TESTSUITE_LIST:="../../../../semantic-test-suite/copasitestlist.txt"}

# 10000 iterations is the recommended number by the testsuite authors
NUM_ITERATIONS=${NUM_ITERATIONS:=10000}
STOCH_METHOD=${STOCH_METHOD:=stochastic}

if [ -z $STOCHASTIC_TESTSUITE_WRAPPER ];then
  if [ "$SYSTEM" == "Darwin" ];then
    STOCHASTIC_TESTSUITE_WRAPPER=../../../../stochastic-testsuite/stochastic-testsuite.app/Contents/MacOS/stochastic-testsuite
  else
    STOCHASTIC_TESTSUITE_WRAPPER=../../../../stochastic-testsuite/stochastic-testsuite
  fi
fi

STOCHASTIC_TESTSUITE_DIR=${STOCHASTIC_TESTSUITE_DIR:="../../../../stochastic-testsuite/dsmts23-20080307"}

ANALYSIS_SCRIPTS_DIR=${ANALYSIS_SCRIPTS_DIR:="../../../../stochastic-testsuite"}

STOCHASTIC_TESTSUITE_LIST=${STOCHASTIC_TESTSUITE_LIST:="../../../../stochastic-testsuite/copasi-model-list"}

# parameters for franks testsuite
if [ -z "$FRANKS_WRAPPER" ];then
  if [ "$SYSTEM" == "Darwin" ];then
    FRANKS_WRAPPER=../../../../franks_testsuite/franks_testsuite.app/Contents/MacOS/franks_testsuite
  else
    FRANKS_WRAPPER=../../../../franks_testsuite/franks_testsuite
  fi
fi


function run_import_tests
{
  # run the import tests on all curated biomodels files
  echo "Running import tests ..."
  echo -e "\nImporting curated models ..."
  # check if ${BIOMODELS_DIR}/curated exists
  if [ ! -d ${BIOMODELS_DIR}/curated ];then
    echo "Error. \"${BIOMODELS_DIR}/curated\" does not exist or is not a directory."
    exit 1;
  fi
  ${MKDIR} ${RESULT_DIR}/import/
  ${MKDIR} ${RESULT_DIR}/import/curated
  COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/import/curated ./test_sbml_import.sh ${BIOMODELS_DIR}/curated/*.xml
  if [ "${DO_NONCURATED}" == "yes" ];then
    echo -e "\nImporting noncurated models ..."
    # check if ${BIOMODELS_DIR}/noncurated exists
    if [ ! -d ${BIOMODELS_DIR}/noncurated ];then
      echo "Error. \"${BIOMODELS_DIR}/noncurated\" does not exist or is not a directory."
      exit 1;
    fi
    ${MKDIR} ${RESULT_DIR}/import/noncurated
    COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/import/noncurated ./test_sbml_import.sh ${BIOMODELS_DIR}/noncurated/*.xml
  fi
  echo -e "\n\n"
}

function run_export_tests
{
  # run the export test
  echo "Running export tests ..."
  # if CPS_DIR is set, we try to export the CPS files in that directory instead
  # of taking the ones created in the import test
  if [ ! -z "${CPS_DIR}" ];then
    echo -e "\nExporting COPASI models in ${CPS_DIR} ..."
    ${MKDIR} ${RESULT_DIR}/export
    if [ ! -d ${CPS_DIR} ];then
      echo "Error. \"${CPS_DIR}\" does not exist or is not a directory."
      exit 1;
    fi
    COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/export ./test_sbml_export.sh ${CPS_DIR}/*.cps

  else
    echo -e "\nExporting models created from curated biomodel files ..."
    ${MKDIR} ${RESULT_DIR}/export
    ${MKDIR} ${RESULT_DIR}/export/curated
    CPS_DIR=${RESULT_DIR}/import/curated
    if [ ! -d ${RESULT_DIR}/import/curated ];then
      echo "Error. \"${RESULT_DIR}/import/curated\" does not exist or is not a directory."
      exit 1;
    fi
    COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/export/curated ./test_sbml_export.sh ${CPS_DIR}/*.cps

    if [ "${DO_NONCURATED}" == "yes" ];then
      echo -e "\nExporting models created from noncurated biomodel files ..."
      ${MKDIR} ${RESULT_DIR}/export/noncurated
      CPS_DIR=${RESULT_DIR}/import/noncurated
      if [ ! -d ${RESULT_DIR}/import/noncurated ];then
        echo "Error. \"${RESULT_DIR}/import/noncurated\" does not exist or is not a directory."
        exit 1;
      fi
      COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/export/noncurated ./test_sbml_export.sh ${CPS_DIR}/*.cps
    fi
  fi
  echo -e "\n\n"
}

function run_roundtripping_tests
{
  # run the roundtripping test
  echo "Running roundtripping tests ..."
  echo -e "\nRoundtripping curated models ..."
  # check if ${BIOMODELS_DIR}/curated exists
  if [ ! -d ${BIOMODELS_DIR}/curated ];then
    echo "Error. \"${BIOMODELS_DIR}/curated\" does not exist or is not a directory."
    exit 1;
  fi
  ${MKDIR} ${RESULT_DIR}/roundtripping
  ${MKDIR} ${RESULT_DIR}/roundtripping/curated
  COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/roundtripping/curated ./test_sbml_roundtripping.sh ${BIOMODELS_DIR}/curated/*.xml
  
  if [ "${DO_NONCURATED}" == "yes" ];then
    echo -e "\nRoundtripping noncurated models ..."
    # check if ${BIOMODELS_DIR}/noncurated exists
    if [ ! -d ${BIOMODELS_DIR}/noncurated ];then
      echo "Error. \"${BIOMODELS_DIR}/noncurated\" does not exist or is not a directory."
      exit 1;
    fi
    ${MKDIR} ${RESULT_DIR}/roundtripping/noncurated
    COPASISE=${COPASISE} COPASISE_OPTIONS=${COPASISE_OPTIONS} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/roundtripping/noncurated ./test_sbml_roundtripping.sh ${BIOMODELS_DIR}/noncurated/*.xml
  fi
  echo -e "\n\n"
}

function run_semantic_testsuite
{
  # run the sbml_semantic_testsuite
  echo "Running SBML semantic testsuite ..."
  ${MKDIR} ${RESULT_DIR}/semantic-testsuite
  SBML_SEMANTIC_TESTSUITE_WRAPPER=${SBML_SEMANTIC_TESTSUITE_WRAPPER} SBML_SEMANTIC_TESTSUITE_DIR=${SBML_SEMANTIC_TESTSUITE_DIR} SBML_SEMANTIC_TESTSUITE_LIST=${SBML_SEMANTIC_TESTSUITE_LIST} USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/semantic-testsuite ./run_sbml_semantic_testsuite.sh
  echo -e "\n\n"
}

function run_stochastic_testsuite
{
  # run the stochastic testsuite
  echo "Running stochastic testsuite ..."
  ${MKDIR} ${RESULT_DIR}/stochastic-testsuite
  ANALYSIS_SCRIPTS_DIR=${ANALYSIS_SCRIPTS_DIR} \
  STOCHASTIC_TESTSUITE_WRAPPER=${STOCHASTIC_TESTSUITE_WRAPPER} \
  STOCHASTIC_TESTSUITE_DIR=${STOCHASTIC_TESTSUITE_DIR} \
  STOCHASTIC_TESTSUITE_LIST=${STOCHASTIC_TESTSUITE_LIST}\
  USE_VALGRIND=${USE_VALGRIND}\
  DO_LEAKCHECK="no"\
  TMP_DIR=${RESULT_DIR}/stochastic-testsuite\
  ./run_stochastic_testsuite.sh
  echo -e "\n\n"
}


function run_franks_testsuite
{
  # run franks test
  # not written yet.
  echo "Running Franks simulation test ..."
  ${MKDIR} ${RESULT_DIR}/franks
  ${MKDIR} ${RESULT_DIR}/franks/curated
  if [ ! -d ${BIOMODELS_DIR}/curated ];then
    echo "Error. \"${BIOMODELS_DIR}/curated\" does not exist or is not a directory."
    exit 1;
  fi
  USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/franks/curated ./run_franks_test.sh ${BIOMODELS_DIR}/curated/*.xml
  if [ "${DO_NONCURATED}" == "yes" ];then
    echo -e "\nSimulating noncurated models ..."
    # check if ${BIOMODELS_DIR}/noncurated exists
    if [ ! -d ${BIOMODELS_DIR}/noncurated ];then
      echo "Error. \"${BIOMODELS_DIR}/noncurated\" does not exist or is not a directory."
      exit 1;
    fi
    ${MKDIR} ${RESULT_DIR}/franks/noncurated
    USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/franks/noncurated ./run_franks_test.sh ${BIOMODELS_DIR}/noncurated/*.xml
  fi
  echo -e "\n\n"
}

function simulate_sbmlfiles
{
  # not written yet.
  echo "Running simulation ..."
  ${MKDIR} ${RESULT_DIR}/simulate
  if [ ! -d ${MODEL_DIR} ];then
    echo "Error. \"${MODEL_DIR}\" does not exist or is not a directory."
    exit 1;
  fi
  USE_VALGRIND=${USE_VALGRIND} DO_LEAKCHECK=${DO_LEAKCHECK} TMP_DIR=${RESULT_DIR}/simulate/ ./run_franks_test.sh ${MODEL_DIR}/*.xml
  echo -e "\n\n"
}

function run_all_tests
{
    run_import_tests
    run_export_tests
    run_roundtripping_tests
    run_semantic_testsuite
    run_stochastic_testsuite
    run_franks_testsuite
}

function print_help_screen
{
   echo "Usage: ./run_all_tests [import|export|importexport|roundtrip|semantic|stochastic|franks]"; 
   echo "or";
   echo "Usage: ./run_all_tests help which prints this help screen";
   echo "";
   echo "The script takes an optional list of one or more tests names to run. If no test names are given, all available tests are run.";
   echo "";
   echo "import: tries to import all SBML models in the given BIOMODELS_DIR."
   echo "export: tries to export all cps models in the given CPS_DIR to SBML."
   echo "importexport: runs the import test and then runs the export test with all cps files generated during the import test."
   echo "roundtrip: import all models from the given BIOMODELS_DIR and directly export them again without a cps file in between."
   echo "semantic: run tests from the SBML semantic testsuite."
   echo "stochastic: run tests from the stochastic testsuite."
   echo "franks: simulate all biomodels models for 10 seconds."
   echo "";
   echo "The binaries that are used to run the tests are given as variables. Each test has default values for all the variables that are used if a variable is not explicitely set by the user."
   echo "Variables that can be set are:"
   echo "";
   echo "TMP_DIR: directory where all results will be stored. The directory must exist and must be writable. Each test creates a subdirectory in that directory."
   echo "USE_VALGRIND: if set to \"yes\" all tests are run within valgrind. Only the stochastic testsuite will ot be run within valgrind because this would take to long."
   echo "DO_LEAKCHECK: only usefull if valgrind is enabled. It tells valgrind to also check for memory leaks."
   echo "FILTER_SBML_IMPORT_WARNINGS: if set to yes, warnings and errors marked as filtered in COPASI will be removed from the resulting output."
   echo "COPASISE: Path to the CopasiSE binary. This is used for the import, export and roundtripping tests."
   echo "COPASISE_OPTIONS: additional options that are passed to CopasiSE in each call."
   echo "SBML_SEMANTIC_TESTSUITE_WRAPPER: Path to the binary that is used to simulate the models for the semantic testsuite."
   echo "SBML_SEMANTIC_TESTSUITE_LIST: Path to a file with tests from the semantic testsuite to run."
   echo "SBML_SEMANTIC_TESTSUITE_DIR: Path to the top level directory of the sbml semantic testsuite."
   echo "STOCHASTIC_TESTSUITE_WRAPPER: Path to binary that is used to do the simulations for the stochastic testsuite."
   echo "STOCHASTIC_TESTSUITE_DIR: directory where the tests for the stochastic testsuite are located."
   echo "STOCHASTIC_TESTSUITE_LIST: path to file that contains a list of tests from the stochastic testsuite to run."
   echo "NUM_ITERATIONS: specifies the number of iteration for the stochastic testsuite."
   echo "ANALYSIS_SCRIPTS_DIR: path to the directory where the analysis scripts for the stochastic testsuite are located. Those are normally in the stochastic-testsuite diretory in COPASIs CVS tree."
   echo "FRANKS_WRAPPER: path to binary that is used to simulate all the biomodels files for franks testsuite."
   echo ""
   echo "Most of the variables have default values which point to directories and binaries within this CVS tree and should be OK for most people."
   echo "There is however no default value for CPS_DIR. And the location of the STOCHASTIC_TESTSUITE_DIR and the SBML_SEMANTIC_TESTSUITE_DIR will probably also vary from machine to machine."
}

if [ $# -eq 0 ];then
  # check if TMP_DIR is writable
  if [ ! -d "${TMP_DIR}" ];then
    echo "Error. \"${TMP_DIR}\" does not exist or is not a directory.";
    exit 1;
  fi
  if [ ! -w "${TMP_DIR}" ];then
    echo "Error. \"${TMP_DIR}\" is not writable.";
    exit 1;
  fi
  # create a directory for the results in TMP_DIR
  DATE_SECONDS=`$DATE "+%s"`
  RESULT_DIR=${TMP_DIR}/results-${DATE_SECONDS}
  $MKDIR ${RESULT_DIR} || exit 1 #{ echo "Error. Unable to create result directory \"${RESULT_DIR}\"."; exit 1 }
  run_all_tests
else
  if test  $# -eq 1  -a  "$1" = "help" ;then
    print_help_screen
  else
    # check if TMP_DIR is writable
    if [ ! -d "${TMP_DIR}" ];then
      echo "Error. \"${TMP_DIR}\" does not exist or is not a directory.";
      exit 1;
    fi
    if [ ! -w "${TMP_DIR}" ];then
      echo "Error. \"${TMP_DIR}\" is not writable.";
      exit 1;
    fi
    # create a directory for the results in TMP_DIR
    DATE_SECONDS=`$DATE "+%s"`
    RESULT_DIR=${TMP_DIR}/results-${DATE_SECONDS}
    $MKDIR ${RESULT_DIR} || exit 1 #{ echo "Error. Unable to create result directory \"${RESULT_DIR}\"."; exit 1 }
    TEST=$1
    while [ "${TEST}" != "" ];do
        case ${TEST} in
          import )
            run_import_tests;
            shift;
            ;;
          importexport )
            run_import_tests;
            run_export_tests;
            shift;
            ;;
          export )
            if [ -z ${CPS_DIR} ];then
                echo "Error. \"export\" given as a test to run, but the CPS_DIR variable was not set. Not running the export tests."
                echo "Either use \"importexport\" to test import of sbml files and export of the resulting cps files, or specifiy a directory that contains cps files via the CPS_DIR variable."
            else
              run_export_tests;
            fi
            shift;
            ;;
          roundtrip )
            run_roundtripping_tests;
            shift;
            ;;
          semantic )
            run_semantic_testsuite;
            shift;
            ;;
          stochastic )
            run_stochastic_testsuite;
            shift;
            ;;
          franks )
            run_franks_testsuite;
            shift;
            ;;
          simulate )
            simulate_sbmlfiles;
            shift;
            ;;
          * )
            echo "Error. invalid testname \"${TEST}\" specified. For a list of valid test names run \"./run_all_tests help\"."
            shift;
            ;;
        esac
        TEST=$1
    done
  fi
fi



