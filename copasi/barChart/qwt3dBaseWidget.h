// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/Attic/qwt3dBaseWidget.h,v $
//   $Revision: 1.1.14.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/27 16:57:08 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef BASE_WIDGET_H
#define BASE_WIDGET_H

#include <qmainwindow.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QSlider;
class QFrame;

class BaseWidget : public QWidget
  {
    Q_OBJECT

  public:
    BaseWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0 /*, bool showSlider = false*/);
    ~BaseWidget();

    bool mpSlider;

    QLabel* mpLabelColumn;
    QLabel* mpLabelRow;
    QSlider* mpSliderColumn;
    QSlider* mpSliderRow;
    QFrame* mpFrame;

    QHBoxLayout* mpHBoxBig;
    QVBoxLayout* mpVBoxBig;
    QVBoxLayout* mpVBoxSmall;
    QHBoxLayout* mpHBoxSmall;

    void activateSlider();
    virtual void sliderMoved(int column, int row) = 0;

  protected:
    QGridLayout* mpBaseWidgetLayout;

  protected slots:
    void setSlider();
  };

#endif // BASE_WIDGET_H
