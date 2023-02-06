// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include <iostream>

#include <QLabel>
#include <QComboBox>
//Added by qt3to4:
#include <QKeyEvent>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <QGuiApplication>
#else
#include <QApplication>
#endif
#include <QPalette>

#include "CQExpressionWidget.h"
#include "CQMessageBox.h"
#include "CCopasiSelectionDialog.h"
#include "qtUtilities.h"
#include "listviews.h"

#include "copasi/copasi.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CMassAction.h"
#include "copasi/core/CDataArray.h"
#include "copasi/model/CModel.h"
#include "CQMatrixDialog.h"
#include "qtUtilities.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/utilities/CExpressionGenerator.h"

#define DEBUG_UI

#ifdef DEBUG_UI
std::ostream & operator<<(std::ostream & os, const QTextCursor & d)
{
  os << "Position:        " << d.position() << std::endl;
  os << "Selection Start: " << d.selectionStart() << std::endl;
  os << "Selection End:   " << d.selectionEnd() << std::endl;
  os << "Anchor:          " << d.anchor() << std::endl;
  os << "Selected Text:   " << TO_UTF8(d.selectedText()) << std::endl;
  return os;
}
#endif // DEBUG_UI

CQExpressionHighlighter::CQExpressionHighlighter(CQExpressionWidget * ew)
  : QSyntaxHighlighter(ew)
  , mObjectDisplayPattern(CQExpressionWidget::DisplayPattern)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  QColor Foreground = Palette.color(QPalette::Active, QPalette::WindowText);
  QColor Background = Palette.color(QPalette::Active, QPalette::Window);

  if (Foreground.redF() + Foreground.greenF() + Foreground.blueF() < Background.redF() + Background.greenF() + Background.blueF())
    {
      mObjectDisplayFormat.setForeground(QColor(154, 58, 33));
    }
  else
    {
      mObjectDisplayFormat.setForeground(QColor(81, 144, 145));
    }
}

CQExpressionHighlighter::~CQExpressionHighlighter()
{}

void CQExpressionHighlighter::highlightBlock(const QString & text)
{
  int index = mObjectDisplayPattern.indexIn(text);

  while (index >= 0)
    {
      int length = mObjectDisplayPattern.matchedLength();
      setFormat(index, length, mObjectDisplayFormat);
      index = mObjectDisplayPattern.indexIn(text, index + length);
    }
}

//***********************************************************************

CQValidatorExpression::CQValidatorExpression(QTextEdit * parent, const char * name, bool isBoolean)
  : CQValidator< QTextEdit >(parent, &QTextEdit::toPlainText, name)
  , mExpression()
{
  CDataModel * pDataModel = ListViews::dataModel(parent);
  assert(pDataModel != NULL);
  mExpression.setObjectParent(pDataModel);
  mExpression.setIsBoolean(isBoolean);
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
    dynamic_cast< CQExpressionWidget * >(parent());

  if (pExpressionWidget != NULL)
    {
      if (const_cast< CExpression * >(&mExpression)->setInfix(pExpressionWidget->getExpression())
          && const_cast< CExpression * >(&mExpression)->compile())
        {
          return CQValidator< QTextEdit >::validate(input, pos);
        }
    }

  setColor(Invalid);
  return Intermediate;
}

/**
  * Function to get CExpression object
  */
CExpression * CQValidatorExpression::getExpression()
{
  return &mExpression;
}

void CQValidatorExpression::setBooleanRequired(bool booleanRequired)
{
  mExpression.setIsBoolean(booleanRequired);
}

//***********************************************************************

