# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# 
# 
#
###############################################################################


file(GLOB HEADERS_LAYOUT layout/*.h)
file(GLOB SOURCES_LAYOUT layout/*.cpp)

if(NOT OPENGL_FOUND)

  list(REMOVE_ITEM SOURCES_LAYOUT
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLLayoutRenderer.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/layout/utility_classes.cpp
  )
	
  list(REMOVE_ITEM HEADERS_LAYOUT
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLFontRendererBase.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLLayoutRenderer.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/layout/utility_classes.h
  )  
endif(NOT OPENGL_FOUND)

# remove other elements that 
list(REMOVE_ITEM SOURCES_LAYOUT 
  ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLSimpleImageTexturizer.cpp
)

# create source group for IDEs
source_group(layout FILES ${SOURCES_LAYOUT} ${HEADERS_LAYOUT})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_LAYOUT})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_LAYOUT})

