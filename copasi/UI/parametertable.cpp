// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtGui/QTableWidgetItem>
#include <QtCore/QStringList>
#include <QtGui/QLineEdit>

#include "parametertable.h"
#include "resourcesUI/CQIconResource.h"

#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "qtUtilities.h"
#include "utilities/CDimension.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "CQComboDelegate.h"

ParameterTable::ParameterTable(QWidget * parent)
  : QTableWidget(parent),
    mOldRow(0)
{
  initTable();

  connect(this, SIGNAL(cellChanged(int, int)),
          this, SLOT(slotCellChanged(int, int)));

  connect(this, SIGNAL(signalChanged(int, int, QString)),
          parent, SLOT(slotTableChanged(int, int, QString)));

  connect(this, SIGNAL(parameterStatusChanged(int, bool)),
          parent, SLOT(slotParameterStatusChanged(int, bool)));
}

void ParameterTable::initTable()
{
  setRowCount(0);
  setSelectionMode(QTableWidget::NoSelection);

  mpComboDelegate = new CQComboDelegate(NULL, this);
  setItemDelegateForColumn(2, mpComboDelegate);

  setShowGrid(false);
}

const std::vector<std::string> ParameterTable::getListOfAllMetabNames(const CModel & model,
    const CReactionInterface & ri)
{
  std::vector<std::string> ret;

  ret.push_back("unknown");

  //first all the metabs in the model
  size_t i, imax = model.getMetabolites().size();

  for (i = 0; i < imax; ++i)
    ret.push_back(CMetabNameInterface::getDisplayName(&model, *model.getMetabolites()[i], false));

  //now all the metabs from the ReactionInterface (that have not yet been committed to the model)
  std::vector<std::string> lll;
  std::vector<std::string>::const_iterator sourceIt, sourceItEnd;
  std::vector<std::string>::const_iterator searchIt, searchItEnd;

  lll = ri.getListOfMetabs(CFunctionParameter::SUBSTRATE);
  sourceItEnd = lll.end();

  for (sourceIt = lll.begin(); sourceIt != sourceItEnd; ++sourceIt)
    {
      std::string Source = CMetabNameInterface::unQuote(*sourceIt);
      searchItEnd = ret.end();

      for (searchIt = ret.begin(); searchIt != searchItEnd; ++searchIt)
        if (*searchIt == Source)
          break;

      if (searchIt == searchItEnd) //that means new metab name is not in model yet
        ret.push_back(Source);
    }

  lll = ri.getListOfMetabs(CFunctionParameter::PRODUCT);
  sourceItEnd = lll.end();

  for (sourceIt = lll.begin(); sourceIt != sourceItEnd; ++sourceIt)
    {
      std::string Source = CMetabNameInterface::unQuote(*sourceIt);
      searchItEnd = ret.end();

      for (searchIt = ret.begin(); searchIt != searchItEnd; ++searchIt)
        if (*searchIt == Source)
          break;

      if (searchIt == searchItEnd) //that means new metab name is not in model yet
        ret.push_back(Source);
    }

  lll = ri.getListOfMetabs(CFunctionParameter::MODIFIER);
  sourceItEnd = lll.end();

  for (sourceIt = lll.begin(); sourceIt != sourceItEnd; ++sourceIt)
    {
      std::string Source = CMetabNameInterface::unQuote(*sourceIt);
      searchItEnd = ret.end();

      for (searchIt = ret.begin(); searchIt != searchItEnd; ++searchIt)
        if (*searchIt == Source)
          break;

      if (searchIt == searchItEnd) //that means new metab name is not in model yet
        ret.push_back(Source);
    }

  return ret;
}

//static
QStringList ParameterTable::getListOfAllGlobalParameterNames(const CModel & model)
{
  QStringList ret;

  ret += "unknown";

  //all the global paramters  in the model
  size_t i, imax = model.getNumModelValues();

  for (i = 0; i < imax; ++i)
    ret += FROM_UTF8(model.getModelValues()[i]->getObjectName());

  return ret;
}

