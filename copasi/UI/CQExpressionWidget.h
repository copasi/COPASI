// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpressionWidget.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/12 19:27:44 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQEXPRESSION
#define CQEXPRESSION

#include <qtextedit.h>
#include <qsyntaxhighlighter.h>

#include <vector>

#include "UI/CQValidator.h"
#include "UI/CCopasiSimpleSelectionTree.h"

#include "function/CExpression.h"

class CQExpressionWidget;
class CCopasiObject;

class CQExpressionHighlighter: public QSyntaxHighlighter
  {
  public:
    CQExpressionHighlighter(CQExpressionWidget* ew);
    ~CQExpressionHighlighter() {};

    virtual int highlightParagraph (const QString & text, int endStateOfLastPara);
  };

class CQValidatorExpression: public CQValidator< QTextEdit >
  {
  public:
    CQValidatorExpression(QTextEdit * parent, const char * name = 0);

    virtual State validate(QString & input, int & pos) const;

  protected:
    CExpression mExpression;
  };

class CQExpressionWidget: public QTextEdit
  {
    Q_OBJECT
  public:
    CQExpressionWidget(QWidget * parent = 0, const char * name = 0);

    CQValidatorExpression * mpValidator;

  protected:
    int mOldPar;
    int mOldPos;

    int mOldPar1;
    int mOldPos1;
    int mOldPar2;
    int mOldPos2;

    /**
     * Indecates whether we are dealing with an INITIAL or TRANSIENT expression
     */
    CCopasiSimpleSelectionTree::SelectionFlag mExpressionType;

    std::map< std::string, const CCopasiObject * > mParseList;
    const CCopasiObject * mpCurrentObject;
    QString mNewName;

    QColor mSavedColor;
    QColor mChangedColor;

    virtual void keyPressEvent (QKeyEvent * e);

    bool isInObject();
    bool isInObject(int par, int pos);

    /**
     * returns true if (par/pos) is right of (parold/posold)
     */
    bool compareCursorPositions(int parold, int posold, int par, int pos);

  public:
    /**
     * Set the expression for the widget
     * @param const std::string & expression
     */
    void setExpression(const std::string & expression);

    /**
     * Retrieve the expression from the widget
     * @return std::string expression
     */
    std::string getExpression() const;

    /**
     * This function must be called when the current object is renamed
     * @param const CCopasiObject * pObject
     * @param const QString & newName
     */
    void currentObjectRenamed(const CCopasiObject * pObject,
                              const QString & newName);

    /**
     * Set the type of the current expression
     * @param const CCopasiSimpleSelectionTree::SelectionFlag & expressionType
     */
    void setExpressionType(const CCopasiSimpleSelectionTree::SelectionFlag & expressionType);

  protected slots:
    void slotCursorPositionChanged(int para, int pos);
    void slotSelectionChanged();
    void slotTextChanged();

    //void slotLostFocus();
    //void slotReturnPressed();
    //void slotTextChanged(const QString & text);

  public slots:
    void doKeyboardAction (QTextEdit::KeyboardAction action);
    void slotSelectObject();

    //void slotForceUpdate();

    //virtual void setText(const QString & text);

  signals:
    void valid(bool valid);
  };

#endif
