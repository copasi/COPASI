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


file(GLOB HEADERS_PLOTUI plotUI/*.h  )
file(GLOB FORMS_PLOTUI   plotUI/*.ui )
file(GLOB SOURCES_PLOTUI plotUI/*.cpp)


if (NOT ENABLE_COPASI_BANDED_GRAPH)
 list(REMOVE_ITEM HEADERS_PLOTUI ${CMAKE_CURRENT_SOURCE_DIR}/plotUI/BandedGraphWidget.h )
 list(REMOVE_ITEM FORMS_PLOTUI   ${CMAKE_CURRENT_SOURCE_DIR}/plotUI/BandedGraphWidget.ui )
 list(REMOVE_ITEM SOURCES_PLOTUI ${CMAKE_CURRENT_SOURCE_DIR}/plotUI/BandedGraphWidget.cpp )

endif(NOT ENABLE_COPASI_BANDED_GRAPH)

# create source group for IDEs
source_group(plotUI FILES ${FORMS_PLOTUI} ${HEADERS_PLOTUI} ${SOURCES_PLOTUI})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_PLOTUI})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_PLOTUI})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_PLOTUI})
