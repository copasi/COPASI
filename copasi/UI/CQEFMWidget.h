// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMWidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:20 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEFMWIDGET_H
#define CQEFMWIDGET_H

#include <qvariant.h>

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListView>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>
#include "TaskWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CQEFMWidget
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3Frame *mpLine;
    Q3HBoxLayout *hboxLayout;
    QLabel *mpLblFluxModes;
    QLineEdit *mpEditFluxModes;
    QSpacerItem *mpSpacer;
    Q3ListView *mpListView;

    void setupUi(TaskWidget *CQEFMWidget)
    {
      if (CQEFMWidget->objectName().isEmpty())
        CQEFMWidget->setObjectName(QString::fromUtf8("CQEFMWidget"));
      CQEFMWidget->resize(366, 168);
      vboxLayout = new Q3VBoxLayout(CQEFMWidget);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      mpLine = new Q3Frame(CQEFMWidget);
      mpLine->setObjectName(QString::fromUtf8("mpLine"));
      mpLine->setFrameShape(Q3Frame::HLine);
      mpLine->setFrameShadow(Q3Frame::Sunken);

      vboxLayout->addWidget(mpLine);

      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpLblFluxModes = new QLabel(CQEFMWidget);
      mpLblFluxModes->setObjectName(QString::fromUtf8("mpLblFluxModes"));
      mpLblFluxModes->setWordWrap(false);

      hboxLayout->addWidget(mpLblFluxModes);

      mpEditFluxModes = new QLineEdit(CQEFMWidget);
      mpEditFluxModes->setObjectName(QString::fromUtf8("mpEditFluxModes"));
      mpEditFluxModes->setReadOnly(true);

      hboxLayout->addWidget(mpEditFluxModes);

      mpSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      hboxLayout->addItem(mpSpacer);

      vboxLayout->addLayout(hboxLayout);

      mpListView = new Q3ListView(CQEFMWidget);
      mpListView->addColumn(QApplication::translate("CQEFMWidget", "Reversibility", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setClickEnabled(true, mpListView->header()->count() - 1);
      mpListView->header()->setResizeEnabled(true, mpListView->header()->count() - 1);
      mpListView->addColumn(QApplication::translate("CQEFMWidget", "Reaction Name", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setClickEnabled(true, mpListView->header()->count() - 1);
      mpListView->header()->setResizeEnabled(true, mpListView->header()->count() - 1);
      mpListView->addColumn(QApplication::translate("CQEFMWidget", "Reaction Equation", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setClickEnabled(true, mpListView->header()->count() - 1);
      mpListView->header()->setResizeEnabled(true, mpListView->header()->count() - 1);
      mpListView->setObjectName(QString::fromUtf8("mpListView"));

      vboxLayout->addWidget(mpListView);

      retranslateUi(CQEFMWidget);

      QMetaObject::connectSlotsByName(CQEFMWidget);
    } // setupUi

    void retranslateUi(TaskWidget *CQEFMWidget)
    {
      CQEFMWidget->setCaption(QApplication::translate("CQEFMWidget", "Elementary Flux Modes", 0, QApplication::UnicodeUTF8));
      mpLblFluxModes->setText(QApplication::translate("CQEFMWidget", "Flux Modes", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setLabel(0, QApplication::translate("CQEFMWidget", "Reversibility", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setLabel(1, QApplication::translate("CQEFMWidget", "Reaction Name", 0, QApplication::UnicodeUTF8));
      mpListView->header()->setLabel(2, QApplication::translate("CQEFMWidget", "Reaction Equation", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQEFMWidget);
    } // retranslateUi
  };

namespace Ui
  {
  class CQEFMWidget: public Ui_CQEFMWidget {};
} // namespace Ui

QT_END_NAMESPACE

class CQEFMWidget : public TaskWidget, public Ui::CQEFMWidget
  {
    Q_OBJECT

  public:
    CQEFMWidget(QWidget* parent = 0, const char* name = 0);
    ~CQEFMWidget();

    virtual bool runTask();
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

  protected slots:
    virtual void languageChange();

  private:
    void init();
    void destroy();
    void loadFluxModes();
  };

#endif // CQEFMWIDGET_H
