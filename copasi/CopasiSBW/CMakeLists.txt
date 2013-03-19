cmake_minimum_required (VERSION 2.8)
project (CopasiSBW)

if (SBW_FOUND)

set(SBW_SOURCES SBWTranslator.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SBW_INCLUDE_DIR})
include(../CMakeConsoleApp.cmake)


set(CopasiSBW_UI_FLAGS)
if(WIN32 AND NOT CYGWIN)
    set(CopasiSBW_UI_FLAGS WIN32)
    if(MSVC OR USING_INTEL)
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup ")
    endif(MSVC OR USING_INTEL)  
endif(WIN32 AND NOT CYGWIN)

add_executable(CopasiSBW ${CopasiSBW_UI_FLAGS} ${SBW_SOURCES})
target_link_libraries(CopasiSBW libCOPASI ${SE_EXTERNAL_LIBS} ${SE_LIBS} ${SBW_LIBRARIES})

if (UNIX AND NOT APPLE)
target_link_libraries(CopasiSBW pthread z)
endif()

install(TARGETS CopasiSBW DESTINATION bin)

endif(SBW_FOUND)