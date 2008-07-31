// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetRandom.h,v $
//   $Revision: 1.5.18.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/31 23:10:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CScanWidgetRandom.ui'
 **
 ** Created: Thu Jul 31 17:06:25 2008
 **      by: The User Interface Compiler ($Id: CScanWidgetRandom.h,v 1.5.18.1 2008/07/31 23:10:16 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CSCANWIDGETRANDOM_H
#define CSCANWIDGETRANDOM_H

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
class QComboBox;
class QCheckBox;
class CCopasiParameterGroup;
class CCopasiObject;
class CScanProblem;
class CModel;

class CScanWidgetRandom : public QWidget
  {
    Q_OBJECT

  public:
    CScanWidgetRandom(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CScanWidgetRandom();

    QFrame* frame;
    QLabel* labelTitle;
    QLabel* labelObject;
    QLineEdit* lineEditObject;
    QToolButton* buttonObject;
    QComboBox* comboBoxType;
    QLabel* labelType;
    QLineEdit* lineEditMax;
    QLineEdit* lineEditMin;
    QLabel* labelMin;
    QLabel* labelMax;
    QCheckBox* checkBoxLog;

    virtual bool initFromScanItem(CCopasiParameterGroup * pg, const CModel * model);
    virtual bool saveToScanItem(CScanProblem * pg) const;

  protected:
    const CModel* mpModel;
    const CCopasiObject* mpObject;

    QVBoxLayout* CScanWidgetRandomLayout;
    QVBoxLayout* frameLayout;
    QHBoxLayout* layout8;
    QGridLayout* layout2;

  protected slots:
    virtual void languageChange();

    virtual void slotChooseObject();
    virtual void changeType();

  private:
    QPixmap image0;

    void init();
  };

#endif // CSCANWIDGETRANDOM_H
