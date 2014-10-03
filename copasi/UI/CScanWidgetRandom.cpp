// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>

#include <QtGui/QValidator>

#include "copasi.h"

#include "CScanWidgetRandom.h"
#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"
#include "resourcesUI/CQIconResource.h"

#include "report/CCopasiRootContainer.h"
#include "report/CCopasiObjectName.h"

/*
 *  Constructs a CScanWidgetRandom as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetRandom::CScanWidgetRandom(QWidget* parent) :
  QWidget(parent),
  CScanItemData(CScanProblem::SCAN_RANDOM)
{
  setupUi(this);
  buttonObject->setIcon(CQIconResource::icon(CQIconResource::copasi));
  init();
  retranslateUi(this);
}

CScanWidgetRandom::CScanWidgetRandom(const CScanWidgetRandom & src, QWidget * parent) :
  QWidget(parent),
  CScanItemData(src)
{
  setupUi(this);
  buttonObject->setIcon(CQIconResource::icon(CQIconResource::copasi));
  init();
  load(mpData);
  retranslateUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetRandom::~CScanWidgetRandom()
{
  // no need to delete child widgets, Qt does it all for us
}

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
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::InitialTime |
        CQSimpleSelectionTree::Parameters,
        mpObject);

  if (mpObject != pObject) // Object selection changed.
    initFromObject(pObject);
}

void CScanWidgetRandom::initFromObject(const CCopasiObject *obj)
{
  mpObject = obj;

  if (obj)
    {
      lineEditObject->setText(FROM_UTF8(obj->getObjectDisplayName()));

      if (obj->isValueDbl())
        {
          C_FLOAT64 value = *(C_FLOAT64*)obj->getValuePointer();
          C_INT32 type = comboBoxType->currentIndex();

          if (type == 0) //uniform
            {
              lineEditMin->setText(QString::number(value * 0.5));
              lineEditMax->setText(QString::number(value * 2));
            }

          if (type == 1) //normal
            {
              lineEditMin->setText(QString::number(value));
              lineEditMax->setText(QString::number(value * 0.1));
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

// virtual
void CScanWidgetRandom::load(const CCopasiParameterGroup * pItem)
{
  if (pItem == NULL) return;

  *mpData = *pItem;

  unsigned C_INT32 * tmp;

  if (!(tmp = mpData->getValue("Type").pUINT))
    return;

  if (*(CScanProblem::Type *) tmp != CScanProblem::SCAN_RANDOM)
    return;

  std::string *pString;

  if (!(pString = mpData->getValue("Object").pSTRING))
    return;

  if (*pString == "")
    mpObject = NULL;
  else
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      mpObject = pDataModel->getDataObject(*pString);
    }

  if (mpObject)
    lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));
  else
    lineEditObject->setText("");

  if (!(tmp = mpData->getValue("Distribution type").pUINT))
    return;

  comboBoxType->setCurrentIndex(*tmp);
  changeType();

  lineEditMin->setText(getParameterValue(mpData, "Minimum"));
  lineEditMax->setText(getParameterValue(mpData, "Maximum"));

  bool * pBool;

  if (!(pBool = mpData->getValue("log").pBOOL))
    return;

  checkBoxLog->setChecked(* pBool);

  return;
}

// virtual
bool CScanWidgetRandom::save(CCopasiParameterGroup * pItem) const
{
  mpData->setValue("Distribution type", (unsigned C_INT32) comboBoxType->currentIndex());
  mpData->setValue("Minimum", lineEditMin->text().toDouble());
  mpData->setValue("Maximum", lineEditMax->text().toDouble());
  mpData->setValue("log", checkBoxLog->isChecked());

  if (mpObject != NULL)
    {
      mpData->setValue("Object", mpObject->getCN());
    }
  else
    {
      mpData->setValue("Object", std::string(""));
    }

  if (pItem != NULL)
    {
      if (*mpData == *pItem) return false;

      *pItem = *mpData;
      return true;
    }

  return false;
}

void CScanWidgetRandom::changeType()
{
  C_INT32 type = comboBoxType->currentIndex();
  C_FLOAT64 value = 0.0;

  if (mpObject != NULL)
    value = *(C_FLOAT64*)mpObject->getValuePointer();

  switch (type)
    {
      case 0: // uniform
        lineEditMin->setEnabled(true);
        lineEditMax->setEnabled(true);

        labelMin->setText("min");
        labelMax->setText("max");

        if (mpObject != NULL)
          {
            lineEditMin->setText(QString::number(value * 0.5));
            lineEditMax->setText(QString::number(value * 2));
          }
        else
          {
            lineEditMin->setText("");
            lineEditMax->setText("");
          }

        break;

      case 1: // normal
        lineEditMin->setEnabled(true);
        lineEditMax->setEnabled(true);

        labelMin->setText("mean");
        labelMax->setText("standard deviation");

        if (mpObject != NULL)
          {
            lineEditMin->setText(QString::number(value));
            lineEditMax->setText(QString::number(value * 0.1));
          }
        else
          {
            lineEditMin->setText("");
            lineEditMax->setText("");
          }

        break;

      case 2: // Poisson
        lineEditMin->setEnabled(true);
        lineEditMax->setEnabled(false);

        labelMin->setText("mean");
        labelMax->setText("");

        if (mpObject != NULL)
          lineEditMin->setText(QString::number(value));
        else
          lineEditMin->setText("");

        lineEditMax->setText("");

        break;

      case 3: // Gamma
        lineEditMin->setEnabled(true);
        lineEditMax->setEnabled(true);

        labelMin->setText("shape");
        labelMax->setText("scale");

        if (mpObject != NULL)
          {
            lineEditMin->setText(QString::number(1.0 * value));
            lineEditMax->setText(QString::number(0.1));
          }
        else
          {
            lineEditMin->setText("");
            lineEditMax->setText("");
          }

        break;
    }
}
