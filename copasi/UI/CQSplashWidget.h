/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSplashWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/12/01 16:09:09 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQSplashWidget.ui'
 **
 ** Created: Fr Dez 1 17:03:33 2006
 **      by: The User Interface Compiler ($Id: CQSplashWidget.h,v 1.2 2006/12/01 16:09:09 ssahle Exp $)
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
