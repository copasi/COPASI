// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/ParaPanel.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/07/19 14:33:55 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'ParaPanel.ui'
 **
 ** Created: Do Jul 19 16:31:47 2007
 **      by: The User Interface Compiler ($Id: ParaPanel.h,v 1.6 2007/07/19 14:33:55 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef PARAPANEL_H
#define PARAPANEL_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QButtonGroup;
class QRadioButton;
class QSpinBox;

class ParaPanel : public QWidget
  {
    Q_OBJECT

  public:
    ParaPanel(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ParaPanel();

    QLabel* schedModeLabel;
    QButtonGroup* scalingButtonGroup;
    QRadioButton* individScalButton;
    QRadioButton* globalScalButton;
    QLabel* frameRateLabel;
    QSpinBox* spinBox1;
    QLabel* paraLabel;

  public slots:
    virtual void stepSlider_valueChanged(int);

  protected:
    QGridLayout* ParaPanelLayout;
    QSpacerItem* spacer1;
    QVBoxLayout* scalingButtonGroupLayout;

  protected slots:
    virtual void languageChange();
  };

#endif // PARAPANEL_H
