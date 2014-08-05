###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Joseph O. Dada <josephodada@gmail.com>
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

#cmake_minimum_required (VERSION 2.6)

file(GLOB HEADERS_UNDOFRAMEWORK undoFramework/*.h)
file(GLOB SOURCES_UNDOFRAMEWORK undoFramework/*.cpp)


# create source group for IDEs
source_group(undoframework FILES ${SOURCES_UNDOFRAMEWORK} ${HEADERS_UNDOFRAMEWORK})


# add files to COPASI UI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_UNDOFRAMEWORK})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_UNDOFRAMEWORK})


