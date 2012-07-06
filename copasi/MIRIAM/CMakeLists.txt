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

cmake_minimum_required (VERSION 2.6)
#project (MIRIAM)
#
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB_RECURSE HEADERS_MIRIAM MIRIAM/*.h)
file(GLOB_RECURSE SOURCES_MIRIAM MIRIAM/*.cpp)

# create source group for IDEs
source_group(MIRIAM FILES ${SOURCES_MIRIAM} ${HEADERS_MIRIAM})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_MIRIAM})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_MIRIAM})


# set(HEADERS ${HEADERS} CBiologicalDescription.h)
# set(HEADERS ${HEADERS} CCreator.h)
# set(HEADERS ${HEADERS} CConstants.h)
# set(HEADERS ${HEADERS} CMIRIAMResource.h)
# set(HEADERS ${HEADERS} CModelMIRIAMInfo.h)
# set(HEADERS ${HEADERS} CModified.h)
# set(HEADERS ${HEADERS} CReference.h)
# set(HEADERS ${HEADERS} CRaptorInit.h)
# set(HEADERS ${HEADERS} CRDFGraph.h)
# set(HEADERS ${HEADERS} CRDFGraphConverter.h)
# set(HEADERS ${HEADERS} CRDFLiteral.h)
# set(HEADERS ${HEADERS} CRDFNode.h)
# set(HEADERS ${HEADERS} CRDFObject.h)
# set(HEADERS ${HEADERS} CRDFParser.h)
# set(HEADERS ${HEADERS} CRDFPredicate.h)
# set(HEADERS ${HEADERS} CRDFSubject.h)
# set(HEADERS ${HEADERS} CRDFTriplet.h)
# set(HEADERS ${HEADERS} CRDFUtilities.h)
# set(HEADERS ${HEADERS} CRDFWriter.h)
# set(HEADERS ${HEADERS} WebServicesIssues/stdsoap2.h)
# set(HEADERS ${HEADERS} WebServicesIssues/soapStub.h)
# set(HEADERS ${HEADERS} WebServicesIssues/soapH.h)
# set(HEADERS ${HEADERS} WebServicesIssues/soapMiriamWebServicesSoapBindingProxy.h)
# 
# set(SOURCES ${SOURCES} CBiologicalDescription.cpp)
# set(SOURCES ${SOURCES} CCreator.cpp)
# set(SOURCES ${SOURCES} CConstants.cpp)
# set(SOURCES ${SOURCES} CMIRIAMResource.cpp)
# set(SOURCES ${SOURCES} CModelMIRIAMInfo.cpp)
# set(SOURCES ${SOURCES} CModified.cpp)
# set(SOURCES ${SOURCES} CReference.cpp)
# set(SOURCES ${SOURCES} CRaptorInit.cpp)
# set(SOURCES ${SOURCES} CRDFGraph.cpp)
# set(SOURCES ${SOURCES} CRDFGraphConverter.cpp)
# set(SOURCES ${SOURCES} CRDFLiteral.cpp)
# set(SOURCES ${SOURCES} CRDFNode.cpp)
# set(SOURCES ${SOURCES} CRDFObject.cpp)
# set(SOURCES ${SOURCES} CRDFParser.cpp)
# set(SOURCES ${SOURCES} CRDFPredicate.cpp)
# set(SOURCES ${SOURCES} CRDFSubject.cpp)
# set(SOURCES ${SOURCES} CRDFTriplet.cpp)
# set(SOURCES ${SOURCES} CRDFUtilities.cpp)
# set(SOURCES ${SOURCES} CRDFWriter.cpp)
# set(SOURCES ${SOURCES} WebServicesIssues/soapC.cpp)
# set(SOURCES ${SOURCES} WebServicesIssues/soapMiriamWebServicesSoapBindingProxy.cpp)
# set(SOURCES ${SOURCES} WebServicesIssues/stdsoap2.cpp)
# 

# add_library(MIRIAM STATIC ${SOURCES} ${HEADERS})
# target_link_libraries(MIRIAM ${RAPTOR_LIBRARY})

