# Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

include(${QT_USE_FILE})

if (ENABLE_SBW_INTEGRATION)
#setup SBW
set(UI_LIBS ${SBW_LIBRARIES} ${UI_LIBS})
include_directories(BEFORE ${SBW_INCLUDE_DIR})
endif()

#setup qwt
set(UI_LIBS ${QWT_LIBRARY} ${UI_LIBS})
include_directories(BEFORE ${QWT_INCLUDE_DIR})

#setup qwtplot3d
set(UI_LIBS ${QWTPLOT3D_LIBRARY} ${UI_LIBS})
include_directories(BEFORE ${QWTPLOT3D_INCLUDE_DIR})

