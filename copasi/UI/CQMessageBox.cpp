// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMessageBox.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/16 19:51:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QStyle>

#include "CQMessageBox.h"

CQMessageBox::CQMessageBox(Icon icon, const QString &title, const QString &text,
                           QMessageBox::StandardButtons buttons, QWidget *parent,
                           Qt::WindowFlags f):
    QMessageBox(icon, title, QString(), buttons, parent, f),
    mpTabWidget(NULL),
    mpPage1(NULL),
    mpVerticalLayoutPage1(NULL),
    mpText1(NULL),
    mpPage2(NULL),
    mpVerticalLayoutPage2(NULL),
    mpText2(NULL)
{
  mpTabWidget = new QTabWidget(this);
  mpTabWidget->setObjectName(QString::fromUtf8("mpTabWidget"));
  mpTabWidget->setMinimumSize(QSize(400, 200));

  mpPage1 = new QWidget();
  mpPage1->setObjectName(QString::fromUtf8("mpPage1"));

  mpVerticalLayoutPage1 = new QVBoxLayout(mpPage1);
  mpVerticalLayoutPage1->setMargin(2);
  mpVerticalLayoutPage1->setObjectName(QString::fromUtf8("mpVerticalLayoutPage1"));

  mpText1 = new QTextEdit(mpPage1);
  mpText1->setObjectName(QString::fromUtf8("mpText1"));
  mpText1->setReadOnly(true);
  mpText1->setText(text);
  mpVerticalLayoutPage1->addWidget(mpText1);

  mpTabWidget->addTab(mpPage1, QString("Messages"));

  // The code below is derived from qt-4.4.3/src/gui/dialogs/qmessagebox.cpp
  static_cast<QGridLayout *>(layout())->addWidget(mpTabWidget, 0, 1, 1, 1);
  QLabel * pLabel = findChild<QLabel *>("qt_msgbox_label");
  if (pLabel != NULL)
    pLabel->hide();
}

// static
QMessageBox::StandardButton CQMessageBox::information(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Information, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  StandardButton choice = (StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

QMessageBox::StandardButton CQMessageBox::question(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Question, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  StandardButton choice = (StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

// static
QMessageBox::StandardButton CQMessageBox::warning(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Warning, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  StandardButton choice = (StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

// static
QMessageBox::StandardButton CQMessageBox::critical(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Critical, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  StandardButton choice = (StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

void CQMessageBox::setText(const QString & text)
{
  mpText1->setText(text);
}

void CQMessageBox::setFilteredText(const QString & text)
{
  if (!text.isEmpty() && mpPage2 == NULL)
    {
      mpPage2 = new QWidget();
      mpPage2->setObjectName(QString::fromUtf8("mpPage2"));

      mpVerticalLayoutPage2 = new QVBoxLayout(mpPage2);
      mpVerticalLayoutPage2->setMargin(2);
      mpVerticalLayoutPage2->setObjectName(QString::fromUtf8("mpVerticalLayoutPage2"));

      mpText2 = new QTextEdit(mpPage2);
      mpText2->setObjectName(QString::fromUtf8("mpText2"));
      mpText2->setReadOnly(true);
      mpVerticalLayoutPage2->addWidget(mpText2);
      mpTabWidget->addTab(mpPage2, QString("Minor Issues"));
    }

  mpText2->setText(text);
}
