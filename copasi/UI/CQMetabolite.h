// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.h,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:47:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMETABOLITE_H
#define CQMETABOLITE_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <Q3Frame>
#include <QPixmap>
#include <QLabel>

class CQExpressionWidget;
class CMetab;
class CCompartment;
class CExpression;

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListView>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <string>
#include "CQExpressionMmlWidget.h"
#include "copasiWidget.h"

class Ui_CQMetabolite
  {
  public:
    Q3GridLayout *gridLayout;
    Q3HBoxLayout *hboxLayout;
    QPushButton *mpBtnCommit;
    QPushButton *mpBtnRevert;
    QPushButton *mpBtnNew;
    QPushButton *mpBtnDelete;
    QLabel *mpLblType;
    QLineEdit *mpEditName;
    QComboBox *mpComboBoxCompartment;
    QComboBox *mpComboBoxType;
    QLabel *mpLblCompartment;
    QLabel *mpLblName;
    Q3Frame *mpLine1;
    QLineEdit *mpEditInitialValue;
    QLabel *mpLblInitialExpression;
    QCheckBox *mpBoxUseInitialExpression;
    QLabel *mpLblInitialValue;
    QLabel *mpLblExpression;
    QLabel *mpLblReactions;
    Q3ListView *mpReactionTable;
    QLineEdit *mpEditCurrentValue;
    QLineEdit *mpEditRate;
    QLineEdit *mpEditTransitionTime;
    QLabel *mpLblValue;
    QLabel *mpLblTransitionTime;
    QLabel *mpLblRate;
    QSpacerItem *mpSpacer;
    Q3Frame *mpLine2;
    CQExpressionMmlWidget *mpExpressionEMW;
    CQExpressionMmlWidget *mpInitialExpressionEMW;

    void setupUi(CopasiWidget *CQMetabolite)
    {
      if (CQMetabolite->objectName().isEmpty())
        CQMetabolite->setObjectName(QString::fromUtf8("CQMetabolite"));
      CQMetabolite->resize(453, 421);
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(CQMetabolite->sizePolicy().hasHeightForWidth());
      CQMetabolite->setSizePolicy(sizePolicy);
      gridLayout = new Q3GridLayout(CQMetabolite);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(11);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpBtnCommit = new QPushButton(CQMetabolite);
      mpBtnCommit->setObjectName(QString::fromUtf8("mpBtnCommit"));

      hboxLayout->addWidget(mpBtnCommit);

      mpBtnRevert = new QPushButton(CQMetabolite);
      mpBtnRevert->setObjectName(QString::fromUtf8("mpBtnRevert"));

      hboxLayout->addWidget(mpBtnRevert);

      mpBtnNew = new QPushButton(CQMetabolite);
      mpBtnNew->setObjectName(QString::fromUtf8("mpBtnNew"));

      hboxLayout->addWidget(mpBtnNew);

      mpBtnDelete = new QPushButton(CQMetabolite);
      mpBtnDelete->setObjectName(QString::fromUtf8("mpBtnDelete"));

      hboxLayout->addWidget(mpBtnDelete);

      gridLayout->addLayout(hboxLayout, 13, 0, 1, 3);

      mpLblType = new QLabel(CQMetabolite);
      mpLblType->setObjectName(QString::fromUtf8("mpLblType"));
      QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(1));
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(mpLblType->sizePolicy().hasHeightForWidth());
      mpLblType->setSizePolicy(sizePolicy1);
      mpLblType->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblType->setWordWrap(false);

      gridLayout->addWidget(mpLblType, 2, 0, 1, 1);

      mpEditName = new QLineEdit(CQMetabolite);
      mpEditName->setObjectName(QString::fromUtf8("mpEditName"));
      QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(0));
      sizePolicy2.setHorizontalStretch(0);
      sizePolicy2.setVerticalStretch(0);
      sizePolicy2.setHeightForWidth(mpEditName->sizePolicy().hasHeightForWidth());
      mpEditName->setSizePolicy(sizePolicy2);

      gridLayout->addWidget(mpEditName, 0, 1, 1, 2);

      mpComboBoxCompartment = new QComboBox(CQMetabolite);
      mpComboBoxCompartment->setObjectName(QString::fromUtf8("mpComboBoxCompartment"));
      sizePolicy2.setHeightForWidth(mpComboBoxCompartment->sizePolicy().hasHeightForWidth());
      mpComboBoxCompartment->setSizePolicy(sizePolicy2);

      gridLayout->addWidget(mpComboBoxCompartment, 1, 1, 1, 2);

      mpComboBoxType = new QComboBox(CQMetabolite);
      mpComboBoxType->setObjectName(QString::fromUtf8("mpComboBoxType"));
      sizePolicy2.setHeightForWidth(mpComboBoxType->sizePolicy().hasHeightForWidth());
      mpComboBoxType->setSizePolicy(sizePolicy2);

      gridLayout->addWidget(mpComboBoxType, 2, 1, 1, 1);

      mpLblCompartment = new QLabel(CQMetabolite);
      mpLblCompartment->setObjectName(QString::fromUtf8("mpLblCompartment"));
      sizePolicy1.setHeightForWidth(mpLblCompartment->sizePolicy().hasHeightForWidth());
      mpLblCompartment->setSizePolicy(sizePolicy1);
      mpLblCompartment->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblCompartment->setWordWrap(false);

      gridLayout->addWidget(mpLblCompartment, 1, 0, 1, 1);

      mpLblName = new QLabel(CQMetabolite);
      mpLblName->setObjectName(QString::fromUtf8("mpLblName"));
      sizePolicy1.setHeightForWidth(mpLblName->sizePolicy().hasHeightForWidth());
      mpLblName->setSizePolicy(sizePolicy1);
      mpLblName->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblName->setWordWrap(false);

      gridLayout->addWidget(mpLblName, 0, 0, 1, 1);

      mpLine1 = new Q3Frame(CQMetabolite);
      mpLine1->setObjectName(QString::fromUtf8("mpLine1"));
      mpLine1->setFrameShape(Q3Frame::HLine);
      mpLine1->setFrameShadow(Q3Frame::Sunken);

      gridLayout->addWidget(mpLine1, 6, 0, 1, 3);

      mpEditInitialValue = new QLineEdit(CQMetabolite);
      mpEditInitialValue->setObjectName(QString::fromUtf8("mpEditInitialValue"));
      QSizePolicy sizePolicy3(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(5));
      sizePolicy3.setHorizontalStretch(0);
      sizePolicy3.setVerticalStretch(0);
      sizePolicy3.setHeightForWidth(mpEditInitialValue->sizePolicy().hasHeightForWidth());
      mpEditInitialValue->setSizePolicy(sizePolicy3);

      gridLayout->addWidget(mpEditInitialValue, 4, 1, 1, 1);

      mpLblInitialExpression = new QLabel(CQMetabolite);
      mpLblInitialExpression->setObjectName(QString::fromUtf8("mpLblInitialExpression"));
      sizePolicy1.setHeightForWidth(mpLblInitialExpression->sizePolicy().hasHeightForWidth());
      mpLblInitialExpression->setSizePolicy(sizePolicy1);
      mpLblInitialExpression->setAlignment(Qt::AlignTop | Qt::AlignRight);
      mpLblInitialExpression->setWordWrap(false);

      gridLayout->addWidget(mpLblInitialExpression, 5, 0, 1, 1);

      mpBoxUseInitialExpression = new QCheckBox(CQMetabolite);
      mpBoxUseInitialExpression->setObjectName(QString::fromUtf8("mpBoxUseInitialExpression"));

      gridLayout->addWidget(mpBoxUseInitialExpression, 4, 2, 1, 1);

      mpLblInitialValue = new QLabel(CQMetabolite);
      mpLblInitialValue->setObjectName(QString::fromUtf8("mpLblInitialValue"));
      sizePolicy.setHeightForWidth(mpLblInitialValue->sizePolicy().hasHeightForWidth());
      mpLblInitialValue->setSizePolicy(sizePolicy);
      mpLblInitialValue->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblInitialValue->setWordWrap(false);

      gridLayout->addWidget(mpLblInitialValue, 4, 0, 1, 1);

      mpLblExpression = new QLabel(CQMetabolite);
      mpLblExpression->setObjectName(QString::fromUtf8("mpLblExpression"));
      sizePolicy1.setHeightForWidth(mpLblExpression->sizePolicy().hasHeightForWidth());
      mpLblExpression->setSizePolicy(sizePolicy1);
      mpLblExpression->setAlignment(Qt::AlignTop | Qt::AlignRight);
      mpLblExpression->setWordWrap(false);

      gridLayout->addWidget(mpLblExpression, 3, 0, 1, 1);

      mpLblReactions = new QLabel(CQMetabolite);
      mpLblReactions->setObjectName(QString::fromUtf8("mpLblReactions"));
      sizePolicy1.setHeightForWidth(mpLblReactions->sizePolicy().hasHeightForWidth());
      mpLblReactions->setSizePolicy(sizePolicy1);
      mpLblReactions->setAlignment(Qt::AlignTop | Qt::AlignRight);
      mpLblReactions->setWordWrap(false);

      gridLayout->addWidget(mpLblReactions, 10, 0, 1, 1);

      mpReactionTable = new Q3ListView(CQMetabolite);
      mpReactionTable->addColumn(QApplication::translate("CQMetabolite", "Name", 0, QApplication::UnicodeUTF8));
      mpReactionTable->header()->setClickEnabled(true, mpReactionTable->header()->count() - 1);
      mpReactionTable->header()->setResizeEnabled(true, mpReactionTable->header()->count() - 1);
      mpReactionTable->addColumn(QApplication::translate("CQMetabolite", "Equation", 0, QApplication::UnicodeUTF8));
      mpReactionTable->header()->setClickEnabled(true, mpReactionTable->header()->count() - 1);
      mpReactionTable->header()->setResizeEnabled(true, mpReactionTable->header()->count() - 1);
      mpReactionTable->setObjectName(QString::fromUtf8("mpReactionTable"));
      sizePolicy.setHeightForWidth(mpReactionTable->sizePolicy().hasHeightForWidth());
      mpReactionTable->setSizePolicy(sizePolicy);

      gridLayout->addWidget(mpReactionTable, 10, 1, 1, 2);

      mpEditCurrentValue = new QLineEdit(CQMetabolite);
      mpEditCurrentValue->setObjectName(QString::fromUtf8("mpEditCurrentValue"));
      sizePolicy3.setHeightForWidth(mpEditCurrentValue->sizePolicy().hasHeightForWidth());
      mpEditCurrentValue->setSizePolicy(sizePolicy3);
      mpEditCurrentValue->setReadOnly(true);

      gridLayout->addWidget(mpEditCurrentValue, 7, 1, 1, 1);

      mpEditRate = new QLineEdit(CQMetabolite);
      mpEditRate->setObjectName(QString::fromUtf8("mpEditRate"));
      sizePolicy3.setHeightForWidth(mpEditRate->sizePolicy().hasHeightForWidth());
      mpEditRate->setSizePolicy(sizePolicy3);
      mpEditRate->setReadOnly(true);

      gridLayout->addWidget(mpEditRate, 8, 1, 1, 1);

      mpEditTransitionTime = new QLineEdit(CQMetabolite);
      mpEditTransitionTime->setObjectName(QString::fromUtf8("mpEditTransitionTime"));
      sizePolicy3.setHeightForWidth(mpEditTransitionTime->sizePolicy().hasHeightForWidth());
      mpEditTransitionTime->setSizePolicy(sizePolicy3);
      mpEditTransitionTime->setReadOnly(true);

      gridLayout->addWidget(mpEditTransitionTime, 9, 1, 1, 1);

      mpLblValue = new QLabel(CQMetabolite);
      mpLblValue->setObjectName(QString::fromUtf8("mpLblValue"));
      sizePolicy1.setHeightForWidth(mpLblValue->sizePolicy().hasHeightForWidth());
      mpLblValue->setSizePolicy(sizePolicy1);
      mpLblValue->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblValue->setWordWrap(false);

      gridLayout->addWidget(mpLblValue, 7, 0, 1, 1);

      mpLblTransitionTime = new QLabel(CQMetabolite);
      mpLblTransitionTime->setObjectName(QString::fromUtf8("mpLblTransitionTime"));
      sizePolicy1.setHeightForWidth(mpLblTransitionTime->sizePolicy().hasHeightForWidth());
      mpLblTransitionTime->setSizePolicy(sizePolicy1);
      mpLblTransitionTime->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblTransitionTime->setWordWrap(false);

      gridLayout->addWidget(mpLblTransitionTime, 9, 0, 1, 1);

      mpLblRate = new QLabel(CQMetabolite);
      mpLblRate->setObjectName(QString::fromUtf8("mpLblRate"));
      sizePolicy1.setHeightForWidth(mpLblRate->sizePolicy().hasHeightForWidth());
      mpLblRate->setSizePolicy(sizePolicy1);
      mpLblRate->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpLblRate->setWordWrap(false);

      gridLayout->addWidget(mpLblRate, 8, 0, 1, 1);

      mpSpacer = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

      gridLayout->addItem(mpSpacer, 11, 1, 1, 1);

      mpLine2 = new Q3Frame(CQMetabolite);
      mpLine2->setObjectName(QString::fromUtf8("mpLine2"));
      mpLine2->setFrameShape(Q3Frame::HLine);
      mpLine2->setFrameShadow(Q3Frame::Sunken);

      gridLayout->addWidget(mpLine2, 12, 0, 1, 3);

      mpExpressionEMW = new CQExpressionMmlWidget(CQMetabolite);
      mpExpressionEMW->setObjectName(QString::fromUtf8("mpExpressionEMW"));
      mpExpressionEMW->setMinimumSize(QSize(300, 30));

      gridLayout->addWidget(mpExpressionEMW, 3, 1, 1, 2);

      mpInitialExpressionEMW = new CQExpressionMmlWidget(CQMetabolite);
      mpInitialExpressionEMW->setObjectName(QString::fromUtf8("mpInitialExpressionEMW"));
      mpInitialExpressionEMW->setMinimumSize(QSize(300, 30));

      gridLayout->addWidget(mpInitialExpressionEMW, 5, 1, 1, 2);

      QWidget::setTabOrder(mpEditName, mpComboBoxCompartment);
      QWidget::setTabOrder(mpComboBoxCompartment, mpComboBoxType);
      QWidget::setTabOrder(mpComboBoxType, mpEditInitialValue);
      QWidget::setTabOrder(mpEditInitialValue, mpBoxUseInitialExpression);
      QWidget::setTabOrder(mpBoxUseInitialExpression, mpEditCurrentValue);
      QWidget::setTabOrder(mpEditCurrentValue, mpEditRate);
      QWidget::setTabOrder(mpEditRate, mpEditTransitionTime);
      QWidget::setTabOrder(mpEditTransitionTime, mpReactionTable);
      QWidget::setTabOrder(mpReactionTable, mpBtnCommit);
      QWidget::setTabOrder(mpBtnCommit, mpBtnRevert);
      QWidget::setTabOrder(mpBtnRevert, mpBtnNew);
      QWidget::setTabOrder(mpBtnNew, mpBtnDelete);

      retranslateUi(CQMetabolite);
      QObject::connect(mpBtnCommit, SIGNAL(clicked()), CQMetabolite, SLOT(slotBtnCommit()));
      QObject::connect(mpBtnDelete, SIGNAL(clicked()), CQMetabolite, SLOT(slotBtnDelete()));
      QObject::connect(mpBtnNew, SIGNAL(clicked()), CQMetabolite, SLOT(slotBtnNew()));
      QObject::connect(mpBtnRevert, SIGNAL(clicked()), CQMetabolite, SLOT(slotBtnRevert()));
      QObject::connect(mpComboBoxCompartment, SIGNAL(activated(int)), CQMetabolite, SLOT(slotCompartmentChanged(int)));
      QObject::connect(mpComboBoxType, SIGNAL(activated(int)), CQMetabolite, SLOT(slotTypeChanged(int)));
      QObject::connect(mpEditInitialValue, SIGNAL(lostFocus()), CQMetabolite, SLOT(slotInitialValueLostFocus()));
      QObject::connect(mpReactionTable, SIGNAL(doubleClicked(Q3ListViewItem*)), CQMetabolite, SLOT(slotReactionTableCurrentChanged(Q3ListViewItem*)));
      QObject::connect(mpBoxUseInitialExpression, SIGNAL(toggled(bool)), CQMetabolite, SLOT(slotInitialTypeChanged(bool)));
      QObject::connect(mpEditName, SIGNAL(lostFocus()), CQMetabolite, SLOT(slotNameLostFocus()));

      QMetaObject::connectSlotsByName(CQMetabolite);
    } // setupUi

    void retranslateUi(CopasiWidget *CQMetabolite)
    {
      CQMetabolite->setCaption(QApplication::translate("CQMetabolite", "Metabolite", 0, QApplication::UnicodeUTF8));
      mpBtnCommit->setText(QApplication::translate("CQMetabolite", "Commit", 0, QApplication::UnicodeUTF8));
      mpBtnRevert->setText(QApplication::translate("CQMetabolite", "Revert", 0, QApplication::UnicodeUTF8));
      mpBtnNew->setText(QApplication::translate("CQMetabolite", "New", 0, QApplication::UnicodeUTF8));
      mpBtnDelete->setText(QApplication::translate("CQMetabolite", "Delete", 0, QApplication::UnicodeUTF8));
      mpLblType->setText(QApplication::translate("CQMetabolite", "Simulation Type", 0, QApplication::UnicodeUTF8));
      mpLblCompartment->setText(QApplication::translate("CQMetabolite", "Compartment", 0, QApplication::UnicodeUTF8));
      mpLblName->setText(QApplication::translate("CQMetabolite", "Metobolite Name", 0, QApplication::UnicodeUTF8));
      mpLblInitialExpression->setText(QApplication::translate("CQMetabolite", "Initial Expression", 0, QApplication::UnicodeUTF8));
      mpBoxUseInitialExpression->setText(QApplication::translate("CQMetabolite", "Use Initial Expression", 0, QApplication::UnicodeUTF8));
      mpLblInitialValue->setText(QApplication::translate("CQMetabolite", "Initial Value", 0, QApplication::UnicodeUTF8));
      mpLblExpression->setText(QApplication::translate("CQMetabolite", "Expression", 0, QApplication::UnicodeUTF8));
      mpLblReactions->setText(QApplication::translate("CQMetabolite", "Involved in Reactions", 0, QApplication::UnicodeUTF8));
      mpReactionTable->header()->setLabel(0, QApplication::translate("CQMetabolite", "Name", 0, QApplication::UnicodeUTF8));
      mpReactionTable->header()->setLabel(1, QApplication::translate("CQMetabolite", "Equation", 0, QApplication::UnicodeUTF8));
      mpLblValue->setText(QApplication::translate("CQMetabolite", "Concentration", 0, QApplication::UnicodeUTF8));
      mpLblTransitionTime->setText(QApplication::translate("CQMetabolite", "Transition Time", 0, QApplication::UnicodeUTF8));
      mpLblRate->setText(QApplication::translate("CQMetabolite", "Rate", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQMetabolite);
    } // retranslateUi

  protected:
    enum IconID
    {
      image0_ID,
      unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
      static const unsigned char image0_data[] =
        {
          0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
          0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
          0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x03,
          0xb1, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xad, 0x94, 0x5f, 0x4c, 0x5b,
          0x55, 0x1c, 0xc7, 0x3f, 0xe7, 0xdc, 0x4b, 0x7b, 0x4b, 0xcb, 0xa0, 0x76,
          0x2d, 0x45, 0xc4, 0x31, 0x14, 0x32, 0x35, 0x99, 0xee, 0x61, 0x92, 0x60,
          0x9c, 0x51, 0xd8, 0x83, 0x89, 0x2c, 0xe0, 0x83, 0xf1, 0x71, 0x8b, 0x3e,
          0xbb, 0x18, 0x5f, 0x8d, 0xc9, 0x1e, 0x97, 0x2c, 0xf3, 0x9d, 0x2d, 0x2a,
          0x2f, 0x1a, 0xf6, 0x64, 0xb6, 0xf1, 0xe0, 0xfe, 0x38, 0x63, 0xa0, 0x71,
          0x89, 0x69, 0x70, 0x0e, 0xb0, 0xc5, 0x21, 0x42, 0xda, 0x02, 0x42, 0xa1,
          0xbd, 0x6d, 0x69, 0x6f, 0x7b, 0xcf, 0xf1, 0x01, 0x58, 0x52, 0x03, 0xce,
          0xb8, 0xfd, 0x9e, 0xce, 0x39, 0xf9, 0x9d, 0xcf, 0xf9, 0xfe, 0x7e, 0xdf,
          0x93, 0x9f, 0x88, 0xc5, 0x62, 0xec, 0x46, 0x5f, 0x5f, 0x9f, 0xe6, 0x09,
          0x44, 0x2c, 0x16, 0x13, 0x62, 0x17, 0x3c, 0x3e, 0x3e, 0xae, 0x7b, 0x7a,
          0x7a, 0xc8, 0xe7, 0xf3, 0x64, 0x32, 0x19, 0x6c, 0xdb, 0xfe, 0x4f, 0x90,
          0x7c, 0x3e, 0x4f, 0x22, 0x91, 0x20, 0x1e, 0x8f, 0xe3, 0x38, 0xce, 0xc3,
          0x73, 0x73, 0x57, 0xe9, 0xe8, 0xe8, 0x28, 0xad, 0xed, 0x1e, 0x22, 0x9d,
          0x65, 0x0e, 0x1f, 0x2d, 0x51, 0x75, 0x4b, 0x08, 0x21, 0x10, 0x12, 0x4c,
          0x13, 0xa4, 0xdc, 0x5e, 0xa3, 0x41, 0xeb, 0x9d, 0xc2, 0x84, 0xc0, 0x55,
          0x8a, 0x85, 0x3f, 0x3c, 0xe8, 0xcb, 0x06, 0x77, 0xef, 0x50, 0x0f, 0xde,
          0x7d, 0x39, 0xd2, 0x59, 0x66, 0x79, 0xe3, 0x26, 0x59, 0x7b, 0x8e, 0x9a,
          0xbb, 0x85, 0xd7, 0xa7, 0x70, 0xab, 0x16, 0xab, 0x69, 0x83, 0xec, 0x5a,
          0x05, 0xb4, 0x87, 0xa7, 0x0e, 0x36, 0xf0, 0xf4, 0xe1, 0x0a, 0xfe, 0x40,
          0x8d, 0x6a, 0x55, 0x83, 0x10, 0x98, 0x01, 0x08, 0x47, 0x8d, 0xba, 0x4a,
          0x1e, 0x82, 0x33, 0x99, 0x0c, 0x5d, 0x47, 0x4b, 0x64, 0xed, 0x39, 0xaa,
          0x3a, 0x8f, 0xe5, 0xf3, 0x31, 0x7f, 0xbf, 0x81, 0xdb, 0xd7, 0x0b, 0xcc,
          0xfe, 0xb2, 0x05, 0x94, 0x76, 0x32, 0xfd, 0x74, 0xf6, 0x58, 0x9c, 0x1c,
          0x6e, 0xa2, 0xf7, 0x0d, 0x03, 0xa5, 0x8b, 0xa0, 0xc1, 0xf2, 0xc9, 0xbd,
          0xc1, 0xb6, 0x6d, 0xe3, 0xb8, 0x25, 0x6a, 0x6e, 0x11, 0xcb, 0xe7, 0xe3,
          0xee, 0x1d, 0x18, 0x1b, 0x59, 0x01, 0x24, 0xfe, 0x26, 0x93, 0xae, 0xee,
          0x08, 0xd2, 0x23, 0xc8, 0x2c, 0x3a, 0x2c, 0x24, 0xb7, 0xb8, 0x74, 0xbe,
          0xc8, 0xf2, 0x62, 0x88, 0x77, 0x4f, 0x7b, 0xd0, 0x54, 0x50, 0x4a, 0xef,
          0x0d, 0xde, 0x6e, 0x99, 0xc0, 0xeb, 0x83, 0xf9, 0xfb, 0x26, 0x63, 0x23,
          0xcb, 0x80, 0xa2, 0x7f, 0xb0, 0x95, 0x81, 0x41, 0x83, 0x60, 0x44, 0x60,
          0x5a, 0x2e, 0xe5, 0x52, 0x33, 0x93, 0x37, 0x1c, 0xc6, 0x46, 0xfe, 0xe2,
          0xda, 0x37, 0x19, 0x5a, 0xa3, 0x5d, 0x0c, 0x0c, 0x5b, 0x48, 0x59, 0xac,
          0x03, 0xd7, 0xe9, 0x17, 0x12, 0xdc, 0xaa, 0xc5, 0xad, 0xab, 0x36, 0x50,
          0xa3, 0xff, 0x9d, 0x08, 0xef, 0x7d, 0xd8, 0x40, 0x4b, 0xb4, 0x88, 0x69,
          0xe5, 0xd9, 0x58, 0xb5, 0xb8, 0x7d, 0xad, 0xc4, 0xc9, 0xa1, 0x46, 0x4e,
          0x9f, 0x0d, 0x03, 0x26, 0xdf, 0x7e, 0xbd, 0x86, 0xbd, 0x2e, 0x31, 0x0c,
          0xb1, 0xbf, 0x62, 0xd3, 0x84, 0xd5, 0x94, 0x41, 0xf2, 0xd7, 0x0a, 0x07,
          0x0e, 0x1c, 0x60, 0xe0, 0x94, 0x89, 0x92, 0x9b, 0x98, 0x86, 0x81, 0xbd,
          0xd9, 0xcc, 0x97, 0x17, 0x0b, 0xcc, 0x4c, 0x65, 0x59, 0x5f, 0x71, 0xf8,
          0xe0, 0xe3, 0x30, 0x13, 0x37, 0xfc, 0x24, 0xa7, 0x73, 0x24, 0x67, 0x83,
          0x18, 0x75, 0xa4, 0x7f, 0x28, 0x96, 0x52, 0xb0, 0xbe, 0x5e, 0x41, 0x51,
          0xe6, 0xd0, 0x73, 0x16, 0xc1, 0xb0, 0xc0, 0x34, 0x0d, 0x8a, 0xb9, 0x20,
          0x23, 0xe7, 0x6d, 0x66, 0xa6, 0xb2, 0x84, 0x0e, 0x36, 0xd2, 0xfb, 0x7a,
          0x13, 0xfe, 0xe6, 0x32, 0x47, 0x5e, 0x6e, 0xdc, 0x36, 0x7e, 0xa9, 0x8a,
          0x90, 0xfb, 0x98, 0xb7, 0xdd, 0x63, 0x10, 0xca, 0x03, 0x28, 0xa4, 0x47,
          0x61, 0x58, 0x2e, 0x1b, 0xab, 0x41, 0xbe, 0xfa, 0xbc, 0xc0, 0xec, 0x94,
          0x0d, 0x28, 0xbc, 0x5e, 0x93, 0xb6, 0x8e, 0x06, 0x4c, 0xab, 0x84, 0xe1,
          0xd9, 0xbe, 0xae, 0xb4, 0x89, 0x34, 0xea, 0xc1, 0xf5, 0x3b, 0x01, 0xc1,
          0xb0, 0x00, 0xfc, 0xa4, 0x96, 0xaa, 0x54, 0xb6, 0x1a, 0x99, 0xfc, 0xde,
          0x61, 0x66, 0x2a, 0x4b, 0x4b, 0x4b, 0x23, 0xd1, 0x68, 0x0b, 0xe9, 0xd4,
          0x26, 0x17, 0x3e, 0x4d, 0xf3, 0x60, 0x2a, 0x48, 0xea, 0x41, 0x19, 0x89,
          0xa4, 0xfd, 0x59, 0x0f, 0x52, 0xa8, 0xfd, 0x15, 0x6b, 0x05, 0xed, 0x9d,
          0x35, 0x0e, 0x3d, 0xef, 0xe3, 0xcf, 0xdf, 0x4b, 0x4c, 0x7c, 0xe7, 0x70,
          0xea, 0x7d, 0x3f, 0xb9, 0xf5, 0x20, 0xaf, 0xbe, 0x16, 0x20, 0xda, 0xee,
          0xe5, 0xc2, 0x67, 0x35, 0xd2, 0x0b, 0x9b, 0x9c, 0xfb, 0x68, 0x11, 0xa7,
          0x54, 0xa4, 0x39, 0xe4, 0xe5, 0xc5, 0x63, 0x9a, 0x4c, 0xaa, 0x1e, 0x5c,
          0xaf, 0x58, 0x6b, 0xfc, 0x01, 0x97, 0xb7, 0x87, 0x02, 0x00, 0x5c, 0xb9,
          0xb4, 0xca, 0xe4, 0xcd, 0x32, 0x67, 0xce, 0x86, 0x38, 0xfe, 0x96, 0x4b,
          0xd7, 0x2b, 0x39, 0x3e, 0x39, 0xd7, 0x49, 0x28, 0xd2, 0x42, 0x61, 0x73,
          0x03, 0xa7, 0x56, 0xa3, 0x7f, 0x28, 0x44, 0x47, 0x77, 0x0d, 0xcd, 0xbf,
          0xfc, 0x63, 0x84, 0xa0, 0x5a, 0x85, 0xde, 0x13, 0x06, 0xe9, 0xa5, 0x20,
          0x57, 0xc7, 0x52, 0x7c, 0x71, 0x31, 0xc3, 0xc4, 0x2d, 0x3f, 0x47, 0x5e,
          0xb2, 0x30, 0x3c, 0x82, 0xd4, 0xfc, 0x32, 0x76, 0xd6, 0x81, 0x1d, 0xb3,
          0x7e, 0xfe, 0xb1, 0x48, 0x72, 0x30, 0x82, 0xd9, 0xb0, 0x8f, 0x79, 0xf9,
          0x7c, 0x1e, 0x57, 0x29, 0x10, 0x9a, 0x9a, 0x28, 0x30, 0x7c, 0xc6, 0x22,
          0xd2, 0xd6, 0xcd, 0xf5, 0x2b, 0x2b, 0x24, 0xef, 0xe5, 0x48, 0xde, 0xdb,
          0x00, 0x14, 0x20, 0x09, 0x86, 0x2c, 0xfa, 0x87, 0x9e, 0xe1, 0xa7, 0x1f,
          0x6c, 0xec, 0x92, 0x83, 0x53, 0x51, 0x14, 0x72, 0xfb, 0xf4, 0x38, 0x91,
          0x48, 0xb0, 0xb0, 0xe0, 0xc1, 0x08, 0x08, 0x14, 0x12, 0x45, 0x8d, 0xfe,
          0x21, 0xc9, 0xf1, 0x13, 0x51, 0xe6, 0x7e, 0x73, 0x58, 0x59, 0x54, 0x68,
          0x24, 0x6d, 0x1d, 0x1e, 0x5e, 0x38, 0xa6, 0xe9, 0xe8, 0x51, 0xbc, 0x39,
          0xd8, 0x4a, 0xb5, 0x02, 0xa6, 0x69, 0x33, 0x1d, 0xaf, 0xec, 0x0d, 0x8e,
          0xc7, 0xe3, 0xe8, 0xcb, 0x06, 0xe1, 0xa8, 0x81, 0xd7, 0x27, 0xd1, 0xae,
          0x40, 0x18, 0x0a, 0x43, 0x4a, 0x8c, 0x9d, 0xb1, 0x29, 0xa5, 0x41, 0x26,
          0xad, 0x48, 0xa7, 0x35, 0x8c, 0x2b, 0x4c, 0x53, 0x52, 0xc8, 0xc3, 0x74,
          0xbc, 0xcc, 0xda, 0xb2, 0xbb, 0x37, 0xd8, 0x71, 0x9c, 0xba, 0x79, 0xfa,
          0xb8, 0x21, 0x1f, 0x9d, 0xf2, 0x18, 0xe0, 0x58, 0x2c, 0x26, 0x1e, 0x95,
          0xf8, 0xbf, 0xc0, 0x4f, 0x1a, 0x1e, 0x8b, 0xc5, 0xc4, 0xdf, 0xe0, 0xa1,
          0x90, 0x17, 0x2a, 0xf6, 0xa9, 0x69, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
          0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

      switch (id)
        {
        case image0_ID: {QImage img; img.loadFromData(image0_data, sizeof(image0_data), "PNG"); return QPixmap::fromImage(img);}
        default: return QPixmap();
        } // switch
    } // icon
  };

namespace Ui
  {
  class CQMetabolite: public Ui_CQMetabolite {};
} // namespace Ui

class CQMetabolite : public CopasiWidget, public Ui::CQMetabolite
  {
    Q_OBJECT

  public:
    CQMetabolite(QWidget* parent = 0, const char* name = 0);
    ~CQMetabolite();

    virtual bool enter(const std::string & key);
    virtual bool leave();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual void setFramework(int framework);

  protected slots:
    virtual void languageChange();

  private:
    bool mChanged;
    bool mInitialNumberLastChanged;
    std::string mKey;
    CMetab * mpMetab;
    const CCompartment * mpCurrentCompartment;
    std::vector< int > mItemToType;
    double mInitialNumber;
    double mInitialConcentration;
    bool mExpressionValid;
    bool mInitialExpressionValid;

    void init();
    void load();
    void save();
    void destroy();
    void loadReactionTable();

  private slots:
    void slotBtnCommit();
    void slotBtnRevert();
    void slotBtnNew();
    void slotBtnDelete();
    void slotCompartmentChanged(int compartment);
    void slotTypeChanged(int type);
    void slotInitialTypeChanged(bool useInitialExpression);
    void slotNameLostFocus();
    void slotExpressionValid(bool valid);
    void slotInitialExpressionValid(bool valid);
    void slotReactionTableCurrentChanged(Q3ListViewItem * pItem);
    void slotInitialValueLostFocus();
  };

#endif // CQMETABOLITE_H
