// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/Attic/qwt3dBaseWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/07 18:52:46 $
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

#include <q3mainwindow.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3Frame>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <QLabel>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QLabel;
class QSlider;
class Q3Frame;

class BaseWidget : public QWidget
  {
    Q_OBJECT

  public:
    BaseWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~BaseWidget();

    bool mpSlider;

    QLabel* mpLabelColumn;
    QLabel* mpLabelRow;
    QSlider* mpSliderColumn;
    QSlider* mpSliderRow;
    Q3Frame* mpFrame;

    Q3HBoxLayout* mpHBoxBig;
    Q3VBoxLayout* mpVBoxBig;
    Q3VBoxLayout* mpVBoxSmall;
    Q3HBoxLayout* mpHBoxSmall;

    void activateSlider();
    virtual void sliderMoved(int column, int row) = 0;

  protected:
    Q3GridLayout* mpBaseWidgetLayout;

  protected slots:
    virtual void languageChange();
    void setSlider();
  };

#endif // BASE_WIDGET_H
