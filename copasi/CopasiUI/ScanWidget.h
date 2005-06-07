/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ScanWidget.h,v $
   $Revision: 1.55 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/06/07 21:45:41 $
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
#include "copasiWidget.h"
#include "utilities/CVector.h"
#include <vector>

class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QLabel;
class QPushButton;
class QComboBox;
class QToolButton;

class CScanTask;
class CScanProblem;
class CScanMethod;
class CModel;
class SteadyStateWidget;
class TrajectoryWidget;
class CCopasiObject;
class CScanContainerWidget;

class ScanWidget : public CopasiWidget
  {
    Q_OBJECT

  private:
    std::string scanTaskKey;

  public:
    ScanWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanWidget();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected:
    bool loadScan();

    bool saveScan() const;

    //inline std::string getScanTaskKey() const {return scanTaskKey;};

    CScanContainerWidget* scrollview;
    QCheckBox* sExecutable;
    QPushButton* scanButton;
    QPushButton* cancelChange;

    QPushButton* buttonNewItem;
    QComboBox* comboType;

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;

    QPushButton* reportDefinitionButton;
    QPushButton* outputDefinitionButton;

    QGridLayout* ScanWidgetLayout;
    QHBoxLayout* Layout2;
    QHBoxLayout* Layout24;
    CModel *mModel;

  public slots:
    virtual void CancelChangeButton();
    virtual void ScanCheckBoxClicked();

    virtual void runScanTask();
    //virtual void SteadyStateButtonClicked();
    //virtual void TrajectoryButtonClicked();

    //virtual void SteadyStateEditing();
    //virtual void TrajectoryEditing();

    virtual void ReportDefinitionClicked();
    virtual void outputDefinitionClicked();

  protected slots:
    bool slotAddItem();
  };

#endif
