###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., University of Heidelberg, and The University
# of Manchester.
# All rights reserved.
#
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.
#
# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.
#
###############################################################################

cmake_minimum_required (VERSION 2.8.8)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 OLD)
endif(POLICY CMP0048)

project (COPASI)
cmake_policy(SET CMP0011 NEW)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 OLD)
endif(POLICY CMP0048)

if(POLICY CMP0043)
  cmake_policy(SET CMP0043 OLD)
endif(POLICY CMP0043)


if (COPASI_INSTALL_C_API)
  include (CMakePackageConfigHelpers)
endif(COPASI_INSTALL_C_API)

include (common.cmake)

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
include(trajectory/CMakeLists.txt)
include(tss/CMakeLists.txt)
include(tssanalysis/CMakeLists.txt)
include(undo/CMakeLists.txt)
include(utilities/CMakeLists.txt)
include(xml/CMakeLists.txt)


if(ENABLE_COPASI_SEDML)
include(sedml/CMakeLists.txt)
include_directories(${LIBSEDML_INCLUDE_DIR})
endif()


include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/.."
  ${RAPTOR_INCLUDE_DIR}
  ${LIBEXPAT_INCLUDE_DIR}
  ${LAPACK_INCLUDE_DIR}
  ${LIBSBML_INCLUDE_DIR}

)

#need to include iconv dir
if (NOT (WIN32 AND NOT CYGWIN) AND NOT APPLE)
  if (EXISTS ${ICONV_INCLUDE_DIR})
  include_directories(${ICONV_INCLUDE_DIR})
  endif()
endif()



if (APPLE AND CMAKE_GENERATOR STREQUAL "Xcode" OR DISABLE_CORE_OBJECT_LIBRARY)
add_library (libCOPASISE-static STATIC ${COPASI_SOURCES} ${COPASI_HEADERS})
else()
add_library (libCOPASISE-core OBJECT ${COPASI_SOURCES} ${COPASI_HEADERS})
add_library (libCOPASISE-static STATIC $<TARGET_OBJECTS:libCOPASISE-core>)
endif()
set_target_properties (libCOPASISE-static PROPERTIES OUTPUT_NAME "COPASISE")

if(ENABLE_COPASI_SEDML)
  target_link_libraries(libCOPASISE-static ${LIBSEDML_LIBRARY})
  if (${LIBNUML_LIBRARY})
  target_link_libraries(libCOPASISE-static ${LIBNUML_LIBRARY})
  endif()
endif()

target_link_libraries(libCOPASISE-static ${RAPTOR_LIBRARY} ${LIBSBML_LIBRARY} ${EXPAT_LIBRARIES} ${EXPAT_LIBRARY} ${CLAPACK_LIBRARIES})

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
    # install headers
    foreach (file ${COPASI_HEADERS})
      get_filename_component(dir ${file} DIRECTORY)
      string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} include/copasi destination ${dir})
      install(FILES ${file} DESTINATION ${destination})
    endforeach()

    install(TARGETS libCOPASISE-static EXPORT libcopasise-static-config
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        ${INCLUDE_DESTINATION}
        )

    install (EXPORT libcopasise-static-config
        DESTINATION lib/cmake
        )

    WRITE_BASIC_PACKAGE_VERSION_FILE(
        ${CMAKE_CURRENT_BINARY_DIR}/libcopasise-static-config-version.cmake
        VERSION ${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}
        COMPATIBILITY AnyNewerVersion
        )

    install (FILES
        ${CMAKE_CURRENT_BINARY_DIR}/libcopasise-static-config-version.cmake
        DESTINATION lib/cmake)

endif(COPASI_INSTALL_C_API)


if(ENABLE_LIBCOPASISE_SHARED)

  if (APPLE AND CMAKE_GENERATOR STREQUAL "Xcode" OR DISABLE_CORE_OBJECT_LIBRARY)
    add_library (libCOPASISE-shared SHARED ${COPASI_SOURCES} ${COPASI_HEADERS})
  else()
    add_library (libCOPASISE-shared SHARED $<TARGET_OBJECTS:libCOPASISE-core>)
  endif()

  set_target_properties (libCOPASISE-shared PROPERTIES OUTPUT_NAME "COPASISE")

  if(ENABLE_COPASI_SEDML)
    target_link_libraries(libCOPASISE-shared ${LIBSEDML_LIBRARY})
  endif()

  target_link_libraries(libCOPASISE-shared ${RAPTOR_LIBRARY} ${LIBSBML_LIBRARY} ${EXPAT_LIBRARIES} ${CLAPACK_LIBRARIES})
  
  #need to link against iconv
  if (NOT (WIN32 AND NOT CYGWIN) AND NOT APPLE)
    if (ICONV_LIBRARIES)
      target_link_libraries(libCOPASISE-shared ${ICONV_LIBRARIES})
    endif()
  endif()

  if (COPASI_INSTALL_C_API)

      install(TARGETS libCOPASISE-shared EXPORT libcopasise-shared-config
          RUNTIME DESTINATION bin
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib
          ${INCLUDE_DESTINATION}
          )

      install (EXPORT libCOPASISE-shared-config
          DESTINATION lib/cmake
          )

      WRITE_BASIC_PACKAGE_VERSION_FILE(
          ${CMAKE_CURRENT_BINARY_DIR}/libcopasise-shared-config-version.cmake
          VERSION ${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}
          COMPATIBILITY AnyNewerVersion
          )

      install (FILES
          ${CMAKE_CURRENT_BINARY_DIR}/libcopasise-shared-config-version.cmake
          DESTINATION lib/cmake)


  endif(COPASI_INSTALL_C_API)

