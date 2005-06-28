/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CScanWidgetRandom.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/28 20:32:36 $
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

  unsigned C_INT32 * tmp;

  if (!(tmp = pg->getValue("Type").pUINT)) return false;
  if (* (CScanProblem::Type *) tmp != CScanProblem::SCAN_RANDOM)
    return false;

  std::string *pString;
  if (!(pString = pg->getValue("Object").pSTRING)) return false;
  if (*pString == "")
    mpObject = NULL;
  else
    mpObject = CCopasiContainer::ObjectFromName(*pString);

  if (mpObject)
    lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));
  else
    lineEditObject->setText("");

  if (!(tmp = pg->getValue("Distribution type").pUINT)) return false;
  comboBoxType->setCurrentItem(*tmp);

  lineEditMin->setText(getParameterValue(pg, "Minimum"));

  lineEditMax->setText(getParameterValue(pg, "Maximum"));

  bool * pBool;
  if (!(pBool = pg->getValue("log").pBOOL)) return false;
  checkBoxLog->setChecked(* pBool);

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

void CScanWidgetRandom::changeType()
{
  C_INT32 type = comboBoxType->currentItem();

  if (type == 0) //uniform
    {
      lineEditMin->setEnabled(true);
      lineEditMax->setEnabled(true);

      labelMin->setText("min");
      labelMax->setText("max");
    }

  if (type == 1) //normal
    {
      lineEditMin->setEnabled(true);
      lineEditMax->setEnabled(true);

      labelMin->setText("mean");
      labelMax->setText("standard deviation");
    }

  if (type == 2) //poisson
    {
      lineEditMin->setEnabled(true);
      lineEditMax->setEnabled(false);

      labelMin->setText("mean");
      labelMax->setText("");
    }

  //TODO: handle log: rename standard deviation -> sd factor,
  //                  disable poisson?
}
