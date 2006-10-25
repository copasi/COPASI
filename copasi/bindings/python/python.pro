TEMPLATE = lib

include(../../common.pri)

TARGET = CopasiPython

COPASI_LIBS += -lCOPASIGUI 
COPASI_LIBS += -lCOPASI 

COPASI_LIBS += -L../../lib

LIBS = $$COPASI_LIBS $$LIBS


INCLUDEPATH += ../../COPASIGUI

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
    system(touch python.i)

    wrapper_source.target = copasi_wrapper.cpp
    wrapper_source.depends = python.i
    wrapper_source.commands = $(DEL_FILE) $$wrapper_source.target ; $$SWIG_PATH/bin/swig -c++ -python -o $$wrapper_source.target $$wrapper_source.depends

    QMAKE_EXTRA_UNIX_TARGETS += wrapper_source
    PRE_TARGETDEPS += copasi_wrapper.cpp
}

PRE_TARGETDEPS += ../../lib/libCOPASI.a
PRE_TARGETDEPS += ../../lib/libCOPASIGUI.a


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

SOURCES += copasi_wrapper.cpp
