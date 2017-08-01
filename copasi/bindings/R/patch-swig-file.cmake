# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

if (NOT FILENAME OR NOT EXISTS ${FILENAME})
  message(FATAL_ERROR "Please specify the filename to the file to patch")
endif()

#if (EXISTS "${SRC_DIR}/sedscript.txt")
#execute_process(COMMAND sed 
#          -f ${SRC_DIR}/sedscript.txt -i
#           "${FILENAME}"
#           )
#endif()

file(READ "${FILENAME}" SOURCECODE)

#string (REGEX MATCHALL "enumToInteger.*coerceIfNotSubclass" matches ${SOURCECODE})
#message("Matches:")
#foreach(match ${matches})
# message("${match}")
#endforeach()

# Fixes for swig <3.0.11
string(REPLACE "'get''get'" "'get','get'" SOURCECODE "${SOURCECODE}" )
string(REPLACE "if ( &&" "if (" SOURCECODE "${SOURCECODE}" )
string(REPLACE "if ()" "if(TRUE)" SOURCECODE "${SOURCECODE}" )

# Fixes for swig 3.0.12
string(REPLACE "if (capture.output(ans) %in% c(\"<pointer: 0x0>\", \"<pointer: (nil)>\")) return()\n  ans <- new(\"_p_size_t\", ref=ans)" "" SOURCECODE "${SOURCECODE}" )

# Changes $ operator of Copasi S4 classes to disable partial matching which can mess up calls to inherited methods.
string(REPLACE "idx = pmatch(name, names(accessorFuns));" "idx = match(name, names(accessorFuns));" SOURCECODE "${SOURCECODE}" )

# Prevents get(...) methods from falsely being categorizes as accessor functions by swig
string(REGEX REPLACE "vaccessors = c\\('(get|set)[a-zA-Z0-9_]*'" "vaccessors = c(''" SOURCECODE "${SOURCECODE}" )
string(REGEX REPLACE "vaccessors = c\\('([a-zA-Z0-9_]*)', ?'(get|set)[a-zA-Z0-9_]*'" "vaccessors = c('\\1'" SOURCECODE "${SOURCECODE}" )
string(REGEX REPLACE "vaccessors = c\\('', ?" "vaccessors = c(" SOURCECODE "${SOURCECODE}" )
string(REPLACE "vaccessors = c('')" "vaccessors = c()" SOURCECODE "${SOURCECODE}" )

# Remove broken print function for ExternalReference
string(REPLACE "setAs('ExternalReference', 'character',\nfunction(from) {if (!is.null(from\$\"__str__\")) from\$\"__str__\"()})" "" SOURCECODE "${SOURCECODE}" )
string(REPLACE "suppressMessages(suppressWarnings(setMethod('print', 'ExternalReference',\nfunction(x) {print(as(x, \"character\"))})))" "" SOURCECODE "${SOURCECODE}" )

# remove enumFrom/ToInteger code
SET(NEW_CODE "
enumToInteger <- function(name,type)
 {
    if (is.character(name)) {
    gettype <- paste(\".__E__\", type, sep = \"\")
    if (!exists(gettype)) gettype <- paste(\".__E__\", substr(type, 3, nchar(type)), sep = \"\")
    ans <- as.integer(get(gettype)[name])
    if (is.na(ans)) {warning(\"enum not found \", name, \" \", type)}
    ans
    }
 }

 enumFromInteger =
 function(i,type)
 {
   gettype <- paste(\".__E__\", type, sep = \"\")
   if (!exists(gettype)) gettype <- paste(\".__E__\", substr(type, 3, nchar(type)), sep = \"\")
   itemlist <- get(gettype)
   names(itemlist)[match(i, itemlist)]
 }

")


string(REGEX REPLACE "enumToInteger.*coerceIfNotSubclass" "${NEW_CODE}coerceIfNotSubclass" SOURCECODE "${SOURCECODE}")
file(WRITE "${FILENAME}" "${SOURCECODE}")
message (STATUS "Patched COPASI.R")
