/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiSlider.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/31 14:49:17 $
   End CVS Header */

#ifndef CopasiSlider_H__
#define CopasiSlider_H__

#include "qvbox.h"
#include "utilities/CCopasiParameter.h"

class QSlider;
class QWidget;
class CCopasiObject;
class QLabel;
class CCopasiParameterGroup;

class CopasiSlider: public QVBox
  {
    Q_OBJECT
  public:
    enum NumberType {undefined = 0, intType, doubleType};

    CopasiSlider(CCopasiObject* object, QWidget* parent = 0);
    virtual ~CopasiSlider();

    CCopasiParameter::Type type() const;
    void setType(CCopasiParameter::Type type);

    C_FLOAT64 value() const;
    void setValue(C_FLOAT64 value);
    unsigned C_INT32 minorMajorFactor() const;
    void setMinorMajorFactor(unsigned C_INT32 factor);
    C_FLOAT64 minorTickInterval() const;
    unsigned C_INT32 numMinorTicks() const;
    void setNumMinorTicks(unsigned C_INT32 numMinorTicks);
    CCopasiObject* object() const;
    void setObject(CCopasiObject* object);
    void setMinValue(C_FLOAT64 value);
    void setMaxValue(C_FLOAT64 value);
    C_FLOAT64 minValue() const;
    C_FLOAT64 maxValue() const;
    CCopasiParameterGroup* parameterGroup() const;
    void setParameterGroup(CCopasiParameterGroup* parameterGroup);
    void updateValue(bool modifyRange);

  public slots:
    void sliderValueChanged(int value);
    void qSliderReleased();

  signals:
    void valueChanged(double);
    void sliderReleased();

  protected:
    CCopasiObject* mpObject;
    QSlider* mpSlider;
    QLabel* mpLabel;
    CCopasiParameterGroup* mpParameterGroup;
    C_FLOAT64 mTickInterval;
    C_FLOAT64 mMinValue;
    C_FLOAT64 mMaxValue;
    C_FLOAT64 mValue;
    unsigned C_INT32 mNumMinorTicks;
    unsigned C_INT32 mMinorMajorFactor;
    CCopasiParameter::Type mType;
    bool mValueOutOfRange;

    void updateSliderData();
    void updateLabel();
  };

#endif // CopasiSlider_H__
