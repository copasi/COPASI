// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetScan.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/13 19:56:56 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CScanWidgetScan.ui'
 **
 ** Created: Tue Mar 28 14:27:57 2006
 **      by: The User Interface Compiler ($Id: CScanWidgetScan.h,v 1.6 2007/03/13 19:56:56 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CSCANWIDGETSCAN_H
#define CSCANWIDGETSCAN_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;
class QToolButton;
class QCheckBox;
class CCopasiParameterGroup;
class CScanProblem;
class CModel;
class CCopasiObject;

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
    const CCopasiObject* mpObject;
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
