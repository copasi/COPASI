# Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
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

# add COPASI version to wrapper file
if (VERSION)
file(APPEND  "${WRAPPER_FILE}" "\n__version__ = '${VERSION}'\n")
endif()


#now read the file again and create a python 3 version of it. 

file(READ "${WRAPPER_FILE}" SOURCECODE)

foreach(class 
   CObjectInterface
   CUnitComponent
   CUnit
   COutputInterface
   CScanItem
   
   )
string(REPLACE 
  "class ${class}(_object):"
  "class ${class}(_object, metaclass=AutoProperty):"
  SOURCECODE ${SOURCECODE}
)

string(REPLACE 
  "class ${class}(object):"
  "class ${class}(object, metaclass=AutoProperty):"
  SOURCECODE ${SOURCECODE}
)

endforeach()

file(WRITE "${BIN_DIRECTORY}/COPASI3.py" "${SOURCECODE}")
