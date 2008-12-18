// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CQProgressItem.h,v $
//   $Revision: 1.2.28.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPROGRESSITEM_H
#define CQPROGRESSITEM_H

#include <qvariant.h>

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QWidget>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include "utilities/CProcessReport.h"
#include "utilities/CVector.h"

QT_BEGIN_NAMESPACE

class Ui_CQProgressItem
  {
  public:
    QWidget *mLabel;
    Q3HBoxLayout *hboxLayout;

    void setupUi(QWidget *CQProgressItem)
    {
      if (CQProgressItem->objectName().isEmpty())
        CQProgressItem->setObjectName(QString::fromUtf8("CQProgressItem"));
      CQProgressItem->resize(404, 44);
      mLabel = new QWidget(CQProgressItem);
      mLabel->setObjectName(QString::fromUtf8("mLabel"));
      mLabel->setGeometry(QRect(10, 10, 330, 22));
      hboxLayout = new Q3HBoxLayout(mLabel);
      hboxLayout->setSpacing(6);
      hboxLayout->setMargin(11);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      hboxLayout->setContentsMargins(0, 0, 0, 0);

      retranslateUi(CQProgressItem);

      QMetaObject::connectSlotsByName(CQProgressItem);
    } // setupUi

    void retranslateUi(QWidget *CQProgressItem)
    {
      CQProgressItem->setWindowTitle(QApplication::translate("CQProgressItem", "Form1", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQProgressItem);
    } // retranslateUi
  };

namespace Ui
  {
  class CQProgressItem: public Ui_CQProgressItem {};
} // namespace Ui

QT_END_NAMESPACE

class CQProgressItem : public QWidget, public Ui::CQProgressItem
  {
    Q_OBJECT

  public:
    CQProgressItem(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CQProgressItem();

    virtual bool initFromProcessReportItem(CProcessReportItem * pItem);
    virtual bool process();
    virtual bool reset();

  protected:
    CProcessReportItem * mpItem;

  protected slots:
    virtual void languageChange();
  };

#endif // CQPROGRESSITEM_H
