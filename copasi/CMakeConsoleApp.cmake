# Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# TODO set libraries and library paths
# for expat, raptor, libsbml
# and MKL,CLAPACK LAPACK on non-apple
# for apple we set the Accelerate framework

set(SE_LIBS ${SE_LIBS} ${RAPTOR_LIBRARY})
set(SE_LIBS ${SE_LIBS} ${LIBSBML_LIBRARY})
set(SE_LIBS ${SE_LIBS} ${EXPAT_LIBRARY})

if (APPLE)
   FIND_LIBRARY(ACCELERATE_LIBRARY Accelerate REQUIRED)
   MARK_AS_ADVANCED (ACCELERATE_LIBRARY)
   SET(SE_LIBS ${ACCELERATE_LIBRARY} ${SE_LIBS})
   
   FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation REQUIRED)
   MARK_AS_ADVANCED (COREFOUNDATION_LIBRARY)
   SET(SE_LIBS ${COREFOUNDATION_LIBRARY} ${SE_LIBS})
    
else (APPLE)

  if (MKL_FOUND)
   set(SE_LIBS ${MKL_LIBRARY} ${SE_LIBS}) 
  else (MKL_FOUND)
    if (CLAPACK_FOUND)
          set(SE_LIBS ${SE_LIBS} ${LAPACK_CLAPACK_LIBRARY} ) 
          set(SE_LIBS ${SE_LIBS} ${LAPACK_BLAS_LIBRARY}    ) 
          set(SE_LIBS ${SE_LIBS} ${LAPACK_F2C_LIBRARY}     ) 
    else (CLAPACK_FOUND)
      if (LAPACK_FOUND)
          set(SE_LIBS ${LAPACK_LINKER_FLAGS} ${SE_LIBS}) 
      else (LAPACK_FOUND)
        # just to be on the safe side
        message(FATAL_ERROR "No lapack implementation available. Please specify either the LAPACK_LIBRARIES or CLAPACK_LIBRARIES variable.")
        #message("You should never have ended up here. Please informa the COPASI developers.")
        #return()
      endif (LAPACK_FOUND)
    endif (CLAPACK_FOUND)
  endif (MKL_FOUND)

endif (APPLE)

