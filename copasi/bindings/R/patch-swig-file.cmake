if (NOT FILENAME OR NOT EXISTS ${FILENAME})
	message(FATAL_ERROR "Please specify the filename to the file to patch")
endif()

execute_process(COMMAND sed 
					-f 
				     ${SRC_DIR}/sedscript.txt -i
					 "${FILENAME}"
					 )

#file(STRINGS "${FILENAME}" SOURCECODE)
#file(READ "${FILENAME}" SOURCECODE)
#STRING( REGEX REPLACE "\r?\n.$" "\n" SOURCECODE "${SOURCECODE}" )
# for whatever reason the enums don't quite work out as they should
#STRING(REGEX REPLACE ";" "\\\\;" SOURCECODE "${SOURCECODE}")
#STRING(REGEX REPLACE "\n" ";" SOURCECODE "${SOURCECODE}")
# STRING(REGEX REPLACE "\r?\n" ";" SOURCECODE "${SOURCECODE}")
# file(WRITE "${FILENAME}" "# modified code\n")
# FOREACH(line ${SOURCECODE})
# 	string(LENGTH "${line}" line_length)
# 	Message( "${line_length}\n")
# 	STRING(REGEX REPLACE "(.*)(enum)(.*)(_p)(.*)" "\\1\\2\\4" new_line "${line}" )
# 	file(APPEND "${FILENAME}" "${new_line}\n")
# endforeach()
message ("DONE")