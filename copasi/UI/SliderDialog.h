/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/01 14:50:51 $
   End CVS Header */

#ifndef SLIDER_DIALOG_H__
#define SLIDER_DIALOG_H__

#include "qdialog.h"
#include "qvbox.h"
#include <vector>

class QScrollView;
class QHBox;
class QVBox;
class QListBox;
class QCheckBox;
class QPushButton;
class QString;
class QSlider;
class CCopasiObject;
class QLabel;

class SliderDialog: public QDialog
  {
    Q_OBJECT

  public:
    SliderDialog(QWidget* parent);
    virtual ~SliderDialog();
    void addSlider(const QString& name, int min, int max, int tickInterval);

  protected:
    QPushButton* runTaskButton;
    QCheckBox* autoRunCheckBox;
    QScrollView* scrollView;
    QVBox* sliderBox;

    void init();

  public slots:
    void toggleRunButtonState(bool);
  };

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
    double tickInterval() const;
    void setTickInterval(double tickInterval);
    CCopasiObject* object() const;
    void setObject(CCopasiObject* object);
    void setMinValue(double value);
    void setMaxValue(double value);
    double minValue() const;
    double maxValue() const;

  public slots:
    void sliderValueChanged(int value);

  protected:
    CCopasiObject* cobject;
    NumberType typeVar;
    double minValueVar;
    double maxValueVar;
    double factorVar;
    QSlider* slider;
    QLabel* label;

    void updateSliderData();
    void updateLabel();
    std::string numberToString(double number) const;
  };

#endif
