// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpressionWidget.cpp,v $
//   $Revision: 1.47 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/09/30 21:20:10 $
// End CVS Header

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

#include <QtDebug>

CQExpressionHighlighter::CQExpressionHighlighter(CQExpressionWidget* ew)
    : QSyntaxHighlighter(ew)
{
  // COPASI object format
  COPASIObjectFormat.setForeground(QColor(100, 0, 200));
  COPASIObjectPattern = QRegExp("<[^<]*>");
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
    CQValidator< QTextEdit >(parent, name),
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
          QString Input = mpLineEdit->text();
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

//***********************************************************************

CQExpressionWidget::CQExpressionWidget(QWidget * parent, const char * name, bool isBoolean)
    : QTextEdit(parent, name),
    mpValidator(NULL),
    mOldPar(0),
    mOldPos(0),
    mObjectClasses(TransientExpression),
    mpCurrentObject(NULL),
    mNewName("")
{
#ifdef DEBUG_UI
  qDebug() << "in constructor CQEW";
#endif

  setTabChangesFocus(true);

  expressionHighlighter = new CQExpressionHighlighter(this);

  int h, s, v;

  mSavedColor = paletteBackgroundColor();
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;

  mChangedColor.setHsv(240, s, v);

  mpValidator = new CQValidatorExpression(this, "", isBoolean);
  mpValidator->revalidate();

  mAnchorPos = -1;
  mOldPos = -1;

  connect(this, SIGNAL(cursorPositionChanged()),
          this, SLOT(slotCursorPositionChanged()));
  connect(this, SIGNAL(selectionChanged()),
          this, SLOT(slotSelectionChanged()));
  connect(this, SIGNAL(textChanged()),
          this, SLOT(slotTextChanged()));

  mCursor = textCursor();
}

CQExpressionWidget::~CQExpressionWidget()
{}

void CQExpressionWidget::mousePressEvent(QMouseEvent * e)
{
#ifdef DEBUG_UI
  qDebug() << "- CQExpressionWidget::mousePressEvent - ";

  QTextCursor tc = cursorForPosition(e->pos());

  mCursor.setPosition(tc.position());

  qDebug() << "Cursor position on mousePressEvent of mCursor = " << mCursor.position();
  qDebug() << "Cursor position on mousePressEvent of tc = " << tc.position();
#endif

  eMove = CQExpressionWidget::Mouse;

  QTextEdit::mousePressEvent(e);

  mCursor.setPosition(cursorForPosition(e->pos()).position());
#ifdef DEBUG_UI
  qDebug() << "Updated Cursor position on mousePressEvent = " << mCursor.position();
#endif
}

void CQExpressionWidget::keyPressEvent(QKeyEvent * e)
{
#ifdef DEBUG_UI
  qDebug() << "- CQExpressionWidget::keyPressEvent - ";
#endif

  // in case of clicking Return/Enter key
  if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
    {
#ifdef DEBUG_UI
      qDebug() << "R E T U R N / E N T E R is just typed --> not allowed";
#endif
      return;
    }

  // in case of deleting character by backspace
  if (e->key() == Qt::Key_Backspace)
    {
#ifdef DEBUG_UI
      qDebug() << "B A C K S P A C E is just typed";

      qDebug() << "selectedText = " << mCursor.selectedText();
#endif

      if (mCursor.selectedText().isEmpty())
        {
          mCursor.setPosition(textCursor().position());
#ifdef DEBUG_UI
          qDebug() << "position = " << mCursor.position();
#endif
          mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
#ifdef DEBUG_UI
          qDebug() << "selectedText = " << mCursor.selectedText();
          qDebug() << "position = " << mCursor.position();
#endif

          if (mCursor.selectedText() == ">")
            {
              // select the whole object
              QTextDocument *doc = document();
              QTextCursor cursor = doc->find("<", mCursor, QTextDocument::FindBackward);
#ifdef DEBUG_UI
              qDebug() << "------> cursor.position of '<' = " << cursor.position();
              qDebug() << "selectedText = " << cursor.selectedText();
#endif
              mCursor.setPosition(cursor.position() - 1, QTextCursor::KeepAnchor);
            }
        }

      // delete the selected object one or just the character
      mCursor.deleteChar();

      return;
    }

  // in case of deleting character by delete
  if (e->key() == Qt::Key_Delete)
    {
#ifdef DEBUG_UI
      qDebug() << "D E L E T E is just typed";
      qDebug() << "selectedText = " << mCursor.selectedText();
#endif

      if (mCursor.selectedText().isEmpty())
        {
          mCursor.setPosition(textCursor().position());
#ifdef DEBUG_UI
          qDebug() << "position = " << mCursor.position();
#endif
          mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
#ifdef DEBUG_UI
          qDebug() << "selectedText = " << mCursor.selectedText();
          qDebug() << "position = " << mCursor.position();
#endif

          if (mCursor.selectedText() == "<")
            {
              // select the whole object
              QTextDocument *doc = document();
              QTextCursor cursor = doc->find(">", mCursor);
#ifdef DEBUG_UI
              qDebug() << "------> cursor.position of '>' = " << cursor.position();
              qDebug() << "selectedText = " << cursor.selectedText();
#endif
              mCursor.setPosition(cursor.position(), QTextCursor::KeepAnchor);
            }
        }

      // delete the selected object one or just the character
      mCursor.deleteChar();

      return;
    }

#ifdef DEBUG_UI
  qDebug() << "e->text() = " << e->text();
#endif

  if (e->key() == Qt::Key_Shift)
    {
#ifdef DEBUG_UI
      qDebug() << "S H I F T is just pressed";
#endif
    }

  if (e == QKeySequence::SelectNextChar)
    {
#ifdef DEBUG_UI
      qDebug() << "SelectNextChar is just pressed";
#endif
      eAction = CQExpressionWidget::SelectToRight;

#ifdef DEBUG_UI
      QTextCursor tc = textCursor();
      qDebug() << "Cursor position = " << tc.position();

      qDebug() << "Updated Cursor position = " << mCursor.position();

      qDebug() << "selection start = " << mCursor.selectionStart();
      qDebug() << "selection end = " << mCursor.selectionEnd();
      qDebug() << "Cursor position = " << mCursor.position();
      qDebug() << "selectedText = " << mCursor.selectedText();

      qDebug() << "-x-x-x-x-x-";
#endif
    }

  else if (e == QKeySequence::SelectPreviousChar)
    {
#ifdef DEBUG_UI
      qDebug() << "SelectPreviousChar is just pressed";
#endif
      eAction = CQExpressionWidget::SelectToLeft;
    }

  else if (e->key() == Qt::Key_Left || e->key() == Qt::Key_Right)
    {
#ifdef DEBUG_UI
      qDebug() << "M O V I N G";
#endif
      int currentCursorPosition = mCursor.position();
#ifdef DEBUG_UI
      qDebug() << "Cursor position = " << currentCursorPosition;
#endif

      // in case of moving cursor one character to left
      if (e->key() == Qt::Key_Left)
        {
#ifdef DEBUG_UI
          qDebug() << "L E F T is just typed";
#endif
          eMove = CQExpressionWidget::Left;
        }

      // in case of moving cursor one character to right
      if (e->key() == Qt::Key_Right)
        {
#ifdef DEBUG_UI
          qDebug() << "R I G H T is just typed";
#endif
          eMove = CQExpressionWidget::Right;
        }

      setTextCursor(mCursor);
    }
  else
    {
      if (!e->text().isEmpty())
        {
          // in case of typing a character
          // filter "<" and ">" - these characters are not allowed to manually type
#ifdef DEBUG_UI
          qDebug() << "T Y P I N G";
#endif

          if (e->text() == "<") return;

          if (e->text() == ">") return;

          // set format original
          QTextCharFormat f;
          f.setForeground(QColor(0, 0, 0));

          setCurrentCharFormat(f);
        }
    }

#ifdef DEBUG_UI
  QColor color = textColor();
  qDebug() << "clor text: red = " << color.red() << " - green = " << color.green() << " - blue = " << color.blue();
#endif

  // This will lead to emitting signal cursorPositionChanged()
  QTextEdit::keyPressEvent(e);

  if (e == QKeySequence::Undo)
    {
#ifdef DEBUG_UI
      qDebug() << "U N D O is just pressed";
#endif

      // update cursor position, especially useful for undo/redo action
      mCursor.setPosition(textCursor().position());
#ifdef DEBUG_UI
      qDebug() << "Updated Cursor position = " << mCursor.position();
#endif
    }
}

void CQExpressionWidget::slotSelectionChanged()
{
#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEW text() = " << text();
  qDebug() << "- on CQExpressionWidget::slotSelectionChanged - ";

  QTextCursor tc = textCursor();
  int currentCursorPosition = tc.position();
  qDebug() << "Cursor position = " << currentCursorPosition;
#endif

  mCursor =  textCursor();
#ifdef DEBUG_UI
  qDebug() << "selection start = " << mCursor.selectionStart();
  qDebug() << "selection end = " << mCursor.selectionEnd();
  qDebug() << "Cursor position = " << mCursor.position();
  qDebug() << "selectedText = " << mCursor.selectedText();
  qDebug() << "anchr pos = " << mCursor.anchor();
#endif

  int startPos = mCursor.selectionStart();
  int endPos = mCursor.selectionEnd();
  int curPos = mCursor.position();  // it can be startPos or endPos

  QTextDocument *dc = document();
  QChar ch = dc->characterAt(curPos);
#ifdef DEBUG_UI
  qDebug() << "*** last character = " << ch;
#endif

  if (isInObject(curPos))
    {
      // current cursor position, either startPos or endPos, is in object
#ifdef DEBUG_UI
      qDebug() << "-x- in object -x-";
#endif

      QTextDocument *doc = document();

      if (curPos == startPos)
        {
          // selection is done from right to left, ie. endPos is fix.
          QChar ch = doc->characterAt(curPos);
#ifdef DEBUG_UI
          qDebug() << "last character = " << ch;
#endif

          if (ch == '>')
            {
              // this is the first character of object will be met in such a selection way
              QTextCursor cursor1 = doc->find("<", curPos, QTextDocument::FindBackward);
#ifdef DEBUG_UI
              qDebug() << "------> cursor.position of '<' = " << cursor1.position();
#endif
              // '-1' because the cursor should be before character '<'
              mOldPos = cursor1.position() - 1;
            }
        }

      if (curPos == endPos)
        {
          // selection is done from left to right, ie. startPos is fix.
          QChar ch = doc->characterAt(curPos - 1);
#ifdef DEBUG_UI
          qDebug() << "last character = " << ch;
#endif

          if (ch == '<')
            {
              // this is the first character of object will be met in such a selection way
              QTextCursor cursor1 = doc->find(">", curPos);
#ifdef DEBUG_UI
              qDebug() << "------> cursor.position of '>' = " << cursor1.position();
#endif
              // '-1' because the cursor should be before character '<'
              mOldPos = cursor1.position();
            }
        }
    }
  else
    {
      mOldPos = curPos; // just update if cursor is not in object
#ifdef DEBUG_UI
      qDebug() << "-x- out of object -x-";
#endif
    }

  eMove = CQExpressionWidget::None;
#ifdef DEBUG_UI
  qDebug() << "Cursor position on end of slotSelectionChanged = " << mCursor.position();
#endif

  if (eMove == CQExpressionWidget::Mouse)
    mCursor.setPosition(mOldPos, QTextCursor::KeepAnchor);

  if (startPos == endPos) // no selection
    mCursor.setPosition(mOldPos);
  else            // keep selection
    mCursor.setPosition(mOldPos, QTextCursor::KeepAnchor);

  setTextCursor(mCursor);
}

/**
  *  This slot checks any characters that are newly typed on Expression Widget.
  */
void CQExpressionWidget::slotTextChanged()
{
#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEW slotTextChanged => " << toPlainText();

  qDebug() << "position = " << mCursor.position();
  qDebug() << "----------------------------------";
#endif

  int pos = 0;
  QString Input = text();
  setPaletteBackgroundColor(QColor(255, 0, 0));
#ifdef DEBUG_UI
  qDebug() << "bool = " << (mpValidator->validate(Input, pos) == QValidator::Acceptable);
#endif
  emit valid(mpValidator->validate(Input, pos) == QValidator::Acceptable);
}

//void CQExpressionWidget::slotCursorPositionChanged(int para, int pos)
void CQExpressionWidget::slotCursorPositionChanged()
{
#ifdef DEBUG_UI
  qDebug() << "----------------------------------";
  qDebug() << "- Need implementaion on CQExpressionWidget::slotCursorPositionChanged - ";

  qDebug() << "selectedText = " << mCursor.selectedText();

  qDebug() << "----------------------------------";
#endif

  int currentCursorPosition = mCursor.position();
  bool inObject = isInObject(currentCursorPosition - 1); // '-1' means candidate as the cursor is not moved yet

  QTextDocument *doc = document();
  QTextCursor cursor1, cursor2;
#ifdef DEBUG_UI
  qDebug() << "ABC cursor position = " << mCursor.position();
#endif

  if (inObject)
    {
#ifdef DEBUG_UI
      qDebug() << "in O B J E C T";
#endif
      cursor1 = doc->find("<", mCursor.position() + 1, QTextDocument::FindBackward);
#ifdef DEBUG_UI
      qDebug() << "cursor position = " << mCursor.position();
      qDebug() << "------> cursor.position of '<' = " << cursor1.position();
      qDebug() << "selectedText = " << cursor1.selectedText();
#endif
      cursor2 = doc->find(">", mCursor.position());
#ifdef DEBUG_UI
      qDebug() << "cursor position = " << mCursor.position();
      qDebug() << "------> cursor.position of '>' = " << cursor2.position();
      qDebug() << "selectedText = " << cursor2.selectedText();
#endif
    }

#ifdef DEBUG_UI
  else
    qDebug() << "out of O B J E C T";

#endif

  switch (eMove)
    {
      case CQExpressionWidget::Left:
#ifdef DEBUG_UI
        qDebug() << "MOVE TO LEFT";
#endif

        if (inObject)
          mCursor.setPosition(cursor1.position() - 1);
        else
          mCursor.setPosition(currentCursorPosition - 1);

        eMove = CQExpressionWidget::None;
        setTextCursor(mCursor);
        break;
      case CQExpressionWidget::Right:
#ifdef DEBUG_UI
        qDebug() << "MOVE TO RIGHT";
#endif

        if (inObject)
          mCursor.setPosition(cursor2.position());
        else
          mCursor.setPosition(currentCursorPosition + 1);

        eMove = CQExpressionWidget::None;
        setTextCursor(mCursor);
        break;
#ifdef DEBUG_UI
      case CQExpressionWidget::Mouse:
        qDebug() << "MOUSE";
#endif

        if (inObject)
          {
#ifdef DEBUG_UI
            qDebug() << "currentCursorPosition = " << currentCursorPosition;
#endif

            if (currentCursorPosition - cursor1.position() < cursor2.position() - currentCursorPosition)
              mCursor.setPosition(cursor1.position() - 1);
            else
              mCursor.setPosition(cursor2.position());

            setTextCursor(mCursor);
          }

        break;
      default:
        break;
    }

  switch (eAction)
    {
      case CQExpressionWidget::SelectToLeft:
#ifdef DEBUG_UI
        qDebug() << "- Select Previous Character -";
#endif

        if (inObject)
          mCursor.setPosition(cursor1.position() - 1, QTextCursor::KeepAnchor);
        else
          mCursor.setPosition(currentCursorPosition - 1, QTextCursor::KeepAnchor);

        eAction = CQExpressionWidget::NoAction;
        setTextCursor(mCursor);
        break;
      case CQExpressionWidget::SelectToRight:
#ifdef DEBUG_UI
        qDebug() << "- Select Next Character -";
#endif

        if (inObject)
          mCursor.setPosition(cursor2.position(), QTextCursor::KeepAnchor);
        else
          mCursor.setPosition(currentCursorPosition + 1, QTextCursor::KeepAnchor);

        eAction = CQExpressionWidget::NoAction;
        setTextCursor(mCursor);
        break;
      default:
        break;
    }

#ifdef DEBUG_UI
  qDebug() << "------> cursor position now = " << mCursor.position();
#endif
}

bool CQExpressionWidget::isInObject(int curPos)
{
#ifdef DEBUG_UI
  qDebug() << "- on CQExpressionWidget::isInObject - ";
#endif

  QColor color = textColor();
#ifdef DEBUG_UI
  qDebug() << "OOO red text = " << color.red() << " - green = " << color.green() << " - blue = " << color.blue();
#endif

  if (color == QColor(0, 0, 0)) return false;

  QTextDocument *doc = document();

  QChar ch = doc->characterAt(curPos - 1); // previous character
#ifdef DEBUG_UI
  qDebug() << "cursor position = " << curPos;
  qDebug() << "[right] character = " << doc->characterAt(curPos);
  qDebug() << "left character = " << ch;
#endif

  if (ch == '>') return false;

#ifdef DEBUG_UI
  qDebug() << "-- in Object --";
#endif
  return true;
}

void CQExpressionWidget::setExpression(const std::string & expression)
{
  // Reset the parse list.
  mParseList.clear();

  // clear the text edit
  clear();

  std::string Expression = expression;
  std::string out_str = "";

  unsigned C_INT32 i = 0;

  QTextCharFormat f1;
  f1.setForeground(QColor(0, 0, 0));

  QTextCharFormat f = expressionHighlighter->COPASIObjectFormat;
  QColor color2 = f.foreground().color();

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
          CFunctionDB* pFunDB = CCopasiRootContainer::getFunctionList();
          assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
          CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
          assert(pDataModel != NULL);
          std::vector<CCopasiContainer*> containers;
          containers.push_back(pDataModel);
          containers.push_back(pFunDB);
          CCopasiObject* temp_object = pDataModel->ObjectFromName(containers, temp_CN);

          if (temp_object != NULL)
            {
              std::string DisplayName = temp_object->getObjectDisplayName();
              mParseList[DisplayName] = temp_object;

              // We need to escape >
              std::string::size_type pos = DisplayName.find_first_of("\\>");

              while (pos != std::string::npos)
                {
                  DisplayName.insert(pos, "\\");
                  pos += 2;
                  pos = DisplayName.find_first_of("\\>", pos);
                }

              setCurrentCharFormat(f);
              insertPlainText(FROM_UTF8("<" + DisplayName + ">"));
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
          setCurrentCharFormat(f1);
          insertPlainText(FROM_UTF8(out_str));
        }

      i++;
    }

  setCurrentCharFormat(f);

  mpValidator->saved();

#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEW text() = " << text();
#endif

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
      InfixCN += InfixDispayName[i];
      DisplayName = "";

      if (InfixDispayName[i] == '<')
        {
          i++;

          while (i < InfixDispayName.length() && InfixDispayName[i] != '>')
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
    }

#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEW text() = " << text();
#endif

  return InfixCN;
}

void CQExpressionWidget::setExpressionType(const CQExpressionWidget::ExpressionType & expressionType)
{
  mObjectClasses = expressionType;
}

void CQExpressionWidget::setBoolean(bool isBoolean)
{
  mpValidator->setBooleanRequired(isBoolean);
};

bool CQExpressionWidget::isValid()
{
  return mpValidator->revalidate() == QValidator::Acceptable;
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
      std::string::size_type pos = Insert.find_first_of("\\>");

      while (pos != std::string::npos)
        {
          Insert.insert(pos, "\\");
          pos += 2;
          pos = Insert.find_first_of("\\>", pos);
        }

      QTextCharFormat f1;
      f1.setForeground(QColor(0, 0, 0));

      QTextCharFormat f = expressionHighlighter->COPASIObjectFormat;
      QColor color2 = f.foreground().color();
#ifdef DEBUG_UI
      qDebug() << "NEW red = " << color2.red() << " - green = " << color2.green() << " - blue = " << color2.blue();
#endif

      setCurrentCharFormat(f);
      insertPlainText(FROM_UTF8("<" + Insert + ">"));
      setCurrentCharFormat(f1);
    }
}