endif (ENABLE_LIBCOPASISE_SHARED)


# add all directories with libraries to the list of
# directories the linker searches
foreach (N ${})
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -I${PROJECT_SOURCE_DIR}/copasi/${N})
endforeach (N)

if(BUILD_CXX_EXAMPLES OR ENABLE_CSHARP OR ENABLE_JAVA OR ENABLE_PYTHON OR ENABLE_OCTAVE OR ENABLE_PERL OR ENABLE_R)
  add_subdirectory(bindings)
endif (BUILD_CXX_EXAMPLES OR ENABLE_CSHARP OR ENABLE_JAVA OR ENABLE_PYTHON OR ENABLE_OCTAVE OR ENABLE_PERL OR ENABLE_R)

option(BUILD_SE "Build the commandline executable for COPASI (CopasiSE)." ON)
mark_as_advanced(BUILD_SE)

if(BUILD_SE)
  add_subdirectory(CopasiSE)
  add_dependencies(CopasiSE libCOPASISE-static ${SE_DEPENDENCIES})
endif(BUILD_SE)


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
  include(undoFramework/CMakeLists.txt)
  include(undoUI/CMakeLists.txt)

  set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS})

  if(ENABLE_VERSIONING)
    include(versioning/CMakeLists.txt)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_Versioning=1)
  endif()

  if(ENABLE_PROVENANCE)
    include(Provenance/CMakeLists.txt)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_Provenance=1)
  endif()

  if (ENABLE_COMBINE_ARCHIVE)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DWITH_COMBINE_ARCHIVE=1)
  endif(ENABLE_COMBINE_ARCHIVE)
  
  if (ENABLE_COPASI_SEDML)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_SEDML=1)
  endif(ENABLE_COPASI_SEDML)
  
  if (ENABLE_SBW_INTEGRATION)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_SBW_INTEGRATION=1)
  endif(ENABLE_SBW_INTEGRATION)

  if (ENABLE_WITH_MERGEMODEL)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DWITH_MERGEMODEL=1)
  endif(ENABLE_WITH_MERGEMODEL)

  if (ENABLE_COPASI_BANDED_GRAPH)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_BANDED_GRAPH=1)
  endif(ENABLE_COPASI_BANDED_GRAPH)

  if (ENABLE_COPASI_NONLIN_DYN_OSCILLATION)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_NONLIN_DYN_OSCILLATION=1)
  endif()

  if (ENABLE_PE_EVENT_CREATION)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DWITH_PE_EVENT_CREATION=1)
  endif()

  if (ENABLE_COPASI_UNDO)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_UNDO=1)
  endif(ENABLE_COPASI_UNDO)

  if (QT5_USE_WEBENGINE)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DQT5_USE_WEBENGINE=1)
    add_definitions(-DQT5_USE_WEBENGINE=1)
  endif()

  if (QT_USE_TEXTBROWSER)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DQT_USE_TEXTBROWSER=1)
    add_definitions(-DQT_USE_TEXTBROWSER=1)
  endif()

