// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

#include "CQScanWidgetParameterSet.h"

#include <QValidator>

#include "copasi/copasi.h"

#include "copasi/core/CDataVector.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelParameterSet.h"
#include "copasi/scan/CScanProblem.h"

#include "copasi/UI/listviews.h"
#include "copasi/UI/DataModelGUI.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/UI/CCopasiSelectionDialog.h"
#include "copasi/UI/CQMultipleSelectionDialog.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/CopasiDataModel/CDataModel.h"

CQScanWidgetParameterSet::CQScanWidgetParameterSet(QWidget * parent)
  : QWidget(parent)
  , CScanItemData(CScanProblem::Type::SCAN_PARAMETER_SET)
{
  setupUi(this);

  cmdSelectSet->setIcon(CQIconResource::icon(CQIconResource::copasi));

  init();
}

CQScanWidgetParameterSet::CQScanWidgetParameterSet(const CQScanWidgetParameterSet & src, QWidget * parent)
  : QWidget(parent)
  , CScanItemData(src)
{
  setupUi(this);

  cmdSelectSet->setIcon(CQIconResource::icon(CQIconResource::copasi));

  init();
  load(mpData);
}

CQScanWidgetParameterSet::~CQScanWidgetParameterSet()
{
}

void CQScanWidgetParameterSet::load(const CCopasiParameterGroup * pItem)
{
  if (pItem == NULL)
    return;

  *mpData = *pItem;

  CScanProblem::Type type = mpData->getValue< CScanProblem::Type >("Type");

  if (type != CScanProblem::SCAN_PARAMETER_SET)
    return;

  auto * group = mpData->getGroup("ParameterSet CNs");
  if (!group)
    return;

  std::map< QString, const CModelParameterSet * > selection;
  for (size_t i = 0; i < group->size(); ++i)
    {
      auto * p = group->getParameter(i);
      std::string cn = p->getValue< std::string >();
      auto * pSet = dynamic_cast< const CModelParameterSet * >(ListViews::dataModel(this)->getObjectFromCN(cn));
      if (!pSet)
        continue;

      selection[FROM_UTF8(pSet->getObjectName())] = pSet;
    }
  initFromSelection(selection);
}

bool CQScanWidgetParameterSet::save(CCopasiParameterGroup * pItem) const
{
  mpData->setValue< unsigned C_INT32 >("Number of steps", mSelection.size());
  auto * group = mpData->getGroup("ParameterSet CNs");
  if (!group)
    {
      mpData->addParameter("ParameterSet CNs", CCopasiParameter::Type::GROUP);
      group = mpData->getGroup("ParameterSet CNs");
    }

  group->clear();
  int count = 0;
  for (auto & p : mSelection)
    {
      group->addParameter(std::to_string(count++), CCopasiParameter::Type::CN, p.second->getCN());
    }

  if (pItem != NULL)
    {
      if (*mpData == *pItem)
        return false;

      *pItem = *mpData;
      return true;
    }
}

void CQScanWidgetParameterSet::initFromSelection(std::map< QString, const CModelParameterSet * > & selection)
{
  mSelection = selection;

  // generate label, just listing the names of the parameter sets selected
  QString label;
  for (auto & entry : mSelection)
    label.append(entry.first).append(", ");
  // remove last ", "
  label.chop(2);

  txtSets->setText(label);
}

void CQScanWidgetParameterSet::init()
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  QColor Foreground = Palette.color(QPalette::Active, QPalette::Text);
  QColor Background = Palette.color(QPalette::Active, QPalette::Base);
  QColor Target(210, 255, 210, 255);

  if (Foreground.redF() + Foreground.greenF() + Foreground.blueF() > Background.redF() + Background.greenF() + Background.blueF())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
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

  // clear selection
  mSelection.clear();
}

void CQScanWidgetParameterSet::slotChooseParameterSets()
{
  auto * dmGui = getDataModel();
  if (!dmGui)
    return;
  auto * dm = dmGui->getDataModel();
  if (!dm)
    return;
  auto * model = dm->getModel();
  if (!model)
    return;

  QStringList oldSelection;
  for (auto & p : mSelection)
    oldSelection << p.first;

  std::map< QString, const CModelParameterSet * > pSets;
  auto & sets = model->getModelParameterSets();
  QStringList list;
  for (auto & set : sets)
    {
      QString current = FROM_UTF8(set.getObjectName());
      pSets[current] = &set;
      list << current;
    }

  QStringList selection = CQMultipleSelectionDialog::getSelection(this, "Select ParameterSet(s)", "Parameter Sets:", list, &oldSelection);
  if (selection.isEmpty())
    return;

  std::map< QString, const CModelParameterSet * > pSelection;
  for (auto & set : pSets)
    {
      if (selection.contains(set.first))
        pSelection.insert(set);
    }

  pSets = std::move(pSelection);
  if (!pSets.empty() && oldSelection != selection) // Object selection changed.
    initFromSelection(pSets);
}
