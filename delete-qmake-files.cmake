###############################################################################
#
# Description       : CMake build script for removing qt ui and moc files 
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., University of Heidelberg, and The University
# of Manchester.
# All rights reserved.
# 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.
# 
# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.
#
###############################################################################

if (NOT SRC_DIRECTORY)
message(FATAL_ERROR "Need the SRC_DIRECTORY to be specified.")
endif()
STRING(REGEX REPLACE "\"" "" SRC_DIRECTORY ${SRC_DIRECTORY} )
file(TO_CMAKE_PATH ${SRC_DIRECTORY} SRC_DIRECTORY)
if (NOT EXISTS ${SRC_DIRECTORY})
message(FATAL_ERROR "Source dir could not be found!")
endif()

message("Deleting UI and moc files from: ${SRC_DIRECTORY}")

foreach(dir barChart layoutUI plotUI MIRIAMUI UI wizard)
  
  file(GLOB_RECURSE UI_FILES RELATIVE  ${SRC_DIRECTORY} ${SRC_DIRECTORY}/copasi/${dir}/ui_*)
  file(GLOB_RECURSE MOC_FILES RELATIVE ${SRC_DIRECTORY} ${SRC_DIRECTORY}/copasi/${dir}/moc_*)
  set(FILES_TO_DELETE ${UI_FILES} ${MOC_FILES})
  foreach (fileName ${FILES_TO_DELETE})
  
    message (STATUS "deleting ${fileName}")
    execute_process(
    	COMMAND "${CMAKE_COMMAND}"
    		 -E remove ${fileName}
    	
    	WORKING_DIRECTORY "${SRC_DIRECTORY}"
    )
  
  endforeach()
endforeach()