if (ENABLE_SDE_SUPPORT)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DWITH_SDE_SUPPORT=1)
endif(ENABLE_SDE_SUPPORT)


  if (ENABLE_SBW_INTEGRATION)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_SBW_INTEGRATION=1)
    include_directories(${SBW_INCLUDE_DIR})
    add_definitions(-DCOPASI_SBW_INTEGRATION)
  endif(ENABLE_SBW_INTEGRATION)

  set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DQWT_VERSION=0x${QWT_VERSION_NUMERIC})

  if (EXTRA_MOC_OPTIONS)
    set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} ${EXTRA_MOC_OPTIONS})
  endif(EXTRA_MOC_OPTIONS)

  #if (COPASI_UI_MOC_OPTIONS)
  #  message(STATUS "Mocing with options: ${COPASI_UI_MOC_OPTIONS}")
  #endif(COPASI_UI_MOC_OPTIONS)
  #

  set(HEADERS_UI_MOC)
  set(HEADERS_UI_FORMS)

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

  foreach (dir barChart layoutUI MIRIAMUI plotUI tex UI wizard qlayout undoFramework undoUI)
    string(TOUPPER ${dir} suffix)
    #message(STATUS "Mocing files for subdir: ${dir}")
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

    include_directories(${CMAKE_CURRENT_BINARY_DIR}/${dir})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${dir})
  endforeach()


  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  include_directories(${CMAKE_BINARY_DIR})
  include_directories(${LIBSBML_INCLUDE_DIR})
  include_directories(${QWT_INCLUDE_DIR})
  include_directories(${QWTPLOT3D_INCLUDE_DIR})
  if (QT_QTWEBKIT_INCLUDE_DIR)
    include_directories(${QT_QTWEBKIT_INCLUDE_DIR})
  endif(QT_QTWEBKIT_INCLUDE_DIR)
  include_directories(${QT_QTXML_INCLUDE_DIR})
  include_directories(${QT_QTSVG_INCLUDE_DIR})

  if(ENABLE_COPASI_SEDML)
    include_directories(${LIBSEDML_INCLUDE_DIR})
  endif()

  add_library(libCOPASIUI STATIC ${COPASI_UI_SOURCES} ${COPASI_UI_HEADERS} ${HEADERS_UI_FORMS} ${COPASI_RCC_SOURCES} ${HEADERS_UI_MOC})
  QT_BIND_TO_TARGET(libCOPASIUI)
  target_link_libraries(libCOPASIUI libCOPASISE-static ${SBW_LIBRARY} ${QWT_LIBRARY} ${QWTPLOT3D_LIBRARY} ${MML_LIBRARY})
  
  if (OPENGL_glu_LIBRARY AND OPENGL_gl_LIBRARY)
  # need to specify the dependencies on the gl libraries on some linux systems
  # to ensure the order of these libraries during link is correct
  target_link_libraries(libCOPASIUI ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
  endif()

  set_target_properties (libCOPASIUI PROPERTIES OUTPUT_NAME "COPASIUI")

  set(UI_LIBS libCOPASIUI)
  set(UI_DEPENDENCIES libCOPASIUI)

  #the mml widget is only build if the HAVE_MML variable is set
  if(HAVE_MML)
    add_subdirectory(mml)
    set(UI_LIBS ${UI_LIBS} mml)
    set(UI_DEPENDENCIES ${UI_DEPENDENCIES} mml)
  endif (HAVE_MML)

  if (COPASI_INSTALL_C_API)
    install(TARGETS libCOPASIUI EXPORT libcopasiui-config
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib
      ${INCLUDE_DESTINATION}
      )

    install (EXPORT libcopasiui-config
      DESTINATION lib/cmake
      )

    WRITE_BASIC_PACKAGE_VERSION_FILE(
      ${CMAKE_CURRENT_BINARY_DIR}/libcopasiui-config-version.cmake
      VERSION ${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}
      COMPATIBILITY AnyNewerVersion
      )

    install (FILES
      ${CMAKE_CURRENT_BINARY_DIR}/libcopasiui-config-version.cmake
      DESTINATION lib/cmake)
  endif(COPASI_INSTALL_C_API)

  add_subdirectory(CopasiUI)
  add_dependencies(CopasiUI ${SE_DEPENDENCIES} libCOPASIUI ${UI_DEPENDENCIES})

  option(BUILD_VIEWCURRENT "Build the viewer for optimization / fitting tasks (ViewCurrent)." OFF)
  mark_as_advanced(BUILD_VIEWCURRENT)

  if(BUILD_VIEWCURRENT)
    add_subdirectory(ViewCurrentUI)
  endif(BUILD_VIEWCURRENT)

  if (COPASI_INSTALL_C_API)
    # install headers
    foreach (file ${COPASI_UI_HEADERS})
      get_filename_component(dir ${file} DIRECTORY)
      string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} include/copasi destination ${dir})
      install(FILES ${file} DESTINATION ${destination})
    endforeach()
  endif(COPASI_INSTALL_C_API)
endif(BUILD_GUI)

option(BUILD_COPASISBW "Build the CopasiML to SBML L3V1 tanslator for SBW." OFF)
mark_as_advanced(BUILD_COPASISBW)

if(BUILD_COPASISBW AND SBW_FOUND)
  add_subdirectory(CopasiSBW)
endif(BUILD_COPASISBW AND SBW_FOUND)
