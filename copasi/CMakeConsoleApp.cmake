# Copyright (C) 2012 - 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# TODO set libraries and library paths
# for expat, raptor, libsbml
# and MKL,CLAPACK LAPACK on non-apple
# for apple we set the Accelerate framework

set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${CLAPACK_LIBRARIES})
#   LAPACK LDFLAGS    = ${CLAPACK_LINKER_FLAGS}

if(ENABLE_COPASI_SEDML)
set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${LIBSEDML_LIBRARY})
endif()

set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${LIBSBML_LIBRARY})
set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${RAPTOR_LIBRARY})
set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${EXPAT_LIBRARY})

