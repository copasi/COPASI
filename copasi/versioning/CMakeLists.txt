###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Peyman Zarrineh
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


file(GLOB HEADERS_Versioning versioning/*.h )
file(GLOB SOURCES_Versioning versioning/*.cpp )


# create source group for IDEs
source_group(versioning FILES ${SOURCES_Versioning} ${HEADERS_Versioning})


# add files to COPASI UI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_Versioning})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_Versioning})
