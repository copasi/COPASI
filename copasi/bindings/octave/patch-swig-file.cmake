# Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

if (NOT FILENAME OR NOT EXISTS ${FILENAME})
  message(FATAL_ERROR "Please specify the filename to the file to patch")
endif()

file(READ "${FILENAME}" SOURCECODE)

file(WRITE  "${FILENAME}" "// patched by cmake, all manual changes to this file will be lost\n")


file(APPEND "${FILENAME}" "${SOURCECODE}")

message (STATUS "Patched Octave Wrapper")
