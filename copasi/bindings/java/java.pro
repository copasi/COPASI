# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/java.pro,v $ 
#   $Revision: 1.13 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2007/06/13 16:13:30 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

TEMPLATE = lib

include(../../common.pri)

TARGET = CopasiJava

COPASI_LIBS += -L../../lib

COPASI_LIBS += -lCOPASISE 

LIBS = $$COPASI_LIBS $$LIBS

INCLUDEPATH += ../..

SWIG_INTERFACE_FILES=../swig/CChemEq.i \
                     ../swig/CChemEqElement.i \
                     ../swig/CCompartment.i \
                     ../swig/CCopasiContainer.i \
                     ../swig/CCopasiDataModel.i \
                     ../swig/CCopasiMethod.i \
                     ../swig/CCopasiObject.i \
                     ../swig/CCopasiObjectName.i \
                     ../swig/CCopasiParameter.i \
                     ../swig/CCopasiParameterGroup.i \
                     ../swig/CCopasiProblem.i \
                     ../swig/CCopasiStaticString.i \
                     ../swig/CCopasiTask.i \
                     ../swig/CCopasiVector.i \
                     ../swig/CEvaluationTree.i \
                     ../swig/CFunction.i \
                     ../swig/CFunctionDB.i \
                     ../swig/CFunctionParameter.i \
                     ../swig/CFunctionParameters.i \
                     ../swig/CMatrix.i \
                     ../swig/CMetab.i \
                     ../swig/CModel.i \
                     ../swig/CModelValue.i \
                     ../swig/CMoiety.i \
                     ../swig/COutputAssistant.i \
                     ../swig/COutputHandler.i \
                     ../swig/CReaction.i \
                     ../swig/CReport.i \
                     ../swig/CReportDefinition.i \
                     ../swig/CReportDefinitionVector.i \
                     ../swig/CState.i \
                     ../swig/CTimeSeries.i \
                     ../swig/CTrajectoryMethod.i \
                     ../swig/CTrajectoryProblem.i \
                     ../swig/CTrajectoryTask.i \
                     ../swig/CVersion.i \
                     ../swig/copasi.i 


#DISTFILE   = $$SWIG_INTERFACE_FILES
#DISTFILES += local.cpp
#DISTFILES += java.i
#DISTFILES += gui/org/COPASI/gui/TaskWidget.java
#DISTFILES += gui/org/COPASI/gui/TrajectoryTaskWidget.java
#DISTFILES += gui/org/COPASI/gui/PositiveIntegerVerifier.java
#DISTFILES += gui/org/COPASI/gui/IntegerVerifier.java
#DISTFILES += gui/org/COPASI/gui/PositiveFloatVerifier.java
#DISTFILES += gui/org/COPASI/gui/FloatVerifier.java
#DISTFILES += unittests/Test_CreateSimpleModel.java 
#DISTFILES += unittests/Test_RunSimulations.java

isEmpty(SWIG_PATH){
    # check if the wrapper file is there
    !exists(copasi_wrapper.cpp){
        error(Wrapper file copasi_wrapper.cpp missing. Please reconfigure with --with-swig=PATH_TO_SWIG.)
    }
}

!isEmpty(SWIG_PATH){
    # check if swig is there and create a target to run it to create
    # copasi_wrapper.cpp
    win32{
        !exists($$SWIG_PATH/swig.exe){
        error(Unable to find swig excecutable in $$SWIG_PATH. Please use --with-swig=PATH to specify the path where PATH/bin/swig is located.) 
    }
    else{
        !exists($$SWIG_PATH/bin/swig){
        error(Unable to find swig excecutable in $$SWIG_PATH/bin/. Please use --with-swig=PATH to specify the path where PATH/bin/swig is located.) 
    }
}

    DEFINE_COMMANDLINE = $$join(DEFINES," -D",-D)

    wrapper_source.target = copasi_wrapper.cpp
    wrapper_source.depends = $$SWIG_INTERFACE_FILES java.i local.cpp
    win32{
      wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target ; mkdir  java_files/org/COPASI ; $$SWIG_PATH/swig.exe $$DEFINE_COMMANDLINE -I../.. -c++ -java -o $$wrapper_source.target -package org.COPASI -outdir java_files/org/COPASI/  java.i; cd java_files; javac -classpath . -d . org/COPASI/*.java ;rm -f  copasi.jar;jar cf copasi.jar org ; cd .. 
    } 
    else{
      wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target ; mkdir -p java_files/org/COPASI ; $$SWIG_PATH/bin/swig $$DEFINE_COMMANDLINE -I../.. -c++ -java -o $$wrapper_source.target -package org.COPASI -outdir java_files/org/COPASI/  java.i; cd java_files; javac -classpath . -d . org/COPASI/*.java ;rm -f  copasi.jar;jar cf copasi.jar org ; cd .. 
    }
    QMAKE_EXTRA_UNIX_TARGETS += wrapper_source
    PRE_TARGETDEPS += copasi_wrapper.cpp
}

PRE_TARGETDEPS += ../../lib/libCOPASISE.a
#PRE_TARGETDEPS += ../../lib/libCOPASIUI.a

contains(BUILD_OS,Linux){

  !isEmpty(JAVA_LIB_PATH){
    LIBS += -L$$JAVA_LIB_PATH
  }

  !isEmpty(JAVA_INCLUDE_PATH){
    INCLUDEPATH += $$JAVA_INCLUDE_PATH 
  }


 LIBS += -llapack
 LIBS += -lblas
# LIBS += -lF77
 LIBS += -lfl
 LIBS += -lsbml
 LIBS += -lfl
 LIBS += -lqwt
 LIBS += -lexpat


}

contains(BUILD_OS, Darwin) {
    LIBS += -framework JavaVM
    LIBS += -framework Quicktime
    LIBS += -framework Carbon
    LIBS += -framework Accelerate

  !isEmpty(JAVA_INCLUDE_PATH){
    INCLUDEPATH += $$JAVA_INCLUDE_PATH
  }
  

}

contains(BUILD_OS, WIN32) {

  !isEmpty(JAVA_INCLUDE_PATH){
    INCLUDEPATH += $$JAVA_INCLUDE_PATH
  }
  

}



SOURCES += copasi_wrapper.cpp
