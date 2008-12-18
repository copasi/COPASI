// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DefaultplotDialog.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:53 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef DEFAULTPLOTDIALOG_H
#define DEFAULTPLOTDIALOG_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <QLabel>

class CCopasiProblem;
class CCopasiTask;

#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QDialog>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <vector>
#include "copasi.h"

QT_BEGIN_NAMESPACE

class Ui_DefaultPlotDialog
  {
  public:
    Q3GridLayout *gridLayout;
    Q3ListBox *listBox;
    QLabel *titleLabel;
    QLineEdit *lineEditTitle;
    Q3TextEdit *textEdit;
    Q3HBoxLayout *hboxLayout;
    QSpacerItem *spacerButtons;
    QPushButton *createButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DefaultPlotDialog)
    {
      if (DefaultPlotDialog->objectName().isEmpty())
        DefaultPlotDialog->setObjectName(QString::fromUtf8("DefaultPlotDialog"));
      DefaultPlotDialog->resize(586, 383);
      gridLayout = new Q3GridLayout(DefaultPlotDialog);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(11);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      listBox = new Q3ListBox(DefaultPlotDialog);
      listBox->setObjectName(QString::fromUtf8("listBox"));

      gridLayout->addWidget(listBox, 0, 0, 3, 1);

      titleLabel = new QLabel(DefaultPlotDialog);
      titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
      titleLabel->setWordWrap(false);

      gridLayout->addWidget(titleLabel, 0, 1, 1, 1);

      lineEditTitle = new QLineEdit(DefaultPlotDialog);
      lineEditTitle->setObjectName(QString::fromUtf8("lineEditTitle"));

      gridLayout->addWidget(lineEditTitle, 1, 1, 1, 1);

      textEdit = new Q3TextEdit(DefaultPlotDialog);
      textEdit->setObjectName(QString::fromUtf8("textEdit"));

      gridLayout->addWidget(textEdit, 2, 1, 1, 1);

      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      spacerButtons = new QSpacerItem(51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      hboxLayout->addItem(spacerButtons);

      createButton = new QPushButton(DefaultPlotDialog);
      createButton->setObjectName(QString::fromUtf8("createButton"));

      hboxLayout->addWidget(createButton);

      cancelButton = new QPushButton(DefaultPlotDialog);
      cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

      hboxLayout->addWidget(cancelButton);

      gridLayout->addLayout(hboxLayout, 3, 0, 1, 2);

      retranslateUi(DefaultPlotDialog);
      QObject::connect(cancelButton, SIGNAL(clicked()), DefaultPlotDialog, SLOT(close()));
      QObject::connect(createButton, SIGNAL(clicked()), DefaultPlotDialog, SLOT(slotCreate()));
      QObject::connect(listBox, SIGNAL(selectionChanged()), DefaultPlotDialog, SLOT(slotSelect()));

      QMetaObject::connectSlotsByName(DefaultPlotDialog);
    } // setupUi

    void retranslateUi(QDialog *DefaultPlotDialog)
    {
      DefaultPlotDialog->setWindowTitle(QApplication::translate("DefaultPlotDialog", "Form1", 0, QApplication::UnicodeUTF8));
      listBox->clear();
      listBox->insertItem(QApplication::translate("DefaultPlotDialog", "New Item", 0, QApplication::UnicodeUTF8));
      titleLabel->setText(QApplication::translate("DefaultPlotDialog", "Title", 0, QApplication::UnicodeUTF8));
      createButton->setText(QApplication::translate("DefaultPlotDialog", "Create!", 0, QApplication::UnicodeUTF8));
      cancelButton->setText(QApplication::translate("DefaultPlotDialog", "Cancel", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(DefaultPlotDialog);
    } // retranslateUi
  };

namespace Ui
  {
  class DefaultPlotDialog: public Ui_DefaultPlotDialog {};
} // namespace Ui

QT_END_NAMESPACE

class DefaultPlotDialog : public QDialog, public Ui::DefaultPlotDialog
  {
    Q_OBJECT

  public:
    DefaultPlotDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~DefaultPlotDialog();

  public slots:
    virtual void setTask(CCopasiTask * t);
    virtual void newSlot();

  protected:
    CCopasiTask* mpTask;
    std::vector<C_INT32> mList;
    int mIndex;

  protected slots:
    virtual void languageChange();

    virtual void slotCreate();
    virtual void slotSelect();
  };

#endif // DEFAULTPLOTDIALOG_H