CQValidatorFunction::CQValidatorFunction(QTextEdit * parent, const char * name)
  : CQValidator< QTextEdit >(parent, &QTextEdit::toPlainText, name)
  , mFunction()
{
  CDataModel * pDataModel = ListViews::dataModel(parent);
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
    dynamic_cast< CQExpressionWidget * >(parent());

  if (pExpressionWidget != NULL)
    {
      std::string Infix = pExpressionWidget->getFunction();

      if (Infix == CMassAction::Infix[0]
          || Infix == CMassAction::Infix[1]
          || (const_cast< CFunction * >(&mFunction)->setInfix(Infix)
              && const_cast< CFunction * >(&mFunction)->compile()))
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

// static
const char CQExpressionWidget::InfixPattern[] = "<(CN=([^\\\\>]|\\\\.)*)>";

// static
const char CQExpressionWidget::DisplayPattern[] = "\\{(([^\\\\\\}]|\\\\.)*)\\}";

CQExpressionWidget::CQExpressionWidget(QWidget * parent, const char * name)
  : QTextEdit(parent)
  , mpValidatorExpression(NULL)
  , mpValidatorFunction(NULL)
  , mObjectClasses(TransientExpression)
  , mpCurrentObject(NULL)
  , mSavedColor()
  , mChangedColor()
  , mText()
  , mCursor()
  , mpExpressionHighlighter(NULL)

{
  setObjectName(QString::fromUtf8(name));
  setTabChangesFocus(true);
  mpExpressionHighlighter = new CQExpressionHighlighter(this);
  int h, s, v;

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  mText = Palette.color(QPalette::Active, QPalette::Text);
  mSavedColor = Palette.color(QPalette::Active, QPalette::Base);
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20)
    s = 20;

  mChangedColor.setHsv(240, s, v);

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
      std::string Infix = getFunction();

      if (Infix == CMassAction::Infix[0])
        {
          CMassAction Function(TriTrue, NULL);
          std::vector< std::vector< std::string > > params;
          Function.createListOfParametersForMathML(params);
          out << Function.writeMathML(params, true, false);
        }
      else if (Infix == CMassAction::Infix[1])
        {
          CMassAction Function(TriFalse, NULL);
          std::vector< std::vector< std::string > > params;
          Function.createListOfParametersForMathML(params);
          out << Function.writeMathML(params, true, false);
        }
      else
        {
          std::vector< std::vector< std::string > > params;
          mpValidatorFunction->getFunction()->createListOfParametersForMathML(params);
          out << mpValidatorFunction->getFunction()->writeMathML(params, true, false);
        }
    }

  return;
}

void CQExpressionWidget::mouseReleaseEvent(QMouseEvent * e)
{
  QTextEdit::mouseReleaseEvent(e);
  mCursor = textCursor();
  int Left;
  int Right;

  if (objectBoundaries(mCursor.selectionStart(), Left, Right))
    {
      // Move the selection start out of the object.
      mCursor.setPosition(mCursor.selectionEnd());
      mCursor.setPosition(Left, QTextCursor::KeepAnchor);
      setTextCursor(mCursor);
    }

  if (objectBoundaries(mCursor.selectionEnd(), Left, Right))
    {
      // Move the selection end out of the object.
      mCursor.setPosition(mCursor.selectionStart());
      mCursor.setPosition(Right, QTextCursor::KeepAnchor);
      setTextCursor(mCursor);
    }
}

void CQExpressionWidget::dropEvent(QDropEvent * e)
{
  QString SelectedText = textCursor().selectedText();
  QTextEdit::dropEvent(e);
  int Left;
  int Right;

  if (objectBoundaries(textCursor().position() - SelectedText.length(), Left, Right))
    {
      mCursor = textCursor();
      // Remove the inserted text.
      mCursor.setPosition(mCursor.position() - SelectedText.length(), QTextCursor::KeepAnchor);
      mCursor.removeSelectedText();
      int CurrentPosition = mCursor.position();
      // Determine the insertion point
      objectBoundaries(mCursor.position(), Left, Right);

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
  int Left;
  int Right;
  bool isAdvancedEditing = CRootContainer::getConfiguration()->useAdvancedEditing();

  if (e == QKeySequence::SelectNextChar && !isAdvancedEditing)
    {
      mCursor = textCursor();
      mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

      if (objectBoundaries(mCursor.position(), Left, Right))
        {
          mCursor.setPosition(Right - 1, QTextCursor::KeepAnchor);
          setTextCursor(mCursor);
        }

      QTextEdit::keyPressEvent(e);
      return;
    }

  if (e == QKeySequence::SelectPreviousChar && !isAdvancedEditing)
    {
      mCursor = textCursor();
      mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);

      if (objectBoundaries(mCursor.position(), Left, Right))
        {
          mCursor.setPosition(Left + 1, QTextCursor::KeepAnchor);
          setTextCursor(mCursor);
        }

      QTextEdit::keyPressEvent(e);
      return;
    }

  switch (e->key())
    {
      case Qt::Key_Backspace:
        if (isAdvancedEditing)
          break;

        mCursor = textCursor();

        if (mCursor.selectedText().isEmpty())
          {
            mCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);

            if (objectBoundaries(mCursor.position(), Left, Right))
              {
                mCursor.setPosition(Left + 1, QTextCursor::KeepAnchor);
                mCursor.deleteChar();
                setTextCursor(mCursor);
              }
          }

        // delete the selected object or just the character
        QTextEdit::keyPressEvent(e);
        return;
        break;

      case Qt::Key_Delete:
        if (isAdvancedEditing)
          break;

        mCursor = textCursor();

        if (mCursor.selectedText().isEmpty())
          {
            mCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

            if (objectBoundaries(mCursor.position(), Left, Right))
              {
                mCursor.setPosition(Right - 1, QTextCursor::KeepAnchor);
                mCursor.deleteChar();
                setTextCursor(mCursor);
              }
          }

        // delete the selected object or just the character
        QTextEdit::keyPressEvent(e);
        return;
        break;

      case Qt::Key_Left:
        if (isAdvancedEditing)
          break;

        mCursor = textCursor();
        // We check whether the new position is in an object.
        mCursor.movePosition(QTextCursor::PreviousCharacter);

        if (objectBoundaries(mCursor.position(), Left, Right))
          {
            mCursor.setPosition(Left + 1, QTextCursor::KeepAnchor);
            setTextCursor(mCursor);
          }

        QTextEdit::keyPressEvent(e);
        return;
        break;

      case Qt::Key_Right:
        if (isAdvancedEditing)
          break;

        mCursor = textCursor();
        // We check whether the new position is in an object.
        mCursor.movePosition(QTextCursor::NextCharacter);

        if (objectBoundaries(mCursor.position(), Left, Right))
          {
            mCursor.setPosition(Right - 1, QTextCursor::KeepAnchor);
            setTextCursor(mCursor);
          }

        QTextEdit::keyPressEvent(e);
        return;
        break;

      case Qt::Key_BraceLeft:
      case Qt::Key_BraceRight:
        if (isAdvancedEditing)
          break;

        e->ignore();
        return;
        break;
    }

  if (!e->text().isEmpty())
    {
      // set format original
      QTextCharFormat f;
      f.setForeground(mText);
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
  QString Input = toPlainText();
  emit valid(pValidator->validate(Input, pos) == QValidator::Acceptable);
}

