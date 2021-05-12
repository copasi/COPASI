# Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
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
# Original author(s): Joseph O. Dada <joseph.dada@manchester.ac.uk>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# 
# 
#
###############################################################################

#cmake_minimum_required (VERSION 2.8.12)


file(GLOB HEADERS_SEDML sedml/*.h)
file(GLOB SOURCES_SEDML sedml/*.cpp)

# create source group for IDEs
source_group(sedml FILES ${SOURCES_SEDML} ${HEADERS_SEDML})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_SEDML})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_SEDML})
