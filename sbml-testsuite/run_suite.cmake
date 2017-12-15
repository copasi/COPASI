# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 


if ("${CASES_DIR}" STREQUAL "" OR 
    "${OUT_DIR}" STREQUAL "" OR 
    "${FILE_SEP}" STREQUAL "" OR 
    "${WRAPPER_EXECUTABLE}" STREQUAL "" OR 
    "${JAVA_EXECUTABLE}" STREQUAL "" )

   message(FATAL_ERROR 
"
  Need the following parameters: 
    - CASES_DIR: the directory containing the SBML test suite 
                 usually ends with cases/semantic
    - SRC_DIR:   the source directory
    - OUT_DIR:   the directory where to place the output
    - FILE_SEP:  the file separator to use
    - WRAPPER_EXECUTABLE: full filename of the wrapper executable
    - JAVA_EXECUTABLE: java executable executable

")

endif()

if (NOT EXISTS ${OUT_DIR})
  file(MAKE_DIRECTORY ${OUT_DIR})
endif()

string(REPLACE " " "" UNSUPPORTED ${UNSUPPORTED})
string(REPLACE ";" "," UNSUPPORTED ${UNSUPPORTED})
string(REPLACE "\"" "" UNSUPPORTED ${UNSUPPORTED})

if ("${UNSUPPORTED}" STREQUAL "")
  set (UNSUPPORTED "AlgebraicRule,CSymbolDelay,CSymbolRateOf,AssignedVariableStoichiometry,FastReaction, VolumeConcentrationRates,L3v2MathML,BoolNumericSwap,fbc")
endif()

if (UNSUPPORTED)
message(STATUS "Not supporting: '${UNSUPPORTED}'")
endif()

if ("${SBML_LEVEL}" STREQUAL "")
  set(SBML_LEVEL 3)
endif()

if ("${SBML_VERSION}" STREQUAL "")
  set(SBML_VERSION 1)
endif()

if ("${NUM_TRHEADS}" STREQUAL "")
  set(NUM_TRHEADS 8)
endif()


file(TO_NATIVE_PATH ${SRC_DIR}/testsuite-core.jar JAR_FILE_TESTSUITE)
file(TO_NATIVE_PATH ${SRC_DIR}/simple-xml-2.6.4.jar JAR_FILE_XML)

if (NOT "${FILE_SEP}" STREQUAL ":" AND NOT "${FILE_SEP}" STREQUAL "\":\"")
set (FILE_SEP ";")
endif()


set(CLASSPATH ".${FILE_SEP}${JAR_FILE_XML}${FILE_SEP}${JAR_FILE_TESTSUITE}${FILE_SEP}.")
string(REPLACE "\"" "" CLASSPATH "${CLASSPATH}")

set(NAME "COPASI${VERSION}")
if (NOT "${VERSION}" STREQUAL "")
set(NAME "COPASI ${VERSION}")
endif()

# initialize test suite if needed
message(STATUS "initialize testsuite")

execute_process(
  COMMAND "${JAVA_EXECUTABLE}"
    -cp "${CLASSPATH}"
    initalizeSuite ${CASES_DIR} ${SBML_LEVEL} ${SBML_VERSION}
  WORKING_DIRECTORY "${SRC_DIR}"
  OUTPUT_QUIET
)

message(STATUS "remove wrapper ${NAME} if it exists")
execute_process(
  COMMAND "${JAVA_EXECUTABLE}"
    -cp "${CLASSPATH}"
    removeWrapper "${NAME}"
  WORKING_DIRECTORY "${SRC_DIR}"
  OUTPUT_QUIET
)

message(STATUS "add wrapper ${NAME}")
execute_process(
  COMMAND "${JAVA_EXECUTABLE}"
    -cp "${CLASSPATH}"
    addWrapper 
    "${NAME}"
    ${WRAPPER_EXECUTABLE}
    ${OUT_DIR}
    "${UNSUPPORTED}"
    "%d %n %o %l %v"
  WORKING_DIRECTORY "${SRC_DIR}"
  OUTPUT_QUIET
)

SET (SBML "SBML L${SBML_LEVEL}V${SBML_VERSION}")
if ("${SBML_LEVEL}" STREQUAL "0" AND "${SBML_VERSION}" STREQUAL "0")
SET (SBML "highest available SBML L/V")
endif()


message(STATUS "run wrapper ${NAME} with #threads:${NUM_TRHEADS} for ${SBML}")
execute_process(
  COMMAND "${JAVA_EXECUTABLE}"
    -cp "${CLASSPATH}"
    runSupportedParallel "${NAME}"
    ${NUM_TRHEADS} ${SBML_LEVEL} ${SBML_VERSION}
  WORKING_DIRECTORY "${SRC_DIR}"
)

if (REMOVE_WRAPPER)
message(STATUS "remove wrapper ${NAME}")
execute_process(
  COMMAND "${JAVA_EXECUTABLE}"
    -cp "${CLASSPATH}"
    removeWrapper "${NAME}"
  WORKING_DIRECTORY "${SRC_DIR}"
  OUTPUT_QUIET
)
endif()
