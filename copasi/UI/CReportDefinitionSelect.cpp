/****************************************************************************
 ** Form implementation generated from reading ui file '.\CReportDefinitionSelect.ui'
 **
 ** Created: Fri Aug 15 09:16:02 2003
 **      by: The User Interface Compiler ($Id: CReportDefinitionSelect.cpp,v 1.19 2003/09/18 02:51:54 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CReportDefinitionSelect.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "utilities/CCopasiException.h"
#include "listviews.h"
#include "DataModel.h"
#include "report/CReportDefinitionVector.h"
#include "report/CReport.h"

/*
 *  Constructs a CReportDefinitionSelect as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */

CReportDefinitionSelect::CReportDefinitionSelect(QWidget* parent, const char* name, WFlags fl)
    : QDialog(parent, name, fl),
    pListView((ListViews*)parent),
    mpReport(NULL)
{
  if (!name)
    setName("CReportDefinitionSelect");
  CReportDefinitionSelectLayout = new QGridLayout(this, 1, 1, 11, 6, "CReportDefinitionSelectLayout");

  frame5 = new QFrame(this, "frame5");
  frame5->setFrameShape(QFrame::Box);
  frame5->setFrameShadow(QFrame::Sunken);
  frame5Layout = new QGridLayout(frame5, 1, 1, 11, 6, "frame5Layout");

  reportLabel = new QLabel(frame5, "reportLabel");

  frame5Layout->addWidget(reportLabel, 0, 0);

  targetLabel = new QLabel(frame5, "targetLabel");

  frame5Layout->addWidget(targetLabel, 1, 0);

  appendChecked = new QCheckBox(frame5, "appendChecked");

  frame5Layout->addMultiCellWidget(appendChecked, 2, 2, 1, 2);

  reportDefinitionNameList = new QComboBox(FALSE, frame5, "reportDefinitionNameList");

  frame5Layout->addWidget(reportDefinitionNameList, 0, 1);

  jumpButton = new QPushButton(frame5, "jumpButton");

  frame5Layout->addWidget(jumpButton, 0, 2);

  targetEdit = new QLineEdit(frame5, "targetEdit");
  targetEdit->setFrameShape(QLineEdit::LineEditPanel);
  targetEdit->setFrameShadow(QLineEdit::Sunken);

  frame5Layout->addWidget(targetEdit, 1, 1);

  browseButton = new QPushButton(frame5, "browseButton");

  frame5Layout->addWidget(browseButton, 1, 2);

  CReportDefinitionSelectLayout->addMultiCellWidget(frame5, 0, 0, 0, 1);

  confirmButton = new QPushButton(this, "confirmButton");

  CReportDefinitionSelectLayout->addWidget(confirmButton, 1, 0);

  cancelButton = new QPushButton(this, "cancelButton");

  CReportDefinitionSelectLayout->addWidget(cancelButton, 1, 1);
  languageChange();
  clearWState(WState_Polished);

  // tab order
  setTabOrder(reportDefinitionNameList, jumpButton);
  setTabOrder(jumpButton, targetEdit);
  setTabOrder(targetEdit, browseButton);
  setTabOrder(browseButton, appendChecked);
  setTabOrder(appendChecked, confirmButton);
  setTabOrder(confirmButton, cancelButton);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
  connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirmClicked()));
  connect(jumpButton, SIGNAL(clicked()), this, SLOT(jumpToEdit()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CReportDefinitionSelect::~CReportDefinitionSelect()
{
  cleanup();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CReportDefinitionSelect::languageChange()
{
  setCaption(tr("CReportDefinitionSelect"));
  reportLabel->setText(tr("ReportDefinitions"));
  targetLabel->setText(tr("Target"));
  appendChecked->setText(tr("Append"));
  jumpButton->setText(tr("edit"));
  browseButton->setText(tr("browse"));
  confirmButton->setText(tr("Confirm"));
  cancelButton->setText(tr("Cancel"));
}

void CReportDefinitionSelect::loadReportDefinitionVector()
{
  DataModel* dataModel = ListViews::getDataModel();
  CReportDefinitionVector* pReportDefinitionVector = dataModel->getReportDefinitionVectorAddr();
  C_INT32 i;
  for (i = 0; i < pReportDefinitionVector->size(); i++)
    reportDefinitionNameList->insertItem((*(pReportDefinitionVector))[i]->getName().c_str());

  // if it is an empty list
  if (reportDefinitionNameList->count() == 0)
    {
      try
        {
          std::string name = "ReportDefinition_0";
          dataModel->getReportDefinitionVectorAddr()->addReportDefinition(name, "");
          reportDefinitionNameList->insertItem (name.c_str());
          reportDefinitionNameList->setCurrentItem(1);
          mpReport->setReportDefinition((*dataModel->getReportDefinitionVectorAddr())[0]); //first one report definition
          mpReport->setAppend(appendChecked->isChecked());
          mpReport->setTarget(targetEdit->text().latin1());
          ListViews::notify(ListViews::REPORT, ListViews::CHANGE, ""); //notify Table Definition to
          if (QMessageBox::information (NULL, "No Report Definition Defined",
                                        "No report definition defined, Copasi has already created a new one for you.\n Do you want to switch to the GUI to edit it?",
                                        QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
            jumpToEdit();
        }
      catch (CCopasiException Exception)
      {}
      return;
    }

  if (!mpReport->getReportDefinition())
    {
      C_INT32 row;
      row = reportDefinitionNameList->currentItem();
      mpReport->setReportDefinition((*(pReportDefinitionVector))[row]);
      mpReport->setAppend(appendChecked->isChecked());
      mpReport->setTarget(targetEdit->text().latin1());
      jumpToEdit();
      return;
    }
  else
    {
      C_INT32 i;
      // no use to compare the last one
      for (i = reportDefinitionNameList->count() - 1; i >= 1; i--)
        if (reportDefinitionNameList->text(i) == mpReport->getReportDefinition()->getName().c_str())
          break;
      reportDefinitionNameList->setCurrentItem(i);
      appendChecked->setChecked(mpReport->append());
      targetEdit->setText(mpReport->getTarget().c_str());
    }
}

void CReportDefinitionSelect::cancelClicked()
{
  cleanup();
  delete this;
}

void CReportDefinitionSelect::confirmClicked()
{
  if (!mpReport)
    //exception made here
    return;
  DataModel* dataModel = ListViews::getDataModel();
  CReportDefinitionVector* pReportDefinitionVector = dataModel->getReportDefinitionVectorAddr();
  C_INT32 row;
  row = reportDefinitionNameList->currentItem();
  mpReport->setReportDefinition((*(pReportDefinitionVector))[row]);
  mpReport->setAppend(appendChecked->isChecked());
  mpReport->setTarget(targetEdit->text().latin1());
  cleanup();
  delete this;
}

void CReportDefinitionSelect::cleanup()
{
  mpReport = NULL;
}

void CReportDefinitionSelect::jumpToEdit()
{
  DataModel* dataModel = ListViews::getDataModel();
  CReportDefinitionVector* pReportDefinitionVector = dataModel->getReportDefinitionVectorAddr();
  C_INT32 row;
  row = reportDefinitionNameList->currentItem();
  pListView->switchToOtherWidget((*(pReportDefinitionVector))[row]->getKey());
  confirmClicked();
}

void CReportDefinitionSelect::setReport(CReport* newReport)
{
  mpReport = newReport;
}
