// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpressionWidget.h,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/09/23 12:45:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQEXPRESSION
#define CQEXPRESSION

//#include <q3textedit.h>
#include <QTextEdit>
//#include <q3syntaxhighlighter>
#include <QSyntaxHighlighter.h>
//Added by qt3to4:
#include <QKeyEvent>

#include <QKeySequence>

#include <vector>

#include "UI/CQValidator.h"
#include "UI/CCopasiSimpleSelectionTree.h"

#include "function/CExpression.h"

class CQExpressionWidget;
class CCopasiObject;

/*!
    \brief The class for highlighting the expression syntax
 */
//class CQExpressionHighlighter: public Q3SyntaxHighlighter
class CQExpressionHighlighter: public QSyntaxHighlighter
{
public:
  CQExpressionHighlighter(CQExpressionWidget* ew);
  ~CQExpressionHighlighter();

  virtual int highlightParagraph(const QString & text, int endStateOfLastPara);

// new since 14.09.09
protected:
  void highlightBlock(const QString &text);

public:
  QTextCharFormat COPASIObjectFormat;
  QRegExp COPASIObjectPattern;
};

/*!
    \brief The class for checking the validity of a given mathematical expression
 */
//class CQValidatorExpression: public CQValidator< Q3TextEdit >
class CQValidatorExpression: public CQValidator< QTextEdit >
{
public:
//  CQValidatorExpression(Q3TextEdit * parent, const char * name = 0, bool isBoolean = false);
  CQValidatorExpression(QTextEdit * parent, const char * name = 0, bool isBoolean = false);

  /**
   * Function to validate a string input
   */
  virtual State validate(QString & input, int & pos) const;

  /**
   * Function to get CExpression object
   */
  virtual CExpression *getExpression();

  void setBooleanRequired(bool booleanRequired) {mExpression.setBooleanRequired(booleanRequired);};

protected:
  CExpression mExpression;
};

/*!
    \brief The class for writing/editing a mathematical expression
 */
//class CQExpressionWidget: public Q3TextEdit
class CQExpressionWidget: public QTextEdit
{
  Q_OBJECT
public:
  CQExpressionWidget(QWidget * parent = 0, const char * name = 0, bool isBoolean = false);

  ~CQExpressionWidget();

  CQValidatorExpression * mpValidator;

protected:
  int mOldPar;
  int mOldPos;

  int mOldPar1;
  int mOldPos1;
  int mOldPar2;
  int mOldPos2;

  /**
   * Function to indicate whether we are dealing with an INITIAL or TRANSIENT expression
   */
  CCopasiSimpleSelectionTree::ObjectClasses mObjectClasses;

  std::map< std::string, const CCopasiObject * > mParseList;
  const CCopasiObject * mpCurrentObject;
  QString mNewName;

  QColor mSavedColor;
  QColor mChangedColor;

  virtual void keyPressEvent(QKeyEvent * e);
  virtual void mousePressEvent(QMouseEvent * e);

  bool isInObject();
  bool isInObject(int par, int pos);

  /**
   * Function to check whether the current cursor position is in object
   */
  bool isInObject(int pos);

  /**
   * returns true if (par/pos) is right of (parold/posold)
   */
  bool compareCursorPositions(int parold, int posold, int par, int pos);

  /**
   * return anchor position -> new 16.09.09
   */
  int mAnchorPos;

public:
  /**
   * Enumeration of movement type
   */
  enum MoveType {None, Left, Right, Mouse, Unknown };
  enum ActionType {NoAction, /*Undo*/ };

  enum ExpressionType
  {
    InitialExpression = CCopasiSimpleSelectionTree::InitialTime |
    CCopasiSimpleSelectionTree::Parameters |
    CCopasiSimpleSelectionTree::ObservedConstants,
    TransientExpression = CCopasiSimpleSelectionTree::InitialTime |
    CCopasiSimpleSelectionTree::Parameters |
    CCopasiSimpleSelectionTree::ObservedConstants |
    CCopasiSimpleSelectionTree::Time |
    CCopasiSimpleSelectionTree::Variables |
    CCopasiSimpleSelectionTree::ObservedValues,
    ObjectiveFunctions = CCopasiSimpleSelectionTree::InitialTime |
    CCopasiSimpleSelectionTree::Parameters |
    CCopasiSimpleSelectionTree::ObservedConstants |
    CCopasiSimpleSelectionTree::Time |
    CCopasiSimpleSelectionTree::Variables |
    CCopasiSimpleSelectionTree::ObservedValues |
    CCopasiSimpleSelectionTree::Results
  };

  /**
   * Set the expression for the widget
   * @param const std::string & expression
   */
  void setExpression(const std::string & expression);

  /**
   * Retrieve the expression from the widget in string format
   * @return std::string expression
   */
  std::string getExpression() const;

  /**
   * Set the type of the current expression
   * @param const ExpressionType & expressionType
   */
  void setExpressionType(const ExpressionType & expressionType);

  void setBoolean(bool isBoolean);

  bool isValid();

protected slots:
//  void slotCursorPositionChanged(int para, int pos);

  /**
   * Slot for being activated whenever the cursor is moved
   */
  void slotCursorPositionChanged();

  /**
   * Slot for being activated
   */
  void slotSelectionChanged();

  /**
   * Slot for being activated whenever the text on Expression Widget is changed
   */
  void slotTextChanged();

public slots:
//  void doKeyboardAction(Q3TextEdit::KeyboardAction action);
  void doKeyboardAction(QTextEdit::KeyboardAction action);
  void slotSelectObject();

  void slotCharFormatChanged(const QTextCharFormat & f);

signals:
  void valid(bool valid);

private:
  CQExpressionHighlighter *expressionHighlighter;
  MoveType eMove;
  ActionType eAction;
  bool goFurther;
  QTextCursor mCursor;
};

#endif
