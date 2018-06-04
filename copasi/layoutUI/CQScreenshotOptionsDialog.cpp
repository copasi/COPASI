// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQScreenshotOptionsDialog.h"

#include <QColor>
#include <QDoubleValidator>
#include <QPalette>
#include <QButtonGroup>

#include <iostream>
#include <assert.h>
#include <sstream>

#include "copasi/function/CEvaluationNodeFunction.h"

CQScreenshotOptionsDialog::CQScreenshotOptionsDialog(double layoutX, double layoutY, double layoutWidth, double layoutHeight,
    double currentX, double currentY, double currentWidth, double currentHeight, unsigned int imageWidth, unsigned int imageHeight,
    int lastFrame, QWidget* pParent):
  QDialog(pParent),
  mLayoutX(layoutX),
  mLayoutY(layoutY),
  mLayoutWidth(layoutWidth),
  mLayoutHeight(layoutHeight),
  mCurrentX(currentX),
  mCurrentY(currentY),
  mCurrentWidth(currentWidth),
  mCurrentHeight(currentHeight),
  mFrameOption(UNSET),
  mX(mCurrentX),
  mY(mCurrentY),
  mWidth(mCurrentWidth),
  mHeight(mCurrentHeight),
  mImageWidth(imageWidth),
  mImageHeight(imageHeight),
  mDrawSelectionDecorations(false),
  mLastFrame(lastFrame),
  mFramesEditHighlighted(false)
{
  setupUi(this);
  QPalette palette = this->mpFramesEdit->palette();
  this->mDefaultColor = palette.color(this->mpFramesEdit->backgroundRole());
  this->mHighlightColor = QColor(224, 128, 128);
  // we disable the edit window after we get the background color
  // otherwise we save the background for the disabled state
  this->mpFramesEdit->setEnabled(false);

  // check if we need to display the frame options, if yes make them visible and enable them
  this->mpFramesWidget->setEnabled(this->mLastFrame > 0);
  this->mpFramesWidget->setVisible(this->mLastFrame > 0);
  //
  // hide the custom size options
  this->mpAdvancedWidget->setVisible(false);
  this->adjustSize();

  // set a validator on the frames input field
  CQFrameInputValidator* pFrameVal = new CQFrameInputValidator(this);
  this->mpFramesEdit->setValidator(pFrameVal);

  // create a button group for the frame option checkboxes
  QButtonGroup* pFrameButtonGroup = new QButtonGroup(this);
  pFrameButtonGroup->addButton(this->mpCurrentFrameButton);
  pFrameButtonGroup->addButton(this->mpAllFramesButton);
  pFrameButtonGroup->addButton(this->mpFramesButton);
  pFrameButtonGroup->setExclusive(true);
  connect(pFrameButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(slotFrameButtonClicked(QAbstractButton*)));

  // create a button group for the display selection
  QButtonGroup* pDisplayButtonGroup = new QButtonGroup(this);
  pDisplayButtonGroup->addButton(this->mpCompleteButton);
  pDisplayButtonGroup->addButton(this->mpVisibleButton);
  pDisplayButtonGroup->addButton(this->mpCustomButton);
  pDisplayButtonGroup->setExclusive(true);
  connect(pDisplayButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(slotDisplayButtonClicked(QAbstractButton*)));

  //
  // set validators on the input fields
  QDoubleValidator* pVal = new QDoubleValidator(this->mpXLineEdit);
  this->mpXLineEdit->setValidator(pVal);
  this->mpXLineEdit->setText(QString("%1").arg(this->mCurrentX));
  pVal = new QDoubleValidator(this->mpYLineEdit);
  this->mpYLineEdit->setValidator(pVal);
  this->mpXLineEdit->setText(QString("%1").arg(this->mCurrentY));
  pVal = new QDoubleValidator(this->mpWidthLineEdit);
  pVal->setBottom(0.0);
  this->mpWidthLineEdit->setValidator(pVal);
  this->mpWidthLineEdit->setText(QString("%1").arg(this->mCurrentWidth));
  pVal = new QDoubleValidator(this->mpHeightLineEdit);
  pVal->setBottom(0.0);
  this->mpHeightLineEdit->setValidator(pVal);
  this->mpHeightLineEdit->setText(QString("%1").arg(this->mCurrentHeight));

  // set the information labels text at the top
  std::ostringstream os;
  os << "visible area: " << this->mCurrentX << "," << this->mCurrentY;
  os << " " << this->mCurrentWidth << " x " << this->mCurrentHeight;
  this->visible_area_label->setText(QString(os.str().c_str()));
  os.str("");
  os << "layout area: " << this->mLayoutX << "," << this->mLayoutY;
  os << " " << this->mLayoutWidth << " x " << this->mLayoutHeight;
  this->layout_area_label->setText(QString(os.str().c_str()));
  // set the values of the input fields
  this->mpXLineEdit->setText(QString("%1").arg(this->mX));
  this->mpYLineEdit->setText(QString("%1").arg(this->mY));
  this->mpWidthLineEdit->setText(QString("%1").arg(this->mWidth));
  this->mpHeightLineEdit->setText(QString("%1").arg(this->mHeight));
  this->mpImageWidthSpinbox->setValue(this->mImageWidth);
  this->mpImageHeightSpinbox->setValue(this->mImageHeight);

  // check if the image width or the image height are 0, if so uncheck
  // and disable the aspect check box
  if (this->mImageWidth == 0 || this->mImageHeight == 0)
    {
      this->mpKeepImageAspectCheckbox->setChecked(false);
      this->mpKeepImageAspectCheckbox->setEnabled(false);
    }

  //
  // check if the mCurrentWidth or the mCurrentHeight are 0.0, if so
  // uncheck and disable the aspect check box
  if (this->mCurrentWidth == 0.0 || this->mCurrentHeight == 0.0)
    {
      this->mpKeepAreaAspectCheckbox->setChecked(false);
      this->mpKeepAreaAspectCheckbox->setEnabled(false);
    }

  connect(this->mpImageWidthSpinbox, SIGNAL(valueChanged(int)), this, SLOT(slotImageWidthChanged(int)));
  connect(this->mpImageHeightSpinbox, SIGNAL(valueChanged(int)), this, SLOT(slotImageHeightChanged(int)));
  connect(this->mpWidthLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotWidthChanged(const QString&)));
  connect(this->mpHeightLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotHeightChanged(const QString&)));
  connect(this->mpXLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotXChanged(const QString&)));
  connect(this->mpYLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotYChanged(const QString&)));
  connect(this->mpDrawSelectionCheckbox, SIGNAL(toggled(bool)), this, SLOT(slotDrawSelectionToggled(bool)));
  connect(this->mpFramesEdit, SIGNAL(textEdited(const QString&)), this, SLOT(slotFramesTextEdited(const QString&)));
  connect(this->mpFramesEdit, SIGNAL(editingFinished()), this, SLOT(slotFramesTextEditingFinished()));
}

