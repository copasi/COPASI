# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 


include (${CMAKE_SOURCE_DIR}/copasi/common.cmake)

if (NOT Qt5_FOUND)
include(${QT_USE_FILE})
endif()

#setup SBW
if (ENABLE_SBW_INTEGRATION)
set(UI_EXTERNAL_LIBS ${UI_EXTERNAL_LIBS} ${SBW_LIBRARIES})
include_directories(BEFORE ${SBW_INCLUDE_DIR})
endif()

#setup qwt
set(UI_EXTERNAL_LIBS ${UI_EXTERNAL_LIBS} ${QWT_LIBRARY})
include_directories(BEFORE ${QWT_INCLUDE_DIR})

#setup qwtplot3d
set(UI_EXTERNAL_LIBS ${UI_EXTERNAL_LIBS} ${QWTPLOT3D_LIBRARY})
include_directories(BEFORE ${QWTPLOT3D_INCLUDE_DIR})

#setup mml
if(ENABLE_MML)
set(UI_EXTERNAL_LIBS ${UI_EXTERNAL_LIBS} ${MML_LIBRARY})
include_directories(BEFORE ${MML_INCLUDE_DIR})
endif(ENABLE_MML)

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_BINARY_DIR}/copasi)
include_directories(${CMAKE_BINARY_DIR}/copasi/UI)

