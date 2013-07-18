# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 





######################################################################
# $Revision: 1.265 $ $Author: shoops $ $Date: 2012/05/09 21:32:16 $
######################################################################

LIB = UI
DISTFILES = UI.pro

# Input

### Headers that belong to widgets generated from uic4 forms
HEADERS	+= \
  CMCAResultSubwidget.h \
  CLNAResultSubwidget.h \
  CQArrayAnnotationsWidget.h \
  CQBrowserPane.h \
  CQBrowserPaneDM.h \
  CQCompartment.h \
  CQCompartmentCopyOptions.h \
  CQCompartmentsWidget.h \
  CQCrossSectionTaskWidget.h \
  CQDifferentialEquations.h \
  CQEFMListWidget.h \
  CQEFMResultWidget.h \
  CWindowInterface.h \
  CQEFMWidget.h \
  CQEventsWidget.h \
  CQEventWidget1.h \
  CQExperimentData.h \
  CQExperimentSelection.h \
  CQExpressionMmlStackedWidget.h \
  CQFittingItemWidget.h \
  CQFittingResult.h \
  CQFittingResultTab1.h \
  CQFittingWidget.h \
  CQFunctionsWidget.h \
  CQGlobalQuantitiesWidget.h \
  CQLayoutsWidget.h \
  CQLyapWidget.h \
  CQLyapResultWidget.h \
  CQMatrixDialog.h \
  CQMCAWidget.h \
  CQLNAWidget.h \
  CQMathMatrixWidget.h \
  CQMergingData.h \
  CQModelValue.h \
  CQModelWidget.h \
  CQMoietiesTaskWidget.h \
  CQMoietiesTaskResult.h \
  CQNameSelectionDialog.h \
  CQNotes.h \
  CQOptimizationWidget.h \
  CQOptimizationResult.h \
  CQOscillationTaskWidget.h \
  CQParameterOverviewWidget.h \
  CQParameterSetsWidget.h \
  CQPlotsWidget.h \
  CQPreferenceDialog.h \
  CQProgressDialog.h \
  CQProgressItem.h \
  CQProgressItemBar.h \
  CQProgressItemText.h \
  CQReactionsWidget.h \
  CQReportDefinition.h \
  CQReportDefinitionSelect.h \
  CQReportsWidget.h \
  CQSensResultWidget.h \
  CQSpeciesDetail.h \
  CQSpeciesWidget.h \
  CQSplashWidget.h \
  CQStartValueReset.h \
  CQSteadyStateResult.h \
  CQTabWidget.h \
  CQTaskBtnWidget.h \
  CQTaskHeaderWidget.h \
  CQTaskMethodWidget.h \
  CQTextDialog.h \
  CQTimeSeriesWidget.h \
  CQTrajectoryWidget.h \
  CQTSSAWidget.h \
  CQTSSAResultSubWidget.h \
  CUpDownSubwidget.h \
  CScanWidgetRandom.h \
  CScanWidgetRepeat.h \
  CScanWidgetScan.h \
  CScanWidgetTask.h \
  DefaultplotDialog.h \
  FunctionWidget1.h \
  objectdebug.h \
  SensitivitiesWidget.h \
  SliderSettingsDialog.h \
  StateSubwidget.h \
  SteadyStateWidget.h \
  CQExpandModelData.h \
