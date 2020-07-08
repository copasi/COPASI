// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQBaseWidget
#define COPASI_CQBaseWidget

#include <QtCore/QVariant>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

#include "copasi/barChart/ui_CQBaseWidget.h"

class CQBaseWidget : public QWidget, public Ui::CQBaseWidget
{
  Q_OBJECT

public:
  CQBaseWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  virtual ~CQBaseWidget();

  void setSliderActive(const bool &active);

  bool isSliderActive() const;

  virtual void sliderMoved(int column, int row) = 0;

  int scaleFactor();

protected slots:
  void setSlider();

protected:
  bool mSliderActive;

  int mScaleFactor;
};

#endif // COPASI_CQBaseWidget
