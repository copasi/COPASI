/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CScanWidgetRandom.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/27 20:27:39 $
   End CVS Header */

//comboBoxType linear| normal

#include <qvalidator.h>
#include <CCopasiSelectionDialog.h>
#include "qtUtilities.h"

void CScanWidgetRandom::init()
{
  lineEditObject->setReadOnly(true);

  lineEditMin->setValidator(new QDoubleValidator(lineEditMin));
  lineEditMax->setValidator(new QDoubleValidator(lineEditMax));

  mpObject = NULL;
}

void CScanWidgetRandom::slotChooseObject()
{
  CCopasiObject* tmpObject = mpObject;
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
        {
          lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));

          if (mpObject != tmpObject)
            {
              //TODO: init min and max
              if (mpObject->isValueDbl())
                {
                  C_FLOAT64 value = *(C_FLOAT64*)mpObject->getReference();
                  lineEditMin->setText(QString::number(value*0.5));
                  lineEditMax->setText(QString::number(value*2));
                }
            }
        }
      else
        lineEditObject->setText("");
    }
  else
    {}}

#include "report/CCopasiObjectName.h"
bool CScanWidgetRandom::initFromScanItem(CCopasiParameterGroup * pg, const CModel* model)
{
  if (!model) return false;
  mpModel = model;

  void* tmp;

  if (!(tmp = pg->getValue("Type"))) return false;
  CScanProblem::Type type = *(CScanProblem::Type*)tmp;
  if (type != CScanProblem::SCAN_RANDOM)
    return false;

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

  if (!(tmp = pg->getValue("Distribution type"))) return false;
  comboBoxType->setCurrentItem(*(unsigned C_INT32*)tmp);

  if (!(tmp = pg->getValue("Minimum"))) return false;
  lineEditMin->setText(QString::number(*(C_FLOAT64*)tmp));

  if (!(tmp = pg->getValue("Maximum"))) return false;
  lineEditMax->setText(QString::number(*(C_FLOAT64*)tmp));

  if (!(tmp = pg->getValue("log"))) return false;
  checkBoxLog->setChecked(*(bool*)tmp);

  return true;
}

bool CScanWidgetRandom::saveToScanItem(CScanProblem * pg) const
  {
    CScanProblem::Type type = CScanProblem::SCAN_RANDOM;

    unsigned C_INT32 steps = 1;

    CCopasiParameterGroup* tmp = pg->createScanItem(type, steps, mpObject);
    assert(tmp);

    tmp->setValue("Distribution type", (unsigned C_INT32)comboBoxType->currentItem());
    tmp->setValue("Minimum", lineEditMin->text().toDouble());
    tmp->setValue("Maximum", lineEditMax->text().toDouble());
    tmp->setValue("log", checkBoxLog->isChecked());

    return true;
  }
