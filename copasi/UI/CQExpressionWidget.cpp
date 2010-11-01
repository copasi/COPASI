// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpressionWidget.cpp,v $
//   $Revision: 1.55.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/11/01 18:00:40 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>

#include <qlabel.h>
#include <qcombobox.h>
//Added by qt3to4:
#include <QKeyEvent>

#include "CQExpressionWidget.h"
#include "CQMessageBox.h"
#include "CCopasiSelectionDialog.h"
#include "qtUtilities.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CExpression.h"
#include "function/CFunctionDB.h"
#include "utilities/CAnnotatedMatrix.h"
#include "model/CModel.h"
#include "CQMatrixDialog.h"
#include "qtUtilities.h"
#include "report/CCopasiRootContainer.h"

#define DEBUG_UI

#ifdef DEBUG_UI
std::ostream &operator<<(std::ostream &os, const QTextCursor & d)
{
  os << "Position:        " << d.position() << std::endl;
  os << "Selection Start: " << d.selectionStart() << std::endl;
  os << "Selection End:   " << d.selectionEnd() << std::endl;
  os << "Anchor:          " << d.anchor() << std::endl;
  os << "Selected Text:   " << TO_UTF8(d.selectedText()) << std::endl;

  return os;
}
#endif // DEBUG_UI

CQExpressionHighlighter::CQExpressionHighlighter(CQExpressionWidget* ew)
    : QSyntaxHighlighter(ew),
    COPASIObjectPattern("\\{([^\\}]|\\.)*\\}")
{
  // COPASI object format
  COPASIObjectFormat.setForeground(QColor(100, 0, 200));
  //COPASIObjectPattern = QRegExp("\\{[^\\{]*\\}");
}

CQExpressionHighlighter::~CQExpressionHighlighter()
{}

void CQExpressionHighlighter::highlightBlock(const QString &text)
{
  int index = COPASIObjectPattern.indexIn(text);

  while (index >= 0)
    {
      int length = COPASIObjectPattern.matchedLength();
      setFormat(index, length, COPASIObjectFormat);
      index = COPASIObjectPattern.indexIn(text, index + length);
    }
}

//***********************************************************************

CQValidatorExpression::CQValidatorExpression(QTextEdit * parent, const char * name, bool isBoolean):
    CQValidator< QTextEdit >(parent, &QTextEdit::text, name),
    mExpression()
{
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  mExpression.setObjectParent(pDataModel);
  mExpression.setBooleanRequired(isBoolean);
}

/**
  *  This function ensures that any characters on Expression Widget are validated
  *  to go to further processes.
  */
QValidator::State CQValidatorExpression::validate(QString & input, int & pos) const
{
  // The input is the display version of the infix string.
  // We must first convert the display string to infix.

  CQExpressionWidget * pExpressionWidget =
    static_cast< CQExpressionWidget * >(parent());

  if (pExpressionWidget != NULL)
    {
      if (const_cast< CExpression * >(&mExpression)->setInfix(pExpressionWidget->getExpression()) &&
          const_cast< CExpression * >(&mExpression)->compile())
        {
          QString Input = (*mpContainer.*mRetrieve)();
          return CQValidator< QTextEdit >::validate(input, pos);
        }
    }

  setColor(Invalid);
  return Intermediate;
}

/**
  * Function to get CExpression object
  */
CExpression *CQValidatorExpression::getExpression()
{
  return &mExpression;
}

void CQValidatorExpression::setBooleanRequired(bool booleanRequired)
{
  mExpression.setBooleanRequired(booleanRequired);
}

//***********************************************************************

CQValidatorFunction::CQValidatorFunction(QTextEdit * parent, const char * name):
    CQValidator< QTextEdit >(parent, &QTextEdit::text, name),
    mFunction()
{
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  mFunction.setObjectParent(pDataModel);
}

/**
  *  This function ensures that any characters on Expression Widget are validated
  *  to go to further processes.
  */
QValidator::State CQValidatorFunction::validate(QString & input, int & pos) const
{
  // The input is the display version of the infix string.
  // We must first convert the display string to infix.

  State CurrentState = Invalid;

  CQExpressionWidget * pExpressionWidget =
    static_cast< CQExpressionWidget * >(parent());

  if (pExpressionWidget != NULL)
    {
      if (const_cast< CFunction * >(&mFunction)->setInfix(pExpressionWidget->getExpression()) &&
          const_cast< CFunction * >(&mFunction)->compile())
        {
          QString Input = (*mpContainer.*mRetrieve)();
          CurrentState = CQValidator< QTextEdit >::validate(input, pos);
        }
    }

  if (CurrentState != Acceptable)
    {
      setColor(Invalid);
      CurrentState = Intermediate;
    }

  emit stateChanged(CurrentState == Acceptable);

  return CurrentState;
}

