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

project (bindings)

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


