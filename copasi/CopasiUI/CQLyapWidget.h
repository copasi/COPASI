/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQLyapWidget.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef LYAPWIDGET_H
#define LYAPWIDGET_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include "CopasiUI/copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QComboBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QTable;
class CLyapTask;
class CLyapProblem;
class CLyapMethod;
class CModel;

class CQLyapWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQLyapWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQLyapWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  signals:

  protected slots:
    virtual void CancelChange();
    virtual void CommitChange();
    virtual void UpdateMethod(const bool & update = true);
    virtual void ReportDefinitionClicked();
    virtual void outputDefinitionClicked();

    //virtual void DurationSlot();
    //virtual void StepsizeSlot();
    //virtual void NumStepsSlot();

    //checks whether the time series will be too huge
    //void checkTimeSeries();

  public slots:
    virtual void runLyapTask();

  private:

    std::string objKey;
    void loadLyapTask();
    void saveLyapTask();
    void loadMethodParameters();

    //QWidget* pParent;
    QGridLayout* CQLyapWidgetLayout;
    QHBoxLayout* Layout2;
    QFrame* line8;
    QTable* parameterTable;
    QLabel* taskNameLabel;
    QFrame* line7;
    QFrame* line7_2;
    QComboBox* ComboBox1;
    QCheckBox* bExecutable, *setInitialState;
    //QCheckBox* bStoreTimeSeries;
    QCheckBox* bDivergence;
    QLabel* parameterValueLabel;
    QLabel* TextLabel1;
    QLabel* TextLabel1_3_2;
    //QLineEdit* nStepSize;
    QLabel* TextLabelNum;
    QLineEdit* lineNum;
    //QLineEdit* nStepNumber;
    QLabel* TextLabel1_2;
    QFrame* line6;
    QPushButton* bRunTask;
    QPushButton* cancelChange;
    QPushButton* reportDefinitionButton;
    QPushButton* outputDefinitionButton;
    QLineEdit* mLineEditStartOutput;
    QCheckBox* mCheckBoxStartOutput;

    //CLyapProblem * mpProblem;
  };

#endif // TRAJECTORYWIDGET_H
