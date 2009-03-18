// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ui_CScanWidgetScan.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/03/18 12:54:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/*
 All rights reserved.
 */

/********************************************************************************
 ** Form generated from reading ui file 'CScanWidgetScan.ui'
 **
 ** Created: Fri Mar 13 10:23:53 2009
 **      by: Qt User Interface Compiler version 4.4.1
 **
 ** WARNING! All changes made in this file will be lost when recompiling ui file!
 ********************************************************************************/

#ifndef UI_CSCANWIDGETSCAN_H
#define UI_CSCANWIDGETSCAN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_CScanWidgetScan
{
public:
  QVBoxLayout *verticalLayout_2;
  QFrame *frame_2;
  QVBoxLayout *verticalLayout;
  QLabel *labelTitle;
  QHBoxLayout *hboxLayout;
  QLabel *labelObject;
  QLineEdit *lineEditObject;
  QToolButton *buttonObject;
  QGridLayout *gridLayout;
  QLabel *labelNumber;
  QLabel *labelMin;
  QLabel *labelMax;
  QLineEdit *lineEditNumber;
  QLineEdit *lineEditMin;
  QLineEdit *lineEditMax;
  QCheckBox *checkBoxLog;

  void setupUi(QWidget *CScanWidgetScan)
  {
    if (CScanWidgetScan->objectName().isEmpty())
      CScanWidgetScan->setObjectName(QString::fromUtf8("CScanWidgetScan"));

    CScanWidgetScan->resize(371, 196);
    verticalLayout_2 = new QVBoxLayout(CScanWidgetScan);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setMargin(11);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    frame_2 = new QFrame(CScanWidgetScan);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    QPalette palette;
    QBrush brush(QColor(207, 206, 249, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
    QBrush brush1(QColor(212, 208, 200, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
    frame_2->setPalette(palette);
    frame_2->setAutoFillBackground(true);
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    verticalLayout = new QVBoxLayout(frame_2);
    verticalLayout->setSpacing(6);
    verticalLayout->setMargin(11);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    labelTitle = new QLabel(frame_2);
    labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
    labelTitle->setAlignment(Qt::AlignTop);
    labelTitle->setWordWrap(true);

    verticalLayout->addWidget(labelTitle);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    labelObject = new QLabel(frame_2);
    labelObject->setObjectName(QString::fromUtf8("labelObject"));
    labelObject->setWordWrap(false);

    hboxLayout->addWidget(labelObject);

    lineEditObject = new QLineEdit(frame_2);
    lineEditObject->setObjectName(QString::fromUtf8("lineEditObject"));

    hboxLayout->addWidget(lineEditObject);

    buttonObject = new QToolButton(frame_2);
    buttonObject->setObjectName(QString::fromUtf8("buttonObject"));
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8("image0")), QIcon::Normal, QIcon::Off);
    buttonObject->setIcon(icon);

    hboxLayout->addWidget(buttonObject);

    verticalLayout->addLayout(hboxLayout);

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    labelNumber = new QLabel(frame_2);
    labelNumber->setObjectName(QString::fromUtf8("labelNumber"));
    labelNumber->setWordWrap(false);

    gridLayout->addWidget(labelNumber, 0, 0, 1, 1);

    labelMin = new QLabel(frame_2);
    labelMin->setObjectName(QString::fromUtf8("labelMin"));
    labelMin->setWordWrap(false);

    gridLayout->addWidget(labelMin, 0, 1, 1, 1);

    labelMax = new QLabel(frame_2);
    labelMax->setObjectName(QString::fromUtf8("labelMax"));
    labelMax->setWordWrap(false);

    gridLayout->addWidget(labelMax, 0, 2, 1, 1);

    lineEditNumber = new QLineEdit(frame_2);
    lineEditNumber->setObjectName(QString::fromUtf8("lineEditNumber"));

    gridLayout->addWidget(lineEditNumber, 1, 0, 1, 1);

    lineEditMin = new QLineEdit(frame_2);
    lineEditMin->setObjectName(QString::fromUtf8("lineEditMin"));

    gridLayout->addWidget(lineEditMin, 1, 1, 1, 1);

    lineEditMax = new QLineEdit(frame_2);
    lineEditMax->setObjectName(QString::fromUtf8("lineEditMax"));

    gridLayout->addWidget(lineEditMax, 1, 2, 1, 1);

    verticalLayout->addLayout(gridLayout);

    checkBoxLog = new QCheckBox(frame_2);
    checkBoxLog->setObjectName(QString::fromUtf8("checkBoxLog"));

    verticalLayout->addWidget(checkBoxLog);

    verticalLayout_2->addWidget(frame_2);

    retranslateUi(CScanWidgetScan);
    QObject::connect(buttonObject, SIGNAL(clicked()), CScanWidgetScan, SLOT(slotChooseObject()));

    QMetaObject::connectSlotsByName(CScanWidgetScan);
  } // setupUi

  void retranslateUi(QWidget *CScanWidgetScan)
  {
    CScanWidgetScan->setWindowTitle(QApplication::translate("CScanWidgetScan", "Form1", 0, QApplication::UnicodeUTF8));
    labelTitle->setText(QApplication::translate("CScanWidgetScan", "<h2>Scan</h2>", 0, QApplication::UnicodeUTF8));
    labelObject->setText(QApplication::translate("CScanWidgetScan", "Parameter", 0, QApplication::UnicodeUTF8));
    buttonObject->setText(QString());
    labelNumber->setText(QApplication::translate("CScanWidgetScan", "Intervals", 0, QApplication::UnicodeUTF8));
    labelMin->setText(QApplication::translate("CScanWidgetScan", "min", 0, QApplication::UnicodeUTF8));
    labelMax->setText(QApplication::translate("CScanWidgetScan", "max", 0, QApplication::UnicodeUTF8));
    checkBoxLog->setText(QApplication::translate("CScanWidgetScan", "logarithmic scan", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CScanWidgetScan);
  } // retranslateUi
};

namespace Ui
{
class CScanWidgetScan: public Ui_CScanWidgetScan {};
} // namespace Ui

#endif // UI_CSCANWIDGETSCAN_H
