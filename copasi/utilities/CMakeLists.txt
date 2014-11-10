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

file(GLOB HEADERS_UTILITIES utilities/*.h)
file(GLOB SOURCES_UTILITIES utilities/*.cpp)

list(REMOVE_ITEM SOURCES_UTILITIES 
   ${CMAKE_CURRENT_SOURCE_DIR}/utilities/CWriteConfig.cpp
)



# create source group for IDEs
source_group(utilities FILES ${SOURCES_UTILITIES} ${HEADERS_UTILITIES})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_UTILITIES})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_UTILITIES})
