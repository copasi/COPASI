######################################################################
# $Revision: 1.80 $ $Author: gauges $ $Date: 2005/02/15 12:27:47 $  
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
          ../lib/randomGenerator.lib \
          ../lib/report.lib \
          ../lib/sbmlimport.lib \
          ../lib/scan.lib \
          ../lib/steadystate.lib \
          ../lib/trajectory.lib \
          ../lib/utilities.lib \
          ../lib/plot.lib \
          ../lib/wizard.lib \
          ../lib/mml.lib

  LIBS += $$COPASI_LIBS
  
  TARGETDEPS += $$COPASI_LIBS

  release {
    distribution.extra = bash ../../admin/mkbuild.sh $${BUILD_OS}
  }
} 
else {
  LIBS = -L../lib \
         -Wl,--start-group \
         -lcommandline \
         -lcopasiXML \
         -lelementaryFluxModes \
         -lfunction \
         -lmathmodel \
         -lmml \
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
         -lwizard \
         -Wl,--end-group \
         $${LIBS}

  release {
    distribution.extra = ../../admin/mkbuild.sh $${BUILD_OS}
  }

  TARGETDEPS += ../lib/libcommandline.a \
                ../lib/libcopasiXML.a \
                ../lib/libelementaryFluxModes.a \
                ../lib/libfunction.a \
                ../lib/libmathmodel.a \
                ../lib/libmodel.a \
                ../lib/libmml.a \
                ../lib/liboptimization.a \
                ../lib/librandomGenerator.a \
                ../lib/libreport.a \
                ../lib/libsbmlimport.a \
                ../lib/libscan.a \
                ../lib/libsteadystate.a \
                ../lib/libtrajectory.a \
                ../lib/libutilities.a \
                ../lib/libplot.a \
                ../lib/libwizard.a
}


contains(BUILD_OS, Linux) {   
  LIBS += -Wl,-lqt-mt \
          -Wl,-lXcursor \
          -Wl,-lXft \
          -Wl,-lfontconfig \
          -Wl,-lpthread

  release {
    dynamic_LFLAGS = $${QMAKE_LFLAGS}
    dynamic_LFLAGS -= -static

    dynamic_LIBS = -Wl,-Bstatic $${LIBS} -Wl,-Bdynamic 
    dynamic_LIBS -= -Wl,-lqt-mt
    dynamic_LIBS -= -Wl,-lXcursor
    dynamic_LIBS -= -Wl,-lXft
    dynamic_LIBS -= -Wl,-lfontconfig
    dynamic_LIBS -= -Wl,-lpthread
 
    dynamic.target   = CopasiUI-dynamic
    dynamic.depends  = CopasiUI
    dynamic.commands = \
      $(LINK) $${dynamic_LFLAGS} -L$(QTDIR)/lib -L/usr/X11R6/lib \
              -o $@ $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${dynamic_LIBS} \
              -Wl,--start-group -Wl,-Bstatic \
              -lqt-mt -lXrender -lXrandr -lXcursor -lXinerama -lXft \ 
              -lfreetype -lfontconfig -lSM -lICE -lXext -lX11 -lm \
              -Wl,--end-group -Wl,-Bdynamic \
              -ldl -lpthread && \
              strip $@

    QMAKE_EXTRA_UNIX_TARGETS += dynamic
  }
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS += -lICE -ldl

  LIBS -= -Wl,--start-group
  LIBS -= -Wl,--end-group
}  

contains(BUILD_OS, Darwin){
  LIBS -= -Wl,--start-group
  LIBS -= -Wl,--end-group
  LIBS -= -lplot
  LIBS += ../lib/libplot.a
  LIBS -= -lrandomGenerator
  LIBS -= -lutilities
  LIBS += -lrandomGenerator 
  LIBS += -lutilities
  
}

