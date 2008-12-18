// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapWidget.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQLYAPWIDGET_H
#define CQLYAPWIDGET_H

#include <qvariant.h>

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
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>
#include "TaskWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CQLyapWidget
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3GridLayout *gridLayout;
    Q3Frame *mpLine;
    Q3HBoxLayout *hboxLayout;
    QCheckBox *mpCheckDelay;
    QLineEdit *mpEditDelay;
    QLineEdit *mpEditExponent;
    QCheckBox *mpCheckDivergence;
    QLabel *mpLblExponents;

    void setupUi(TaskWidget *CQLyapWidget)
    {
      if (CQLyapWidget->objectName().isEmpty())
        CQLyapWidget->setObjectName(QString::fromUtf8("CQLyapWidget"));
      CQLyapWidget->resize(292, 106);
      vboxLayout = new Q3VBoxLayout(CQLyapWidget);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      gridLayout = new Q3GridLayout(1, 1);
      gridLayout->setSpacing(6);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      mpLine = new Q3Frame(CQLyapWidget);
      mpLine->setObjectName(QString::fromUtf8("mpLine"));
      mpLine->setFrameShape(Q3Frame::HLine);
      mpLine->setFrameShadow(Q3Frame::Sunken);

      gridLayout->addWidget(mpLine, 3, 0, 1, 2);

      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(0);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpCheckDelay = new QCheckBox(CQLyapWidget);
      mpCheckDelay->setObjectName(QString::fromUtf8("mpCheckDelay"));

      hboxLayout->addWidget(mpCheckDelay);

      mpEditDelay = new QLineEdit(CQLyapWidget);
      mpEditDelay->setObjectName(QString::fromUtf8("mpEditDelay"));

      hboxLayout->addWidget(mpEditDelay);

      gridLayout->addLayout(hboxLayout, 1, 1, 1, 1);

      mpEditExponent = new QLineEdit(CQLyapWidget);
      mpEditExponent->setObjectName(QString::fromUtf8("mpEditExponent"));

      gridLayout->addWidget(mpEditExponent, 0, 1, 1, 1);

      mpCheckDivergence = new QCheckBox(CQLyapWidget);
      mpCheckDivergence->setObjectName(QString::fromUtf8("mpCheckDivergence"));

      gridLayout->addWidget(mpCheckDivergence, 2, 1, 1, 1);

      mpLblExponents = new QLabel(CQLyapWidget);
      mpLblExponents->setObjectName(QString::fromUtf8("mpLblExponents"));
      mpLblExponents->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblExponents->setWordWrap(false);

      gridLayout->addWidget(mpLblExponents, 0, 0, 1, 1);

      vboxLayout->addLayout(gridLayout);

      QWidget::setTabOrder(mpEditExponent, mpCheckDelay);
      QWidget::setTabOrder(mpCheckDelay, mpEditDelay);
      QWidget::setTabOrder(mpEditDelay, mpCheckDivergence);

      retranslateUi(CQLyapWidget);
      QObject::connect(mpCheckDelay, SIGNAL(clicked()), CQLyapWidget, SLOT(slotDelayChecked()));

      QMetaObject::connectSlotsByName(CQLyapWidget);
    } // setupUi

    void retranslateUi(TaskWidget *CQLyapWidget)
    {
      CQLyapWidget->setCaption(QApplication::translate("CQLyapWidget", "CQLyapWidget", 0, QApplication::UnicodeUTF8));
      mpCheckDelay->setText(QApplication::translate("CQLyapWidget", "start averaging after t =", 0, QApplication::UnicodeUTF8));
      mpCheckDivergence->setText(QApplication::translate("CQLyapWidget", "calculate Divergence", 0, QApplication::UnicodeUTF8));
      mpLblExponents->setText(QApplication::translate("CQLyapWidget", "Number of Exponents", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQLyapWidget);
    } // retranslateUi
  };

namespace Ui
  {
  class CQLyapWidget: public Ui_CQLyapWidget {};
} // namespace Ui

QT_END_NAMESPACE

class CQLyapWidget : public TaskWidget, public Ui::CQLyapWidget
  {
    Q_OBJECT

  public:
    CQLyapWidget(QWidget* parent = 0, const char* name = 0);
    ~CQLyapWidget();

    virtual bool runTask();

  protected:
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);
    virtual bool loadTask();
    virtual bool saveTask();

  protected slots:
    virtual void languageChange();

    void slotDelayChecked();

  private:
    void init();
  };

#endif // CQLYAPWIDGET_H
