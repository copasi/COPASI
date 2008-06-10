// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/10 08:08:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQExpressionMmlWidget.ui'
 **
 ** Created: Tue Jun 10 09:53:19 2008
 **      by: The User Interface Compiler ($Id: CQExpressionMmlWidget.h,v 1.3 2008/06/10 08:08:46 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQEXPRESSIONMMLWIDGET_H
#define CQEXPRESSIONMMLWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qwidgetstack.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQExpressionWidget;
class CQMmlScrollView;
class QWidgetStack;
class QToolButton;

class CQExpressionMmlWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQExpressionMmlWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQExpressionMmlWidget();

    QWidgetStack* mpWidgetStackExpressionMml;
    QWidget* mpExpressionPage;
    CQExpressionWidget* mpExpressionWidget;
    QToolButton* mpBtnExpressionObject;
    QToolButton* mpBtnViewExpression;
    QWidget* mpMmlPage;
    QToolButton* mpBtnEditExpression;
    CQMmlScrollView* mpMmlScrollView;

  public slots:
    void updateWidget();

  signals:
    void signalCheckValidity(bool);

  protected:
    void init();

    QGridLayout* CQExpressionMmlWidgetLayout;
    QGridLayout* mpExpressionPageLayout;
    QVBoxLayout* layout4;
    QSpacerItem* mpSpacerExpressionObject;
    QGridLayout* mpMmlPageLayout;
    QVBoxLayout* mpVBLayoutMml;
    QSpacerItem* mpSpacerMmlObject;

  protected slots:
    virtual void languageChange();

    void slotGoExpressionWidget();
    void slotGoMmlWidget();

  private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
  };

#endif // CQEXPRESSIONMMLWIDGET_H
