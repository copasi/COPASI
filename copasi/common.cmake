# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
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



# if(NOT COPASI_COMMON_INCLUDED)
# set (COPASI_COMMON_INCLUDED ON)

# set(UI_LIBS libCOPASIUI )

# include_directories(BEFORE ${CMAKE_BINARY_DIR})
# link_directories(${CMAKE_BINARY_DIR}/copasi)

set(SE_LIBS  libCOPASISE-static)
set(SE_DEPENDENCIES  libCOPASISE-static)

# set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${CLAPACK_LIBRARIES})
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CLAPACK_LINKER_FLAGS}")

# set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${LIBSBML_LIBRARY})
# set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${RAPTOR_LIBRARY})
# set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${EXPAT_LIBRARY})
# set(SE_EXTERNAL_LIBS ${SE_EXTERNAL_LIBS} ${CROSSGUID_LIBRARY})




# endif()
