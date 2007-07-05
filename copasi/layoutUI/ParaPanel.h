// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/ParaPanel.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/07/05 16:29:10 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'ParaPanel.ui'
 **
 ** Created: Thu Jul 5 18:13:52 2007
 **      by: The User Interface Compiler ($Id: ParaPanel.h,v 1.2 2007/07/05 16:29:10 urost Exp $)
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
class QSpinBox;
class QButtonGroup;
class QRadioButton;
class QSlider;

class ParaPanel : public QWidget
  {
    Q_OBJECT

  public:
    ParaPanel(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ParaPanel();

    QLabel* paraLabel;
    QLabel* frameRateLabel;
    QSpinBox* spinBox1;
    QLabel* schedModeLabel;
    QButtonGroup* scalingButtonGroup;
    QRadioButton* individScalButton;
    QRadioButton* globalScalButton;
    QLabel* animModeLabel;
    QSlider* stepSlider;

  public slots:
    virtual void stepSlider_valueChanged(int);

  protected:
    QVBoxLayout* ParaPanelLayout;
    QHBoxLayout* layout1;
    QHBoxLayout* layout3;
    QVBoxLayout* layout2;

  protected slots:
    virtual void languageChange();
  };

#endif // PARAPANEL_H
