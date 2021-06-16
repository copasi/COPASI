// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include <copasi/layoutUI/CQSpringLayoutParameterWindow.h>

#include <qwt_slider.h>
#include <qwt_scale_engine.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

CQSpringLayoutParameterWindow::CQSpringLayoutParameterWindow(const QString &title, QWidget *parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
  QWidget* pParaWidget = new QWidget(this);
  QVBoxLayout* pLayout = new QVBoxLayout;
  pParaWidget->setLayout(pLayout);
  size_t i;

  for (i = 0; i < mLayoutParameters.values.size(); ++i)
    {
      QLabel* label = new QLabel(mLayoutParameters.names[i].c_str());
      pLayout->addWidget(label);
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
      QwtSlider* slider = new QwtSlider(Qt::Horizontal,  pParaWidget);
      slider->setScalePosition(QwtSlider::LeadingScale);

      if (mLayoutParameters.isLog[i])
        slider->setScaleEngine(new QwtLogScaleEngine());

#else
      QwtSlider* slider = new QwtSlider(pParaWidget, Qt::Horizontal, QwtSlider::BottomScale);

      if (mLayoutParameters.isLog[i])
        {
          slider->setScaleEngine(new QwtLog10ScaleEngine());
          slider->setRange(log10(mLayoutParameters.min[i]), log10(mLayoutParameters.max[i]));
          slider->setScale(mLayoutParameters.min[i], mLayoutParameters.max[i]);
        }
      else
        {
          slider->setRange(mLayoutParameters.min[i], mLayoutParameters.max[i]);
        }

#endif

      if (mLayoutParameters.isLog[i])
        {

          slider->setScale(mLayoutParameters.min[i], mLayoutParameters.max[i]);
          slider->setValue(log10(mLayoutParameters.values[i]));
        }
      else
        {
          slider->setValue(mLayoutParameters.values[i]);
        }

      pLayout->addWidget(slider);
      mLayoutSliders.push_back(slider);

      connect(slider, SIGNAL(valueChanged(double)), this, SLOT(slotLayoutSliderChanged()));
    }

  setWidget(pParaWidget);
  setVisible(false);
}

CQSpringLayoutParameterWindow::~CQSpringLayoutParameterWindow()
{
}

CCopasiSpringLayout::Parameters& CQSpringLayoutParameterWindow::getLayoutParameters()
{
  return mLayoutParameters;
}

void CQSpringLayoutParameterWindow::slotLayoutSliderChanged()
{
  //std::cout << "slider..." << std::endl;
  size_t i;

  for (i = 0; i < mLayoutSliders.size(); ++i)
    {
      if (mLayoutParameters.isLog[i])
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
        mLayoutParameters.values[i] = pow(10, log10(mLayoutSliders[i]->value()));

#else
        mLayoutParameters.values[i] = pow(10, mLayoutSliders[i]->value());
#endif
      else
        mLayoutParameters.values[i] = mLayoutSliders[i]->value();
    }
}
