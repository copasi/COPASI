######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2005/02/08 23:32:04 $  
######################################################################

TEMPLATE = app

CONFIG -= qt

include(../common.pri)

DEPENDPATH += .. 
INCLUDEPATH += ..

contains(BUILD_OS, WIN32) {
  LIBS += ../lib/commandline.lib \
          ../lib/copasiXML.lib \
          ../lib/elementaryFluxModes.lib \
          ../lib/function.lib \
          ../lib/mathmodel.lib \
          ../lib/model.lib \
          ../lib/optimization.lib \
          ../lib/plot.lib \
          ../lib/randomGenerator.lib \
          ../lib/report.lib \
          ../lib/scan.lib \
          ../lib/steadystate.lib \
          ../lib/trajectory.lib \
          ../lib/utilities.lib
} else {
  LIBS = -L../lib \
         -Wl,--start-group \
         -lcommandline \
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

  TARGETDEPS += ../lib/libcommandline.a \
                ../lib/libcopasiXML.a \
                ../lib/libelementaryFluxModes.a \
                ../lib/libfunction.a \
                ../lib/libmathmodel.a \
                ../lib/libmodel.a \
                ../lib/liboptimization.a \
                ../lib/libplot.a \
                ../lib/librandomGenerator.a \
                ../lib/libreport.a \
                ../lib/libscan.a \
                ../lib/libsteadystate.a \
                ../lib/libtrajectory.a \
                ../lib/libutilities.a
}

# Input
HEADERS += 

SOURCES += CopasiSE.cpp
