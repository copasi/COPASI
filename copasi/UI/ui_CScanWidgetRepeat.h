// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ui_CScanWidgetRepeat.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/03/18 12:54:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/********************************************************************************
 ** Form generated from reading ui file 'CScanWidgetRepeat.ui'
 **
 ** Created: Fri Mar 13 15:53:52 2009
 **      by: Qt User Interface Compiler version 4.4.1
 **
 ** WARNING! All changes made in this file will be lost when recompiling ui file!
 ********************************************************************************/

#ifndef UI_CSCANWIDGETREPEAT_H
#define UI_CSCANWIDGETREPEAT_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_CScanWidgetRepeat
{
public:
  QVBoxLayout *verticalLayout;
  QFrame *frame;
  QHBoxLayout *horizontalLayout;
  QLabel *labelTitle;
  QSpacerItem *spacer1;
  QLabel *labelNumber;
  QLineEdit *lineEditNumber;

  void setupUi(QWidget *CScanWidgetRepeat)
  {
    if (CScanWidgetRepeat->objectName().isEmpty())
      CScanWidgetRepeat->setObjectName(QString::fromUtf8("CScanWidgetRepeat"));

    CScanWidgetRepeat->resize(417, 80);
    verticalLayout = new QVBoxLayout(CScanWidgetRepeat);
    verticalLayout->setSpacing(6);
    verticalLayout->setMargin(11);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    frame = new QFrame(CScanWidgetRepeat);
    frame->setObjectName(QString::fromUtf8("frame"));
    QPalette palette;
    QBrush brush(QColor(207, 206, 249, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
    QBrush brush1(QColor(212, 208, 200, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
    frame->setPalette(palette);
    frame->setAutoFillBackground(true);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    horizontalLayout = new QHBoxLayout(frame);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setMargin(11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    labelTitle = new QLabel(frame);
    labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
    labelTitle->setAlignment(Qt::AlignVCenter);
    labelTitle->setWordWrap(true);

    horizontalLayout->addWidget(labelTitle);

    spacer1 = new QSpacerItem(1, 25, QSizePolicy::Maximum, QSizePolicy::Minimum);

    horizontalLayout->addItem(spacer1);

    labelNumber = new QLabel(frame);
    labelNumber->setObjectName(QString::fromUtf8("labelNumber"));
    labelNumber->setWordWrap(false);

    horizontalLayout->addWidget(labelNumber);

    lineEditNumber = new QLineEdit(frame);
    lineEditNumber->setObjectName(QString::fromUtf8("lineEditNumber"));

    horizontalLayout->addWidget(lineEditNumber);

    verticalLayout->addWidget(frame);

    frame->raise();
    frame->raise();
    lineEditNumber->raise();

    retranslateUi(CScanWidgetRepeat);

    QMetaObject::connectSlotsByName(CScanWidgetRepeat);
  } // setupUi

  void retranslateUi(QWidget *CScanWidgetRepeat)
  {
    CScanWidgetRepeat->setWindowTitle(QApplication::translate("CScanWidgetRepeat", "Form1", 0, QApplication::UnicodeUTF8));
    labelTitle->setText(QApplication::translate("CScanWidgetRepeat", "<h2>Repeat</h2>", 0, QApplication::UnicodeUTF8));
    labelNumber->setText(QApplication::translate("CScanWidgetRepeat", "Number of iterations", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CScanWidgetRepeat);
  } // retranslateUi
};

namespace Ui
{
class CScanWidgetRepeat: public Ui_CScanWidgetRepeat {};
} // namespace Ui

#endif // UI_CSCANWIDGETREPEAT_H
