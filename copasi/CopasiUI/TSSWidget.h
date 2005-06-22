/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TSSWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/06/22 14:23:07 $
   End CVS Header */

#ifndef TSSWIDGET_H
#define TSSWIDGET_H

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
class CTSSTask;
class CTSSProblem;
class CTSSMethod;
class CModel;

class TSSWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    TSSWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TSSWidget();

    void loadTask();

    QFrame* line7;
    QFrame* line6;
    QFrame* line8;
    QFrame* line8_2;
    QLabel* taskNameLabel;
    //QCheckBox* taskJacobian;
    //QCheckBox* taskStability;
    //QLabel* taskDescriptionLabel;
    QLabel* parameterValueLabel;
    QCheckBox* bExecutable;
    // QCheckBox* setInitialState;
    //QLineEdit* taskName;
    QTable* parameterTable;
    QPushButton* bRunButton;
    QPushButton* cancelChange;
    //QPushButton* ExportFileButton;
    QPushButton* reportDefinitionButton;

  signals:
    //virtual void runFinished(CModel*);

  public slots:
    virtual void CancelButtonClicked();
    virtual void CommitButtonClicked();
    //virtual void ExportToFileButtonClicked();
    virtual void parameterValueChanged();
    //virtual void RunButtonChecked();
    virtual void runTask();
    virtual void ReportDefinitionClicked();

  protected:
    QGridLayout* TSSWidgetLayout;
    QHBoxLayout* Layout2;
    std::string objKey;
    QWidget* pParent;
  };

#endif // STEADYSTATEWIDGET_H