#
### other headers (not belonging to generated widgets)
  AboutDialog.h \
  CColorScale.h \
  CCopasiPlotSelectionDialog.h \
  CCopasiSelectionDialog.h \
  CCopasiSelectionWidget.h \
  ChemEqValidator.h \
  CMCAResultWidget.h \
  CLNAResultWidget.h \
  CopasiFileDialog.h \
  CopasiSlider.h \
  copasiWidget.h \
  copasiui3window.h \
  CProgressBar.h \
  CQBaseDataModel.h \
  CQComboDelegate.h \
  CQCompartmentDM.h \
  CQCopasiApplication.h \
  CQDateTimeEditDelegate.h \
  CQEFMNetReactionDM.h  \
  CQEFMReactionDM.h \
  CQEFMSpeciesDM.h  \
  CQEventDM.h \
  CQExpressionWidget.h \
  CQFluxModeDM.h \
  CQFunctionDM.h \
  CQGlobalQuantityDM.h \
  CQLayoutsDM.h \
  CQMessageBox.h \
  CQMmlScrollView.h \
  CQParameterOverviewDM.h \
  CQParameterSetsDM.h \
  CQPlotDM.h \
  CQPushButtonDelegate.h \
  CQReactionDM.h \
  CQReportDM.h \
  CQReportListItem.h \
  CQSBMLFileDialog.h \
  CQSimpleSelectionTree.h \
  CQSortFilterProxyModel.h \
  CQSpecieDM.h \
  CQSpinBoxDelegate.h \
  CQTableView.h \
  CQTaskThread.h \
  CQTimeSeriesDM.h \
  CQThread.h \
  CQTSSAResultWidget.h \
  CQTSSATimeScaleWidget.h \
  CQUpdatesWidget.h \
  CQValidator.h \
  CScanContainerWidget.h \
  CScanItemData.h \
  DataModelGUI.h \
  DataModel.txt.h \
  listviews.h \
  MyLineEdit.h \
  ObjectBrowserDialog.h \
  ObjectBrowserItem.h \
  ObjectBrowserWidget.h \
  ParametersWidget.h \
  parametertable.h \
  qtUtilities.h \
  ReactionsWidget1.h \
  ScanWidget.h \
  SensWidgetComboBox.h \
  SliderDialog.h \
  TaskWidget.h

### Source files that belong to widgets generated from uic4 forms
SOURCES	+= \
  CMCAResultSubwidget.cpp \
  CLNAResultSubwidget.cpp \
  CQArrayAnnotationsWidget.cpp \
  CQBrowserPane.cpp \
  CQBrowserPaneDM.cpp \
  CQCompartment.cpp \
  CQCompartmentCopyOptions.cpp \
  CQCompartmentsWidget.cpp \
  CQCrossSectionTaskWidget.cpp \
  CQDifferentialEquations.cpp \
  CQEFMListWidget.cpp \
  CQEFMResultWidget.cpp \
  CQEFMWidget.cpp \
  CQEventsWidget.cpp \
  CQEventWidget1.cpp \
  CQExperimentData.cpp \
  CQExperimentSelection.cpp \
  CQExpressionMmlStackedWidget.cpp \
  CQFittingItemWidget.cpp \
  CQFittingResult.cpp \
  CQFittingResultTab1.cpp \
  CQFittingWidget.cpp \
  CQFunctionsWidget.cpp \
  CQGlobalQuantitiesWidget.cpp \
  CQLayoutsWidget.cpp \
  CQLyapWidget.cpp \
  CQLyapResultWidget.cpp \
  CQMatrixDialog.cpp \
  CQMCAWidget.cpp \
  CQLNAWidget.cpp \
  CQMathMatrixWidget.cpp \
  CQMergingData.cpp \
  CQModelValue.cpp \
  CQModelWidget.cpp \
  CQMoietiesTaskWidget.cpp \
  CQMoietiesTaskResult.cpp \
  CQNameSelectionDialog.cpp \
  CQNotes.cpp \
  CQOptimizationWidget.cpp \
  CQOptimizationResult.cpp \
  CQOscillationTaskWidget.cpp \
  CQParameterOverviewWidget.cpp \
  CQParameterSetsWidget.cpp \
  CQPlotsWidget.cpp \
  CQPreferenceDialog.cpp \
  CQProgressDialog.cpp \
  CQProgressItem.cpp \
  CQProgressItemBar.cpp \
  CQProgressItemText.cpp \
  CQReactionsWidget.cpp \
  CQReportDefinition.cpp \
  CQReportDefinitionSelect.cpp \
  CWindowInterface.cpp \
  CQReportsWidget.cpp \
  CQSensResultWidget.cpp \
  CQSpeciesDetail.cpp \
  CQSpeciesWidget.cpp \
  CQSplashWidget.cpp \
  CQStartValueReset.cpp \
  CQSteadyStateResult.cpp \
  CQTabWidget.cpp \
  CQTaskBtnWidget.cpp \
  CQTaskHeaderWidget.cpp \
  CQTaskMethodWidget.cpp \
  CQTaskThread.cpp \
  CQTextDialog.cpp \
  CQTimeSeriesWidget.cpp \
  CQThread.cpp \
  CQTrajectoryWidget.cpp \
  CQTSSAWidget.cpp \
  CQTSSAResultSubWidget.cpp \
  CScanWidgetRandom.cpp \
  CScanWidgetRepeat.cpp \
  CScanWidgetScan.cpp \
  CScanWidgetTask.cpp \
  CUpDownSubwidget.cpp \
  DefaultplotDialog.cpp \
  FunctionWidget1.cpp \
  objectdebug.cpp \
  SensitivitiesWidget.cpp \
  SliderSettingsDialog.cpp \
  StateSubwidget.cpp \
  SteadyStateWidget.cpp \
  CQExpandModelData.cpp \
