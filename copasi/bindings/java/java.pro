TEMPLATE = lib

include(../../common.pri)

TARGET = CopasiJava

COPASI_LIBS += -L../../lib

COPASI_LIBS += -lCOPASIUI 
COPASI_LIBS += -lCOPASISE 

LIBS = $$COPASI_LIBS $$LIBS


INCLUDEPATH += ../../


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
    system(touch java.i)

    wrapper_source.target = copasi_wrapper.cpp
    wrapper_source.depends = java.i
    wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target ; mkdir -p java_files ; $$SWIG_PATH/bin/swig -I../.. -c++ -java -o $$wrapper_source.target -outdir java_files  $$wrapper_source.depends

    QMAKE_EXTRA_UNIX_TARGETS += wrapper_source
    PRE_TARGETDEPS += copasi_wrapper.cpp
}

PRE_TARGETDEPS += ../../lib/libCOPASI.a
PRE_TARGETDEPS += ../../lib/libCOPASIGUI.a

contains(BUILD_OS,Linux){

  !isEmpty(JAVA_LIB_PATH){
    LIBS += -L$$JAVA_LIB_PATH
  }

  !isEmpty(JAVA_INCLUDE_PATH){
    INCLUDEPATH += $$JAVA_INCLUDE_PATH 
  }


 LIBS += -llapack
 LIBS += -lblas
 LIBS += -lF77
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
