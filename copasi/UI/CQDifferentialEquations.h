// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/05 12:24:53 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQDifferentialEquations.ui'
 **
 ** Created: So Aug 5 14:11:34 2007
 **      by: The User Interface Compiler ($Id: CQDifferentialEquations.h,v 1.2 2007/08/05 12:24:53 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQDIFFERENTIALEQUATIONS_H
#define CQDIFFERENTIALEQUATIONS_H

#include <qvariant.h>
#include <qpixmap.h>
#include <sstream>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QScrollView;
class QLabel;
class QComboBox;
class QPushButton;
class QtMmlWidget;

class CQDifferentialEquations : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQDifferentialEquations(QWidget* parent = 0, const char* name = 0);
    ~CQDifferentialEquations();

    QScrollView* mpScrollView;
    QLabel* textLabelParameters;
    QLabel* textLabelFunctions;
    QComboBox* comboBoxParameters;
    QComboBox* comboBoxFunctions;
    QPushButton* mpSaveButton;

    virtual bool enter(const std::string &);

  public slots:
    virtual void slotUpdateWidget();

  protected:
    QtMmlWidget * mpMMLWidget;
    std::ostringstream mml;

    QGridLayout* CQDifferentialEquationsLayout;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1_2;
    QHBoxLayout* layout2;
    QSpacerItem* spacer1;
    QVBoxLayout* layout3;
    QSpacerItem* spacer3;

  protected slots:
    virtual void languageChange();

    virtual void slotSaveMML();

  private:
    QPixmap image0;

    void init();
    virtual void newFunction();
  };

#endif // CQDIFFERENTIALEQUATIONS_H
