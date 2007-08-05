// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/05 10:00:19 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQDifferentialEquations.ui'
 **
 ** Created: So Aug 5 11:45:07 2007
 **      by: The User Interface Compiler ($Id: CQDifferentialEquations.h,v 1.1 2007/08/05 10:00:19 ssahle Exp $)
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
class QtMmlWidget;

class CQDifferentialEquations : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQDifferentialEquations(QWidget* parent = 0, const char* name = 0);
    ~CQDifferentialEquations();

    QPushButton* mpSaveButton;
    QScrollView* mpScrollView;

    virtual bool enter(const std::string &);

  public slots:
    virtual void slotUpdateWidget();

  protected:
    QtMmlWidget * mpMMLWidget;
    std::ostringstream mml;

    QGridLayout* CQDifferentialEquationsLayout;
    QSpacerItem* spacer1;

  protected slots:
    virtual void languageChange();

    virtual void slotSaveMML();

  private:
    QPixmap image0;

    void init();
    virtual void newFunction();
  };

#endif // CQDIFFERENTIALEQUATIONS_H
