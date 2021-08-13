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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QApplication>
#include <QTableWidgetItem>
#include <QStringList>
#include <QLineEdit>
#include <QCommonStyle>

#include "copasi/UI/parametertable.h"
#include "copasi/UI/CQComboDelegate.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/copasi.h"

#include "copasi/UI/qtUtilities.h"

#include "copasi/model/CReactionInterface.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/utilities/CUnitValidator.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/math/CMathExpression.h"
#include "copasi/commandline/CConfigurationFile.h"

ParameterTable::ParameterTable(QWidget * parent)
  : QTableWidget(parent),
    mOldRow(0)
{
  initTable();

  connect(this, SIGNAL(cellChanged(int, int)),
          this, SLOT(slotCellChanged(int, int)));

  connect(this, SIGNAL(currentCellChanged(int, int, int, int)),
          this, SLOT(slotCurrentCellChanged(int, int, int, int)));

  connect(this, SIGNAL(signalChanged(int, int, QString)),
          parent, SLOT(slotTableChanged(int, int, QString)));

  connect(this, SIGNAL(parameterStatusChanged(int, bool)),
          parent, SLOT(slotParameterStatusChanged(int, bool)));
}

void ParameterTable::initTable()
{
  setRowCount(0);
  setSelectionMode(QTableWidget::NoSelection);

  mpComboDelegate = new CQComboDelegate(this);
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
    ret.push_back(CMetabNameInterface::getDisplayName(&model, model.getMetabolites()[i], false));

  //now all the metabs from the ReactionInterface (that have not yet been committed to the model)
  std::vector<std::string> lll;
  std::vector<std::string>::const_iterator sourceIt, sourceItEnd;
  std::vector<std::string>::const_iterator searchIt, searchItEnd;

  lll = ri.getListOfMetabs(CFunctionParameter::Role::SUBSTRATE);
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

  lll = ri.getListOfMetabs(CFunctionParameter::Role::PRODUCT);
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

  lll = ri.getListOfMetabs(CFunctionParameter::Role::MODIFIER);
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
    ret += FROM_UTF8(model.getModelValues()[i].getObjectName());

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
    ret += FROM_UTF8(model.getCompartments()[i].getObjectName());

  return ret;
}

