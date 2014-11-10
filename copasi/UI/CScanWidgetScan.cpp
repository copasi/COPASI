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

#include "copasi.h"

#include "CScanWidgetScan.h"

#include <QtGui/QValidator>

#include "UI/qtUtilities.h"
#include "UI/CCopasiSelectionDialog.h"
#include "resourcesUI/CQIconResource.h"

#include "report/CCopasiRootContainer.h"
#include "report/CCopasiObjectName.h"

/*
 *  Constructs a CScanWidgetScan as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetScan::CScanWidgetScan(QWidget* parent) :
  QWidget(parent),
  CScanItemData(CScanProblem::SCAN_LINEAR)
{
  setupUi(this);

  buttonObject->setIcon(CQIconResource::icon(CQIconResource::copasi));

  init();
}

CScanWidgetScan::CScanWidgetScan(const CScanWidgetScan & src, QWidget * parent) :
  QWidget(parent),
  CScanItemData(src)
{
  setupUi(this);

  buttonObject->setIcon(CQIconResource::icon(CQIconResource::copasi));

  init();
  load(mpData);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetScan::~CScanWidgetScan()
{
  // no need to delete child widgets, Qt does it all for us
}

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
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::InitialTime |
        CQSimpleSelectionTree::Parameters,
        mpObject);

  if (mpObject != pObject) // Object selection changed.
    initFromObject(pObject);
}

void CScanWidgetScan::initFromObject(const CCopasiObject *obj)
{
  mpObject = obj;

  if (obj)
    {
      lineEditObject->setText(FROM_UTF8(obj->getObjectDisplayName()));

      if (obj->isValueDbl())
        {
          C_FLOAT64 value = *(C_FLOAT64*)obj->getValuePointer();
          lineEditNumber->setText("10");
          lineEditMin->setText(QString::number(value * 0.5));
          lineEditMax->setText(QString::number(value * 2));
        }
    }
  else
    {
      lineEditObject->setText("");
      lineEditNumber->setText("");
      lineEditMin->setText("");
      lineEditMax->setText("");
    }
}

// virtual
void CScanWidgetScan::load(const CCopasiParameterGroup * pItem)
{
  if (pItem == NULL) return;

  *mpData = *pItem;

  void * tmp;

  if (!(tmp = mpData->getValue("Type").pVOID)) return;

  CScanProblem::Type type = *(CScanProblem::Type*)tmp;

  if (type != CScanProblem::SCAN_LINEAR)
    return;

  if (!(tmp = mpData->getValue("Number of steps").pVOID)) return;

  lineEditNumber->setText(QString::number(*(C_INT32*)tmp));

  if (!(tmp = mpData->getValue("Object").pVOID)) return;

  std::string tmpString = *(std::string*)tmp;

  if (tmpString == "")
    mpObject = NULL;
  else
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      mpObject = pDataModel->getDataObject(tmpString);
    }

  if (mpObject)
    lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));
  else
    lineEditObject->setText("");

  if (!(tmp = mpData->getValue("Minimum").pVOID)) return;

  lineEditMin->setText(QString::number(*(C_FLOAT64*)tmp));

  if (!(tmp = mpData->getValue("Maximum").pVOID)) return;

  lineEditMax->setText(QString::number(*(C_FLOAT64*)tmp));

  if (!(tmp = mpData->getValue("log").pVOID)) return;

  checkBoxLog->setChecked(*(bool*)tmp);

  return;
}

// virtual
bool CScanWidgetScan::save(CCopasiParameterGroup * pItem) const
{
  mpData->setValue("Number of steps", lineEditNumber->text().toUInt());
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
