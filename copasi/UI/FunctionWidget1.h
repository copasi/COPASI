/* Begin CVS Header
$Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/FunctionWidget1.h,v $
$Revision: 1.57 $
$Name:  $
$Author: shoops $
$Date: 2009/07/16 15:47:26 $
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
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

class Q3VBox;
class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class Q3HButtonGroup;
class Q3Frame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class Q3Table;
class Q3TextEdit;
class Q3WidgetStack;
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
  FunctionWidget1(QWidget *parent, const char * name = 0, Qt::WFlags f = 0);
  virtual ~FunctionWidget1();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

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
  virtual bool enterProtected();
  bool loadFromFunction(const CFunction* = NULL);
  bool loadParameterTable();
  bool loadUsageTable(/*const CCopasiVectorN<CUsageRange>& usages*/);
  bool loadReversibility(TriLogic rev);
  void updateApplication();
  bool saveToFunction();
  bool copyFunctionContentsToFunction(const CFunction* src, CFunction* target);
  bool functionParametersChanged();
  void updateMmlWidget();

  bool flagRO;
  bool flagChanged;
  bool isValid;

  //Widgets
  Q3GridLayout* FunctionWidget1Layout;
  Q3HBoxLayout* Layout1;
  Q3HBoxLayout* Layout2;
  QLabel* TextLabel1;
  QLabel* TextLabel2;
  Q3TextEdit* textBrowser;

  Q3Frame* Line2;
  QPushButton* commitChanges;
  QPushButton* cancelChanges;
  QPushButton* newFcn;
  QPushButton* deleteFcn;
  Q3HButtonGroup* ButtonGroup1;
  QRadioButton* RadioButton1;
  QRadioButton* RadioButton2;
  QRadioButton* RadioButton3;
  QLabel* TextLabel4;
  Q3Frame* Line3;
  QLineEdit* LineEdit1;
  Q3Table* Table2;
  QLabel* TextLabel5;
  Q3Frame* Line4;
  Q3Table* Table1;
  QLabel* TextLabel3;
  Q3Frame* Line1;

  Q3WidgetStack* mStack;
  Q3VBox* mMmlViewBox;
  Q3ScrollView* mScrollView;
  QToolButton* mFormulaEditToggleButton;

#ifdef HAVE_MML
  QtMmlWidget* mMmlWidget;
#endif // HAVE_MML

  QString MMLStr;
  CFunction * mpFunction;

  QToolButton *mpSaveBtn;
  Q3HBoxLayout *mpFormulaHBL;
  Q3VBoxLayout *mpFormulaVBL;
  QSpacerItem *mpFormulaSpacer;

private:

  void saveMML(const QString filename);

  void saveTeX(const QString filename);
};

#endif // FunctionWidget1
