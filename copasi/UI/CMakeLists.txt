###############################################################################
###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., University of Heidelberg, and The University
# of Manchester.
# All rights reserved.
# 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.
# 
# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.
#
###############################################################################

# cmake_minimum_required (VERSION 2.8)
# project (UI)
# 
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB FORMS_UI   UI/*.ui )
file(GLOB HEADERS_UI UI/*.h  )
file(GLOB SOURCES_UI UI/*.cpp)

 

list(REMOVE_ITEM FORMS_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQMessageBox.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQFileDialogBtnGrp.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQMetabolite.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQPrintAsDialog.ui
#  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQProgressItemBar.ui
  #${CMAKE_CURRENT_SOURCE_DIR}/UI/CQProgressItemText.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQRegistrationDialog.ui
#  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQTextDialog.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/FunctionItemWidget.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/CQCrossSectionTaskWidget.ui
)


list(REMOVE_ITEM HEADERS_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CPlotSelectionDialog.h
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQSBMLSaveOptionsDialog.h
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQCompartment.ui.h        
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQProgressItemBar.ui.h    
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQReportDefinition.ui.h   
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CScanWidgetRepeat.ui.h    
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/SliderSettingsDialog.ui.h
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQPrintAsDialog.ui.h      
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQProgressItemText.ui.h   
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQTextDialog.ui.h         
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CScanWidgetScan.ui.h
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQProgressItem.ui.h       
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQRegistrationDialog.ui.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CScanWidgetRandom.ui.h    
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CScanWidgetTask.ui.h  
)

list(REMOVE_ITEM SOURCES_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/MetabolitesWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/FunctionWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/ModelValuesWidget.cpp  
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/TableDefinition.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/TSSWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQExpressionMmlWidgetStack.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CPlotSelectionDialog.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQSBMLSaveOptionsDialog.cpp
)

if (NOT ENABLE_COPASI_NONLIN_DYN)

list(REMOVE_ITEM FORMS_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQCrossSectionTaskWidget.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQOscillationTaskWidget.ui
)

list(REMOVE_ITEM HEADERS_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQCrossSectionTaskWidget.h
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQOscillationTaskWidget.h
)

list(REMOVE_ITEM SOURCES_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQCrossSectionTaskWidget.cpp  
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQOscillationTaskWidget.cpp  
)

endif(NOT ENABLE_COPASI_NONLIN_DYN)

include_directories(${MML_INCLUDE_DIR})

set(SOURCES_RCC)
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/CQIconResource.h)
set (HEADERS_UI ${HEADERS_UI} ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/CQIconResource.h)
set (SOURCES_UI ${SOURCES_UI} ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/CQIconResource.cpp)
QT4_ADD_RESOURCES(COPASI_RCC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/copasi.qrc)
endif()


# create source group for IDEs
source_group(UI FILES ${FORMS_UI} ${HEADERS_UI} ${SOURCES_UI})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_UI})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_UI})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_UI})




# SET(COPASI_UI_HAVE_LNA_HEADER NO)
# if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/CLNAResultSubwidget.h")
# SET(COPASI_UI_HAVE_LNA_HEADER YES)
# endif()
# 
# 
# SET(COPASI_UI_HAVE_REPORTDEF_HEADER NO)
# if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/CReportDefinitionSelect.h")
# SET(COPASI_UI_HAVE_REPORTDEF_HEADER YES)
# endif()
# 
# 
# SET(COPASI_UI_HAVE_CQREPORTDEF_HEADER NO)
# if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/CQReportDefinitionSelect.h")
# SET(COPASI_UI_HAVE_CQREPORTDEF_HEADER YES)
# endif()
# 
# 
# # message(STATUS 
# # "
# # -- Project UI:
# # --   PROJECT_SOURCE_DIR       = ${PROJECT_SOURCE_DIR}
# # --   CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}
# # --
# # --  Have LNA:                = ${COPASI_UI_HAVE_LNA_HEADER}
# # --  "
# # 
# # )
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )
# 
# set(HEADERS CMCAResultSubwidget.h ${HEADERS})
# if (COPASI_UI_HAVE_LNA_HEADER)
# set(HEADERS CLNAResultSubwidget.h ${HEADERS})
# set(HEADERS CQLNAWidget.h ${HEADERS})
# endif()
# set(HEADERS CQArrayAnnotationsWidget.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQBrowserPane.h)
# set(HEADERS CQBrowserPane.h ${HEADERS})
# set(HEADERS CQBrowserPaneDM.h ${HEADERS})
# endif()
# set(HEADERS CQCompartment.h ${HEADERS})
# set(HEADERS CQCompartmentsWidget.h ${HEADERS})
# if (NOT BUILD_33)
# set(HEADERS CQCrossSectionTaskWidget.h ${HEADERS})
# set(SOURCES CQCrossSectionTaskWidget.cpp ${SOURCES})
# set(FORMS CQCrossSectionTaskWidget.ui ${FORMS})
# else()
# set(HEADERS 
# 
# objectdebug.h 
# CQExpressionMmlWidget.h
# TimeSeriesSubwidget.h
# CopasiTableWidget.h 
# CQArrayAnnotationsWidget.h 
# CQBarChart.h 
#  CQDateTimeEditTableItem.h
#   CQIcons.h
#   CQLayoutsWidget.h
#   CQMathMatrixWidget.h
#   CTimeSeriesTable.h
#   FunctionItemWidget.h 
#   TimeSeriesWidget.h 
#   Tree.h 
#   #TSSWidget.h
# 
# ${HEADERS})
# set(SOURCES 
# 
# objectdebug.cpp 
# CQExpressionMmlWidget.cpp 
# TimeSeriesSubwidget.cpp
#  CopasiTableWidget.cpp
#   CQArrayAnnotationsWidget.cpp 
#   CQBarChart.cpp 
#   CQDateTimeEditTableItem.cpp 
#   CQIcons.cpp 
#   CQLayoutsWidget.cpp 
#   CQMathMatrixWidget.cpp
#   CTimeSeriesTable.cpp
#   FunctionItemWidget.cpp
#   TaskWidget.cpp
#   TimeSeriesWidget.cpp
#   Tree.cpp
#   #TSSWidget.cpp
# 
# ${SOURCES})
# 
# set(FORMS 
# 
# objectdebug.ui 
#  CQExpressionMmlWidget.ui
#  TimeSeriesSubwidget.ui
# 
# ${FORMS})
# 
# endif()
# set(HEADERS CQEFMListWidget.h ${HEADERS})
# set(HEADERS CQEFMResultWidget.h ${HEADERS})
# set(HEADERS CQEFMWidget.h ${HEADERS})
# set(HEADERS CQEventsWidget.h ${HEADERS})
# set(HEADERS CQEventWidget1.h ${HEADERS})
# set(HEADERS CQExperimentData.h ${HEADERS})
# set(HEADERS CQExperimentSelection.h ${HEADERS})
# set(HEADERS CQExpressionMmlStackedWidget.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQExpressionMmlWidget.h)
# set(HEADERS CQExpressionMmlWidget.h ${HEADERS})
# endif()
# set(HEADERS CQFittingItemWidget.h ${HEADERS})
# set(HEADERS CQFittingResult.h ${HEADERS})
# set(HEADERS CQFittingResultTab1.h ${HEADERS})
# set(HEADERS CQFittingWidget.h ${HEADERS})
# set(HEADERS CQFunctionsWidget.h ${HEADERS})
# set(HEADERS CQGlobalQuantitiesWidget.h ${HEADERS})
# set(HEADERS CQLayoutsWidget.h ${HEADERS})
# set(HEADERS CQLyapWidget.h ${HEADERS})
# set(HEADERS CQLyapResultWidget.h ${HEADERS})
# set(HEADERS CQMatrixDialog.h ${HEADERS})
# set(HEADERS CQMCAWidget.h ${HEADERS})
# set(HEADERS CQMathMatrixWidget.h ${HEADERS})
# set(HEADERS CQMergingData.h ${HEADERS})
# set(HEADERS CQModelValue.h ${HEADERS})
# set(HEADERS CQModelWidget.h ${HEADERS})
# set(HEADERS CQMoietiesTaskWidget.h ${HEADERS})
# set(HEADERS CQMoietiesTaskResult.h ${HEADERS})
# set(HEADERS CQNotes.h ${HEADERS})
# set(HEADERS CQOptimizationWidget.h ${HEADERS})
# set(HEADERS CQOptimizationResult.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQOscillationTaskWidget.h)
# set(HEADERS CQOscillationTaskWidget.h ${HEADERS})
# endif()
# set(HEADERS CQPlotsWidget.h ${HEADERS})
# set(HEADERS CQPreferenceDialog.h ${HEADERS})
# set(HEADERS CQProgressDialog.h ${HEADERS})
# set(HEADERS CQProgressItem.h ${HEADERS})
# set(HEADERS CQProgressItemBar.h ${HEADERS})
# set(HEADERS CQProgressItemText.h ${HEADERS})
# set(HEADERS CQReactionsWidget.h ${HEADERS})
# set(HEADERS CQReportDefinition.h ${HEADERS})
# set(HEADERS CQReportsWidget.h ${HEADERS})
# set(HEADERS CQSensResultWidget.h ${HEADERS})
# set(HEADERS CQSpeciesDetail.h ${HEADERS})
# set(HEADERS CQSpeciesWidget.h ${HEADERS})
# set(HEADERS CQSplashWidget.h ${HEADERS})
# set(HEADERS CQStartValueReset.h ${HEADERS})
# set(HEADERS CQSteadyStateResult.h ${HEADERS})
# set(HEADERS CQTaskBtnWidget.h ${HEADERS})
# set(HEADERS CQTaskHeaderWidget.h ${HEADERS})
# set(HEADERS CQTaskMethodWidget.h ${HEADERS})
# set(HEADERS CQTextDialog.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQTimeSeriesWidget.h)
# set(HEADERS CQTimeSeriesWidget.h ${HEADERS})
# endif()
# set(HEADERS CQTrajectoryWidget.h ${HEADERS})
# set(HEADERS CQTSSAWidget.h ${HEADERS})
# set(HEADERS CQTSSAResultSubWidget.h ${HEADERS})
# set(HEADERS CUpDownSubwidget.h ${HEADERS})
# set(HEADERS CScanWidgetRandom.h ${HEADERS})
# set(HEADERS CScanWidgetRepeat.h ${HEADERS})
# set(HEADERS CScanWidgetScan.h ${HEADERS})
# set(HEADERS CScanWidgetTask.h ${HEADERS})
# set(HEADERS DefaultplotDialog.h ${HEADERS})
# set(HEADERS FunctionWidget1.h ${HEADERS})
# set(HEADERS SensitivitiesWidget.h ${HEADERS})
# set(HEADERS SliderSettingsDialog.h ${HEADERS})
# set(HEADERS StateSubwidget.h ${HEADERS})
# set(HEADERS SteadyStateWidget.h ${HEADERS})
# set(HEADERS CQExpandModelData.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQCopasiApplication.h)
# set(HEADERS CQCopasiApplication.h ${HEADERS})
# endif()
# set(HEADERS AboutDialog.h ${HEADERS})
# set(HEADERS CColorScale.h ${HEADERS})
# set(HEADERS CCopasiPlotSelectionDialog.h ${HEADERS})
# set(HEADERS CCopasiSelectionDialog.h ${HEADERS})
# set(HEADERS CCopasiSelectionWidget.h ${HEADERS})
# set(HEADERS ChemEqValidator.h ${HEADERS})
# set(HEADERS CMCAResultWidget.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CLNAResultWidget.h)
# set(HEADERS CLNAResultWidget.h ${HEADERS})
# endif()
# set(HEADERS CopasiFileDialog.h ${HEADERS})
# set(HEADERS CopasiSlider.h ${HEADERS})
# set(HEADERS copasiWidget.h ${HEADERS})
# set(HEADERS copasiui3window.h ${HEADERS})
# set(HEADERS CProgressBar.h ${HEADERS})
# if (COPASI_UI_HAVE_REPORTDEF_HEADER)
# set(HEADERS CReportDefinitionSelect.h ${HEADERS})
# endif(COPASI_UI_HAVE_REPORTDEF_HEADER)
# set(HEADERS CQBaseDataModel.h ${HEADERS})
# set(HEADERS CQComboDelegate.h ${HEADERS})
# set(HEADERS CQCompartmentDM.h ${HEADERS})
# set(HEADERS CQDateTimeEditDelegate.h ${HEADERS})
# set(HEADERS CQEFMNetReactionDM.h  ${HEADERS})
# set(HEADERS CQEFMReactionDM.h ${HEADERS})
# set(HEADERS CQEFMSpeciesDM.h  ${HEADERS})
# set(HEADERS CQEventDM.h ${HEADERS})
# set(HEADERS CQExpressionWidget.h ${HEADERS})
# set(HEADERS CQFluxModeDM.h ${HEADERS})
# set(HEADERS CQFunctionDM.h ${HEADERS})
# set(HEADERS CQGlobalQuantityDM.h ${HEADERS})
# 
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQIcons.h)
# set(HEADERS CQIcons.h ${HEADERS})
# endif()
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQLayoutsDM.h)
# set(HEADERS CQLayoutsDM.h ${HEADERS})
# endif()
# set(HEADERS CQMessageBox.h ${HEADERS})
# set(HEADERS CQMmlScrollView.h ${HEADERS})
# set(HEADERS CQPlotDM.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQPushButtonDelegate.h)
# set(HEADERS CQPushButtonDelegate.h ${HEADERS})
# endif()
# set(HEADERS CQReactionDM.h ${HEADERS})
# set(HEADERS CQReportDM.h ${HEADERS})
# set(HEADERS CQReportListItem.h ${HEADERS})
# set(HEADERS CQSBMLFileDialog.h ${HEADERS})
# set(HEADERS CQSimpleSelectionTree.h ${HEADERS})
# set(HEADERS CQSortFilterProxyModel.h ${HEADERS})
# set(HEADERS CQSpecieDM.h ${HEADERS})
# set(HEADERS CQSpinBoxDelegate.h ${HEADERS})
# set(HEADERS CQTableView.h ${HEADERS})
# set(HEADERS CQTaskThread.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQTimeSeriesDM.h)
# set(HEADERS CQTimeSeriesDM.h ${HEADERS})
# endif()
# set(HEADERS CQThread.h ${HEADERS})
# set(HEADERS CQTSSAResultWidget.h ${HEADERS})
# set(HEADERS CQTSSATimeScaleWidget.h ${HEADERS})
# set(HEADERS CQUpdatesWidget.h ${HEADERS})
# set(HEADERS CQValidator.h ${HEADERS})
# set(HEADERS CScanContainerWidget.h ${HEADERS})
# set(HEADERS CTabWidget.h ${HEADERS})
# set(HEADERS DataModelGUI.h ${HEADERS})
# set(HEADERS DataModel.txt.h ${HEADERS})
# set(HEADERS listviews.h ${HEADERS})
# set(HEADERS MyLineEdit.h ${HEADERS})
# set(HEADERS ObjectBrowserDialog.h ${HEADERS})
# set(HEADERS ObjectBrowserItem.h ${HEADERS})
# set(HEADERS ObjectBrowserWidget.h ${HEADERS})
# set(HEADERS ParametersWidget.h ${HEADERS})
# set(HEADERS parametertable.h ${HEADERS})
# set(HEADERS qtUtilities.h ${HEADERS})
# set(HEADERS ReactionsWidget1.h ${HEADERS})
# set(HEADERS ScanWidget.h ${HEADERS})
# set(HEADERS SensWidgetComboBox.h ${HEADERS})
# set(HEADERS SliderDialog.h ${HEADERS})
# set(HEADERS TaskWidget.h ${HEADERS})
# set(HEADERS CQLayoutsWidget.h ${HEADERS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CScanItemData.h)
# set(HEADERS CScanItemData.h ${HEADERS})
# set(SOURCES CScanItemData.cpp ${SOURCES})
# endif()
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQCopasiApplication.cpp)
# set(SOURCES CQCopasiApplication.cpp ${SOURCES})
# endif()
# set(SOURCES CMCAResultSubwidget.cpp ${SOURCES})
# if (COPASI_UI_HAVE_LNA_HEADER)
# set(SOURCES CLNAResultSubwidget.cpp ${SOURCES})
# set(SOURCES CQLNAWidget.cpp ${SOURCES})
# endif()
# set(SOURCES CQArrayAnnotationsWidget.cpp ${SOURCES})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQBrowserPaneDM.cpp)
# set(SOURCES CQBrowserPane.cpp ${SOURCES})
# set(SOURCES CQBrowserPaneDM.cpp ${SOURCES})
# endif()
# set(SOURCES CQCompartment.cpp ${SOURCES})
# set(SOURCES CQCompartmentsWidget.cpp ${SOURCES})
# set(SOURCES CQEFMListWidget.cpp ${SOURCES})
# set(SOURCES CQEFMResultWidget.cpp ${SOURCES})
# set(SOURCES CQEFMWidget.cpp ${SOURCES})
# set(SOURCES CQEventsWidget.cpp ${SOURCES})
# set(SOURCES CQEventWidget1.cpp ${SOURCES})
# set(SOURCES CQExperimentData.cpp ${SOURCES})
# set(SOURCES CQExperimentSelection.cpp ${SOURCES})
# set(SOURCES CQExpressionMmlStackedWidget.cpp ${SOURCES})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQExpressionMmlWidget.cpp)
# set(SOURCES CQExpressionMmlWidget.cpp ${SOURCES})
# endif()
# set(SOURCES CQFittingItemWidget.cpp ${SOURCES})
# set(SOURCES CQFittingResult.cpp ${SOURCES})
# set(SOURCES CQFittingResultTab1.cpp ${SOURCES})
# set(SOURCES CQFittingWidget.cpp ${SOURCES})
# set(SOURCES CQFunctionsWidget.cpp ${SOURCES})
# set(SOURCES CQGlobalQuantitiesWidget.cpp ${SOURCES})
# set(SOURCES CQLayoutsWidget.cpp ${SOURCES})
# set(SOURCES CQLyapWidget.cpp ${SOURCES})
# set(SOURCES CQLyapResultWidget.cpp ${SOURCES})
# set(SOURCES CQMatrixDialog.cpp ${SOURCES})
# set(SOURCES CQMCAWidget.cpp ${SOURCES})
# set(SOURCES CQMathMatrixWidget.cpp ${SOURCES})
# set(SOURCES CQMergingData.cpp ${SOURCES})
# set(SOURCES CQModelValue.cpp ${SOURCES})
# set(SOURCES CQModelWidget.cpp ${SOURCES})
# set(SOURCES CQMoietiesTaskWidget.cpp ${SOURCES})
# set(SOURCES CQMoietiesTaskResult.cpp ${SOURCES})
# set(SOURCES CQNotes.cpp ${SOURCES})
# set(SOURCES CQOptimizationWidget.cpp ${SOURCES})
# set(SOURCES CQOptimizationResult.cpp ${SOURCES})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQOscillationTaskWidget.cpp)
# set(SOURCES CQOscillationTaskWidget.cpp ${SOURCES})
# endif()
# set(SOURCES CQPlotsWidget.cpp ${SOURCES})
# set(SOURCES CQPreferenceDialog.cpp ${SOURCES})
# set(SOURCES CQProgressDialog.cpp ${SOURCES})
# set(SOURCES CQProgressItem.cpp ${SOURCES})
# set(SOURCES CQProgressItemBar.cpp ${SOURCES})
# set(SOURCES CQProgressItemText.cpp ${SOURCES})
# set(SOURCES CQReactionsWidget.cpp ${SOURCES})
# set(SOURCES CQReportDefinition.cpp ${SOURCES})
# set(SOURCES CQReportsWidget.cpp ${SOURCES})
# set(SOURCES CQSensResultWidget.cpp ${SOURCES})
# set(SOURCES CQSpeciesDetail.cpp ${SOURCES})
# set(SOURCES CQSpeciesWidget.cpp ${SOURCES})
# set(SOURCES CQSplashWidget.cpp ${SOURCES})
# set(SOURCES CQStartValueReset.cpp ${SOURCES})
# set(SOURCES CQSteadyStateResult.cpp ${SOURCES})
# set(SOURCES CQTaskBtnWidget.cpp ${SOURCES})
# set(SOURCES CQTaskHeaderWidget.cpp ${SOURCES})
# set(SOURCES CQTaskMethodWidget.cpp ${SOURCES})
# set(SOURCES CQTaskThread.cpp ${SOURCES})
# set(SOURCES CQTextDialog.cpp ${SOURCES})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQTimeSeriesWidget.cpp)
# set(SOURCES CQTimeSeriesWidget.cpp ${SOURCES})
# endif()
# set(SOURCES CQThread.cpp ${SOURCES})
# set(SOURCES CQTrajectoryWidget.cpp ${SOURCES})
# set(SOURCES CQTSSAWidget.cpp ${SOURCES})
# set(SOURCES CQTSSAResultSubWidget.cpp ${SOURCES})
# set(SOURCES CScanWidgetRandom.cpp ${SOURCES})
# set(SOURCES CScanWidgetRepeat.cpp ${SOURCES})
# set(SOURCES CScanWidgetScan.cpp ${SOURCES})
# set(SOURCES CScanWidgetTask.cpp ${SOURCES})
# set(SOURCES CUpDownSubwidget.cpp ${SOURCES})
# set(SOURCES DefaultplotDialog.cpp ${SOURCES})
# set(SOURCES FunctionWidget1.cpp ${SOURCES})
# set(SOURCES SensitivitiesWidget.cpp ${SOURCES})
# set(SOURCES SliderSettingsDialog.cpp ${SOURCES})
# set(SOURCES StateSubwidget.cpp ${SOURCES})
# set(SOURCES SteadyStateWidget.cpp ${SOURCES})
# set(SOURCES CQExpandModelData.cpp ${SOURCES})
# 
# set(SOURCES AboutDialog.cpp ${SOURCES})
# set(SOURCES CColorScale.cpp ${SOURCES})
# set(SOURCES CCopasiPlotSelectionDialog.cpp ${SOURCES})
# set(SOURCES CCopasiSelectionDialog.cpp ${SOURCES})
# set(SOURCES CCopasiSelectionWidget.cpp ${SOURCES})
# set(SOURCES CMCAResultWidget.cpp ${SOURCES})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CLNAResultWidget.cpp)
# set(SOURCES CLNAResultWidget.cpp ${SOURCES})
# endif()
# set(SOURCES CopasiFileDialog.cpp ${SOURCES})
# set(SOURCES CopasiSlider.cpp ${SOURCES})
# set(SOURCES copasiWidget.cpp ${SOURCES})
# set(SOURCES copasiui3window.cpp ${SOURCES})
# set(SOURCES CProgressBar.cpp ${SOURCES})
# if (COPASI_UI_HAVE_REPORTDEF_HEADER)
# set(SOURCES CReportDefinitionSelect.cpp ${SOURCES})
# endif(COPASI_UI_HAVE_REPORTDEF_HEADER)
# set(SOURCES CQBaseDataModel.cpp ${SOURCES})
# set(SOURCES CQComboDelegate.cpp ${SOURCES})
# set(SOURCES CQCompartmentDM.cpp ${SOURCES})
# set(SOURCES CQDateTimeEditDelegate.cpp ${SOURCES})
# set(SOURCES CQEFMNetReactionDM.cpp  ${SOURCES})
# set(SOURCES CQEFMReactionDM.cpp ${SOURCES})
# set(SOURCES CQEFMSpeciesDM.cpp  ${SOURCES})	
# set(SOURCES CQEventDM.cpp ${SOURCES})
# set(SOURCES CQExpressionWidget.cpp ${SOURCES})
# set(SOURCES CQFluxModeDM.cpp ${SOURCES})
# set(SOURCES CQFunctionDM.cpp ${SOURCES})
# set(SOURCES CQGlobalQuantityDM.cpp ${SOURCES})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQIcons.cpp)
# set(SOURCES CQIcons.cpp ${SOURCES})
# endif()
# set(SOURCES CQMessageBox.cpp ${SOURCES})
# set(SOURCES CQMmlScrollView.cpp ${SOURCES})
# set(SOURCES CQPlotDM.cpp ${SOURCES})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQPushButtonDelegate.cpp)
# set(SOURCES CQPushButtonDelegate.cpp ${SOURCES})
# set(SOURCES CQLayoutsDM.cpp ${SOURCES})
# endif()
# set(SOURCES CQReactionDM.cpp ${SOURCES})
# set(SOURCES CQReportDM.cpp ${SOURCES})
# set(SOURCES CQReportListItem.cpp ${SOURCES})
# set(SOURCES CQSBMLFileDialog.cpp ${SOURCES})
# set(SOURCES CQSimpleSelectionTree.cpp ${SOURCES})
# set(SOURCES CQSortFilterProxyModel.cpp ${SOURCES})
# set(SOURCES CQSpecieDM.cpp ${SOURCES})
# set(SOURCES CQSpinBoxDelegate.cpp ${SOURCES})
# set(SOURCES CQTableView.cpp ${SOURCES})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQTimeSeriesDM.cpp)
# set(SOURCES CQTimeSeriesDM.cpp ${SOURCES})
# endif()
# set(SOURCES CQTSSAResultWidget.cpp ${SOURCES})
# set(SOURCES CQTSSATimeScaleWidget.cpp ${SOURCES})
# set(SOURCES CQUpdatesWidget.cpp ${SOURCES})
# set(SOURCES CQValidator.cpp ${SOURCES})
# set(SOURCES CScanContainerWidget.cpp ${SOURCES})
# set(SOURCES CTabWidget.cpp ${SOURCES})
# set(SOURCES DataModelGUI.cpp ${SOURCES})
# set(SOURCES listviews.cpp ${SOURCES})
# set(SOURCES MyLineEdit.cpp ${SOURCES})
# set(SOURCES ObjectBrowserDialog.cpp ${SOURCES})
# set(SOURCES ObjectBrowserItem.cpp ${SOURCES})
# set(SOURCES ObjectBrowserWidget.cpp ${SOURCES})
# set(SOURCES ParametersWidget.cpp ${SOURCES})
# set(SOURCES parametertable.cpp ${SOURCES})
# set(SOURCES qtUtilities.cpp ${SOURCES})
# set(SOURCES ReactionsWidget1.cpp ${SOURCES})
# set(SOURCES ScanWidget.cpp ${SOURCES})
# set(SOURCES SensWidgetComboBox.cpp ${SOURCES})
# set(SOURCES SliderDialog.cpp ${SOURCES})
# set(SOURCES TaskWidget.cpp ${SOURCES})
# 
# set(FORMS CMCAResultSubwidget.ui ${FORMS})
# if (COPASI_UI_HAVE_LNA_HEADER)
# set(FORMS CLNAResultSubwidget.ui ${FORMS})
# set(FORMS CQLNAWidget.ui ${FORMS})
# set(FORMS CQArrayAnnotationsWidget.ui ${FORMS})
# endif()
# set(FORMS CQCompartment.ui ${FORMS})
# set(FORMS CQCompartmentsWidget.ui ${FORMS})
# set(FORMS CQEFMListWidget.ui ${FORMS})
# set(FORMS CQEFMResultWidget.ui ${FORMS})
# set(FORMS CQEFMWidget.ui ${FORMS})
# set(FORMS CQEventsWidget.ui ${FORMS})
# set(FORMS CQEventWidget1.ui ${FORMS})
# set(FORMS CQExperimentData.ui ${FORMS})
# set(FORMS CQExperimentSelection.ui ${FORMS})
# set(FORMS CQExpressionMmlStackedWidget.ui ${FORMS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQExpressionMmlWidget.ui)
# set(FORMS CQExpressionMmlWidget.ui ${FORMS})
# endif()
# set(FORMS CQFittingItemWidget.ui ${FORMS})
# set(FORMS CQFittingResult.ui ${FORMS})
# set(FORMS CQFittingResultTab1.ui ${FORMS})
# set(FORMS CQFittingWidget.ui ${FORMS})
# set(FORMS CQFunctionsWidget.ui ${FORMS})
# set(FORMS CQGlobalQuantitiesWidget.ui ${FORMS})
# set(FORMS CQLyapWidget.ui ${FORMS})
# set(FORMS CQLyapResultWidget.ui ${FORMS})
# set(FORMS CQMatrixDialog.ui ${FORMS})
# set(FORMS CQMCAWidget.ui ${FORMS})
# set(FORMS CQMergingData.ui ${FORMS})
# set(FORMS CQModelValue.ui ${FORMS})
# set(FORMS CQModelWidget.ui ${FORMS})
# set(FORMS CQMoietiesTaskWidget.ui ${FORMS})
# set(FORMS CQMoietiesTaskResult.ui ${FORMS})
# set(FORMS CQNotes.ui ${FORMS})
# set(FORMS CQOptimizationWidget.ui ${FORMS})
# set(FORMS CQOptimizationResult.ui ${FORMS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQOscillationTaskWidget.ui)
# set(FORMS CQLayoutsWidget.ui ${FORMS})
# set(FORMS CQMathMatrixWidget.ui ${FORMS})
# set(FORMS CQProgressItemText.ui ${FORMS})
# set(FORMS CQProgressItemBar.ui ${FORMS})
# 
# set(FORMS CQOscillationTaskWidget.ui ${FORMS})
# endif()
# set(FORMS CQPlotsWidget.ui ${FORMS})
# set(FORMS CQPreferenceDialog.ui ${FORMS})
# set(FORMS CQProgressDialog.ui ${FORMS})
# set(FORMS CQProgressItem.ui ${FORMS})
# set(FORMS CQReactionsWidget.ui ${FORMS})
# set(FORMS CQReportDefinition.ui ${FORMS})
# set(FORMS CQReportsWidget.ui ${FORMS})
# set(FORMS CQSensResultWidget.ui ${FORMS})
# set(FORMS CQSpeciesDetail.ui ${FORMS})
# set(FORMS CQSpeciesWidget.ui ${FORMS})
# set(FORMS CQSplashWidget.ui ${FORMS})
# set(FORMS CQStartValueReset.ui ${FORMS})
# set(FORMS CQSteadyStateResult.ui ${FORMS})
# set(FORMS CQTaskBtnWidget.ui ${FORMS})
# set(FORMS CQTaskHeaderWidget.ui ${FORMS})
# set(FORMS CQTaskMethodWidget.ui ${FORMS})
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQTimeSeriesWidget.ui)
# set(FORMS CQTimeSeriesWidget.ui ${FORMS})
# endif()
# set(FORMS CQTrajectoryWidget.ui ${FORMS})
# set(FORMS CQTSSAWidget.ui ${FORMS})
# set(FORMS CQTSSAResultSubWidget.ui ${FORMS})
# set(FORMS CScanWidgetRandom.ui ${FORMS})
# set(FORMS CScanWidgetRepeat.ui ${FORMS})
# set(FORMS CScanWidgetScan.ui ${FORMS})
# set(FORMS CScanWidgetTask.ui ${FORMS})
# set(FORMS CUpDownSubwidget.ui ${FORMS})
# set(FORMS DefaultplotDialog.ui ${FORMS})
# set(FORMS FunctionWidget1.ui ${FORMS})
# set(FORMS SensitivitiesWidget.ui ${FORMS})
# set(FORMS SliderSettingsDialog.ui ${FORMS})
# set(FORMS StateSubwidget.ui ${FORMS})
# set(FORMS SteadyStateWidget.ui ${FORMS})
# set(FORMS CQExpandModelData.ui ${FORMS})
# 
# if (NOT BUILD_33)
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQTextDialog.ui)
# set(FORMS CQTextDialog.ui ${FORMS})
# endif()
# endif()
# 
# 
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQParameterOverviewDM.h)
# set (HEADERS ${HEADERS} CQParameterOverviewDM.h CQParameterOverviewWidget.h)
# set (SOURCES ${SOURCES} CQParameterOverviewDM.cpp CQParameterOverviewWidget.cpp)
# set(FORMS ${FORMS} CQParameterOverviewWidget.ui)
# 
# endif()
# 
# 
# if (COPASI_UI_HAVE_CQREPORTDEF_HEADER)
# set (HEADERS ${HEADERS} CQReportDefinitionSelect.h )
# set (SOURCES ${SOURCES} CQReportDefinitionSelect.cpp )
# set(FORMS ${FORMS} CQReportDefinitionSelect.ui)
# endif(COPASI_UI_HAVE_CQREPORTDEF_HEADER)



# if(ENABLE_MML)
# set(FORMS CQDifferentialEquations.ui ${FORMS})
# set(HEADERS CQDifferentialEquations.h ${HEADERS})
# set(SOURCES CQDifferentialEquations.cpp ${SOURCES})
# include_directories(${MML_INCLUDE_DIR})
# endif(ENABLE_MML)
# 

# if (BUILD_33)
# 
# list(REMOVE_ITEM FORMS CQProgressItemBar.ui CQProgressItemText.ui)
# 
# endif()
# 

# include(../CMakeUILib.cmake)
# 
# set(COPASI_UI_MOC_OPTIONS)
# if (ENABLE_SBW_INTEGRATION)
# set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_SBW_INTEGRATION=1)
# endif(ENABLE_SBW_INTEGRATION)
# 
# if (ENABLE_WITH_MERGEMODEL)
# set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DWITH_MERGEMODEL=1)
# endif(ENABLE_WITH_MERGEMODEL)
# 
# if (ENABLE_CRENDER_EXTENSION)
# set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DUSE_CRENDER_EXTENSION=1)
# endif(ENABLE_CRENDER_EXTENSION)
# 
# if (ENABLE_CELLDESIGNER_IMPORT)
# set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCELLDESIGNER_IMPORT=1)
# endif(ENABLE_CELLDESIGNER_IMPORT)
# 
# if (ENABLE_COPASI_NONLIN_DYN)
# set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_NONLIN_DYN=1)
# endif(ENABLE_COPASI_NONLIN_DYN)
# 
# if (ENABLE_COPASI_PARAMETER_SETS)
# set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_PARAMETER_SETS=1)
# endif(ENABLE_COPASI_PARAMETER_SETS)
# 
# 
# 
# if (COPASI_UI_MOC_OPTIONS)
# message(STATUS "Mocing with options: ${COPASI_UI_MOC_OPTIONS}")
# qt4_wrap_cpp(HEADERS_MOC ${HEADERS} OPTIONS ${COPASI_UI_MOC_OPTIONS})
# else()
# qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
# endif(COPASI_UI_MOC_OPTIONS)
# 
# 
# 
# if(FORMS)
# qt4_wrap_ui(HEADERS_FORMS ${FORMS})
# endif(FORMS)
# if (ENABLE_SBW_INTEGRATION)
#   include_directories(${SBW_INCLUDE_DIR})
#   add_definitions(-DCOPASI_SBW_INTEGRATION)
# endif(ENABLE_SBW_INTEGRATION)
  
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/../plotUI)
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/../MIRIAMUI)
# INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
# INCLUDE_DIRECTORIES(${QT_QTWEBKIT_INCLUDE_DIR})
# INCLUDE_DIRECTORIES(${QT_QTXML_INCLUDE_DIR})
# 
# if (NOT MML_LIBRARY)
#   if (EXISTS ${CMAKE_SOURCE_DIR}/copasi/mml/qtmmlwidget.cpp)
#     set(SOURCES ${CMAKE_SOURCE_DIR}/copasi/mml/qtmmlwidget.cpp ${SOURCES})
#   endif(EXISTS ${CMAKE_SOURCE_DIR}/copasi/mml/qtmmlwidget.cpp)
# endif(NOT MML_LIBRARY)
# 
# add_library(UI STATIC ${SOURCES} ${HEADERS} ${HEADERS_FORMS} ${HEADERS_MOC} ${SOURCES_RCC})
# add_dependencies(UI barChart plotUI MIRIAMUI wizard)
# target_link_libraries(UI barChart plotUI MIRIAMUI wizard tex layoutUI)
# 
# target_link_libraries(UI crosssection)
# if (ENABLE_MML AND MML_LIBRARY)
# target_link_libraries(UI ${MML_LIBRARY})
# endif()
