/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderSettingsDialog.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/12/10 15:15:08 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'SliderSettingsDialog.ui'
 **
 ** Created: Fri Dec 10 13:52:15 2004
 **      by: The User Interface Compiler ($Id: SliderSettingsDialog.h,v 1.2 2004/12/10 15:15:08 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef SLIDERSETTINGSDIALOG_H
#define SLIDERSETTINGSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include <string>
#include "CopasiSlider.h"
#include "copasi.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
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
    QLabel* mpMinorMajorFactorLabel;
    QLabel* mpMaxValueLabel;
    QLabel* mpNumMinorTicksLabel;
    QLineEdit* mpNumMinorTicksEdit;
    QLineEdit* mpMinorTickSizeEdit;
    QLabel* mpMinorTickSizeLabel;
    QLabel* mpMinValueLabel;
    QLineEdit* mpObjectValueEdit;
    QLineEdit* mpMinorMajorFactorEdit;
    QLineEdit* mpMinValueEdit;
    QLineEdit* mpMaxValueEdit;
    QLabel* mpObjectValueLabel;
    QPushButton* mpOkButton;
    QPushButton* mpCancelButton;

    virtual CopasiSlider* getSlider();
    virtual void setSlider(CopasiSlider * slider);
    virtual void setDefinedSliders(std::vector< CopasiSlider * > sliderVect);
    virtual void setModel(CModel * model);
    virtual void disableObjectChoosing(bool disableChoosing);
    virtual void updateSlider();

  signals:
    void sliderChanged(CopasiSlider* slider);

  protected:
    CModel* mpModel;
    C_INT32 mCurrentTaskId;
    CopasiSlider* mpSlider;
    std::vector< CopasiSlider* > mDefinedSliders;
    unsigned int mNumMinorTicks;
    unsigned int mMinorMajorFactor;
    double mValue;
    double mMinValue;
    double mMaxValue;
    double mMinorTickSize;

    virtual void updateInputFieldsValues();
    virtual void updateInputFields();
    virtual void init();

    QVBoxLayout* SliderSettingsDialogLayout;
    QHBoxLayout* mpLayout11;
    QGridLayout* layout9;
    QSpacerItem* mpSpacer1;
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
  };

#endif // SLIDERSETTINGSDIALOG_H
