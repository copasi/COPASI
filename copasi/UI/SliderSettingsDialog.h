// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderSettingsDialog.h,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/07/27 13:33:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef SliderSettingsDialog_H__
#define SliderSettingsDialog_H__

#include "ui_SliderSettingsDialog.h"

#include <QDialog>

#include <vector>

class CSlider;
class CModel;

class SliderSettingsDialog : public QDialog, private Ui::SliderSettingsDialog
{
  Q_OBJECT

public:
  /**
   * Ctor.
   */
  SliderSettingsDialog(QWidget* pParent = NULL);

  virtual ~SliderSettingsDialog();

  virtual CSlider * getSlider();
  virtual void setSlider(CSlider * slider);
  virtual void setDefinedSliders(std::vector<CSlider *> sliderVect);
  virtual void setModel(CModel * model);
  virtual void disableObjectChoosing(bool disableChoosing);
  virtual void updateSlider();

signals:
  void sliderChanged(CSlider* slider);

protected:
  enum CHANGETYPE {NONE, OBJECT, MIN, MAX, NUMTICKS, TICKSIZE, TICKFACTOR, ORIGVAL, VALUE, LOGARITHMIC};
  CHANGETYPE mChanged;
  double mMinorTickSize;
  double mMaxValue;
  double mMinValue;
  double mValue;
  double mOriginalValue;
  unsigned int mMinorMajorFactor;
  unsigned int mNumMinorTicks;
  std::vector< CSlider* > mDefinedSliders;
  CSlider* mpSlider;
  int mCurrentTaskId;
  CModel* mpModel;
  int mScaling;

protected slots:
  virtual void okButtonPressed();
  virtual void cancelButtonPressed();
  virtual void minorTickSizeChanged();
  virtual void numMinorTicksChanged();
  virtual void maxValueChanged();
  virtual void objectValueChanged();
  virtual void minorMajorFactorChanged();
  virtual void browseButtonPressed();
  virtual void extendedOptionsClicked();
  virtual void logCheckBoxToggled(bool on);
  virtual void globalCheckBoxToggled();
  virtual void originalValueChanged();
  virtual void minValueChanged();
  virtual void minValueTextChanged();
  virtual void maxValueTextChanged();
  virtual void numTicksTextChanged();
  virtual void tickSizeTextChanged();
  virtual void tickFactorTextChanged();
  virtual void origValueTextChanged();
  virtual void valueTextChanged();

protected:
  void updateInputFieldsValues();
  void updateInputFields();
  void updateInternalValues();
  void init();
};

#endif /* SliderSettingsDialog_H__ */
