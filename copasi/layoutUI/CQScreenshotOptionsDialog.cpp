// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQScreenshotOptionsDialog.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:33:51 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQScreenshotOptionsDialog.h"

#include <QDoubleValidator>

#include <sstream>
#include <assert.h>

CQScreenshotOptionsDialog::CQScreenshotOptionsDialog(double layoutX, double layoutY, double layoutWidth, double layoutHeight,
    double currentX, double currentY, double currentWidth, double currentHeight,
    QWidget* pParent):
    QDialog(pParent),
    mLayoutX(layoutX),
    mLayoutY(layoutY),
    mLayoutWidth(layoutWidth),
    mLayoutHeight(layoutHeight),
    mCurrentX(currentX),
    mCurrentY(currentY),
    mCurrentWidth(currentWidth),
    mCurrentHeight(currentHeight),
    mX(mCurrentX),
    mY(mCurrentY),
    mWidth(mCurrentWidth),
    mHeight(mCurrentHeight),
    mImageWidth(1000),
    mImageHeight((unsigned int)(1000.0*mCurrentHeight / mCurrentWidth)),
    mDrawSelectionDecorations(false)
{
  setupUi(this);
  // set validators on the input fields
  QDoubleValidator* pVal = new QDoubleValidator(this->x_line_edit);
  this->x_line_edit->setValidator(pVal);
  pVal = new QDoubleValidator(this->y_line_edit);
  this->y_line_edit->setValidator(pVal);
  pVal = new QDoubleValidator(this->width_line_edit);
  pVal->setBottom(0.0);
  this->width_line_edit->setValidator(pVal);
  pVal = new QDoubleValidator(this->height_line_edit);
  pVal->setBottom(0.0);
  this->height_line_edit->setValidator(pVal);

  // set the information labels text at the top
  std::ostringstream os;
  os << "visible area: (x=" << this->mCurrentX << ", y=" << this->mCurrentY;
  os << ", width=" << this->mCurrentWidth << ", height=" << this->mCurrentHeight << ")";
  this->visible_area_label->setText(QString(os.str().c_str()));
  os.str("");
  os << "layout area: (x=" << this->mLayoutX << ", y=" << this->mLayoutY;
  os << ", width=" << this->mLayoutWidth << ", height=" << this->mLayoutHeight << ")";
  this->layout_area_label->setText(QString(os.str().c_str()));
  // set the values of the input fields
  this->x_line_edit->setText(QString("%1").arg(this->mX));
  this->y_line_edit->setText(QString("%1").arg(this->mY));
  this->width_line_edit->setText(QString("%1").arg(this->mWidth));
  this->height_line_edit->setText(QString("%1").arg(this->mHeight));
  this->image_width_spinbox->setValue(this->mImageWidth);
  this->image_height_spinbox->setValue(this->mImageHeight);
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
  // set the options depending on the settings made by the user
  this->mDrawSelectionDecorations = this->draw_selection_checkbox->isChecked();

  if (this->custom_button->isChecked())
    {
      // get the values from the input fields
      bool ok = false;

      if (!this->x_line_edit->text().isEmpty())
        {
          this->mX = this->x_line_edit->text().toDouble(&ok);
          assert(ok == true);
        }

      if (!this->y_line_edit->text().isEmpty())
        {
          this->mY = this->y_line_edit->text().toDouble(&ok);
          assert(ok == true);
        }

      if (!this->width_line_edit->text().isEmpty())
        {
          this->mWidth = this->width_line_edit->text().toDouble(&ok);
          assert(ok == true);
        }

      if (!this->height_line_edit->text().isEmpty())
        {
          this->mHeight = this->height_line_edit->text().toDouble(&ok);
          assert(ok == true);
        }
    }
  else if (this->complete_button->isChecked())
    {
      this->mX = this->mLayoutX;
      this->mY = this->mLayoutY;
      this->mWidth = this->mLayoutWidth;
      this->mHeight = this->mLayoutHeight;
    }
  else
    {
      this->mX = this->mCurrentX;
      this->mY = this->mCurrentY;
      this->mWidth = this->mCurrentWidth;
      this->mHeight = this->mCurrentHeight;
    }

  this->mImageWidth = this->image_width_spinbox->value();
  this->mImageHeight = this->image_height_spinbox->value();
  this->QDialog::accept();
}

// if a radio button is clicked
void CQScreenshotOptionsDialog::slot_custom_area_toggled(bool toggled)
{
  this->x_line_edit->setEnabled(toggled);
  this->y_line_edit->setEnabled(toggled);
  this->width_line_edit->setEnabled(toggled);
  this->height_line_edit->setEnabled(toggled);
}
