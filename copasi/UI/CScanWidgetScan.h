/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetScan.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/24 16:40:11 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CScanWidgetScan.ui'
 **
 ** Created: Do Feb 24 12:57:43 2005
 **      by: The User Interface Compiler ($Id: CScanWidgetScan.h,v 1.2 2005/02/24 16:40:11 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CSCANWIDGETSCAN_H
#define CSCANWIDGETSCAN_H

#include <qvariant.h>
#include <qwidget.h>
#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;
class QToolButton;
class QCheckBox;

class CScanWidgetScan : public QWidget
  {
    Q_OBJECT

  public:
    CScanWidgetScan(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CScanWidgetScan();

    QFrame* frame;
    QLabel* labelObject;
    QLabel* labelTitle;
    QLineEdit* lineEditObject;
    QToolButton* buttonObject;
    QLineEdit* lineEditMin;
    QLineEdit* lineEditNumber;
    QLabel* labelNumber;
    QLineEdit* lineEditMax;
    QLabel* labelMin;
    QLabel* labelMax;
    QCheckBox* checkBoxLog;

    virtual bool initFromScanItem(CCopasiParameterGroup * pg, const CModel * model);
    virtual bool saveToScanItem(CScanProblem * pg) const;

  protected:
    CCopasiObject* mpObject;
    const CModel* mpModel;

    QGridLayout* CScanWidgetScanLayout;
    QVBoxLayout* frameLayout;
    QGridLayout* layout1;
    QSpacerItem* spacer1;
    QGridLayout* layout2;

  protected slots:
    virtual void languageChange();

    virtual void slotChooseObject();

  private:
    void init();
  };

#endif // CSCANWIDGETSCAN_H
