/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiSlider.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/12 09:59:22 $
   End CVS Header */

#ifndef CopasiSlider_H__
#define CopasiSlider_H__

#include "qvbox.h"

class QSlider;
class QWidget;
class CCopasiObject;
class QLabel;

class CopasiSlider: public QVBox
  {
    Q_OBJECT
  public:
    enum NumberType {undefined = 0, intType, doubleType};

    CopasiSlider(CCopasiObject* object, QWidget* parent = 0);
    virtual ~CopasiSlider();

    NumberType type() const;
    void setType(NumberType type);

    double value() const;
    void setValue(double value);
    unsigned int minorMajorFactor() const;
    void setMinorMajorFactor(unsigned int factor);
    double minorTickInterval() const;
    unsigned int numMinorTicks() const;
    void setNumMinorTicks(unsigned int numMinorTicks);
    CCopasiObject* object() const;
    void setObject(CCopasiObject* object);
    void setMinValue(double value);
    void setMaxValue(double value);
    double minValue() const;
    double maxValue() const;

  public slots:
    void sliderValueChanged(int value);
    void qSliderReleased();

  signals:
    void valueChanged(double);
    void sliderReleased();

  protected:
    CCopasiObject* mpObject;
    NumberType mTypeVar;
    double mMinValue;
    double mMaxValue;
    int mNumMinorTicks;
    unsigned int mMinorMajorFactor;
    QSlider* mpSlider;
    QLabel* mpLabel;
    double mTickInterval;
    double mValue;

    void updateSliderData();
    void updateLabel();
  };

#endif // CopasiSlider_H__
