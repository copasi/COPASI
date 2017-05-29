# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

###############################################################################
#
# Description       : CMake build script for native java files
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
#
###############################################################################

message("Creating: copasi.jar")

# patch broken enums

set (SWIG_ENUM_FIX_FILES 
        "${BIN_DIRECTORY}/java-files/org/COPASI/CTaskEnum.java"
        "${BIN_DIRECTORY}/java-files/org/COPASI/CModelEntity.java"
        "${BIN_DIRECTORY}/java-files/org/COPASI/CDataArray.java"
     )

foreach(broken_file ${SWIG_ENUM_FIX_FILES})
  file(READ "${broken_file}" SOURCECODE)
#  string(REGEX MATCH
#   "public final static int ([a-zA-Z]*_)([_a-zA-Z0-9]*) = ([a-zA-Z]*) \\+ 1"  
#    OUT
#    ${SOURCECODE}
#  )
#  message(STATUS "${OUT} 1: ${CMAKE_MATCH_1} 2: ${CMAKE_MATCH_2} 3: ${CMAKE_MATCH_3}")

  string(REGEX REPLACE 
   "public final static int ([a-zA-Z]*_)([_a-zA-Z0-9]*) = ([a-zA-Z0-9]*) \\+ 1"
   "public final static int \\1\\2 = \\1\\3 + 1; // FIXED" 
   SOURCECODE "${SOURCECODE}")
  file(WRITE "${broken_file}" "${SOURCECODE}")
  get_filename_component(baseName ${broken_file} NAME)
  message (STATUS "Patched ${baseName}")
endforeach()


# find all sources
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${BIN_DIRECTORY} ${BIN_DIRECTORY}/java-files/org/COPASI/*.java)

# convert paths
set(NATIVE_FILES)
foreach(javaFile ${SOURCE_FILES})
	file(TO_NATIVE_PATH ${javaFile} temp)
	set(NATIVE_FILES ${NATIVE_FILES} ${temp})
endforeach()

# delete file if it exists
if (EXISTS ${BIN_DIRECTORY}/copasi.jar)
	file(REMOVE ${BIN_DIRECTORY}/copasi.jar)	
endif()

# compile files
execute_process(
	COMMAND "${Java_JAVAC_EXECUTABLE}"
		 -source 1.5
		 -target 1.5
		 -d java-files
		 ${NATIVE_FILES}	
	WORKING_DIRECTORY "${BIN_DIRECTORY}"
)

# enumerate class files
file(GLOB_RECURSE CLASS_FILES RELATIVE ${BIN_DIRECTORY}/java-files ${BIN_DIRECTORY}/java-files/org/COPASI/*.class)
set(NATIVE_CLASS_FILES)
foreach(classFile ${CLASS_FILES})
	file(TO_NATIVE_PATH ${classFile} temp)
	set(NATIVE_CLASS_FILES ${NATIVE_CLASS_FILES} ${temp})
endforeach()

# create jar
execute_process(
	COMMAND "${Java_JAR_EXECUTABLE}"
		 -cvfm ..${PATH_SEP}copasi.jar
		 ${SRC_DIRECTORY}/Manifest.txt
		 ${NATIVE_CLASS_FILES}	
	WORKING_DIRECTORY "${BIN_DIRECTORY}/java-files"
)

################################################################
#
# copasi-gui
#


# find all sources
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${BIN_DIRECTORY} ${SRC_DIRECTORY}/gui/org/COPASI/gui/*.java)

# convert paths
set(NATIVE_FILES)
foreach(javaFile ${SOURCE_FILES})
	file(TO_NATIVE_PATH ${javaFile} temp)
	set(NATIVE_FILES ${NATIVE_FILES} ${temp})
endforeach()

# delete file if it exists
if (EXISTS ${BIN_DIRECTORY}/copasi-gui.jar)
	file(REMOVE ${BIN_DIRECTORY}/copasi-gui.jar)	
endif()

make_directory(${BIN_DIRECTORY}/gui/org/COPASI/gui/)

# compile files
execute_process(
	COMMAND "${Java_JAVAC_EXECUTABLE}"
		 -source 1.5
		 -target 1.5
		 -cp ${BIN_DIRECTORY}/copasi.jar
		 -d gui
		 ${NATIVE_FILES}	
	WORKING_DIRECTORY "${BIN_DIRECTORY}"
)

# enumerate class files
file(GLOB_RECURSE CLASS_FILES RELATIVE ${BIN_DIRECTORY}/gui ${BIN_DIRECTORY}/gui/org/COPASI/*.class)
set(NATIVE_CLASS_FILES)
foreach(classFile ${CLASS_FILES})
	file(TO_NATIVE_PATH ${classFile} temp)
	set(NATIVE_CLASS_FILES ${NATIVE_CLASS_FILES} ${temp})
endforeach()

# create jar
execute_process(
	COMMAND "${Java_JAR_EXECUTABLE}"
		 -cvf ..${PATH_SEP}copasi-gui.jar
		 ${NATIVE_CLASS_FILES}	
	WORKING_DIRECTORY "${BIN_DIRECTORY}/gui"
)
