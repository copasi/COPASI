/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ScanWidget.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:50 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/ScanWidget.h               
 **  $ Author  : Liang Xu
 **  
 ** This is the header file for the Scan Widget
 *****************************************************************************/
#ifndef SCANWIDGET_H
#define SCANWIDGET_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include <qscrollview.h>
#include "copasiWidget.h"
#include "utilities/CVector.h"
#include <vector>

class QVBox;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QListBox;
class QListBoxItem;
class QVBoxLayout;
class CScanTask;
class CScanProblem;
class CScanMethod;
class CModel;
class QToolButton;
class SteadyStateWidget;
class TrajectoryWidget;
class ScanItemWidget;
class CCopasiObject;
class ScanWidget;

class ScanScrollView: public QScrollView
  {
    Q_OBJECT
  private:
    CopasiParametersWidget* mParent;
    std::vector<QWidget*>* pSelectedList;
  public:
    void setSelectedList(std::vector<QWidget*>* pNewSelectedList);
    ScanScrollView(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    virtual void contentsMousePressEvent (QMouseEvent * e);
    virtual void resizeEvent (QResizeEvent * e);
    virtual void viewportResizeEvent (QResizeEvent *e);
  };

class ScanWidget : public CopasiParametersWidget
  {
    Q_OBJECT

  private:
    int nSelectedObjects;
    int nTitleHeight;
    int activeObject;
    QWidget* pParent;
    std::string scanTaskKey;

  public:
    ScanWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanWidget();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    //    void loadScan(CModel *model);
    void loadScan();
    inline std::string getScanTaskKey() const {return scanTaskKey;};
    bool addNewScanItem(CCopasiObject* pObject);

    QListBox* ObjectListBox;
    QLineEdit* taskName;
    QFrame* Line1;
    QFrame* Line2;
    QFrame* Line1_2;

    ScanScrollView* scrollview;
    QCheckBox* sExecutable;
    QPushButton* scanButton;
    QPushButton* cancelChange;
    QPushButton* downButton;
    QPushButton* upButton;
    QPushButton* deleteButton;
    QPushButton* addButton;

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;

    QCheckBox* steadyState;
    QToolButton* eSteadyState;
    QCheckBox* trajectory;
    QToolButton* eTrajectory;

    std::string SteadyStateKey;
    std::string TrajectoryKey;
    SteadyStateWidget* pSteadyStateWidget;
    TrajectoryWidget* pTrajectoryWidget;
    std::vector<QWidget*> selectedList;

    QPushButton* reportDefinitionButton;
  protected:
    QGridLayout* ScanWidgetLayout;
    QHBoxLayout* Layout4;
    QHBoxLayout* Layout3;
    QHBoxLayout* Layout4_2;
    QHBoxLayout* Layout2;
    QHBoxLayout* Layout24;
    QVBoxLayout* Layout7;
    QGridLayout* Layout6;
    CModel *mModel;

  signals:
    void hide_me();
    void show_me();

  public slots:
    virtual void CancelChangeButton();
    virtual void ScanCheckBoxClicked();
    virtual void addButtonClicked();
    virtual void deleteButtonClicked();
    virtual void upButtonClicked();
    virtual void downButtonClicked();

    virtual void runScanTask();
    virtual void SteadyStateButtonClicked();
    virtual void TrajectoryButtonClicked();

    virtual void SteadyStateEditing();
    virtual void TrajectoryEditing();
    virtual void ListBoxClicked (QListBoxItem * item);
    virtual void ListBoxDoubleClicked (QListBoxItem* item);

    virtual void ReportDefinitionClicked();
  public:
    void mouseSelected(ScanItemWidget* pSelected);
    void viewMousePressEvent(QMouseEvent* e);
  };

#endif
