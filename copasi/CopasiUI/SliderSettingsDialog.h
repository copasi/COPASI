/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SliderSettingsDialog.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/03/11 08:17:52 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'SliderSettingsDialog.ui'
 **
 ** Created: Fri Mar 11 10:15:27 2005
 **      by: The User Interface Compiler ($Id: SliderSettingsDialog.h,v 1.4 2005/03/11 08:17:52 gauges Exp $)
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
