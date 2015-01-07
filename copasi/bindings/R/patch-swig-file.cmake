# Copyright (C) 2012 - 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

if (NOT FILENAME OR NOT EXISTS ${FILENAME})
  message(FATAL_ERROR "Please specify the filename to the file to patch")
endif()

execute_process(COMMAND sed 
          -f 
             ${SRC_DIR}/sedscript.txt -i
           "${FILENAME}"
           )

file(READ "${FILENAME}" SOURCECODE)

string(REPLACE "'get''get'" "'get','get'" SOURCECODE "${SOURCECODE}" )
string(REPLACE "'get''get'" "'get','get'" SOURCECODE "${SOURCECODE}" )
string(REPLACE "'get''get'" "'get','get'" SOURCECODE "${SOURCECODE}" )
string(REPLACE "if ( &&" "if (" SOURCECODE "${SOURCECODE}" )
string(REPLACE "if ()" "if(TRUE)" SOURCECODE "${SOURCECODE}" )

file(WRITE "${FILENAME}" "${SOURCECODE}")
message (STATUS "Patched COPASI.R")
