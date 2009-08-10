// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.h,v $
//   $Revision: 1.160 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/08/10 15:15:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 **  $ CopasiUI/listviews.h                Modified on : 8th March, 2002
 **  $ Author  : Ankur Gupta
 *****************************************************************************/
#ifndef LISTVIEWS_H
#define LISTVIEWS_H

#include <set>
#include <qsplitter.h>
#include <q3listview.h>

#include "copasi.h"
#include "UI/Tree.h"

class CTabWidget;

class Refresh;
class CCopasiObject;

class DataModelGUI;
class CQCompartment;
class CQCompartmentsWidget;
class CQDifferentialEquations;
#ifdef COPASI_DEBUG
class CQEventsWidget;
class CQEventWidget1;
#endif // COPASI_DEBUG
class FunctionWidget1;
class CQFunctionsWidget;
class CMathModel;
class CQSpeciesDetail;
class CQSpeciesWidget;
class CQEFMWidget;
//class ModelWidget;
class CQGlobalQuantitiesWidget;
class CQMoietiesTaskResult;
class CQMoietiesTaskWidget;
class ParametersWidget;
class ReactionsWidget1;
class CQReactionsWidget;
class SteadyStateWidget;
class ScanWidget;
class SensitivitiesWidget;
class CQSensResultWidget;
class StateWidget;
class CQTrajectoryWidget;
class CQReportsWidget;

#ifdef COPASI_TSS
class TSSWidget;
#endif // COPASI_TSS

class CQTSSAWidget;
class CQTSSAResultWidget;
class CQTSSAResultSubWidget;

#ifdef COPASI_DEBUG
class CQUpdatesWidget;
#endif

class CQOptimizationWidget;
class CQOptimizationResult;
class CopasiWidget;
class PlotWidget1;
class CQPlotsWidget;
class CQSplashWidget;
class TimeSeriesWidget;
class CQFittingWidget;
class CQFittingResult;
class CQMCAWidget;
class CMCAResultWidget;
class CQReportDefinition;
class CQLyapWidget;
class CQLyapResultWidget;
class CQModelValue;
class CQMathMatrixWidget;
class CQLayoutsWidget;

//*********************************************************************************

class FolderListItem : public Q3ListViewItem
{
public:
  FolderListItem(Q3ListView *parent, const IndexedNode *f, bool recurs = true);
  FolderListItem(FolderListItem *parent, const IndexedNode *f, bool recurs = true);
  void createSubFolders();
  void deleteSubFolders();

  bool setFolder(const IndexedNode * folder);
  const IndexedNode * getFolder() const;
  QString key(int, bool) const;

protected:
  const IndexedNode *mpFolder;
  QString mSortKey;
};

//********************************************************************************

class ListViews : public QSplitter
{
  Q_OBJECT

  friend class CopasiUI3Window;

public:
  ListViews(QWidget *parent = 0, const char *name = 0);
  ~ListViews();

#ifdef DELETE
#undef DELETE
#endif
  // CHANGE does not include RENAME
  enum Action {CHANGE = 0, ADD, DELETE, RENAME};
  enum ObjectType {METABOLITE = 0
                                , COMPARTMENT
                   , REACTION
                   , FUNCTION
                   , MODEL
                   , STATE
                   , REPORT
                   , PLOT
                   , MODELVALUE
                   , EVENT
                   , MIRIAM
                   , LAYOUT
                  };

  static void setDataModel(DataModelGUI* dm);
  static DataModelGUI* getDataModel() {return dataModel;};
  static bool notify(ObjectType objectType, Action action, const std::string & key = "");
  static bool commit();
  void switchToOtherWidget(C_INT32 id, const std::string & key);
  static void switchAllListViewsToWidget(C_INT32 id, const std::string & key);

  void storeCurrentItem();
  void restoreCurrentItem();
  static void storeCurrentItemInAllListViews();
  static void restoreCurrentItemInAllListViews();
  CopasiWidget* findWidgetFromId(const C_INT32 & id) const;

  // return current widget - added 02.07.08
  CopasiWidget* getCurrentWidget();

  //TODO these are convenience methods used by SliderDialog. They should be
  //replaced by something more generic when the listviews is updated for QT4
  CQTrajectoryWidget* getTrajectoryWidget();
  SteadyStateWidget* getSteadyStateWidget();
  ScanWidget* getScanWidget();
  CQMCAWidget* getMCAWidget();

private:
  CMathModel *mpMathModel;

