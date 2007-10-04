// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.h,v $
//   $Revision: 1.129 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/04 21:19:25 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include <qlistview.h>

#include "copasi.h"
#include "UI/Tree.h"

#include "CTabWidget.h"

class DataModelGUI;
class CQCompartment;
class CompartmentsWidget;
class CQDifferentialEquations;
//class FunctionSymbols;
class FunctionWidget1;
class FunctionWidget;
class CMathModel;
class CQMetabolite;
class MetabolitesWidget;
class CQEFMWidget;
//class ModelWidget;
class ModelValuesWidget;
class MoietyWidget1;
class MoietyWidget;
class ParametersWidget;
class ReactionsWidget1;
class ReactionsWidget;
class SteadyStateWidget;
class ScanWidget;
class SensitivitiesWidget;
class CQSensResultWidget;
class StateWidget;
class CQTrajectoryWidget;
class TableDefinition;
#ifdef COPASI_TSS
class TSSWidget;
#endif // COPASI_TSS
#ifdef COPASI_DEBUG
class CQTSSAWidget;
class CQTSSAResultWidget;
class CQTSSAResultSubWidget;
#endif
class CQOptimizationWidget;
class OptimizationResultWidget;
class CopasiWidget;
class PlotWidget1;
class PlotWidget;
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
#ifdef COPASI_SSA
class SSAWidget;
#endif

#ifdef WITH_LAYOUT
class CQCopasiLayoutWidget;
#endif

//*********************************************************************************

class FolderListItem : public QListViewItem
  {
  public:
    FolderListItem(QListView *parent, const IndexedNode *f, bool recurs = true);
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

    // CHANGE does not include RENAME
    enum Action {CHANGE = 0, ADD, DELETE, RENAME};
    enum ObjectType {METABOLITE = 0, COMPARTMENT, REACTION, FUNCTION, MODEL, STATE, REPORT, PLOT, MODELVALUE};

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
    QWidget* findWidgetFromId(const C_INT32 & id) const;

  private:
    CMathModel *mpMathModel;

    QWidget* findWidgetFromItem(FolderListItem* item) const;

    void ConstructNodeWidgets();
    void setupFolders();

    void setTheRightPixmap(QListViewItem* lvi);

    FolderListItem* findListViewItem(C_INT32 id, std::string key); //should always return a valid item

  private slots:
    void slotFolderChanged(QListViewItem*);

  private:
    static DataModelGUI* dataModel;
    QListViewItem* lastSelection;
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

    void notifyChildWidgets(FolderListItem * pItem,
                            ObjectType objectType,
                            Action action,
                            const std::string & key);

    static void notifyAllChildWidgets(C_INT32 id,
                                      ObjectType objectType,
                                      Action action,
                                      const std::string & key);

    static void refreshInitialValues();

    //the widgets
    QListView *folders;

    CMCAResultWidget* mpCMCAResultWidget;
    CQMCAWidget* mpCQMCAWidget;
    CompartmentsWidget *compartmentsWidget;
    CQCompartment *compartmentsWidget1;
    CQSplashWidget *defaultWidget;
    CQDifferentialEquations *differentialEquations;
    //FunctionSymbols *functionSymbols;
    FunctionWidget *functionWidget;
    FunctionWidget1 *functionWidget1;
    CQLyapWidget *lyapWidget;
    CQLyapResultWidget *lyapResultWidget;
    MetabolitesWidget *metabolitesWidget;
    CQMetabolite *metabolitesWidget1;
    CTabWidget *modelWidget;
    ModelValuesWidget *modelValuesWidget;
    CQModelValue *mpModelValueWidget;
    CQEFMWidget *modesWidget;
    MoietyWidget *moietyWidget;
    MoietyWidget1 *moietyWidget1;
    CQOptimizationWidget *optimizationWidget;
    OptimizationResultWidget *optResultWidgetS;
    OptimizationResultWidget *optResultWidgetT;
    CQFittingWidget *paramFittingWidget;
    CQFittingResult *mpFittingResultWidget;
    ParametersWidget *parametersWidget;
    PlotWidget *plotWidget;
    PlotWidget1 *plotWidget1;
    ReactionsWidget *reactionsWidget;
    ReactionsWidget1 *reactionsWidget1;
    ScanWidget *scanWidget;
    SensitivitiesWidget *sensWidget;
    CQSensResultWidget *sensResultWidget;
    StateWidget *stateWidget;
    SteadyStateWidget *steadystateWidget;
    TableDefinition *tableDefinition;
    CQReportDefinition *tableDefinition1;
#ifdef COPASI_TSS
    TSSWidget *tssWidget;
#endif // COPASI_TSS
    TimeSeriesWidget *timeSeriesWidget;
    CQTrajectoryWidget *trajectoryWidget;
#ifdef COPASI_DEBUG
    CQTSSAWidget *tssaWidget;
    CQTSSAResultWidget *tssaResultWidget;
#endif // COPASI_DEBUG
#ifdef COPASI_SSA
    SSAWidget * mSSAWidget;
#endif // COPASI_SSA
#ifdef WITH_LAYOUT
    CQCopasiLayoutWidget * mpCopasiLayoutWidget;
#endif
    CQMathMatrixWidget * mpMathMatrixWidget;
  };

#endif
