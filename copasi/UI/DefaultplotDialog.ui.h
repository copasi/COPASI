/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DefaultplotDialog.ui.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 13:56:52 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include "qtUtilities.h"
#include "utilities/CCopasiTask.h"
#include "report/COutputAssistant.h"

void DefaultPlotDialog::slotCreate()
{
  if (!mpTask) return;
  if (COutputAssistant::createDefaultOutput(mIndex, mpTask))
    this->accept();
  else
    this->reject();
}

void DefaultPlotDialog::setTask(CCopasiTask * t)
{
  //set window header
  //this->resize(640, 480);
  this->setCaption("Output definition assistant");

  mpTask = t;
  if (!mpTask->getProblem()) return;
  //todo check
  mList = COutputAssistant::getListOfDefaultOutputDescriptions(mpTask->getProblem());
  listBox->clear();

  std::vector<C_INT32>::const_iterator it, itEnd = mList.end();
  for (it = mList.begin(); it != itEnd; ++it)
    {
      listBox->insertItem(FROM_UTF8(COutputAssistant::getItemName(*it)));
    }
  listBox->setSelected(0, true);
}

void DefaultPlotDialog::slotSelect()
{
  if (!mpTask) return;
  //std::cout << listBox->currentItem() << std::endl;

  C_INT32 i = listBox->currentItem();
  mIndex = mList[i];
  lineEditTitle->setText(FROM_UTF8(COutputAssistant::getItemName(mIndex)));
  textEdit->setText(FROM_UTF8(COutputAssistant::getItem(mIndex).description));
}

void DefaultPlotDialog::newSlot()
{}
