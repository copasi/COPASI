// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQEXPRESSION
#define CQEXPRESSION

#include <QTextEdit>
#include <QSyntaxHighlighter>
#include <QKeyEvent>

#include <QKeySequence>
#include <QRegExp>

#include <vector>

#include "copasi/UI//CQValidator.h"
#include "copasi/UI/CQSimpleSelectionTree.h"

#include "copasi/function/CExpression.h"
#include "copasi/function/CFunction.h"

class CQExpressionWidget;
class CDataObject;

/*!
    \brief The class for highlighting the expression syntax
 */
class CQExpressionHighlighter: public QSyntaxHighlighter
{
public:
  CQExpressionHighlighter(CQExpressionWidget *ew);
  virtual ~CQExpressionHighlighter();

protected:
  void highlightBlock(const QString &text);

public:
  QTextCharFormat mObjectDisplayFormat;
  QRegExp mObjectDisplayPattern;
};

/**
 *  The class for checking the validity of a given mathematical expression
 */
class CQValidatorExpression: public CQValidator< QTextEdit >
{
public:
  CQValidatorExpression(QTextEdit *parent, const char *name = 0, bool isBoolean = false);

  /**
   * Function to validate a string input
   */
  virtual State validate(QString &input, int &pos) const;

  /**
   * Function to get CExpression object
   */
  virtual CExpression *getExpression();

  /**
   * Function to set whether boolean is required
   */
  void setBooleanRequired(bool booleanRequired);

protected:
  CExpression mExpression;
};

/**
 *  The class for checking the validity of a given mathematical function
 */
class CQValidatorFunction: public CQValidator< QTextEdit >
{
  Q_OBJECT
public:
  /**
   * Specific constructor
   * @param QTextEdit * parent
   * @param const char * name (Default: NULL)
   */
  CQValidatorFunction(QTextEdit *parent, const char *name = 0);

  /**
   * Function to validate a string input
   * @param QString & input
   * @param int & pos
   * @return State
   */
  virtual State validate(QString &input, int &pos) const;

  /**
   * Retrieve a pointer to the function object
   * @return CFunction * pFunction
   */
  virtual CFunction *getFunction();

protected:
  CFunction mFunction;

signals:
  void stateChanged(bool) const;
};

/**
 * The class for writing/editing a mathematical expression
 */
class CQExpressionWidget: public QTextEdit
{
  Q_OBJECT
public:
  static const char InfixPattern[];
  static const char DisplayPattern[];

  CQExpressionWidget(QWidget *parent = 0, const char *name = 0);

  ~CQExpressionWidget();

  /**
   * Write display mathml of the expression into the ostream "out"
   */
  void writeMathML(std::ostream &out) const;

  CQValidator< QTextEdit > *getValidator();

private:
  CQValidatorExpression *mpValidatorExpression;

  CQValidatorFunction *mpValidatorFunction;

protected:
  /**
   * Function to indicate whether we are dealing with an INITIAL or TRANSIENT expression
   */
  CQSimpleSelectionTree::ObjectClasses mObjectClasses;

  std::map< std::string, const CDataObject * > mParseList;
  const CDataObject *mpCurrentObject;
  QColor mSavedColor;
  QColor mChangedColor;
  QColor mText;

  /**
   * Function to handle key press events.
   */
  virtual void keyPressEvent(QKeyEvent *e);

  /**
   * Function to handle mouse release events.
   */
  virtual void mouseReleaseEvent(QMouseEvent *e);

  /**
   * Function to handle drag leave events.
   */
  virtual void dropEvent(QDropEvent *e);

  /**
   * Function to check whether the given cursor position is in an object.
   * If the position is within an object left and right mark the boundaries.
   * @param const int & position
   * @param int & left
   * @param int & right
   * @return bool isInObject
   */
  bool objectBoundaries(const int &position, int &left, int &right) const;

public:
  /**
   * Enumeration of expression type
   */
  enum ExpressionType
  {
    InitialExpression = CQSimpleSelectionTree::InitialTime |
                        CQSimpleSelectionTree::Parameters |
                        CQSimpleSelectionTree::ObservedConstants,
    TransientExpression = CQSimpleSelectionTree::InitialTime |
                          CQSimpleSelectionTree::Parameters |
                          CQSimpleSelectionTree::ObservedConstants |
                          CQSimpleSelectionTree::Time |
                          CQSimpleSelectionTree::Variables |
                          CQSimpleSelectionTree::ObservedValues,
    ObjectiveFunctions = CQSimpleSelectionTree::InitialTime |
                         CQSimpleSelectionTree::Parameters |
                         CQSimpleSelectionTree::ObservedConstants |
                         CQSimpleSelectionTree::Time |
                         CQSimpleSelectionTree::Variables |
                         CQSimpleSelectionTree::ObservedValues |
                         CQSimpleSelectionTree::Results
  };

  /**
   * Set the function for the widget
   * @param const std::string & function
   */
  void setFunction(const std::string &function);

  /**
   * Retrieve the function from the widget in string format
   * @return std::string function
   */
  std::string getFunction() const;

  /**
   * Set the expression for the widget
   * @param const std::string & expression
   */
  void setExpression(const std::string &expression);

  /**
   * Retrieve the expression from the widget in string format
   * @return std::string expression
   */
  std::string getExpression() const;

  /**
   * Set the type of the current expression
   * @param const ExpressionType & expressionType
   */
  void setExpressionType(const ExpressionType &expressionType);

  /**
   * Set the boolean
   * @param bool isBoolean
   */
  void setBoolean(bool isBoolean);

  /**
   * Check validity of expression
   * @return bool expression
   */
  bool isValid();

public slots:
  /**
   * Slot for being activated whenever the text on Expression Widget is changed
   */
  void slotTextChanged();

  /**
   * Slot for selecting an object
   */
  void slotSelectObject();

signals:
  /**
   * Signal for being sent whenever the expression is valid
   */
  void valid(bool valid);

private:
  CQExpressionHighlighter *mpExpressionHighlighter;
  QTextCursor mCursor;
};

#endif
