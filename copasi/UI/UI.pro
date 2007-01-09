######################################################################
# $Revision: 1.139 $ $Author: shoops $ $Date: 2007/01/09 15:37:36 $  
######################################################################

LIB = UI

include(../lib.pri)
include(../common.pri)

CONFIG += qt

DEPENDPATH += .. 
INCLUDEPATH += ..

# Input
HEADERS += \
           AboutDialog.h \
           CCopasiPlotSelectionDialog.h \
           CCopasiSelectionDialog.h \
           CCopasiSelectionWidget.h \
           CCopasiSimpleSelectionTree.h \
           ChemEqValidator.h \
           CMCAWidget.h \
           CMCAResultWidget.h \
           CReportDefinitionSelect.h \
           CompartmentsWidget.h \
           CompartmentsWidget1.h \
           CopasiFileDialog.h \
           CopasiSlider.h \
           CopasiTableWidget.h \
           copasiWidget.h \
           copasiui3window.h \
           CProgressBar.h \
           CQExpressionWidget.h \
           CQLyapWidget.h \
           CQLyapResultWidget.h \
           CQReportListItem.h \
           CQSensResultWidget.h \
           CQValidator.h \
           CScanContainerWidget.h \
           CTimeSeriesTable.h \
           DataModelGUI.h \
           DataModel.txt.h \
           DifferentialEquations.h \
           FunctionItemWidget.h \
           FunctionSymbols.h \
           FunctionWidget.h \
           FunctionWidget1.h \
           MetabolitesWidget.h \
           MetabolitesWidget1.h \
           ModelWidget.h \
           ModelValuesWidget.h \
           MoietyWidget.h \
           MoietyWidget1.h \
           MyLineEdit.h \
           listviews.h \
           ObjectBrowserDialog.h \
           ObjectBrowserItem.h \
           ObjectBrowserWidget.h \
           ParametersWidget.h \
           parametertable.h \
           PlotWidget.h \
           qtUtilities.h \
           ReactionsWidget.h \
           ReactionsWidget1.h \
           ScanItemWidget.h \
           ScanWidget.h \
           SensitivitiesWidget.h \
           SliderDialog.h \
           StateWidget.h \
           SteadyStateWidget.h \
           TableDefinition.h \
           TableDefinition1.h \
           OptimizationResultWidget.h \
           TaskWidget.h \
           TimeSeriesWidget.h \
           Tree.h \
           TSSWidget.h


SOURCES += \
           AboutDialog.cpp \
           CCopasiPlotSelectionDialog.cpp \
           CCopasiSelectionDialog.cpp \
           CCopasiSelectionWidget.cpp \
           CCopasiSimpleSelectionTree.cpp \
           CMCAWidget.cpp \
           CMCAResultWidget.cpp \
           CReportDefinitionSelect.cpp \
           CompartmentsWidget.cpp \
           CompartmentsWidget1.cpp \
           CopasiFileDialog.cpp \
           CopasiSlider.cpp \
           CopasiTableWidget.cpp \
           copasiWidget.cpp \
           copasiui3window.cpp \
           CProgressBar.cpp \
           OptimizationResultWidget.cpp \
           CQExpressionWidget.cpp \
           CQLyapWidget.cpp \
           CQLyapResultWidget.cpp \
           CQReportListItem.cpp \
           CQSensResultWidget.cpp \
           CQValidator.cpp \
           CScanContainerWidget.cpp \
           CTimeSeriesTable.cpp \
           DataModelGUI.cpp \
           DifferentialEquations.cpp \
           FunctionItemWidget.cpp \
           FunctionSymbols.cpp \
           FunctionWidget.cpp \
           FunctionWidget1.cpp \
           listviews.cpp \
           MetabolitesWidget.cpp \
           MetabolitesWidget1.cpp \
           ModelValuesWidget.cpp \
           ModelWidget.cpp \
           MoietyWidget.cpp \
           MoietyWidget1.cpp \
           MyLineEdit.cpp \
           ObjectBrowserDialog.cpp \
           ObjectBrowserItem.cpp \
           ObjectBrowserWidget.cpp \
           ParametersWidget.cpp \
           parametertable.cpp \
           PlotWidget.cpp \
           qtUtilities.cpp \
           ReactionsWidget.cpp \
           ReactionsWidget1.cpp \
           ScanItemWidget.cpp \
           ScanWidget.cpp \
           SensitivitiesWidget.cpp \
           SliderDialog.cpp \
           StateWidget.cpp \
           SteadyStateWidget.cpp \
           TableDefinition.cpp \
           TableDefinition1.cpp \
           TaskWidget.cpp \
           TimeSeriesWidget.cpp \
           Tree.cpp \
           TSSWidget.cpp

