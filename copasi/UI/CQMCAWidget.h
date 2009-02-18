// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMCAWidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:46:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMCAWIDGET_H
#define CQMCAWIDGET_H

#include <qvariant.h>

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3VBoxLayout>
#include <Q3Frame>
#include "TaskWidget.h"

class Ui_CQMCAWidget
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3GridLayout *gridLayout;
    QSpacerItem *mpSacer;
    QCheckBox *mpCheckSteadyState;
    Q3Frame *mpLine;

    void setupUi(TaskWidget *CQMCAWidget)
    {
      if (CQMCAWidget->objectName().isEmpty())
        CQMCAWidget->setObjectName(QString::fromUtf8("CQMCAWidget"));
      CQMCAWidget->resize(293, 53);
      vboxLayout = new Q3VBoxLayout(CQMCAWidget);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      gridLayout = new Q3GridLayout(1, 1);
      gridLayout->setSpacing(6);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      mpSacer = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      gridLayout->addItem(mpSacer, 0, 0, 1, 1);

      mpCheckSteadyState = new QCheckBox(CQMCAWidget);
      mpCheckSteadyState->setObjectName(QString::fromUtf8("mpCheckSteadyState"));

      gridLayout->addWidget(mpCheckSteadyState, 0, 1, 1, 1);

      mpLine = new Q3Frame(CQMCAWidget);
      mpLine->setObjectName(QString::fromUtf8("mpLine"));
      mpLine->setFrameShape(Q3Frame::HLine);
      mpLine->setFrameShadow(Q3Frame::Sunken);

      gridLayout->addWidget(mpLine, 1, 0, 1, 2);

      vboxLayout->addLayout(gridLayout);

      retranslateUi(CQMCAWidget);
      QObject::connect(mpCheckSteadyState, SIGNAL(clicked()), CQMCAWidget, SLOT(slotSteadyStateChecked()));

      QMetaObject::connectSlotsByName(CQMCAWidget);
    } // setupUi

    void retranslateUi(TaskWidget *CQMCAWidget)
    {
      CQMCAWidget->setCaption(QApplication::translate("CQMCAWidget", "CQMCAWidget", 0, QApplication::UnicodeUTF8));
      mpCheckSteadyState->setText(QApplication::translate("CQMCAWidget", "perform Steady State Analysis", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQMCAWidget);
    } // retranslateUi
  };

namespace Ui
  {
  class CQMCAWidget: public Ui_CQMCAWidget {};
} // namespace Ui

class CQMCAWidget : public TaskWidget, public Ui::CQMCAWidget
  {
    Q_OBJECT

  public:
    CQMCAWidget(QWidget* parent = 0, const char* name = 0);
    ~CQMCAWidget();

    virtual bool runTask();

  public slots:
    virtual void slotSteadyStateChecked();

  protected:
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);
    virtual bool loadTask();
    virtual bool saveTask();

  protected slots:
    virtual void languageChange();

  private:
    void init();
    bool loadParameterTable();
    bool saveParameterTable();
  };

#endif // CQMCAWIDGET_H
