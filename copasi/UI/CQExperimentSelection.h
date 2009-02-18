// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentSelection.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:46:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEXPERIMENTSELECTION_H
#define CQEXPERIMENTSELECTION_H

#include <qvariant.h>
//Added by qt3to4:
#include <QPixmap>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

class QComboBox;
class CExperimentSet;

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QDialog>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>

class Ui_CQExperimentSelection
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3HBoxLayout *hboxLayout;
    QPushButton *mpBtnAll;
    QPushButton *mpBtnNone;
    Q3HBoxLayout *hboxLayout1;
    Q3Table *mpTable;
    QSpacerItem *spacer10;
    Q3HBoxLayout *hboxLayout2;
    QPushButton *mpBtnOK;
    QPushButton *mpBtnCancel;

    void setupUi(QDialog *CQExperimentSelection)
    {
      if (CQExperimentSelection->objectName().isEmpty())
        CQExperimentSelection->setObjectName(QString::fromUtf8("CQExperimentSelection"));
      CQExperimentSelection->resize(194, 180);
      vboxLayout = new Q3VBoxLayout(CQExperimentSelection);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpBtnAll = new QPushButton(CQExperimentSelection);
      mpBtnAll->setObjectName(QString::fromUtf8("mpBtnAll"));

      hboxLayout->addWidget(mpBtnAll);

      mpBtnNone = new QPushButton(CQExperimentSelection);
      mpBtnNone->setObjectName(QString::fromUtf8("mpBtnNone"));

      hboxLayout->addWidget(mpBtnNone);

      vboxLayout->addLayout(hboxLayout);

      hboxLayout1 = new Q3HBoxLayout();
      hboxLayout1->setSpacing(6);
      hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
      mpTable = new Q3Table(CQExperimentSelection);
      mpTable->setObjectName(QString::fromUtf8("mpTable"));
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(5));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(mpTable->sizePolicy().hasHeightForWidth());
      mpTable->setSizePolicy(sizePolicy);
      mpTable->setLineWidth(0);
      mpTable->setNumRows(3);
      mpTable->setNumCols(1);
      mpTable->setShowGrid(false);
      mpTable->setSelectionMode(Q3Table::NoSelection);

      hboxLayout1->addWidget(mpTable);

      vboxLayout->addLayout(hboxLayout1);

      spacer10 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout->addItem(spacer10);

      hboxLayout2 = new Q3HBoxLayout();
      hboxLayout2->setSpacing(6);
      hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
      mpBtnOK = new QPushButton(CQExperimentSelection);
      mpBtnOK->setObjectName(QString::fromUtf8("mpBtnOK"));

      hboxLayout2->addWidget(mpBtnOK);

      mpBtnCancel = new QPushButton(CQExperimentSelection);
      mpBtnCancel->setObjectName(QString::fromUtf8("mpBtnCancel"));

      hboxLayout2->addWidget(mpBtnCancel);

      vboxLayout->addLayout(hboxLayout2);

      retranslateUi(CQExperimentSelection);
      QObject::connect(mpBtnAll, SIGNAL(clicked()), CQExperimentSelection, SLOT(slotBtnAll()));
      QObject::connect(mpBtnNone, SIGNAL(clicked()), CQExperimentSelection, SLOT(slotBtnNone()));
      QObject::connect(mpBtnCancel, SIGNAL(clicked()), CQExperimentSelection, SLOT(slotBtnCancel()));
      QObject::connect(mpBtnOK, SIGNAL(clicked()), CQExperimentSelection, SLOT(slotBtnOK()));

      QMetaObject::connectSlotsByName(CQExperimentSelection);
    } // setupUi

    void retranslateUi(QDialog *CQExperimentSelection)
    {
      CQExperimentSelection->setWindowTitle(QApplication::translate("CQExperimentSelection", "CQExperimentSelection", 0, QApplication::UnicodeUTF8));
      mpBtnAll->setText(QApplication::translate("CQExperimentSelection", "Select All", 0, QApplication::UnicodeUTF8));
      mpBtnNone->setText(QApplication::translate("CQExperimentSelection", "Deselect All", 0, QApplication::UnicodeUTF8));
      mpTable->horizontalHeader()->setLabel(0, QPixmap(), QApplication::translate("CQExperimentSelection", "1", 0, QApplication::UnicodeUTF8));
      mpTable->verticalHeader()->setLabel(0, QPixmap(), QApplication::translate("CQExperimentSelection", "1", 0, QApplication::UnicodeUTF8));
      mpTable->verticalHeader()->setLabel(1, QPixmap(), QApplication::translate("CQExperimentSelection", "2", 0, QApplication::UnicodeUTF8));
      mpTable->verticalHeader()->setLabel(2, QPixmap(), QApplication::translate("CQExperimentSelection", "3", 0, QApplication::UnicodeUTF8));
      mpBtnOK->setText(QApplication::translate("CQExperimentSelection", "&OK", 0, QApplication::UnicodeUTF8));
      mpBtnOK->setShortcut(QApplication::translate("CQExperimentSelection", "Alt+O", 0, QApplication::UnicodeUTF8));
      mpBtnCancel->setText(QApplication::translate("CQExperimentSelection", "&Cancel", 0, QApplication::UnicodeUTF8));
      mpBtnCancel->setShortcut(QApplication::translate("CQExperimentSelection", "Alt+C", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQExperimentSelection);
    } // retranslateUi
  };

namespace Ui
  {
  class CQExperimentSelection: public Ui_CQExperimentSelection {};
} // namespace Ui

class CQExperimentSelection : public QDialog, public Ui::CQExperimentSelection
  {
    Q_OBJECT

  public:
    CQExperimentSelection(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~CQExperimentSelection();

    virtual void load(QComboBox * pBox, const CExperimentSet * pExperimentSet);

  protected:
    QComboBox * mpBox;

  protected slots:
    virtual void languageChange();

    void slotBtnOK();
    void slotBtnCancel();
    void slotBtnAll();
    void slotBtnNone();

  private:
    void init();
  };

#endif // CQEXPERIMENTSELECTION_H
