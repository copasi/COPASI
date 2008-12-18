// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportDefinition.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:10 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQREPORTDEFINITION_H
#define CQREPORTDEFINITION_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <Q3Frame>
#include <QLabel>
#include <Q3VBoxLayout>

class CReportDefinition;

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <Qt3Support/Q3VBoxLayout>
#include <Qt3Support/Q3ListBoxPixmap>

#include "copasiWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CQReportDefinition
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3Frame *mpReportFrame;
    Q3GridLayout *gridLayout;
    Q3TextEdit *mpCommentEdit;
    QLineEdit *mpName;
    QComboBox *mpTaskBox;
    Q3HBoxLayout *hboxLayout;
    QLineEdit *mpSeparator;
    QCheckBox *mpTabCheck;
    QLineEdit *mpPrecision;
    QLabel *mpPrecisionLabel;
    QLabel *mpTaskLabel;
    QLabel *mpSeparatorLabel;
    QLabel *mpNameLabel;
    QLabel *mpCommentLabel;
    Q3Frame *mpEditListsFrame;
    Q3HBoxLayout *hboxLayout1;
    Q3VBoxLayout *vboxLayout1;
    QPushButton *mpBtnAdvanced;
    QPushButton *mpBtnItem;
    QPushButton *mpBtnSeparator;
    QPushButton *mpBtnText;
    QPushButton *mpBtnDelete;
    QPushButton *mpBtnUp;
    QPushButton *mpBtnDown;
    QCheckBox *mpTitleCheck;
    QSpacerItem *mpSpacerBtnLayout;
    QTabWidget *mpReportSectionTab;
    Q3ListBox *mpTableList;
    Q3ListBox *mpHeaderList;
    Q3ListBox *mpBodyList;
    Q3ListBox *mpFooterList;
    Q3HBoxLayout *hboxLayout2;
    QPushButton *mpBtnCommit;
    QPushButton *mpBtnRevert;
    QPushButton *mpBtnNewReport;
    QPushButton *mpBtnDeleteReport;

    void setupUi(CopasiWidget *CQReportDefinition)
    {
      if (CQReportDefinition->objectName().isEmpty())
        CQReportDefinition->setObjectName(QString::fromUtf8("CQReportDefinition"));
      CQReportDefinition->resize(469, 463);
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(CQReportDefinition->sizePolicy().hasHeightForWidth());
      CQReportDefinition->setSizePolicy(sizePolicy);
      CQReportDefinition->setMinimumSize(QSize(0, 0));
      vboxLayout = new Q3VBoxLayout(CQReportDefinition);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      mpReportFrame = new Q3Frame(CQReportDefinition);
      mpReportFrame->setObjectName(QString::fromUtf8("mpReportFrame"));
      QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(0));
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(mpReportFrame->sizePolicy().hasHeightForWidth());
      mpReportFrame->setSizePolicy(sizePolicy1);
      mpReportFrame->setMinimumSize(QSize(0, 0));
      mpReportFrame->setMaximumSize(QSize(32767, 128));
      mpReportFrame->setFrameShape(Q3Frame::Box);
      mpReportFrame->setFrameShadow(Q3Frame::Sunken);
      gridLayout = new Q3GridLayout(mpReportFrame);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(11);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      mpCommentEdit = new Q3TextEdit(mpReportFrame);
      mpCommentEdit->setObjectName(QString::fromUtf8("mpCommentEdit"));
      QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(0));
      sizePolicy2.setHorizontalStretch(0);
      sizePolicy2.setVerticalStretch(0);
      sizePolicy2.setHeightForWidth(mpCommentEdit->sizePolicy().hasHeightForWidth());
      mpCommentEdit->setSizePolicy(sizePolicy2);
      mpCommentEdit->setMinimumSize(QSize(0, 50));
      mpCommentEdit->setResizePolicy(Q3ScrollView::Manual);

      gridLayout->addWidget(mpCommentEdit, 1, 1, 1, 4);

      mpName = new QLineEdit(mpReportFrame);
      mpName->setObjectName(QString::fromUtf8("mpName"));
      QSizePolicy sizePolicy3(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(0));
      sizePolicy3.setHorizontalStretch(0);
      sizePolicy3.setVerticalStretch(0);
      sizePolicy3.setHeightForWidth(mpName->sizePolicy().hasHeightForWidth());
      mpName->setSizePolicy(sizePolicy3);
      mpName->setMinimumSize(QSize(150, 0));

      gridLayout->addWidget(mpName, 0, 1, 1, 1);

      mpTaskBox = new QComboBox(mpReportFrame);
      mpTaskBox->setObjectName(QString::fromUtf8("mpTaskBox"));
      sizePolicy3.setHeightForWidth(mpTaskBox->sizePolicy().hasHeightForWidth());
      mpTaskBox->setSizePolicy(sizePolicy3);
      mpTaskBox->setMinimumSize(QSize(150, 0));

      gridLayout->addWidget(mpTaskBox, 0, 3, 1, 2);

      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpSeparator = new QLineEdit(mpReportFrame);
      mpSeparator->setObjectName(QString::fromUtf8("mpSeparator"));
      sizePolicy2.setHeightForWidth(mpSeparator->sizePolicy().hasHeightForWidth());
      mpSeparator->setSizePolicy(sizePolicy2);

      hboxLayout->addWidget(mpSeparator);

      mpTabCheck = new QCheckBox(mpReportFrame);
      mpTabCheck->setObjectName(QString::fromUtf8("mpTabCheck"));

      hboxLayout->addWidget(mpTabCheck);

      gridLayout->addLayout(hboxLayout, 2, 1, 1, 1);

      mpPrecision = new QLineEdit(mpReportFrame);
      mpPrecision->setObjectName(QString::fromUtf8("mpPrecision"));

      gridLayout->addWidget(mpPrecision, 2, 4, 1, 1);

      mpPrecisionLabel = new QLabel(mpReportFrame);
      mpPrecisionLabel->setObjectName(QString::fromUtf8("mpPrecisionLabel"));
      mpPrecisionLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpPrecisionLabel->setWordWrap(false);

      gridLayout->addWidget(mpPrecisionLabel, 2, 2, 1, 2);

      mpTaskLabel = new QLabel(mpReportFrame);
      mpTaskLabel->setObjectName(QString::fromUtf8("mpTaskLabel"));
      mpTaskLabel->setMinimumSize(QSize(45, 0));
      mpTaskLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpTaskLabel->setWordWrap(false);

      gridLayout->addWidget(mpTaskLabel, 0, 2, 1, 1);

      mpSeparatorLabel = new QLabel(mpReportFrame);
      mpSeparatorLabel->setObjectName(QString::fromUtf8("mpSeparatorLabel"));
      mpSeparatorLabel->setMinimumSize(QSize(62, 0));
      mpSeparatorLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpSeparatorLabel->setWordWrap(false);

      gridLayout->addWidget(mpSeparatorLabel, 2, 0, 1, 1);

      mpNameLabel = new QLabel(mpReportFrame);
      mpNameLabel->setObjectName(QString::fromUtf8("mpNameLabel"));
      mpNameLabel->setMinimumSize(QSize(62, 0));
      mpNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
      mpNameLabel->setWordWrap(false);

      gridLayout->addWidget(mpNameLabel, 0, 0, 1, 1);

      mpCommentLabel = new QLabel(mpReportFrame);
      mpCommentLabel->setObjectName(QString::fromUtf8("mpCommentLabel"));
      mpCommentLabel->setMinimumSize(QSize(62, 0));
      mpCommentLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
      mpCommentLabel->setWordWrap(false);

      gridLayout->addWidget(mpCommentLabel, 1, 0, 1, 1);

      vboxLayout->addWidget(mpReportFrame);

      mpEditListsFrame = new Q3Frame(CQReportDefinition);
      mpEditListsFrame->setObjectName(QString::fromUtf8("mpEditListsFrame"));
      mpEditListsFrame->setFrameShape(Q3Frame::Box);
      mpEditListsFrame->setFrameShadow(Q3Frame::Sunken);
      hboxLayout1 = new Q3HBoxLayout(mpEditListsFrame);
      hboxLayout1->setSpacing(6);
      hboxLayout1->setMargin(11);
      hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
      vboxLayout1 = new Q3VBoxLayout();
      vboxLayout1->setSpacing(6);
      vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
      mpBtnAdvanced = new QPushButton(mpEditListsFrame);
      mpBtnAdvanced->setObjectName(QString::fromUtf8("mpBtnAdvanced"));
      sizePolicy1.setHeightForWidth(mpBtnAdvanced->sizePolicy().hasHeightForWidth());
      mpBtnAdvanced->setSizePolicy(sizePolicy1);
      mpBtnAdvanced->setMinimumSize(QSize(90, 0));
      mpBtnAdvanced->setMaximumSize(QSize(112, 32767));

      vboxLayout1->addWidget(mpBtnAdvanced);

      mpBtnItem = new QPushButton(mpEditListsFrame);
      mpBtnItem->setObjectName(QString::fromUtf8("mpBtnItem"));
      sizePolicy1.setHeightForWidth(mpBtnItem->sizePolicy().hasHeightForWidth());
      mpBtnItem->setSizePolicy(sizePolicy1);
      mpBtnItem->setMaximumSize(QSize(112, 32767));

      vboxLayout1->addWidget(mpBtnItem);

      mpBtnSeparator = new QPushButton(mpEditListsFrame);
      mpBtnSeparator->setObjectName(QString::fromUtf8("mpBtnSeparator"));
      sizePolicy1.setHeightForWidth(mpBtnSeparator->sizePolicy().hasHeightForWidth());
      mpBtnSeparator->setSizePolicy(sizePolicy1);
      mpBtnSeparator->setMaximumSize(QSize(112, 32767));

      vboxLayout1->addWidget(mpBtnSeparator);

      mpBtnText = new QPushButton(mpEditListsFrame);
      mpBtnText->setObjectName(QString::fromUtf8("mpBtnText"));
      sizePolicy1.setHeightForWidth(mpBtnText->sizePolicy().hasHeightForWidth());
      mpBtnText->setSizePolicy(sizePolicy1);
      mpBtnText->setMaximumSize(QSize(112, 32767));

      vboxLayout1->addWidget(mpBtnText);

      mpBtnDelete = new QPushButton(mpEditListsFrame);
      mpBtnDelete->setObjectName(QString::fromUtf8("mpBtnDelete"));
      sizePolicy1.setHeightForWidth(mpBtnDelete->sizePolicy().hasHeightForWidth());
      mpBtnDelete->setSizePolicy(sizePolicy1);
      mpBtnDelete->setMaximumSize(QSize(112, 32767));

      vboxLayout1->addWidget(mpBtnDelete);

      mpBtnUp = new QPushButton(mpEditListsFrame);
      mpBtnUp->setObjectName(QString::fromUtf8("mpBtnUp"));
      sizePolicy1.setHeightForWidth(mpBtnUp->sizePolicy().hasHeightForWidth());
      mpBtnUp->setSizePolicy(sizePolicy1);
      mpBtnUp->setMaximumSize(QSize(112, 32767));

      vboxLayout1->addWidget(mpBtnUp);

      mpBtnDown = new QPushButton(mpEditListsFrame);
      mpBtnDown->setObjectName(QString::fromUtf8("mpBtnDown"));
      sizePolicy1.setHeightForWidth(mpBtnDown->sizePolicy().hasHeightForWidth());
      mpBtnDown->setSizePolicy(sizePolicy1);
      mpBtnDown->setMaximumSize(QSize(112, 32767));

      vboxLayout1->addWidget(mpBtnDown);

      mpTitleCheck = new QCheckBox(mpEditListsFrame);
      mpTitleCheck->setObjectName(QString::fromUtf8("mpTitleCheck"));
      sizePolicy1.setHeightForWidth(mpTitleCheck->sizePolicy().hasHeightForWidth());
      mpTitleCheck->setSizePolicy(sizePolicy1);
      mpTitleCheck->setMaximumSize(QSize(112, 32767));

      vboxLayout1->addWidget(mpTitleCheck);

      mpSpacerBtnLayout = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

      vboxLayout1->addItem(mpSpacerBtnLayout);

      hboxLayout1->addLayout(vboxLayout1);

      mpReportSectionTab = new QTabWidget(mpEditListsFrame);
      mpReportSectionTab->setObjectName(QString::fromUtf8("mpReportSectionTab"));
      sizePolicy.setHeightForWidth(mpReportSectionTab->sizePolicy().hasHeightForWidth());
      mpReportSectionTab->setSizePolicy(sizePolicy);
      mpReportSectionTab->setMinimumSize(QSize(0, 0));
      mpTableList = new Q3ListBox();
      mpTableList->setObjectName(QString::fromUtf8("mpTableList"));
      mpReportSectionTab->addTab(mpTableList, QString());
      mpHeaderList = new Q3ListBox();
      mpHeaderList->setObjectName(QString::fromUtf8("mpHeaderList"));
      mpReportSectionTab->addTab(mpHeaderList, QString());
      mpBodyList = new Q3ListBox();
      mpBodyList->setObjectName(QString::fromUtf8("mpBodyList"));
      mpReportSectionTab->addTab(mpBodyList, QString());
      mpFooterList = new Q3ListBox();
      mpFooterList->setObjectName(QString::fromUtf8("mpFooterList"));
      mpReportSectionTab->addTab(mpFooterList, QString());

      hboxLayout1->addWidget(mpReportSectionTab);

      vboxLayout->addWidget(mpEditListsFrame);

      hboxLayout2 = new Q3HBoxLayout();
      hboxLayout2->setSpacing(6);
      hboxLayout2->setMargin(0);
      hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
      mpBtnCommit = new QPushButton(CQReportDefinition);
      mpBtnCommit->setObjectName(QString::fromUtf8("mpBtnCommit"));

      hboxLayout2->addWidget(mpBtnCommit);

      mpBtnRevert = new QPushButton(CQReportDefinition);
      mpBtnRevert->setObjectName(QString::fromUtf8("mpBtnRevert"));

      hboxLayout2->addWidget(mpBtnRevert);

      mpBtnNewReport = new QPushButton(CQReportDefinition);
      mpBtnNewReport->setObjectName(QString::fromUtf8("mpBtnNewReport"));

      hboxLayout2->addWidget(mpBtnNewReport);

      mpBtnDeleteReport = new QPushButton(CQReportDefinition);
      mpBtnDeleteReport->setObjectName(QString::fromUtf8("mpBtnDeleteReport"));

      hboxLayout2->addWidget(mpBtnDeleteReport);

      vboxLayout->addLayout(hboxLayout2);

      QWidget::setTabOrder(mpName, mpTaskBox);
      QWidget::setTabOrder(mpTaskBox, mpCommentEdit);
      QWidget::setTabOrder(mpCommentEdit, mpSeparator);
      QWidget::setTabOrder(mpSeparator, mpTabCheck);
      QWidget::setTabOrder(mpTabCheck, mpBtnAdvanced);
      QWidget::setTabOrder(mpBtnAdvanced, mpBtnItem);
      QWidget::setTabOrder(mpBtnItem, mpBtnSeparator);
      QWidget::setTabOrder(mpBtnSeparator, mpBtnText);
      QWidget::setTabOrder(mpBtnText, mpBtnDelete);
      QWidget::setTabOrder(mpBtnDelete, mpBtnUp);
      QWidget::setTabOrder(mpBtnUp, mpBtnDown);
      QWidget::setTabOrder(mpBtnDown, mpTitleCheck);
      QWidget::setTabOrder(mpTitleCheck, mpReportSectionTab);
      QWidget::setTabOrder(mpReportSectionTab, mpBtnCommit);
      QWidget::setTabOrder(mpBtnCommit, mpBtnRevert);
      QWidget::setTabOrder(mpBtnRevert, mpBtnNewReport);
      QWidget::setTabOrder(mpBtnNewReport, mpBtnDeleteReport);

      retranslateUi(CQReportDefinition);
      QObject::connect(mpName, SIGNAL(textChanged(QString)), CQReportDefinition, SLOT(nameChanged(QString)));
      QObject::connect(mpTaskBox, SIGNAL(activated(QString)), CQReportDefinition, SLOT(taskChanged(QString)));
      QObject::connect(mpCommentEdit, SIGNAL(textChanged()), CQReportDefinition, SLOT(commentChanged()));
      QObject::connect(mpSeparator, SIGNAL(textChanged(QString)), CQReportDefinition, SLOT(separatorChanged(QString)));
      QObject::connect(mpPrecision, SIGNAL(textChanged(QString)), CQReportDefinition, SLOT(precisionChanged(QString)));
      QObject::connect(mpTabCheck, SIGNAL(clicked()), CQReportDefinition, SLOT(chkTabClicked()));
      QObject::connect(mpTitleCheck, SIGNAL(clicked()), CQReportDefinition, SLOT(chkTitleClicked()));
      QObject::connect(mpBtnAdvanced, SIGNAL(clicked()), CQReportDefinition, SLOT(btnAdvancedClicked()));
      QObject::connect(mpBtnItem, SIGNAL(clicked()), CQReportDefinition, SLOT(btnItemClicked()));
      QObject::connect(mpBtnSeparator, SIGNAL(clicked()), CQReportDefinition, SLOT(btnSeparatorClicked()));
      QObject::connect(mpBtnText, SIGNAL(clicked()), CQReportDefinition, SLOT(btnTextClicked()));
      QObject::connect(mpBtnDelete, SIGNAL(clicked()), CQReportDefinition, SLOT(btnDeleteClicked()));
      QObject::connect(mpBtnUp, SIGNAL(clicked()), CQReportDefinition, SLOT(btnUpClicked()));
      QObject::connect(mpBtnDown, SIGNAL(clicked()), CQReportDefinition, SLOT(btnDownClicked()));
      QObject::connect(mpBtnCommit, SIGNAL(clicked()), CQReportDefinition, SLOT(btnCommitClicked()));
      QObject::connect(mpBtnRevert, SIGNAL(clicked()), CQReportDefinition, SLOT(btnRevertClicked()));
      QObject::connect(mpBtnNewReport, SIGNAL(clicked()), CQReportDefinition, SLOT(btnNewReportClicked()));
      QObject::connect(mpBtnDeleteReport, SIGNAL(clicked()), CQReportDefinition, SLOT(btnDeleteReportClicked()));

      QMetaObject::connectSlotsByName(CQReportDefinition);
    } // setupUi

    void retranslateUi(CopasiWidget *CQReportDefinition)
    {
      CQReportDefinition->setCaption(QApplication::translate("CQReportDefinition", "Report", 0, QApplication::UnicodeUTF8));
      mpTabCheck->setText(QApplication::translate("CQReportDefinition", "<tab>", 0, QApplication::UnicodeUTF8));
      mpPrecisionLabel->setText(QApplication::translate("CQReportDefinition", "Precision", 0, QApplication::UnicodeUTF8));
      mpTaskLabel->setText(QApplication::translate("CQReportDefinition", "Task", 0, QApplication::UnicodeUTF8));
      mpSeparatorLabel->setText(QApplication::translate("CQReportDefinition", "Separator", 0, QApplication::UnicodeUTF8));
      mpNameLabel->setText(QApplication::translate("CQReportDefinition", "Name", 0, QApplication::UnicodeUTF8));
      mpCommentLabel->setText(QApplication::translate("CQReportDefinition", "Comment", 0, QApplication::UnicodeUTF8));
      mpBtnAdvanced->setText(QApplication::translate("CQReportDefinition", "Advanced >>", 0, QApplication::UnicodeUTF8));
      mpBtnItem->setText(QApplication::translate("CQReportDefinition", "Item", 0, QApplication::UnicodeUTF8));
      mpBtnSeparator->setText(QApplication::translate("CQReportDefinition", "Separator", 0, QApplication::UnicodeUTF8));
      mpBtnText->setText(QApplication::translate("CQReportDefinition", "Text", 0, QApplication::UnicodeUTF8));
      mpBtnDelete->setText(QApplication::translate("CQReportDefinition", "Delete", 0, QApplication::UnicodeUTF8));
      mpBtnUp->setText(QApplication::translate("CQReportDefinition", "Up", 0, QApplication::UnicodeUTF8));
      mpBtnDown->setText(QApplication::translate("CQReportDefinition", "Down", 0, QApplication::UnicodeUTF8));
      mpTitleCheck->setText(QApplication::translate("CQReportDefinition", "Title Row", 0, QApplication::UnicodeUTF8));
      mpReportSectionTab->setTabText(mpReportSectionTab->indexOf(mpTableList), QApplication::translate("CQReportDefinition", "Table", 0, QApplication::UnicodeUTF8));
      mpReportSectionTab->setTabText(mpReportSectionTab->indexOf(mpHeaderList), QApplication::translate("CQReportDefinition", "Header", 0, QApplication::UnicodeUTF8));
      mpReportSectionTab->setTabText(mpReportSectionTab->indexOf(mpBodyList), QApplication::translate("CQReportDefinition", "Body", 0, QApplication::UnicodeUTF8));
      mpReportSectionTab->setTabText(mpReportSectionTab->indexOf(mpFooterList), QApplication::translate("CQReportDefinition", "Footer", 0, QApplication::UnicodeUTF8));
      mpBtnCommit->setText(QApplication::translate("CQReportDefinition", "&Commit", 0, QApplication::UnicodeUTF8));
      mpBtnCommit->setShortcut(QApplication::translate("CQReportDefinition", "Alt+C", 0, QApplication::UnicodeUTF8));
      mpBtnRevert->setText(QApplication::translate("CQReportDefinition", "Revert", 0, QApplication::UnicodeUTF8));
      mpBtnRevert->setShortcut(QString());
      mpBtnNewReport->setText(QApplication::translate("CQReportDefinition", "&New", 0, QApplication::UnicodeUTF8));
      mpBtnNewReport->setShortcut(QApplication::translate("CQReportDefinition", "Alt+N", 0, QApplication::UnicodeUTF8));
      mpBtnDeleteReport->setText(QApplication::translate("CQReportDefinition", "&Delete", 0, QApplication::UnicodeUTF8));
      mpBtnDeleteReport->setShortcut(QApplication::translate("CQReportDefinition", "Alt+D", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(CQReportDefinition);
    } // retranslateUi
  };

namespace Ui
  {
  class CQReportDefinition: public Ui_CQReportDefinition {};
} // namespace Ui

QT_END_NAMESPACE

class CQReportDefinition : public CopasiWidget, public Ui::CQReportDefinition
  {
    Q_OBJECT

  public:
    CQReportDefinition(QWidget* parent = 0, const char* name = 0);
    ~CQReportDefinition();

    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected slots:
    virtual void languageChange();

  private:
    bool mAdvanced;
    bool mChanged;
    std::string mKey;
    CReportDefinition * mpReportDefinition;

    void init();
    void destroy();
    bool load();
    bool save();
    bool setAdvancedMode(const bool & advanced);

  private slots:
    void nameChanged(const QString & string);
    void taskChanged(const QString & string);
    void commentChanged();
    void separatorChanged(const QString & string);
    void precisionChanged(const QString & string);
    void chkTabClicked();
    void btnAdvancedClicked();
    void btnItemClicked();
    void btnSeparatorClicked();
    void btnTextClicked();
    void btnDeleteClicked();
    void btnUpClicked();
    void btnDownClicked();
    void chkTitleClicked();
    void btnDeleteReportClicked();
    void btnNewReportClicked();
    void btnRevertClicked();
    void btnCommitClicked();
  };

#endif // CQREPORTDEFINITION_H
