###############################################################################
#
# Description       : CMake overwrite dependencies script
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

if (COPASI_DEPENDENCY_DIR AND EXISTS ${COPASI_DEPENDENCY_DIR})

# we have a dependencies directory and get to overwrite all the dependencies

if (NOT UNIX OR CYGWIN)

# dependencies for windows

# SBW
if (NOT EXISTS ${SBW_INCLUDE_DIR})
set (SBW_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBW include directory" FORCE)
endif()
if (NOT EXISTS ${SBW_LIBRARY})
set (SBW_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/SBW-static.lib CACHE FILEPATH "SBW library" FORCE)
set (SBW_LIBRARIES ${SBW_LIBRARY};ws2_32.lib CACHE STRING "SBW libraries" FORCE)
endif()

# libsbml
if (NOT EXISTS ${LIBSBML_INCLUDE_DIR})
set (LIBSBML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBML include directory" FORCE)
endif()
if (NOT EXISTS ${LIBSBML_LIBRARY})
set (LIBSBML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libsbml-static.lib CACHE FILEPATH "libSBML library" FORCE)
endif()

# raptor
if (NOT EXISTS ${RAPTOR_INCLUDE_DIR})
set (RAPTOR_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "raptor include directory" FORCE)
endif()
if (NOT EXISTS ${RAPTOR_LIBRARY})
set (RAPTOR_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/raptor.lib CACHE FILEPATH "raptor library" FORCE)
endif()

# clapack
if (NOT EXISTS ${LAPACK_CLAPACK_INCLUDE_DIR})
set (LAPACK_CLAPACK_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "clapack include directory" FORCE)
endif()
if (NOT EXISTS ${LAPACK_CLAPACK_LIBRARY})
set (LAPACK_CLAPACK_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/lapack.lib CACHE FILEPATH "lapack library" FORCE)
endif()
if (NOT EXISTS ${LAPACK_BLAS_LIBRARY})
set (LAPACK_BLAS_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/blas.lib CACHE FILEPATH "lapack library" FORCE)
endif()
if (NOT EXISTS ${LAPACK_F2C_LIBRARY})
set (LAPACK_F2C_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libf2c.lib CACHE FILEPATH "lapack library" FORCE)
endif()

# cpp unit
if (NOT EXISTS ${CPPUNIT_INCLUDE_DIR})
set (CPPUNIT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "cpp unit include directory" FORCE)
endif()
if (NOT EXISTS ${CPPUNIT_LIBRARY})
set (CPPUNIT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/cppunit.lib CACHE FILEPATH "cppunit library" FORCE)
endif()

# expat
if (NOT EXISTS ${LIBEXPAT_INCLUDE_DIR})
set (LIBEXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
endif()
if (NOT EXISTS ${LIBEXPAT_LIBRARY})
set (LIBEXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/expat.lib CACHE FILEPATH "expat library" FORCE)
endif()
if (NOT EXISTS ${EXPAT_INCLUDE_DIR})
set (EXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
endif()
if (NOT EXISTS ${EXPAT_LIBRARY})
set (EXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/expat.lib CACHE FILEPATH "expat library" FORCE)
endif()

# mml
if (NOT EXISTS ${MML_INCLUDE_DIR})
set (MML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "mml include directory" FORCE)
endif()
if (NOT EXISTS ${MML_LIBRARY})
set (MML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/mml.lib CACHE FILEPATH "mml library" FORCE)
endif()

# QWT 
if (NOT EXISTS ${QWT_INCLUDE_DIR})
set (QWT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwt include directory" FORCE)
endif()
if (NOT EXISTS ${QWT_LIBRARY})
set (QWT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/qwt.lib CACHE FILEPATH "qwt library" FORCE)
endif()

# QWT Plot
if (NOT EXISTS ${QWTPLOT3D_INCLUDE_DIR})
set (QWTPLOT3D_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwtplot3d include directory" FORCE)
endif()
if (NOT EXISTS ${QWTPLOT3D_LIBRARY})
set (QWTPLOT3D_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/qwtplot3d.lib CACHE FILEPATH "qwtplot3d library" FORCE)
endif()


else()

# dependencies for linux like 

# SBW
if (NOT EXISTS ${SBW_INCLUDE_DIR})
set (SBW_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBW include directory" FORCE)
endif()
if (NOT EXISTS ${SBW_LIBRARY})
set (SBW_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libSBW-static.a CACHE FILEPATH "SBW library" FORCE)
set (SBW_LIBRARIES ${COPASI_DEPENDENCY_DIR}/lib/libSBW-static.a CACHE FILEPATH "SBW library" FORCE)
endif()


# libsbml
if (NOT EXISTS ${LIBSBML_INCLUDE_DIR})
set (LIBSBML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBML include directory" FORCE)
endif()
if (NOT EXISTS ${LIBSBML_LIBRARY})
set (LIBSBML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libsbml-static.a CACHE FILEPATH "libSBML library" FORCE)
endif()

# raptor
if (NOT EXISTS ${RAPTOR_INCLUDE_DIR})
set (RAPTOR_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "raptor include directory" FORCE)
endif()
if (NOT EXISTS ${RAPTOR_LIBRARY})
set (RAPTOR_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libraptor.a CACHE FILEPATH "raptor library" FORCE)
endif()

if (NOT APPLE)
# clapack
if (NOT EXISTS ${LAPACK_CLAPACK_INCLUDE_DIR})
set (LAPACK_CLAPACK_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "clapack include directory" FORCE)
endif()
if (NOT EXISTS ${LAPACK_CLAPACK_LIBRARY})
set (LAPACK_CLAPACK_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/liblapack.a CACHE FILEPATH "lapack library" FORCE)
endif()
if (NOT EXISTS ${LAPACK_BLAS_LIBRARY})
set (LAPACK_BLAS_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libblas.a CACHE FILEPATH "lapack library" FORCE)
endif()
if (NOT EXISTS ${LAPACK_F2C_LIBRARY})
set (LAPACK_F2C_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libf2c.a CACHE FILEPATH "lapack library" FORCE)
endif()
endif()

# cpp unit
if (NOT EXISTS ${CPPUNIT_INCLUDE_DIR})
set (CPPUNIT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "cpp unit include directory" FORCE)
endif()
if (NOT EXISTS ${CPPUNIT_LIBRARY})
set (CPPUNIT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libcppunit.a CACHE FILEPATH "cppunit library" FORCE)
endif()

# expat
if (NOT EXISTS ${LIBEXPAT_INCLUDE_DIR})
set (LIBEXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
endif()
if (NOT EXISTS ${LIBEXPAT_LIBRARY})
set (LIBEXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libexpat.a CACHE FILEPATH "expat library" FORCE)
endif()

if (NOT EXISTS ${EXPAT_INCLUDE_DIR})
set (EXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
endif()
if (NOT EXISTS ${EXPAT_LIBRARY})
set (EXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libexpat.a CACHE FILEPATH "expat library" FORCE)
endif()

# mml
if (NOT EXISTS ${MML_INCLUDE_DIR})
set (MML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "mml include directory" FORCE)
endif()
if (NOT EXISTS ${MML_LIBRARY})
set (MML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libmml.a CACHE FILEPATH "mml library" FORCE)
endif()

# QWT 
if (NOT EXISTS ${QWT_INCLUDE_DIR})
set (QWT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwt include directory" FORCE)
endif()
if (NOT EXISTS ${QWT_LIBRARY})
set (QWT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libqwt.a CACHE FILEPATH "qwt library" FORCE)
endif()

# QWT Plot
if (NOT EXISTS ${QWTPLOT3D_INCLUDE_DIR})
set (QWTPLOT3D_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwtplot3d include directory" FORCE)
endif()
if (NOT EXISTS ${QWTPLOT3D_LIBRARY})
set (QWTPLOT3D_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libqwtplot3d.a CACHE FILEPATH "qwtplot3d library" FORCE)
endif()


endif()

endif()