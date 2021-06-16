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

#include <iostream>

#include <QValidator>

#include "copasi/copasi.h"

#include "listviews.h"
#include "CScanWidgetRandom.h"
#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/CopasiDataModel/CDataModel.h"

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
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  QColor Foreground = Palette.color(QPalette::Active, QPalette::Text);
  QColor Background = Palette.color(QPalette::Active, QPalette::Base);
  QColor Target(210, 210, 255, 255);

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

  lineEditMin->setValidator(new QDoubleValidator(lineEditMin));
  lineEditMax->setValidator(new QDoubleValidator(lineEditMax));

  mpObject = NULL;
}

void CScanWidgetRandom::slotChooseObject()
{
  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::InitialTime |
        CQSimpleSelectionTree::Parameters,
        mpObject);

  if (mpObject != pObject) // Object selection changed.
    initFromObject(pObject);
}

void CScanWidgetRandom::initFromObject(const CDataObject *obj)
{
  mpObject = obj;

  if (obj)
    {
      lineEditObject->setText(FROM_UTF8(obj->getObjectDisplayName()));

      if (obj->hasFlag(CDataObject::ValueDbl))
        {
          C_FLOAT64 value = *(C_FLOAT64*)obj->getValuePointer();
          C_INT32 type = comboBoxType->currentIndex();

          if (type == 0) //uniform
            {
              lineEditMin->setText(convertToQString(value * 0.5));
              lineEditMax->setText(convertToQString(value * 2));
            }

          if (type == 1) //normal
            {
              lineEditMin->setText(convertToQString(value));
              lineEditMax->setText(convertToQString(value * 0.1));
            }

          if (type == 2) //poisson
            {
              lineEditMin->setText(convertToQString(value));
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

  if (mpData->getValue< unsigned C_INT32 >("Type") != CScanProblem::SCAN_RANDOM)
    return;

  const std::string String = mpData->getValue< std::string >("Object");

  if (String == "")
    mpObject = NULL;
  else
    {
      CDataModel* pDataModel = ListViews::dataModel(this);
      assert(pDataModel != NULL);
      mpObject = CObjectInterface::DataObject(pDataModel->getObjectFromCN(String));
    }

  if (mpObject)
    lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));
  else
    lineEditObject->setText("");

  comboBoxType->setCurrentIndex(mpData->getValue< unsigned C_INT32 >("Distribution type"));
  changeType();

  lineEditMin->setText(getParameterValue(mpData, "Minimum").toString());
  lineEditMax->setText(getParameterValue(mpData, "Maximum").toString());

  checkBoxLog->setChecked(mpData->getValue< bool >("log"));

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
            lineEditMin->setText(convertToQString(value * 0.5));
            lineEditMax->setText(convertToQString(value * 2));
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
            lineEditMin->setText(convertToQString(value));
            lineEditMax->setText(convertToQString(value * 0.1));
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
          lineEditMin->setText(convertToQString(value));
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
            lineEditMin->setText(convertToQString(1.0 * value));
            lineEditMax->setText(convertToQString(0.1));
          }
        else
          {
            lineEditMin->setText("");
            lineEditMax->setText("");
          }

        break;
    }
}
