# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/UI.pro,v $
#   $Revision: 1.242 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2011/05/24 16:32:34 $
# End CVS Header

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.242 $ $Author: shoops $ $Date: 2011/05/24 16:32:34 $
######################################################################

LIB = UI
DISTFILES = UI.pro

# Input

### Headers that belong to widgets generated from uic4 forms
HEADERS	+= \
  CMCAResultSubwidget.h \
  CQCompartment.h \
  CQCompartmentsWidget.h \
  CQDifferentialEquations.h \
  CQEFMListWidget.h \
  CQEFMResultWidget.h \
  CQEFMWidget.h \
  CQEventsWidget.h \
  CQEventWidget1.h \
  CQExperimentData.h \
  CQExperimentSelection.h \
  CQExpressionMmlStackedWidget.h \
  CQExpressionMmlWidget.h \
  CQFittingItemWidget.h \
  CQFittingResult.h \
  CQFittingResultTab1.h \
  CQFittingWidget.h \
  CQFunctionsWidget.h \
  CQGlobalQuantitiesWidget.h \
  CQLyapWidget.h \
  CQLyapResultWidget.h \
  CQMatrixDialog.h \
  CQMCAWidget.h \
  CQMergingData.h \
  CQModelValue.h \
  CQModelWidget.h \
  CQMoietiesTaskWidget.h \
  CQMoietiesTaskResult.h \
  CQNotes.h \
  objectdebug.h \
  CQOptimizationWidget.h \
  CQOptimizationResult.h \
  CQPlotsWidget.h \
  CQPreferenceDialog.h \
  CQProgressDialog.h \
  CQProgressItem.h \
  CQProgressItemBar.h \
  CQReactionsWidget.h \
  CQReportDefinition.h \
  CQReportsWidget.h \
  CQSensResultWidget.h \
  CQSpeciesDetail.h \
  CQSpeciesWidget.h \
  CQSplashWidget.h \
  CQStartValueReset.h \
  CQSteadyStateResult.h \
  CQTaskBtnWidget.h \
  CQTaskHeaderWidget.h \
  CQTaskMethodWidget.h \
  CQTextDialog.h \
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
  SensitivitiesWidget.h \
  SliderSettingsDialog.h \
  StateSubwidget.h \
  SteadyStateWidget.h \
  TimeSeriesSubwidget.h \
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
  CopasiFileDialog.h \
  CopasiSlider.h \
  CopasiTableWidget.h \
  copasiWidget.h \
  copasiui3window.h \
  CProgressBar.h \
  CReportDefinitionSelect.h \
  CQArrayAnnotationsWidget.h \
  CQBarChart.h \
  CQBaseDataModel.h \
  CQComboDelegate.h \
  CQCompartmentDM.h \
  CQDateTimeEditDelegate.h \
  CQDateTimeEditTableItem.h \
  CQEFMNetReactionDM.h  \
  CQEFMReactionDM.h \
  CQEFMSpeciesDM.h  \
  CQEventDM.h \
  CQExpressionWidget.h \
  CQFluxModeDM.h \
  CQFunctionDM.h \
  CQGlobalQuantityDM.h \
  CQIcons.h \
  CQLayoutsWidget.h \
  CQMathMatrixWidget.h \
  CQMessageBox.h \
  CQMmlScrollView.h \
  CQPlotDM.h \
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
  CQThread.h \
  CQTSSAResultWidget.h \
  CQTSSATimeScaleWidget.h \
  CQUpdatesWidget.h \
  CQValidator.h \
  CScanContainerWidget.h \
  CTabWidget.h \
  CTimeSeriesTable.h \
  DataModelGUI.h \
  DataModel.txt.h \
  FunctionItemWidget.h \
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
  TaskWidget.h \
  TimeSeriesWidget.h \
  Tree.h \
  TSSWidget.h

