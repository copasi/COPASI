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

file(GLOB HEADERS_MIRIAMUI MIRIAMUI/*.h)
file(GLOB FORMS_MIRIAMUI   MIRIAMUI/*.ui)
file(GLOB SOURCES_MIRIAMUI MIRIAMUI/*.cpp)

# create source group for IDEs
source_group(MIRIAMUI FILES ${SOURCES_MIRIAMUI} ${HEADERS_MIRIAMUI} ${FORMS_MIRIAMUI})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_MIRIAMUI})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_MIRIAMUI})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_MIRIAMUI})
