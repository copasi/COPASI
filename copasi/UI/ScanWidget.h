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
#include <vector>

class QVBox;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QTable;
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
    ScanWidget* mParent;

  public:
    ScanScrollView(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    virtual void contentsMousePressEvent (QMouseEvent * e);
  };

class ScanWidget : public CopasiWidget
  {
    Q_OBJECT

  private:
    static int nSelectedObjects;
    int activeObject;
  public:
    ScanWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanWidget();
    CScanTask *scanTask;
    void loadScan(CModel *model);
    void addNewScanItem(CCopasiObject* pObject);

    QLabel* TextLabel1;
    QLineEdit* taskName;
    QFrame* Line1;
    ScanScrollView* scrollview;
    QFrame* Line2;
    QCheckBox* sExecutable;
    QPushButton* commitChange;
    QPushButton* cancelChange;
    QPushButton* downButton;
    QPushButton* upButton;
    QPushButton* deleteButton;
    QPushButton* addButton;
    QFrame* Line1_2;
    QLabel* TextLabel2;
    QCheckBox* steadyState;
    QToolButton* eSteadyState;
    QLabel* TextLabel3;
    QCheckBox* trajectory;
    QToolButton* eTrajectory;

    SteadyStateWidget* pSteadyStateWidget;
    TrajectoryWidget* pTrajectoryWidget;

    std::vector<QWidget*> selectedList;

  protected:
    QGridLayout* ScanWidgetLayout;
    QHBoxLayout* Layout2;
    QHBoxLayout* Layout3;
    QHBoxLayout* Layout4;
    CModel *mModel;

  signals:
    void hide_me();
    void show_me();

  public slots:
    virtual void CancelChangeButton();
    virtual void CommitChangeButton();
    virtual void addButtonClicked();
    virtual void deleteButtonClicked();
    virtual void upButtonClicked();
    virtual void downButtonClicked();

    virtual void ScanButtonClicked();
    virtual void SteadyStateButtonClicked();
    virtual void TrajectoryButtonClicked();

    virtual void SteadyStateEditing();
    virtual void TrajectoryEditing();

  public:
    void mouseSelected(ScanItemWidget* pSelected);
    void viewMousePressEvent(QMouseEvent* e);
  };

#endif
