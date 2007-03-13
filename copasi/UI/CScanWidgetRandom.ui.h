// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CScanWidgetRandom.ui.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/13 19:56:56 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//comboBoxType linear| normal

#include <qvalidator.h>

#include "copasi.h"

#include "UI/qtUtilities.h"
#include "UI/CCopasiSelectionDialog.h"

#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

void CScanWidgetRandom::init()
{
  lineEditObject->setReadOnly(true);

  lineEditMin->setValidator(new QDoubleValidator(lineEditMin));
  lineEditMax->setValidator(new QDoubleValidator(lineEditMax));

  mpObject = NULL;
}

void CScanWidgetRandom::slotChooseObject()
{
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::INITIAL_VALUE,
                                            mpObject);

  if (mpObject != pObject) // Object selection changed.
    {
      mpObject = pObject;

      if (mpObject)
        {
          lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));

          if (mpObject->isValueDbl())
            {
              C_FLOAT64 value = *(C_FLOAT64*)mpObject->getValuePointer();
              C_INT32 type = comboBoxType->currentItem();

              if (type == 0) //uniform
                {
                  lineEditMin->setText(QString::number(value*0.5));
                  lineEditMax->setText(QString::number(value*2));
                }

              if (type == 1) //normal
                {
                  lineEditMin->setText(QString::number(value));
                  lineEditMax->setText(QString::number(value*0.1));
                }

              if (type == 2) //poisson
                {
                  lineEditMin->setText(QString::number(value));
                  lineEditMax->setText("");
                }
            }
        }
      else
        {
          lineEditObject->setText("");
          lineEditMin->setText("");
          lineEditMax->setText("");
        }
    }
}

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
  changeType();

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
  C_FLOAT64 value;

  if (mpObject != NULL)
    value = *(C_FLOAT64*)mpObject->getValuePointer();

  if (type == 0) //uniform
    {
      lineEditMin->setEnabled(true);
      lineEditMax->setEnabled(true);

      labelMin->setText("min");
      labelMax->setText("max");

      if (mpObject != NULL)
        {
          lineEditMin->setText(QString::number(value*0.5));
          lineEditMax->setText(QString::number(value*2));
        }
      else
        {
          lineEditMin->setText("");
          lineEditMax->setText("");
        }
    }

  if (type == 1) //normal
    {
      lineEditMin->setEnabled(true);
      lineEditMax->setEnabled(true);

      labelMin->setText("mean");
      labelMax->setText("standard deviation");

      if (mpObject != NULL)
        {
          lineEditMin->setText(QString::number(value));
          lineEditMax->setText(QString::number(value*0.1));
        }
      else
        {
          lineEditMin->setText("");
          lineEditMax->setText("");
        }
    }

  if (type == 2) //poisson
    {
      lineEditMin->setEnabled(true);
      lineEditMax->setEnabled(false);

      labelMin->setText("mean");
      labelMax->setText("");

      if (mpObject != NULL)
        lineEditMin->setText(QString::number(value));
      else
        lineEditMin->setText("");

      lineEditMax->setText("");
    }

  //TODO: handle log: rename standard deviation -> sd factor,
  //                  disable poisson?
}
