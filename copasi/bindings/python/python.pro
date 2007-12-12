# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/python.pro,v $ 
#   $Revision: 1.18 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2007/12/12 14:53:31 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

TEMPLATE = lib
CONFIG -= qt

include(../../common.pri)

TARGET = CopasiPython

COPASI_LIBS += -L../../lib

COPASI_LIBS += -lCOPASISE 

LIBS = $$COPASI_LIBS $$LIBS

INCLUDEPATH += ../..
contains(BUILD_OS,Linux){

  !isEmpty(PYTHON_LIB_PATH){
    LIBS += -L$$PYTHON_LIB_PATH
  }

  !isEmpty(PYTHON_INCLUDE_PATH){
    INCLUDEPATH += $$PYTHON_INCLUDE_PATH
  }


 LIBS += -llapack
 LIBS += -lblas
 LIBS += -lfl
 LIBS += -lpython2.5
 LIBS += -lsbml
 LIBS += -lexpat

 QMAKE_POST_LINK += ln -sf libCopasiPython.so _COPASI.so

}

contains(BUILD_OS, Darwin) {
    LIBS += -framework Python
    LIBS += -framework Quicktime
    LIBS += -framework Carbon
    LIBS += -framework Accelerate

    QMAKE_LFLAGS_SHLIB += -unexported_symbols_list unexported_symbols.list
    QMAKE_PRE_LINK = nm -g $$SBML_PATH/lib/libsbml.a | grep "^[0-9]" | cut -d" " -f3  > unexported_symbols.list ; nm -g $$EXPAT_PATH/lib/libexpat.a | grep "^[0-9]" | cut -d" " -f3  >> unexported_symbols.list


  !isEmpty(PYTHON_INCLUDE_PATH){
    INCLUDEPATH += $$PYTHON_INCLUDE_PATH/python2.5/
  }

  QMAKE_POST_LINK += ln -sf libCopasiPython.dylib _COPASI.so
}

contains(BUILD_OS, WIN32) { 
  CONFIG -= staticlib
  CONFIG += dll
  CONFIG += embed_manifest_dll

  QMAKE_POST_LINK = mt.exe -manifest $(TARGET).manifest -outputresource:$(TARGET);2

  !isEmpty(PYTHON_LIB_PATH){
    LIBS += -L$$PYTHON_LIB_PATH
  }

  !isEmpty(PYTHON_INCLUDE_PATH){
    INCLUDEPATH += $$PYTHON_INCLUDE_PATH
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
		     ../swig/messages.i \
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
                     ../swig/CRandom.i \
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
                     ../swig/CLyapMethod.i \
                     ../swig/CLyapProblem.i \
                     ../swig/CLyapTask.i \
                     ../swig/COptItem.i \
                     ../swig/COptMethod.i \
                     ../swig/COptProblem.i \
                     ../swig/COptTask.i \
                     ../swig/CVersion.i \
                     ../swig/CVector.i \
                     ../swig/compare_utilities.i \
                     ../swig/copasi.i \



UNITTEST_FILES = unittests/Test_CChemEq.py \
                 unittests/Test_CChemEqElement.py \
                 unittests/Test_CCompartment.py \
                 unittests/Test_CCopasiContainer.py \
                 unittests/Test_CCopasiDataModel.py \
                 unittests/Test_CCopasiMethod.py \
                 unittests/Test_CCopasiObject.py \
                 unittests/Test_CCopasiObjectName.py \
                 unittests/Test_CCopasiParameter.py \
                 unittests/Test_CCopasiParameterGroup.py \
                 unittests/Test_CCopasiProblem.py \
                 unittests/Test_CCopasiStaticString.py \
                 unittests/Test_CCopasiTask.py \
                 unittests/Test_CCopasiVector.py \
                 unittests/Test_CEvaluationTree.py \
                 unittests/Test_CFunction.py \
                 unittests/Test_CFunctionDB.py \
                 unittests/Test_CFunctionParameter.py \
                 unittests/Test_CFunctionParameters.py \
                 unittests/Test_CMatrix.py \
                 unittests/Test_CMetab.py \
                 unittests/Test_CModel.py \
                 unittests/Test_CModelValue.py \
                 unittests/Test_CMoiety.py \
                 unittests/Test_COutputAssistant.py \
                 unittests/Test_CReaction.py \
                 unittests/Test_CReport.py \
                 unittests/Test_CReportDefinition.py \
                 unittests/Test_CReportDefinitionVector.py \
                 unittests/Test_CState.py \
                 unittests/Test_CTimeSeries.py \
                 unittests/Test_CTrajectoryMethod.py \
                 unittests/Test_CTrajectoryProblem.py \
                 unittests/Test_CTrajectoryTask.py \
                 unittests/Test_CVersion.py \
                 unittests/Test_CreateSimpleModel.py \
                 unittests/Test_RunSimulations.py \
                 unittests/runTests.py 
 


#DISTFILE   = $$SWIG_INTERFACE_FILES
#DISTFILES += local.cpp
#DISTFILES += python.i
#DISTFILES += $$UNITTEST_FILES

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
      wrapper_source.depends = $$SWIG_INTERFACE_FILES python.i local.cpp
      wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target ; $$SWIG_PATH/swig.exe $$DEFINE_COMMANDLINE -classic -I..\.. -c++ -python -o $$wrapper_source.target python.i
      QMAKE_EXTRA_WIN_TARGETS += wrapper_source
      PRE_TARGETDEPS += ..\..\lib\COPASISE.lib
    }
    !contains(BUILD_OS, WIN32){
      wrapper_source.target = copasi_wrapper.cpp
      wrapper_source.depends = $$SWIG_INTERFACE_FILES python.i local.cpp
      wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target ; $$SWIG_PATH/bin/swig $$DEFINE_COMMANDLINE -classic -I../.. -c++ -python -o $$wrapper_source.target python.i
  
      QMAKE_EXTRA_UNIX_TARGETS += wrapper_source
      PRE_TARGETDEPS += ../../lib/libCOPASISE.a
    }
    PRE_TARGETDEPS += copasi_wrapper.cpp
}


SOURCES += copasi_wrapper.cpp
