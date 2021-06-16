// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QValidator>

#include "copasi/copasi.h"

#include "copasi/UI/CScanWidgetScan.h"

#include "copasi/UI/listviews.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/UI/CCopasiSelectionDialog.h"

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

void CScanWidgetScan::slotIntervalsChecked()
{
  radIntervals->setChecked(!radIntervals->isChecked());
  mpWidgetIntervals->setVisible(radIntervals->isChecked());
  mpWidgetValues->setVisible(!radIntervals->isChecked());
}

void CScanWidgetScan::slotValuesChecked()
{
  radValues->setChecked(!radValues->isChecked());
  mpWidgetIntervals->setVisible(!radValues->isChecked());
  mpWidgetValues->setVisible(radValues->isChecked());
}

void CScanWidgetScan::init()
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  QColor Foreground = Palette.color(QPalette::Active, QPalette::Text);
  QColor Background = Palette.color(QPalette::Active, QPalette::Base);
  QColor Target(210, 255, 210, 255);

  if (Foreground.redF() + Foreground.greenF() + Foreground.blueF() > Background.redF() + Background.greenF() + Background.blueF())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      setStyleSheet("color: " + Target.name(QColor::HexRgb));
#else
      setStyleSheet("color: " + Target.name());
#endif
    }
  else
    {
      QPalette palette;
      QBrush brush(Target);
      brush.setStyle(Qt::SolidPattern);
      palette.setBrush(QPalette::Active, QPalette::Base, brush);
      palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
      QBrush brush1(QColor(212, 208, 200, 255));
      brush1.setStyle(Qt::SolidPattern);
      palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
      frame->setPalette(palette);
    }

  lineEditObject->setReadOnly(true);

  lineEditNumber->setValidator(new QIntValidator(lineEditNumber));
  lineEditMin->setValidator(new QDoubleValidator(lineEditMin));
  lineEditMax->setValidator(new QDoubleValidator(lineEditMax));

  mpWidgetIntervals->setVisible(radIntervals->isChecked());
  mpWidgetValues->setVisible(!radIntervals->isChecked());

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
          txtValues->setText("");
        }
    }
  else
    {
      lineEditObject->setText("");
      lineEditNumber->setText("");
      lineEditMin->setText("");
      lineEditMax->setText("");
      txtValues->setText("");
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

  std::string values;
  bool useValues = false;

  if (mpData->getParameter("Values") != NULL)
    {
      values = mpData->getValue< std::string >("Values");
    }

  if (mpData->getParameter("Use Values") != NULL)
    {
      useValues = mpData->getValue< bool >("Use Values");
    }

  txtValues->setText(FROM_UTF8(values));

  if (useValues)
    slotValuesChecked();
  else
    slotIntervalsChecked();

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

  if (!mpData->getParameter("Values"))
    mpData->addParameter("Values", CCopasiParameter::Type::STRING, std::string(""));

  if (!mpData->getParameter("Use Values"))
    mpData->addParameter("Use Values", CCopasiParameter::Type::BOOL, false);

  std::string stringValues = TO_UTF8(txtValues->text());
  mpData->setValue("Values", stringValues);
  mpData->setValue("Use Values", radValues->isChecked());

  if (pItem != NULL)
    {
      if (*mpData == *pItem) return false;

      *pItem = *mpData;
      return true;
    }

  return false;
}
