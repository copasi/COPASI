# Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
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

file(GLOB HEADERS_LGPL lgpl/*.h)
file(GLOB SOURCES_LGPL lgpl/*.cpp)


# create source group for IDEs
source_group(randomGenerator FILES ${SOURCES_LGPL} ${HEADERS_LGPL})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_LGPL})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_LGPL})
