###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
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

# cmake_minimum_required (VERSION 2.8)
# project (layoutUI)
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB FORMS_QLAYOUT   qlayout/*.ui )
file(GLOB HEADERS_QLAYOUT qlayout/*.h  )
file(GLOB SOURCES_QLAYOUT qlayout/*.cpp)

# create source group for IDEs
source_group(qlayout FILES ${FORMS_QLAYOUT} ${HEADERS_QLAYOUT} ${SOURCES_QLAYOUT})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_QLAYOUT})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_QLAYOUT})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_QLAYOUT})

