/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.h,v $
   $Revision: 1.70 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2003/10/29 15:23:29 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/listviews.h                Modified on : 8th March, 2002
 **  $ Author  : Ankur Gupta
 *****************************************************************************/
#ifndef LISTVIEWS_H
#define LISTVIEWS_H

#include <set>
#include <qsplitter.h>
#include <qstring.h> 
//#include <qobject.h>
#include <qptrlist.h>
#include <qlistview.h>
#include <vector>
#include <qvaluelist.h>
#include <qobjectlist.h>
#include <qheader.h>
#include <qmessagebox.h>
#include <qmultilineedit.h>
#include <qimage.h> 
//#include "copasiWidget.h"
#include "copasi.h"
#include "DataModel.h"
#include "Tree.h" 
//#include "copasiWidget.h"

//public QLineEdit:
// #include "model/model.h"

class CSteadyStateTask;
class CTrajectoryTask;
class CompartmentSymbols;
class CompartmentsWidget1;
class CompartmentsWidget;
class ConstantSymbols;
class DifferentialEquations;
class FixedMetaboliteSymbols;
class FunctionSymbols;
class FunctionWidget1;
class FunctionWidget;
class CMathModel;
class MetaboliteSymbols;
class MetabolitesWidget1;
class MetabolitesWidget;
class ModesWidget;
class ModelWidget;
class MoietyWidget1;
class MoietyWidget;
class ReactionsWidget1;
class ReactionsWidget;
class SteadyStateWidget;
class ScanWidget;
class TrajectoryWidget;
class TableDefinition;
class TableDefinition1;
class OptimizationWidget;
class CopasiWidget;
class Folder;
class PlotWidget1;
class PlotWidget;

//*********************************************************************************

class FolderListItem : public QListViewItem
  {
  public:
    FolderListItem(QListView *parent, Folder *f);
    FolderListItem(FolderListItem *parent, Folder *f);
    void insertSubFolders(const QObjectList *lst);
    Folder *folder();
    QString key(int, bool) const;

  protected:
    Folder *myFolder;
  };

//********************************************************************************

class ListViews : public QSplitter
  {
    Q_OBJECT
  public slots:
    void slotHideWidget();
    void slotShowWidget();

  public:
    ListViews(QWidget *parent = 0, const char *name = 0);
    ~ListViews();

    // CHANGE does not include RENAME
    enum Action {CHANGE = 0, ADD, DELETE, RENAME};
    enum ObjectType {METABOLITE = 0, COMPARTMENT, REACTION, FUNCTION, MODEL, STATE, REPORT};

    void setDataModel(DataModel* dm);
    static DataModel* getDataModel() {return dataModel;};
    static bool notify(ObjectType objectType, Action action, const std::string & key = "");

    void switchToOtherWidget(const std::string & key);
  private:
    CMathModel *mpMathModel;

    CopasiWidget* findWidgetFromItem(FolderListItem* item) const;

    void loadSteadyStateTaskNodes(CSteadyStateTask*);
    void loadTrajectoryTaskNodes(CTrajectoryTask* p_trajectorytask);
    void ConstructNodeWidgets();

    void clearItem(QListViewItem *);
    void clearParentItem(QListViewItem *); // for the top level items to be cleared..

    void setupFolders();

    void setTheRightPixmap(QListViewItem* lvi);

    QListViewItem* searchListViewItem(Folder*);
    QListViewItem* searchListViewItem(int); // search by folder id
    QListViewItem* searchListViewItem(const char*); // search by folder name
    QListViewItem* searchListViewItem(const std::string & key); //search by object key

    bool existsListViewItem(QListViewItem* me);

  private slots:
    void slotFolderChanged(QListViewItem*);

  private:
    static DataModel* dataModel;
    QListViewItem* lastSelection;
    QWidget* currentWidget;
    std::string lastKey;

    static std::set<ListViews *> mListOfListViews;
    bool attach();
    bool detach();
    bool update(ObjectType objectType, Action action, const std::string & key = "");
    bool updateListViews(ObjectType objectType, Action action, const std::string & key);
    static bool updateDataModelAndListviews(ObjectType objectType, Action action, const std::string & key);
    static bool updateAllListviews1(C_INT32 id);
    static bool updateAllListviews2(C_INT32 id);

    void deleteAllMyChildrens(QListViewItem* me);
    void addItem(QListViewItem* parent, Folder* child);
    void addItem(QListView* parent, Folder* child);
    void addItem(Node<Folder>* child);
    void showMessage(QString caption, QString text);
    void loadModes(QListViewItem*);
    static void loadMetabolitesToDataModel();
    static void loadReactionsToDataModel();
    static void loadMoietiesToDataModel();
    static void loadCompartmentsToDataModel();
    static void loadFunctionsToDataModel();
    static void loadReportDefinition();
    static void loadPlotsToDataModel();

    //the widgets
    QListView *folders;
    QMultiLineEdit *bigWidget;

    ScanWidget *scanWidget;
    inline ScanWidget* getScanWidget() const
      {
        return scanWidget;
      }

    SteadyStateWidget *steadystateWidget;
    inline SteadyStateWidget* getSteadystateWidget() const
      {
        return steadystateWidget;
      }

    TrajectoryWidget *trajectoryWidget;
    inline TrajectoryWidget* getTrajectoryWidget() const
      {
        return trajectoryWidget;
      }

    MetabolitesWidget *metabolitesWidget;
    ReactionsWidget *reactionsWidget;
    CompartmentsWidget *compartmentsWidget;
    CompartmentSymbols *compartmentSymbols;
    MoietyWidget *moietyWidget;
    FunctionWidget *functionWidget;
    FunctionSymbols *functionSymbols;
    DifferentialEquations *differentialEquations;
    ReactionsWidget1 *reactionsWidget1;
    MetabolitesWidget1 *metabolitesWidget1;
    MetaboliteSymbols *metaboliteSymbols;
    FixedMetaboliteSymbols *fixedMetaboliteSymbols;
    CompartmentsWidget1 *compartmentsWidget1;
    ConstantSymbols *constantSymbols;
    MoietyWidget1 *moietyWidget1;
    FunctionWidget1 *functionWidget1;
    ModesWidget *modesWidget;
    ModelWidget *modelWidget;
    TableDefinition *tableDefinition;
    TableDefinition1 *tableDefinition1;
    OptimizationWidget *optimizationWidget;
    PlotWidget1 *plotWidget1;
    PlotWidget *plotWidget;
  };

#endif
