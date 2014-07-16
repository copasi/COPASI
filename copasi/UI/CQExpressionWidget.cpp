// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtGui/QLabel>
#include <QtGui/QComboBox>
//Added by qt3to4:
#include <QtGui/QKeyEvent>

#include "CQExpressionWidget.h"
#include "CQMessageBox.h"
#include "CCopasiSelectionDialog.h"
#include "qtUtilities.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CExpression.h"
#include "function/CFunctionDB.h"
#include "function/CMassAction.h"
#include "utilities/CAnnotatedMatrix.h"
#include "model/CModel.h"
#include "CQMatrixDialog.h"
#include "qtUtilities.h"
#include "report/CCopasiRootContainer.h"
#include "commandline/CConfigurationFile.h"

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
    mObjectDisplayPattern(CQExpressionWidget::DisplayPattern)
{
  // COPASI object format
  mObjectDisplayFormat.setForeground(QColor(100, 0, 200));
}

CQExpressionHighlighter::~CQExpressionHighlighter()
{}

void CQExpressionHighlighter::highlightBlock(const QString &text)
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

CQValidatorExpression::CQValidatorExpression(QTextEdit * parent, const char * name, bool isBoolean):
  CQValidator< QTextEdit >(parent, &QTextEdit::toPlainText, name),
  mExpression()
{
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
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
  mExpression.setIsBoolean(booleanRequired);
}

//***********************************************************************

