###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Joseph O. Dada <joseph.dada@manchester.ac.uk>
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


file(GLOB HEADERS_SEDML sedml/*.h)
file(GLOB SOURCES_SEDML sedml/*.cpp)

# create source group for IDEs
source_group(sedml FILES ${SOURCES_SEDML} ${HEADERS_SEDML})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_SEDML})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_SEDML})