/*
 * Returns the chosen lowest x value.
 */
double CQScreenshotOptionsDialog::getX() const
{
  return this->mX;
}

/*
 * Returns the chosen lowest y value.
 */
double CQScreenshotOptionsDialog::getY() const
{
  return this->mY;
}

/*
 * Returns the chosen width value.
 */
double CQScreenshotOptionsDialog::getWidth() const
{
  return this->mWidth;
}

/*
 * Returns the chosen height value.
 */
double CQScreenshotOptionsDialog::getHeight() const
{
  return this->mHeight;
}

/*
 * Returns the chosen image width value.
 */
unsigned int CQScreenshotOptionsDialog::getImageWidth() const
{
  return this->mImageWidth;
}

/*
 * Returns the chosen image height value.
 */
unsigned int CQScreenshotOptionsDialog::getImageHeight() const
{
  return this->mImageHeight;
}

/*
 * Returns whether the user has chosen to include
 * the selection decoration in the screenshot or not.
 */
bool CQScreenshotOptionsDialog::isSetDrawSelectionDecoration() const
{
  return mDrawSelectionDecorations;
}

// if ok is pressed
void CQScreenshotOptionsDialog::accept()
{
  this->QDialog::accept();
}

// if a radio button is clicked
void CQScreenshotOptionsDialog::slotDisplayButtonClicked(QAbstractButton* pButton)
{
  if (pButton == this->mpCustomButton)
    {
      this->mpAdvancedWidget->setEnabled(true);
      this->mpAdvancedWidget->setVisible(true);
      this->adjustSize();
      // set mX and mY to the entries in the edit fields
      this->mX = this->mpXLineEdit->text().toDouble();
      this->mY = this->mpYLineEdit->text().toDouble();
      // set mWidth and mHeight to the entries in the edit fields
      this->mWidth = this->mpWidthLineEdit->text().toDouble();
      this->mHeight = this->mpHeightLineEdit->text().toDouble();
    }
  else
    {
      this->mpAdvancedWidget->setVisible(false);
      this->adjustSize();

      if (pButton == this->mpVisibleButton)
        {
          // set mX and mY to mCurrentX and mCurrentY
          this->mX = this->mCurrentX;
          this->mY = this->mCurrentY;
          // set mWidth and mHeight to mCurrentWidth and mCurrentHeight
          this->mWidth = this->mCurrentWidth;
          this->mHeight = this->mCurrentHeight;
        }
      else
        {
          // set mX and mY to mLayoutX and mLayoutY
          this->mX = this->mLayoutX;
          this->mY = this->mLayoutY;
          // set mWidth and mHeight to mLayoutWidth and mLayoutHeight
          this->mWidth = this->mLayoutWidth;
          this->mHeight = this->mLayoutHeight;
        }
    }
}

