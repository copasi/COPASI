// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQReportDefinitionSelect.h"

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "CQMessageBox.h"
#include "CopasiFileDialog.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/CopasiDataModel/CDataModel.h"

CQReportDefinitionSelect::CQReportDefinitionSelect(QWidget * parent, Qt::WindowFlags f) :
  QDialog(parent, f),
  mpListView(static_cast< ListViews * >(parent)),
  mpReport(NULL),
  mShow(true)
{
  setupUi(this);

  mpBtnEdit->setIcon(CQIconResource::icon(CQIconResource::edit));
  mpBtnBrowse->setIcon(CQIconResource::icon(CQIconResource::fileOpen));
}

CQReportDefinitionSelect::~CQReportDefinitionSelect()
{
  cleanup();
}

void CQReportDefinitionSelect::cleanup()
{
  mpReport = NULL;
}

void CQReportDefinitionSelect::setReport(CReport * newReport)
{
  mpReport = newReport;
}

void CQReportDefinitionSelect::loadReportDefinitionVector()
{
  CDataModel* pDataModel = mpListView->getDataModel();
  assert(pDataModel != NULL);
  CReportDefinitionVector* pReportDefinitionVector = pDataModel->getReportDefinitionList();
  unsigned C_INT32 i;

  for (i = 0; i < pReportDefinitionVector->size(); i++)
    mpComboDefinition->
    insertItem(mpComboDefinition->count(), FROM_UTF8(pReportDefinitionVector->operator[](i).getObjectName()));

  // if it is an empty list
  if (mpComboDefinition->count() == 0)
    {
      std::string name = "ReportDefinition_0";
      pDataModel->getReportDefinitionList()->createReportDefinition(name, "");
      mpComboDefinition->insertItem(mpComboDefinition->count(), FROM_UTF8(name));
      mpComboDefinition->setCurrentIndex(1);
      mpReport->setReportDefinition(&pDataModel->getReportDefinitionList()->operator[](0)); //first one report definition
      mpReport->setAppend(mpCheckAppend->isChecked());
      mpReport->setConfirmOverwrite(mpCheckConfirmOverwrite->isChecked());
      mpReport->setTarget(TO_UTF8(mpEditTarget->text()));
      mpListView->getDataModelGUI()->notify(ListViews::ObjectType::REPORT, ListViews::CHANGE, std::string()); //notify Table Definition to

      if (CQMessageBox::question(ListViews::ancestor(this), "No Report Template Defined",
                                 "No report definition defined, COPASI has already created a new one for you.\n Do you want to switch to the GUI to edit it?",
                                 QMessageBox::Ok | QMessageBox::No, QMessageBox::Ok) == QMessageBox::Ok)
        slotEdit();

      return;
    }

  if (!mpReport->getReportDefinition())
    {
      C_INT32 row;
      row = mpComboDefinition->currentIndex();
      mpReport->setReportDefinition(&pReportDefinitionVector->operator[](row));
      mpReport->setAppend(mpCheckAppend->isChecked());
      mpReport->setConfirmOverwrite(mpCheckConfirmOverwrite->isChecked());
      mpReport->setTarget(TO_UTF8(mpEditTarget->text()));
      return;
    }
  else
    {
      C_INT32 i;

      // no use to compare the last one
      for (i = mpComboDefinition->count() - 1; i >= 1; i--)
        if (mpComboDefinition->itemText(i) == FROM_UTF8(mpReport->getReportDefinition()->getObjectName()))
          break;

      mpComboDefinition->setCurrentIndex(i);
      mpCheckAppend->setChecked(mpReport->append());
      mpCheckConfirmOverwrite->setChecked(mpReport->confirmOverwrite());
      mpEditTarget->setText(FROM_UTF8(mpReport->getTarget()));
    }
}

int CQReportDefinitionSelect::exec()
{
  if (mShow)
    return QDialog::exec();
  else
    return QDialog::Accepted;
}

void CQReportDefinitionSelect::accept()
{
  if (!mpReport)
    //exception made here
    return;

  CDataModel* pDataModel = mpListView->getDataModel();
  assert(pDataModel != NULL);
  CReportDefinitionVector* pReportDefinitionVector = pDataModel->getReportDefinitionList();
  C_INT32 row;
  row = mpComboDefinition->currentIndex();
  mpReport->setReportDefinition(&pReportDefinitionVector->operator[](row));
  mpReport->setAppend(mpCheckAppend->isChecked());
  mpReport->setConfirmOverwrite(mpCheckConfirmOverwrite->isChecked());
  mpReport->setTarget(TO_UTF8(mpEditTarget->text()));
  cleanup();
  QDialog::done(QDialog::Accepted);
}

void CQReportDefinitionSelect::reject()
{
  cleanup();
  QDialog::done(QDialog::Rejected);
}

void CQReportDefinitionSelect::slotEdit()
{
  CDataModel* pDataModel = mpListView->getDataModel();
  assert(pDataModel != NULL);
  CReportDefinitionVector* pReportDefinitionVector = pDataModel->getReportDefinitionList();
  C_INT32 row;
  row = mpComboDefinition->currentIndex();
  mpListView->switchToOtherWidget(ListViews::WidgetType::ReportTemplateDetail, pReportDefinitionVector->operator[](row).getCN());
  accept(); // if shown then close
  mShow = false; // if not shown then close
}

void CQReportDefinitionSelect::slotBrowse()
{
  QString reportFile =
    CopasiFileDialog::getSaveFileName(this, "Save File Dialog", CopasiFileDialog::getDefaultFileName(".txt"), "TEXT Files (*.txt)",
                                      "Choose to create a new a file");

  if (!reportFile.isNull())
    {
      mpEditTarget->setText(reportFile);
    }
}