CQValidatorFunction::CQValidatorFunction(QTextEdit * parent, const char * name):
  CQValidator< QTextEdit >(parent, &QTextEdit::toPlainText, name),
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
      std::string Infix = pExpressionWidget->getFunction();

      if (Infix == CMassAction::Infix[0] ||
          Infix == CMassAction::Infix[1] ||
          (const_cast< CFunction * >(&mFunction)->setInfix(Infix) &&
           const_cast< CFunction * >(&mFunction)->compile()))
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
  : QTextEdit(parent),
    mpValidatorExpression(NULL),
    mpValidatorFunction(NULL),
    mObjectClasses(TransientExpression),
    mpCurrentObject(NULL)
{
  setObjectName(QString::fromUtf8(name));
  setTabChangesFocus(true);

  mpExpressionHighlighter = new CQExpressionHighlighter(this);

  int h, s, v;

  mSavedColor = palette().color(backgroundRole());
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;

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
          std::vector<std::vector<std::string> > params;

          Function.createListOfParametersForMathML(params);
          out << Function.writeMathML(params, true, false);
        }
      else if (Infix == CMassAction::Infix[1])
        {
          CMassAction Function(TriFalse, NULL);
          std::vector<std::vector<std::string> > params;

          Function.createListOfParametersForMathML(params);
          out << Function.writeMathML(params, true, false);
        }
      else
        {
          std::vector<std::vector<std::string> > params;
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
  bool isAdvancedEditing = CCopasiRootContainer::getConfiguration()->useAdvancedEditing();

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

  if (e == QKeySequence::SelectPreviousChar  && !isAdvancedEditing)
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

        if (isAdvancedEditing) break;

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

        if (isAdvancedEditing) break;

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

        if (isAdvancedEditing) break;

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

        if (isAdvancedEditing) break;

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

        if (isAdvancedEditing) break;

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
  f1.setForeground(QColor(0, 0, 0));

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

  CFunctionDB* pFunDB = CCopasiRootContainer::getFunctionList();
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  std::vector<CCopasiContainer*> containers;
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

      CCopasiObjectName InfixName(TO_UTF8(InfixObjectPattern.cap(1)));
      CCopasiObject * pObject = pDataModel->ObjectFromName(containers, InfixName);

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

const CCopasiObject* findObjectByDisplayName(const CCopasiDataModel* dataModel, const std::string displayString)
{
  if (dataModel == NULL || displayString.empty()) return NULL;

  const CModel* model = dataModel->getModel();

  if (displayString == "Time") return model;

  if (displayString == "Avogadro Constant") return dynamic_cast<const CCopasiObject* >(model->getObject("Reference=" + displayString));

  if (displayString == "Quantity Conversion Factor") return dynamic_cast<const CCopasiObject* >(model->getObject("Reference=" + displayString));

  size_t pos = displayString.find("Compartments[");

  if (pos != std::string::npos)
    {
      const CCopasiVectorN< CCompartment > & compartments = model->getCompartments();

      for (CCopasiVectorN< CCompartment >::const_iterator it = compartments.begin(); it != compartments.end(); ++it)
        {
          const CCompartment *current = *it;

          if (current->getObjectDisplayName() == displayString)
            {
              return current;
            }
          else if (current->getInitialValueReference() != NULL &&
                   current->getInitialValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getInitialValueReference();
            }
          else if (current->getValueReference() != NULL &&
                   current->getValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getValueReference();
            }
          else if (current->getRateReference() != NULL &&
                   current->getRateReference()->getObjectDisplayName() == displayString)
            {
              return current->getRateReference();
            }
        }
    }

  pos = displayString.find("Values[");

  if (pos != std::string::npos)
    {
      const CCopasiVectorN< CModelValue > & values = model->getModelValues();

      for (CCopasiVectorN< CModelValue >::const_iterator it = values.begin(); it != values.end(); ++it)
        {
          const CModelValue *current = *it;

          if (current->getObjectDisplayName() == displayString)
            {
              return current;
            }
          else if (current->getInitialValueReference() != NULL &&
                   current->getInitialValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getInitialValueReference();
            }
          else if (current->getValueReference() != NULL &&
                   current->getValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getValueReference();
            }
          else if (current->getRateReference() != NULL &&
                   current->getRateReference()->getObjectDisplayName() == displayString)
            {
              return current->getRateReference();
            }
        }
    }

  // no reasonable check for metabolites, so lets just go through them
  {
    const CCopasiVector< CMetab > & metabs = model->getMetabolites();

    for (CCopasiVector< CMetab >::const_iterator it = metabs.begin(); it != metabs.end(); ++it)
      {
        const CMetab *current = *it;

        if (current->getObjectDisplayName() == displayString)
          {
            return current;
          }
        else if (current->getInitialValueReference() != NULL &&
                 current->getInitialValueReference()->getObjectDisplayName() == displayString)
          {
            return current->getInitialValueReference();
          }
        else if (current->getInitialConcentrationReference() != NULL &&
                 current->getInitialConcentrationReference()->getObjectDisplayName() == displayString)
          {
            return current->getInitialConcentrationReference();
          }
        else if (current->getValueReference() != NULL &&
                 current->getValueReference()->getObjectDisplayName() == displayString)
          {
            return current->getValueReference();
          }
        else if (current->getConcentrationReference() != NULL &&
                 current->getConcentrationReference()->getObjectDisplayName() == displayString)
          {
            return current->getConcentrationReference();
          }
        else if (current->getRateReference() != NULL &&
                 current->getRateReference()->getObjectDisplayName() == displayString)
          {
            return current->getRateReference();
          }
        else if (current->getConcentrationRateReference() != NULL &&
                 current->getConcentrationRateReference()->getObjectDisplayName() == displayString)
          {
            return current->getConcentrationRateReference();
          }
      }
  }

  return NULL;
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
      std::map< std::string, const CCopasiObject *>::const_iterator itObject = mParseList.find(DisplayName);

      if (itObject == mParseList.end() && CCopasiRootContainer::getConfiguration()->useAdvancedEditing())
        {

          // the object pattern does not match the species name if
          // the species is in a different compartment, in that case we
          // have to remove the backslash in the displayname.
          std::string::size_type bsPos = DisplayName.find("\\}");

          if (bsPos != std::string::npos)
            DisplayName.erase(bsPos, 1);

          // here we don't have an object recognized, what we ought to do is to find it in the model
          const CCopasiObject* object = findObjectByDisplayName(
                                          mpCurrentObject != NULL ? mpCurrentObject->getObjectDataModel() : (*CCopasiRootContainer::getDatamodelList())[0],
                                          DisplayName);

          if (object != NULL)
            {
              const_cast<CQExpressionWidget*>(this)->mParseList[DisplayName] = object;
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
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, mObjectClasses);

  if (pObject)
    {
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
      f1.setForeground(QColor(0, 0, 0));

      QTextCharFormat f = mpExpressionHighlighter->mObjectDisplayFormat;
      //QColor color2 = f.foreground().color();

      setCurrentCharFormat(f);
      insertPlainText(FROM_UTF8("{" + Insert + "}"));
      setCurrentCharFormat(f1);
    }
}
