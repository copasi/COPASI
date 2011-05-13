// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQRegistrationDialog.h,v $
//   $Revision: 1.3.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:59 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQREGISTRATIONDIALOG_H
#define CQREGISTRATIONDIALOG_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

class CRegistration;

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QDialog>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>

class Ui_CQRegistrationDialog
{
public:
  Q3VBoxLayout *vboxLayout;
  Q3GridLayout *gridLayout;
  QLabel *mpLblDate;
  QLabel *mpLblEmail;
  QLineEdit *mpEditName;
  QLabel *mpLblName;
  QLabel *mpLblCode;
  QLineEdit *mpEditStatus;
  Q3Frame *mpLine;
  QLineEdit *mpEditEmail;
  QLineEdit *mpEditDate;
  QLineEdit *mpEditCode;
  QLabel *mpLblStatus;
  QSpacerItem *mpSpacerVertical;
  Q3HBoxLayout *hboxLayout;
  QPushButton *mpBtnValidate;
  QSpacerItem *mpSpacerBtn;
  QPushButton *mpBtnOk;
  QPushButton *mpBtnCancel;

  void setupUi(QDialog *CQRegistrationDialog)
  {
    if (CQRegistrationDialog->objectName().isEmpty())
      CQRegistrationDialog->setObjectName(QString::fromUtf8("CQRegistrationDialog"));

    CQRegistrationDialog->resize(514, 253);
    CQRegistrationDialog->setSizeGripEnabled(true);
    vboxLayout = new Q3VBoxLayout(CQRegistrationDialog);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    gridLayout = new Q3GridLayout(1, 1);
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    mpLblDate = new QLabel(CQRegistrationDialog);
    mpLblDate->setObjectName(QString::fromUtf8("mpLblDate"));
    mpLblDate->setEnabled(true);
    mpLblDate->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    mpLblDate->setWordWrap(false);

    gridLayout->addWidget(mpLblDate, 5, 0, 1, 1);

    mpLblEmail = new QLabel(CQRegistrationDialog);
    mpLblEmail->setObjectName(QString::fromUtf8("mpLblEmail"));
    mpLblEmail->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    mpLblEmail->setWordWrap(false);

    gridLayout->addWidget(mpLblEmail, 1, 0, 1, 1);

    mpEditName = new QLineEdit(CQRegistrationDialog);
    mpEditName->setObjectName(QString::fromUtf8("mpEditName"));

    gridLayout->addWidget(mpEditName, 0, 1, 1, 1);

    mpLblName = new QLabel(CQRegistrationDialog);
    mpLblName->setObjectName(QString::fromUtf8("mpLblName"));
    mpLblName->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    mpLblName->setWordWrap(false);

    gridLayout->addWidget(mpLblName, 0, 0, 1, 1);

    mpLblCode = new QLabel(CQRegistrationDialog);
    mpLblCode->setObjectName(QString::fromUtf8("mpLblCode"));
    mpLblCode->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    mpLblCode->setWordWrap(false);

    gridLayout->addWidget(mpLblCode, 2, 0, 1, 1);

    mpEditStatus = new QLineEdit(CQRegistrationDialog);
    mpEditStatus->setObjectName(QString::fromUtf8("mpEditStatus"));
    mpEditStatus->setEnabled(false);

    gridLayout->addWidget(mpEditStatus, 4, 1, 1, 1);

    mpLine = new Q3Frame(CQRegistrationDialog);
    mpLine->setObjectName(QString::fromUtf8("mpLine"));
    mpLine->setFrameShape(Q3Frame::HLine);
    mpLine->setFrameShadow(Q3Frame::Sunken);

    gridLayout->addWidget(mpLine, 3, 0, 1, 2);

    mpEditEmail = new QLineEdit(CQRegistrationDialog);
    mpEditEmail->setObjectName(QString::fromUtf8("mpEditEmail"));

    gridLayout->addWidget(mpEditEmail, 1, 1, 1, 1);

    mpEditDate = new QLineEdit(CQRegistrationDialog);
    mpEditDate->setObjectName(QString::fromUtf8("mpEditDate"));
    mpEditDate->setEnabled(false);

    gridLayout->addWidget(mpEditDate, 5, 1, 1, 1);

    mpEditCode = new QLineEdit(CQRegistrationDialog);
    mpEditCode->setObjectName(QString::fromUtf8("mpEditCode"));

    gridLayout->addWidget(mpEditCode, 2, 1, 1, 1);

    mpLblStatus = new QLabel(CQRegistrationDialog);
    mpLblStatus->setObjectName(QString::fromUtf8("mpLblStatus"));
    mpLblStatus->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    mpLblStatus->setWordWrap(false);

    gridLayout->addWidget(mpLblStatus, 4, 0, 1, 1);

    vboxLayout->addLayout(gridLayout);

    mpSpacerVertical = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(mpSpacerVertical);

    hboxLayout = new Q3HBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    mpBtnValidate = new QPushButton(CQRegistrationDialog);
    mpBtnValidate->setObjectName(QString::fromUtf8("mpBtnValidate"));
    mpBtnValidate->setAutoDefault(true);

    hboxLayout->addWidget(mpBtnValidate);

    mpSpacerBtn = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(mpSpacerBtn);

    mpBtnOk = new QPushButton(CQRegistrationDialog);
    mpBtnOk->setObjectName(QString::fromUtf8("mpBtnOk"));
    mpBtnOk->setAutoDefault(true);
    mpBtnOk->setDefault(true);

    hboxLayout->addWidget(mpBtnOk);

    mpBtnCancel = new QPushButton(CQRegistrationDialog);
    mpBtnCancel->setObjectName(QString::fromUtf8("mpBtnCancel"));
    mpBtnCancel->setAutoDefault(true);

    hboxLayout->addWidget(mpBtnCancel);

    vboxLayout->addLayout(hboxLayout);

    retranslateUi(CQRegistrationDialog);
    QObject::connect(mpBtnOk, SIGNAL(clicked()), CQRegistrationDialog, SLOT(slotBtnOk()));
    QObject::connect(mpBtnCancel, SIGNAL(clicked()), CQRegistrationDialog, SLOT(slotBtnCancel()));
    QObject::connect(mpBtnValidate, SIGNAL(clicked()), CQRegistrationDialog, SLOT(slotBtnValidate()));

    QMetaObject::connectSlotsByName(CQRegistrationDialog);
  } // setupUi

