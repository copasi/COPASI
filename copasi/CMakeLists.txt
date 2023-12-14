# Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
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

###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
#
#
#
###############################################################################

cmake_minimum_required (VERSION 2.8.12...3.19.1)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project (COPASI VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")
cmake_policy(SET CMP0011 NEW)

if (COPASI_INSTALL_C_API)
  include (CMakePackageConfigHelpers)
endif(COPASI_INSTALL_C_API)

set(COPASI_SOURCES)
set(COPASI_HEADERS)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CopasiVersion.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CopasiVersion.h.in ${CMAKE_CURRENT_SOURCE_DIR}/CopasiVersion.h)
endif (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CopasiVersion.h)

file(GLOB COPASI_HEADERS *.h lapack/*.h GL/*.h)

include(CopasiDataModel/CMakeLists.txt)
include(MIRIAM/CMakeLists.txt)
include(core/CMakeLists.txt)
include(commandline/CMakeLists.txt)
include(compareExpressions/CMakeLists.txt)
include(crosssection/CMakeLists.txt)

if(ENABLE_ANALYTICS)
include(analytics/CMakeLists.txt)
endif()

include(elementaryFluxModes/CMakeLists.txt)
include(function/CMakeLists.txt)
include(layout/CMakeLists.txt)
include(lna/CMakeLists.txt)
include(lyap/CMakeLists.txt)
include(math/CMakeLists.txt)
include(model/CMakeLists.txt)
include(moieties/CMakeLists.txt)
include(odepack++/CMakeLists.txt)
include(OpenMP/CMakeLists.txt)
include(optimization/CMakeLists.txt)
include(output/CMakeLists.txt)
include(parameterFitting/CMakeLists.txt)
include(plot/CMakeLists.txt)

include(randomGenerator/CMakeLists.txt)
include(report/CMakeLists.txt)
include(sbml/CMakeLists.txt)
include(sbmlunit/CMakeLists.txt)
include(scan/CMakeLists.txt)
include(sensitivities/CMakeLists.txt)
include(steadystate/CMakeLists.txt)
include(timesens/CMakeLists.txt)
include(trajectory/CMakeLists.txt)
include(tss/CMakeLists.txt)
include(tssanalysis/CMakeLists.txt)
include(undo/CMakeLists.txt)
include(utilities/CMakeLists.txt)
include(xml/CMakeLists.txt)


include(sedml/CMakeLists.txt)

if(ENABLE_VERSIONING)
  include(versioning/CMakeLists.txt)
endif(ENABLE_VERSIONING)


###############################################################################
#
# utility macro for copying files only if they have changed, for this it is
# assumed that the source file is always created. Then the macro is called.
# If the target file will only be overwritten if it does not yet exist, or
# its content is different. At the end the source file will be removed.
#
macro(copy_if_different_and_remove source target)
# message(
# "
# copy_if_different_and_remove called with:
#     source = ${source}
#     target = ${target}
# "
# )
file(READ ${source} CONTENT)

if (EXISTS ${target})
    # message("target exists")
    file(READ ${target} CURRENT_CONTENT)
    string(COMPARE EQUAL ${CURRENT_CONTENT} ${CONTENT} IS_SAME)
    if (NOT ${IS_SAME})
        #message("content is different")
        file(WRITE ${target} ${CONTENT})
    endif()
else()
    #message("target does not exist")
    file(WRITE ${target} ${CONTENT})
endif()
endmacro()


set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS})

if (EXTRA_MOC_OPTIONS)
  set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} ${EXTRA_MOC_OPTIONS})
endif(EXTRA_MOC_OPTIONS)


###############################################################################
# convert options for config file

  if(ENABLE_TIME_SENS)
    set(WITH_TIME_SENS 1)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DWITH_TIME_SENS=1)
  endif(ENABLE_TIME_SENS)

  if(ENABLE_VERSIONING)
    set(COPASI_Versioning 1)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_Versioning=1)
  endif(ENABLE_VERSIONING)

  if(ENABLE_PROVENANCE)
    set(COPASI_Provenance 1)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_Provenance=1)
  endif(ENABLE_PROVENANCE)

  if (QT5_USE_DATAVISUALIZATION)
    set(WITH_QT5_VISUALIZATION 1)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DWITH_QT5_VISUALIZATION=1)
  endif(QT5_USE_DATAVISUALIZATION)
  
  if (ENABLE_SBW_INTEGRATION)
    set(COPASI_SBW_INTEGRATION 1)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_SBW_INTEGRATION=1)
  endif(ENABLE_SBW_INTEGRATION)

  if (ENABLE_COPASI_BANDED_GRAPH)
    set(COPASI_BANDED_GRAPH 1)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_BANDED_GRAPH=1)
  endif(ENABLE_COPASI_BANDED_GRAPH)

  if (ENABLE_COPASI_NONLIN_DYN_OSCILLATION)
    set(COPASI_NONLIN_DYN_OSCILLATION 1)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_NONLIN_DYN_OSCILLATION=1)
  endif(ENABLE_COPASI_NONLIN_DYN_OSCILLATION)

  if (QT5_USE_WEBENGINE)
    set(QT5_USE_WEBENGINE 1)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DQT5_USE_WEBENGINE=1)
  endif(QT5_USE_WEBENGINE)

  if (QT_USE_TEXTBROWSER)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DQT_USE_TEXTBROWSER=1)    
  endif()

  if (COPASI_USE_QWT)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_USE_QWT=1)    
  endif()
  
  if (COPASI_USE_QCUSTOMPLOT)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_USE_QCUSTOMPLOT=1)    
  endif()
  
  if (ENABLE_COPASI_PARAMETERFITTING_RESIDUAL_SCALING)
    set(COPASI_PARAMETERFITTING_RESIDUAL_SCALING 1)
  endif(ENABLE_COPASI_PARAMETERFITTING_RESIDUAL_SCALING)

  if (ENABLE_COPASI_EXTUNIT)
    set(COPASI_EXTUNIT 1)
  endif(ENABLE_COPASI_EXTUNIT)

  if (CLAPACK_NO_BLASWRAP)
    set(NO_BLAS_WRAP 1)
  endif(CLAPACK_NO_BLASWRAP)

  if(DEFINED F2C_HAVE_H)
    set(HAVE_F2C_H 1)
  endif()
  
  if (ICONV_SECOND_ARGUMENT_IS_CONST)
    set(COPASI_ICONV_CONST_CHAR 1)
  endif (ICONV_SECOND_ARGUMENT_IS_CONST)


  if(ENABLE_MML)
    set(HAVE_MML 1)
  endif(ENABLE_MML)

    
  if(ENABLE_COPASI_DEBUG_TRACE)
    set(COPASI_DEBUG_TRACE 1)
  endif(ENABLE_COPASI_DEBUG_TRACE)

  set(QWT_VERSION 0x0${QWT_VERSION_NUMERIC})
  set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DQWT_VERSION=0x0${QWT_VERSION_NUMERIC})

  if (CLAPACK_FOUND)
    set(USE_CLAPACK 1)
  elseif (USE_MKL)
    set(USE_MKL 1)
  elseif(USE_ACML)
    set(USE_ACML 1)
  elseif(LAPACK_FOUND)
    set(USE_LAPACK 1)
  endif()


###############################################################################
# write configuration options to headers

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h.tmp @ONLY)
# we only replace the config.h if changes were made, otherwise we would trigger
# rebuilds after every configuration change
copy_if_different_and_remove(${CMAKE_CURRENT_BINARY_DIR}/config.h.tmp ${CMAKE_CURRENT_BINARY_DIR}/config.h)
set(COPASI_HEADERS ${COPASI_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/config.h)

#need to include iconv dir
if (NOT (WIN32 AND NOT CYGWIN) AND NOT APPLE)
  if (EXISTS ${ICONV_INCLUDE_DIR})
  include_directories(${ICONV_INCLUDE_DIR})
  endif()
endif()



if (APPLE AND CMAKE_GENERATOR STREQUAL "Xcode" OR DISABLE_CORE_OBJECT_LIBRARY)
  add_library (libCOPASISE-static STATIC ${COPASI_SOURCES} ${COPASI_HEADERS})
  # target_compile_options(libCOPASISE-static PRIVATE -Werror -Wall -Wextra -Wsuggest-override)

  if (ENABLE_OMP)
    target_compile_options(libCOPASISE-static PRIVATE ${OpenMP_CXX_FLAGS})
  endif (ENABLE_OMP)
else()
  add_library (libCOPASISE-core OBJECT ${COPASI_SOURCES} ${COPASI_HEADERS})
  # add option to disable stack protector
  option(DISABLE_STACK_PROTECTOR "Disable stack protector" OFF)
  mark_as_advanced(DISABLE_STACK_PROTECTOR)
  if (NOT DISABLE_STACK_PROTECTOR)
  target_compile_options(libCOPASISE-core PRIVATE -fstack-protector-all)
  endif()
  target_link_libraries(libCOPASISE-core
    ${CROSSGUID_LIBRARY} 
    RAPTOR::RAPTOR
    ${LIBSBML_LIBRARY_NAME} 
    ${LIBSEDML_LIBRARY_NAME}
    ${LIBCOMBINE_LIBRARY_NAME}
    EXPAT::EXPAT
    ${CLAPACK_LIBRARIES} 
    ${NATIVEJIT_LIBRARY} 
    ${CPUFEATURES_LIBRARY}
  )

  add_library (libCOPASISE-static STATIC $<TARGET_OBJECTS:libCOPASISE-core>)

  if (ENABLE_OMP)
    target_compile_options(libCOPASISE-core PRIVATE ${OpenMP_CXX_FLAGS})
  endif (ENABLE_OMP)
endif()

set_target_properties (libCOPASISE-static PROPERTIES 
    OUTPUT_NAME "COPASISE"
    INCLUDE_DIRECTORIES "${COPASI_INCLUDE_DIRS}"
    )

target_link_libraries(libCOPASISE-static ${LIBSEDML_LIBRARY_NAME})
target_link_libraries(libCOPASISE-static ${LIBCOMBINE_LIBRARY_NAME})

if (APPLE)
  FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation REQUIRED)
  MARK_AS_ADVANCED (COREFOUNDATION_LIBRARY)
  target_link_libraries(libCOPASISE-static ${COREFOUNDATION_LIBRARY})
  target_include_directories(libCOPASISE-static PUBLIC ${CLAPACK_INCLUDE_DIR})
endif (APPLE)

target_link_libraries(libCOPASISE-static 
  ${CROSSGUID_LIBRARY} 
  RAPTOR::RAPTOR
  ${LIBSBML_LIBRARY_NAME} 
  EXPAT::EXPAT
  ${CLAPACK_LIBRARIES} 
  ${NATIVEJIT_LIBRARY} 
  ${CPUFEATURES_LIBRARY})

 if (EXTRA_LIBS)
   target_link_libraries(libCOPASISE-static ${EXTRA_LIBS})   
 else ()
   if (UNIX AND BLA_VENDOR AND "${BLA_VENDOR}" STREQUAL "Intel (MKL)")
     target_link_libraries(libCOPASISE-static -lpthread -lm)
   endif()
 endif(EXTRA_LIBS)

if (ENABLE_OMP)
  target_link_libraries(libCOPASISE-static OpenMP::OpenMP_CXX)
endif (ENABLE_OMP)

#need to link against iconv
if (NOT (WIN32 AND NOT CYGWIN) AND NOT APPLE)
  if (ICONV_LIBRARIES)
    target_link_libraries(libCOPASISE-static ${ICONV_LIBRARIES})
  endif()
endif()

SET(INCLUDE_DESTINATION)
if (${CMAKE_VERSION} VERSION_GREATER "2.8.11")
    SET(INCLUDE_DESTINATION INCLUDES DESTINATION include)
endif()

if (COPASI_INSTALL_C_API)
    # install config 
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config.h DESTINATION include/copasi)

    # install headers
    foreach (file ${COPASI_HEADERS})
      get_filename_component(dir ${file} DIRECTORY)
      string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} include/copasi destination ${dir})
      install(FILES ${file} DESTINATION ${destination})
    endforeach()

    # install CMakeModules /raid/shoops/git/COPASI/CMakeModules
    file(GLOB MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../CMakeModules/*.cmake)

    foreach (file ${MODULES})
      get_filename_component(dir ${file} DIRECTORY)
      string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/../ share/copasi/ destination ${dir})
      install(FILES ${file} DESTINATION ${destination})
    endforeach()

    install(TARGETS libCOPASISE-static EXPORT libcopasise-static-config
        RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        ${INCLUDE_DESTINATION}
        )

    install (EXPORT libcopasise-static-config
        DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake
        )

    WRITE_BASIC_PACKAGE_VERSION_FILE(
        ${CMAKE_CURRENT_BINARY_DIR}/libcopasise-static-config-version.cmake
        VERSION ${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}
        COMPATIBILITY AnyNewerVersion
        )

    install (FILES
        ${CMAKE_CURRENT_BINARY_DIR}/libcopasise-static-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

endif(COPASI_INSTALL_C_API)


if(ENABLE_LIBCOPASISE_SHARED)
  if (APPLE AND CMAKE_GENERATOR STREQUAL "Xcode" OR DISABLE_CORE_OBJECT_LIBRARY)
    add_library (libCOPASISE-shared SHARED ${COPASI_SOURCES} ${COPASI_HEADERS})

    if (ENABLE_OMP)
      target_compile_options(libCOPASISE-shared PRIVATE ${OpenMP_CXX_FLAGS})
    endif (ENABLE_OMP)
  else()
    add_library (libCOPASISE-shared SHARED $<TARGET_OBJECTS:libCOPASISE-core>)
  endif()


  set_target_properties (libCOPASISE-shared PROPERTIES OUTPUT_NAME "COPASISE")

  target_link_libraries(libCOPASISE-shared ${LIBSEDML_LIBRARY_NAME})

  target_link_libraries(libCOPASISE-shared RAPTOR::RAPTOR ${LIBSBML_LIBRARY_NAME} EXPAT::EXPAT ${CLAPACK_LIBRARIES})
  
  if (ENABLE_OMP)
    target_link_libraries(libCOPASISE-shared OpenMP::OpenMP_CXX)
  endif (ENABLE_OMP)


  #need to link against iconv
  if (NOT (WIN32 AND NOT CYGWIN) AND NOT APPLE)
    if (ICONV_LIBRARIES)
      target_link_libraries(libCOPASISE-shared ${ICONV_LIBRARIES})
    endif()
  endif()

  if (COPASI_INSTALL_C_API)

      install(TARGETS libCOPASISE-shared EXPORT libcopasise-shared-config
          RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
          LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
          ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
          ${INCLUDE_DESTINATION}
          )

      install (EXPORT libCOPASISE-shared-config
          DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake
          )

      WRITE_BASIC_PACKAGE_VERSION_FILE(
          ${CMAKE_CURRENT_BINARY_DIR}/libcopasise-shared-config-version.cmake
          VERSION ${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}
          COMPATIBILITY AnyNewerVersion
          )

      install (FILES
          ${CMAKE_CURRENT_BINARY_DIR}/libcopasise-shared-config-version.cmake
          DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)


  endif(COPASI_INSTALL_C_API)

endif (ENABLE_LIBCOPASISE_SHARED)


# add all directories with libraries to the list of
# directories the linker searches
foreach (N ${})
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -I${PROJECT_SOURCE_DIR}/copasi/${N})
endforeach (N)


if(BUILD_GUI)
  set(COPASI_RCC_SOURCES)
  set(COPASI_UI_SOURCES)
  set(COPASI_UI_HEADERS)
  set(COPASI_UI_FORMS)

  include(MIRIAMUI/CMakeLists.txt)
  
  include(barChart/CMakeLists.txt)
  
  include(layoutUI/CMakeLists.txt)
  
  include(qlayout/CMakeLists.txt)
  include(plotUI/CMakeLists.txt)
  include(tex/CMakeLists.txt)
  include(wizard/CMakeLists.txt)
  include(UI/CMakeLists.txt)
  include(undoUI/CMakeLists.txt)

  set(COPASI_UI_DIRECTORIES barChart layoutUI MIRIAMUI plotUI tex UI wizard qlayout undoFramework undoUI)
  
  if(ENABLE_VERSIONING)
    include(versioning/CMakeLists.txt)
    include(versioningUI/CMakeLists.txt)
    set(COPASI_UI_DIRECTORIES ${COPASI_UI_DIRECTORIES} versioningUI)
  endif()

  if(ENABLE_PROVENANCE)
    include(Provenance/CMakeLists.txt)
  endif()

  if (COPASI_UI_MOC_OPTIONS)
    message(STATUS "Mocing with options: ${COPASI_UI_MOC_OPTIONS}")
  endif(COPASI_UI_MOC_OPTIONS)
  
  set(HEADERS_UI_MOC)
  set(HEADERS_UI_FORMS)
  set(GUI_INCLUDE_DIRS)

  if (Qt6_FOUND)
  include(CMakeParseArguments)
  # qt5_wrap_ui(outfiles inputfile ... )


  if (NOT Qt6Widgets_UIC_EXECUTABLE OR NOT EXISTS "${Qt6Widgets_UIC_EXECUTABLE}")
    find_program(Qt6Widgets_UIC_EXECUTABLE
           NAMES uic uic.exe 
           DOC "Path to the uic executable"
           PATHS ${Qt6Widgets_DIR}/../../../bin/
                 ${Qt6Widgets_DIR}/../../../share/qt/libexec/
           )

    if (NOT EXISTS "${Qt6Widgets_UIC_EXECUTABLE}")
      message(FATAL_ERROR "Need UIC executable to compile GUI, it should be in: 
          ${Qt6Widgets_DIR}/../../../bin
          ${Qt6Widgets_DIR}/../../../share/qt/libexec
          ")
    endif()
  endif()

  MACRO(COPASI_QT6_WRAP_UI outfiles)
    set(options)
    set(oneValueArgs SUBDIR)
    set(multiValueArgs OPTIONS)    

    cmake_parse_arguments(_WRAP_UI "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  #get_cmake_property(_vars VARIABLES)
  #foreach(_name ${_vars})
  #  message("${_name}: ${${_name}})")
  #endforeach()

    set(ui_files ${_WRAP_UI_UNPARSED_ARGUMENTS})
    set(ui_options ${_WRAP_UI_OPTIONS})
    set(ui_subdir ${_WRAP_UI_SUBDIR})

    foreach(it ${ui_files})
        get_filename_component(outfile ${it} NAME_WE)
        get_filename_component(infile ${it} ABSOLUTE)
        set(outfile ${CMAKE_CURRENT_BINARY_DIR}/${ui_subdir}/ui_${outfile}.h)
        add_custom_command(OUTPUT ${outfile}
          COMMAND ${Qt6Widgets_UIC_EXECUTABLE}
          ARGS ${ui_options} -o ${outfile} ${infile}
          MAIN_DEPENDENCY ${infile} VERBATIM)
        list(APPEND ${outfiles} ${outfile})
    endforeach()
    
    set(${outfiles} ${${outfiles}} PARENT_SCOPE)
  ENDMACRO()
endif()


  if (Qt5_FOUND)
    include(CMakeParseArguments)
    # qt5_wrap_ui(outfiles inputfile ... )

    MACRO(COPASI_QT5_WRAP_UI outfiles)
      set(options)
      set(oneValueArgs SUBDIR)
      set(multiValueArgs OPTIONS)    

      cmake_parse_arguments(_WRAP_UI "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    #get_cmake_property(_vars VARIABLES)
    #foreach(_name ${_vars})
    #  message("${_name}: ${${_name}})")
    #endforeach()

      set(ui_files ${_WRAP_UI_UNPARSED_ARGUMENTS})
      set(ui_options ${_WRAP_UI_OPTIONS})
      set(ui_subdir ${_WRAP_UI_SUBDIR})

      foreach(it ${ui_files})
          get_filename_component(outfile ${it} NAME_WE)
          get_filename_component(infile ${it} ABSOLUTE)
          set(outfile ${CMAKE_CURRENT_BINARY_DIR}/${ui_subdir}/ui_${outfile}.h)
          add_custom_command(OUTPUT ${outfile}
            COMMAND ${Qt5Widgets_UIC_EXECUTABLE}
            ARGS ${ui_options} -o ${outfile} ${infile}
            MAIN_DEPENDENCY ${infile} VERBATIM)
          list(APPEND ${outfiles} ${outfile})
      endforeach()
      
      set(${outfiles} ${${outfiles}} PARENT_SCOPE)
    ENDMACRO()
  endif()

  MACRO (COPASI_QT4_WRAP_UI outfiles subdir )
    if (${CMAKE_VERSION} VERSION_LESS  "2.8.12")
      QT4_EXTRACT_OPTIONS(ui_files ui_options ${ARGN})
    else (${CMAKE_VERSION} VERSION_LESS  "2.8.12")
      QT4_EXTRACT_OPTIONS(ui_files ui_options ui_targets ${ARGN})
    endif (${CMAKE_VERSION} VERSION_LESS  "2.8.12")

    FOREACH (it ${ui_files})
      GET_FILENAME_COMPONENT(outfile ${it} NAME_WE)
      GET_FILENAME_COMPONENT(infile ${it} ABSOLUTE)
      SET(outfile ${CMAKE_CURRENT_BINARY_DIR}/${subdir}/ui_${outfile}.h) # Here we set output
      ADD_CUSTOM_COMMAND(OUTPUT ${outfile}
        COMMAND ${QT_UIC_EXECUTABLE}
        ARGS ${ui_options} -o ${outfile} ${infile}
        MAIN_DEPENDENCY ${infile})
      SET(${outfiles} ${${outfiles}} ${outfile})
    ENDFOREACH (it)
    
  ENDMACRO (COPASI_QT4_WRAP_UI)

  foreach (dir ${COPASI_UI_DIRECTORIES})
    string(TOUPPER ${dir} suffix)
    message(STATUS "Mocing files for subdir: ${dir}")
    set(TEMP_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -p${dir})
    
    if (Qt5_FOUND)
      if (TEMP_UI_MOC_OPTIONS)
        qt5_wrap_cpp(TEMP_UI_MOC ${HEADERS_${suffix}} OPTIONS ${TEMP_UI_MOC_OPTIONS})
      else()
        qt5_wrap_cpp(TEMP_UI_MOC ${dir} ${HEADERS_${suffix}})
      endif(TEMP_UI_MOC_OPTIONS)
      

      set(HEADERS_UI_MOC ${HEADERS_UI_MOC} ${TEMP_UI_MOC})
      
      if(FORMS_${suffix})
        #message(STATUS "uic'ing files for subdir: ${dir}")
        COPASI_QT5_WRAP_UI(TEMP_UI_FORMS SUBDIR "${dir}" ${FORMS_${suffix}})
      endif()
      
      set(HEADERS_UI_FORMS ${HEADERS_UI_FORMS} ${TEMP_UI_FORMS})
    elseif (Qt6_FOUND)
    
    if (TEMP_UI_MOC_OPTIONS)
      qt6_wrap_cpp(TEMP_UI_MOC ${HEADERS_${suffix}} OPTIONS ${TEMP_UI_MOC_OPTIONS})
    else()
      qt6_wrap_cpp(TEMP_UI_MOC ${dir} ${HEADERS_${suffix}})
    endif(TEMP_UI_MOC_OPTIONS)
  
    set(HEADERS_UI_MOC ${HEADERS_UI_MOC} ${TEMP_UI_MOC})
  
    if(FORMS_${suffix})
      #message(STATUS "uic'ing files for subdir: ${dir}")
      COPASI_QT6_WRAP_UI(TEMP_UI_FORMS SUBDIR "${dir}" ${FORMS_${suffix}})
    endif()
  
  set(HEADERS_UI_FORMS ${HEADERS_UI_FORMS} ${TEMP_UI_FORMS})
    else (Qt5_FOUND)
      if (TEMP_UI_MOC_OPTIONS)
        qt4_wrap_cpp(TEMP_UI_MOC ${HEADERS_${suffix}} OPTIONS ${TEMP_UI_MOC_OPTIONS})
      else()
        qt4_wrap_cpp(TEMP_UI_MOC ${dir} ${HEADERS_${suffix}})
      endif(TEMP_UI_MOC_OPTIONS)

      set(HEADERS_UI_MOC ${HEADERS_UI_MOC} ${TEMP_UI_MOC})

      if(FORMS_${suffix})
        #message(STATUS "uic'ing files for subdir: ${dir}")
        COPASI_QT4_WRAP_UI(TEMP_UI_FORMS "${dir}" ${FORMS_${suffix}})
      endif()
      
      set(HEADERS_UI_FORMS ${HEADERS_UI_FORMS} ${TEMP_UI_FORMS})
    endif (Qt5_FOUND)

    set (GUI_INCLUDE_DIRS ${GUI_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/${dir})
    
  endforeach()

  
  set(GUI_INCLUDE_DIRS ${GUI_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR})

  include_directories(${LIBSBML_INCLUDE_DIR})
  include_directories(${QWT_INCLUDE_DIR})
  include_directories(${QWTPLOT3D_INCLUDE_DIR})
  if (QT_QTWEBKIT_INCLUDE_DIR)
    include_directories(${QT_QTWEBKIT_INCLUDE_DIR})
  endif(QT_QTWEBKIT_INCLUDE_DIR)
  include_directories(${QT_QTXML_INCLUDE_DIR})
  include_directories(${QT_QTSVG_INCLUDE_DIR})

  if (NOT ${CMAKE_VERSION} VERSION_GREATER "2.8.11")
    include_directories(${GUI_INCLUDE_DIRS})
  endif()


  add_library(libCOPASIUI STATIC ${COPASI_UI_SOURCES} ${COPASI_UI_HEADERS} ${HEADERS_UI_FORMS} ${COPASI_RCC_SOURCES} ${HEADERS_UI_MOC})

  QT_BIND_TO_TARGET(libCOPASIUI)
  SET(UI_LIBS ${QWT_LIBRARY} ${MML_LIBRARY})
  if (NOT QT5_USE_DATAVISUALIZATION)
    SET(UI_LIBS ${UI_LIBS} ${QWTPLOT3D_LIBRARY})
  endif()
  
  if (COPASI_USE_QCUSTOMPLOT)
    SET(UI_LIBS ${UI_LIBS} QCP::QCP)  
  endif()
  
  if (${CMAKE_VERSION} VERSION_GREATER "2.8.11")
    target_include_directories(libCOPASIUI PUBLIC ${GUI_INCLUDE_DIRS})
    target_link_libraries(libCOPASIUI libCOPASISE-static ${UI_LIBS})
  else()
    target_link_libraries(libCOPASIUI libCOPASISE-static ${UI_LIBS})
  endif()
  
  
  if (OPENGL_glu_LIBRARY AND OPENGL_gl_LIBRARY)
  # need to specify the dependencies on the gl libraries on some linux systems
  # to ensure the order of these libraries during link is correct
  target_link_libraries(libCOPASIUI ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
  endif()


  if (NOT USING_INTEL)
    target_link_libraries(libCOPASIUI ${ZLIB_LIBRARY})
  endif (NOT USING_INTEL)
  
  if (ENABLE_SBW_INTEGRATION)
  target_link_libraries(libCOPASIUI SBW::SBW)
  endif(ENABLE_SBW_INTEGRATION)
  
  # On some linux systems we do require a link against the pthread library
  # as well as the libz library
  if (UNIX AND NOT APPLE)
    find_package(Threads)
    find_package(ZLIB)
    if (CMAKE_USE_PTHREADS_INIT)
      target_link_libraries(libCOPASIUI ${CMAKE_THREAD_LIBS_INIT})
    endif()
    if (ZLIB_FOUND)
      target_link_libraries(libCOPASIUI ${ZLIB_LIBRARIES})
    endif()
  endif()


  set_target_properties (libCOPASIUI PROPERTIES OUTPUT_NAME "COPASIUI")

  set(UI_LIBS libCOPASIUI)
  set(UI_DEPENDENCIES libCOPASIUI)

  if (COPASI_INSTALL_C_API_)
    install(TARGETS libCOPASIUI EXPORT libcopasiui-config
      RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
      LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
      ${INCLUDE_DESTINATION}
      )

    install (EXPORT libcopasiui-config
      DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake
      )

    WRITE_BASIC_PACKAGE_VERSION_FILE(
      ${CMAKE_CURRENT_BINARY_DIR}/libcopasiui-config-version.cmake
      VERSION ${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}
      COMPATIBILITY AnyNewerVersion
      )

    install (FILES
      ${CMAKE_CURRENT_BINARY_DIR}/libcopasiui-config-version.cmake
      DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

    # install headers
    foreach (file ${COPASI_UI_HEADERS})
      get_filename_component(dir ${file} DIRECTORY)
      string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} include/copasi destination ${dir})
      install(FILES ${file} DESTINATION ${destination})
    endforeach()
  endif(COPASI_INSTALL_C_API_)
endif(BUILD_GUI)


if(BUILD_CXX_EXAMPLES OR ENABLE_CSHARP OR ENABLE_JAVA OR ENABLE_PYTHON OR ENABLE_OCTAVE OR ENABLE_PERL OR ENABLE_R)
  add_subdirectory(bindings)
endif (BUILD_CXX_EXAMPLES OR ENABLE_CSHARP OR ENABLE_JAVA OR ENABLE_PYTHON OR ENABLE_OCTAVE OR ENABLE_PERL OR ENABLE_R)

option(BUILD_SE "Build the commandline executable for COPASI (CopasiSE)." ON)
mark_as_advanced(BUILD_SE)

if(BUILD_SE)
  add_subdirectory(CopasiSE)
endif(BUILD_SE)

if(BUILD_GUI)
  add_subdirectory(CopasiUI)

  option(BUILD_VIEWCURRENT "Build the viewer for optimization / fitting tasks (ViewCurrent)." OFF)
  mark_as_advanced(BUILD_VIEWCURRENT)

  if(BUILD_VIEWCURRENT)
    add_subdirectory(ViewCurrentUI)
  endif(BUILD_VIEWCURRENT)
endif(BUILD_GUI)

option(BUILD_COPASISBW "Build the CopasiML to SBML L3V1 tanslator for SBW." OFF)
mark_as_advanced(BUILD_COPASISBW)

if(BUILD_COPASISBW AND SBW_FOUND)
  add_subdirectory(CopasiSBW)
endif(BUILD_COPASISBW AND SBW_FOUND)
