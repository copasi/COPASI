/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanWidgetScan.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/22 23:23:59 $
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

#include <qvalidator.h>
#include <CCopasiSelectionDialog.h>
#include "qtUtilities.h"

void CScanWidgetScan::init()
{
  lineEditObject->setReadOnly(true);

  lineEditNumber->setValidator(new QIntValidator(lineEditNumber));
  lineEditMin->setValidator(new QDoubleValidator(lineEditMin));
  lineEditMax->setValidator(new QDoubleValidator(lineEditMax));

  mpObject = NULL;
}

void CScanWidgetScan::slotChooseObject()
{
  // open a selection dialog with single selection mode
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);
  browseDialog->setModel(mpModel);
  browseDialog->setSingleSelection(true);
  //browseDialog->enableExpertMode(false);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  if (mpObject)
    selection->push_back(mpObject);
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      mpObject = selection->at(0);
      if (mpObject)
        lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));
      else
        lineEditObject->setText("");
    }
  else
    {}}

#include "report/CCopasiObjectName.h"
bool CScanWidgetScan::initFromScanItem(CCopasiParameterGroup * pg, const CModel* model)
{
  if (!model) return false;
  mpModel = model;

  void* tmp;

  if (!(tmp = pg->getValue("Type"))) return false;
  CScanProblem::Type type = *(CScanProblem::Type*)tmp;
  if (type != CScanProblem::SCAN_LINEAR)
    return false;

  if (!(tmp = pg->getValue("Number of steps"))) return false;
  lineEditNumber->setText(QString::number(*(C_INT32*)tmp));

  if (!(tmp = pg->getValue("Object"))) return false;
  std::string tmpString = *(std::string*)tmp;
  if (tmpString == "")
    mpObject = NULL;
  else
    mpObject = CCopasiContainer::ObjectFromName(tmpString);

  if (mpObject)
    lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));
  else
    lineEditObject->setText("");

  if (!(tmp = pg->getValue("Minimum"))) return false;
  lineEditMin->setText(QString::number(*(C_FLOAT64*)tmp));

  if (!(tmp = pg->getValue("Maximum"))) return false;
  lineEditMax->setText(QString::number(*(C_FLOAT64*)tmp));

  return true;
}

bool CScanWidgetScan::saveToScanItem(CScanProblem * pg) const
  {
    CScanProblem::Type type = CScanProblem::SCAN_LINEAR;

    unsigned C_INT32 steps = lineEditNumber->text().toUInt();

    CCopasiParameterGroup* tmp = pg->createScanItem(type, steps, mpObject);
    assert(tmp);

    tmp->setValue("Minimum", lineEditMin->text().toDouble());
    tmp->setValue("Maximum", lineEditMax->text().toDouble());

    return true;
  }
