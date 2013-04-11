// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "CQReportTemplateSelect.h"

#include "copasi.h"

#include "qtUtilities.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "CQMessageBox.h"
#include "CopasiFileDialog.h"

#include "resourcesUI/CQIconResource.h"

#include "report/CCopasiRootContainer.h"
#include "report/CReportTemplateVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"

CQReportTemplateSelect::CQReportTemplateSelect(QWidget * parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    mpListView(static_cast< ListViews * >(parent)),
    mpReport(NULL),
    mShow(true)
{
  setupUi(this);

  mpBtnEdit->setIcon(CQIconResource::icon(CQIconResource::edit));
  mpBtnBrowse->setIcon(CQIconResource::icon(CQIconResource::fileOpen));

}

CQReportTemplateSelect::~CQReportTemplateSelect()
{
  cleanup();
}

void CQReportTemplateSelect::cleanup()
{
  mpReport = NULL;
}

void CQReportTemplateSelect::setReport(CReport * newReport)
{
  mpReport = newReport;
}

void CQReportTemplateSelect::loadReportTemplateVector()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CReportTemplateVector* pReportTemplateVector = (*CCopasiRootContainer::getDatamodelList())[0]->getReportTemplateList();
  unsigned C_INT32 i;

  for (i = 0; i < pReportTemplateVector->size(); i++)
    mpComboDefinition->
    insertItem(mpComboDefinition->count(), FROM_UTF8((*(pReportTemplateVector))[i]->getObjectName()));

  // if it is an empty list
  if (mpComboDefinition->count() == 0)
    {
      std::string name = "ReportTemplate_0";
      (*CCopasiRootContainer::getDatamodelList())[0]->getReportTemplateList()->createReportTemplate(name, "");
      mpComboDefinition->insertItem(mpComboDefinition->count(), FROM_UTF8(name));
      mpComboDefinition->setCurrentIndex(1);
      mpReport->setReportTemplate((*(*CCopasiRootContainer::getDatamodelList())[0]->getReportTemplateList())[0]); //first one report template
      mpReport->setAppend(mpCheckAppend->isChecked());
      mpReport->setConfirmOverwrite(mpCheckConfirmOverwrite->isChecked());
      mpReport->setTarget(TO_UTF8(mpEditTarget->text()));
      mpListView->getDataModel()->notify(ListViews::REPORT, ListViews::CHANGE, ""); //notify Table Definition to

      if (CQMessageBox::question(NULL, "No Report Template Defined",
                                 "No report template defined, COPASI has already created a new one for you.\n Do you want to switch to the GUI to edit it?",
                                 QMessageBox::Ok | QMessageBox::No, QMessageBox::Ok) == QMessageBox::Ok)
        slotEdit();

      return;
    }

  if (!mpReport->getReportTemplate())
    {
      C_INT32 row;
      row = mpComboDefinition->currentIndex();
      mpReport->setReportTemplate((*(pReportTemplateVector))[row]);
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
        if (mpComboDefinition->itemText(i) == FROM_UTF8(mpReport->getReportTemplate()->getObjectName()))
          break;

      mpComboDefinition->setCurrentIndex(i);
      mpCheckAppend->setChecked(mpReport->append());
      mpCheckConfirmOverwrite->setChecked(mpReport->confirmOverwrite());
      mpEditTarget->setText(FROM_UTF8(mpReport->getTarget()));
    }
}

int CQReportTemplateSelect::exec()
{
  if (mShow)
    return QDialog::exec();
  else
    return QDialog::Accepted;
}

void CQReportTemplateSelect::accept()
{
  if (!mpReport)
    //exception made here
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CReportTemplateVector* pReportTemplateVector = (*CCopasiRootContainer::getDatamodelList())[0]->getReportTemplateList();
  C_INT32 row;
  row = mpComboDefinition->currentIndex();
  mpReport->setReportTemplate((*(pReportTemplateVector))[row]);
  mpReport->setAppend(mpCheckAppend->isChecked());
  mpReport->setConfirmOverwrite(mpCheckConfirmOverwrite->isChecked());
  mpReport->setTarget(TO_UTF8(mpEditTarget->text()));
  cleanup();
  QDialog::done(QDialog::Accepted);
}

void CQReportTemplateSelect::reject()
{
  cleanup();
  QDialog::done(QDialog::Rejected);
}

void CQReportTemplateSelect::slotEdit()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CReportTemplateVector* pReportTemplateVector = (*CCopasiRootContainer::getDatamodelList())[0]->getReportTemplateList();
  C_INT32 row;
  row = mpComboDefinition->currentIndex();
  mpListView->switchToOtherWidget(C_INVALID_INDEX, (*pReportTemplateVector)[row]->getKey());
  accept(); // if shown then close
  mShow = false; // if not shown then close
}

void CQReportTemplateSelect::slotBrowse()
{
  QString reportFile =
    CopasiFileDialog::getSaveFileName(this, "Save File Dialog", "untitled.txt", "TEXT Files (*.txt)",
                                      "Choose to create a new a file");

  if (!reportFile.isNull())
    {
      mpEditTarget->setText(reportFile);
    }
}

