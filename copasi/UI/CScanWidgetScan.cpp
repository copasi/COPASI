// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "CScanWidgetScan.h"

#include <QValidator>

#include "listviews.h"
#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/CopasiDataModel/CDataModel.h"

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
  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::InitialTime |
        CQSimpleSelectionTree::Parameters,
        mpObject);

  if (mpObject != pObject) // Object selection changed.
    initFromObject(pObject);
}

void CScanWidgetScan::initFromObject(const CDataObject *obj)
{
  mpObject = obj;

  if (obj)
    {
      lineEditObject->setText(FROM_UTF8(obj->getObjectDisplayName()));

      if (obj->hasFlag(CDataObject::ValueDbl))
        {
          C_FLOAT64 value = *(C_FLOAT64*)obj->getValuePointer();
          lineEditNumber->setText("10");
          lineEditMin->setText(convertToQString(value * 0.5));
          lineEditMax->setText(convertToQString(value * 2));
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

  CScanProblem::Type type = mpData->getValue< CScanProblem::Type >("Type");

  if (type != CScanProblem::SCAN_LINEAR)
    return;

  lineEditNumber->setText(QString::number(mpData->getValue< C_INT32 >("Number of steps")));
  std::string tmpString = mpData->getValue< std::string >("Object");

  if (tmpString == "")
    mpObject = NULL;
  else
    {
      CDataModel* pDataModel = ListViews::dataModel(this);
      assert(pDataModel != NULL);
      mpObject = CObjectInterface::DataObject(pDataModel->getObjectFromCN(tmpString));
    }

  if (mpObject)
    lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));
  else
    lineEditObject->setText("");

  lineEditMin->setText(convertToQString(mpData->getValue< C_FLOAT64 >("Minimum")));
  lineEditMax->setText(convertToQString(mpData->getValue< C_FLOAT64 >("Maximum")));

  checkBoxLog->setChecked(mpData->getValue< bool >("log"));

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