CFunction * CQValidatorFunction::getFunction()
{
  return &mFunction;
}


//***********************************************************************

CQExpressionWidget::CQExpressionWidget(QWidget * parent, const char * name)
    : QTextEdit(parent, name),
    mpValidatorExpression(NULL),
    mpValidatorFunction(NULL),
    mOldPar(0),
    mOldPos(0),
    mObjectClasses(TransientExpression),
    mpCurrentObject(NULL),
    mNewName("")
{
  setTabChangesFocus(true);

  expressionHighlighter = new CQExpressionHighlighter(this);

  int h, s, v;

  mSavedColor = paletteBackgroundColor();
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;

  mChangedColor.setHsv(240, s, v);

  mAnchorPos = -1;
  mOldPos = -1;

  connect(this, SIGNAL(textChanged()),
          this, SLOT(slotTextChanged()));
}

CQExpressionWidget::~CQExpressionWidget()
{}

CQValidator< QTextEdit > * CQExpressionWidget::getValidator()
{
  if (mpValidatorExpression != NULL)
    {
      return mpValidatorExpression;
    }

  return mpValidatorFunction;
}

void CQExpressionWidget::writeMathML(std::ostream & out) const
{
  if (mpValidatorExpression != NULL)
    mpValidatorExpression->getExpression()->writeMathML(out, false, 0);
  else if (mpValidatorFunction != NULL)
    {
      std::vector<std::vector<std::string> > params;
      mpValidatorFunction->getFunction()->createListOfParametersForMathML(params);
      mpValidatorFunction->getFunction()->writeMathML(out, params, true, false, 0);
    }

  return;
}

void CQExpressionWidget::mouseReleaseEvent(QMouseEvent * e)
{
  QTextEdit::mouseReleaseEvent(e);

  mCursor = textCursor();

  if (isInObject(mCursor.selectionStart()))
    {
      // Move the selection start out of the object.
      mCursor.setPosition(mCursor.selectionEnd());
      mCursor.setPosition(textCursor().selectionStart(), QTextCursor::KeepAnchor);

      while (isInObject(mCursor.position()))
        {
          mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
        }

      setTextCursor(mCursor);
    }

  if (isInObject(mCursor.selectionEnd()))
    {
      // Move the selection end out of the object.
      mCursor.setPosition(mCursor.selectionStart());
      mCursor.setPosition(textCursor().selectionEnd(), QTextCursor::KeepAnchor);

      while (isInObject(mCursor.position()))
        {
          mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        }

      setTextCursor(mCursor);
    }
}

void CQExpressionWidget::dropEvent(QDropEvent * e)
{
  QString SelectedText = textCursor().selectedText();

  QTextEdit::dropEvent(e);

  if (isInObject(textCursor().position() - SelectedText.length()))
    {
      mCursor = textCursor();
      // Remove the inserted text.

      mCursor.setPosition(mCursor.position() - SelectedText.length(), QTextCursor::KeepAnchor);
      mCursor.removeSelectedText();

      int CurrentPosition = mCursor.position();

      // Determine the insertion point
      while (isInObject(mCursor.position()))
        {
          mCursor.movePosition(QTextCursor::PreviousCharacter);
        }

      int Left = mCursor.position();
      mCursor.setPosition(CurrentPosition);

      // Determine the insertion point
      while (isInObject(mCursor.position()))
        {
          mCursor.movePosition(QTextCursor::NextCharacter);
        }

      int Right = mCursor.position();

      if (CurrentPosition - Left < Right - CurrentPosition)
        {
          mCursor.setPosition(Left);
        }
      else
        {
          mCursor.setPosition(Right);
        }

      mCursor.insertText(SelectedText);
      setTextCursor(mCursor);
    }
}

