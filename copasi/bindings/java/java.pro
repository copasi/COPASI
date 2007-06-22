# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/java.pro,v $ 
#   $Revision: 1.20 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2007/06/22 08:17:12 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

TEMPLATE = lib
CONFIG -= qt

include(../../common.pri)

TARGET = CopasiJava

COPASI_LIBS += -L../../lib

COPASI_LIBS += -lCOPASISE 

LIBS = $$COPASI_LIBS $$LIBS

INCLUDEPATH += ../..
contains(BUILD_OS,Linux){
  !isEmpty(JAVA_HOME){
   isEmpty(JAVA_INCLUDE_PATH){
     INCLUDEPATH += $$JAVA_HOME/include/
   }
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
# LIBS += -lqwt
 LIBS += -lexpat


}

contains(BUILD_OS, Darwin) {
    LIBS += -framework JavaVM
    LIBS += -framework Quicktime
    LIBS += -framework Carbon
    LIBS += -framework Accelerate

    QMAKE_LFLAGS_SHLIB += -unexported_symbols_list unexported_symbols.list
    
    # make a hard link from the generated dylib file to a file with the ending
    # jnilib
    QMAKE_PRE_LINK = nm -g $$SBML_PATH/lib/libsbml.a | grep "^[0-9]" | cut -d" " -f3  > unexported_symbols.list  
    QMAKE_POST_LINK = ln -f libCopasiJava.1.0.0.dylib libCopasiJava.jnilib 

  !isEmpty(JAVA_HOME){
   isEmpty(JAVA_INCLUDE_PATH){
     INCLUDEPATH += $$JAVA_HOME/include/
   }  
  }

  !isEmpty(JAVA_INCLUDE_PATH){
    INCLUDEPATH += $$JAVA_INCLUDE_PATH
  }
  

}

contains(BUILD_OS, WIN32) { 
  CONFIG -= staticlib
  CONFIG += dll
  CONFIG += embed_manifest_dll

  QMAKE_POST_LINK = mt.exe -manifest $(TARGET).manifest -outputresource:$(TARGET);2

  !isEmpty(JAVA_HOME){
   isEmpty(JAVA_INCLUDE_PATH){
     INCLUDEPATH += $$JAVA_HOME\include\
     INCLUDEPATH += $$JAVA_HOME\include\win32
   }  
  }

  !isEmpty(JAVA_INCLUDE_PATH){
    INCLUDEPATH += $$JAVA_INCLUDE_PATH
    INCLUDEPATH += $$JAVA_INCLUDE_PATH\win32
  }
  
  !isEmpty(MKL_PATH) {
    DEFINES += USE_MKL
    QMAKE_CXXFLAGS_DEBUG   += -I"$${MKL_PATH}\include"
    QMAKE_CXXFLAGS_RELEASE += -I"$${MKL_PATH}\include"
    QMAKE_LFLAGS_WINDOWS += /LIBPATH:"$${MKL_PATH}\32\lib"
    QMAKE_LFLAGS_CONSOLE += /LIBPATH:"$${MKL_PATH}\32\lib"
#    LIBS += mkl_lapack.lib mkl_p3.lib mkl_c.lib
    LIBS += mkl_lapack.lib mkl_ia32.lib guide.lib
  } else {
    !isEmpty(CLAPACK_PATH) {
      DEFINES += USE_CLAPACK
      QMAKE_CXXFLAGS_DEBUG   += -I"$${CLAPACK_PATH}\include"
      QMAKE_CXXFLAGS_RELEASE += -I"$${CLAPACK_PATH}\include"
      QMAKE_LFLAGS_WINDOWS += /LIBPATH:"$${CLAPACK_PATH}\lib"
      QMAKE_LFLAGS_CONSOLE += /LIBPATH:"$${CLAPACK_PATH}\lib"
      QMAKE_LFLAGS_CONSOLE_DLL += /LIBPATH:"$${CLAPACK_PATH}\lib"
      LIBS += libI77.lib
      LIBS += libF77.lib
#      LIBS += blas.lib
      LIBS += clapack.lib
    } else {
      error( "Either MKL_PATH or CLAPACK_PATH must be specified" )
    }
  }

  !isEmpty(EXPAT_PATH) {
    QMAKE_CXXFLAGS_DEBUG   += -I"$${EXPAT_PATH}\Source\lib"
    QMAKE_CXXFLAGS_RELEASE += -I"$${EXPAT_PATH}\Source\lib"
    QMAKE_LFLAGS_WINDOWS += /LIBPATH:"$${EXPAT_PATH}\StaticLibs"
    QMAKE_LFLAGS_CONSOLE_DLL += /LIBPATH:"$${EXPAT_PATH}\StaticLibs"
    LIBS += libexpat.lib
  } else {
    error( "EXPAT_PATH must be specified" )
  }

  !isEmpty(SBML_PATH) {
    QMAKE_CXXFLAGS_DEBUG   += -I"$${SBML_PATH}\include"
    QMAKE_CXXFLAGS_RELEASE += -I"$${SBML_PATH}\include"
    QMAKE_CXXFLAGS_DEBUG   += -I"$${SBML_PATH}\include\sbml"
    QMAKE_CXXFLAGS_RELEASE += -I"$${SBML_PATH}\include\sbml"
    QMAKE_LFLAGS_WINDOWS += /LIBPATH:"$${SBML_PATH}\lib"
    QMAKE_LFLAGS_CONSOLE_DLL += /LIBPATH:"$${SBML_PATH}\lib"
    release{
      LIBS += libsbml.lib
    }
    debug{
      LIBS += libsbmlD.lib
    }

  } else {
    error( "SBML_PATH must be specified" )
  }
}


SWIG_INTERFACE_FILES=../swig/CChemEq.i \
                     ../swig/CChemEqElement.i \
                     ../swig/CCompartment.i \
                     ../swig/CCopasiContainer.i \
                     ../swig/CCopasiDataModel.i \
                     ../swig/CCopasiException.i \
		     ../swig/CCopasiMessage.i \
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
		     ../swig/CNewtonMethod.i \
                     ../swig/COutputAssistant.i \
                     ../swig/COutputHandler.i \
                     ../swig/CReaction.i \
                     ../swig/CReport.i \
                     ../swig/CReportDefinition.i \
                     ../swig/CReportDefinitionVector.i \
       		     ../swig/CScanMethod.i \
		     ../swig/CScanProblem.i \
		     ../swig/CScanTask.i \
                     ../swig/CState.i \
       		     ../swig/CSteadyStateMethod.i \
		     ../swig/CSteadyStateProblem.i \
		     ../swig/CSteadyStateTask.i \
                     ../swig/CTimeSeries.i \
                     ../swig/CTrajectoryMethod.i \
                     ../swig/CTrajectoryProblem.i \
                     ../swig/CTrajectoryTask.i \
                     ../swig/CVersion.i \
                     ../swig/copasi.i \


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
    contains(BUILD_OS, WIN32){
        !exists($$SWIG_PATH/swig.exe){
        error(Unable to find swig excecutable in $$SWIG_PATH. Please use --with-swig=PATH to specify the path where PATH/swig.exe is located.) 
         }
    }
    !contains(BUILD_OS, WIN32){
        !exists($$SWIG_PATH/bin/swig){
        error(Unable to find swig excecutable in $$SWIG_PATH/bin/. Please use --with-swig=PATH to specify the path where PATH/bin/swig is located.) 
        }
    }

    DEFINE_COMMANDLINE = $$join(DEFINES," -D",-D)
    contains(BUILD_OS, WIN32){
      wrapper_source.target = copasi_wrapper.cpp
      wrapper_source.depends = $$SWIG_INTERFACE_FILES java.i local.cpp
      wrapper_source.commands = $(DEL_FILE) copasi_wrapper.cpp && $(DEL_FILE) java_files\org\COPASI\*.java && $(DEL_FILE) java_files\org\COPASI\*.class && $(DEL_FILE) gui\org\COPASI\gui\*.class && $$SWIG_PATH\swig.exe $$DEFINE_COMMANDLINE -I..\.. -c++ -java -o $$wrapper_source.target -package org.COPASI -outdir java_files\org\COPASI\  java.i && cd java_files && $$JAVA_HOME\bin\javac.exe -classpath . -d . org\COPASI\*.java  && cd .. && $$JAVA_HOME\bin\jar.exe cvf copasi.jar -C java_files .\org && cd gui && $$JAVA_HOME\bin\javac.exe -classpath .;..\copasi.jar -d . org\COPASI\gui\*.java && $$JAVA_HOME\bin\jar.exe cvf ..\copasi_gui.jar -C . org\COPASI\gui\*.class org\COPASI\gui\*.java
      QMAKE_EXTRA_WIN_TARGETS += wrapper_source
      PRE_TARGETDEPS += ..\..\lib\COPASISE.lib
    } 
    !contains(BUILD_OS, WIN32){

      wrapper_source.target = copasi_wrapper.cpp
      wrapper_source.depends = $$SWIG_INTERFACE_FILES java.i local.cpp
      wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target; $(DEL_FILE) java_files/org/COPASI/*; $(DEL_FILE) gui/org/COPASI/gui/*.class ; mkdir -p java_files/org/COPASI ; $$SWIG_PATH/bin/swig $$DEFINE_COMMANDLINE -I../.. -c++ -java -o $$wrapper_source.target -package org.COPASI -outdir java_files/org/COPASI/  java.i; cd java_files; $$JAVA_HOME/bin/javac -classpath . -d . org/COPASI/*.java ;rm -f  copasi.jar;$$JAVA_HOME/bin/jar cf ../copasi.jar org ; cd .. ; cd  gui; $$JAVA_HOME/bin/javac -classpath ../copasi.jar:. -d . org/COPASI/gui/*.java ; $$JAVA_HOME/bin/jar cf ../copasi_gui.jar org/COPASI/gui/*.class org/COPASI/gui/*.java 
      QMAKE_EXTRA_UNIX_TARGETS += wrapper_source
      PRE_TARGETDEPS += ../../lib/libCOPASISE.a
    }
    PRE_TARGETDEPS += copasi_wrapper.cpp
}




SOURCES += copasi_wrapper.cpp