/**
 * Returns which frames are to be exported.
 * For a dialog that does not display the frames option, this will
 * return UNSET.
 * For dialogs with the frame option, possible values are CURRENT_FRAME,
 * ALL_FRAMES, USER_DEFINED_FRAMES.
 */
CQScreenshotOptionsDialog::FRAME_OPTION CQScreenshotOptionsDialog::getFrameOption() const
{
  return this->mFrameOption;
}

/**
 * Returns the set of frames.
 */
const std::set<size_t>& CQScreenshotOptionsDialog::getFrameSet() const
{
  return this->mFrames;
}

// if a radio button in the frame options widget is clicked
void CQScreenshotOptionsDialog::slotFrameButtonClicked(QAbstractButton* pButton)
{
  if (pButton == this->mpCurrentFrameButton)
    {
      this->mFrameOption = CQScreenshotOptionsDialog::CURRENT_FRAME;
      this->mpFramesEdit->setEnabled(false);
    }
  else if (pButton == this->mpAllFramesButton)
    {
      this->mFrameOption = CQScreenshotOptionsDialog::ALL_FRAMES;
      this->mpFramesEdit->setEnabled(false);
    }
  else if (pButton == this->mpFramesButton)
    {
      this->mFrameOption = CQScreenshotOptionsDialog::USER_DEFINED_FRAMES;
      this->mpFramesEdit->setEnabled(true);
    }
}

// called when the image width is changed
void CQScreenshotOptionsDialog::slotImageWidthChanged(int w)
{
  // is the keep aspect check box is set, we need to calculate the aspect first
  if (this->mpKeepImageAspectCheckbox->isChecked())
    {
      double aspect = (double)this->mImageHeight / (double)this->mImageWidth;
      int h = (int)(round(w * aspect));
      disconnect(this->mpImageHeightSpinbox, SIGNAL(valueChanged(int)), this, SLOT(slotImageHeightChanged(int)));
      this->mpImageHeightSpinbox->setValue(h);
      this->mImageHeight = h;
      connect(this->mpImageHeightSpinbox, SIGNAL(valueChanged(int)), this, SLOT(slotImageHeightChanged(int)));
    }

  // set the new width
  this->mImageWidth = w;

  // if either the new width or new height is 0, we have to disable the aspect check box
  if ((this->mImageWidth == 0 || this->mImageHeight == 0) && (this->mpKeepImageAspectCheckbox->isEnabled() || this->mpKeepImageAspectCheckbox->isChecked()))
    {
      this->mpKeepImageAspectCheckbox->setChecked(false);
      this->mpKeepImageAspectCheckbox->setEnabled(false);
    }
  else if (this->mpKeepImageAspectCheckbox->isEnabled() == false)
    {
      this->mpKeepImageAspectCheckbox->setEnabled(true);
    }
}