  void retranslateUi(QDialog *CQRegistrationDialog)
  {
    CQRegistrationDialog->setWindowTitle(QApplication::translate("CQRegistrationDialog", "Registration", 0, QApplication::UnicodeUTF8));
    mpLblDate->setText(QApplication::translate("CQRegistrationDialog", "Expiration Date", 0, QApplication::UnicodeUTF8));
    mpLblEmail->setText(QApplication::translate("CQRegistrationDialog", "Email", 0, QApplication::UnicodeUTF8));
    mpLblName->setText(QApplication::translate("CQRegistrationDialog", "User Name", 0, QApplication::UnicodeUTF8));
    mpLblCode->setText(QApplication::translate("CQRegistrationDialog", "Registration Code", 0, QApplication::UnicodeUTF8));
    mpLblStatus->setText(QApplication::translate("CQRegistrationDialog", "License Status", 0, QApplication::UnicodeUTF8));
    mpBtnValidate->setText(QApplication::translate("CQRegistrationDialog", "Validate", 0, QApplication::UnicodeUTF8));
    mpBtnValidate->setShortcut(QString());
    mpBtnOk->setText(QApplication::translate("CQRegistrationDialog", "&OK", 0, QApplication::UnicodeUTF8));
    mpBtnOk->setShortcut(QString());
    mpBtnCancel->setText(QApplication::translate("CQRegistrationDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
    mpBtnCancel->setShortcut(QString());
    Q_UNUSED(CQRegistrationDialog);
  } // retranslateUi
};

namespace Ui
{
class CQRegistrationDialog: public Ui_CQRegistrationDialog {};
} // namespace Ui

class CQRegistrationDialog : public QDialog, public Ui::CQRegistrationDialog
{
  Q_OBJECT

public:
  CQRegistrationDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQRegistrationDialog();

protected slots:


private:
  CRegistration * mpRegistration;

  void init();
  void destroy();

private slots:
  void slotBtnValidate();
  void slotBtnOk();
  void slotBtnCancel();
};

#endif // CQREGISTRATIONDIALOG_H
