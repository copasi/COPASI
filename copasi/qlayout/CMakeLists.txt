# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# 
# 
#
###############################################################################

file(GLOB FORMS_QLAYOUT   qlayout/*.ui )
file(GLOB HEADERS_QLAYOUT qlayout/*.h  )
file(GLOB SOURCES_QLAYOUT qlayout/*.cpp)

# create source group for IDEs
source_group(qlayout FILES ${FORMS_QLAYOUT} ${HEADERS_QLAYOUT} ${SOURCES_QLAYOUT})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_QLAYOUT})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_QLAYOUT})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_QLAYOUT})
