# Copyright (C) 2012 - 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# TODO set libraries and library paths
# for expat, raptor, libsbml
# and MKL,CLAPACK LAPACK on non-apple
# for apple we set the Accelerate framework

set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${CLAPACK_LIBRARIES})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CLAPACK_LINKER_FLAGS}")

if(ENABLE_COPASI_SEDML)
  set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${LIBSEDML_LIBRARY})
endif()

set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${LIBSBML_LIBRARY})
set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${RAPTOR_LIBRARY})
set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${EXPAT_LIBRARY})

if (APPLE)
  FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation REQUIRED)
  MARK_AS_ADVANCED (COREFOUNDATION_LIBRARY)
  SET(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${COREFOUNDATION_LIBRARY})
endif (APPLE)
