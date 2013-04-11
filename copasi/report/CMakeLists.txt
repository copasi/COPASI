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

#cmake_minimum_required (VERSION 2.6)
#project (report)
#
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_REPORT report/*.h)
file(GLOB SOURCES_REPORT report/*.cpp)


# create source group for IDEs
source_group(report FILES ${SOURCES_REPORT} ${HEADERS_REPORT})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_REPORT})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_REPORT})

# set(HEADERS ${HEADERS} ArtisticLicense.h)
# set(HEADERS ${HEADERS} CArrayElementReference.h)
# set(HEADERS ${HEADERS} CCopasiArray.h)
# set(HEADERS ${HEADERS} CCopasiContainer.h)
# set(HEADERS ${HEADERS} CCopasiObject.h)
# set(HEADERS ${HEADERS} CCopasiObjectName.h)
# set(HEADERS ${HEADERS} CCopasiObjectReference.h)
# set(HEADERS ${HEADERS} CCopasiRootContainer.h)
# set(HEADERS ${HEADERS} CCopasiStaticString.h)
# set(HEADERS ${HEADERS} CCopasiTimer.h)
# set(HEADERS ${HEADERS} CKeyFactory.h)
# set(HEADERS ${HEADERS} COutputAssistant.h)
# set(HEADERS ${HEADERS} CRenameHandler.h)
# set(HEADERS ${HEADERS} CReportTemplate.h)
# set(HEADERS ${HEADERS} CReportTemplateVector.h)
# set(HEADERS ${HEADERS} CReport.h)
# 
# set(SOURCES ${SOURCES} CArrayElementReference.cpp)
# set(SOURCES ${SOURCES} CCopasiArray.cpp)
# set(SOURCES ${SOURCES} CCopasiContainer.cpp)
# set(SOURCES ${SOURCES} CCopasiObject.cpp)
# set(SOURCES ${SOURCES} CCopasiObjectName.cpp)
# set(SOURCES ${SOURCES} CCopasiRootContainer.cpp)
# set(SOURCES ${SOURCES} CCopasiStaticString.cpp)
# set(SOURCES ${SOURCES} CCopasiTimer.cpp)
# set(SOURCES ${SOURCES} CKeyFactory.cpp)
# set(SOURCES ${SOURCES} COutputAssistant.cpp)
# set(SOURCES ${SOURCES} CReportTemplate.cpp)
# set(SOURCES ${SOURCES} CReportTemplateVector.cpp)
# set(SOURCES ${SOURCES} CReport.cpp)
# 

# add_library(report STATIC ${SOURCES} ${HEADERS})
# target_link_libraries(report commandline)