  CopasiWidget* findWidgetFromItem(FolderListItem* item) const;

  void ConstructNodeWidgets();
  void setupFolders();

  void setTheRightPixmap(Q3ListViewItem* lvi);

  FolderListItem* findListViewItem(C_INT32 id, std::string key); //should always return a valid item

private slots:
  void slotFolderChanged(Q3ListViewItem*);

private:
  static DataModelGUI* dataModel;
  static std::vector< Refresh * > mUpdateVector;
  static std::set< const CCopasiObject * > mChangedObjects;
  static int mFramework;

  Q3ListViewItem* lastSelection;
  CopasiWidget* currentWidget;
  std::string lastKey;

  std::string mSaveObjectKey;
  C_INT32 mSaveFolderID;

  static std::set<ListViews *> mListOfListViews;
  bool attach();
  bool detach();

  bool updateCurrentWidget(ObjectType objectType, Action action, const std::string & key = "");
  static bool updateDataModelAndListviews(ObjectType objectType, Action action, const std::string & key);
  static bool updateAllListviews(C_INT32 id);

  void notifyChildWidgets(ObjectType objectType,
                          Action action,
                          const std::string & key);

  static void notifyAllChildWidgets(ObjectType objectType,
                                    Action action,
                                    const std::string & key);

  static void refreshInitialValues();
  static void buildChangedObjects();

  void setChildWidgetsFramework(int framework);

  static void setFramework(int framework);

  void updateBiologicalDescriptionContents();
  static void updateMIRIAMResourceContents();

  //the widgets
  Q3ListView *folders;

  CMCAResultWidget* mpCMCAResultWidget;
  CQMCAWidget* mpCQMCAWidget;
  CQCompartmentsWidget *mpCompartmentsWidget;
  CTabWidget *compartmentsWidget1;
  CQSplashWidget *defaultWidget;
  CQDifferentialEquations *differentialEquations;
#ifdef COPASI_DEBUG
  CQEventsWidget *eventsWidget;
  CQEventWidget1 *eventWidget1;
#endif // COPASI_DEBUG
  CQFunctionsWidget *mpFunctionsWidget;
  CTabWidget *functionWidget1;
  CQLyapWidget *lyapWidget;
  CQLyapResultWidget *lyapResultWidget;
  CQSpeciesWidget *mpSpeciesWidget;
  CTabWidget *metabolitesWidget1;
  CTabWidget *modelWidget;
  CQGlobalQuantitiesWidget *mpGlobalQuantitiesWidget;
  CTabWidget *mpModelValueWidget;
  CQEFMWidget *modesWidget;
  CQMoietiesTaskResult *mpMoietiesTaskResult;
  CQMoietiesTaskWidget *mpMoietiesTaskWidget;
  CQOptimizationWidget *optimizationWidget;
  CQOptimizationResult *optResultWidget;
  CQFittingWidget *paramFittingWidget;
  CQFittingResult *mpFittingResultWidget;
  ParametersWidget *parametersWidget;
  CQPlotsWidget *mpPlotsWidget;
  PlotWidget1 *plotWidget1;
  CQReactionsWidget *mpReactionsWidget;
  CTabWidget *reactionsWidget1;
  ScanWidget *scanWidget;
  SensitivitiesWidget *sensWidget;
  CQSensResultWidget *sensResultWidget;
  StateWidget *stateWidget;
  SteadyStateWidget *steadystateWidget;
  CQReportsWidget *mpReportsWidget;
  CQReportDefinition *tableDefinition1;

#ifdef COPASI_TSS
  TSSWidget *tssWidget;
#endif // COPASI_TSS

  TimeSeriesWidget *timeSeriesWidget;
  CQTrajectoryWidget *trajectoryWidget;
  CQTSSAWidget *tssaWidget;
  CQTSSAResultWidget *tssaResultWidget;

#ifdef COPASI_DEBUG
  CQUpdatesWidget *mpUpdatesWidget;
#endif // COPASI_DEBUG

  CQLayoutsWidget * mpLayoutsWidget;
  CQMathMatrixWidget * mpMathMatrixWidget;
};

#endif
