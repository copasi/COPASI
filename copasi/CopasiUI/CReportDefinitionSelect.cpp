/****************************************************************************
 ** Form implementation generated from reading ui file '.\CReportDefinitionSelect.ui'
 **
 ** Created: Fri Aug 15 09:16:02 2003
 **      by: The User Interface Compiler ($Id: CReportDefinitionSelect.cpp,v 1.12 2003/08/19 20:47:12 lixu1 Exp $)
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

  confirmButton = new QPushButton(this, "confirmButton");

  CReportDefinitionSelectLayout->addWidget(confirmButton, 1, 0);

  cancelButton = new QPushButton(this, "cancelButton");

  CReportDefinitionSelectLayout->addWidget(cancelButton, 1, 1);

  frame5 = new QFrame(this, "frame5");
  frame5->setFrameShape(QFrame::Box);
  frame5->setFrameShadow(QFrame::Sunken);
  frame5Layout = new QGridLayout(frame5, 1, 1, 11, 6, "frame5Layout");

  reportLabel = new QLabel(frame5, "reportLabel");

  frame5Layout->addWidget(reportLabel, 0, 0);

  reportDefinitionNameList = new QComboBox(FALSE, frame5, "reportDefinitionNameList");

  frame5Layout->addWidget(reportDefinitionNameList, 0, 1);

  targetEdit = new QLineEdit(frame5, "targetEdit");
  targetEdit->setFrameShape(QLineEdit::LineEditPanel);
  targetEdit->setFrameShadow(QLineEdit::Sunken);

  frame5Layout->addWidget(targetEdit, 2, 1);

  targetLabel = new QLabel(frame5, "targetLabel");

  frame5Layout->addWidget(targetLabel, 2, 0);

  appendChecked = new QCheckBox(frame5, "appendChecked");

  frame5Layout->addWidget(appendChecked, 3, 1);

  jumpButton = new QPushButton(frame5, "jumpButton");

  frame5Layout->addWidget(jumpButton, 1, 1);

  CReportDefinitionSelectLayout->addMultiCellWidget(frame5, 0, 0, 0, 1);
  languageChange();
  clearWState(WState_Polished);

  // tab order
  setTabOrder(reportDefinitionNameList, jumpButton);
  setTabOrder(jumpButton, targetEdit);
  setTabOrder(targetEdit, appendChecked);
  setTabOrder(appendChecked, confirmButton);
  setTabOrder(confirmButton, cancelButton);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
  connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirmClicked()));
  connect(jumpButton, SIGNAL(clicked()), this, SLOT(jumpToEdit()));

  loadReportDefinitionVector();
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
  confirmButton->setText(tr("Confirm"));
  cancelButton->setText(tr("Cancel"));
  reportLabel->setText(tr("ReportDefinitions"));
  targetLabel->setText(tr("Target"));
  appendChecked->setText(tr("Append"));
  jumpButton->setText(tr("Go editing..."));
}

void CReportDefinitionSelect::loadReportDefinitionVector()
{
  DataModel* dataModel = ListViews::getDataModel();
  CReportDefinitionVector* pReportDefinitionVector = dataModel->getReportDefinitionVectorAddr();
  C_INT32 i;
  for (i = 0; i < pReportDefinitionVector->getReportDefinitionsAddr()->size(); i++)
    reportDefinitionNameList->insertItem((*(pReportDefinitionVector->getReportDefinitionsAddr()))[i]->getName().c_str());
}

void CReportDefinitionSelect::cancelClicked()
{
  cleanup();
  close();
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
  mpReport->setReportDefinintion((*(pReportDefinitionVector->getReportDefinitionsAddr()))[row]);
  mpReport->setAppend(appendChecked->isChecked());
  mpReport->setTarget(targetEdit->text().latin1());
  cleanup();
  close();
}

void CReportDefinitionSelect::cleanup()
{}

void CReportDefinitionSelect::jumpToEdit()
{
  DataModel* dataModel = ListViews::getDataModel();
  CReportDefinitionVector* pReportDefinitionVector = dataModel->getReportDefinitionVectorAddr();
  C_INT32 row;
  row = reportDefinitionNameList->currentItem();
  pListView->switchToOtherWidget((*(pReportDefinitionVector->getReportDefinitionsAddr()))[row]->getKey());
  confirmClicked();
}

void CReportDefinitionSelect::setReport(CReport* newReport)
{
  mpReport = newReport;
}
