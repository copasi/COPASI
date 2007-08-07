// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/Attic/CQCopasiLayoutWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/07 15:35:41 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQCopasiLayoutWidget.ui'
 **
 ** Created: Di Aug 7 17:30:34 2007
 **      by: The User Interface Compiler ($Id: CQCopasiLayoutWidget.h,v 1.3 2007/08/07 15:35:41 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQCOPASILAYOUTWIDGET_H
#define CQCOPASILAYOUTWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "UI/copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;

class CQCopasiLayoutWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQCopasiLayoutWidget(QWidget* parent = 0, const char* name = 0);
    ~CQCopasiLayoutWidget();

    QPushButton* mpShowLayoutOld;

    virtual bool enter(const std::string &);

  public slots:
    virtual void slotUpdateWidget();

  protected:
    QVBoxLayout* CQCopasiLayoutWidgetLayout;
    QSpacerItem* spacer4;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;

    void init();
    virtual void newFunction();

  private slots:
    virtual void displayNetworkWidgetOld();
  };

#endif // CQCOPASILAYOUTWIDGET_H