//static
QStringList ParameterTable::getListOfAllCompartmentNames(const CModel & model)
{
  QStringList ret;

  ret += "unknown";

  //all the global paramters  in the model
  size_t i, imax = model.getCompartments().size();

  for (i = 0; i < imax; ++i)
    ret += FROM_UTF8(model.getCompartments()[i]->getObjectName());

  return ret;
}

void ParameterTable::updateTable(const CReactionInterface & ri, const CReaction * pReaction)
{
  blockSignals(true); // So cellChanged doesn't fire when items are set.

  setRowCount(0);

  if (pReaction == NULL) return;

  CModel * pModel = dynamic_cast< CModel * >(pReaction->getObjectAncestor("Model"));

  //first get the units strings
  CFindDimensions units(ri.getFunction(), pModel->getQuantityUnit()->isDimensionless(),
                        pModel->getVolumeUnit()->isDimensionless(),
                        pModel->getTimeUnit()->isDimensionless(),
                        pModel->getAreaUnit()->isDimensionless(),
                        pModel->getLengthUnit()->isDimensionless()
                       );
  units.setUseHeuristics(true);
  units.setMolecularitiesForMassAction(ri.getChemEqInterface().getMolecularity(CFunctionParameter::SUBSTRATE),
                                       ri.getChemEqInterface().getMolecularity(CFunctionParameter::PRODUCT));
  units.findDimensions(ri.isMulticompartment());

  CFunctionParameter::Role usage;

  // Load the comboDelegate lists
  mGlobalParameters.clear();
  mGlobalParameters = getListOfAllGlobalParameterNames(*pModel);

  if (mGlobalParameters.indexOf("--local--") != -1) // in case someone names a parameter "--local--"
    mGlobalParameters.replace(mGlobalParameters.indexOf("--local--"), "\"--local--\"");

  mGlobalParameters.push_front("--local--");

  std::vector<std::string>::const_iterator it;

  mSubstrates.clear();
  usage = CFunctionParameter::SUBSTRATE;

  for (it = ri.getListOfMetabs(usage).begin(); it != ri.getListOfMetabs(usage).end(); ++it)
    mSubstrates += FROM_UTF8(CMetabNameInterface::unQuote(*it));

  mProducts.clear();
  usage = CFunctionParameter::PRODUCT;

  for (it = ri.getListOfMetabs(usage).begin(); it != ri.getListOfMetabs(usage).end(); ++it)
    mProducts += FROM_UTF8(CMetabNameInterface::unQuote(*it));

  mModifiers.clear();  // Get all metabs; modifiers are never locked
  vectorOfStrings2QStringList(getListOfAllMetabNames(*pModel, ri), mModifiers);

  mVolumes.clear();
  mVolumes = getListOfAllCompartmentNames(*pModel);

  size_t i, imax = ri.size();
  size_t j, jmax;
  size_t rowCounter = 0;

  QTableWidgetItem *pItem = NULL;

  QColor subsColor(255, 210, 210);
  QColor prodColor(210, 255, 210);
  QColor modiColor(250, 250, 190);
  QColor paraColor(210, 210, 255);
  QColor volColor(210, 210, 255);
  QColor timeColor(210, 210, 210);

  QString qUsage;
  bool locked = false;
  QColor color;
  const std::vector<std::string> * metabNames;

  mIndex2Line.resize(imax);
  mLine2Index.clear();

  setRowCount((int) imax);

  for (i = 0; i < imax; ++i)
    {
      mIndex2Line[i] = rowCounter;

      // set the stuff that is different for the specific usages
      usage = ri.getUsage(i);
      qUsage = FROM_UTF8(CFunctionParameter::RoleNameDisplay[usage]);
      locked = ri.isLocked(i);

      switch (usage)
        {
          case CFunctionParameter::SUBSTRATE:
            color = subsColor;
            break;

          case CFunctionParameter::PRODUCT:
            color = prodColor;
            break;

          case CFunctionParameter::MODIFIER:
            color = modiColor;
            break;

          case CFunctionParameter::PARAMETER:
            color = paraColor;
            break;

          case CFunctionParameter::VOLUME:
            color = volColor;
            break;

          case CFunctionParameter::TIME:
            color = timeColor;
            break;

          case CFunctionParameter::VARIABLE:
            color = QColor(255, 20, 20);
            break;

          default :
            qUsage = "unknown";
            color = QColor(255, 20, 20);
            break;
        }

      // add first column
      pItem = new QTableWidgetItem(qUsage);
      pItem->setBackground(color);

      if (usage == CFunctionParameter::SUBSTRATE)
        pItem->setIcon(CQIconResource::icon(CQIconResource::reactionSubstrate));
      else if (usage == CFunctionParameter::PRODUCT)
        pItem->setIcon(CQIconResource::icon(CQIconResource::reactionProduct));
      else if (usage == CFunctionParameter::MODIFIER)
        pItem->setIcon(CQIconResource::icon(CQIconResource::reactionModifier));

      pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
      setItem((int) rowCounter, 0, pItem);

      // add second column
      pItem = new QTableWidgetItem(FROM_UTF8(ri.getParameterName(i)));
      pItem->setBackground(color);

      if ((usage != CFunctionParameter::PARAMETER)
          && (usage != CFunctionParameter::VOLUME)
          && (usage != CFunctionParameter::TIME))
        {
          if (locked)
            pItem->setIcon(CQIconResource::icon(CQIconResource::locked));
          else
            pItem->setIcon(CQIconResource::icon(CQIconResource::unlocked));
        }

      pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
      setItem((int) rowCounter, 1, pItem);

      // add units column
      const CCopasiDataModel* pDataModel = pModel->getObjectDataModel();

      if (pDataModel == NULL) return;

      QString theseUnits = FROM_UTF8(" " + units.getDimensions()[i].getDisplayString(pModel));
      pItem = new QTableWidgetItem(theseUnits);
      pItem->setBackgroundColor(color);
      pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
      setItem((int) rowCounter, 4, pItem);

      // Create and color Value column
      pItem = new QTableWidgetItem("");
      pItem->setBackground(QColor(color));
      pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
      setItem((int) rowCounter, 3, pItem);

      // add fourth (Mapping) column (col index = 3)
      pItem = new QTableWidgetItem("");
      pItem->setBackground(color);
      setItem((int) rowCounter, 2, pItem);

      // if line is for a metabolite Parameter . . .
      if ((usage == CFunctionParameter::SUBSTRATE)
          || (usage == CFunctionParameter::PRODUCT)
          || (usage == CFunctionParameter::MODIFIER))
        {

          metabNames = &(ri.getMappings(i));

          if (locked)
            {
              pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
              closePersistentEditor(pItem);
            }
          else
            {
              if (usage == CFunctionParameter::SUBSTRATE)
                mpComboDelegate->setItems(rowCounter, &mSubstrates);
              else if (usage == CFunctionParameter::PRODUCT)
                mpComboDelegate->setItems(rowCounter, &mProducts);
              else   // must be MODIFIER
                {
                  mpComboDelegate->setItems(rowCounter, &mModifiers);
                }

              openPersistentEditor(pItem);
            }

          if (!ri.isVector(i))
            pItem->setText(FROM_UTF8(CMetabNameInterface::unQuote((*metabNames)[0])));
          else
            {
              if (locked)
                pItem->setText("");
              else  // this should not happen
                pItem->setText("add species");

              // add lines for vector parameters
              jmax = metabNames->size();

              if (jmax > 0)
                {
                  setRowCount(rowCount() + (int)(jmax - 1));

                  item((int) rowCounter, 2)->setText(FROM_UTF8((*metabNames)[0]));

                  for (j = 1; j < jmax; ++j)
                    {
                      ++rowCounter;

                      for (int k = 0; k < 5; k++)
                        {
                          pItem = new QTableWidgetItem("");
                          pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
                          pItem->setBackgroundColor(color);
                          setItem((int) rowCounter, k, pItem);
                        }

                      item((int) rowCounter, 2)->setText(FROM_UTF8((*metabNames)[j]));
                      item((int) rowCounter, 4)->setText(theseUnits);
                    }
                }
            }
        }
      // if line is for a kinetic parameter . . .
      else if (usage == CFunctionParameter::PARAMETER)
        {
          mpComboDelegate->setItems(rowCounter, &mGlobalParameters);

          if (ri.isLocalValue(i))
            {
              pItem->setText("--local--");
            }
          else //global parameter
            {
              QString paramText = FROM_UTF8(ri.getMapping(i));

              if (paramText == "--local--")
                paramText = "\"--local--\"";

              pItem->setText(paramText);
            }

          openPersistentEditor(pItem);

          // add item to Value column
          pItem = item((int) rowCounter, 3);

          if (ri.isLocalValue(i))
            {
              pItem->setText(QString::number(ri.getLocalValue(i)));
              pItem->setFlags(pItem->flags() | (Qt::ItemIsEditable));
            }
          else
            {
              const std::vector<std::string> &mapping = pReaction->getParameterMapping(i);

              if (mapping.size() > 0)
                {
                  std::string Key = mapping[0];

                  const CModelValue * pParamObject =
                    dynamic_cast<const CModelValue *>(CCopasiRootContainer::getKeyFactory()->get(Key));

                  if (pParamObject != NULL &&
                      pParamObject->getStatus() == CModelEntity::FIXED)
                    {
                      pItem->setText(QString::number(pParamObject->getInitialValue()));
                      pItem->setTextColor(QColor(Qt::darkGray));
                    }
                }
            }
        }

      // if line is for a volume . . .
      else if (usage == CFunctionParameter::VOLUME)
        {
          mpComboDelegate->setItems(rowCounter, &mVolumes);
          pItem->setText(FROM_UTF8(ri.getMapping(i)));
          openPersistentEditor(pItem);
        }
      // if line is for time . . .
      else if (usage == CFunctionParameter::TIME)
        {
          pItem->setText("");
        }
      // if line is for an unknown role . . .
      else
        {
          pItem->setText(QString::number(ri.getLocalValue(i)));
        }

      resizeRowToContents((int) rowCounter);

      ++rowCounter;
    }

  resizeColumnsToContents();

  blockSignals(false);
}

