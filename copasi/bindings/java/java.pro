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

    DEFINE_COMMANDLINE = $$join(DEFINES," -D",-D)

    wrapper_source.target = copasi_wrapper.cpp
    wrapper_source.depends = $$SWIG_INTERFACE_FILES java.i local.cpp
    wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target ; mkdir -p java_files ; $$SWIG_PATH/bin/swig $$DEFINE_COMMANDLINE -I../.. -c++ -java -o $$wrapper_source.target -outdir java_files  java.i

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
    LIBS += -framework vecLib

  !isEmpty(JAVA_INCLUDE_PATH){
    INCLUDEPATH += $$JAVA_INCLUDE_PATH
  }
  

}



SOURCES += copasi_wrapper.cpp