// called when the image height is changed
void CQScreenshotOptionsDialog::slotImageHeightChanged(int h)
{
  // is the keep aspect check box is set, we need to calculate the aspect first
  if (this->mpKeepImageAspectCheckbox->isChecked())
    {
      double aspect = (double)this->mImageWidth / (double)this->mImageHeight;
      int w = (int)(round(h * aspect));
      disconnect(this->mpImageWidthSpinbox, SIGNAL(valueChanged(int)), this, SLOT(slotImageWidthChanged(int)));
      this->mpImageWidthSpinbox->setValue(w);
      this->mImageWidth = w;
      connect(this->mpImageWidthSpinbox, SIGNAL(valueChanged(int)), this, SLOT(slotImageWidthChanged(int)));
    }

  // set the new width
  this->mImageHeight = h;

  // if either the new width or new height is 0, we have to disable the aspect check box
  if ((this->mImageWidth == 0 || this->mImageHeight == 0) && (this->mpKeepImageAspectCheckbox->isEnabled() || this->mpKeepImageAspectCheckbox->isChecked()))
    {
      this->mpKeepImageAspectCheckbox->setChecked(false);
      this->mpKeepImageAspectCheckbox->setEnabled(false);
    }
  else if (this->mpKeepImageAspectCheckbox->isEnabled() == false)
    {
      this->mpKeepImageAspectCheckbox->setEnabled(true);
    }
}

// called when the width is changed
void CQScreenshotOptionsDialog::slotWidthChanged(const QString& wt)
{
  double newWidth = wt.toDouble();

  // is the keep aspect check box is set, we need to calculate the aspect first
  if (this->mpKeepAreaAspectCheckbox->isChecked())
    {
      double aspect = (double)this->mHeight / (double)this->mWidth;
      double h = newWidth * aspect;
      disconnect(this->mpHeightLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotHeightChanged(const QString&)));
      this->mpHeightLineEdit->setText(QString("%1").arg(h));
      this->mHeight = h;
      connect(this->mpHeightLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotHeightChanged(const QString&)));
    }

  // set the new width
  this->mWidth = newWidth;

  // if either the new width or new height is 0, we have to disable the aspect check box
  if ((this->mWidth == 0.0 || this->mHeight == 0.0) && (this->mpKeepAreaAspectCheckbox->isEnabled() || this->mpKeepAreaAspectCheckbox->isChecked()))
    {
      this->mpKeepAreaAspectCheckbox->setChecked(false);
      this->mpKeepAreaAspectCheckbox->setEnabled(false);
    }
  else if (this->mpKeepAreaAspectCheckbox->isEnabled() == false)
    {
      this->mpKeepAreaAspectCheckbox->setEnabled(true);
    }
}

// called when the width is changed
void CQScreenshotOptionsDialog::slotHeightChanged(const QString& ht)
{
  double newHeight = ht.toDouble();

  // is the keep aspect check box is set, we need to calculate the aspect first
  if (this->mpKeepAreaAspectCheckbox->isChecked())
    {
      double aspect = (double)this->mWidth / (double)this->mHeight;
      double w = newHeight * aspect;
      disconnect(this->mpWidthLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotWidthChanged(const QString&)));
      this->mpWidthLineEdit->setText(QString("%1").arg(w));
      this->mWidth = w;
      connect(this->mpWidthLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotWidthChanged(const QString&)));
    }

  // set the new width
  this->mHeight = newHeight;

  // if either the new width or new height is 0, we have to disable the aspect check box
  if ((this->mWidth == 0.0 || this->mHeight == 0.0) && (this->mpKeepAreaAspectCheckbox->isEnabled() || this->mpKeepAreaAspectCheckbox->isChecked()))
    {
      this->mpKeepAreaAspectCheckbox->setChecked(false);
      this->mpKeepAreaAspectCheckbox->setEnabled(false);
    }
  else if (this->mpKeepAreaAspectCheckbox->isEnabled() == false)
    {
      this->mpKeepAreaAspectCheckbox->setEnabled(true);
    }
}

