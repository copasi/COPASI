# Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
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

cmake_minimum_required (VERSION 2.8.12)
project (sbml-unittests)

include_directories(
	${COPASI_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CPPUNIT_INCLUDE_DIR}
)

set(SOURCES
  utilities.cpp
  test000001.cpp
  test000002.cpp
  test000003.cpp
  test000004.cpp
  test000005.cpp
  test000006.cpp
  test000007.cpp
  test000008.cpp
  test000009.cpp
  test000010.cpp
  test000011.cpp
  test000012.cpp
  test000013.cpp
  test000014.cpp
  test000015.cpp
  test000016.cpp
  test000017.cpp
  test000018.cpp
  test000019.cpp
  test000020.cpp
  test000021.cpp
  test000022.cpp
  test000023.cpp
  test000024.cpp
  test000025.cpp
  test000026.cpp
  test000027.cpp
  test000028.cpp
  test000029.cpp
  test000030.cpp
  test000031.cpp
  test000032.cpp
  test000033.cpp
  test000034.cpp
  test000035.cpp
  test000036.cpp
  test000037.cpp
  test000038.cpp
  test000039.cpp
  test000040.cpp
  test000041.cpp
  test000042.cpp
  test000043.cpp
  test000044.cpp
  test000045.cpp
  test000046.cpp
  test000047.cpp
  test000048.cpp
  test000049.cpp
  test000050.cpp
  test000051.cpp
  test000052.cpp
  test000053.cpp
  test000054.cpp
  test000055.cpp
  test000056.cpp
  test000057.cpp
  test000058.cpp
  test000059.cpp
  test000060.cpp
  test000061.cpp
  test000062.cpp
  test000063.cpp
  test000064.cpp
  test000065.cpp
  test000066.cpp
  test000067.cpp
  test000068.cpp
  test000069.cpp
  test000070.cpp
  test000071.cpp
  test000072.cpp
  test000073.cpp
  test000074.cpp
  test000075.cpp
  test000076.cpp
  test000077.cpp
  test000078.cpp
  test000079.cpp
  test000080.cpp
  test000081.cpp
  test000082.cpp
  test000083.cpp
  test000084.cpp
  test000085.cpp
  test000086.cpp
  test000087.cpp
  test000088.cpp
  test000089.cpp
  test000090.cpp
  test000091.cpp
  test000092.cpp
  test000093.cpp
  test000094.cpp
  test000095.cpp
  test000096.cpp
  test000097.cpp
  test000098.cpp
  test000099.cpp
  test000100.cpp
  test000101.cpp
  test000102.cpp
  test000103.cpp
  test000104.cpp
  test.cpp
)

add_executable(sbml-unittests ${SOURCES})

target_link_libraries(sbml-unittests libCOPASISE-static ${CPPUNIT_LIBRARY})

add_test(NAME run_sbml_unittests COMMAND ${CMAKE_CURRENT_BINARY_DIR}/sbml-unittests )
#set_tests_properties(run_sbml_unittests PROPERTIES FAIL_REGULAR_EXPRESSION "!!!FAILURES!!!")
set_tests_properties(run_sbml_unittests PROPERTIES PASS_REGULAR_EXPRESSION "Failures: 3")
