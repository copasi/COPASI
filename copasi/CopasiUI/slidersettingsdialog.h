/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/slidersettingsdialog.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/02 17:13:58 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'slidersettingsdialog.ui'
 **
 ** Created: Tue Nov 2 18:08:00 2004
 **      by: The User Interface Compiler ($Id: slidersettingsdialog.h,v 1.2 2004/11/02 17:13:58 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef SLIDERSETTINGSDIALOG_H
#define SLIDERSETTINGSDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "SliderDialog.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QComboBox;
class QLineEdit;
class CModel;

class SliderSettingsDialog : public QDialog
  {
    Q_OBJECT

  public:
    SliderSettingsDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~SliderSettingsDialog();

    QPushButton* objectBrowseButton;
    QLabel* objectLabel;
    QLabel* taskLabel;
    QComboBox* objectComboBox;
    QComboBox* taskComboBox;
    QLabel* minorTickSizeLabel;
    QLabel* minValueLabel;
    QLineEdit* majorTickSizeEdit;
    QLineEdit* minValueEdit;
    QLineEdit* minorTickSizeEdit;
    QLabel* majorTickSizeLabel;
    QLineEdit* numMinorTicksEdit;
    QLineEdit* numMajorTicksEdit;
    QLabel* numMinorTicksLabel;
    QLineEdit* maxValueEdit;
    QLabel* maxValueLabel;
    QLabel* objectValueLabel;
    QLineEdit* objectValueEdit;
    QLabel* numMajorTicksLabel;
    QPushButton* okButton;
    QPushButton* cancelButton;

    virtual void setSlider(C_INT32 taskId, CopasiSlider * slider);
    virtual void setTask(C_INT32 taskId);
    virtual void setTaskList(std::map<C_INT32, std::string> taskMap);
    virtual void setSliderMap(std::map<C_INT32, std::vector<CopasiSlider *> > sliderMap);
    virtual void setObject(CCopasiObject * object);
    virtual void setModel(CModel * model);

  public slots:
    virtual void numMajorTicksChanged();
    virtual void numMinorTicksChanged();

  signals:
    void sliderChanged(CopasiSlider* slider);

  protected:
    CModel* mpModel;
    double numMinorSteps;
    double numMajorSteps;
    double maxValueVar;
    double minValueVar;
    double minorTickSizeVar;
    double majorTickSizeVar;
    double objectValueVar;
    C_INT32 mCurrentTaskId;
    std::ostringstream outStream;
    std::map<C_INT32, std::vector< CopasiSlider * > > sliderMap;
    std::map<C_INT32, std::string> taskDisplayMap;

    virtual void init();
    virtual const std::string int2Text(int i);
    virtual const std::string double2Text(double d);
    virtual double text2Double(const std::string & text);
    virtual int text2Int(const std::string & text);

    QHBoxLayout* SliderSettingsDialogLayout;
    QVBoxLayout* layout19;
    QGridLayout* layout18;
    QHBoxLayout* layout15;
    QSpacerItem* spacer1;
    QVBoxLayout* layout14;
    QSpacerItem* spacer2;
    QGridLayout* layout12;
    QGridLayout* layout13;
    QHBoxLayout* layout2;

  protected slots:
    virtual void languageChange();

    virtual void updateObjectBox();
    virtual void updateSliderValues();
    virtual void okButtonPressed();
    virtual void cancelButtonPressed();
    virtual void majorTickSizeChanged();
    virtual void minorTickSizeChanged();
    virtual void minValueChanged();
    virtual void maxValueChanged();
    virtual void objectValueChanged();
    virtual void browseButtonPressed();
  };

#endif // SLIDERSETTINGSDIALOG_H
