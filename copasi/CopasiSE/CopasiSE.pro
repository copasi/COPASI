######################################################################
# $Revision: 1.6 $ $Author: shoops $ $Date: 2003/09/12 19:10:36 $  
######################################################################

include(../common.pri)

TEMPLATE = app

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
          ../lib/output.lib \
          ../lib/randomGenerator.lib \
          ../lib/report.lib \
          ../lib/scan.lib \
          ../lib/steadystate.lib \
          ../lib/trajectory.lib \
          ../lib/utilities.lib
} else {
  # The order of objects is important 
  OBJECTS += ../lib/libmodel.a \
             ../lib/libcommandline.a \
             ../lib/libelementaryFluxModes.a \
             ../lib/libmathmodel.a \
             ../lib/liboptimization.a \
             ../lib/libscan.a \
             ../lib/libsteadystate.a \
             ../lib/libtrajectory.a \
             ../lib/librandomGenerator.a \
             ../lib/libutilities.a \
             ../lib/liboutput.a \
             ../lib/libreport.a \
             ../lib/libfunction.a \
             ../lib/libcopasiXML.a \
             ../lib/libmodel.a

  LIBS += -lexpat
  
  TARGETDEPS += ../lib/libcommandline.a \
                ../lib/libcopasiXML.a \
                ../lib/libelementaryFluxModes.a \
                ../lib/libfunction.a \
                ../lib/libmathmodel.a \
                ../lib/libmodel.a \
                ../lib/liboptimization.a \
                ../lib/liboutput.a \
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