bool CQExpressionWidget::objectBoundaries(const int & position, int & left, int & right) const
{
  static QRegExp ObjectDisplayPattern(CQExpressionWidget::DisplayPattern);
  int Index = ObjectDisplayPattern.indexIn(toPlainText());

  while (0 <= Index && Index <= position)
    {
      left = Index;
      Index += ObjectDisplayPattern.matchedLength();
      right = Index;

      if (left < position && position < right)
        {
          return true;
        }

      Index = ObjectDisplayPattern.indexIn(toPlainText(), Index);
    }

  left = -1;
  right = -1;
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
  f1.setForeground(mText);
  setCurrentCharFormat(f1);
  insertPlainText(FROM_UTF8(function));
}

std::string CQExpressionWidget::getFunction() const
{
  return TO_UTF8(toPlainText());
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
  mCursor = textCursor();
  CFunctionDB * pFunDB = CRootContainer::getFunctionList();
  CDataModel * pDataModel = ListViews::dataModel(parent());
  assert(pDataModel != NULL);
  CObjectInterface::ContainerList containers;
  containers.push_back(pDataModel);
  containers.push_back(pFunDB);
  const QString Infix(FROM_UTF8(expression));
  QString Display;
  QRegExp InfixObjectPattern(CQExpressionWidget::InfixPattern);
  int Index = 0;
  QString::const_iterator it = Infix.begin();
  QString::const_iterator end;

  while (true)
    {
      Index = InfixObjectPattern.indexIn(Infix, Index);

      if (Index < 0)
        {
          end = Infix.end();
        }
      else
        {
          end = Infix.begin() + Index;
        }

      // Copy the non-object part
      for (; it != end; ++it)
        {
          Display.append(*it);
        }

      if (InfixObjectPattern.matchedLength() < 0)
        break;

      Index += InfixObjectPattern.matchedLength();
      it += InfixObjectPattern.matchedLength();
      CCommonName InfixName(TO_UTF8(InfixObjectPattern.cap(1)));
      const CDataObject * pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(containers, InfixName));

      if (pObject != NULL)
        {
          std::string DisplayName = pObject->getObjectDisplayName();
          // We need to escape '\' and '}'
          std::string::size_type pos = DisplayName.find_first_of("\\}");

          while (pos != std::string::npos)
            {
              DisplayName.insert(pos, "\\");
              pos += 2;
              pos = DisplayName.find_first_of("\\}", pos);
            }

          mParseList[DisplayName] = pObject;
          Display += '{' + FROM_UTF8(DisplayName) + '}';
        }
      else
        {
          std::string DisplayName = InfixName;
          // We need to escape '\' and '}'
          std::string::size_type pos = DisplayName.find_first_of("\\}");

          while (pos != std::string::npos)
            {
              DisplayName.insert(pos, "\\");
              pos += 2;
              pos = DisplayName.find_first_of("\\}", pos);
            }

          Display += '{' + FROM_UTF8(DisplayName) + '}';
        }
    }

  setText(Display);
  mpValidatorExpression->saved();
  return;
}

