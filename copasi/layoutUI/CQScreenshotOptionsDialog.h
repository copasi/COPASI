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

#ifndef CQScreenshotOptionsDialog_H__
#define CQScreenshotOptionsDialog_H__

#include "ui_CQScreenshotDialog.h"

#include <set>

#include <QDialog>
#include <QRegExp>
#include <QValidator>

class CQScreenshotOptionsDialog : public QDialog, private Ui::screenshot_option_dialog
{
  Q_OBJECT

public:
  enum FRAME_OPTION
  {
    UNSET,
    CURRENT_FRAME,
    ALL_FRAMES,
    USER_DEFINED_FRAMES
  };

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

  // stores the value of which frames are to be exported.
  FRAME_OPTION mFrameOption;

  // store the frames to export
  std::set<size_t> mFrames;

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

  // whether to draw the options for the frame selection or not
  int mLastFrame;

  // color for background highlighting in
  // the frames input field
  QColor mDefaultColor;
  QColor mHighlightColor;
  bool mFramesEditHighlighted;

public:
  CQScreenshotOptionsDialog(double layoutX, double layoutY, double layoutWidth, double layoutHeight,
                            double currentX, double currentY, double currentWidth, double currentHeight,
                            unsigned int imageWidth, unsigned int imageHeight, int lastFrame = -1,
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

  /**
   * Returns which frames are to be exported.
   * For a dialog that does not display the frames option, this will
   * return UNSET.
   * For dialogs with the frame option, possible values are CURRENT_FRAME,
   * ALL_FRAMES, USER_DEFINED_FRAMES.
   */
  FRAME_OPTION getFrameOption() const;

  /**
   * Returns the set of frames.
   */
  const std::set<size_t>& getFrameSet() const;

protected slots:
  // if ok is pressed
  virtual void accept();

  // if a radio button is clicked
  void slotDisplayButtonClicked(QAbstractButton* pButton);

  // if a radio button in the frame options widget is clicked
  void slotFrameButtonClicked(QAbstractButton* pButton);

  // called when the image width is changed
  void slotImageWidthChanged(int w);

  // called when the image height is changed
  void slotImageHeightChanged(int h);

  // called when the width is changed
  void slotWidthChanged(const QString& wt);

  // called when the height is changed
  void slotHeightChanged(const QString& ht);

  // called when the x value is changed
  void slotXChanged(const QString& xt);

  // called when the y value is changed
  void slotYChanged(const QString& yt);

  // called when the frames text is finished
  void slotFramesTextEditingFinished();

  // called when the frames text is edited
  void slotFramesTextEdited(const QString& text);

  // called when the draw selection item checkbox is toggled
  void slotDrawSelectionToggled(bool v);
};

class CQFrameInputValidator : public QValidator
{
protected:
  static const QString ValidRegExpString;
  static const QString IntermediateRegExpString;
  static const QString ClosedRangeGroupRegExpString;

  QRegExp mValidationRegExp;
  QRegExp mIntermediateRegExp;
  QRegExp mClosedRangeGroupRegExp;

public:
  CQFrameInputValidator(QObject* pParent = NULL);

  virtual QValidator::State validate(QString& input, int & pos) const;
};

#endif // CQScreenshotOptionsDialog_H__
