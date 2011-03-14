// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetScan.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/14 19:20:59 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CScanWidgetScan.h"

//#include <qvariant.h>
//#include "CScanWidgetScan.ui.h"

#include <qvalidator.h>

#include "UI/qtUtilities.h"
#include "UI/CCopasiSelectionDialog.h"
#include "report/CCopasiRootContainer.h"

#include "UI/icons/Copasi16-Alpha.xpm"

/*
 *  Constructs a CScanWidgetScan as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetScan::CScanWidgetScan(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  buttonObject->setIcon(QPixmap(Copasi16_Alpha_xpm));

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetScan::~CScanWidgetScan()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CScanWidgetScan::languageChange()
{
  retranslateUi(this);
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
          lineEditMin->setText(QString::number(value*0.5));
          lineEditMax->setText(QString::number(value*2));
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

#include "report/CCopasiObjectName.h"
bool CScanWidgetScan::initFromScanItem(CCopasiParameterGroup * pg, const CModel* model)
{
  if (!model) return false;

  mpModel = model;

  void* tmp;

  if (!(tmp = pg->getValue("Type").pVOID)) return false;

  CScanProblem::Type type = *(CScanProblem::Type*)tmp;

  if (type != CScanProblem::SCAN_LINEAR)
    return false;

  if (!(tmp = pg->getValue("Number of steps").pVOID)) return false;

  lineEditNumber->setText(QString::number(*(C_INT32*)tmp));

  if (!(tmp = pg->getValue("Object").pVOID)) return false;

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

  if (!(tmp = pg->getValue("Minimum").pVOID)) return false;

  lineEditMin->setText(QString::number(*(C_FLOAT64*)tmp));

  if (!(tmp = pg->getValue("Maximum").pVOID)) return false;

  lineEditMax->setText(QString::number(*(C_FLOAT64*)tmp));

  if (!(tmp = pg->getValue("log").pVOID)) return false;

  checkBoxLog->setChecked(*(bool*)tmp);

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
  tmp->setValue("log", checkBoxLog->isChecked());

  return true;
}
