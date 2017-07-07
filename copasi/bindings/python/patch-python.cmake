# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

#
# Description       : CMake script patching SWIG wrappers
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#


# patch python wrapper file 
set (WRAPPER_FILE "${BIN_DIRECTORY}/COPASI.py")

if (NOT EXISTS ${WRAPPER_FILE})
  message(FATAL_ERROR "Wrapper file does not exist")
endif()

message(STATUS "Patching Python wrapper")

file(READ "${WRAPPER_FILE}" SOURCECODE)

file(WRITE "${WRAPPER_FILE}" "
# import statement needed on some systems
import sys
import os.path
sys.path.append(os.path.dirname(__file__))
")
file(APPEND  "${WRAPPER_FILE}" "${SOURCECODE}")
