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

# cmake_minimum_required (VERSION 2.8)
# project (MIRIAMUI)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_MIRIAMUI MIRIAMUI/*.h)
file(GLOB FORMS_MIRIAMUI   MIRIAMUI/*.ui)
file(GLOB SOURCES_MIRIAMUI MIRIAMUI/*.cpp)

# create source group for IDEs
source_group(MIRIAMUI FILES ${SOURCES_MIRIAMUI} ${HEADERS_MIRIAMUI} ${FORMS_MIRIAMUI})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_MIRIAMUI})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_MIRIAMUI})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_MIRIAMUI})


# set(FORMS CQMiriamWidget.ui ${FORMS})
# set(FORMS CQRDFTreeView.ui ${FORMS})
# 
# 
# set(HEADERS CQMiriamWidget.h ${HEADERS})
# set(HEADERS CQCreatorDM.h ${HEADERS})
# set(HEADERS CQReferenceDM.h ${HEADERS})
# set(HEADERS CQBiologicalDescriptionDM.h ${HEADERS})
# set(HEADERS CQModifiedDM.h ${HEADERS})
# set(HEADERS CQRDFTreeView.h ${HEADERS})
# if (NOT WIN32 OR CYGWIN)
# set(HEADERS CQRDFTreeViewItem.h ${HEADERS})
# endif()
# 
# set(SOURCES CQMiriamWidget.cpp ${SOURCES})
# set(SOURCES CQCreatorDM.cpp ${SOURCES})
# set(SOURCES CQReferenceDM.cpp ${SOURCES})
# set(SOURCES CQBiologicalDescriptionDM.cpp ${SOURCES})
# set(SOURCES CQModifiedDM.cpp ${SOURCES})
# set(SOURCES CQRDFTreeView.cpp ${SOURCES})
# set(SOURCES CQRDFTreeViewItem.cpp ${SOURCES})
# 
		
#include(../CMakeUILib.cmake)
#
#qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
#
#if(FORMS)
#qt4_wrap_ui(HEADERS_FORMS ${FORMS})
#endif(FORMS)
#
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
#INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
#
#add_library(MIRIAMUI STATIC ${SOURCES} ${HEADERS} ${HEADERS_FORMS} ${HEADERS_MOC})
#
#target_link_libraries(MIRIAMUI MIRIAM)