void ParameterTable::updateTable(CReactionInterface & ri, CReaction * pReaction)
{
  bool wasSortingEnabled = isSortingEnabled();
  setSortingEnabled(false);

  blockSignals(true); // So cellChanged doesn't fire when items are set.

  setRowCount(0);

  if (pReaction == NULL) return;

  CModel * pModel = dynamic_cast< CModel * >(pReaction->getObjectAncestor("Model"));

  // Handle units

  // Determine the units of the variables depending on the type
  std::vector < CUnit > Variables;

  size_t i, imax = ri.size();
  size_t j, jmax;

  for (i = 0; i < imax; ++i)
    {
      switch (ri.getUsage(i))
        {
          case CFunctionParameter::Role::SUBSTRATE:
          case CFunctionParameter::Role::PRODUCT:
          case CFunctionParameter::Role::MODIFIER:

            if (ri.isVector(i))
              {
                std::vector< std::string > Units = ri.getUnitVector(i);

                std::vector< std::string >::const_iterator it = Units.begin();
                std::vector< std::string >::const_iterator end = Units.end();

                for (; it != end; ++it)
                  {
                    Variables.push_back(*it);
                  }
              }
            else
              {
                Variables.push_back(ri.getUnit(i)); // This is just to compare the results
              }

            break;

          case CFunctionParameter::Role::PARAMETER:
          case CFunctionParameter::Role::VARIABLE:
          case CFunctionParameter::Role::TEMPORARY:
          case CFunctionParameter::Role::VOLUME:
          case CFunctionParameter::Role::TIME:
            Variables.push_back(ri.getUnit(i));
            break;
        }
    }

  // This depends on the effective kinetic law units.
  CMathContainer & Container = pModel->getMathContainer();
  CUnitValidator Validator(Container, ri.getFunction());

  Validator.validateUnits(ri.getEffectiveKineticLawUnit(), Variables);

  CFunctionParameter::Role usage;

  // Load the comboDelegate lists
  mGlobalParameters.clear();
  mGlobalParameters = getListOfAllGlobalParameterNames(*pModel);

  if (mGlobalParameters.indexOf("--local--") != -1) // in case someone names a parameter "--local--"
    mGlobalParameters.replace(mGlobalParameters.indexOf("--local--"), "\"--local--\"");

  mGlobalParameters.push_front("--local--");

  std::vector<std::string>::const_iterator it;

  mSubstrates.clear();
  usage = CFunctionParameter::Role::SUBSTRATE;

  for (it = ri.getListOfMetabs(usage).begin(); it != ri.getListOfMetabs(usage).end(); ++it)
    mSubstrates += FROM_UTF8(CMetabNameInterface::unQuote(*it));

  if (mSubstrates.empty())
    mSubstrates += "unknown";

  mProducts.clear();
  usage = CFunctionParameter::Role::PRODUCT;

  for (it = ri.getListOfMetabs(usage).begin(); it != ri.getListOfMetabs(usage).end(); ++it)
    mProducts += FROM_UTF8(CMetabNameInterface::unQuote(*it));

  if (mProducts.empty())
    mProducts += "unknown";

  mModifiers.clear();  // Get all metabs; modifiers are never locked
  vectorOfStrings2QStringList(getListOfAllMetabNames(*pModel, ri), mModifiers);

  mVolumes.clear();
  mVolumes = getListOfAllCompartmentNames(*pModel);

  size_t rowCounter = 0;

  QTableWidgetItem *pItem = NULL;

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  QColor Foreground = Palette.color(QPalette::Active, QPalette::Text);
  QColor Background = Palette.color(QPalette::Active, QPalette::Base);

  bool isDarkTheme = (Foreground.redF() + Foreground.greenF() + Foreground.blueF() > Background.redF() + Background.greenF() + Background.blueF());
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
          case CFunctionParameter::Role::SUBSTRATE:
            color = subsColor;
            break;

          case CFunctionParameter::Role::PRODUCT:
            color = prodColor;
            break;

          case CFunctionParameter::Role::MODIFIER:
            color = modiColor;
            break;

          case CFunctionParameter::Role::PARAMETER:
            color = paraColor;
            break;

          case CFunctionParameter::Role::VOLUME:
            color = volColor;
            break;

          case CFunctionParameter::Role::TIME:
            color = timeColor;
            break;

          case CFunctionParameter::Role::VARIABLE:
            color = QColor(255, 20, 20);
            break;

          default :
            qUsage = "unknown";
            color = QColor(255, 20, 20);
            break;
        }

      // add first column
      pItem = new QTableWidgetItem(qUsage);

      if (isDarkTheme)
        pItem->setForeground(color);
      else
        pItem->setBackground(color);

      if (usage == CFunctionParameter::Role::SUBSTRATE)
        pItem->setIcon(CQIconResource::icon(CQIconResource::reactionSubstrate));
      else if (usage == CFunctionParameter::Role::PRODUCT)
        pItem->setIcon(CQIconResource::icon(CQIconResource::reactionProduct));
      else if (usage == CFunctionParameter::Role::MODIFIER)
        pItem->setIcon(CQIconResource::icon(CQIconResource::reactionModifier));

      pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
      setItem((int) rowCounter, 0, pItem);

      // add second column
      pItem = new QTableWidgetItem(FROM_UTF8(ri.getParameterName(i)));

      if (isDarkTheme)
        pItem->setForeground(color);
      else
        pItem->setBackground(color);

      if ((usage != CFunctionParameter::Role::PARAMETER)
          && (usage != CFunctionParameter::Role::VOLUME)
          && (usage != CFunctionParameter::Role::TIME))
        {
          if (locked)
            pItem->setIcon(CQIconResource::icon(CQIconResource::locked));
          else
            pItem->setIcon(CQIconResource::icon(CQIconResource::unlocked));
        }

      pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
      setItem((int) rowCounter, 1, pItem);

      // add units column
      if (rowCounter < Validator.getVariableUnits().size())
        {
          const CValidatedUnit & Unit = Validator.getVariableUnits()[rowCounter];
          pItem = new QTableWidgetItem(FROM_UTF8(" " + Unit.getExpression()));

          if (Unit.conflict() && usage == CFunctionParameter::Role::PARAMETER)
            {
              CValidity Validity;
              Validity.add(CIssue(CIssue::eSeverity::Warning, CIssue::eKind::UnitConflict));
              pItem->setToolTip(FROM_UTF8(Validity.getIssueMessages()));
              pItem->setIcon(QCommonStyle().standardIcon(QStyle::SP_MessageBoxWarning));
            }
        }
      else
        {
          pItem = new QTableWidgetItem(" ? ");
        }

      if (isDarkTheme)
        pItem->setForeground(color);
      else
        pItem->setBackground(color);

      pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
      setItem((int) rowCounter, 4, pItem);

      // Create and color Value column
      pItem = new QTableWidgetItem("");

      if (isDarkTheme)
        pItem->setForeground(color);
      else
        pItem->setBackground(color);

      pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
      setItem((int) rowCounter, 3, pItem);

      // add fourth (Mapping) column (col index = 3)
      pItem = new QTableWidgetItem("");

      if (isDarkTheme)
        pItem->setForeground(color);
      else
        pItem->setBackground(color);

      setItem((int) rowCounter, 2, pItem);

      // if line is for a metabolite Parameter . . .
      if ((usage == CFunctionParameter::Role::SUBSTRATE)
          || (usage == CFunctionParameter::Role::PRODUCT)
          || (usage == CFunctionParameter::Role::MODIFIER))
        {

          metabNames = &(ri.getMappings(i));

          if (locked)
            {
              pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
              mpComboDelegate->setItems(rowCounter, QStringList());
              closePersistentEditor(pItem);
            }
          else
            {
              if (usage == CFunctionParameter::Role::SUBSTRATE)
                mpComboDelegate->setItems(rowCounter, mSubstrates);
              else if (usage == CFunctionParameter::Role::PRODUCT)
                mpComboDelegate->setItems(rowCounter, mProducts);
              else   // must be MODIFIER
                {
                  mpComboDelegate->setItems(rowCounter, mModifiers);
                }

              //openPersistentEditor(pItem);
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

                          if (isDarkTheme)
                            pItem->setForeground(color);
                          else
                            pItem->setBackground(color);

                          setItem((int) rowCounter, k, pItem);
                        }

                      item((int) rowCounter, 2)->setText(FROM_UTF8((*metabNames)[j]));

                      if (rowCounter < Validator.getVariableUnits().size())
                        item((int) rowCounter, 4)->setText(FROM_UTF8(" " + Validator.getVariableUnits()[rowCounter].getExpression()));
                    }
                }
            }
        }
      // if line is for a kinetic parameter . . .
      else if (usage == CFunctionParameter::Role::PARAMETER)
        {
          mpComboDelegate->setItems(rowCounter, mGlobalParameters);

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

          //openPersistentEditor(pItem);

          // add item to Value column
          pItem = item((int) rowCounter, 3);

          if (ri.isLocalValue(i))
            {
              pItem->setText(convertToQString(ri.getLocalValue(i)));
              pItem->setFlags(pItem->flags() | (Qt::ItemIsEditable));
              pItem->setForeground(Foreground);
            }
          else
            {
              const std::vector< const CDataObject * > &mapping = pReaction->getParameterObjects(i);

              if (mapping.size() > 0)
                {
                  const CModelValue * pParamObject =
                    dynamic_cast<const CModelValue *>(mapping[0]);

                  if (pParamObject != NULL &&
                      pParamObject->getStatus() == CModelEntity::Status::FIXED)
                    {
                      pItem->setText(convertToQString(pParamObject->getInitialValue()));
                    }
                }
            }
        }

      // if line is for a volume . . .
      else if (usage == CFunctionParameter::Role::VOLUME)
        {
          mpComboDelegate->setItems(rowCounter, mVolumes);
          pItem->setText(FROM_UTF8(ri.getMapping(i)));
          //openPersistentEditor(pItem);
        }
      // if line is for time . . .
      else if (usage == CFunctionParameter::Role::TIME)
        {
          pItem->setText("");
        }
      // if line is for an unknown role . . .
      else
        {
          pItem->setText(convertToQString(ri.getLocalValue(i)));
        }

      if (CRootContainer::getConfiguration()->resizeToContents())
        {
          resizeRowToContents((int)rowCounter);
        }

      ++rowCounter;
    }

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      resizeColumnsToContents();
    }

  blockSignals(false);
  setSortingEnabled(wasSortingEnabled);
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

  QModelIndex Index = model()->index(row, col, QModelIndex());

  const QStringList & comboList = mpComboDelegate->getItems(Index);

  if (col == 2
      && !comboList.empty()
      && comboList[0] == "--local--") //is Parameter
    {
      emit parameterStatusChanged((int) i, (newVal == "--local--"));

      if (newVal == "--local--")
        newVal = "0"; // item(row, 3)->text();
    }

  emit signalChanged((int) i, row - (int) mIndex2Line[i], newVal);
}

void ParameterTable::slotCurrentCellChanged(int currentRow, int currentColumn,
    int previousRow, int previousColumn)
{
  if (currentColumn == previousColumn && currentRow == previousRow)
    return;

  if (previousColumn == 2)
    {
      QTableWidgetItem *pItem = item(previousRow, previousColumn);
      closePersistentEditor(pItem);
    }

  if (currentColumn == 2)
    {
      QTableWidgetItem *pItem = item(currentRow, currentColumn);

      if (mpComboDelegate->getItems(indexFromItem(pItem)).count() > 1)
        openPersistentEditor(pItem);
    }
}
