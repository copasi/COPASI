####################################################################
#
# CMake Build Script for java examples
#
# 

find_package(Java COMPONENTS Development REQUIRED)

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
		)
	
	file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} CURRENT_BIN)
	file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/../copasi.jar CURRENT_JAR )
	file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${file}.java CURRENT_FILE)
		
	ADD_CUSTOM_COMMAND(	
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${file}.class
		COMMAND "${Java_JAVAC_EXECUTABLE}"
		ARGS -cp ".${FILE_SEP}\"${CURRENT_JAR}\"${FILE_SEP}${CMAKE_CURRENT_SOURCE_DIR}"
			 ${CURRENT_FILE}
			 -source 1.5
			 -target 1.5
			 -d ${CMAKE_CURRENT_BINARY_DIR}
		MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/../copasi.jar
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${file}.java
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
