//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSplashWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/01/12 18:01:13 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQSplashWidget.ui'
 **
 ** Created: Fri Jan 12 13:00:50 2007
 **      by: The User Interface Compiler ($Id: CQSplashWidget.h,v 1.3 2007/01/12 18:01:13 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQSPLASHWIDGET_H
#define CQSPLASHWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;

class CQSplashWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQSplashWidget(QWidget* parent = 0, const char* name = 0);
    ~CQSplashWidget();

    QLabel* mpPixmap;
    QLabel* mpLblVersion;
    QLabel* mpLblLicense;
    QPushButton* mpBtnLicense;

  protected:
    QVBoxLayout* CQSplashWidgetLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpLayoutLicense;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;

    void init();

  private slots:
    void slotViewLicense();
  };

#endif // CQSPLASHWIDGET_H
