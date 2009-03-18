// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ui_CScanWidgetTask.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/03/18 12:58:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/*
 All rights reserved.
 */

/********************************************************************************
 ** Form generated from reading ui file 'CScanWidgetTask.ui'
 **
 ** Created: Fri Mar 13 15:24:49 2009
 **      by: Qt User Interface Compiler version 4.4.1
 **
 ** WARNING! All changes made in this file will be lost when recompiling ui file!
 ********************************************************************************/

#ifndef UI_CSCANWIDGETTASK_H
#define UI_CSCANWIDGETTASK_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_CScanWidgetTask
{
public:
  QVBoxLayout *verticalLayout_2;
  QFrame *frame;
  QVBoxLayout *verticalLayout;
  QHBoxLayout *hboxLayout;
  QLabel *labelTitle;
  QSpacerItem *spacer1;
  QComboBox *comboType;
  QSpacerItem *spacer2;
  QHBoxLayout *hboxLayout1;
  QCheckBox *checkInitialConditions;
  QSpacerItem *spacer3;
  QCheckBox *checkOutput;
  QSpacerItem *spacer4;

  void setupUi(QWidget *CScanWidgetTask)
  {
    if (CScanWidgetTask->objectName().isEmpty())
      CScanWidgetTask->setObjectName(QString::fromUtf8("CScanWidgetTask"));

    CScanWidgetTask->resize(501, 119);
    CScanWidgetTask->setAutoFillBackground(false);
    verticalLayout_2 = new QVBoxLayout(CScanWidgetTask);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setMargin(11);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    frame = new QFrame(CScanWidgetTask);
    frame->setObjectName(QString::fromUtf8("frame"));
    QPalette palette;
    QBrush brush(QColor(191, 236, 183, 255));
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
    verticalLayout = new QVBoxLayout(frame);
    verticalLayout->setSpacing(6);
    verticalLayout->setMargin(11);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    labelTitle = new QLabel(frame);
    labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
    labelTitle->setWordWrap(false);

    hboxLayout->addWidget(labelTitle);

    spacer1 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

    hboxLayout->addItem(spacer1);

    comboType = new QComboBox(frame);
    comboType->setObjectName(QString::fromUtf8("comboType"));

    hboxLayout->addWidget(comboType);

    spacer2 = new QSpacerItem(99, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacer2);

    verticalLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    checkInitialConditions = new QCheckBox(frame);
    checkInitialConditions->setObjectName(QString::fromUtf8("checkInitialConditions"));
    checkInitialConditions->setChecked(true);

    hboxLayout1->addWidget(checkInitialConditions);

    spacer3 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacer3);

    checkOutput = new QCheckBox(frame);
    checkOutput->setObjectName(QString::fromUtf8("checkOutput"));
    checkOutput->setChecked(true);

    hboxLayout1->addWidget(checkOutput);

    spacer4 = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacer4);

    verticalLayout->addLayout(hboxLayout1);

    verticalLayout_2->addWidget(frame);

    retranslateUi(CScanWidgetTask);
    QObject::connect(comboType, SIGNAL(activated(int)), CScanWidgetTask, SLOT(typeChanged(int)));

    comboType->setCurrentIndex(1);

    QMetaObject::connectSlotsByName(CScanWidgetTask);
  } // setupUi

  void retranslateUi(QWidget *CScanWidgetTask)
  {
    CScanWidgetTask->setWindowTitle(QApplication::translate("CScanWidgetTask", "Form1", 0, QApplication::UnicodeUTF8));
    labelTitle->setText(QApplication::translate("CScanWidgetTask", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                        "p, li {white-space: pre-wrap; }\n"
                        "</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
                        "<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:x-large; font-weight:600;\"><span style=\" font-size:x-large;\">Task</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    comboType->clear();
    comboType->insertItems(0, QStringList()
                           << QApplication::translate("CScanWidgetTask", "Steady State", 0, QApplication::UnicodeUTF8)
                           << QApplication::translate("CScanWidgetTask", "Time course", 0, QApplication::UnicodeUTF8)
                           << QApplication::translate("CScanWidgetTask", "Metabolic control analysis", 0, QApplication::UnicodeUTF8)
                           << QApplication::translate("CScanWidgetTask", "Lyapunov exponents", 0, QApplication::UnicodeUTF8)
                           << QApplication::translate("CScanWidgetTask", "Optimization", 0, QApplication::UnicodeUTF8)
                           << QApplication::translate("CScanWidgetTask", "Parameter Estimation", 0, QApplication::UnicodeUTF8)
                           << QApplication::translate("CScanWidgetTask", "Sensitivities", 0, QApplication::UnicodeUTF8)
                          );

#ifndef QT_NO_TOOLTIP
    checkInitialConditions->setToolTip(QApplication::translate("CScanWidgetTask", "If this is activated every calculation will start with the initial conditions specified in the model. <p>If it is not activated only the first calculation will use the initial value specified in the model. All subsequent calculations will start with the result of the previous calculation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    checkInitialConditions->setText(QApplication::translate("CScanWidgetTask", "always use initial conditions", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
    checkOutput->setToolTip(QApplication::translate("CScanWidgetTask", "If this is activated output will be generated during each calculation. <p>If it is not activated only the state at the end of each calculation will be plotted.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    checkOutput->setText(QApplication::translate("CScanWidgetTask", "output during subtask execution", 0, QApplication::UnicodeUTF8));
    checkOutput->setShortcut(QString());
    Q_UNUSED(CScanWidgetTask);
  } // retranslateUi
};

namespace Ui
{
class CScanWidgetTask: public Ui_CScanWidgetTask {};
} // namespace Ui

#endif // UI_CSCANWIDGETTASK_H
