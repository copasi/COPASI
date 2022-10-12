// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQSEDMLImportDialog.h"

#include "qtUtilities.h"

#include <QFileDialog>

CQSEDMLImportDialog::CQSEDMLImportDialog(QWidget * parent)
  : QDialog(parent)
  , mInfo(NULL)
{
  setupUi(this);
}

CQSEDMLImportDialog::~CQSEDMLImportDialog()
{
}

void CQSEDMLImportDialog::loadSedML(SedmlInfo & info)
{
  mInfo = info;
  lstPlots->clear();
  cbmReportSelect->clear();
  cbmTaskSelect->clear();

for (auto & item : info.getTaskNames())
    {
      cbmTaskSelect->addItem(FROM_UTF8(item.second), FROM_UTF8(item.first));
    }

  int index = cbmTaskSelect->findData(FROM_UTF8(mInfo.getFirstTaskWithOutput()));

  if (index < 0)
    index = 0;

  cbmTaskSelect->setCurrentIndex(index);
}

SedmlImportOptions CQSEDMLImportDialog::getOptions()
{
  std::string taskId = TO_UTF8(cbmTaskSelect->currentData().toString());
  auto modelId = mInfo.getFirstModel(taskId);
  std::vector< std::string > plots;

for (auto * pItem : lstPlots->selectedItems())
    plots.push_back(TO_UTF8(pItem->data(Qt::UserRole).toString()));

  auto result = SedmlImportOptions(
                  taskId,
                  modelId,
                  plots,
                  TO_UTF8(cbmReportSelect->currentData().toString()),
                  TO_UTF8(txtReportFilename->text()));

  return result;
}

void CQSEDMLImportDialog::slotReportSelected(const QString & report)
{
  txtReportFilename->setText(FROM_UTF8(mInfo.getReportFileName(TO_UTF8(report))));
}

void CQSEDMLImportDialog::slotTaskSelected(const QString & task)
{
  lstPlots->clear();
  cbmReportSelect->clear();

  std::string taskId = TO_UTF8(cbmTaskSelect->currentData().toString());

for (auto & report : mInfo.getReportsForTask(taskId))
    {
      cbmReportSelect->addItem(FROM_UTF8(report.second), FROM_UTF8(report.first));
    }

for (auto & plot : mInfo.getPlotsForTask(taskId))
    {
      QListWidgetItem * pItem = new QListWidgetItem(FROM_UTF8(plot.second));
      pItem->setData(Qt::UserRole, FROM_UTF8(plot.first));
      lstPlots->addItem(pItem);
      pItem->setSelected(true);
    }

  lstPlots->selectAll();
}

void CQSEDMLImportDialog::slotBrowseReportfile()
{
  txtReportFilename->setText(QFileDialog::getSaveFileName(this, "Choose a report filename", "", "TXT files (*.txt);;All files (*.*)"));
}
