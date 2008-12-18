// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPreferenceDialog.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPREFERENCEDIALOG_H
#define CQPREFERENCEDIALOG_H

#include <qvariant.h>

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListView>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QDialog>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
//Added by qt3to4:
#include <Q3HBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CQPreferenceDialog
  {
  public:
    QWidget *Layout1;
    Q3HBoxLayout *hboxLayout;
    QPushButton *mpBtnOk;
    QPushButton *mpBtnCancel;
    Q3ListView *mpListView;

    void setupUi(QDialog *CQPreferenceDialog)
    {
      if (CQPreferenceDialog->objectName().isEmpty())
        CQPreferenceDialog->setObjectName(QString::fromUtf8("CQPreferenceDialog"));
      CQPreferenceDialog->resize(261, 225);
      CQPreferenceDialog->setSizeGripEnabled(true);
      Layout1 = new QWidget(CQPreferenceDialog);
      Layout1->setObjectName(QString::fromUtf8("Layout1"));
      Layout1->setGeometry(QRect(10, 190, 240, 28));
      hboxLayout = new Q3HBoxLayout(Layout1);
      hboxLayout->setSpacing(6);
      hboxLayout->setMargin(0);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      hboxLayout->setContentsMargins(0, 0, 0, 0);
      mpBtnOk = new QPushButton(Layout1);
      mpBtnOk->setObjectName(QString::fromUtf8("mpBtnOk"));
      mpBtnOk->setAutoDefault(true);
      mpBtnOk->setDefault(true);

      hboxLayout->addWidget(mpBtnOk);

      mpBtnCancel = new QPushButton(Layout1);
      mpBtnCancel->setObjectName(QString::fromUtf8("mpBtnCancel"));
      mpBtnCancel->setAutoDefault(true);

      hboxLayout->addWidget(mpBtnCancel);

      mpListView = new Q3ListView(CQPreferenceDialog);
      mpListView->addColumn(QApplication::translate("CQPreferenceDialog", "Name", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setClickEnabled(true, mpListView->header()->count() - 1);
      mpListView->header()->setResizeEnabled(true, mpListView->header()->count() - 1);
      mpListView->addColumn(QApplication::translate("CQPreferenceDialog", "Value", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setClickEnabled(true, mpListView->header()->count() - 1);
      mpListView->header()->setResizeEnabled(true, mpListView->header()->count() - 1);
      mpListView->setObjectName(QString::fromUtf8("mpListView"));
      mpListView->setGeometry(QRect(10, 10, 238, 170));
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(mpListView->sizePolicy().hasHeightForWidth());
      mpListView->setSizePolicy(sizePolicy);
      mpListView->setAllColumnsShowFocus(true);
      mpListView->setDefaultRenameAction(Q3ListView::Accept);
      QWidget::setTabOrder(mpListView, mpBtnOk);
      QWidget::setTabOrder(mpBtnOk, mpBtnCancel);

      retranslateUi(CQPreferenceDialog);
      QObject::connect(mpBtnOk, SIGNAL(clicked()), CQPreferenceDialog, SLOT(slotBtnOk()));
      QObject::connect(mpBtnCancel, SIGNAL(clicked()), CQPreferenceDialog, SLOT(slotBtnCancel()));
      QObject::connect(mpListView, SIGNAL(clicked(Q3ListViewItem*, QPoint, int)), CQPreferenceDialog, SLOT(editItem(Q3ListViewItem*, QPoint, int)));
      QObject::connect(mpListView, SIGNAL(returnPressed(Q3ListViewItem*)), CQPreferenceDialog, SLOT(editItem(Q3ListViewItem*)));

      QMetaObject::connectSlotsByName(CQPreferenceDialog);
    } // setupUi

    void retranslateUi(QDialog *CQPreferenceDialog)
    {
      CQPreferenceDialog->setWindowTitle(QApplication::translate("CQPreferenceDialog", "Preferences", 0, QApplication::UnicodeUTF8));
      mpBtnOk->setText(QApplication::translate("CQPreferenceDialog", "&OK", 0, QApplication::UnicodeUTF8));
      mpBtnOk->setShortcut(QString());
      mpBtnCancel->setText(QApplication::translate("CQPreferenceDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
      mpBtnCancel->setShortcut(QString());
      mpListView->header()->setLabel(0, QApplication::translate("CQPreferenceDialog", "Name", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setLabel(1, QApplication::translate("CQPreferenceDialog", "Value", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQPreferenceDialog);
    } // retranslateUi
  };

namespace Ui
  {
  class CQPreferenceDialog: public Ui_CQPreferenceDialog {};
} // namespace Ui

QT_END_NAMESPACE

class CQPreferenceDialog : public QDialog, public Ui::CQPreferenceDialog
  {
    Q_OBJECT

  public:
    CQPreferenceDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~CQPreferenceDialog();

  protected slots:
    virtual void languageChange();

    virtual void slotBtnOk();
    virtual void slotBtnCancel();
    virtual void editItem(Q3ListViewItem*, const QPoint&, int);
    virtual void editItem(Q3ListViewItem*);

  private slots:
    virtual void init();
  };

#endif // CQPREFERENCEDIALOG_H
