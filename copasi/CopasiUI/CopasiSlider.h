/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiSlider.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/02/25 15:15:58 $
   End CVS Header */

#ifndef CopasiSlider_H__
#define CopasiSlider_H__

#include "qhbox.h"
#include "utilities/CCopasiParameter.h"
#include "utilities/CSlider.h"

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
    CopasiSlider(CSlider* pSlider, QWidget* parent = 0);
    virtual ~CopasiSlider();

    CSlider::Type type() const;
    void setType(CSlider::Type type);

    C_FLOAT64 value() const;
    void setValue(C_FLOAT64 value);
    unsigned C_INT32 minorMajorFactor() const;
    void setMinorMajorFactor(unsigned C_INT32 factor);
    C_FLOAT64 minorTickInterval() const;
    unsigned C_INT32 numMinorTicks() const;
    void setNumMinorTicks(unsigned C_INT32 numMinorTicks);
    void setMinValue(C_FLOAT64 value);
    void setMaxValue(C_FLOAT64 value);
    C_FLOAT64 minValue() const;
    C_FLOAT64 maxValue() const;
    void updateValue(bool modifyRange);
    CCopasiObject* object() const;
    void setObject(CCopasiObject* object);
    CSlider* getCSlider() const;

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
    CSlider* mpCSlider;
    QSlider* mpQSlider;
    QLabel* mpLabel;
    QToolButton* mpCloseButton;
    QToolButton* mpEditButton;
    bool mValueOutOfRange;

    void updateSliderData();
    void updateLabel();
  };

#endif // CopasiSlider_H__