### Source files that belong to widgets generated from uic4 forms
SOURCES	+= \
  CMCAResultSubwidget.cpp \
  CQCompartment.cpp \
  CQCompartmentsWidget.cpp \
  CQDifferentialEquations.cpp \
  CQEFMListWidget.cpp \
  CQEFMResultWidget.cpp \
  CQEFMWidget.cpp \
  CQEventsWidget.cpp \
  CQEventWidget1.cpp \
  CQExperimentData.cpp \
  CQExperimentSelection.cpp \
  CQExpressionMmlStackedWidget.cpp \
  CQExpressionMmlWidget.cpp \
  CQFittingItemWidget.cpp \
  CQFittingResult.cpp \
  CQFittingResultTab1.cpp \
  CQFittingWidget.cpp \
  CQFunctionsWidget.cpp \
  CQGlobalQuantitiesWidget.cpp \
  CQLyapWidget.cpp \
  CQLyapResultWidget.cpp \
  CQMatrixDialog.cpp \
  CQMCAWidget.cpp \
  CQMergingData.cpp \
  CQModelValue.cpp \
  CQModelWidget.cpp \
  CQMoietiesTaskWidget.cpp \
  CQMoietiesTaskResult.cpp \
  CQNotes.cpp \
  CQOptimizationWidget.cpp \
  CQOptimizationResult.cpp \
  CQPlotsWidget.cpp \
  CQPreferenceDialog.cpp \
  CQProgressDialog.cpp \
  CQProgressItem.cpp \
  CQProgressItemBar.cpp \
  CQReactionsWidget.cpp \
  CQReportDefinition.cpp \
  CQReportsWidget.cpp \
  CQSensResultWidget.cpp \
  CQSpeciesDetail.cpp \
  CQSpeciesWidget.cpp \
  CQSplashWidget.cpp \
  CQStartValueReset.cpp \
  CQSteadyStateResult.cpp \
  CQTaskBtnWidget.cpp \
  CQTaskHeaderWidget.cpp \
  CQTaskMethodWidget.cpp \
  CQTaskThread.cpp \
  CQTextDialog.cpp \
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
  TimeSeriesSubwidget.cpp \
  CQExpandModelData.cpp \
#
### other sources (not belonging to generated widgets)
  AboutDialog.cpp \
  CColorScale.cpp \
  CCopasiPlotSelectionDialog.cpp \
  CCopasiSelectionDialog.cpp \
  CCopasiSelectionWidget.cpp \
  CMCAResultWidget.cpp \
  CopasiFileDialog.cpp \
  CopasiSlider.cpp \
  CopasiTableWidget.cpp \
  copasiWidget.cpp \
  copasiui3window.cpp \
  CProgressBar.cpp \
  CReportDefinitionSelect.cpp \
  CQArrayAnnotationsWidget.cpp \
  CQBarChart.cpp \
  CQBaseDataModel.cpp \
  CQComboDelegate.cpp \
  CQCompartmentDM.cpp \
  CQDateTimeEditDelegate.cpp \
  CQDateTimeEditTableItem.cpp \
  CQEFMNetReactionDM.cpp  \
  CQEFMReactionDM.cpp \
  CQEFMSpeciesDM.cpp  \
  CQEventDM.cpp \
  CQExpressionWidget.cpp \
  CQFluxModeDM.cpp \
  CQFunctionDM.cpp \
  CQGlobalQuantityDM.cpp \
  CQIcons.cpp \
  CQLayoutsWidget.cpp \
  CQMathMatrixWidget.cpp \
  CQMessageBox.cpp \
  CQMmlScrollView.cpp \
  CQPlotDM.cpp \
  CQReactionDM.cpp \
  CQReportDM.cpp \
  CQReportListItem.cpp \
  CQSBMLFileDialog.cpp \
  CQSimpleSelectionTree.cpp \
  CQSortFilterProxyModel.cpp \
  CQSpecieDM.cpp \
  CQSpinBoxDelegate.cpp \
  CQTableView.cpp \
  CQTSSAResultWidget.cpp \
  CQTSSATimeScaleWidget.cpp \
  CQUpdatesWidget.cpp \
  CQValidator.cpp \
  CScanContainerWidget.cpp \
  CTabWidget.cpp \
  CTimeSeriesTable.cpp \
  DataModelGUI.cpp \
  FunctionItemWidget.cpp \
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
  TaskWidget.cpp \
  TimeSeriesWidget.cpp \
  Tree.cpp \
  TSSWidget.cpp

