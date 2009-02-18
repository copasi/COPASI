// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTrajectoryWidget.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:48:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTRAJECTORYWIDGET_H
#define CQTRAJECTORYWIDGET_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

class CTrajectoryProblem;
class CQValidatorInt;
class CQValidatorDouble;

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
#include "TaskWidget.h"

class Ui_CQTrajectoryWidget
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3GridLayout *gridLayout;
    Q3Frame *line2;
    QLineEdit *mpEditDuration;
    QLineEdit *mpEditIntegrationInterval;
    QLabel *mpLblIntervals;
    QLineEdit *mpEditIntervals;
    QLabel *mpLblOutputInterval;
    QLabel *mpLblIntervalSize;
    Q3HBoxLayout *hboxLayout;
    QCheckBox *mpCheckDelay;
    QLineEdit *mpEditDelay;
    QSpacerItem *spacer1;
    QLabel *mpLblDuration;
    QLabel *mpLblIntegrationInterval;
    QLineEdit *mpEditOutputInterval;
    QLineEdit *mpEditIntervalSize;
    QCheckBox *mpCheckSave;
    Q3Frame *line1;

    void setupUi(TaskWidget *CQTrajectoryWidget)
    {
      if (CQTrajectoryWidget->objectName().isEmpty())
        CQTrajectoryWidget->setObjectName(QString::fromUtf8("CQTrajectoryWidget"));
      CQTrajectoryWidget->resize(553, 222);
      vboxLayout = new Q3VBoxLayout(CQTrajectoryWidget);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      gridLayout = new Q3GridLayout(1, 1);
      gridLayout->setSpacing(6);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      line2 = new Q3Frame(CQTrajectoryWidget);
      line2->setObjectName(QString::fromUtf8("line2"));
      line2->setFrameShape(Q3Frame::HLine);
      line2->setFrameShadow(Q3Frame::Sunken);

      gridLayout->addWidget(line2, 4, 0, 1, 4);

      mpEditDuration = new QLineEdit(CQTrajectoryWidget);
      mpEditDuration->setObjectName(QString::fromUtf8("mpEditDuration"));

      gridLayout->addWidget(mpEditDuration, 0, 1, 1, 1);

      mpEditIntegrationInterval = new QLineEdit(CQTrajectoryWidget);
      mpEditIntegrationInterval->setObjectName(QString::fromUtf8("mpEditIntegrationInterval"));
      mpEditIntegrationInterval->setReadOnly(true);

      gridLayout->addWidget(mpEditIntegrationInterval, 5, 1, 1, 1);

      mpLblIntervals = new QLabel(CQTrajectoryWidget);
      mpLblIntervals->setObjectName(QString::fromUtf8("mpLblIntervals"));
      mpLblIntervals->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblIntervals->setWordWrap(false);

      gridLayout->addWidget(mpLblIntervals, 1, 2, 1, 1);

      mpEditIntervals = new QLineEdit(CQTrajectoryWidget);
      mpEditIntervals->setObjectName(QString::fromUtf8("mpEditIntervals"));

      gridLayout->addWidget(mpEditIntervals, 1, 3, 1, 1);

      mpLblOutputInterval = new QLabel(CQTrajectoryWidget);
      mpLblOutputInterval->setObjectName(QString::fromUtf8("mpLblOutputInterval"));
      mpLblOutputInterval->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblOutputInterval->setWordWrap(false);

      gridLayout->addWidget(mpLblOutputInterval, 6, 0, 1, 1);

      mpLblIntervalSize = new QLabel(CQTrajectoryWidget);
      mpLblIntervalSize->setObjectName(QString::fromUtf8("mpLblIntervalSize"));
      mpLblIntervalSize->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblIntervalSize->setWordWrap(false);

      gridLayout->addWidget(mpLblIntervalSize, 1, 0, 1, 1);

      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpCheckDelay = new QCheckBox(CQTrajectoryWidget);
      mpCheckDelay->setObjectName(QString::fromUtf8("mpCheckDelay"));

      hboxLayout->addWidget(mpCheckDelay);

      mpEditDelay = new QLineEdit(CQTrajectoryWidget);
      mpEditDelay->setObjectName(QString::fromUtf8("mpEditDelay"));

      hboxLayout->addWidget(mpEditDelay);

      spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      hboxLayout->addItem(spacer1);

      gridLayout->addLayout(hboxLayout, 2, 1, 1, 3);

      mpLblDuration = new QLabel(CQTrajectoryWidget);
      mpLblDuration->setObjectName(QString::fromUtf8("mpLblDuration"));
      mpLblDuration->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblDuration->setWordWrap(false);

      gridLayout->addWidget(mpLblDuration, 0, 0, 1, 1);

      mpLblIntegrationInterval = new QLabel(CQTrajectoryWidget);
      mpLblIntegrationInterval->setObjectName(QString::fromUtf8("mpLblIntegrationInterval"));
      mpLblIntegrationInterval->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblIntegrationInterval->setWordWrap(false);

      gridLayout->addWidget(mpLblIntegrationInterval, 5, 0, 1, 1);

      mpEditOutputInterval = new QLineEdit(CQTrajectoryWidget);
      mpEditOutputInterval->setObjectName(QString::fromUtf8("mpEditOutputInterval"));
      mpEditOutputInterval->setReadOnly(true);

      gridLayout->addWidget(mpEditOutputInterval, 6, 1, 1, 1);

      mpEditIntervalSize = new QLineEdit(CQTrajectoryWidget);
      mpEditIntervalSize->setObjectName(QString::fromUtf8("mpEditIntervalSize"));

      gridLayout->addWidget(mpEditIntervalSize, 1, 1, 1, 1);

      mpCheckSave = new QCheckBox(CQTrajectoryWidget);
      mpCheckSave->setObjectName(QString::fromUtf8("mpCheckSave"));

      gridLayout->addWidget(mpCheckSave, 3, 1, 1, 2);

      vboxLayout->addLayout(gridLayout);

      line1 = new Q3Frame(CQTrajectoryWidget);
      line1->setObjectName(QString::fromUtf8("line1"));
      line1->setFrameShape(Q3Frame::HLine);
      line1->setFrameShadow(Q3Frame::Sunken);

      vboxLayout->addWidget(line1);

      QWidget::setTabOrder(mpEditDuration, mpEditIntervalSize);
      QWidget::setTabOrder(mpEditIntervalSize, mpEditIntervals);
      QWidget::setTabOrder(mpEditIntervals, mpCheckDelay);
      QWidget::setTabOrder(mpCheckDelay, mpEditDelay);
      QWidget::setTabOrder(mpEditDelay, mpCheckSave);

      retranslateUi(CQTrajectoryWidget);
      QObject::connect(mpEditDuration, SIGNAL(lostFocus()), CQTrajectoryWidget, SLOT(slotDuration()));
      QObject::connect(mpEditIntervalSize, SIGNAL(lostFocus()), CQTrajectoryWidget, SLOT(slotIntervalSize()));
      QObject::connect(mpEditIntervals, SIGNAL(lostFocus()), CQTrajectoryWidget, SLOT(slotIntervals()));
      QObject::connect(mpEditDelay, SIGNAL(lostFocus()), CQTrajectoryWidget, SLOT(updateIntervals()));
      QObject::connect(mpCheckDelay, SIGNAL(toggled(bool)), CQTrajectoryWidget, SLOT(slotOutputDelay(bool)));

      QMetaObject::connectSlotsByName(CQTrajectoryWidget);
    } // setupUi

    void retranslateUi(TaskWidget *CQTrajectoryWidget)
    {
      CQTrajectoryWidget->setCaption(QApplication::translate("CQTrajectoryWidget", "Time Course", 0, QApplication::UnicodeUTF8));
      mpLblIntervals->setText(QApplication::translate("CQTrajectoryWidget", "Intervals", 0, QApplication::UnicodeUTF8));
      mpLblOutputInterval->setText(QApplication::translate("CQTrajectoryWidget", "Output Interval", 0, QApplication::UnicodeUTF8));
      mpLblIntervalSize->setText(QApplication::translate("CQTrajectoryWidget", "Interval Size", 0, QApplication::UnicodeUTF8));
      mpCheckDelay->setText(QApplication::translate("CQTrajectoryWidget", "Suppress Output Before", 0, QApplication::UnicodeUTF8));
      mpLblDuration->setText(QApplication::translate("CQTrajectoryWidget", "Duration", 0, QApplication::UnicodeUTF8));
      mpLblIntegrationInterval->setText(QApplication::translate("CQTrajectoryWidget", "Integration Interval", 0, QApplication::UnicodeUTF8));
      mpCheckSave->setText(QApplication::translate("CQTrajectoryWidget", "Save Result in Memory", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQTrajectoryWidget);
    } // retranslateUi
  };

namespace Ui
  {
  class CQTrajectoryWidget: public Ui_CQTrajectoryWidget {};
} // namespace Ui

class CQTrajectoryWidget : public TaskWidget, public Ui::CQTrajectoryWidget
  {
    Q_OBJECT

  public:
    CQTrajectoryWidget(QWidget* parent = 0, const char* name = 0);
    ~CQTrajectoryWidget();

    virtual bool runTask();

  public slots:
    void slotDuration();
    void slotIntervalSize();
    void slotIntervals();
    void updateIntervals();
    void slotOutputDelay(bool checked);

  protected:
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

  protected slots:
    virtual void languageChange();

  private:
    CQValidatorInt * mpValidatorIntervals;
    CQValidatorDouble * mpValidatorDelay;
    CQValidatorDouble * mpValidatorIntervalSize;
    CQValidatorDouble * mpValidatorDuration;
    CTrajectoryProblem * mpTrajectoryProblem;

    void init();
    void destroy();
    void checkTimeSeries();
  };

#endif // CQTRAJECTORYWIDGET_H
