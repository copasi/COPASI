# Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 



if (NOT FILENAME OR NOT EXISTS ${FILENAME})
  message(FATAL_ERROR "Please specify the filename to the file to patch")
endif()

get_filename_component(NAME_ONLY ${FILENAME} NAME)
file(READ "${FILENAME}" SOURCECODE)

file(WRITE  "${FILENAME}" "// patched ${NAME_ONLY}\n")
file(APPEND "${FILENAME}" "#include <copasi/optimization/COptProblem.h>\n")
file(APPEND "${FILENAME}" "${SOURCECODE}")

message (STATUS "Patched ${NAME_ONLY}")
