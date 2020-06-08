// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CopasiSlider_H__
#define CopasiSlider_H__

#include <QFrame>
#include <QLabel>

#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/utilities/CSlider.h"

class QSlider;
class QWidget;
class CDataObject;
class QLabel;
class CCopasiParameterGroup;
class QToolButton;
class DataModelGUI;

class CopasiSlider: public QFrame
{
  Q_OBJECT
public:
  CopasiSlider(CSlider* pSlider, DataModelGUI * pDM, QWidget* parent = 0);
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
  void setOriginalValue(C_FLOAT64 value);
  C_FLOAT64 minValue() const;
  C_FLOAT64 maxValue() const;
  C_FLOAT64 originalValue() const;
  void updateValue(bool modifyRange, bool updateDependencies);
  const CDataObject* object() const;
  void setObject(const CDataObject * object);
  CSlider* getCSlider() const;
  void setCSlider(CSlider* pSlider);
  void updateLabel();
  void updateSliderData();
  void resetValue();
  void focusSlider();

  /**
   * Checks whether the slider is actually valid.
   * This is mainly done by calling isValid on the underlying CSlider object.
   */
  bool isValid() const;

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
  DataModelGUI * mpDM;

  int calculatePositionFromValue(C_FLOAT64 value);
  C_FLOAT64 calculateValueFromPosition(int position);
};

#endif // CopasiSlider_H__
