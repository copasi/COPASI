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

cmake_minimum_required (VERSION 2.6)


project (COPASI)
cmake_policy(SET CMP0011 NEW)

include (common.cmake)

execute_process(
	COMMAND "${CMAKE_COMMAND}"
	ARGS -DSRC_DIRECTORY=\"${CMAKE_SOURCE_DIR}\"
		 -P "${CMAKE_SOURCE_DIR}/delete-qmake-files.cmake"

	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	)

set(COPASI_SOURCES)
set(COPASI_HEADERS)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CopasiVersion.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CopasiVersion.h.in ${CMAKE_CURRENT_SOURCE_DIR}/CopasiVersion.h)
endif (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CopasiVersion.h)

include(CopasiDataModel/CMakeLists.txt)
include(MIRIAM/CMakeLists.txt)
include(commandline/CMakeLists.txt)
include(compareExpressions/CMakeLists.txt)
include(crosssection/CMakeLists.txt)
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


add_library(libCOPASI STATIC ${COPASI_SOURCES} ${COPASI_HEADERS})
target_link_libraries(libCOPASI ${CLAPACK_LIBRARIES} ${RAPTOR_LIBRARY} ${LIBSBML_LIBRARY} ${EXPAT_LIBRARIES})
set_target_properties (libCOPASI PROPERTIES OUTPUT_NAME "COPASISE")

if(ENABLE_COPASI_SEDML)
target_link_libraries(libCOPASI ${LIBSEDML_LIBRARY})
endif()


#need to link against iconv
if (NOT (WIN32 AND NOT CYGWIN) AND NOT APPLE)
  if (ICONV_LIBRARIES)
  target_link_libraries(libCOPASI ${ICONV_LIBRARIES})
  endif()
endif()

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
  add_dependencies(CopasiSE libCOPASI ${SE_DEPENDENCIES})
endif(BUILD_SE)


if(BUILD_GUI)

  include(${QT_USE_FILE})

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

# add the directory for UNDO framework
if(ENABLE_COPASI_UNDO)
include(undoFramework/CMakeLists.txt)
endif()

set(COPASI_UI_MOC_OPTIONS)
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

if (ENABLE_SBW_INTEGRATION)
  set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_SBW_INTEGRATION=1)
  include_directories(${SBW_INCLUDE_DIR})
  add_definitions(-DCOPASI_SBW_INTEGRATION)
endif(ENABLE_SBW_INTEGRATION)

#if (COPASI_UI_MOC_OPTIONS)
#  message(STATUS "Mocing with options: ${COPASI_UI_MOC_OPTIONS}")
#endif(COPASI_UI_MOC_OPTIONS)
#
set(HEADERS_UI_MOC)
set(HEADERS_UI_FORMS)

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

foreach (dir
  barChart layoutUI MIRIAMUI plotUI tex UI wizard qlayout
)

  string(TOUPPER ${dir} suffix)
  #message(STATUS "Mocing files for subdir: ${dir}")

  set(TEMP_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -p${dir})

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
  include_directories(${CMAKE_CURRENT_BINARY_DIR}/${dir})
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${dir})
endforeach()


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_BINARY_DIR})
include_directories(${LIBSBML_INCLUDE_DIR})
include_directories(${QWT_INCLUDE_DIR})
include_directories(${QWTPLOT3D_INCLUDE_DIR})
include_directories(${QT_QTWEBKIT_INCLUDE_DIR})
include_directories(${QT_QTXML_INCLUDE_DIR})
include_directories(${QT_QTSVG_INCLUDE_DIR})

if(ENABLE_COPASI_SEDML)
include_directories(${LIBSEDML_INCLUDE_DIR})
endif()

add_library(libCOPASIUI STATIC ${COPASI_UI_SOURCES} ${COPASI_UI_HEADERS} ${HEADERS_UI_FORMS} ${COPASI_RCC_SOURCES} ${HEADERS_UI_MOC})
target_link_libraries(libCOPASIUI libCOPASI ${OPENGL_glu_LIBRARY} ${QT_QTOPENGL_LIBRARY}  ${QWT_LIBRARY} ${QT_LIBRARIES} ${QT_QTSVG_LIBRARY} ${MML_LIBRARY})
set_target_properties (libCOPASIUI PROPERTIES OUTPUT_NAME "COPASIUI")

  set(UI_LIBS
    libCOPASIUI
  )

   set(UI_DEPENDENCIES
     libCOPASIUI
   )

   #the mml widget is only build if the HAVE_MML variable is set
   if(HAVE_MML)
    add_subdirectory(mml)
    set(UI_LIBS ${UI_LIBS} mml)
    set(UI_DEPENDENCIES ${UI_DEPENDENCIES} mml)
  endif (HAVE_MML)

  add_subdirectory(CopasiUI)
  add_dependencies(CopasiUI ${SE_DEPENDENCIES} libCOPASIUI ${UI_DEPENDENCIES})

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