#
### other sources (not belonging to generated widgets)
  AboutDialog.cpp \
  CColorScale.cpp \
  CCopasiPlotSelectionDialog.cpp \
  CCopasiSelectionDialog.cpp \
  CCopasiSelectionWidget.cpp \
  CMCAResultWidget.cpp \
  CLNAResultWidget.cpp \
  CopasiFileDialog.cpp \
  CopasiSlider.cpp \
  copasiWidget.cpp \
  copasiui3window.cpp \
  CProgressBar.cpp \
  CQBaseDataModel.cpp \
  CQComboDelegate.cpp \
  CQCompartmentDM.cpp \
  CQCopasiApplication.cpp \
  CQDateTimeEditDelegate.cpp \
  CQEFMNetReactionDM.cpp  \
  CQEFMReactionDM.cpp \
  CQEFMSpeciesDM.cpp  \
  CQEventDM.cpp \
  CQExpressionWidget.cpp \
  CQFluxModeDM.cpp \
  CQFunctionDM.cpp \
  CQGlobalQuantityDM.cpp \
  CQLayoutsDM.cpp \
  CQMessageBox.cpp \
  CQMmlScrollView.cpp \
  CQParameterOverviewDM.cpp \
  CQParameterSetsDM.cpp \
  CQPlotDM.cpp \
  CQPushButtonDelegate.cpp \
  CQReactionDM.cpp \
  CQReportDM.cpp \
  CQReportListItem.cpp \
  CQSBMLFileDialog.cpp \
  CQSimpleSelectionTree.cpp \
  CQSortFilterProxyModel.cpp \
  CQSpecieDM.cpp \
  CQSpinBoxDelegate.cpp \
  CQTableView.cpp \
  CQTimeSeriesDM.cpp \
  CQTSSAResultWidget.cpp \
  CQTSSATimeScaleWidget.cpp \
  CQUpdatesWidget.cpp \
  CQValidator.cpp \
  CScanContainerWidget.cpp \
  CScanItemData.cpp \
  DataModelGUI.cpp \
  listviews.cpp \
  MyLineEdit.cpp \
  ObjectBrowserDialog.cpp \
  ObjectBrowserItem.cpp \
  ObjectBrowserWidget.cpp \
  ParametersWidget.cpp \
  parametertable.cpp \
  qtUtilities.cpp \
  ReactionsWidget1.cpp \
  ScanWidget.cpp \
  SensWidgetComboBox.cpp \
  SliderDialog.cpp \
  TaskWidget.cpp

