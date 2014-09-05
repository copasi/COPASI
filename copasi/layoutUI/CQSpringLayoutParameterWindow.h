// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQ_SPRING_LAYOUT_PARAMETER_WINDOW_H
#define CQ_SPRING_LAYOUT_PARAMETER_WINDOW_H

#include <QtGui/QDockWidget>
#include <QtCore/QString>

#include <vector>

#include <layout/CCopasiSpringLayout.h>

class QwtSlider;
class CQSpringLayoutParameterWindow : public QDockWidget
{
  Q_OBJECT
public:
  CQSpringLayoutParameterWindow(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
  virtual ~CQSpringLayoutParameterWindow();
  CCopasiSpringLayout::Parameters& getLayoutParameters();

protected slots:
  void slotLayoutSliderChanged();
protected:
  std::vector<QwtSlider*> mLayoutSliders;
  CCopasiSpringLayout::Parameters mLayoutParameters;
};

#endif

