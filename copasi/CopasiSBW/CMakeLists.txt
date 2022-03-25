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

cmake_minimum_required (VERSION 2.8)

if (SBW_FOUND)

set(SBW_SOURCES SBWTranslator.cpp)

set(CopasiSBW_UI_FLAGS)
if(WIN32 AND NOT CYGWIN)
    set(CopasiSBW_UI_FLAGS WIN32)
    if(MSVC OR USING_INTEL)
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup ")
    endif(MSVC OR USING_INTEL)  
endif(WIN32 AND NOT CYGWIN)

add_executable(CopasiSBW ${CopasiSBW_UI_FLAGS} ${SBW_SOURCES})
target_link_libraries(CopasiSBW libCOPASISE-static SBW::SBW)

if (UNIX AND NOT APPLE)
target_link_libraries(CopasiSBW pthread z)
endif()

install(TARGETS CopasiSBW DESTINATION bin)

endif(SBW_FOUND)
