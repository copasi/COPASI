/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMCAWidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/15 12:30:39 $
   End CVS Header */

#ifndef CMCAWIDGET_H
#define CMCAWIDGET_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QTable;

class CMCAWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    CMCAWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CMCAWidget();

    void loadMCATask();
    void saveMCATask();
    //    void setModel(CModel* newModel);

    QFrame* line7;
    QFrame* line6;
    QFrame* line8;
    QFrame* line8_2;
    QLabel* taskNameLabel;
    QLabel* parameterValueLabel;
    //QLineEdit* taskName;
    QTable* parameterTable;
    QPushButton* bRunButton;
    QPushButton* cancelChange;
    QPushButton* reportDefinitionButton;
    QCheckBox* taskSteadyState;
    QCheckBox* bExecutable;

  public slots:
    virtual void CancelButtonClicked();
    virtual void parameterValueChanged();
    virtual void runMCATask();
    virtual void ReportDefinitionClicked();
    virtual void taskSteadyStateToggled();

  protected:
    QGridLayout* CMCAWidgetLayout;
    QHBoxLayout* Layout2;
    std::string objKey;
    QWidget* pParent;

    void initParameterTable();
  };

#endif // CMCAWIDGET_H