void CQExpressionWidget::keyPressEvent(QKeyEvent * e)
{
  bool cursorAdjusted = false;

  if (e == QKeySequence::SelectNextChar)
    {
      mCursor = textCursor();
      mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

      while (isInObject(mCursor.position()))
        {
          mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
          cursorAdjusted = true;
        }

      if (cursorAdjusted)
        {
          mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
          setTextCursor(mCursor);
        }

      QTextEdit::keyPressEvent(e);

      return;
    }

  if (e == QKeySequence::SelectPreviousChar)
    {
      mCursor = textCursor();
      mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);

      while (isInObject(mCursor.position()))
        {
          mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
          cursorAdjusted = true;
        }

      if (cursorAdjusted)
        {
          mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
          setTextCursor(mCursor);
        }

      QTextEdit::keyPressEvent(e);

      return;
    }

  switch (e->key())
    {
      case Qt::Key_Backspace:
        mCursor = textCursor();

        if (mCursor.selectedText().isEmpty())
          {
            mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);

            while (isInObject(mCursor.position()))
              {
                mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
                cursorAdjusted = true;
              }

            if (cursorAdjusted)
              {
                mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                mCursor.deleteChar();
                setTextCursor(mCursor);
              }
          }

        // delete the selected object or just the character
        QTextEdit::keyPressEvent(e);

        return;
        break;

      case Qt::Key_Delete:
        mCursor = textCursor();

        if (mCursor.selectedText().isEmpty())
          {
            mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

            while (isInObject(mCursor.position()))
              {
                mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                cursorAdjusted = true;
              }

            if (cursorAdjusted)
              {
                mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
                mCursor.deleteChar();
                setTextCursor(mCursor);
              }
          }

        // delete the selected object or just the character
        QTextEdit::keyPressEvent(e);

        return;
        break;

      case Qt::Key_Left:
        mCursor = textCursor();

        // We check whether the new position is in an object.
        mCursor.movePosition(QTextCursor::PreviousCharacter);

        while (isInObject(mCursor.position()))
          {
            mCursor.movePosition(QTextCursor::PreviousCharacter);
            cursorAdjusted = true;
          }

        if (cursorAdjusted)
          {
            mCursor.movePosition(QTextCursor::NextCharacter);
            setTextCursor(mCursor);
          }

        QTextEdit::keyPressEvent(e);

        return;
        break;

      case Qt::Key_Right:
        mCursor = textCursor();

        // We check whether the new position is in an object.
        mCursor.movePosition(QTextCursor::NextCharacter);

        while (isInObject(mCursor.position()))
          {
            mCursor.movePosition(QTextCursor::NextCharacter);
            cursorAdjusted = true;
          }

        if (cursorAdjusted)
          {
            mCursor.movePosition(QTextCursor::PreviousCharacter);
            setTextCursor(mCursor);
          }

        QTextEdit::keyPressEvent(e);

        return;
        break;

      case Qt::Key_BraceLeft:
      case Qt::Key_BraceRight:
        e->ignore();
        return;
        break;
    }

  if (!e->text().isEmpty())
    {
      // set format original
      QTextCharFormat f;
      f.setForeground(QColor(0, 0, 0));

      setCurrentCharFormat(f);
      QTextEdit::keyPressEvent(e);

      return;
    }

  QTextEdit::keyPressEvent(e);
}

/**
  *  This slot checks any characters that are newly typed on Expression Widget.
  */
void CQExpressionWidget::slotTextChanged()
{
  CQValidator< QTextEdit > * pValidator = NULL;

  if (mpValidatorExpression != NULL)
    pValidator = mpValidatorExpression;
  else if (mpValidatorFunction != NULL)
    pValidator = mpValidatorFunction;
  else
    return;

  int pos = 0;
  QString Input = text();
  setPaletteBackgroundColor(QColor(255, 0, 0));

  emit valid(pValidator->validate(Input, pos) == QValidator::Acceptable);
}

bool CQExpressionWidget::isInObject(int curPos)
{
  static QRegExp COPASIObjectPattern("\\{([^\\}]|\\.)*\\}");

  int Index = COPASIObjectPattern.indexIn(text());

  int Left = -1;
  int Right = -1;

  while (0 <= Index && Index <= curPos)
    {
      Left = Index;
      Index += COPASIObjectPattern.matchedLength();
      Right = Index;

      if (Left < curPos && curPos < Right)
        {
          return true;
        }

      Index = COPASIObjectPattern.indexIn(text(), Index);
    }

  return false;
}

void CQExpressionWidget::setFunction(const std::string & function)
{
  if (mpValidatorFunction == NULL)
    {
      mpValidatorFunction = new CQValidatorFunction(this, "");
      mpValidatorFunction->revalidate();
    }

  // clear the text edit
  clear();

  mCursor = textCursor();

  QTextCharFormat f1;
  f1.setForeground(QColor(0, 0, 0));

  setCurrentCharFormat(f1);
  insertPlainText(FROM_UTF8(function));
}

std::string CQExpressionWidget::getFunction() const
{
  return TO_UTF8(text());
}


