/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SliderSettingsDialog.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:46 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'SliderSettingsDialog.ui'
 **
 ** Created: Tue Mar 28 14:42:13 2006
 **      by: The User Interface Compiler ($Id: SliderSettingsDialog.h,v 1.11 2006/04/27 01:27:46 shoops Exp $)
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

  public slots:
    virtual void lineEditChanged();

  signals:
    void sliderChanged(CSlider* slider);

  protected:
    int mScaling;
    CModel* mpModel;
    int mCurrentTaskId;
    CSlider* mpSlider;
    std::vector< CSlider* > mDefinedSliders;
    unsigned int mNumMinorTicks;
    unsigned int mMinorMajorFactor;
    double mOriginalValue;
    double mValue;
    double mMinValue;
    double mMaxValue;
    double mMinorTickSize;
    bool mChanged;

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
    virtual void minValueChanged();
    virtual void maxValueChanged();
    virtual void objectValueChanged();
    virtual void minorMajorFactorChanged();
    virtual void browseButtonPressed();
    virtual void extendedOptionsClicked();
    virtual void logCheckBoxToggled(bool on);
    virtual void globalCheckBoxToggled();
    virtual void originalValueChanged();
  };

#endif // SLIDERSETTINGSDIALOG_H
