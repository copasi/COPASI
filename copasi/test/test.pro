######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:18:03 $  
######################################################################

include(../common.pri)

TEMPLATE = app

DEPENDPATH += .. 
INCLUDEPATH += ..

contains(BUILD_OS, WIN32) {
  COPASI_LIBS += ../lib/commandline.lib \
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

  LIBS += $$COPASI_LIBS
  TARGETDEPS += $$COPASI_LIBS
} else {
  # The order of objects is important 
  OBJECTS += ../lib/libelementaryFluxModes.a \
             ../lib/libcopasiXML.a \
             ../lib/libmathmodel.a \
             ../lib/libmodel.a \
             ../lib/libfunction.a \
             ../lib/liboutput.a \
             ../lib/libreport.a \
             ../lib/liboptimization.a \
             ../lib/libscan.a \
             ../lib/libsteadystate.a \
             ../lib/libtrajectory.a \
             ../lib/librandomGenerator.a \
             ../lib/libutilities.a \
             ../lib/liboutput.a \
             ../lib/libreport.a \
             ../lib/libfunction.a \
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

SOURCES += test.cpp \