FORMS += CMCAResultSubwidget.ui
FORMS += CLNAResultSubwidget.ui
FORMS += CQArrayAnnotationsWidget.ui
FORMS += CQCompartment.ui
FORMS += CQCompartmentCopyOptions.ui
FORMS += CQCompartmentsWidget.ui
FORMS += CQCrossSectionTaskWidget.ui
FORMS += CQDifferentialEquations.ui
FORMS += CQEFMListWidget.ui
FORMS += CQEFMResultWidget.ui
FORMS += CQEFMWidget.ui
FORMS += CQEventsWidget.ui
FORMS += CQEventWidget1.ui
FORMS += CQExperimentData.ui
FORMS += CQExperimentSelection.ui
FORMS += CQExpressionMmlStackedWidget.ui
FORMS += CQFittingItemWidget.ui
FORMS += CQFittingResult.ui
FORMS += CQFittingResultTab1.ui
FORMS += CQFittingWidget.ui
FORMS += CQFunctionsWidget.ui
FORMS += CQGlobalQuantitiesWidget.ui
FORMS += CQLayoutsWidget.ui
FORMS += CQLyapWidget.ui
FORMS += CQLyapResultWidget.ui
FORMS += CQMatrixDialog.ui
FORMS += CQMathMatrixWidget.ui
FORMS += CQMCAWidget.ui
FORMS += CQLNAWidget.ui
FORMS += CQMergingData.ui
FORMS += CQModelValue.ui
FORMS += CQModelWidget.ui
FORMS += CQMoietiesTaskWidget.ui
FORMS += CQMoietiesTaskResult.ui
FORMS += CQNameSelectionDialog.ui
FORMS += CQNotes.ui
FORMS += CQOptimizationWidget.ui
FORMS += CQOptimizationResult.ui
FORMS += CQOscillationTaskWidget.ui
FORMS += CQParameterOverviewWidget.ui
FORMS += CQParameterSetsWidget.ui
FORMS += CQPlotsWidget.ui
FORMS += CQPreferenceDialog.ui
FORMS += CQProgressDialog.ui
FORMS += CQProgressItem.ui
FORMS += CQProgressItemBar.ui
FORMS += CQProgressItemText.ui
FORMS += CQReactionsWidget.ui
FORMS += CQReportDefinition.ui
FORMS += CQReportDefinitionSelect.ui 
FORMS += CQReportsWidget.ui
FORMS += CQSensResultWidget.ui
FORMS += CQSpeciesDetail.ui
FORMS += CQSpeciesWidget.ui
FORMS += CQSplashWidget.ui
FORMS += CQStartValueReset.ui
FORMS += CQSteadyStateResult.ui
FORMS += CQTabWidget.ui
FORMS += CQTaskBtnWidget.ui
FORMS += CQTaskHeaderWidget.ui
FORMS += CQTaskMethodWidget.ui
FORMS += CQTextDialog.ui
FORMS += CQTimeSeriesWidget.ui
FORMS += CQTrajectoryWidget.ui
FORMS += CQTSSAWidget.ui
FORMS += CQTSSAResultSubWidget.ui
FORMS += CScanWidgetRandom.ui
FORMS += CScanWidgetRepeat.ui
FORMS += CScanWidgetScan.ui
FORMS += CScanWidgetTask.ui
FORMS += CUpDownSubwidget.ui
FORMS += DefaultplotDialog.ui
FORMS += FunctionWidget1.ui
FORMS += objectdebug.ui
FORMS += SensitivitiesWidget.ui
FORMS += SliderSettingsDialog.ui
FORMS += StateSubwidget.ui
FORMS += SteadyStateWidget.ui
FORMS += CQExpandModelData.ui

DISTFILES += icons/Copasi.ico \
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
             icons/MIRIAM.xpm \
             icons/saveIcon.xpm \
             icons/edit_Icon.xpm \
             icons/photo.xpm
             
include(../lib.pri)

CONFIG += qt 

include(../common.pri)

!contains(DEFINES, HAVE_MML) {
  HEADERS -= CQDifferentialEquations.h
  SOURCES -= CQDifferentialEquations.cpp
  
  DISTFILES += CQDifferentialEquations.h
  DISTFILES += CQDifferentialEquations.cpp
}

include(../srcDistribution.pri)
