# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/UI.pro,v $
#   $Revision: 1.192 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2009/04/14 16:03:50 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.192 $ $Author: shoops $ $Date: 2009/04/14 16:03:50 $
######################################################################

LIB = UI
include(../lib.pri)

CONFIG	+= qt
include(../common.pri)

DEPENDPATH += ..
INCLUDEPATH	+= ..
INCLUDEPATH += $${QWT3D_PATH}/include


# Input
HEADERS	+= \
    AboutDialog.h \
    CColorScale.h \
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
	CTabWidget.h \
	CQArrayAnnotationsWidget.h \
	CQBarChart.h \
	CQBaseDataModel.h \
	CQDateTimeEditTableItem.h \
	CQEventsWidget.h \
	CQExpressionWidget.h \
    CQLayoutsWidget.h \
	CQLyapResultWidget.h \
	CQMathMatrixWidget.h \
	CQMatrixDialog.h \
	CQMatrixDialog.ui.h \
    CQMessageBox.h \
	CQReactionDM.h \
	CQReactionsWidget.h \
	CQReportListItem.h \
	CQSBMLFileDialog.h \
	CQSensResultWidget.h \
	CQSortFilterProxyModel.h \
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
	MyLineEdit.h \
	listviews.h \
	ObjectBrowserDialog.h \
	ObjectBrowserItem.h \
	ObjectBrowserWidget.h \
	ParametersWidget.h \
	parametertable.h \
	PlotWidget.h \
	qtUtilities.h \
	ReactionsWidget1.h \
	ScanWidget.h \
	SensitivitiesWidget.h \
	SensWidgetComboBox.h \
	SliderDialog.h \
	StateWidget.h \
	SteadyStateWidget.h \
	TableDefinition.h \
	TaskWidget.h \
	TimeSeriesWidget.h \
	Tree.h \
	TSSWidget.h \
    CQExpressionMmlWidgetStack.h \
	CQMmlScrollView.h

SOURCES	+= \
    AboutDialog.cpp \
    CColorScale.cpp \
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
	CTabWidget.cpp \
	CQArrayAnnotationsWidget.cpp \
	CQBarChart.cpp \
	CQBaseDataModel.cpp \
	CQDateTimeEditTableItem.cpp \
	CQEventsWidget.cpp \
	CQExpressionWidget.cpp \
    CQLayoutsWidget.cpp \
	CQLyapResultWidget.cpp \
	CQMathMatrixWidget.cpp \
	CQMatrixDialog.cpp \
    CQMessageBox.cpp \
	CQPreferenceDialog.cpp \
	CQReactionDM.cpp \
	CQReactionsWidget.cpp \
	CQReportListItem.cpp \
	CQSBMLFileDialog.cpp \
	CQSensResultWidget.cpp \
	CQSortFilterProxyModel.cpp \
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
	MyLineEdit.cpp \
	ObjectBrowserDialog.cpp \
	ObjectBrowserItem.cpp \
	ObjectBrowserWidget.cpp \
	ParametersWidget.cpp \
	parametertable.cpp \
	PlotWidget.cpp \
	qtUtilities.cpp \
	ReactionsWidget1.cpp \
	ScanWidget.cpp \
	SensitivitiesWidget.cpp \
	SensWidgetComboBox.cpp \
	SliderDialog.cpp \
	StateWidget.cpp \
	SteadyStateWidget.cpp \
	TableDefinition.cpp \
	TaskWidget.cpp \
	TimeSeriesWidget.cpp \
	Tree.cpp \
	TSSWidget.cpp \
  CQExpressionMmlWidgetStack.cpp \
	CQMmlScrollView.cpp

!contains(DEFINES, COPASI_TSS) {
  HEADERS -= TSSWidget.h
  SOURCES -= TSSWidget.cpp
}

# FORMS3 += CMCAResultSubwidget.ui
# FORMS3 += CQCompartment.ui
# FORMS3 += CQDifferentialEquations.ui
FORMS3 += CQEFMWidget.ui
# FORMS3 += CQEventWidget1.ui
# FORMS3 += CQExperimentData.ui
# FORMS3 += CQExperimentSelection.ui
# FORMS3 += CQExpressionMmlWidget.ui
# FORMS3 += CQFileDialogBtnGrp.ui
FORMS += CQFittingItemWidget.ui
# FORMS3 += CQFittingResult.ui
# FORMS3 += CQFittingResultTab1.ui
FORMS += CQFittingWidget.ui
FORMS += CQLyapWidget.ui
FORMS += CQMCAWidget.ui
# FORMS3 += CQMetabolite.ui
# FORMS3 += CQModelValue.ui
# FORMS3 += CQMoietiesTaskResult.ui
# FORMS3 += CQMoietiesTaskWidget.ui
FORMS3 += CQOptimizationResult.ui
FORMS3 += CQOptimizationWidget.ui
# FORMS3 += CQPreferenceDialog.ui
# FORMS3 += CQProgressDialog.ui
# FORMS3 += CQProgressItem.ui
# FORMS3 += CQProgressItemBar.ui
# FORMS3 += CQProgressItemText.ui
FORMS += CQReactionsWidget.ui
# FORMS3 += CQReportDefinition.ui
# FORMS3 += CQSplashWidget.ui
# FORMS3 += CQStartValueReset.ui
# FORMS3 += CQTaskBtnWidget.ui
# FORMS3 += CQTaskHeaderWidget.ui
# FORMS3 += CQTextDialog.ui
FORMS += CQTrajectoryWidget.ui
# FORMS3 += CScanWidgetBreak.ui
FORMS += CScanWidgetRandom.ui
FORMS += CScanWidgetRepeat.ui
FORMS += CScanWidgetScan.ui
FORMS += CScanWidgetTask.ui
# FORMS3 += CUpDownSubwidget.ui
# FORMS3 += DefaultplotDialog.ui
FORMS += SensitivitiesWidget.ui
# FORMS3 += SliderSettingsDialog.ui
FORMS += StateSubwidget.ui
FORMS += SteadyStateWidget.ui
# FORMS3 += TimeSeriesSubwidget.ui
# FORMS3 += objectdebug.ui