std::string CQExpressionWidget::getExpression() const
{
  QString Infix;
  const QString Display(toPlainText());
  QRegExp DisplayObjectPattern(CQExpressionWidget::DisplayPattern);
  int Index = 0;
  QString::const_iterator it = Display.begin();
  QString::const_iterator end;

  while (true)
    {
      Index = DisplayObjectPattern.indexIn(Display, Index);

      if (Index < 0)
        {
          end = Display.end();
        }
      else
        {
          end = Display.begin() + Index;
        }

      // Copy the non-object part
      for (; it != end; ++it)
        {
          Infix.append(*it);
        }

      if (DisplayObjectPattern.matchedLength() < 0)
        break;

      Index += DisplayObjectPattern.matchedLength();
      it += DisplayObjectPattern.matchedLength();
      std::string DisplayName(TO_UTF8(DisplayObjectPattern.cap(1)));
      std::map< std::string, const CDataObject * >::const_iterator itObject = mParseList.find(DisplayName);

      if (itObject == mParseList.end()
          && CRootContainer::getConfiguration()->useAdvancedEditing())
        {
          // the object pattern does not match the species name if
          // the species is in a different compartment, in that case we
          // have to remove the backslash in the displayname.
          std::string::size_type bsPos = DisplayName.find("\\}");

          if (bsPos != std::string::npos)
            DisplayName.erase(bsPos, 1);

          // here we don't have an object recognized, what we ought to do is to find it in the model
          CDataModel * pDataModel = ListViews::dataModel(parent());

          if (mpCurrentObject != NULL)
            pDataModel = mpCurrentObject->getObjectDataModel();

          const CDataObject * object = pDataModel->findObjectByDisplayName(DisplayName);

          if (object != NULL)
            {
              const_cast< CQExpressionWidget * >(this)->mParseList[DisplayName] = object;
              itObject = mParseList.find(DisplayName);
            }
        }

      if (itObject != mParseList.end())
        Infix += "<" + FROM_UTF8(itObject->second->getCN()) + ">";
      else
        {
          Infix += "<";
          // We need to escape '\'
          std::string CN = TO_UTF8(DisplayObjectPattern.cap(1));
          std::string::const_iterator it = CN.begin();
          std::string::const_iterator end = CN.end();

          for (; it < end; ++it)
            {
              if (*it == '\\')
                {
                  ++it;
                }

              Infix += *it;
            }

          Infix += ">";
        }
    }

  return TO_UTF8(Infix);
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
  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, mObjectClasses, NULL, true);

  if (pObject)
    {
      auto* pExpressionGenerator = dynamic_cast< const CExpressionGenerator * >(pObject);

      if (pExpressionGenerator)
        {
          CDataModel * pDataModel = ListViews::dataModel(parent());
          insertPlainText(FROM_UTF8(pExpressionGenerator->generateExpressionFor(pDataModel->getModel())));
          delete const_cast< CExpressionGenerator * >(pExpressionGenerator);
          return;
        }

      // Check whether the object is valid
      if (!CQSimpleSelectionTree::filter(mObjectClasses, pObject))
        {
          CQMessageBox::critical(this, "Invalid Selection",
                                 "The use of the selected object is not allowed in this type of expression.");
          return;
        }

      std::string Insert = pObject->getObjectDisplayName();
      // We need to escape >
      std::string::size_type pos = Insert.find_first_of("}");

      while (pos != std::string::npos)
        {
          Insert.insert(pos, "\\");
          pos += 2;
          pos = Insert.find_first_of("}", pos);
        }

      mParseList[Insert] = pObject;
      QTextCharFormat f1;
      f1.setForeground(mText);
      QTextCharFormat f = mpExpressionHighlighter->mObjectDisplayFormat;
      //QColor color2 = f.foreground().color();
      setCurrentCharFormat(f);
      insertPlainText(FROM_UTF8("{" + Insert + "}"));
      setCurrentCharFormat(f1);
    }
}
