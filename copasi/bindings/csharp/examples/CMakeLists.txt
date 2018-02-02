####################################################################
#
# CMake Build Script for COPASI C# examples
#

macro(ADJUST_ENVIRONMENT target)

if (APPLE)
# adjust DYLD_LIBRARY_PATH
set_tests_properties(${target} PROPERTIES ENVIRONMENT DYLD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/../:$<TARGET_FILE_DIR:binding_csharp_native_lib>:$ENV{DYLD_LIBRARY_PATH})
elseif(UNIX)
# adjust LD_LIBRARY_PATH
set_tests_properties(${target} PROPERTIES ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/../:$<TARGET_FILE_DIR:binding_csharp_native_lib>:$ENV{LD_LIBRARY_PATH})
else()
# adjust path variable
SET (NEW_PATH "${CMAKE_CURRENT_BINARY_DIR}/../\\;$<TARGET_FILE_DIR:binding_csharp_native_lib>\\;$ENV{PATH}")
STRING(REPLACE "\\;" ";" NEW_PATH "${NEW_PATH}")
STRING(REPLACE ";" "\\;" NEW_PATH "${NEW_PATH}")
set_tests_properties(${target} PROPERTIES ENVIRONMENT PATH=${NEW_PATH})
endif()

endmacro()

foreach( example
  
  example1
  example2
  example3
  example4
  example5
  example6
  example7
  example8
  example9
  exampleMathExport
  exampleParameterSets
  printUnsupportedAnnotation
  process_callback
  
)

  ADD_CUSTOM_COMMAND(  
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${example}.exe
    COMMAND "${CSHARP_COMPILER}"
    ARGS -r:${CMAKE_CURRENT_BINARY_DIR}/../copasicsP.dll
      -target:exe
      -out:${example}.exe
      ${CSHARP_EXTRA_ARGS}
      ${CMAKE_CURRENT_SOURCE_DIR}${PATH_SEP}${example}.cs
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
    COMMENT "Build C# example: ${example}") 
  
  add_custom_target(exmple_cs_${example} ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${example}.exe)
  add_dependencies(exmple_cs_${example} binding_csharp_managed_lib)
endforeach()

set(CS_INTERPRETER)
if (NOT WIN32)
set(CS_INTERPRETER mono)
endif()

add_test(NAME test_cs_example1
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example1.exe
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example1)

add_test(NAME test_cs_example2
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example2.exe
                 ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator.cps
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example2)

add_test(NAME test_cs_example3
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example3.exe
                 ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator-model.xml
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example3)

add_test(NAME test_cs_example4
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example4.exe
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example4)

add_test(NAME test_cs_example5
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example5.exe
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example5)

add_test(NAME test_cs_example6
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example6.exe
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example6)

add_test(NAME test_cs_example7
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example7.exe
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example7)

add_test(NAME test_cs_example8
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example8.exe
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example8)

add_test(NAME test_cs_example9
         COMMAND ${CS_INTERPRETER} ${CMAKE_CURRENT_BINARY_DIR}/example9.exe
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
)
ADJUST_ENVIRONMENT(test_cs_example9)


