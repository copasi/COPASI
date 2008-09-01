// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetScan.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/01 16:55:49 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CScanWidgetScan.ui'
 **
 ** Created: Thu Jul 31 17:06:25 2008
 **      by: The User Interface Compiler ($Id: CScanWidgetScan.h,v 1.7 2008/09/01 16:55:49 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CSCANWIDGETSCAN_H
#define CSCANWIDGETSCAN_H

#include <qvariant.h>
#include <qpixmap.h>
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
    QLabel* labelTitle;
    QLabel* labelObject;
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
    const CModel* mpModel;
    const CCopasiObject* mpObject;

    QVBoxLayout* CScanWidgetScanLayout;
    QVBoxLayout* frameLayout;
    QHBoxLayout* layout7;
    QGridLayout* layout2;

  protected slots:
    virtual void languageChange();

    virtual void slotChooseObject();

  private:
    QPixmap image0;

    void init();
  };

#endif // CSCANWIDGETSCAN_H