// called when the x value is changed
void CQScreenshotOptionsDialog::slotXChanged(const QString& xt)
{
  this->mX = xt.toDouble();
}

// called when the y value is changed
void CQScreenshotOptionsDialog::slotYChanged(const QString& yt)
{
  this->mY = yt.toDouble();
}

// called when the draw selection item checkbox is toggled
void CQScreenshotOptionsDialog::slotDrawSelectionToggled(bool v)
{
  this->mDrawSelectionDecorations = v;
}

// called when the frames text is changed
void CQScreenshotOptionsDialog::slotFramesTextEdited(const QString& /*text*/)
{
  if (this->mpFramesEdit->hasAcceptableInput() && this->mFramesEditHighlighted == true)
    {
      // set background to normal
      mpFramesEdit->setStyleSheet(QString(mpFramesEdit->metaObject()->className()) + " {background-color:" + mDefaultColor.name() + ";}");
      mFramesEditHighlighted = false;
    }
  else if (!this->mpFramesEdit->hasAcceptableInput() && this->mFramesEditHighlighted == false)
    {
      // set background to red
      mpFramesEdit->setStyleSheet(QString(mpFramesEdit->metaObject()->className()) + " {background-color:" + mHighlightColor.name() + ";}");
      mFramesEditHighlighted = true;
    }
}

// called when the frames text is changed
void CQScreenshotOptionsDialog::slotFramesTextEditingFinished()
{
  QString yt = this->mpFramesEdit->text();
  // the [0-9] are used instead of \\d because I only want these digits and not any symbol of any alphabet that counts as a digit
  //const QString complete("^(\\s*[0-9]+\\s*(-\\s*(?:[0-9]+\\s*)?)?|\\s*-\\s*[0-9]+\\s*)(?:,(\\s*[0-9]+\\s*(?:-\\s*([0-9]+\\s*)?)?|\\s*-\\s*[0-9]+\\s*))*$");
  //QRegExp completeRegExp(complete);
  //completeRegExp.setPatternSyntax(QRegExp::RegExp2);
  const QString number("^[0-9]+$");
  QRegExp numberRegExp(number);
  numberRegExp.setPatternSyntax(QRegExp::RegExp2);
  const QString closed("^([0-9]+)\\s*-\\s*([0-9]+)$");
  QRegExp closedRegExp(closed);
  closedRegExp.setPatternSyntax(QRegExp::RegExp2);
  const QString start("^([0-9]+)\\s*-$");
  QRegExp startRegExp(start);
  startRegExp.setPatternSyntax(QRegExp::RegExp2);
  const QString end("^-\\s*([0-9]+)$");
  QRegExp endRegExp(end);
  endRegExp.setPatternSyntax(QRegExp::RegExp2);
  // split the input into groups and parse the groups
  //bool match = completeRegExp.exactMatch(yt);
  //assert(match == true);

  //if (!match) return;

  //QStringList l = completeRegExp.capturedTexts();
  QStringList l = yt.split(QString(","), QString::SkipEmptyParts);
  int i, iMax = l.size();
  assert(iMax != 0);
  this->mFrames.clear();
  QString s1, s2;

  for (i = 0; i < iMax; ++i)
    {
      s1 = l[i].trimmed();

      // check if it is a number, a closed range or one of
      // the two possible open ranges
      if (numberRegExp.exactMatch(s1))
        {
          QStringList l2 = numberRegExp.capturedTexts();
          assert(l2.size() == 1);

          if (l2.size() > 0)
            {
              unsigned int n = l2[0].toUInt();

              if (this->mLastFrame > 0 && n <= (unsigned int)this->mLastFrame)
                {
                  this->mFrames.insert(n);
                }
            }
        }
      else if (closedRegExp.exactMatch(s1))
        {
          QStringList l2 = closedRegExp.capturedTexts();
          assert(l2.size() == 3);

          if (l2.size() > 2)
            {
              unsigned int n1 = l2[1].toUInt();
              unsigned int n2 = l2[2].toUInt();
              assert(n1 <= n2);

              if (this->mLastFrame > 0 && n1 <= (unsigned int)this->mLastFrame)
                {
                  n2 = (n2 > (unsigned int)this->mLastFrame) ? (unsigned int)this->mLastFrame : n2;

                  while (n1 <= n2)
                    {
                      this->mFrames.insert(n1);
                      ++n1;
                    }
                }
            }
        }
      else if (startRegExp.exactMatch(s1))
        {
          QStringList l2 = startRegExp.capturedTexts();
          assert(l2.size() == 2);

          if (l2.size() > 1)
            {
              unsigned int n = l2[1].toUInt();

              if (this->mLastFrame > 0 && n <= (unsigned int)this->mLastFrame)
                {
                  // add all number from n to this->mLastFrame
                  while (n <= (unsigned int)this->mLastFrame)
                    {
                      this->mFrames.insert(n);
                      ++n;
                    }
                }
            }
        }
      else if (endRegExp.exactMatch(s1))
        {
          QStringList l2 = endRegExp.capturedTexts();
          assert(l2.size() == 2);

          if (l2.size() > 1)
            {
              unsigned int n = l2[1].toUInt();

              if (this->mLastFrame > 0 && n <= (unsigned int)this->mLastFrame)
                {
                  // add all number from 1 to n
                  while (n != 0)
                    {
                      this->mFrames.insert(n);
                      --n;
                    }
                }
            }
        }
      else
        {
          // it be an empty string
          this->mFrames.clear();
          return;
        }
    }
}

