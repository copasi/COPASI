# Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# 
# 
#
###############################################################################

cmake_minimum_required (VERSION 2.8.12)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project (bindings VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")

if (BUILD_CXX_EXAMPLES)
  add_subdirectory(cpp_examples)
endif (BUILD_CXX_EXAMPLES)

if (ENABLE_CSHARP)
  add_subdirectory(csharp)
endif (ENABLE_CSHARP)

if (ENABLE_JAVA)
  add_subdirectory(java)
endif (ENABLE_JAVA)

if (ENABLE_PYTHON)
  add_subdirectory(python)
endif (ENABLE_PYTHON)

if (ENABLE_PERL)
  add_subdirectory(perl)
endif (ENABLE_PERL)

if (ENABLE_OCTAVE)
  add_subdirectory(octave)
endif (ENABLE_OCTAVE)

if (ENABLE_R)
  add_subdirectory(R)
endif (ENABLE_R)


