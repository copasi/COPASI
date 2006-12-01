/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSplashWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/01 15:24:00 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQSplashWidget.ui'
 **
 ** Created: Fri Dec 1 09:18:04 2006
 **      by: The User Interface Compiler ($Id: CQSplashWidget.h,v 1.1 2006/12/01 15:24:00 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQSPLASHWIDGET_H
#define CQSPLASHWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "CopasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;

class CQSplashWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQSplashWidget(QWidget* parent = 0, const char* name = 0);
    ~CQSplashWidget();

    QLabel* mpPixmap;
    QLabel* mpLblVersion;

  protected:
    QVBoxLayout* CQSplashWidgetLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;

    void init();
  };

#endif // CQSPLASHWIDGET_H
