/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiSlider.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/02/18 09:58:02 $
   End CVS Header */

#ifndef CopasiSlider_H__
#define CopasiSlider_H__

#include "qhbox.h"
#include "utilities/CCopasiParameter.h"

class QSlider;
class QWidget;
class CCopasiObject;
class QLabel;
class CCopasiParameterGroup;
class QToolButton;

class CopasiSlider: public QHBox
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
    void qSliderPressed();
    void closeButtonClicked();
    void editButtonClicked();

  signals:
    void valueChanged(double);
    void sliderReleased();
    void sliderPressed();
    void closeClicked(CopasiSlider* slider);
    void editClicked(CopasiSlider* slider);

  protected:
    CCopasiObject* mpObject;
    QSlider* mpSlider;
    QLabel* mpLabel;
    QToolButton* mpCloseButton;
    QToolButton* mpEditButton;
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
