# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

#
# Description       : CMake script patching SWIG wrappers
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#


# patch c++ wrapper file 
set (WRAPPER_FILE "${BIN_DIRECTORY}/copasi_wrapper.cpp")

if (NOT EXISTS ${WRAPPER_FILE})
  message(FATAL_ERROR "Wrapper file does not exist")
endif()

message(STATUS "Patching C++ wrapper")

file(READ "${WRAPPER_FILE}" SOURCECODE)

string(REPLACE "enum CTaskEnum::Method," "CTaskEnum::Method," SOURCECODE "${SOURCECODE}" )
string(REPLACE "enum CTaskEnum::Method " "CTaskEnum::Method " SOURCECODE "${SOURCECODE}" )
string(REPLACE "enum CTaskEnum::Task " "CTaskEnum::Task " SOURCECODE "${SOURCECODE}" )
string(REPLACE "enum CTaskEnum::Task," "CTaskEnum::Task," SOURCECODE "${SOURCECODE}" )

file(WRITE "${WRAPPER_FILE}" "${SOURCECODE}")
