# Copyright (C) 2012 - 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

include(${QT_USE_FILE})

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
