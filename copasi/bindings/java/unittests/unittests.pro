# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/unittests/unittests.pro,v $ 
#   $Revision: 1.5 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/01/15 17:53:26 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

CONFIG -= qt

TEMPLATE=lib

include(../../../common.pri)


QMAKE_RUN_CXX = echo
QMAKE_RUN_CXX_IMP = echo
QMAKE_LINK_SHLIB_CMD = echo
QMAKE_LN_SHLIB = echo 

JAVAC_ARGS=-classpath ../copasi.jar:$$JUNIT_PATH
JAVA_ARGS=-Djava.library.path=.. $$JAVAC_ARGC

JAVA_SOURCE_FILES=Test_CreateSimpleModel.java \
                 Test_RunOptimization.java \
                 Test_RunSimulations.java \
                 Test_RunSteadyStateCalculation.java


contains(BUILD_OS, WIN32){
  unittests_jar.target = unittests.jar
  unittests_jar.depends = $$JAVA_SOURCE_FILES ..\copasi.jar 
  unittests_jar.commands = $(DEL_FILE)  $$unittests_jar.target org\COPASI\unittests\*.class  && $$JAVA_HOME\bin\javac.exe $$JAVAC_ARGS -d . $$JAVA_SOURCE_FILES && $$JAVA_HOME\bin\jar.exe cvf $$unittests_jar.target *.class 
  QMAKE_EXTRA_WIN_TARGETS += unittests_jar
  PRE_TARGETDEPS += ..\..\..\lib\COPASISE.lib
}
!contains(BUILD_OS, WIN32){
  unittests_jar.target = unittests.jar
  unittests_jar.depends = $$JAVA_SOURCE_FILES ../copasi.jar 
  unittests_jar.commands = $(DEL_FILE) $$unittests_jar.target org/COPASI/unittests/*.class && $$JAVA_HOME/bin/javac $$JAVAC_ARGS -d . $$JAVA_SOURCE_FILES && $$JAVA_HOME/bin/jar cvf $$unittests_jar.target ./org
  QMAKE_EXTRA_UNIX_TARGETS += unittests_jar
  PRE_TARGETDEPS += ../../../lib/libCOPASISE.a

  contains(BUILD_OS, Darwin){
     PRE_TARGETDEPS += ../libCopasiJava.jnilib
  }
  !contains(BUILD_OS, Darwin){
     PRE_TARGETDEPS += ../libCopasiJava.so
  }
}


PRE_TARGETDEPS += ../copasi.jar
PRE_TARGETDEPS += unittests.jar

QMAKE_CLEAN += unittests.jar
QMAKE_CLEAN += org/COPASI/unittests/*.class
