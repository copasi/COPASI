/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationWidget.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/30 15:39:51 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/OptimizationWidget.h               
 **  $ Author  : Anrurag Srivastava
 **  
 ** This is the header file for the Optimization Widget
 *****************************************************************************/

#ifndef OPTIMIZATIONWIDGET_H
#define OPTIMIZATIONWIDGET_H

#include <qvariant.h>
#include <qwidget.h>

#include <vector>

#include "copasi.h"
#include "copasiWidget.h"
#include "utilities/CVector.h"
#include "CScanContainerWidget.h"
#include "utilities/CCopasiVector.h"
#include "report/CKeyFactory.h"
#include "function/CFunction.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QCheckBox;
class QGroupBox;
class QLineEdit;
class QLabel;
class QTable;
class QFrame;
class QPushButton;
class QComboBox;

class COptTask;
class COptProblem;
class COptMethod;
class CModel;
class CCopasiObject;

class OptimizationWidget : public CopasiWidget
  {
    Q_OBJECT

  private:
    std::string optimizationTaskKey;
    QWidget* pParent;
    //CFunction * pFunction;

  public:

    OptimizationWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~OptimizationWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    virtual std::string getKey();

  protected:
    bool loadOptimization();
    bool saveOptimization();

    /* functions for parsing <start>*/
    bool saveExpression();

    /* functions for parsing <end>*/

    CScanContainerWidget* scrollview;
    CCopasiObject* mObject;
    CModel *mModel;
    std::vector<CCopasiObject *> parseList;

    QPushButton* reportDefinitionButton;
    QHBoxLayout* scrollviewLayout;
    QHBoxLayout* expressionTextLayout;
    QVBoxLayout *methodGroupBoxLayout;

    QGridLayout* optimizationWidgetLayout, *constraintLayout, *typeGroupBoxLayout;

    /*<from UIC>*/

    QHBoxLayout* Layoutparams, *buttonsLayout, *nameLayout;

    QFrame* buttonsSeparator;
    QGroupBox* paramsGroupBox;
    //QGroupBox* typeGroupBox;
    QCheckBox* timeCheck;
    QCheckBox* steadystateCheck;
    QCheckBox* taskExecCheck;
    QPushButton* AddTaskButton;
    //QGroupBox* methodGroupBox;
    QLabel* methodLabel, *typeLabel, *nameLabel;
    QComboBox* methodCombo;
    QPushButton* runButton;
    QPushButton* cancelButton;
    QPushButton* reportButton;
    QPushButton* outputAssistantButton;
    QPushButton* selectParameterButton;
    QLabel* expressionEditlabel;
    QLineEdit* expressionText;
    QTable* parameterTable;

  protected:

    /*</from UIC>*/

  public slots:

    virtual void CancelChangeButton();
    virtual void CheckBoxClicked();
    virtual void ReportDefinitionClicked();
    virtual void runOptimizationTask();
    virtual void slotTimechecked();
    virtual void slotSteadystatechecked();
    virtual void slotConfirm();
    virtual void slottaskExecCheck();

  protected slots:
    virtual void languageChange();
    bool changeMethod(int);
    void slotChooseObject();
    bool slotAddItem();
  };

#endif
