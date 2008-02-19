# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/UI.pro,v $ 
#   $Revision: 1.164.4.1 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2008/02/19 15:25:41 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.164.4.1 $ $Author: ssahle $ $Date: 2008/02/19 15:25:41 $  
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
           CopasiFileDialog.h \
           CopasiSlider.h \
           CopasiTableWidget.h \
           copasiWidget.h \
           copasiui3window.h \
           CProgressBar.h \
           CQArrayAnnotationsWidget.h \
           CQBarChart.h \
           CQEventsWidget.h \
           CQEventWidget1.h \
           CQExpressionWidget.h \
           CQLyapResultWidget.h \
           CQMathMatrixWidget.h \
           CQReportListItem.h \
           CQSBMLFileDialog.h \
           CQSensResultWidget.h \
           CQUpdatesWidget.h \
           CQValidator.h \
           CScanContainerWidget.h \
           CTimeSeriesTable.h \
           DataModelGUI.h \
           DataModel.txt.h \
           FunctionItemWidget.h \
           FunctionWidget.h \
           FunctionWidget1.h \
           MetabolitesWidget.h \
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
           CopasiFileDialog.cpp \
           CopasiSlider.cpp \
           CopasiTableWidget.cpp \
           copasiWidget.cpp \
           copasiui3window.cpp \
           CProgressBar.cpp \
           OptimizationResultWidget.cpp \
           CQArrayAnnotationsWidget.cpp \
           CQBarChart.cpp \
           CQEventsWidget.cpp \
           CQEventWidget1.cpp \
           CQExpressionWidget.cpp \
           CQLyapResultWidget.cpp \
           CQMathMatrixWidget.cpp \
           CQPreferenceDialog.cpp \
           CQReportListItem.cpp \
           CQSBMLFileDialog.cpp \
           CQSensResultWidget.cpp \
           CQUpdatesWidget.cpp \
           CQValidator.cpp \
           CScanContainerWidget.cpp \
           CTimeSeriesTable.cpp \
           DataModelGUI.cpp \
           FunctionItemWidget.cpp \
           FunctionWidget.cpp \
           FunctionWidget1.cpp \
           listviews.cpp \
           MetabolitesWidget.cpp \
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


!contains(DEFINES, COPASI_TSS) {
  HEADERS -= TSSWidget.h
  SOURCES -= TSSWidget.cpp
}

!contains(DEFINES, WITH_QWT3D) {
  HEADERS -= CQBarChart.h
  SOURCES -= CQBarChart.cpp
}


#contains(DEFINES, WITH_LAYOUT) {
#  HEADERS += CQCopasiLayoutWidget.h
#  SOURCES += CQCopasiLayoutWidget.cpp
#}


# FORMS += CMCAResultSubwidget.ui
# FORMS += CQCompartment.ui
# FORMS += CQDifferentialEquations.ui
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
# FORMS += CQMetabolite.ui
# FORMS += CQModelValue.ui
# FORMS += CQOptimizationWidget.ui
# FORMS += CQPreferenceDialog.ui
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
           CQCompartment.h \
           CQCompartment.ui.h \
           CQDifferentialEquations.h \
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
           CQMetabolite.h \
           CQMetabolite.ui.h \
           CQModelValue.h \
           CQModelValue.ui.h \
           CQOptimizationWidget.h \
           CQOptimizationWidget.ui.h \
           CQPreferenceDialog.h \
           CQPreferenceDialog.ui.h \
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
           CQCompartment.cpp \
           CQDifferentialEquations.cpp \
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
           CQMetabolite.cpp \
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


!contains(DEFINES, HAVE_MML) {
  HEADERS -= CQDifferentialEquations.h
  SOURCES -= CQDifferentialEquations.cpp
}

contains(DEFINES, COPASI_TSSA) {
  HEADERS += CQTSSAResultWidget.h
  SOURCES += CQTSSAResultWidget.cpp
	  
# FORMS += CQTSSAWidget.ui
# FORMS += CQTSSAResultSubWidget.ui

  HEADERS += CQTSSAWidget.h \
             CQTSSAWidget.ui.h \
             CQTSSAResultSubWidget.h \
             CQTSSAResultSubWidget.ui.h
             
  SOURCES += CQTSSAWidget.cpp \
             CQTSSAResultSubWidget.cpp
             
}

#ifdef COPASI_LICENSE_COM
contains(USE_LICENSE, COM) {
# FORMS += CQRegistrationDialog.ui

HEADERS += CQRegistrationDialog.h \
           CQRegistrationDialog.ui.h

SOURCES += CQRegistrationDialog.cpp
}
#endif // COPAS_LICENSE_COM

contains(DEFINES, COPASI_MIRIAM) {
  HEADERS += CTabWidget.h \
             CAuthorsWidget.h \
             CMIRIAMModelWidget.h

  SOURCES += CTabWidget.cpp \
             CAuthorsWidget.cpp \
             CMIRIAMModelWidget.cpp
}

DISTFILES += UI.dsp \
             icons/Copasi.ico \
             icons/Copasi??-Alpha.xpm \
             icons/CopasiDoc.ico \
             icons/CopasiDoc??-Alpha.xpm \
             icons/closeSlider.xpm \
             icons/checkModel.xpm \
             icons/copasi_beta_background.xpm \
             icons/copasi_rc.xpm \
             icons/editSlider.xpm \
             icons/filenew.xpm \
             icons/fileopen.xpm \
             icons/fileprint.xpm \
             icons/filesave.xpm \
             icons/istos.xpm \
             icons/locked.xpm \
             icons/modifier.xpm \
             icons/objectAll.xpm \
             icons/objectNone.xpm \
             icons/objectParts.xpm \
             icons/product.xpm \
             icons/scanwidgetbuttonicon.xpm \
             icons/showSliders.xpm \
             icons/stois.xpm \
             icons/substrate.xpm \
             icons/unlocked.xpm \
             
             