# Input
HEADERS += \
           AboutDialog.h \
           CCopasiPlotSelectionDialog.h \
           CCopasiSelectionDialog.h \
           CCopasiSelectionWidget.h \
           CCopasiSimpleSelectionTree.h \
           ChemEqValidator.h \
           CMCAWidget.h \
           CMCAResultSubwidget.h \
           CMCAResultWidget.h \
           CReportDefinitionSelect.h \
           CompartmentSymbols.h \
           CompartmentsWidget.h \
           CompartmentsWidget1.h \
           ConstantSymbols.h \
           CopasiDefaultWidget.h \
           CopasiSlider.h \
           CopasiTableWidget.h \
           copasiWidget.h \
           copasiui3window.h \
           CProgressBar.h \
           CTimeSeriesTable.h \
           DataModel.h \
           DataModelGUI.h \
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
           MoietyWidget.h \
           MoietyWidget1.h \
           MyLineEdit.h \
           listviews.h \
           ObjectBrowserDialog.h \
           ObjectBrowserItem.h \
           ObjectBrowserWidget.h \
           objectdebug.h \
           OptimizationItemWidget.h \
           OptimizationWidget.h \
           ParametersWidget.h \
           ParamFittingItemWidget.h \
           ParamFittingWidget.h \
           parametertable.h \
           PlotWidget.h \
           qtUtilities.h \
           ReactionsWidget.h \
           ReactionsWidget1.h \
           ScanItemWidget.h \
           ScanWidget.h \
           SliderDialog.h \
           SliderSettingsDialog.h \
           StateWidget.h \
           StateSubwidget.h \
           SteadyStateWidget.h \
           TableDefinition.h \
           TableDefinition1.h \
           TimeSeriesWidget.h \
           TimeSeriesSubwidget.h \
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
           AboutDialog.cpp \
           CCopasiPlotSelectionDialog.cpp \
           CCopasiSelectionDialog.cpp \
           CCopasiSelectionWidget.cpp \
           CCopasiSimpleSelectionTree.cpp \
           CMCAWidget.cpp \
           CMCAResultSubwidget.cpp \
           CMCAResultWidget.cpp \
           CReportDefinitionSelect.cpp \
           CompartmentSymbols.cpp \
           CompartmentsWidget.cpp \
           CompartmentsWidget1.cpp \
           ConstantSymbols.cpp \
           CopasiDefaultWidget.cpp \
           CopasiSlider.cpp \
           CopasiTableWidget.cpp \
           copasiWidget.cpp \
           copasiui3window.cpp \
           CProgressBar.cpp \
           CTimeSeriesTable.cpp \
           DataModel.cpp \
           DataModelGUI.cpp \
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
           MoietyWidget.cpp \
           MoietyWidget1.cpp \
           MyLineEdit.cpp \
           ObjectBrowserDialog.cpp \
           ObjectBrowserItem.cpp \
           ObjectBrowserWidget.cpp \
           objectdebug.cpp \
           OptimizationItemWidget.cpp \
           OptimizationWidget.cpp \
           ParametersWidget.cpp \
           ParamFittingItemWidget.cpp \
           ParamFittingWidget.cpp \
           parametertable.cpp \
           PlotWidget.cpp \
           qtUtilities.cpp \
           ReactionsWidget.cpp \
           ReactionsWidget1.cpp \
           ScanItemWidget.cpp \
           ScanWidget.cpp \
           SliderDialog.cpp \
           SliderSettingsDialog.cpp \	
           StateWidget.cpp \
           StateSubwidget.cpp \
           SteadyStateWidget.cpp \
           TableDefinition.cpp \
           TableDefinition1.cpp \
           TimeSeriesWidget.cpp \
           TimeSeriesSubwidget.cpp \
           TrajectoryWidget.cpp \
           Tree.cpp


# FORMS +=  TimeSeriesSubwidget.ui
# FORMS +=  StateSubwidget.ui
# FORMS +=  CMCAResultSubwidget.ui
# FORMS +=  SimpleSelectionWidget.ui        
# FORMS +=  SliderSettingsDialog.ui    
# FORMS +=  objectdebug.ui       

release {
  distribution.path = .
  distribution.file = CopasiUI

  INSTALLS += distribution
}
