/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/TaskWidget.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/18 13:02:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"

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
class QSpacerItem;

class CQTaskHeaderWidget;
class CQTaskBtnWidget;

class CCopasiTask;
#include "utilities/CCopasiMethod.h"

//class CModel;
class CProgressBar;

class TaskWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    TaskWidget(QWidget* parent = 0,
               const char* name = 0,
               WFlags fl = 0);

    ~TaskWidget();

    //the TaskWidget interface
    virtual bool update(ListViews::ObjectType objectType,
                        ListViews::Action action,
                        const std::string & key);

    virtual bool leave();

    virtual bool enter(const std::string & key = "");

    virtual bool runTask() = 0;

  protected slots:
    void runBtnClicked();

    void revertBtnClicked();

    void reportBtnClicked();

    void assistantBtnClicked();

    void changeMethod(int);

  protected:
    std::string mObjectKey;
    CProgressBar * mProgressBar;

    virtual bool loadTask() = 0;

    virtual bool saveTask() = 0;

    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type) = 0;

    //these methods should be called by the loadTask() or saveTask() methods
    //of the derived classes. They handle the "executable" checkbox
    bool loadCommon();
    bool saveCommon();

    //these methods should be called by the constructor, loadTask(), or saveTask() methods
    //of the derived classes. They handle the method parameters table
    void addMethodSelectionBox(const unsigned C_INT32 * validMethods, unsigned int row = 2);
    void addMethodParameterTable(const unsigned C_INT32 & rows = 4, unsigned int row = 3);

    //convenience functions
    void addHeaderToGrid(unsigned int row = 0);
    bool addHLineToGrid(QGridLayout* grid, unsigned int row, unsigned int maxcol);

    bool loadMethod();
    bool saveMethod();

    //this method should be called at the beginning or the end of the runTask() method
    //of the derived classes, respectively
    bool commonBeforeRunTask();
    bool commonAfterRunTask();

    bool commonRunTask();

    CQTaskHeaderWidget * mpHeaderWidget;
    CQTaskBtnWidget * mpBtnWidget;

    QGridLayout * mpMethodLayout;

    QLabel * mpLblParameter;
    QTable * mpTblParameter;
    QSpacerItem * mpSpacer1;
    QLabel * mpLblMethod;
    QComboBox * mpBoxMethod;
    QSpacerItem * mpSpacer2;

    CCopasiTask * mpTask;
    CCopasiMethod * mpMethod;

    bool mChanged;
  };

#endif
