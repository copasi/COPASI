// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ui_CQReactionsWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/03/19 10:49:43 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/*
 All rights reserved.
 */

/********************************************************************************
 ** Form generated from reading ui file 'CQReactionsWidget.ui'
 **
 ** Created: Tue Mar 10 13:23:58 2009
 **      by: Qt User Interface Compiler version 4.4.1
 **
 ** WARNING! All changes made in this file will be lost when recompiling ui file!
 ********************************************************************************/

#ifndef UI_CQREACTIONSWIDGET_H
#define UI_CQREACTIONSWIDGET_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <vector>
#include "copasi/UI/copasiWidget.h"
#include "copasiWidget.h"

class Ui_CQReactionsWidget
{
public:
  QGridLayout *gridLayout;
  QHBoxLayout *hboxLayout;
  QSpacerItem *horizontalSpacerLeft;
  QPushButton *mpBtnNew;
  QPushButton *mpBtnDelete;
  QPushButton *mpBtnClear;
  QSpacerItem *horizontalSpacerRight;
  QTableView *mpTblReactions;

  void setupUi(CopasiWidget *CQReactionsWidget)
  {
    if (CQReactionsWidget->objectName().isEmpty())
      CQReactionsWidget->setObjectName(QString::fromUtf8("CQReactionsWidget"));

    CQReactionsWidget->resize(541, 456);
    gridLayout = new QGridLayout(CQReactionsWidget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    horizontalSpacerLeft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(horizontalSpacerLeft);

    mpBtnNew = new QPushButton(CQReactionsWidget);
    mpBtnNew->setObjectName(QString::fromUtf8("mpBtnNew"));
    mpBtnNew->setFocusPolicy(Qt::NoFocus);

    hboxLayout->addWidget(mpBtnNew);

    mpBtnDelete = new QPushButton(CQReactionsWidget);
    mpBtnDelete->setObjectName(QString::fromUtf8("mpBtnDelete"));
    mpBtnDelete->setFocusPolicy(Qt::NoFocus);

    hboxLayout->addWidget(mpBtnDelete);

    mpBtnClear = new QPushButton(CQReactionsWidget);
    mpBtnClear->setObjectName(QString::fromUtf8("mpBtnClear"));
    mpBtnClear->setFocusPolicy(Qt::NoFocus);

    hboxLayout->addWidget(mpBtnClear);

    horizontalSpacerRight = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(horizontalSpacerRight);

    gridLayout->addLayout(hboxLayout, 2, 0, 1, 3);

    mpTblReactions = new QTableView(CQReactionsWidget);
    mpTblReactions->setObjectName(QString::fromUtf8("mpTblReactions"));
    mpTblReactions->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed | QAbstractItemView::SelectedClicked);
    mpTblReactions->setSelectionMode(QAbstractItemView::SingleSelection);
    mpTblReactions->setSelectionBehavior(QAbstractItemView::SelectRows);
    mpTblReactions->setSortingEnabled(false);

    gridLayout->addWidget(mpTblReactions, 0, 0, 1, 3);

    QWidget::setTabOrder(mpTblReactions, mpBtnNew);
    QWidget::setTabOrder(mpBtnNew, mpBtnDelete);
    QWidget::setTabOrder(mpBtnDelete, mpBtnClear);

    retranslateUi(CQReactionsWidget);
    QObject::connect(mpBtnClear, SIGNAL(pressed()), CQReactionsWidget, SLOT(slotBtnClearClicked()));
    QObject::connect(mpBtnDelete, SIGNAL(pressed()), CQReactionsWidget, SLOT(slotBtnDeleteClicked()));
    QObject::connect(mpBtnNew, SIGNAL(pressed()), CQReactionsWidget, SLOT(slotBtnNewClicked()));
    QObject::connect(mpTblReactions, SIGNAL(doubleClicked(QModelIndex)), CQReactionsWidget, SLOT(slotDoubleClicked(QModelIndex)));

    QMetaObject::connectSlotsByName(CQReactionsWidget);
  } // setupUi

  void retranslateUi(CopasiWidget *CQReactionsWidget)
  {
    CQReactionsWidget->setProperty("caption", QVariant(QApplication::translate("CQReactionsWidget", "Reactions", 0, QApplication::UnicodeUTF8)));
    mpBtnNew->setText(QApplication::translate("CQReactionsWidget", "New", 0, QApplication::UnicodeUTF8));
    mpBtnDelete->setText(QApplication::translate("CQReactionsWidget", "Delete", 0, QApplication::UnicodeUTF8));
    mpBtnClear->setText(QApplication::translate("CQReactionsWidget", "Clear", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CQReactionsWidget);
  } // retranslateUi
};

namespace Ui
{
class CQReactionsWidget: public Ui_CQReactionsWidget {};
} // namespace Ui

#endif // UI_CQREACTIONSWIDGET_H
