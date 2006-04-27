/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanWidgetRandom.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CScanWidgetRandom.ui'
 **
 ** Created: Tue Mar 28 14:23:45 2006
 **      by: The User Interface Compiler ($Id: CScanWidgetRandom.h,v 1.4 2006/04/27 01:27:42 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CSCANWIDGETRANDOM_H
#define CSCANWIDGETRANDOM_H

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
    QLabel* labelObject;
    QLabel* labelTitle;
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
    CCopasiObject* mpObject;
    const CModel* mpModel;

    QVBoxLayout* CScanWidgetRandomLayout;
    QVBoxLayout* frameLayout;
    QGridLayout* layout1;
    QSpacerItem* spacer1;
    QGridLayout* layout2;

  protected slots:
    virtual void languageChange();

    virtual void slotChooseObject();
    virtual void changeType();

  private:
    void init();
  };

#endif // CSCANWIDGETRANDOM_H