!contains(DEFINES, COPASI_TSS) {
  HEADERS -= TSSWidget.h
  SOURCES -= TSSWidget.cpp
}

#FORMS3 += CQProgressItemText.ui
HEADERS += CQProgressItemText.h
HEADERS += CQProgressItemText.ui.h
SOURCES += CQProgressItemText.cpp


FORMS += CMCAResultSubwidget.ui
FORMS += CQCompartment.ui
FORMS += CQCompartmentsWidget.ui
FORMS += CQDifferentialEquations.ui
FORMS += CQEFMListWidget.ui
FORMS += CQEFMResultWidget.ui
FORMS += CQEFMWidget.ui
FORMS += CQEventsWidget.ui
FORMS += CQEventWidget1.ui
FORMS += CQExperimentData.ui
FORMS += CQExperimentSelection.ui
FORMS += CQExpressionMmlStackedWidget.ui
FORMS += CQExpressionMmlWidget.ui
FORMS += CQFittingItemWidget.ui
FORMS += CQFittingResult.ui
FORMS += CQFittingResultTab1.ui
FORMS += CQFittingWidget.ui
FORMS += CQFunctionsWidget.ui
FORMS += CQGlobalQuantitiesWidget.ui
FORMS += CQLyapWidget.ui
FORMS += CQLyapResultWidget.ui
FORMS += CQMatrixDialog.ui
FORMS += CQMCAWidget.ui
FORMS += CQMergingData.ui
FORMS += CQModelValue.ui
FORMS += CQModelWidget.ui
FORMS += CQMoietiesTaskWidget.ui
FORMS += CQMoietiesTaskResult.ui
FORMS += CQNotes.ui
FORMS += CQOptimizationWidget.ui
FORMS += CQOptimizationResult.ui
FORMS += CQPlotsWidget.ui
FORMS += CQPreferenceDialog.ui
FORMS += CQProgressDialog.ui
FORMS += CQProgressItem.ui
FORMS += CQProgressItemBar.ui
FORMS += CQReactionsWidget.ui
FORMS += CQReportDefinition.ui
FORMS += CQReportsWidget.ui
FORMS += CQSensResultWidget.ui
FORMS += CQSpeciesDetail.ui
FORMS += CQSpeciesWidget.ui
FORMS += CQSplashWidget.ui
FORMS += CQStartValueReset.ui
FORMS += CQSteadyStateResult.ui
FORMS += CQTaskBtnWidget.ui
FORMS += CQTaskHeaderWidget.ui
FORMS += CQTaskMethodWidget.ui
FORMS += CQTextDialog.ui
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
FORMS += TimeSeriesSubwidget.ui
FORMS += CQExpandModelData.ui

contains(COPASI_SRC_PACKAGE, true) {
  HEADERS -= CQDifferentialEquations.h
  SOURCES -= CQDifferentialEquations.cpp
  
  DISTFILES += CQDifferentialEquations.h
  DISTFILES += CQDifferentialEquations.cpp
}

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

#ifdef COPASI_LICENSE_COM
contains(USE_LICENSE, COM) {
# FORMS3 += CQRegistrationDialog.ui

  HEADERS += CQRegistrationDialog.h \
             CQRegistrationDialog.ui.h

  SOURCES += CQRegistrationDialog.cpp
}
#endif // COPASI_LICENSE_COM

#The following line was inserted by qt3to4
QT += xml  opengl qt3support webkit

include(../srcDistribution.pri)
