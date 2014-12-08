###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
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

cmake_minimum_required (VERSION 2.6)
project (exportSedML)

include_directories("${PROJECT_SOURCE_DIR}/../../.." "${PROJECT_SOURCE_DIR}/../../../.." "${PROJECT_SOURCE_DIR}")

set(SOURCES ${SOURCES} exportSedML.cpp)

include(../../../CMakeConsoleApp.cmake)

add_executable(exportSedML ${SOURCES} ${HEADERS})
add_dependencies(exportSedML ${SE_DEPENDENCIES}) 
target_link_libraries(exportSedML ${SE_EXTERNAL_LIBS} ${SE_LIBS})

