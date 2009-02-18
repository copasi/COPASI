// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressDialog.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:47:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPROGRESSDIALOG_H
#define CQPROGRESSDIALOG_H

#include <qvariant.h>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QDialog>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <QPixmap>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <Q3Frame>
#include "CQProgressItem.h"

class Ui_CQProgressDialog
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3HBoxLayout *hboxLayout;
    QPushButton *mpBtnPause;
    QPushButton *mpBtnContinue;
    QPushButton *mpBtnStop;
    QSpacerItem *mpBtnSpacer;
    Q3Frame *mpLine;
    QSpacerItem *mpSpacer;

    void setupUi(QDialog *CQProgressDialog)
    {
      if (CQProgressDialog->objectName().isEmpty())
        CQProgressDialog->setObjectName(QString::fromUtf8("CQProgressDialog"));
      CQProgressDialog->resize(363, 57);
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(7));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(CQProgressDialog->sizePolicy().hasHeightForWidth());
      CQProgressDialog->setSizePolicy(sizePolicy);
      CQProgressDialog->setMinimumSize(QSize(300, 57));
      vboxLayout = new Q3VBoxLayout(CQProgressDialog);
      vboxLayout->setSpacing(3);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpBtnPause = new QPushButton(CQProgressDialog);
      mpBtnPause->setObjectName(QString::fromUtf8("mpBtnPause"));
      QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(mpBtnPause->sizePolicy().hasHeightForWidth());
      mpBtnPause->setSizePolicy(sizePolicy1);
      mpBtnPause->setIcon(qt_get_icon(image0_ID));

      hboxLayout->addWidget(mpBtnPause);

      mpBtnContinue = new QPushButton(CQProgressDialog);
      mpBtnContinue->setObjectName(QString::fromUtf8("mpBtnContinue"));
      sizePolicy1.setHeightForWidth(mpBtnContinue->sizePolicy().hasHeightForWidth());
      mpBtnContinue->setSizePolicy(sizePolicy1);
      mpBtnContinue->setIcon(qt_get_icon(image1_ID));

      hboxLayout->addWidget(mpBtnContinue);

      mpBtnStop = new QPushButton(CQProgressDialog);
      mpBtnStop->setObjectName(QString::fromUtf8("mpBtnStop"));
      sizePolicy1.setHeightForWidth(mpBtnStop->sizePolicy().hasHeightForWidth());
      mpBtnStop->setSizePolicy(sizePolicy1);
      mpBtnStop->setIcon(qt_get_icon(image2_ID));

      hboxLayout->addWidget(mpBtnStop);

      mpBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      hboxLayout->addItem(mpBtnSpacer);

      vboxLayout->addLayout(hboxLayout);

      mpLine = new Q3Frame(CQProgressDialog);
      mpLine->setObjectName(QString::fromUtf8("mpLine"));
      mpLine->setMinimumSize(QSize(200, 0));
      mpLine->setFrameShape(Q3Frame::HLine);
      mpLine->setFrameShadow(Q3Frame::Sunken);

      vboxLayout->addWidget(mpLine);

      mpSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout->addItem(mpSpacer);

      QWidget::setTabOrder(mpBtnStop, mpBtnPause);
      QWidget::setTabOrder(mpBtnPause, mpBtnContinue);

      retranslateUi(CQProgressDialog);
      QObject::connect(mpBtnStop, SIGNAL(clicked()), CQProgressDialog, SLOT(btnStopPressed()));
      QObject::connect(mpBtnPause, SIGNAL(clicked()), CQProgressDialog, SLOT(btnPausePressed()));
      QObject::connect(mpBtnContinue, SIGNAL(clicked()), CQProgressDialog, SLOT(btnContinuePressed()));

      QMetaObject::connectSlotsByName(CQProgressDialog);
    } // setupUi

    void retranslateUi(QDialog *CQProgressDialog)
    {
      CQProgressDialog->setWindowTitle(QApplication::translate("CQProgressDialog", "COPASI Progress Dialog", 0, QApplication::UnicodeUTF8));
      mpBtnPause->setText(QString());
      mpBtnContinue->setText(QString());
      mpBtnStop->setText(QString());
      Q_UNUSED(CQProgressDialog);
    } // retranslateUi

  protected:
    enum IconID
    {
      image0_ID,
      image1_ID,
      image2_ID,
      unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
      static const unsigned char image0_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
          0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x00,
          0x31, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0xfc, 0xff, 0xff, 0x3f,
          0x03, 0x25, 0x80, 0x89, 0x22, 0xdd, 0x83, 0xc2, 0x00, 0x16, 0x74, 0x01,
          0x46, 0x46, 0x46, 0x78, 0xa0, 0xfc, 0xff, 0xff, 0x9f, 0x11, 0x97, 0x18,
          0xd5, 0x5c, 0x30, 0x6a, 0xc0, 0x60, 0x30, 0x80, 0x71, 0x34, 0x2f, 0x30,
          0x00, 0x00, 0xa1, 0x5e, 0x0e, 0x1b, 0xc0, 0x83, 0x3e, 0xb5, 0x00, 0x00,
          0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      static const unsigned char image1_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
          0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x00,
          0x41, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0xac, 0xe0,
          0x3f, 0xb1, 0x0a, 0x99, 0x28, 0x35, 0x04, 0x9f, 0x01, 0x44, 0x19, 0x42,
          0xc8, 0x00, 0x82, 0x86, 0x10, 0x63, 0x00, 0x5e, 0x43, 0x88, 0x35, 0x00,
          0xa7, 0x21, 0xa4, 0x18, 0x40, 0xb1, 0x0b, 0x18, 0x29, 0x31, 0x00, 0xab,
          0x66, 0x62, 0x0d, 0xc0, 0xa9, 0x99, 0x18, 0x03, 0xf0, 0x6a, 0xc6, 0x07,
          0x88, 0x4e, 0xca, 0x03, 0x0f, 0x00, 0x87, 0xd3, 0x07, 0x12, 0x18, 0xc5,
          0xb3, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
          0x60, 0x82
        };

      static const unsigned char image2_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
          0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x00,
          0x2f, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0xfc, 0xff, 0xff, 0x3f,
          0x03, 0x25, 0x80, 0x89, 0x22, 0xdd, 0x83, 0xc2, 0x00, 0x16, 0x74, 0x01,
          0x46, 0x46, 0x46, 0xbc, 0x81, 0xf2, 0xff, 0xff, 0x7f, 0x46, 0xaa, 0xba,
          0x60, 0xd4, 0x80, 0xc1, 0x60, 0x00, 0xe3, 0x68, 0x5e, 0x60, 0x00, 0x00,
          0xf2, 0xba, 0x0a, 0x1b, 0x43, 0x7a, 0xe1, 0x23, 0x00, 0x00, 0x00, 0x00,
          0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      switch (id)
        {
        case image0_ID: {QImage img; img.loadFromData(image0_data, sizeof(image0_data), "PNG"); return QPixmap::fromImage(img);}
        case image1_ID: {QImage img; img.loadFromData(image1_data, sizeof(image1_data), "PNG"); return QPixmap::fromImage(img);}
        case image2_ID: {QImage img; img.loadFromData(image2_data, sizeof(image2_data), "PNG"); return QPixmap::fromImage(img);}
        default: return QPixmap();
        } // switch
    } // icon
  };

namespace Ui
  {
  class CQProgressDialog: public Ui_CQProgressDialog {};
} // namespace Ui

class CQProgressDialog : public QDialog, public Ui::CQProgressDialog
  {
    Q_OBJECT

  public:
    CQProgressDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~CQProgressDialog();

    bool insertProgressItem(CQProgressItem * pItem);
    bool removeProgressItem(CQProgressItem * pItem);

  protected:
    bool mProceed;
    bool mPause;
    QTimer *mpTimer;

  protected slots:
    virtual void languageChange();

    void btnStopPressed();
    void btnPausePressed();
    void btnContinuePressed();
    void timerShow();

  private:
    unsigned C_INT32 mItemCount;

    void init();
  };

#endif // CQPROGRESSDIALOG_H
