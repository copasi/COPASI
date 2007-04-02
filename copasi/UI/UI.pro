# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/UI.pro,v $ 
#   $Revision: 1.147 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/04/02 17:01:05 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.147 $ $Author: shoops $ $Date: 2007/04/02 17:01:05 $  
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
           CQArrayAnnotationsWidget.h \
           CQExpressionWidget.h \
           CQLyapResultWidget.h \
           CQMathMatrixWidget.h \
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
           CQArrayAnnotationsWidget.cpp \
           CQExpressionWidget.cpp \
           CQLyapResultWidget.cpp \
           CQMathMatrixWidget.cpp \
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

contains(DEFINES, WITH_LAYOUT) {
  HEADERS += CQCopasiLayoutWidget.h
  SOURCES += CQCopasiLayoutWidget.cpp
}


# FORMS += CMCAResultSubwidget.ui
# FORMS += CQEFMWidget.ui
# FORMS += CQExperimentData.ui
# FORMS += CQExperimentSelection.ui
# FORMS += CQFileDialogBtnGrp.ui
# FORMS += CQFittingItemWidget.ui
# FORMS += CQFittingResult.ui
# FORMS += CQFittingResultTab1.ui
# FORMS += CQFittingWidget.ui
# FORMS += CQLyapWidget.ui
# FORMS += CQMCAWidget.ui
# FORMS += CQMessageBox.ui
# FORMS += CQModelValue.ui
# FORMS += CQOptimizationWidget.ui
# FORMS += CQProgressDialog.ui
# FORMS += CQProgressItem.ui
# FORMS += CQProgressItemBar.ui
# FORMS += CQProgressItemText.ui
# FORMS += CQReportDefinition.ui
# FORMS += CQSplashWidget.ui
# FORMS += CQStartValueReset.ui
# FORMS += CQTaskBtnWidget.ui
# FORMS += CQTaskHeaderWidget.ui
# FORMS += CQTextDialog.ui
# FORMS += CQTrajectoryWidget.ui
# FORMS += CScanWidgetBreak.ui
# FORMS += CScanWidgetRandom.ui
# FORMS += CScanWidgetRepeat.ui
# FORMS += CScanWidgetScan.ui
# FORMS += CScanWidgetTask.ui
# FORMS += CUpDownSubwidget.ui
# FORMS += DefaultplotDialog.ui
# FORMS += SliderSettingsDialog.ui 
# FORMS += StateSubwidget.ui
# FORMS += TimeSeriesSubwidget.ui
# FORMS += objectdebug.ui

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
           CQLyapWidget.h \
           CQLyapWidget.ui.h \
           CQMCAWidget.h \
           CQMCAWidget.ui.h \
           CQMessageBox.h \
           CQMessageBox.ui.h \
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
           CQLyapWidget.cpp \
           CQMCAWidget.cpp \
           CQMessageBox.cpp \
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

#ifdef COPASI_LICENSE_COM
contains(USE_LICENSE, COM) {
# FORMS += CQRegistrationDialog.ui

HEADERS += CQRegistrationDialog.h \
           CQRegistrationDialog.ui.h

SOURCES += CQRegistrationDialog.cpp
}
#endif // COPAS_LICENSE_COM

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

