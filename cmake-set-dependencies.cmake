# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
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
# Description       : CMake overwrite dependencies script
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

# libsedml
if (NOT EXISTS ${LIBSEDML_INCLUDE_DIR})
set (LIBSEDML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SEDML include directory" FORCE)
endif()
if (NOT EXISTS ${LIBSEDML_LIBRARY})
set (LIBSEDML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libsedml-static.lib CACHE FILEPATH "libSEDML library" FORCE)
endif()

# raptor
if (NOT EXISTS ${RAPTOR_INCLUDE_DIR})
set (RAPTOR_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "raptor include directory" FORCE)
endif()
if (NOT EXISTS ${RAPTOR_LIBRARY})
set (RAPTOR_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/raptor.lib CACHE FILEPATH "raptor library" FORCE)
endif()

if (NOT BLA_VENDOR OR "${BLA_VENDOR}" STREQUAL "COPASI Dependencies")
  # clapack
  set (CLAPACK_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "clapack include directory" FORCE)
  
  # the default clapack uses the names 'lapack.lib' / 'blas.lib'
  set(CLAPACK_LIBRARY_LAPACK ${COPASI_DEPENDENCY_DIR}/lib/liblapack.lib)
  if (NOT EXISTS ${CLAPACK_LIBRARY_LAPACK})
    set(CLAPACK_LIBRARY_LAPACK ${COPASI_DEPENDENCY_DIR}/lib/lapack.lib)
  endif()
  
  set(CLAPACK_LIBRARY_BLAS ${COPASI_DEPENDENCY_DIR}/lib/libblas.lib)
  if (NOT EXISTS ${CLAPACK_LIBRARY_BLAS})
    set(CLAPACK_LIBRARY_BLAS ${COPASI_DEPENDENCY_DIR}/lib/blas.lib)
  endif()
  
  set(CLAPACK_LIBRARY_F2C ${COPASI_DEPENDENCY_DIR}/lib/libf2c.lib)
  if (NOT EXISTS ${CLAPACK_LIBRARY_F2C})
    set(CLAPACK_LIBRARY_F2C ${COPASI_DEPENDENCY_DIR}/lib/f2c.lib)
  endif()
  
  set (CLAPACK_LIBRARIES
       ${CLAPACK_LIBRARY_LAPACK};${CLAPACK_LIBRARY_BLAS};${CLAPACK_LIBRARY_F2C}
       CACHE FILEPATH "lapack library" FORCE)

  add_definitions(-DHAVE_BLASWRAP_H)
  add_definitions(-DHAVE_F2C_H)
  add_definitions(-DHAVE_CLAPACK_H)
  add_definitions(-DNO_BLAS_WRAP)
  
  set (BLA_VENDOR "COPASI Dependencies")
  set (CLAPACK_FOUND TRUE)
  mark_as_advanced(CLAPACK_INCLUDE_DIR CLAPACK_LIBRARIES)

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
set (LIBEXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libexpat.lib CACHE FILEPATH "expat library" FORCE)
endif()
if (NOT EXISTS ${EXPAT_INCLUDE_DIR})
set (EXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
endif()
if (NOT EXISTS ${EXPAT_LIBRARY})
set (EXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libexpat.lib CACHE FILEPATH "expat library" FORCE)
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
set (SBW_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libSBW-static.a CACHE FILEPATH "SBW library" FORCE)
set (SBW_LIBRARIES ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libSBW-static.a CACHE FILEPATH "SBW library" FORCE)
endif()


# libsbml
if (NOT EXISTS ${LIBSBML_INCLUDE_DIR})
set (LIBSBML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBML include directory" FORCE)
endif()
if (NOT EXISTS ${LIBSBML_LIBRARY})
set (LIBSBML_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libsbml-static.a CACHE FILEPATH "libSBML library" FORCE)
endif()

# libsedml
if (NOT EXISTS ${LIBSEDML_INCLUDE_DIR})
set (LIBSEDML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SEDML include directory" FORCE)
endif()
if (NOT EXISTS ${LIBSEDML_LIBRARY})
set (LIBSEDML_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libsedml-static.a CACHE FILEPATH "libSEDML library" FORCE)
endif()


# raptor
if (NOT EXISTS ${RAPTOR_INCLUDE_DIR})
set (RAPTOR_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "raptor include directory" FORCE)
endif()
if (NOT EXISTS ${RAPTOR_LIBRARY})
set (RAPTOR_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libraptor.a CACHE FILEPATH "raptor library" FORCE)
endif()

if (NOT APPLE AND (NOT BLA_VENDOR OR "${BLA_VENDOR}" STREQUAL "COPASI Dependencies"))

  # clapack
  set (CLAPACK_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "clapack include directory" FORCE)

  set(CLAPACK_LIBRARY_F2C "${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libf2c.a")

  if (NOT EXISTS "${CLAPACK_LIBRARY_F2C}")
    set(CLAPACK_LIBRARY_F2C "/usr/${CMAKE_INSTALL_LIBDIR}/libgfortran.so")
  endif()
  

  set (CLAPACK_LIBRARIES
       ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/liblapack.a;${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libblas.a;${CLAPACK_LIBRARY_F2C}
       CACHE FILEPATH "lapack library" FORCE)

  add_definitions(-DHAVE_BLASWRAP_H)
  add_definitions(-DHAVE_F2C_H)
  add_definitions(-DHAVE_CLAPACK_H)
  add_definitions(-DNO_BLAS_WRAP)
  
  set (BLA_VENDOR "COPASI Dependencies")
  set (CLAPACK_FOUND TRUE)
  mark_as_advanced(CLAPACK_INCLUDE_DIR CLAPACK_LIBRARIES)
endif()

# cpp unit
if (NOT EXISTS ${CPPUNIT_INCLUDE_DIR})
set (CPPUNIT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "cpp unit include directory" FORCE)
endif()
if (NOT EXISTS ${CPPUNIT_LIBRARY})
set (CPPUNIT_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libcppunit.a CACHE FILEPATH "cppunit library" FORCE)
endif()

# expat
if (NOT EXISTS ${LIBEXPAT_INCLUDE_DIR})
set (LIBEXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
endif()
if (NOT EXISTS ${LIBEXPAT_LIBRARY})
set (LIBEXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libexpat.a CACHE FILEPATH "expat library" FORCE)
endif()

if (NOT EXISTS ${EXPAT_INCLUDE_DIR})
set (EXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
endif()
if (NOT EXISTS ${EXPAT_LIBRARY})
set (EXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libexpat.a CACHE FILEPATH "expat library" FORCE)
endif()

# mml
if (NOT EXISTS ${MML_INCLUDE_DIR})
set (MML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "mml include directory" FORCE)
endif()
if (NOT EXISTS ${MML_LIBRARY})
set (MML_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libmml.a CACHE FILEPATH "mml library" FORCE)
endif()

# QWT 
if (NOT EXISTS ${QWT_INCLUDE_DIR})
set (QWT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwt include directory" FORCE)
endif()
if (NOT EXISTS ${QWT_LIBRARY})
set (QWT_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libqwt.a CACHE FILEPATH "qwt library" FORCE)
endif()

# QWT Plot
if (NOT EXISTS ${QWTPLOT3D_INCLUDE_DIR})
set (QWTPLOT3D_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwtplot3d include directory" FORCE)
endif()
if (NOT EXISTS ${QWTPLOT3D_LIBRARY})
set (QWTPLOT3D_LIBRARY ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/libqwtplot3d.a CACHE FILEPATH "qwtplot3d library" FORCE)
endif()


endif()

endif()
