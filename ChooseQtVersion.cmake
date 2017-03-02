# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

cmake_minimum_required(VERSION 2.8.9)

option(PREFER_QT5 "Preferably to use Qt5 if possible" OFF)
option(NEED_QT5 "Fail if Qt5 not found" OFF)
set(QT5_FIND_MODE QUIET)
if (NEED_QT5)
  set(PREFER_QT5 ON)
  set(QT5_FIND_MODE REQUIRED)
endif()
 
macro(QT_USE_MODULES _target)
    # Enable AUTOMOC
    set_target_properties(${_target} PROPERTIES AUTOMOC TRUE)
    # Local variables
    set(_modules_qt4)
    set(_modules_qt5)
    # Prepare modules
    foreach(_module ${ARGN})
        list(APPEND _modules_qt4 Qt${_module})
        list(APPEND _modules_qt5 ${_module})
        if(_module MATCHES "Gui")
            list(APPEND _modules_qt5 "Widgets")
        endif(_module MATCHES "Gui")
    endforeach(_module ${ARGN})
    list(REMOVE_DUPLICATES _modules_qt4)
    list(REMOVE_DUPLICATES _modules_qt5)
    # Find Qt libraries
    if (PREFER_QT5)
      find_package(Qt5 ${QT5_FIND_MODE} COMPONENTS ${_modules_qt5})
    endif()

    if(Qt5_FOUND)
        qt5_use_modules(${_target} ${_modules_qt5})
    else(Qt5_FOUND)
        find_package(Qt4 QUIET COMPONENTS ${_modules_qt4})
        if(Qt4_FOUND OR QT4_FOUND)
            include(${QT_USE_FILE})
            include_directories(${QT_INCLUDES})
            add_definitions(${QT_DEFINITIONS})
            target_link_libraries(${_target} ${QT_LIBRARIES})
        endif(Qt4_FOUND OR QT4_FOUND)
    endif(Qt5_FOUND)
endmacro(QT_USE_MODULES)

macro(QT_FIND_MODULES)
    # Local variables
    set(_modules_qt4)
    set(_modules_qt5)
    # Prepare modules
    foreach(_module ${ARGN})
        list(APPEND _modules_qt4 Qt${_module})
        list(APPEND _modules_qt5 ${_module})
        if(_module MATCHES "Gui")
            list(APPEND _modules_qt5 "Widgets")
        endif(_module MATCHES "Gui")
    endforeach(_module ${ARGN})
    list(REMOVE_DUPLICATES _modules_qt4)
    list(REMOVE_DUPLICATES _modules_qt5)
    # Find Qt libraries
    if (PREFER_QT5)
      find_package(Qt5 ${QT5_FIND_MODE} COMPONENTS ${_modules_qt5})
    endif()
    if( NOT Qt5_FOUND)
        find_package(Qt4 QUIET COMPONENTS ${_modules_qt4})
        if(Qt4_FOUND OR QT4_FOUND)
            include(${QT_USE_FILE})
            include_directories(${QT_INCLUDES})
            add_definitions(${QT_DEFINITIONS})
        endif(Qt4_FOUND OR QT4_FOUND)
    endif( NOT Qt5_FOUND)
endmacro(QT_FIND_MODULES)

macro(QT_BIND_TO_TARGET _target)
    # Enable AUTOMOC
    #set_target_properties(${_target} PROPERTIES AUTOMOC TRUE)
    if(Qt5_FOUND)
        qt5_use_modules(${_target} ${_modules_qt5})
    else(Qt5_FOUND)
        if(Qt4_FOUND OR QT4_FOUND)
            include(${QT_USE_FILE})
            include_directories(${QT_INCLUDES})
            add_definitions(${QT_DEFINITIONS})
            target_link_libraries(${_target} ${QT_LIBRARIES})
        endif(Qt4_FOUND OR QT4_FOUND)
    endif(Qt5_FOUND)
endmacro(QT_BIND_TO_TARGET)
