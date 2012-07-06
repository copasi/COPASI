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
set (SBW_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBW include directory" FORCE)
set (SBW_LIBRARIES ${COPASI_DEPENDENCY_DIR}/lib/SBW-static.lib CACHE FILEPATH "SBW library" FORCE)

# libsbml
set (LIBSBML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBML include directory" FORCE)
set (LIBSBML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libsbml-static.lib CACHE FILEPATH "libSBML library" FORCE)

# raptor
set (RAPTOR_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "raptor include directory" FORCE)
set (RAPTOR_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/raptor.lib CACHE FILEPATH "raptor library" FORCE)

# clapack
set (LAPACK_CLAPACK_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "clapack include directory" FORCE)
set (LAPACK_CLAPACK_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/lapack.lib CACHE FILEPATH "lapack library" FORCE)
set (LAPACK_BLAS_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/blas.lib CACHE FILEPATH "lapack library" FORCE)
set (LAPACK_F2C_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libf2c.lib CACHE FILEPATH "lapack library" FORCE)

# expat
set (LIBEXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
set (LIBEXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/expat.lib CACHE FILEPATH "expat library" FORCE)

# mml
set (MML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "mml include directory" FORCE)
set (MML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/mml.lib CACHE FILEPATH "mml library" FORCE)

# QWT 
set (QWT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwt include directory" FORCE)
set (QWT_LIBRARIES ${COPASI_DEPENDENCY_DIR}/lib/qwt.lib CACHE FILEPATH "qwt library" FORCE)

# QWT Plot
set (QWTPLOT3D_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwtplot3d include directory" FORCE)
set (QWTPLOT3D_LIBRARIES ${COPASI_DEPENDENCY_DIR}/lib/qwtplot3d.lib CACHE FILEPATH "qwtplot3d library" FORCE)


else()

# dependencies for linux like 

# SBW
set (SBW_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBW include directory" FORCE)
set (SBW_LIBRARIES ${COPASI_DEPENDENCY_DIR}/lib/libSBW-static.a CACHE FILEPATH "SBW library" FORCE)

# libsbml
set (LIBSBML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "SBML include directory" FORCE)
set (LIBSBML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libsbml-static.a CACHE FILEPATH "libSBML library" FORCE)

# raptor
set (RAPTOR_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "raptor include directory" FORCE)
set (RAPTOR_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libraptor.a CACHE FILEPATH "raptor library" FORCE)

if (NOT APPLE)
# clapack
set (LAPACK_CLAPACK_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "clapack include directory" FORCE)
set (LAPACK_CLAPACK_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/liblapack.a CACHE FILEPATH "lapack library" FORCE)
set (LAPACK_BLAS_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libblas.a CACHE FILEPATH "lapack library" FORCE)
set (LAPACK_F2C_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libf2c.a CACHE FILEPATH "lapack library" FORCE)
endif()

# expat
set (LIBEXPAT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "expat include directory" FORCE)
set (LIBEXPAT_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libexpat.a CACHE FILEPATH "expat library" FORCE)

# mml
set (MML_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "mml include directory" FORCE)
set (MML_LIBRARY ${COPASI_DEPENDENCY_DIR}/lib/libmml.a CACHE FILEPATH "mml library" FORCE)

# QWT 
set (QWT_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwt include directory" FORCE)
set (QWT_LIBRARIES ${COPASI_DEPENDENCY_DIR}/lib/libqwt.a CACHE FILEPATH "qwt library" FORCE)

# QWT Plot
set (QWTPLOT3D_INCLUDE_DIR ${COPASI_DEPENDENCY_DIR}/include CACHE PATH "qwtplot3d include directory" FORCE)
set (QWTPLOT3D_LIBRARIES ${COPASI_DEPENDENCY_DIR}/lib/libqwtplot3d.a CACHE FILEPATH "qwtplot3d library" FORCE)


endif()

endif(COPASI_DEPENDENCY_DIR)