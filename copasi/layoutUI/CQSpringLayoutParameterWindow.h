// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQ_SPRING_LAYOUT_PARAMETER_WINDOW_H
#define CQ_SPRING_LAYOUT_PARAMETER_WINDOW_H

#include <QDockWidget>
#include <QtCore/QString>

#include <vector>

#include <copasi/layout/CCopasiSpringLayout.h>

class QwtSlider;
class CQSpringLayoutParameterWindow : public QDockWidget
{
  Q_OBJECT
public:
  CQSpringLayoutParameterWindow(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
  virtual ~CQSpringLayoutParameterWindow();
  CCopasiSpringLayout::Parameters& getLayoutParameters();

protected slots:
  void slotLayoutSliderChanged();
protected:
  std::vector<QwtSlider*> mLayoutSliders;
  CCopasiSpringLayout::Parameters mLayoutParameters;
};

#endif
