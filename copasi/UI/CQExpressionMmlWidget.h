// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidget.h,v $
//   $Revision: 1.4.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/13 17:04:14 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQExpressionMmlWidget.ui'
 **
 ** Created: Thu Nov 13 10:42:30 2008
 **      by: The User Interface Compiler ($Id: CQExpressionMmlWidget.h,v 1.4.4.1 2008/11/13 17:04:14 shoops Exp $)
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
    CQMmlScrollView* mpMmlScrollView;
    QToolButton* mpBtnEditExpression;
    QToolButton* mpBtnSaveExpression;

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
    QHBoxLayout* mpMmlPageLayout;
    QVBoxLayout* layout5;
    QSpacerItem* mpSpacerMmlObject;

  protected slots:
    virtual void languageChange();

    void slotGoExpressionWidget();
    void slotGoMmlWidget();

  private:
    QString MMLStr;

    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;

    void saveTeX(const QString filename);
    void saveMML(const QString filename);

  private slots:
    void slotSaveExpression();
  };

#endif // CQEXPRESSIONMMLWIDGET_H
