// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/07/25 06:30:01 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQDifferentialEquations.ui'
 **
 ** Created: Wed Jul 23 14:04:44 2008
 **      by: The User Interface Compiler ($Id: CQDifferentialEquations.h,v 1.3 2008/07/25 06:30:01 pwilly Exp $)
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
class QPushButton;
class QComboBox;
class QLabel;
class QtMmlWidget;

class CQDifferentialEquations : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQDifferentialEquations(QWidget* parent = 0, const char* name = 0);
    ~CQDifferentialEquations();

    QScrollView* mpScrollView;
    QPushButton* mpSaveButton;
    QComboBox* comboBoxFunctions;
    QComboBox* comboBoxParameters;
    QLabel* textLabelParameters;
    QLabel* textLabelFunctions;

    virtual bool enter(const std::string &);

  public slots:
    virtual void slotUpdateWidget();
    virtual void slotSave();

  protected:
    QtMmlWidget * mpMMLWidget;
    std::ostringstream mml;

    QVBoxLayout* CQDifferentialEquationsLayout;
    QGridLayout* layout9;
    QSpacerItem* spacer1_2;
    QSpacerItem* spacer1;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;

    void init();
    virtual void newFunction();
    virtual void saveMML(const QString filename);
    virtual void saveTeX(const QString filename);
  };

#endif // CQDIFFERENTIALEQUATIONS_H
