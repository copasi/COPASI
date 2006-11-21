TEMPLATE = lib

include(../../common.pri)

TARGET = CopasiPython

COPASI_LIBS += -L../../lib

#COPASI_LIBS += -lCOPASIUI 
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
                     ../swig/CReaction.i \
                     ../swig/CReportDefinition.i \
                     ../swig/CReportDefinitionVector.i \
                     ../swig/CState.i \
                     ../swig/CTimeSeries.i \
                     ../swig/CTrajectoryMethod.i \
                     ../swig/CTrajectoryProblem.i \
                     ../swig/CTrajectoryTask.i \
                     ../swig/CVersion.i \
                     ../swig/copasi.i 


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
    #system(touch python.i)

    DEFINE_COMMANDLINE = $$join(DEFINES," -D",-D)

    wrapper_source.target = copasi_wrapper.cpp
    wrapper_source.depends = $$SWIG_INTERFACE_FILES 
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

contains(BUILD_OS,Darwin){
    LIBS += -framework Python
    LIBS += -framework Quicktime
    LIBS += -framework Carbon
    LIBS += -framework vecLib

  !isEmpty(PYTHON_INCLUDE_PATH){
    INCLUDEPATH += $$PYTHON_INCLUDE_PATH
  }

  QMAKE_POST_LINK += ln -sf libCopasiPython.dylib _COPASI.so
}



