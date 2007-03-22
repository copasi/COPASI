# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/python.pro,v $ 
#   $Revision: 1.12 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/03/22 17:02:14 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

TEMPLATE = lib

include(../../common.pri)

TARGET = CopasiPython

COPASI_LIBS += -L../../lib

COPASI_LIBS += -lCOPASISE 


LIBS = $$COPASI_LIBS $$LIBS


INCLUDEPATH += ../..

SOURCES += copasi_wrapper.cpp

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
    !exists($$SWIG_PATH/bin/swig){
        error(Unable to find swig excecutable in $$SWIG_PATH/bin/. Please use --with-swig=PATH to specify the path where PATH/bin/swig is located.) 
    }

    DEFINE_COMMANDLINE = $$join(DEFINES," -D",-D)

    wrapper_source.target = copasi_wrapper.cpp
    wrapper_source.depends = $$SWIG_INTERFACE_FILES python.i local.cpp
    wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target ; $$SWIG_PATH/bin/swig $$DEFINE_COMMANDLINE -classic -I../.. -c++ -python -o $$wrapper_source.target python.i

    QMAKE_EXTRA_UNIX_TARGETS += wrapper_source
    PRE_TARGETDEPS += copasi_wrapper.cpp
}

PRE_TARGETDEPS += ../../lib/libCOPASISE.a
#PRE_TARGETDEPS += ../../lib/libCOPASIUI.a


contains(BUILD_OS,Linux){

  !isEmpty(PYTHON_LIB_PATH){
    LIBS += -L$$PYTHON_LIB_PATH
  }

  !isEmpty(PYTHON_INCLUDE_PATH){
    INCLUDEPATH += $$PYTHON_INCLUDE_PATH
  }


 LIBS += -llapack
 LIBS += -lblas
 LIBS += -lF77
 LIBS += -lfl
 LIBS += -lpython2.3
 LIBS += -lsbml
 LIBS += -lqwt
 LIBS += -lexpat

 QMAKE_POST_LINK += ln -sf libCopasiPython.so _COPASI.so

}

contains(BUILD_OS, Darwin) {
    LIBS += -framework Python
    LIBS += -framework Quicktime
    LIBS += -framework Carbon
    LIBS += -framework Accelerate

  !isEmpty(PYTHON_INCLUDE_PATH){
    INCLUDEPATH += $$PYTHON_INCLUDE_PATH
  }

  QMAKE_POST_LINK += ln -sf libCopasiPython.dylib _COPASI.so
}



