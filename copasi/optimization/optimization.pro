######################################################################
# $Revision: 1.26 $ $Author: gauges $ $Date: 2006/10/15 06:25:22 $  
######################################################################

LIB = optimization

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += COptItem.h \
           COptMethod.h \
           COptMethodEP.h \
           COptMethodGA.h \
           COptMethodGASR.h \
           COptMethodHookeJeeves.h \
           COptMethodLevenbergMarquardt.h \
           COptMethodNelderMead.h \
           COptMethodPS.h \
           COptMethodSA.h \
           COptMethodSRES.h \
           COptMethodSteepestDescent.h \
           COptMethodStatistics.h \
           COptProblem.h \
           COptTask.h \ 
           CRandomSearch.h \
           FminBrent.h
           
SOURCES += COptItem.cpp \
           COptMethod.cpp \
           COptMethodEP.cpp \
           COptMethodGA.cpp \
           COptMethodGASR.cpp \
           COptMethodHookeJeeves.cpp \
           COptMethodLevenbergMarquardt.cpp \
           COptMethodNelderMead.cpp \
           COptMethodPS.cpp \
           COptMethodSA.cpp \
           COptMethodSRES.cpp \
           COptMethodSteepestDescent.cpp \
           COptMethodStatistics.cpp \
           COptProblem.cpp \
           COptTask.cpp \
           CRandomSearch.cpp \
           FminBrent.cpp

contains(BUILD_OS, Linux){
    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)   
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI

    POST_TARGETDEPS += ../lib/libCOPASI.a
     
}

contains(BUILD_OS, Darwin){
    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)  
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI

    POST_TARGETDEPS += ../lib/libCOPASI.a
        
}   


DISTFILES += optimization.dsp
