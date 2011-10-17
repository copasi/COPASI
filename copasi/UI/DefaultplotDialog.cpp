// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DefaultplotDialog.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/17 19:56:22 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "DefaultplotDialog.h"

#include "qtUtilities.h"

#include "utilities/CCopasiTask.h"
#include "report/COutputAssistant.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a DefaultPlotDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DefaultPlotDialog::DefaultPlotDialog(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
DefaultPlotDialog::~DefaultPlotDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

void DefaultPlotDialog::slotCreate()
{
  if (!mpTask) return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (COutputAssistant::createDefaultOutput(mIndex, mpTask, pDataModel))
    this->accept();
  else
    this->reject();
}

void DefaultPlotDialog::setTask(CCopasiTask * t)
{
  //set window header
  //this->resize(640, 480);
  this->setWindowTitle("Output definition assistant");

  mpTask = t;

  if (!mpTask->getProblem()) return;

  //todo check
  mList = COutputAssistant::getListOfDefaultOutputDescriptions(mpTask->getProblem());
  listBox->clear();

  std::vector<C_INT32>::const_iterator it, itEnd = mList.end();

  QStringList Items;

  for (it = mList.begin(); it != itEnd; ++it)
    {
      QString Name = FROM_UTF8(COutputAssistant::getItemName(*it));

      if (!Name.startsWith("--")) Name = "   " + Name;

      Items.append(Name);
    }

  listBox->insertItems(0, Items);

  listBox->item(0)->setSelected(true);
}

void DefaultPlotDialog::slotSelect()
{
  if (!mpTask) return;

  int i = listBox->currentRow();

  mIndex = mList[i];
  lineEditTitle->setText(FROM_UTF8(COutputAssistant::getItemName(mIndex)));
  textEdit->setText(FROM_UTF8(COutputAssistant::getItem(mIndex).description));

  createButton->setEnabled(!lineEditTitle->text().startsWith("-- "));
}

void DefaultPlotDialog::newSlot()
{}
