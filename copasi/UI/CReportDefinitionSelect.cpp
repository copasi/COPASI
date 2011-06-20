// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CReportDefinitionSelect.cpp,v $
//   $Revision: 1.56 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/20 16:07:09 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description:
Date: 08/15
Comment : CReportDefinitionSelect to select the report definition for one task
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QLayout>
#include <QToolTip>
#include <QWhatsThis>
#include <QFileDialog>

#include "copasi.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "CReportDefinitionSelect.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CCopasiException.h"
#include "report/CReportDefinitionVector.h"
#include "report/CReport.h"

/*
 *  Constructs a CReportDefinitionSelect as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */

CReportDefinitionSelect::CReportDefinitionSelect(QWidget* parent, const char* name, Qt::WFlags fl)
    : QDialog(parent, fl),
    pListView((ListViews*)parent),
    mpReport(NULL),
    bShow(true)
{
  setObjectName(QString::fromUtf8(name));

  if (!name)
    setObjectName("CReportDefinitionSelect");

  CReportDefinitionSelectLayout = new QGridLayout(this);
  CReportDefinitionSelectLayout->setMargin(11);
  CReportDefinitionSelectLayout->setSpacing(6);
  CReportDefinitionSelectLayout->setObjectName("CReportDefinitionSelectLayout");


  frame5 = new QFrame(this);
  frame5->setObjectName("frame5");
  frame5->setFrameShape(QFrame::Box);
  frame5->setFrameShadow(QFrame::Sunken);
  frame5Layout = new QGridLayout(frame5);
  frame5Layout->setMargin(11);
  frame5Layout->setSpacing(6);
  frame5Layout->setObjectName("frame5Layout");

  reportLabel = new QLabel(frame5);
  reportLabel->setObjectName("reportLabel");

  frame5Layout->addWidget(reportLabel, 0, 0);

  targetLabel = new QLabel(frame5);
  targetLabel->setObjectName("targetLabel");

  frame5Layout->addWidget(targetLabel, 1, 0);

  appendChecked = new QCheckBox(frame5);
  appendChecked->setObjectName("appendChecked");

  frame5Layout->addWidget(appendChecked, 2, 2, 1, 2);

  reportDefinitionNameList = new QComboBox(frame5);
  reportDefinitionNameList->setObjectName("reportDefinitionNameList");

  frame5Layout->addWidget(reportDefinitionNameList, 0, 1);

  jumpButton = new QPushButton(frame5);
  jumpButton->setObjectName("jumpButton");

  frame5Layout->addWidget(jumpButton, 0, 2);

  targetEdit = new QLineEdit(frame5);
  targetEdit->setObjectName("targetEdit");
  targetEdit->setFrame(true);
  //targetEdit->setFrameShape(QLineEdit::LineEditPanel);
  //targetEdit->setFrameShadow(QLineEdit::Sunken);

  frame5Layout->addWidget(targetEdit, 1, 1);

  browseButton = new QPushButton(frame5);
  browseButton->setObjectName("browseButton");

  frame5Layout->addWidget(browseButton, 1, 2);

  CReportDefinitionSelectLayout->addWidget(frame5, 0, 0, 0, 1);

  confirmButton = new QPushButton(this);
  confirmButton->setObjectName("confirmButton");

  CReportDefinitionSelectLayout->addWidget(confirmButton, 1, 0);

  cancelButton = new QPushButton(this);
  cancelButton->setObjectName("cancelButton");


  CReportDefinitionSelectLayout->addWidget(cancelButton, 1, 1);

  reportLabel->setText(tr("ReportDefinitions"));
  targetLabel->setText(tr("Target"));
  appendChecked->setText(tr("Append"));
  jumpButton->setText(tr("edit"));
  browseButton->setText(tr("browse"));
  confirmButton->setText(tr("Confirm"));
  cancelButton->setText(tr("Cancel"));

  // tab order
  setTabOrder(reportDefinitionNameList, confirmButton);
  setTabOrder(confirmButton, cancelButton);
  setTabOrder(cancelButton, jumpButton);
  setTabOrder(jumpButton, targetEdit);
  setTabOrder(targetEdit, browseButton);
  setTabOrder(browseButton, appendChecked);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
  connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirmClicked()));
  connect(jumpButton, SIGNAL(clicked()), this, SLOT(jumpToReportDefinitionEdit()));
  connect(browseButton, SIGNAL(clicked()), this, SLOT(jumpToFileBrowser()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CReportDefinitionSelect::~CReportDefinitionSelect()
{
  cleanup();
  // no need to delete child widgets, Qt does it all for us
}

void CReportDefinitionSelect::loadReportDefinitionVector()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CReportDefinitionVector* pReportDefinitionVector = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList();
  unsigned C_INT32 i;

  for (i = 0; i < pReportDefinitionVector->size(); i++)
    reportDefinitionNameList->
    insertItem(reportDefinitionNameList->count(), FROM_UTF8((*(pReportDefinitionVector))[i]->getObjectName()));

  // if it is an empty list
  if (reportDefinitionNameList->count() == 0)
    {
      std::string name = "ReportDefinition_0";
      (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->createReportDefinition(name, "");
      reportDefinitionNameList->insertItem(reportDefinitionNameList->count(), FROM_UTF8(name));
      reportDefinitionNameList->setCurrentIndex(1);
      mpReport->setReportDefinition((*(*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList())[0]); //first one report definition
      mpReport->setAppend(appendChecked->isChecked());
      mpReport->setTarget(TO_UTF8(targetEdit->text()));
      pListView->getDataModel()->notify(ListViews::REPORT, ListViews::CHANGE, ""); //notify Table Definition to

      if (CQMessageBox::question(NULL, "No Report Definition Defined",
                                 "No report definition defined, COPASI has already created a new one for you.\n Do you want to switch to the GUI to edit it?",
                                 QMessageBox::Ok | QMessageBox::No, QMessageBox::Ok) == QMessageBox::Ok)
        jumpToReportDefinitionEdit();

      return;
    }

  if (!mpReport->getReportDefinition())
    {
      C_INT32 row;
      row = reportDefinitionNameList->currentIndex();
      mpReport->setReportDefinition((*(pReportDefinitionVector))[row]);
      mpReport->setAppend(appendChecked->isChecked());
      mpReport->setTarget(TO_UTF8(targetEdit->text()));
      return;
    }
  else
    {
      C_INT32 i;

      // no use to compare the last one
      for (i = reportDefinitionNameList->count() - 1; i >= 1; i--)
        if (reportDefinitionNameList->itemText(i) == FROM_UTF8(mpReport->getReportDefinition()->getObjectName()))
          break;

      reportDefinitionNameList->setCurrentIndex(i);
      appendChecked->setChecked(mpReport->append());
      targetEdit->setText(FROM_UTF8(mpReport->getTarget()));
    }
}

void CReportDefinitionSelect::cancelClicked()
{
  cleanup();
  QDialog::done(QDialog::Rejected);
  // delete this;
}

void CReportDefinitionSelect::confirmClicked()
{
  if (!mpReport)
    //exception made here
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CReportDefinitionVector* pReportDefinitionVector = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList();
  C_INT32 row;
  row = reportDefinitionNameList->currentIndex();
  mpReport->setReportDefinition((*(pReportDefinitionVector))[row]);
  mpReport->setAppend(appendChecked->isChecked());
  mpReport->setTarget(TO_UTF8(targetEdit->text()));
  cleanup();
  QDialog::done(QDialog::Accepted);
  //  delete this;
}

void CReportDefinitionSelect::cleanup()
{
  mpReport = NULL;
}

void CReportDefinitionSelect::jumpToReportDefinitionEdit()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CReportDefinitionVector* pReportDefinitionVector = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList();
  C_INT32 row;
  row = reportDefinitionNameList->currentIndex();
  pListView->switchToOtherWidget(0, (*pReportDefinitionVector)[row]->getKey());
  confirmClicked(); // if shown then close
  bShow = false; // if not shown then close
}

void CReportDefinitionSelect::jumpToFileBrowser()
{
  QString reportFile =
    CopasiFileDialog::getSaveFileName(this, "Save File Dialog", "untitled.txt", "TEXT Files (*.txt)",
                                      "Choose to create a new a file");

  if (!reportFile.isNull())
    {
      targetEdit->setText(reportFile);
    }
}

void CReportDefinitionSelect::setReport(CReport* newReport)
{
  mpReport = newReport;
}

int CReportDefinitionSelect::exec()
{
  if (bShow)
    return QDialog::exec();
  else
    return QDialog::Accepted;
}
