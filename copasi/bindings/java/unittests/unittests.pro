# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/unittests/unittests.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/01/12 10:09:25 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

CONFIG -= qt

TARGET = dummy

JAVAC_ARGS=-classpath ../copasi.jar:$$JUNIT_PATH
JAVA_ARGS=-Djava.library.path=.. $$JAVAC_ARGC

JAVA_SOURCE_FILE=Test_CreateSimpleModel.java \
                 Test_RunOptimization.java \
                 Test_RunSimulations.java \
                 Test_RunSteadyStateCalculation.java


contains(BUILD_OS, WIN32){
  unittest_jar.target = unittest.jar
  unittest_jar_source.depends = $$JAVA_SOURCE_FILES
  unittest_jar.commands = $(DEL_FILE) unittest.jar *.class && $$JAVA_HOME\bin\javac.exe $$JAVAC_ARGS -d . *.java && $$JAVA_HOME\bin\jar.exe cvf unittest.jar *.class 
  QMAKE_EXTRA_WIN_TARGETS += unittest_jar
  PRE_TARGETDEPS += ..\..\..\lib\COPASISE.lib
}
!contains(BUILD_OS, WIN32){
  unittest_jar.target = unittest.jar
  unittest_jar_source.depends = $$JAVA_SOURCE_FILES
  unittest_jar.commands = $(DEL_FILE) unittest.jar *.class && $$JAVA_HOME/bin/javac $$JAVAC_ARGS -d . *.java && $$JAVA_HOME/bin/jar cvf unittest.jar *.class 
  QMAKE_EXTRA_UNIX_TARGETS += unittest_jar
  PRE_TARGETDEPS += ../../../lib/libCOPASISE.a
}

PRE_TARGETDEPS += unittest.jar

