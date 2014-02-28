####################################################################
#
# CMake Build Script for COPASI C# examples
#

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
