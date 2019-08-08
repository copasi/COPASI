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

file(GLOB HEADERS_XML xml/*.h)
file(GLOB SOURCES_XML xml/*.cpp)

file(GLOB HEADERS_XML_PARSER xml/parser/*.h)
file(GLOB SOURCES_XML_PARSER xml/parser/*.cpp)

# create source group for IDEs
source_group(xml FILES ${SOURCES_XML} ${HEADERS_XML})
source_group(xmlParser FILES ${SOURCES_XML_PARSER} ${HEADERS_XML_PARSER})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_XML} ${SOURCES_XML_PARSER})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_XML} ${HEADERS_XML_PARSER})
