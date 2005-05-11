/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportDefinition.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/11 17:43:08 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQReportDefinition.ui'
 **
 ** Created: Wed May 11 13:40:05 2005
 **      by: The User Interface Compiler ($Id: CQReportDefinition.cpp,v 1.2 2005/05/11 17:43:08 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQReportDefinition.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qtabwidget.h>
#include <qlistbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQReportDefinition.ui.h"

/*
 *  Constructs a CQReportDefinition which is a child of 'parent', with the
 *  name 'name'.' 
 */
CQReportDefinition::CQReportDefinition(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQReportDefinition");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  setMinimumSize(QSize(0, 0));
  CQReportDefinitionLayout = new QVBoxLayout(this, 11, 6, "CQReportDefinitionLayout");

  mpReportFrame = new QFrame(this, "mpReportFrame");
  mpReportFrame->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpReportFrame->sizePolicy().hasHeightForWidth()));
  mpReportFrame->setMinimumSize(QSize(0, 0));
  mpReportFrame->setMaximumSize(QSize(32767, 128));
  mpReportFrame->setFrameShape(QFrame::Box);
  mpReportFrame->setFrameShadow(QFrame::Sunken);
  mpReportFrameLayout = new QGridLayout(mpReportFrame, 1, 1, 11, 6, "mpReportFrameLayout");

  mpSeparatorLabel = new QLabel(mpReportFrame, "mpSeparatorLabel");
  mpSeparatorLabel->setMinimumSize(QSize(57, 0));
  mpSeparatorLabel->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpReportFrameLayout->addWidget(mpSeparatorLabel, 2, 0);

  mpNameLabel = new QLabel(mpReportFrame, "mpNameLabel");
  mpNameLabel->setMinimumSize(QSize(45, 0));
  mpNameLabel->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpReportFrameLayout->addWidget(mpNameLabel, 0, 0);

  mpCommentLabel = new QLabel(mpReportFrame, "mpCommentLabel");
  mpCommentLabel->setMinimumSize(QSize(53, 0));
  mpCommentLabel->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpReportFrameLayout->addWidget(mpCommentLabel, 1, 0);

  mpCommentEdit = new QTextEdit(mpReportFrame, "mpCommentEdit");
  mpCommentEdit->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, mpCommentEdit->sizePolicy().hasHeightForWidth()));
  mpCommentEdit->setMinimumSize(QSize(0, 50));
  mpCommentEdit->setResizePolicy(QTextEdit::Manual);

  mpReportFrameLayout->addMultiCellWidget(mpCommentEdit, 1, 1, 1, 3);

  mpName = new QLineEdit(mpReportFrame, "mpName");
  mpName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpName->sizePolicy().hasHeightForWidth()));
  mpName->setMinimumSize(QSize(150, 0));

  mpReportFrameLayout->addWidget(mpName, 0, 1);

  mpTaskBox = new QComboBox(FALSE, mpReportFrame, "mpTaskBox");
  mpTaskBox->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpTaskBox->sizePolicy().hasHeightForWidth()));
  mpTaskBox->setMinimumSize(QSize(150, 0));

  mpReportFrameLayout->addWidget(mpTaskBox, 0, 3);

  mpSeparator = new QLineEdit(mpReportFrame, "mpSeparator");
  mpSeparator->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpSeparator->sizePolicy().hasHeightForWidth()));
  mpSeparator->setMinimumSize(QSize(150, 0));

  mpReportFrameLayout->addWidget(mpSeparator, 2, 1);

  mpTabCheck = new QCheckBox(mpReportFrame, "mpTabCheck");

  mpReportFrameLayout->addWidget(mpTabCheck, 2, 2);

  mpTaskLabel = new QLabel(mpReportFrame, "mpTaskLabel");
  mpTaskLabel->setMinimumSize(QSize(45, 0));
  mpTaskLabel->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpReportFrameLayout->addWidget(mpTaskLabel, 0, 2);
  CQReportDefinitionLayout->addWidget(mpReportFrame);

  mpEditListsFrame = new QFrame(this, "mpEditListsFrame");
  mpEditListsFrame->setFrameShape(QFrame::Box);
  mpEditListsFrame->setFrameShadow(QFrame::Sunken);
  mpEditListsFrameLayout = new QHBoxLayout(mpEditListsFrame, 11, 6, "mpEditListsFrameLayout");

  layout2 = new QVBoxLayout(0, 0, 6, "layout2");

  mpBtnAdvanced = new QPushButton(mpEditListsFrame, "mpBtnAdvanced");
  mpBtnAdvanced->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpBtnAdvanced->sizePolicy().hasHeightForWidth()));
  mpBtnAdvanced->setMinimumSize(QSize(90, 0));
  mpBtnAdvanced->setMaximumSize(QSize(100, 32767));
  layout2->addWidget(mpBtnAdvanced);

  mpBtnItem = new QPushButton(mpEditListsFrame, "mpBtnItem");
  mpBtnItem->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpBtnItem->sizePolicy().hasHeightForWidth()));
  mpBtnItem->setMaximumSize(QSize(100, 32767));
  layout2->addWidget(mpBtnItem);

  mpBtnSeparator = new QPushButton(mpEditListsFrame, "mpBtnSeparator");
  mpBtnSeparator->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpBtnSeparator->sizePolicy().hasHeightForWidth()));
  mpBtnSeparator->setMaximumSize(QSize(100, 32767));
  layout2->addWidget(mpBtnSeparator);

  mpBtnText = new QPushButton(mpEditListsFrame, "mpBtnText");
  mpBtnText->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpBtnText->sizePolicy().hasHeightForWidth()));
  mpBtnText->setMaximumSize(QSize(100, 32767));
  layout2->addWidget(mpBtnText);

  mpBtnDelete = new QPushButton(mpEditListsFrame, "mpBtnDelete");
  mpBtnDelete->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpBtnDelete->sizePolicy().hasHeightForWidth()));
  mpBtnDelete->setMaximumSize(QSize(100, 32767));
  layout2->addWidget(mpBtnDelete);

  mpBtnUp = new QPushButton(mpEditListsFrame, "mpBtnUp");
  mpBtnUp->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpBtnUp->sizePolicy().hasHeightForWidth()));
  mpBtnUp->setMaximumSize(QSize(100, 32767));
  layout2->addWidget(mpBtnUp);

  mpBtnDown = new QPushButton(mpEditListsFrame, "mpBtnDown");
  mpBtnDown->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpBtnDown->sizePolicy().hasHeightForWidth()));
  mpBtnDown->setMaximumSize(QSize(100, 32767));
  layout2->addWidget(mpBtnDown);

  mpTitleCheck = new QCheckBox(mpEditListsFrame, "mpTitleCheck");
  mpTitleCheck->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpTitleCheck->sizePolicy().hasHeightForWidth()));
  mpTitleCheck->setMaximumSize(QSize(100, 32767));
  layout2->addWidget(mpTitleCheck);
  mpSpacerBtnLayout = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout2->addItem(mpSpacerBtnLayout);
  mpEditListsFrameLayout->addLayout(layout2);

  mpReportSectionTab = new QTabWidget(mpEditListsFrame, "mpReportSectionTab");
  mpReportSectionTab->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpReportSectionTab->sizePolicy().hasHeightForWidth()));
  mpReportSectionTab->setMinimumSize(QSize(0, 0));

  mpTableList = new QListBox(mpReportSectionTab, "mpTableList");
  mpReportSectionTab->insertTab(mpTableList, QString(""));

  mpHeaderList = new QListBox(mpReportSectionTab, "mpHeaderList");
  mpReportSectionTab->insertTab(mpHeaderList, QString(""));

  mpBodyList = new QListBox(mpReportSectionTab, "mpBodyList");
  mpReportSectionTab->insertTab(mpBodyList, QString(""));

  mpFooterList = new QListBox(mpReportSectionTab, "mpFooterList");
  mpReportSectionTab->insertTab(mpFooterList, QString(""));
  mpEditListsFrameLayout->addWidget(mpReportSectionTab);
  CQReportDefinitionLayout->addWidget(mpEditListsFrame);

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");

  mpBtnCommit = new QPushButton(this, "mpBtnCommit");
  mpBtnLayout->addWidget(mpBtnCommit);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");
  mpBtnLayout->addWidget(mpBtnRevert);

  mpBtnNewReport = new QPushButton(this, "mpBtnNewReport");
  mpBtnLayout->addWidget(mpBtnNewReport);

  mpBtnDeleteReport = new QPushButton(this, "mpBtnDeleteReport");
  mpBtnLayout->addWidget(mpBtnDeleteReport);
  CQReportDefinitionLayout->addLayout(mpBtnLayout);
  languageChange();
  resize(QSize(469, 463).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpName, SIGNAL(changed()), this, SLOT(nameChanged()));
  connect(mpTaskBox, SIGNAL(changed()), this, SLOT(taskChanged()));
  connect(mpCommentEdit, SIGNAL(changed()), this, SLOT(commentChanged()));
  connect(mpSeparator, SIGNAL(changed()), this, SLOT(separatorChanged()));
  connect(mpTabCheck, SIGNAL(clicked()), this, SLOT(chkTabClicked()));
  connect(mpTitleCheck, SIGNAL(clicked()), this, SLOT(chkTitleClicked()));
  connect(mpBtnAdvanced, SIGNAL(clicked()), this, SLOT(btnAdvancedClicked()));
  connect(mpBtnItem, SIGNAL(clicked()), this, SLOT(btnItemClicked()));
  connect(mpBtnSeparator, SIGNAL(clicked()), this, SLOT(btnSeparatorClicked()));
  connect(mpBtnText, SIGNAL(clicked()), this, SLOT(btnTextClicked()));
  connect(mpBtnDelete, SIGNAL(clicked()), this, SLOT(btnDeleteClicked()));
  connect(mpBtnUp, SIGNAL(clicked()), this, SLOT(btnUpClicked()));
  connect(mpBtnDown, SIGNAL(clicked()), this, SLOT(btnDownClicked()));
  connect(mpBtnCommit, SIGNAL(clicked()), this, SLOT(btnCommitClicked()));
  connect(mpBtnRevert, SIGNAL(clicked()), this, SLOT(btnRevertClicked()));
  connect(mpBtnNewReport, SIGNAL(clicked()), this, SLOT(btnNewReportClicked()));
  connect(mpBtnDeleteReport, SIGNAL(clicked()), this, SLOT(btnDeleteReportClicked()));

  // tab order
  setTabOrder(mpName, mpTaskBox);
  setTabOrder(mpTaskBox, mpCommentEdit);
  setTabOrder(mpCommentEdit, mpSeparator);
  setTabOrder(mpSeparator, mpTabCheck);
  setTabOrder(mpTabCheck, mpBtnAdvanced);
  setTabOrder(mpBtnAdvanced, mpBtnItem);
  setTabOrder(mpBtnItem, mpBtnSeparator);
  setTabOrder(mpBtnSeparator, mpBtnText);
  setTabOrder(mpBtnText, mpBtnDelete);
  setTabOrder(mpBtnDelete, mpBtnUp);
  setTabOrder(mpBtnUp, mpBtnDown);
  setTabOrder(mpBtnDown, mpTitleCheck);
  setTabOrder(mpTitleCheck, mpReportSectionTab);
  setTabOrder(mpReportSectionTab, mpBtnCommit);
  setTabOrder(mpBtnCommit, mpBtnRevert);
  setTabOrder(mpBtnRevert, mpBtnNewReport);
  setTabOrder(mpBtnNewReport, mpBtnDeleteReport);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQReportDefinition::~CQReportDefinition()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQReportDefinition::languageChange()
{
  setCaption(tr("Report"));
  mpSeparatorLabel->setText(tr("Separator"));
  mpNameLabel->setText(tr("Name"));
  mpCommentLabel->setText(tr("Comment"));
  mpTabCheck->setText(tr("<tab>"));
  mpTaskLabel->setText(tr("Task"));
  mpBtnAdvanced->setText(tr("Advanced >>"));
  mpBtnItem->setText(tr("Item"));
  mpBtnSeparator->setText(tr("Separator"));
  mpBtnText->setText(tr("Text"));
  mpBtnDelete->setText(tr("Delete"));
  mpBtnUp->setText(tr("Up"));
  mpBtnDown->setText(tr("Down"));
  mpTitleCheck->setText(tr("Title Row"));
  mpReportSectionTab->changeTab(mpTableList, tr("Table"));
  mpReportSectionTab->changeTab(mpHeaderList, tr("Header"));
  mpReportSectionTab->changeTab(mpBodyList, tr("Body"));
  mpReportSectionTab->changeTab(mpFooterList, tr("Footer"));
  mpBtnCommit->setText(tr("&Commit"));
  mpBtnCommit->setAccel(QKeySequence(tr("Alt+C")));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnRevert->setAccel(QKeySequence(QString::null));
  mpBtnNewReport->setText(tr("&New"));
  mpBtnNewReport->setAccel(QKeySequence(tr("Alt+N")));
  mpBtnDeleteReport->setText(tr("&Delete"));
  mpBtnDeleteReport->setAccel(QKeySequence(tr("Alt+D")));
}
