// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQPrintAsDialog.h,v $
//   $Revision: 1.4.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:51 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPRINTASDIALOG_H
#define CQPRINTASDIALOG_H

#include <qvariant.h>

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class Ui_CQPrintAsDialog
{
public:
  QVBoxLayout *vboxLayout;
  Q3Frame *mpFrame;
  QGridLayout *gridLayout;
  QLabel *mpLabelType;
  QHBoxLayout *hboxLayout;
  QLineEdit *mpEditFileName;
  QPushButton *mpBtnBrowse;
  QLabel *mpLabelFileName;
  QHBoxLayout *hboxLayout1;
  QCheckBox *mpCBPNG;
  QCheckBox *mpCBSVG;
  QSpacerItem *spacer3;
  QHBoxLayout *hboxLayout2;
  QPushButton *mpBtnConfirm;
  QPushButton *mpBtnCancel;

  void setupUi(QDialog *CQPrintAsDialog)
  {
    if (CQPrintAsDialog->objectName().isEmpty())
      CQPrintAsDialog->setObjectName(QString::fromUtf8("CQPrintAsDialog"));

    CQPrintAsDialog->resize(514, 161);
    vboxLayout = new QVBoxLayout(CQPrintAsDialog);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    mpFrame = new Q3Frame(CQPrintAsDialog);
    mpFrame->setObjectName(QString::fromUtf8("mpFrame"));
    mpFrame->setFrameShape(Q3Frame::Box);
    mpFrame->setFrameShadow(Q3Frame::Sunken);
    gridLayout = new QGridLayout(mpFrame);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    mpLabelType = new QLabel(mpFrame);
    mpLabelType->setObjectName(QString::fromUtf8("mpLabelType"));
    mpLabelType->setWordWrap(false);

    gridLayout->addWidget(mpLabelType, 1, 0, 1, 1);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    mpEditFileName = new QLineEdit(mpFrame);
    mpEditFileName->setObjectName(QString::fromUtf8("mpEditFileName"));

    hboxLayout->addWidget(mpEditFileName);

    mpBtnBrowse = new QPushButton(mpFrame);
    mpBtnBrowse->setObjectName(QString::fromUtf8("mpBtnBrowse"));

    hboxLayout->addWidget(mpBtnBrowse);

    gridLayout->addLayout(hboxLayout, 0, 1, 1, 1);

    mpLabelFileName = new QLabel(mpFrame);
    mpLabelFileName->setObjectName(QString::fromUtf8("mpLabelFileName"));
    mpLabelFileName->setWordWrap(false);

    gridLayout->addWidget(mpLabelFileName, 0, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    mpCBPNG = new QCheckBox(mpFrame);
    mpCBPNG->setObjectName(QString::fromUtf8("mpCBPNG"));

    hboxLayout1->addWidget(mpCBPNG);

    mpCBSVG = new QCheckBox(mpFrame);
    mpCBSVG->setObjectName(QString::fromUtf8("mpCBSVG"));

    hboxLayout1->addWidget(mpCBSVG);

    spacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacer3);

    gridLayout->addLayout(hboxLayout1, 1, 1, 1, 1);

    vboxLayout->addWidget(mpFrame);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    mpBtnConfirm = new QPushButton(CQPrintAsDialog);
    mpBtnConfirm->setObjectName(QString::fromUtf8("mpBtnConfirm"));

    hboxLayout2->addWidget(mpBtnConfirm);

    mpBtnCancel = new QPushButton(CQPrintAsDialog);
    mpBtnCancel->setObjectName(QString::fromUtf8("mpBtnCancel"));

    hboxLayout2->addWidget(mpBtnCancel);

    vboxLayout->addLayout(hboxLayout2);

    retranslateUi(CQPrintAsDialog);
    QObject::connect(mpBtnConfirm, SIGNAL(clicked()), CQPrintAsDialog, SLOT(confirm()));
    QObject::connect(mpBtnCancel, SIGNAL(clicked()), CQPrintAsDialog, SLOT(reject()));
    QObject::connect(mpBtnBrowse, SIGNAL(clicked()), CQPrintAsDialog, SLOT(openFileDialog()));

    QMetaObject::connectSlotsByName(CQPrintAsDialog);
  } // setupUi

  void retranslateUi(QDialog *CQPrintAsDialog)
  {
    CQPrintAsDialog->setWindowTitle(QApplication::translate("CQPrintAsDialog", "Print As Image", 0, QApplication::UnicodeUTF8));
    mpLabelType->setText(QApplication::translate("CQPrintAsDialog", "as type of:", 0, QApplication::UnicodeUTF8));
    mpBtnBrowse->setText(QApplication::translate("CQPrintAsDialog", "browse", 0, QApplication::UnicodeUTF8));
    mpLabelFileName->setText(QApplication::translate("CQPrintAsDialog", "File Name:", 0, QApplication::UnicodeUTF8));
    mpCBPNG->setText(QApplication::translate("CQPrintAsDialog", "png", 0, QApplication::UnicodeUTF8));
    mpCBSVG->setText(QApplication::translate("CQPrintAsDialog", "svg", 0, QApplication::UnicodeUTF8));
    mpBtnConfirm->setText(QApplication::translate("CQPrintAsDialog", "Confirm", 0, QApplication::UnicodeUTF8));
    mpBtnCancel->setText(QApplication::translate("CQPrintAsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CQPrintAsDialog);
  } // retranslateUi
};

namespace Ui
{
class CQPrintAsDialog: public Ui_CQPrintAsDialog {};
} // namespace Ui

class CQPrintAsDialog : public QDialog, public Ui::CQPrintAsDialog
{
  Q_OBJECT

public:
  CQPrintAsDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQPrintAsDialog();

protected slots:


  void openFileDialog();
  void confirm();
};

#endif // CQPRINTASDIALOG_H
