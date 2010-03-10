// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQScreenshotOptionsDialog.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:33:51 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQScreenshotOptionsDialog_H__
#define CQScreenshotOptionsDialog_H__

#include "ui_CQScreenshotDialog.h"

#include <QDialog>

class CQScreenshotOptionsDialog : public QDialog, private Ui::screenshot_option_dialog
{
  Q_OBJECT

protected:
  // values needed by the dialog

  // the lowest x value of the layout
  double mLayoutX;
  // the lowest y value of the layout
  double mLayoutY;
  // the width of the layout
  double mLayoutWidth;
  // the height of the layout
  double mLayoutHeight;
  // the x value of the current view
  double mCurrentX;
  // the y value of the current view
  double mCurrentY;
  // the width of the current view
  double mCurrentWidth;
  // the height of the current view
  double mCurrentHeight;

  // values set by the user

  // the part of the layout to use for the screenshot
  double mX;
  double mY;
  double mWidth;
  double mHeight;
  // the size of the image
  unsigned int mImageWidth;
  unsigned int mImageHeight;
  // whether the selection decorations are
  // to be drawn in the screenshot or not
  bool mDrawSelectionDecorations;

public:
  CQScreenshotOptionsDialog(double layoutX, double layoutY, double layoutWidth, double layoutHeight,
                            double currentX, double currentY, double currentWidth, double currentHeight,
                            QWidget* pParent = NULL);

  /*
   * Returns the chosen lowest x value.
   */
  double getX() const;

  /*
   * Returns the chosen lowest y value.
   */
  double getY() const;

  /*
   * Returns the chosen width value.
   */
  double getWidth() const;

  /*
   * Returns the chosen height value.
   */
  double getHeight() const;

  /*
   * Returns the chosen image width value.
   */
  unsigned int getImageWidth() const;

  /*
   * Returns the chosen image height value.
   */
  unsigned int getImageHeight() const;

  /*
   * Returns whether the user has chosen to include
   * the selection decoration in the screenshot or not.
   */
  bool isSetDrawSelectionDecoration() const;

protected slots:
  // if ok is pressed
  virtual void accept();

  // if a radio button is clicked
  void slot_custom_area_toggled(bool toggled);
};

#endif // CQScreenshotOptionsDialog_H__
