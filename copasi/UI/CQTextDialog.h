// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTextDialog.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:48:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTEXTDIALOG_H
#define CQTEXTDIALOG_H

#include <qvariant.h>

#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QDialog>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

class Ui_CQTextDialog
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3TextEdit *mpTextEdit;
    Q3HBoxLayout *hboxLayout;
    QSpacerItem *mpSpacer;
    QPushButton *mpBtnOK;
    QPushButton *mpBtnCancel;

    void setupUi(QDialog *CQTextDialog)
    {
      if (CQTextDialog->objectName().isEmpty())
        CQTextDialog->setObjectName(QString::fromUtf8("CQTextDialog"));
      CQTextDialog->resize(495, 178);
      CQTextDialog->setSizeGripEnabled(true);
      vboxLayout = new Q3VBoxLayout(CQTextDialog);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      mpTextEdit = new Q3TextEdit(CQTextDialog);
      mpTextEdit->setObjectName(QString::fromUtf8("mpTextEdit"));

      vboxLayout->addWidget(mpTextEdit);

      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setMargin(0);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      hboxLayout->addItem(mpSpacer);

      mpBtnOK = new QPushButton(CQTextDialog);
      mpBtnOK->setObjectName(QString::fromUtf8("mpBtnOK"));
      mpBtnOK->setAutoDefault(true);
      mpBtnOK->setDefault(true);

      hboxLayout->addWidget(mpBtnOK);

      mpBtnCancel = new QPushButton(CQTextDialog);
      mpBtnCancel->setObjectName(QString::fromUtf8("mpBtnCancel"));
      mpBtnCancel->setAutoDefault(true);

      hboxLayout->addWidget(mpBtnCancel);

      vboxLayout->addLayout(hboxLayout);

      retranslateUi(CQTextDialog);
      QObject::connect(mpBtnOK, SIGNAL(clicked()), CQTextDialog, SLOT(accept()));
      QObject::connect(mpBtnCancel, SIGNAL(clicked()), CQTextDialog, SLOT(reject()));

      QMetaObject::connectSlotsByName(CQTextDialog);
    } // setupUi

    void retranslateUi(QDialog *CQTextDialog)
    {
      CQTextDialog->setWindowTitle(QApplication::translate("CQTextDialog", "Text Dialog", 0, QApplication::UnicodeUTF8));
      mpBtnOK->setText(QApplication::translate("CQTextDialog", "&OK", 0, QApplication::UnicodeUTF8));
      mpBtnOK->setShortcut(QString());
      mpBtnCancel->setText(QApplication::translate("CQTextDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
      mpBtnCancel->setShortcut(QString());
      Q_UNUSED(CQTextDialog);
    } // retranslateUi
  };

namespace Ui
  {
  class CQTextDialog: public Ui_CQTextDialog {};
} // namespace Ui

class CQTextDialog : public QDialog, public Ui::CQTextDialog
  {
    Q_OBJECT

  public:
    CQTextDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~CQTextDialog();

    QString getText();

  protected slots:
    virtual void languageChange();
  };

#endif // CQTEXTDIALOG_H
