#include <layoutUI/CQSpringLayoutParameterWindow.h>

#include <qwt_slider.h>
#include <qwt_scale_engine.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>



CQSpringLayoutParameterWindow::CQSpringLayoutParameterWindow(const QString &title, QWidget *parent , Qt::WindowFlags flags )
  : QDockWidget(title, parent, flags)
{
  QWidget* pParaWidget = new QWidget();
  QVBoxLayout* pLayout = new QVBoxLayout;
  pParaWidget->setLayout(pLayout);
  size_t i;

  for (i = 0; i < mLayoutParameters.values.size(); ++i)
  {
    QLabel* label = new QLabel(mLayoutParameters.names[i].c_str());
    pLayout->addWidget(label);
    QwtSlider* slider = new QwtSlider(pParaWidget);
    slider->setScalePosition(QwtSlider::BottomScale);

    if (mLayoutParameters.isLog[i])
    {
      slider->setScaleEngine(new QwtLog10ScaleEngine);
      slider->setRange(log10(mLayoutParameters.min[i]), log10(mLayoutParameters.max[i]));
      slider->setScale(mLayoutParameters.min[i], mLayoutParameters.max[i]);
      slider->setValue(log10(mLayoutParameters.values[i]));
    }
    else
    {
      slider->setRange(mLayoutParameters.min[i], mLayoutParameters.max[i]);
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
      mLayoutParameters.values[i] = pow(10, mLayoutSliders[i]->value());
    else
      mLayoutParameters.values[i] = mLayoutSliders[i]->value();
  }
}
