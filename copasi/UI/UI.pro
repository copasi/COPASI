######################################################################
# $Revision: 1.26 $ $Author: shoops $ $Date: 2004/02/19 03:33:50 $  
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
          ../lib/utilities.lib \
          ../lib/plot.lib

  LIBS += $$COPASI_LIBS
  LIBS += $(QTDIR)/lib/qwt.lib

  TARGETDEPS += $$COPASI_LIBS

  release {
    distribution.extra = bash ../../admin/mkbuild.sh $${BUILD_OS}
  }
} else {
  # The order of objects is important 
  OBJECTS +=  ../lib/libcommandline.a \
              ../lib/libelementaryFluxModes.a \
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
              ../lib/libmodel.a \
              ../lib/libplot.a 

  LIBS += -lexpat \
          -lqwt
  
  release {
    LIBS += -Wl,-lqt \
            -Wl,-lXcursor \
            -Wl,-lXft \
            -Wl,-lfontconfig \
            -Wl,-lpthread

    distribution.extra = ../../admin/mkbuild.sh $${BUILD_OS}
  }

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
                ../lib/libutilities.a \
                ../lib/libplot.a
}

contains(BUILD_OS, SunOS) {
  LIBS += -lICE -ldl
  LIBS -= -Wl,-lXft \ 
          -Wl,-lXcursor 
}  

# Input
HEADERS += \
           CReactionInterface.h \
           CReportDefinitionSelect.h \
           CompartmentSymbols.h \
           CompartmentsWidget.h \
           CompartmentsWidget1.h \
           ConstantSymbols.h \
           copasiWidget.h \
           copasiui3window.h \
           DataModel.h \
           DifferentialEquations.h \
           FixedMetaboliteSymbols.h \
           FunctionItemWidget.h \
           FunctionSymbols.h \
           FunctionWidget.h \
           FunctionWidget1.h \
           MetaboliteSymbols.h \
           MetabolitesWidget.h \
           MetabolitesWidget1.h \
           ModelWidget.h \
           ModesWidget.h \
           MoietiesWidget.h \
           MoietyWidget.h \
           MoietyWidget1.h \
           MyLineEdit.h \
           MyTable.h \
           listviews.h \
           ObjectBrowser.h \
           ObjectBrowserItem.h \
           objectdebug.h \
           OptimizationItemWidget.h \
           OptimizationWidget.h \
           parametertable.h \
           PlotWidget.h \
           qtUtilities.h \
           ReactionsWidget.h \
           ReactionsWidget1.h \
           ScanItemWidget.h \
           ScanWidget.h \
           SteadyStateWidget.h \
           StretchTable.h \
           TableDefinition.h \
           TableDefinition1.h \
           TrajectoryWidget.h \
           Tree.h

# INTERFACES += CompartmentsWidget.ui \
#               FunctionWidget1.ui \
#               MetabolitesWidget1.ui \
#               MoietyWidget1.ui \
#               ObjectBrowser.ui \
#               objectdebug.ui \
#               ReactionsWidget1.ui \
#               SteadyStateWidget.ui \
#               TrajectoryWidget.ui

SOURCES += \
           CReactionInterface.cpp \
           CReportDefinitionSelect.cpp \
           CompartmentSymbols.cpp \
           CompartmentsWidget.cpp \
           CompartmentsWidget1.cpp \
           ConstantSymbols.cpp \
           copasiWidget.cpp \
           copasiui3window.cpp \
           DataModel.cpp \
           DifferentialEquations.cpp \
           FixedMetaboliteSymbols.cpp \
           FunctionItemWidget.cpp \
           FunctionSymbols.cpp \
           FunctionWidget.cpp \
           FunctionWidget1.cpp \
           listviews.cpp \
           main.cpp \
           MetaboliteSymbols.cpp \
           MetabolitesWidget.cpp \
           MetabolitesWidget1.cpp \
           ModelWidget.cpp \
           ModesWidget.cpp \
           MoietiesWidget.cpp \
           MoietyWidget.cpp \
           MoietyWidget1.cpp \
           MyLineEdit.cpp \
           MyTable.cpp \
           ObjectBrowser.cpp \
           ObjectBrowserItem.cpp \
           objectdebug.cpp \
           OptimizationItemWidget.cpp \
           OptimizationWidget.cpp \
           parametertable.cpp \
           PlotWidget.cpp \
           qtUtilities.cpp \
           ReactionsWidget.cpp \
           ReactionsWidget1.cpp \
           ScanItemWidget.cpp \
           ScanWidget.cpp \
           SteadyStateWidget.cpp \
           StretchTable.cpp \
           TableDefinition.cpp \
           TableDefinition1.cpp \
           TrajectoryWidget.cpp

release {
  distribution.path = .
  distribution.file = CopasiUI

  INSTALLS += distribution
}
