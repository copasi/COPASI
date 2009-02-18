// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMoietiesTaskWidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:47:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMOIETIESTASKWIDGET_H
#define CQMOIETIESTASKWIDGET_H

#include <qvariant.h>

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include "TaskWidget.h"

class Ui_CQMoietiesTaskWidget
  {
  public:
    Q3VBoxLayout *vboxLayout;
    QSpacerItem *mpSpacer;

    void setupUi(TaskWidget *CQMoietiesTaskWidget)
    {
      if (CQMoietiesTaskWidget->objectName().isEmpty())
        CQMoietiesTaskWidget->setObjectName(QString::fromUtf8("CQMoietiesTaskWidget"));
      CQMoietiesTaskWidget->resize(260, 23);
      vboxLayout = new Q3VBoxLayout(CQMoietiesTaskWidget);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      mpSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout->addItem(mpSpacer);

      retranslateUi(CQMoietiesTaskWidget);

      QMetaObject::connectSlotsByName(CQMoietiesTaskWidget);
    } // setupUi

    void retranslateUi(TaskWidget *CQMoietiesTaskWidget)
    {
      CQMoietiesTaskWidget->setCaption(QApplication::translate("CQMoietiesTaskWidget", "Mass Conservation", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQMoietiesTaskWidget);
    } // retranslateUi
  };

namespace Ui
  {
  class CQMoietiesTaskWidget: public Ui_CQMoietiesTaskWidget {};
} // namespace Ui

class CQMoietiesTaskWidget : public TaskWidget, public Ui::CQMoietiesTaskWidget
  {
    Q_OBJECT

  public:
    CQMoietiesTaskWidget(QWidget* parent = 0, const char* name = 0);
    ~CQMoietiesTaskWidget();

    virtual bool runTask();
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

  protected slots:
    virtual void languageChange();

  private:
    void init();
    void destroy();
  };

#endif // CQMOIETIESTASKWIDGET_H
