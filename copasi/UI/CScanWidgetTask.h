// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetTask.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CScanWidgetTask.ui'
 **
 ** Created: Wed Oct 8 02:15:43 2008
 **      by: The User Interface Compiler ($Id: CScanWidgetTask.h,v 1.12 2008/12/18 19:57:33 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CSCANWIDGETTASK_H
#define CSCANWIDGETTASK_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

class CModel;
class CCopasiObject;
class CScanProblem;

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CScanWidgetTask
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3Frame *frame;
    Q3VBoxLayout *vboxLayout1;
    Q3HBoxLayout *hboxLayout;
    QLabel *labelTitle;
    QSpacerItem *spacer1;
    QComboBox *comboType;
    QSpacerItem *spacer2;
    Q3HBoxLayout *hboxLayout1;
    QCheckBox *checkInitialConditions;
    QSpacerItem *spacer3;
    QCheckBox *checkOutput;
    QSpacerItem *spacer4;

    void setupUi(QWidget *CScanWidgetTask)
    {
      if (CScanWidgetTask->objectName().isEmpty())
        CScanWidgetTask->setObjectName(QString::fromUtf8("CScanWidgetTask"));
      CScanWidgetTask->resize(374, 76);
      vboxLayout = new Q3VBoxLayout(CScanWidgetTask);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(5);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      frame = new Q3Frame(CScanWidgetTask);
      frame->setObjectName(QString::fromUtf8("frame"));
      frame->setFrameShape(Q3Frame::StyledPanel);
      frame->setFrameShadow(Q3Frame::Raised);
      vboxLayout1 = new Q3VBoxLayout(frame);
      vboxLayout1->setSpacing(6);
      vboxLayout1->setMargin(6);
      vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
      hboxLayout = new Q3HBoxLayout();
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

      vboxLayout1->addLayout(hboxLayout);

      hboxLayout1 = new Q3HBoxLayout();
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

      vboxLayout1->addLayout(hboxLayout1);

      vboxLayout->addWidget(frame);

      retranslateUi(CScanWidgetTask);
      QObject::connect(comboType, SIGNAL(activated(int)), CScanWidgetTask, SLOT(typeChanged(int)));

      comboType->setCurrentIndex(1);

      QMetaObject::connectSlotsByName(CScanWidgetTask);
    } // setupUi

    void retranslateUi(QWidget *CScanWidgetTask)
    {
      CScanWidgetTask->setWindowTitle(QApplication::translate("CScanWidgetTask", "Form1", 0, QApplication::UnicodeUTF8));
      labelTitle->setText(QApplication::translate("CScanWidgetTask", "<h2>Subtask</h2>", 0, QApplication::UnicodeUTF8));
      comboType->clear();
      comboType->insertItems(0, QStringList()
                             << QApplication::translate("CScanWidgetTask", "Steady State", 0, QApplication::UnicodeUTF8)
                             << QApplication::translate("CScanWidgetTask", "Time course", 0, QApplication::UnicodeUTF8)
                             << QApplication::translate("CScanWidgetTask", "Lyapunov exponents", 0, QApplication::UnicodeUTF8)
                             << QApplication::translate("CScanWidgetTask", "Optimization", 0, QApplication::UnicodeUTF8)
                             << QApplication::translate("CScanWidgetTask", "Prameter Estimation", 0, QApplication::UnicodeUTF8)
                             << QApplication::translate("CScanWidgetTask", "Sensitivities", 0, QApplication::UnicodeUTF8)
);
      checkInitialConditions->setText(QApplication::translate("CScanWidgetTask", "always use initial conditions", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      checkInitialConditions->setProperty("toolTip", QVariant(QApplication::translate("CScanWidgetTask", "If this is activated every calculation will start with the initial conditions specified in the model. <p>If it is not activated only the first calculation will use the initial value specified in the model. All subsequent calculations will start with the result of the previous calculation.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

      checkOutput->setText(QApplication::translate("CScanWidgetTask", "output during subtask execution", 0, QApplication::UnicodeUTF8));
      checkOutput->setShortcut(QString());

#ifndef QT_NO_TOOLTIP
      checkOutput->setProperty("toolTip", QVariant(QApplication::translate("CScanWidgetTask", "If this is activated output will be generated during each calculation. <p>If it is not activated only the state at the end of each calculation will be plotted.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

      Q_UNUSED(CScanWidgetTask);
    } // retranslateUi
  };

namespace Ui
  {
  class CScanWidgetTask: public Ui_CScanWidgetTask {};
} // namespace Ui

QT_END_NAMESPACE

class CScanWidgetTask : public QWidget, public Ui::CScanWidgetTask
  {
    Q_OBJECT

  public:
    CScanWidgetTask(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~CScanWidgetTask();

    virtual bool initFromScanProblem(CScanProblem * pg, const CModel * model);
    virtual bool saveToScanProblem(CScanProblem * pg) const;

  protected:
    CCopasiObject* mpObject;
    const CModel* mpModel;

  protected slots:
    virtual void languageChange();

  private:
    void init();

  private slots:
    virtual void typeChanged(int n);
  };

#endif // CSCANWIDGETTASK_H
