// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMatrixDialog.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/07 19:43:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMATRIXDIALOG_H
#define CQMATRIXDIALOG_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

class CArrayAnnotation;

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CQMatrixDialog
  {
  public:
    Q3VBoxLayout *vboxLayout;
    QLabel *mpLabelRow;
    QComboBox *mpCBRow;
    QLabel *mpLabelColumn;
    QComboBox *mpCBColumn;
    QLabel *mpLabelDim3;
    QComboBox *mpCBDim3;
    QSpacerItem *spacer1;
    Q3Frame *line1;
    Q3HBoxLayout *hboxLayout;
    QPushButton *mpOKBtn;
    QPushButton *mpCancelBtn;

    void setupUi(QDialog *CQMatrixDialog)
    {
      if (CQMatrixDialog->objectName().isEmpty())
        CQMatrixDialog->setObjectName(QString::fromUtf8("CQMatrixDialog"));
      CQMatrixDialog->resize(425, 211);
      vboxLayout = new Q3VBoxLayout(CQMatrixDialog);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      mpLabelRow = new QLabel(CQMatrixDialog);
      mpLabelRow->setObjectName(QString::fromUtf8("mpLabelRow"));
      mpLabelRow->setWordWrap(false);

      vboxLayout->addWidget(mpLabelRow);

      mpCBRow = new QComboBox(CQMatrixDialog);
      mpCBRow->setObjectName(QString::fromUtf8("mpCBRow"));

      vboxLayout->addWidget(mpCBRow);

      mpLabelColumn = new QLabel(CQMatrixDialog);
      mpLabelColumn->setObjectName(QString::fromUtf8("mpLabelColumn"));
      mpLabelColumn->setWordWrap(false);

      vboxLayout->addWidget(mpLabelColumn);

      mpCBColumn = new QComboBox(CQMatrixDialog);
      mpCBColumn->setObjectName(QString::fromUtf8("mpCBColumn"));

      vboxLayout->addWidget(mpCBColumn);

      mpLabelDim3 = new QLabel(CQMatrixDialog);
      mpLabelDim3->setObjectName(QString::fromUtf8("mpLabelDim3"));
      mpLabelDim3->setWordWrap(false);

      vboxLayout->addWidget(mpLabelDim3);

      mpCBDim3 = new QComboBox(CQMatrixDialog);
      mpCBDim3->setObjectName(QString::fromUtf8("mpCBDim3"));

      vboxLayout->addWidget(mpCBDim3);

      spacer1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout->addItem(spacer1);

      line1 = new Q3Frame(CQMatrixDialog);
      line1->setObjectName(QString::fromUtf8("line1"));
      line1->setFrameShape(Q3Frame::HLine);
      line1->setFrameShadow(Q3Frame::Sunken);

      vboxLayout->addWidget(line1);

      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpOKBtn = new QPushButton(CQMatrixDialog);
      mpOKBtn->setObjectName(QString::fromUtf8("mpOKBtn"));

      hboxLayout->addWidget(mpOKBtn);

      mpCancelBtn = new QPushButton(CQMatrixDialog);
      mpCancelBtn->setObjectName(QString::fromUtf8("mpCancelBtn"));

      hboxLayout->addWidget(mpCancelBtn);

      vboxLayout->addLayout(hboxLayout);

      retranslateUi(CQMatrixDialog);
      QObject::connect(mpOKBtn, SIGNAL(clicked()), CQMatrixDialog, SLOT(accept()));
      QObject::connect(mpCancelBtn, SIGNAL(clicked()), CQMatrixDialog, SLOT(close()));

      QMetaObject::connectSlotsByName(CQMatrixDialog);
    } // setupUi

    void retranslateUi(QDialog *CQMatrixDialog)
    {
      CQMatrixDialog->setWindowTitle(QApplication::translate("CQMatrixDialog", "Cell Matrix Selection Dialog", 0, QApplication::UnicodeUTF8));
      mpLabelRow->setText(QApplication::translate("CQMatrixDialog", "Row :", 0, QApplication::UnicodeUTF8));
      mpLabelColumn->setText(QApplication::translate("CQMatrixDialog", "Column :", 0, QApplication::UnicodeUTF8));
      mpLabelDim3->setText(QApplication::translate("CQMatrixDialog", "Dimension 3 :", 0, QApplication::UnicodeUTF8));
      mpOKBtn->setText(QApplication::translate("CQMatrixDialog", "OK", 0, QApplication::UnicodeUTF8));
      mpCancelBtn->setText(QApplication::translate("CQMatrixDialog", "Cancel", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQMatrixDialog);
    } // retranslateUi
  };

namespace Ui
  {
  class CQMatrixDialog: public Ui_CQMatrixDialog {};
} // namespace Ui

QT_END_NAMESPACE

class CQMatrixDialog : public QDialog, public Ui::CQMatrixDialog
  {
    Q_OBJECT

  public:
    CQMatrixDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~CQMatrixDialog();

  public slots:
    virtual void setArray(const CArrayAnnotation * tmp, bool single);

  protected slots:
    virtual void languageChange();
  };

#endif // CQMATRIXDIALOG_H
