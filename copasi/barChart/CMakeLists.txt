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

file(GLOB FORMS_BARCHART   barChart/*.ui )
file(GLOB HEADERS_BARCHART barChart/*.h  )
file(GLOB SOURCES_BARCHART barChart/*.cpp)

# create source group for IDEs
source_group(barChart FILES ${FORMS_BARCHART} ${HEADERS_BARCHART} ${SOURCES_BARCHART})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_BARCHART})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_BARCHART})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_BARCHART})
