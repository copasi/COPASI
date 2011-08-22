// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/CQBaseWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/08/22 21:39:53 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQBaseWidget
#define COPASI_CQBaseWidget

#include <QVariant>

#include "copasi/barChart/ui_CQBaseWidget.h"

class CQBaseWidget : public QWidget, public Ui::CQBaseWidget
{
  Q_OBJECT

public:
  CQBaseWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  virtual ~CQBaseWidget();

  void setSliderActive(const bool & active);

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