!contains(DEFINES, HAVE_MML) {
  HEADERS -= DifferentialEquations.h
  SOURCES -= DifferentialEquations.cpp
}

!contains(DEFINES, COPASI_TSS) {
  HEADERS -= TSSWidget.h
  SOURCES -= TSSWidget.cpp
}

# FORMS += TimeSeriesSubwidget.ui
# FORMS += StateSubwidget.ui
# FORMS += CMCAResultSubwidget.ui
# FORMS += SliderSettingsDialog.ui 
# FORMS += objectdebug.ui
# FORMS += CUpDownSubwidget.ui
# FORMS += CScanWidgetBreak.ui
# FORMS += CScanWidgetRandom.ui
# FORMS += CScanWidgetRepeat.ui
# FORMS += CScanWidgetScan.ui
# FORMS += CScanWidgetTask.ui
# FORMS += DefaultplotDialog.ui
# FORMS += CQProgressItem.ui
# FORMS += CQProgressItemBar.ui
# FORMS += CQProgressItemText.ui
# FORMS += CQProgressDialog.ui
# FORMS += CQReportDefinition.ui
# FORMS += CQTextDialog.ui
# FORMS += CQExperimentData.ui
# FORMS += CQExperimentSelection.ui
# FORMS += CQFileDialogBtnGrp.ui
# FORMS += CQFittingResultTab1.ui
# FORMS += CQFittingResult.ui
# FORMS += CQFittingItemWidget.ui
# FORMS += CQFittingWidget.ui
# FORMS += CQOptimizationWidget.ui
# FORMS += CQSplashWidget.ui
# FORMS += CQTaskHeaderWidget.ui
# FORMS += CQTaskBtnWidget.ui
# FORMS += CQTrajectoryWidget.ui
# FORMS += CQModelValue.ui
# FORMS += CQStartValueReset.ui
# FORMS += CQEFMWidget.ui

# headers generated from .ui files   
HEADERS += \
           CMCAResultSubwidget.h \
           CMCAResultSubwidget.ui.h \
           CQEFMWidget.h \
           CQEFMWidget.ui.h \
           CQExperimentData.h \
           CQExperimentData.ui.h \
           CQExperimentSelection.h \
           CQExperimentSelection.ui.h \
           CQFileDialogBtnGrp.h \
           CQFittingItemWidget.h \
           CQFittingItemWidget.ui.h \
           CQFittingResult.h \
           CQFittingResult.ui.h \
           CQFittingResultTab1.h \
           CQFittingResultTab1.ui.h \
           CQFittingWidget.h \
           CQFittingWidget.ui.h \
           CQOptimizationWidget.h \
           CQOptimizationWidget.ui.h \
           CQProgressDialog.h \
           CQProgressDialog.ui.h \
           CQProgressItem.h \
           CQProgressItem.ui.h \
           CQProgressItemBar.h \
           CQProgressItemBar.ui.h \
           CQProgressItemText.h \
           CQProgressItemText.ui.h \
           CQReportDefinition.h \
           CQReportDefinition.ui.h \
           CQSplashWidget.h \
           CQSplashWidget.ui.h \
           CQStartValueReset.h \
           CQStartValueReset.ui.h \
           CQTaskBtnWidget.h \
           CQTaskHeaderWidget.h \
           CQTaskHeaderWidget.ui.h \
           CQTextDialog.h \
           CQTextDialog.ui.h \
           CQTrajectoryWidget.h \
           CQTrajectoryWidget.ui.h \
           CQModelValue.h \
           CQModelValue.ui.h \
           CScanWidgetBreak.h \
           CScanWidgetBreak.ui.h \
           CScanWidgetRandom.h \
           CScanWidgetRandom.ui.h \
           CScanWidgetRepeat.h \
           CScanWidgetRepeat.ui.h \
           CScanWidgetScan.h \
           CScanWidgetScan.ui.h \
           CScanWidgetTask.h  \ 
           CScanWidgetTask.ui.h  \ 
           CUpDownSubwidget.h \
           CUpDownSubwidget.ui.h \
           DefaultplotDialog.h \
           DefaultplotDialog.ui.h \
           SliderSettingsDialog.h \
           SliderSettingsDialog.ui.h \
           StateSubwidget.h \
           StateSubwidget.ui.h \
           TimeSeriesSubwidget.h \
           TimeSeriesSubwidget.ui.h \
           objectdebug.h \
           objectdebug.ui.h