void CQExpressionWidget::setExpression(const std::string & expression)
{
  if (mpValidatorExpression == NULL)
    {
      mpValidatorExpression = new CQValidatorExpression(this, "");
      mpValidatorExpression->revalidate();
    }

  // Reset the parse list.
  mParseList.clear();

  // clear the text edit
  clear();

  mCursor = textCursor();

  CFunctionDB* pFunDB = CCopasiRootContainer::getFunctionList();
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  std::vector<CCopasiContainer*> containers;
  containers.push_back(pDataModel);
  containers.push_back(pFunDB);

  std::string Expression = expression;
  std::string out_str = "";

  unsigned C_INT32 i = 0;

  QTextCharFormat f1;
  f1.setForeground(QColor(0, 0, 0));

  QTextCharFormat f = expressionHighlighter->COPASIObjectFormat;
  QColor color2 = f.foreground().color();

  setCurrentCharFormat(f1);

  while (i < Expression.length())
    {
      if (Expression[i] == '<')
        {
          i++;
          std::string objectName = "";

          while (Expression[i] != '>' && i < Expression.length())
            {
              if (Expression[i] == '\\')
                objectName += Expression[i++];

              objectName += Expression[i];
              i++;
            }

          CCopasiObjectName temp_CN(objectName);
          CCopasiObject* temp_object = pDataModel->ObjectFromName(containers, temp_CN);

          if (temp_object != NULL)
            {
              std::string DisplayName = temp_object->getObjectDisplayName();
              mParseList[DisplayName] = temp_object;

              // We need to escape }
              std::string::size_type pos = DisplayName.find_first_of("}");

              while (pos != std::string::npos)
                {
                  DisplayName.insert(pos, "\\");
                  pos += 2;
                  pos = DisplayName.find_first_of("}", pos);
                }

              setCurrentCharFormat(f);
              insertPlainText(FROM_UTF8("{" + DisplayName + "}"));
              setCurrentCharFormat(f1);
            }

          continue;
        }

      else if (Expression[i] == '>')
        {
          //do nothing
        }

      else
        {
          out_str = Expression[i];
          insertPlainText(FROM_UTF8(out_str));
        }

      i++;
    }

  setCurrentCharFormat(f);

  mpValidatorExpression->saved();

  return;
}

std::string CQExpressionWidget::getExpression() const
{
  std::string DisplayName = "";
  std::string InfixCN = "";

  std::string InfixDispayName = TO_UTF8(text());
  std::map< std::string, const CCopasiObject *>::const_iterator it;

  unsigned int i;

  for (i = 0; i < InfixDispayName.length(); i++)
    {
      if (InfixDispayName[i] == '{')
        {
          InfixCN += "<";

          i++;
          DisplayName = "";

          while (i < InfixDispayName.length() && InfixDispayName[i] != '}')
            {
              if (InfixDispayName[i] == '\\') // '\' is an escape character.
                i++;

              DisplayName += InfixDispayName[i++];
            }

          it = mParseList.find(DisplayName);

          if (it != mParseList.end())
            InfixCN += it->second->getCN() + ">";
          else
            InfixCN = InfixCN.substr(0, InfixCN.length() - 1);
        }
      else
        {
          InfixCN += InfixDispayName[i];
        }
    }

  return InfixCN;
}

void CQExpressionWidget::setExpressionType(const CQExpressionWidget::ExpressionType & expressionType)
{
  mObjectClasses = expressionType;
}

void CQExpressionWidget::setBoolean(bool isBoolean)
{
  if (mpValidatorExpression == NULL)
    {
      mpValidatorExpression = new CQValidatorExpression(this, "");
      mpValidatorExpression->revalidate();
    }

  mpValidatorExpression->setBooleanRequired(isBoolean);
};

bool CQExpressionWidget::isValid()
{
  if (mpValidatorExpression != NULL)
    return mpValidatorExpression->revalidate() == QValidator::Acceptable;
  else if (mpValidatorFunction != NULL)
    return mpValidatorFunction->revalidate() == QValidator::Acceptable;

  return true;
}

void CQExpressionWidget::slotSelectObject()
{
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, mObjectClasses);

  if (pObject)
    {
      // Check whether the object is valid
      if (!CCopasiSimpleSelectionTree::filter(mObjectClasses, pObject))
        {
          CQMessageBox::critical(this, "Invalid Selection",
                                 "The use of the selected object is not allowed in this type of expression.");
          return;
        }

      std::string Insert = pObject->getObjectDisplayName();
      mParseList[Insert] = pObject;

      // We need to escape >
      std::string::size_type pos = Insert.find_first_of("}");

      while (pos != std::string::npos)
        {
          Insert.insert(pos, "\\");
          pos += 2;
          pos = Insert.find_first_of("}", pos);
        }

      QTextCharFormat f1;
      f1.setForeground(QColor(0, 0, 0));

      QTextCharFormat f = expressionHighlighter->COPASIObjectFormat;
      QColor color2 = f.foreground().color();

      setCurrentCharFormat(f);
      insertPlainText(FROM_UTF8("{" + Insert + "}"));
      setCurrentCharFormat(f1);
    }
}