void ParameterTable::handleCurrentCell(int row, int col, int, int)
{
  bool changed = false;

  size_t i, imax = mIndex2Line.size();

  for (i = 0; i < imax; ++i)
    if ((int) mIndex2Line[i] - 1 == row)
      {
        changed = true;
        if ((mOldRow < row) || (row == 0)) ++row; else --row;

        break;
      }

  if (col > 3) {changed = true; col = 3;}

  if (col < 2) {changed = true; col = 2;}

  mOldRow = row;

  if (changed) setCurrentCell(row, col);

  //TODO: allow keyboard editing of col 2
}

void ParameterTable::slotCellChanged(int row, int col)
{
  if (col != 2 && col != 3) return; //Other cols shouldn't change, anyway.

  size_t i, imax = mIndex2Line.size();

  for (i = imax - 1; i != C_INVALID_INDEX; --i)
    if ((int) mIndex2Line[i] <= row) break;

  QString newVal = item(row, col)->text();

  QStringList comboList = *mpComboDelegate->getItems(row);

  if (col == 2 && comboList[0] == "--local--") //is Parameter
    {
      emit parameterStatusChanged((int) i, (newVal == "--local--"));

      if (newVal == "--local--")
        newVal = "0"; // item(row, 3)->text();
    }

  emit signalChanged((int) i, row - (int) mIndex2Line[i], newVal);
}
