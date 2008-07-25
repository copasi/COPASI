/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/FunctionWidget1.h,v $
 $Revision: 1.54 $
 $Name:  $
 $Author: pwilly $
 $Date: 2008/07/25 06:53:38 $
 End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 **  $ CopasiUI/FunctionWidget1.h
 **  $ Author  : Mrinmayee Kulkarni
 **
 ** This is the header file for Function Widget1, i.e the Second  level
 ** widget which shows detailed description of an individual function
 *****************************************************************************/
#ifndef FUNCTION_WIDGET1_H
#define FUNCTION_WIDGET1_H

#include <sstream>

#include "UI/copasiWidget.h"

class QVBox;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QHButtonGroup;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QTable;
class QTextEdit;
class QWidgetStack;
class QToolButton;
class QSpacerItem;
//class MyLineEdit;

class QtMmlWidget;

class CFunction;
class CFunctionParameters;
class CUsageRange;
template <class CType> class CCopasiVectorN;

/*!
  \brief A widget class for Functions branch

  This widget shows detailed description of an individual function
 */
class FunctionWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    FunctionWidget1(QWidget *parent, const char * name = 0, WFlags f = 0);
    virtual ~FunctionWidget1();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotCancelButtonClicked();
    virtual void slotCommitButtonClicked();
    virtual void slotNewButtonClicked();
    virtual void slotDeleteButtonClicked();
    virtual void slotTableValueChanged(int row, int col);
    //virtual void slotAppTableValueChanged(int row, int col);
    virtual void slotToggleFcnDescriptionEdit();
    virtual void slotFcnDescriptionChanged();
    virtual void slotReversibilityChanged();
    void slotSave();

  protected:
    bool loadFromFunction(const CFunction* = NULL);
    bool loadParameterTable();
    bool loadUsageTable(/*const CCopasiVectorN<CUsageRange>& usages*/);
    bool loadReversibility(TriLogic rev);
    void updateApplication();
    bool saveToFunction();
    bool copyFunctionContentsToFunction(const CFunction* src, CFunction* target);
    bool functionParametersChanged();
    void updateMmlWidget();

    std::string objKey;
    bool flagRO;
    bool flagChanged;
    bool isValid;

    //Widgets
    QGridLayout* FunctionWidget1Layout;
    QHBoxLayout* Layout1;
    QHBoxLayout* Layout2;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QTextEdit* textBrowser;

    QFrame* Line2;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QPushButton* newFcn;
    QPushButton* deleteFcn;
    QHButtonGroup* ButtonGroup1;
    QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;
    QRadioButton* RadioButton3;
    QLabel* TextLabel4;
    QFrame* Line3;
    QLineEdit* LineEdit1;
    QTable* Table2;
    QLabel* TextLabel5;
    QFrame* Line4;
    QTable* Table1;
    QLabel* TextLabel3;
    QFrame* Line1;

    QWidgetStack* mStack;
    QVBox* mMmlViewBox;
    QScrollView* mScrollView;
#ifdef HAVE_MML
    //    QPushButton* mFormulaEditToggleButton;
    QToolButton* mFormulaEditToggleButton;
    QtMmlWidget* mMmlWidget;

    QString MMLStr;
#endif // HAVE_MML
    CFunction * mpFunction;

    QToolButton *mpSaveBtn;
    QHBoxLayout *mpFormulaHBL;
    QVBoxLayout *mpFormulaVBL;
    QSpacerItem *mpFormulaSpacer;

  private:

#ifdef HAVE_MML
    void saveTeX(const QString filename);
    void saveMML(const QString filename);
#endif // HAVE_MML
  };

#endif // FunctionWidget1