# headers generated from .ui files
HEADERS += \
           CMCAResultSubwidget.h \
           CMCAResultSubwidget.ui.h \
           CQCompartment.h \
           CQCompartment.ui.h \
           CQDifferentialEquations.h \
           CQEFMWidget.ui.h \
           CQEventWidget1.h \
           CQEventWidget1.ui.h \
           CQExperimentData.h \
           CQExperimentData.ui.h \
           CQExperimentSelection.h \
           CQExperimentSelection.ui.h \
           CQExpressionMmlWidget.ui.h \
           CQExpressionMmlWidget.h \
           CQFileDialogBtnGrp.h \
           CQFittingItemWidget.h \
           CQFittingResult.h \
           CQFittingResult.ui.h \
           CQFittingResultTab1.h \
           CQFittingResultTab1.ui.h \
           CQFittingWidget.h \
           CQLyapWidget.h \
           CQMCAWidget.h \
           CQMetabolite.h \
           CQMetabolite.ui.h \
           CQModelValue.h \
           CQModelValue.ui.h \
           CQMoietiesTaskResult.h \
           CQMoietiesTaskResult.ui.h \
           CQMoietiesTaskWidget.h \
           CQMoietiesTaskWidget.ui.h \
           CQOptimizationWidget.ui.h \
           CQOptimizationResult.ui.h \
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
           CScanWidgetBreak.h \
           CScanWidgetBreak.ui.h \
           CScanWidgetRandom.h \
           CScanWidgetRepeat.h \
           CScanWidgetScan.h \
           CScanWidgetTask.h  \
           CUpDownSubwidget.h \
           CUpDownSubwidget.ui.h \
           DefaultplotDialog.h \
           DefaultplotDialog.ui.h \
           SliderSettingsDialog.h \
           SliderSettingsDialog.ui.h \
           StateSubwidget.h \
           TimeSeriesSubwidget.h \
           TimeSeriesSubwidget.ui.h \
           objectdebug.h \
           objectdebug.ui.h

# sources generated from .ui files
SOURCES += \
           CMCAResultSubwidget.cpp \
           CQCompartment.cpp \
           CQDifferentialEquations.cpp \
           CQEventWidget1.cpp \
           CQExperimentData.cpp \
           CQExperimentSelection.cpp \
           CQExpressionMmlWidget.cpp \
           CQFileDialogBtnGrp.cpp \
           CQFittingItemWidget.cpp \
           CQFittingResult.cpp \
           CQFittingResultTab1.cpp \
           CQFittingWidget.cpp \
           CQLyapWidget.cpp \
           CQMCAWidget.cpp \
           CQMetabolite.cpp \
           CQModelValue.cpp \
           CQMoietiesTaskResult.cpp \
           CQMoietiesTaskWidget.cpp \
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

# FORMS3 += CQTSSAResultSubWidget.ui

FORMS += CQTSSAWidget.ui

  HEADERS += CQTSSAWidget.h \
             CQTSSAResultSubWidget.h \
             CQTSSAResultSubWidget.ui.h \
             CQTSSATimeScaleWidget.h

  SOURCES += CQTSSAWidget.cpp \
             CQTSSAResultSubWidget.cpp \
             CQTSSATimeScaleWidget.cpp
}

#ifdef COPASI_LICENSE_COM
contains(USE_LICENSE, COM) {
# FORMS3 += CQRegistrationDialog.ui

HEADERS += CQRegistrationDialog.h \
           CQRegistrationDialog.ui.h

  SOURCES += CQRegistrationDialog.cpp
}
#endif // COPAS_LICENSE_COM

DISTFILES += UI.vcproj \
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
             icons/MIRIAM.xpm \
             icons/saveIcon.xpm \
             icons/edit_Icon.xpm \
             icons/photo.xpm
             



#The following line was inserted by qt3to4
QT += xml  opengl qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3