// --------- Validator ------

// the [0-9] are used instead of \\d because I only want these digits and not any symbol of any alphabet that counts as a digit
const QString CQFrameInputValidator::ValidRegExpString("^(\\s*[0-9]+\\s*(-\\s*(?:[0-9]+\\s*)?)?|\\s*-\\s*[0-9]+\\s*)(?:,(\\s*[0-9]+\\s*(-\\s*([0-9]+\\s*)?)?|\\s*-\\s*[0-9]+\\s*))*$");
const QString CQFrameInputValidator::IntermediateRegExpString("^(?:,|-|[0-9]|\\s)*$");
const QString CQFrameInputValidator::ClosedRangeGroupRegExpString("^\\s*([0-9]+)\\s*-\\s*([0-9]+)\\s*$");

CQFrameInputValidator::CQFrameInputValidator(QObject* pParent):
  QValidator(pParent)
  , mValidationRegExp(ValidRegExpString)
  , mIntermediateRegExp(IntermediateRegExpString)
  , mClosedRangeGroupRegExp(ClosedRangeGroupRegExpString)
{
  this->mValidationRegExp.setPatternSyntax(QRegExp::RegExp2);
  this->mIntermediateRegExp.setPatternSyntax(QRegExp::RegExp2);
  this->mClosedRangeGroupRegExp.setPatternSyntax(QRegExp::RegExp2);
}

QValidator::State CQFrameInputValidator::validate(QString& input, int & /*pos*/) const
{
  // the expression is valid if it creates a match with mValidationRegexp
  QValidator::State state = QValidator::Invalid;

  if (this->mValidationRegExp.exactMatch(input))
    {
      state = QValidator::Acceptable;
      QStringList l = this->mValidationRegExp.capturedTexts();

      for (int i = 0; i < l.size() && state != QValidator::Invalid; ++i)
        {
          if (this->mClosedRangeGroupRegExp.exactMatch(l[i]))
            {
              // check if the numbers are ascending
              QStringList l2 = this->mClosedRangeGroupRegExp.capturedTexts();
              assert(l2.size() == 3);

              if (l2.size() != 3 || (l2.size() == 3 && l2[1].toUInt() > l2[2].toUInt()))
                {
                  state = QValidator::Intermediate;
                }
            }
        }
    }
  else
    {
      if (this->mIntermediateRegExp.exactMatch(input))
        {
          state = QValidator::Intermediate;
        }
    }

  // and if the order of items in a closed range group is ascending
  // if not, we check with mIntermediateRegExp if the state is intermediate
  return state;
}
