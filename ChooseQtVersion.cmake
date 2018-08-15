# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

cmake_minimum_required(VERSION 3.1.0)

set(SELECT_QT "Any" CACHE STRING "The prefered Qt version one of: Qt5, Qt4 or Any" )
if (DEFINED SELECT_QT)
  if (NOT (${SELECT_QT} MATCHES "Qt5" OR
           ${SELECT_QT} MATCHES "Qt4" OR
           ${SELECT_QT} MATCHES "Any"))
    message(WARNING "Unsupported Qt version: ${SELECT_QT}. Selecting best available.")
    set(SELECT_QT " Any")
  endif ()
else ()
  set(SELECT_QT " Any")
endif(DEFINED SELECT_QT)

if (${SELECT_QT} MATCHES "Any")
  set(QT_FIND_MODE QUIET)
else ()
  set(QT_FIND_MODE REQUIRED)
endif()
  
macro(QT_FIND_MODULES)
  # Local variables
  set(_modules_qt4)
  set(_modules_qt5)

  # Prepare modules
  foreach(_module ${ARGN})
     list(APPEND _modules_qt4 Qt${_module})
     list(APPEND _modules_qt5 ${_module})
     if(_module MATCHES " Gui")
       list(APPEND _modules_qt5 "Widgets")
     endif(_module MATCHES " Gui")
  endforeach(_module ${ARGN})

  list(REMOVE_DUPLICATES _modules_qt4)
  list(REMOVE_DUPLICATES _modules_qt5)

  set (CMAKE_PREFIX_PATH_TMP ${CMAKE_PREFIX_PATH})

  if (DEFINED ENV{QTDIR})
    set (CMAKE_PREFIX_PATH $ENV{QTDIR})
  endif ()

  # Find Qt libraries
  if (${SELECT_QT} MATCHES "Qt5" OR
      ${SELECT_QT} MATCHES "Any")
    find_package(Qt5 ${QT_FIND_MODE} COMPONENTS ${_modules_qt5})
    
  endif()

  if (${SELECT_QT} MATCHES "Qt4" OR
      ${SELECT_QT} MATCHES "Any")
    find_package(Qt4 ${QT_FIND_MODE} COMPONENTS ${_modules_qt4})
  endif()

  set (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH_TMP})

  if (NOT (Qt5_FOUND OR Qt4_FOUND OR QT4_FOUND))
    message(FATAL_ERROR " Qt not found")
  endif (NOT (Qt5_FOUND OR Qt4_FOUND OR QT4_FOUND))

  if (Qt5_FOUND)
    message(STATUS "Using Qt5")
    set(QT_VERSION ${Qt5_VERSION})
    
    foreach(_m ${_modules_qt5})
      set(QT_INCLUDE_DIRS ${QT_INCLUDE_DIRS} ${Qt5${_m}_INCLUDE_DIRS})
      set(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5${_m}_LIBRARIES})
    endforeach(_m ${_modules_qt5})
    
    list(REMOVE_DUPLICATES QT_INCLUDE_DIRS)
  endif (Qt5_FOUND)

  if (Qt4_FOUND OR QT4_FOUND)
    message(STATUS "Using Qt4")
    include(${QT_USE_FILE}) 
    set(QT_VERSION ${Qt4_VERSION})
    set(QT_INCLUDE_DIRS ${QT_INCLUDES})
  endif (Qt4_FOUND OR QT4_FOUND)

  message (STATUS "${QT_INCLUDE_DIRS}")

endmacro(QT_FIND_MODULES)

macro(QT_USE_MODULES _target) 
  QT_FIND_MODULES(${ARGN}) 

  # Enable AUTOMOC
  set_target_properties(${_target} PROPERTIES AUTOMOC TRUE)

  if (Qt5_FOUND) 
    target_link_libraries(${_target} ${QT_LIBRARIES}) 
  else (Qt5_FOUND)
    if (Qt4_FOUND OR QT4_FOUND)
      include(${QT_USE_FILE}) 
      include_directories(${QT_INCLUDES}) 
      add_definitions(${QT_DEFINITIONS})
    endif (Qt4_FOUND OR QT4_FOUND)
  endif (Qt5_FOUND)
endmacro(QT_USE_MODULES)

macro(QT_BIND_TO_TARGET _target)
  if (Qt5_FOUND)
    target_link_libraries(${_target} ${QT_LIBRARIES}) 
  else (Qt5_FOUND)
    if (Qt4_FOUND OR QT4_FOUND)
      include(${QT_USE_FILE})
      include_directories(${QT_INCLUDES})
      add_definitions(${QT_DEFINITIONS})
      target_link_libraries(${_target} ${QT_LIBRARIES})
    endif (Qt4_FOUND OR QT4_FOUND)
  endif (Qt5_FOUND)
endmacro(QT_BIND_TO_TARGET)
