// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSplashWidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:32:59 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQSplashWidget.ui'
 **
 ** Created: Tue Feb 19 23:23:06 2008
 **      by: The User Interface Compiler ($Id: CQSplashWidget.h,v 1.4 2008/03/12 00:32:59 shoops Exp $)
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
