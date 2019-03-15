####################################################################
#
# CMake Build Script for java examples
#
# 

find_package(Java COMPONENTS Development REQUIRED)

file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} CURRENT_BIN)
file(TO_NATIVE_PATH ${COPASI_JAR} CURRENT_JAR )
file(TO_NATIVE_PATH $<TARGET_FILE_DIR:binding_java_lib> LIBRARY_PATH)
  

foreach(file 
    example1
    example2
    example3
    example4
    example5
    example6
    example7
    example8
    example9
    example10
    exampleMathExport
    printUnsupportedAnnotation
    exampleParameterSets
    processCallback
    )
  
    
  file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${file}.java CURRENT_FILE)
  ADD_CUSTOM_COMMAND(  
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${file}.class
    COMMAND "${Java_JAVAC_EXECUTABLE}"
    ARGS -cp ".${FILE_SEP}\"${CURRENT_JAR}\"${FILE_SEP}${CMAKE_CURRENT_SOURCE_DIR}"
       ${CURRENT_FILE}
       -source ${JAVA_COMPATIBILITY}
       -target ${JAVA_COMPATIBILITY}
       -d ${CMAKE_CURRENT_BINARY_DIR}
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${file}.java
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Build java example ${file}"
  ) 
  add_custom_target(example_java_${file} ALL 
    DEPENDS 
    ${CMAKE_CURRENT_BINARY_DIR}/${file}.class 
    SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/${file}.java
    )
  add_dependencies(example_java_${file} binding_java_jar)
  
endforeach()


add_test(NAME test_java_example1
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example1
)


add_test(NAME test_java_example2
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example2
         ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator.cps
)


add_test(NAME test_java_example3
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example3
         ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator-model.xml
)


add_test(NAME test_java_example4
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example4
)


add_test(NAME test_java_example5
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example5
)


add_test(NAME test_java_example6
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example6
)


add_test(NAME test_java_example7
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example7
)


add_test(NAME test_java_example8
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example8
)


add_test(NAME test_java_example9
         COMMAND ${Java_JAVA_EXECUTABLE} 
         -cp ".${FILE_SEP}${CURRENT_JAR}${FILE_SEP}"
         -Djava.library.path=$<TARGET_FILE_DIR:binding_java_lib>
         example9
)
