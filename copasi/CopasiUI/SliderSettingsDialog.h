/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SliderSettingsDialog.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/03/30 12:11:58 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'SliderSettingsDialog.ui'
 **
 ** Created: Wed Mar 30 14:08:23 2005
 **      by: The User Interface Compiler ($Id: SliderSettingsDialog.h,v 1.6 2005/03/30 12:11:58 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef SLIDERSETTINGSDIALOG_H
#define SLIDERSETTINGSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include <string>
#include "utilities/CSlider.h"
#include "copasi.h"

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
    QCheckBox* mpGlobalCheckBox;
    QPushButton* mpExtendedOptionsButton;
    QFrame* mpExtendedOptionsFrame;
    QLabel* mpMinorMajorFactorLabel;
    QLabel* mpNumMinorTicksLabel;
    QLineEdit* mpNumMinorTicksEdit;
    QLineEdit* mpMinorTickSizeEdit;
    QLineEdit* mpObjectValueEdit;
    QLineEdit* mpMinorMajorFactorEdit;
    QLabel* mpObjectValueLabel;
    QLabel* mpMinorTickSizeLabel;
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
    bool mChanged;
    double mMinorTickSize;
    double mMaxValue;
    double mMinValue;
    double mValue;
    unsigned int mMinorMajorFactor;
    unsigned int mNumMinorTicks;
    std::vector< CSlider* > mDefinedSliders;
    CSlider* mpSlider;
    C_INT32 mCurrentTaskId;
    CModel* mpModel;
    CSlider::Scale mScaling;

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
  };

#endif // SLIDERSETTINGSDIALOG_H
