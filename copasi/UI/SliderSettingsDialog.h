/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderSettingsDialog.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/09/06 09:04:47 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'SliderSettingsDialog.ui'
 **
 ** Created: Wed Sep 6 10:57:55 2006
 **      by: The User Interface Compiler ($Id: SliderSettingsDialog.h,v 1.12 2006/09/06 09:04:47 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef SLIDERSETTINGSDIALOG_H
#define SLIDERSETTINGSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;
class QFrame;
class CModel;
class CSlider;

class SliderSettingsDialog : public QDialog
  {
    Q_OBJECT

  public:
    SliderSettingsDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~SliderSettingsDialog();

    QLabel* mpObjectLabel;
    QLineEdit* mpObjectNameLineEdit;
    QPushButton* mpObjectBrowseButton;
    QLabel* mpMinValueLabel;
    QLineEdit* mpMinValueEdit;
    QLabel* mpMaxValueLabel;
    QLineEdit* mpMaxValueEdit;
    QCheckBox* mpLogCheckBox;
    QPushButton* mpExtendedOptionsButton;
    QFrame* mpExtendedOptionsFrame;
    QLabel* mpNumMinorTicksLabel;
    QLabel* mpMinorMajorFactorLabel;
    QLabel* mpObjectValueLabel;
    QLineEdit* mpNumMinorTicksEdit;
    QLineEdit* mpObjectValueEdit;
    QLineEdit* mpMinorMajorFactorEdit;
    QLabel* mpMinorTickSizeLabel;
    QLineEdit* mpOriginalValueEdit;
    QLineEdit* mpMinorTickSizeEdit;
    QLabel* mpOriginalValueLabel;
    QPushButton* mpOkButton;
    QPushButton* mpCancelButton;

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

    virtual void updateInputFieldsValues();
    virtual void updateInputFields();
    virtual void init();
    virtual void updateInternalValues();

    QVBoxLayout* SliderSettingsDialogLayout;
    QHBoxLayout* mpLayout11;
    QHBoxLayout* layout5;
    QSpacerItem* mpSpacer1;
    QHBoxLayout* layout10;
    QSpacerItem* mpSpacer1_2_2;
    QHBoxLayout* layout9;
    QSpacerItem* spacer6;
    QGridLayout* mpExtendedOptionsFrameLayout;
    QSpacerItem* mpSpacer1_3;
    QSpacerItem* mpSpacer1_2;
    QSpacerItem* mpSpacer1_3_2;
    QHBoxLayout* mpLayout2;

  protected slots:
    virtual void languageChange();

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
  };

#endif // SLIDERSETTINGSDIALOG_H
