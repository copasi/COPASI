// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/objectdebug.h,v $
//   $Revision: 1.9.14.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef OBJECTDEBUG_H
#define OBJECTDEBUG_H

#include <qvariant.h>

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListView>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QDialog>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
//Added by qt3to4:
#include <QPixmap>
#include <Q3GridLayout>
#include <iostream>

QT_BEGIN_NAMESPACE

class Ui_ObjectDebug
  {
  public:
    Q3GridLayout *gridLayout;
    QPushButton *UpdateButton;
    Q3ListView *ListOfObjects;
    QPushButton *pushButton2;
    QSpacerItem *spacer5;
    QPushButton *ButtonModelCheck;

    void setupUi(QDialog *ObjectDebug)
    {
      if (ObjectDebug->objectName().isEmpty())
        ObjectDebug->setObjectName(QString::fromUtf8("ObjectDebug"));
      ObjectDebug->resize(517, 486);
      gridLayout = new Q3GridLayout(ObjectDebug);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(11);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      UpdateButton = new QPushButton(ObjectDebug);
      UpdateButton->setObjectName(QString::fromUtf8("UpdateButton"));

      gridLayout->addWidget(UpdateButton, 1, 3, 1, 1);

      ListOfObjects = new Q3ListView(ObjectDebug);
      ListOfObjects->addColumn(QApplication::translate("ObjectDebug", "Column 1", 0, QApplication::UnicodeUTF8));
      ListOfObjects->header()->setClickEnabled(true, ListOfObjects->header()->count() - 1);
      ListOfObjects->header()->setResizeEnabled(true, ListOfObjects->header()->count() - 1);
      ListOfObjects->setObjectName(QString::fromUtf8("ListOfObjects"));

      gridLayout->addWidget(ListOfObjects, 0, 0, 1, 4);

      pushButton2 = new QPushButton(ObjectDebug);
      pushButton2->setObjectName(QString::fromUtf8("pushButton2"));

      gridLayout->addWidget(pushButton2, 1, 2, 1, 1);

      spacer5 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout->addItem(spacer5, 1, 0, 1, 1);

      ButtonModelCheck = new QPushButton(ObjectDebug);
      ButtonModelCheck->setObjectName(QString::fromUtf8("ButtonModelCheck"));

      gridLayout->addWidget(ButtonModelCheck, 1, 1, 1, 1);

      retranslateUi(ObjectDebug);
      QObject::connect(UpdateButton, SIGNAL(clicked()), ObjectDebug, SLOT(update()));
      QObject::connect(pushButton2, SIGNAL(clicked()), ObjectDebug, SLOT(writeDot()));
      QObject::connect(ButtonModelCheck, SIGNAL(clicked()), ObjectDebug, SLOT(checkModel()));

      QMetaObject::connectSlotsByName(ObjectDebug);
    } // setupUi

    void retranslateUi(QDialog *ObjectDebug)
    {
      ObjectDebug->setWindowTitle(QApplication::translate("ObjectDebug", "Copasi Object Tree", 0, QApplication::UnicodeUTF8));
      UpdateButton->setText(QApplication::translate("ObjectDebug", "update", 0, QApplication::UnicodeUTF8));
      ListOfObjects->header()->setLabel(0, QApplication::translate("ObjectDebug", "Column 1", 0, QApplication::UnicodeUTF8));
      ListOfObjects->clear();

      Q3ListViewItem *__item = new Q3ListViewItem(ListOfObjects);
      __item->setText(0, QApplication::translate("ObjectDebug", "New Item", 0, QApplication::UnicodeUTF8));
      __item->setPixmap(0, QPixmap());
      pushButton2->setText(QApplication::translate("ObjectDebug", "write Dependencies", 0, QApplication::UnicodeUTF8));
      ButtonModelCheck->setText(QApplication::translate("ObjectDebug", "check model", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(ObjectDebug);
    } // retranslateUi
  };

namespace Ui
  {
  class ObjectDebug: public Ui_ObjectDebug {};
} // namespace Ui

QT_END_NAMESPACE

class ObjectDebug : public QDialog, public Ui::ObjectDebug
  {
    Q_OBJECT

  public:
    ObjectDebug(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~ObjectDebug();

  public slots:
    void update();
    virtual void writeDot();
    virtual void checkModel();

  protected slots:
    virtual void languageChange();

  private:
    void addObjectRecursive(QWidget * parent, void * ptr);
    void init();
  };

#endif // OBJECTDEBUG_H