# sources generated from .ui files   
SOURCES += \
           CMCAResultSubwidget.cpp \
           CQEFMWidget.cpp \
           CQExperimentData.cpp \
           CQExperimentSelection.cpp \
           CQFileDialogBtnGrp.cpp \
           CQFittingItemWidget.cpp \
           CQFittingResult.cpp \
           CQFittingResultTab1.cpp \
           CQFittingWidget.cpp \
           CQModelValue.cpp \
           CQOptimizationWidget.cpp \
           CQProgressItem.cpp \
           CQProgressItemBar.cpp \
           CQProgressItemText.cpp \
           CQProgressDialog.cpp \
           CQReportDefinition.cpp \
           CQSplashWidget.cpp \
           CQStartValueReset.cpp \
           CQTaskBtnWidget.cpp \
           CQTaskHeaderWidget.cpp \
           CQTrajectoryWidget.cpp \
           CQTextDialog.cpp \
           CUpDownSubwidget.cpp \
           CScanWidgetBreak.cpp \
           CScanWidgetRandom.cpp \
           CScanWidgetRepeat.cpp \
           CScanWidgetScan.cpp \
           CScanWidgetTask.cpp \  
           DefaultplotDialog.cpp \
           objectdebug.cpp \
           SliderSettingsDialog.cpp \
           StateSubwidget.cpp \
           TimeSeriesSubwidget.cpp 

contains(USE_LICENSE, COM) {
# FORMS += CQRegistrationDialog.ui

HEADERS += CQRegistrationDialog.h \
           CQRegistrationDialog.ui.h

SOURCES += CQRegistrationDialog.cpp
}

release {
  HEADERS -= \
           SensitivitiesWidget.h \
           TSSWidget.h

  SOURCES -= \
           SensitivitiesWidget.cpp \
           TSSWidget.cpp
}

DISTFILES += UI.dsp \
             icons/Copasi.ico \
             icons/Copasi??-Alpha.xpm \
             icons/CopasiDoc.ico \
             icons/CopasiDoc??-Alpha.xpm \
             icons/closeSlider.xpm \
             icons/copasi_beta_background.xpm \
             icons/copasi_rc.xpm \
             icons/editSlider.xpm \
             icons/filenew.xpm \
             icons/fileopen.xpm \
             icons/fileprint.xpm \
             icons/filesave.xpm \
             icons/locked.xpm \
             icons/modifier.xpm \
             icons/objectAll.xpm \
             icons/objectNone.xpm \
             icons/objectParts.xpm \
             icons/product.xpm \
             icons/scanwidgetbuttonicon.xpm \
             icons/showSliders.xpm \
             icons/substrate.xpm \
             icons/unlocked.xpm \

