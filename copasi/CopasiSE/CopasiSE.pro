######################################################################
# $Revision: 1.11 $ $Author: shoops $ $Date: 2005/02/15 23:00:23 $  
######################################################################

TEMPLATE = app

CONFIG -= qt

include(../common.pri)

DEPENDPATH += .. 
INCLUDEPATH += ..

contains(BUILD_OS, WIN32) {
  LIBS += \
    ../lib/commandline.lib \
    ../lib/copasiDM.lib \
    ../lib/copasiXML.lib \
    ../lib/elementaryFluxModes.lib \
    ../lib/function.lib \
    ../lib/mathmodel.lib \
    ../lib/model.lib \
    ../lib/optimization.lib \
    ../lib/plot.lib \
    ../lib/randomGenerator.lib \
    ../lib/report.lib \
    ../lib/sbmlimport.lib \
    ../lib/scan.lib \
    ../lib/steadystate.lib \
    ../lib/trajectory.lib \
    ../lib/utilities.lib

  TARGETDEPS += $$LIBS

} else {
  LIBS = -L../lib \
         -Wl,--start-group \
         -lcommandline \
         -lcopasiDM \
         -lcopasiXML \
         -lelementaryFluxModes \
         -lfunction \
         -lmathmodel \
         -lmodel \
         -loptimization \
         -lplot \
         -lrandomGenerator \
         -lreport \
         -lsbmlimport \
         -lscan \
         -lsteadystate \
         -ltrajectory \
         -lutilities \
         -Wl,--end-group \
         $${LIBS}

  TARGETDEPS += \
    ../lib/libcommandline.a \
    ../lib/libcopasiDM.a \
    ../lib/libcopasiXML.a \
    ../lib/libelementaryFluxModes.a \
    ../lib/libfunction.a \
    ../lib/libmathmodel.a \
    ../lib/libmodel.a \
    ../lib/liboptimization.a \
    ../lib/libplot.a \
    ../lib/librandomGenerator.a \
    ../lib/libreport.a \
    ../lib/libsbmlimport.a \
    ../lib/libscan.a \
    ../lib/libsteadystate.a \
    ../lib/libtrajectory.a \
    ../lib/libutilities.a
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS -= -Wl,--start-group
  LIBS -= -Wl,--end-group
}  

contains(BUILD_OS, Darwin){
  LIBS -= -Wl,--start-group
  LIBS -= -Wl,--end-group
  LIBS -= -lplot
  LIBS += ../lib/libplot.a
  LIBS -= -lrandomGenerator
  LIBS += -lrandomGenerator 
  LIBS -= -lreport
  LIBS += -lreport
  LIBS -= -lcopasiXML
  LIBS += -lcopasiXML
  LIBS -= -lfunction
  LIBS += -lfunction
  LIBS -= -lscan
  LIBS += -lscan
  LIBS -= -lsteadystate
  LIBS += -lsteadystate
  LIBS -= -lutilities
  LIBS += -lutilities
  
}


# Input
HEADERS += 

SOURCES += CopasiSE.cpp
