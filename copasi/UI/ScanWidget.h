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
    ScanWidget* mParent;
    std::vector<QWidget*>* pSelectedList;
  public:
    void setSelectedList(std::vector<QWidget*>* pNewSelectedList);
    ScanScrollView(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    virtual void contentsMousePressEvent (QMouseEvent * e);
    virtual void resizeEvent (QResizeEvent * e);
  };

class ScanWidget : public CopasiWidget
  {
    Q_OBJECT

  private:
    static int nSelectedObjects;
    static int nTitleHeight;
    int activeObject;
  public:
    ScanWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanWidget();
    CScanTask *scanTask;
    void loadScan(CModel *model);
    void addNewScanItem(CCopasiObject* pObject);

    QListBox* ObjectListBox;
    QLineEdit* taskName;
    QFrame* Line1;
    QFrame* Line2;
    QFrame* Line1_2;

    ScanScrollView* scrollview;
    QCheckBox* sExecutable;
    QPushButton* commitChange;
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

    SteadyStateWidget* pSteadyStateWidget;
    TrajectoryWidget* pTrajectoryWidget;

    std::vector<QWidget*> selectedList;

  protected:
    QGridLayout* ScanWidgetLayout;
    QHBoxLayout* Layout2;
    QHBoxLayout* Layout4;
    QHBoxLayout* Layout3;
    QHBoxLayout* Layout4_2;
    QHBoxLayout* Layout8;
    QVBoxLayout* Layout7;
    QGridLayout* Layout6;
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
    virtual void ListBoxClicked (QListBoxItem * item);
    virtual void ListBoxDoubleClicked (QListBoxItem* item);

  public:
    void mouseSelected(ScanItemWidget* pSelected);
    void viewMousePressEvent(QMouseEvent* e);
  };

#endif
