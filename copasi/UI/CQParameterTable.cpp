// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQParameterTable.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/14 17:30:45 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QStringList>
#include <QComboBox>
#include <QHeaderView>
#include <qlineedit.h>
#include <QPixmap>

#include <stdlib.h>

#include "CQParameterTable.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "qtUtilities.h"
#include "utilities/CDimension.h"
#include "copasi/report/CCopasiRootContainer.h"

#include "./icons/product.xpm"
#include "./icons/substrate.xpm"
#include "./icons/modifier.xpm"
#include "./icons/locked.xpm"
#include "./icons/unlocked.xpm"

ParameterTable::ParameterTable(QWidget * parent, const char * name) :
    QTableWidget(parent),
    mOldRow(0)
{
  setObjectName(name);

  initTable();

  connect(this, SIGNAL(currentChanged(int, int)),
          this, SLOT(handleCurrentCell(int, int)));

  connect(this, SIGNAL(valueChanged(int, int)),
          this, SLOT(slotCellChanged(int, int)));

  connect(this, SIGNAL(signalChanged(int, int, QString)),
          parent, SLOT(slotTableChanged(int, int, QString)));

  connect(this, SIGNAL(parameterStatusChanged(int, bool)),
          parent, SLOT(slotParameterStatusChanged(int, bool)));
}

void ParameterTable::initTable()
{
  setRowCount(0);
  verticalHeader()->setVisible(false);
  setSelectionMode(QAbstractItemView::NoSelection);

  //setNumRows(3);
  setColumnCount(5);

  setHorizontalHeaderItem(0, new QTableWidgetItem("Description"));
  setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
  setHorizontalHeaderItem(2, new QTableWidgetItem("global"));
  setHorizontalHeaderItem(3, new QTableWidgetItem("Value"));
  setHorizontalHeaderItem(4, new QTableWidgetItem("Unit"));

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
    ret.push_back(CMetabNameInterface::getDisplayName(&model, *model.getMetabolites()[i]));

  //now all the metabs from the ReactionInterface (that have not yet been committed to the model)
  std::vector<std::string> lll;
  std::vector<std::string>::const_iterator sourceIt, sourceItEnd;
  std::vector<std::string>::const_iterator searchIt, searchItEnd;

  lll = ri.getListOfMetabs(CFunctionParameter::SUBSTRATE);
  sourceItEnd = lll.end();

  for (sourceIt = lll.begin(); sourceIt != sourceItEnd; ++sourceIt)
    {
      searchItEnd = ret.end();

      for (searchIt = ret.begin(); searchIt != searchItEnd; ++searchIt)
        if (*searchIt == *sourceIt)
          break;

      if (searchIt == searchItEnd) //that means new metab name is not in model yet
        ret.push_back(*sourceIt);
    }

  lll = ri.getListOfMetabs(CFunctionParameter::PRODUCT);
  sourceItEnd = lll.end();

  for (sourceIt = lll.begin(); sourceIt != sourceItEnd; ++sourceIt)
    {
      searchItEnd = ret.end();

      for (searchIt = ret.begin(); searchIt != searchItEnd; ++searchIt)
        if (*searchIt == *sourceIt)
          break;

      if (searchIt == searchItEnd) //that means new metab name is not in model yet
        ret.push_back(*sourceIt);
    }

  lll = ri.getListOfMetabs(CFunctionParameter::MODIFIER);
  sourceItEnd = lll.end();

  for (sourceIt = lll.begin(); sourceIt != sourceItEnd; ++sourceIt)
    {
      searchItEnd = ret.end();

      for (searchIt = ret.begin(); searchIt != searchItEnd; ++searchIt)
        if (*searchIt == *sourceIt)
          break;

      if (searchIt == searchItEnd) //that means new metab name is not in model yet
        ret.push_back(*sourceIt);
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

  //all the global parameters  in the model
  size_t i, imax = model.getCompartments().size();

  for (i = 0; i < imax; ++i)
    ret += FROM_UTF8(model.getCompartments()[i]->getObjectName());

  return ret;
}

void ParameterTable::updateTable(const CReactionInterface & ri, const CModel & model)
{
  //first get the units strings
  CFindDimensions units(ri.getFunction(), model.getQuantityUnitEnum() == CModel::dimensionlessQuantity,
                        model.getVolumeUnitEnum() == CModel::dimensionlessVolume,
                        model.getTimeUnitEnum() == CModel::dimensionlessTime,
                        model.getAreaUnitEnum() == CModel::dimensionlessArea,
                        model.getLengthUnitEnum() == CModel::dimensionlessLength
                       );
  units.setUseHeuristics(true);
  units.setMolecularitiesForMassAction(ri.getChemEqInterface().getMolecularity(CFunctionParameter::SUBSTRATE),
                                       ri.getChemEqInterface().getMolecularity(CFunctionParameter::PRODUCT));
  units.findDimensions(ri.isMulticompartment());

  size_t i, imax = ri.size();
  size_t j, jmax;
  size_t rowCounter = 0;

  QStringList qsl;

  QColor subsColor(255, 210, 210);
  QColor prodColor(210, 255, 210);
  QColor modiColor(250, 250, 190);
  QColor paraColor(210, 210, 255);
  QColor volColor(210, 210, 255);
  QColor timeColor(210, 210, 210);

  QPixmap * pProduct = new QPixmap((const char**)product_xpm);
  QPixmap * pSubstrate = new QPixmap((const char**)substrate_xpm);
  QPixmap * pModifier = new QPixmap((const char**)modifier_xpm);
  QPixmap * pLocked = new QPixmap((const char**)locked_xpm);
  QPixmap * pUnlocked = new QPixmap((const char**)unlocked_xpm);

  CFunctionParameter::Role usage;
  QString qUsage;
  QColor color;
  const std::vector<std::string> * metabNames;

  mIndex2Line.resize(imax);
  mLine2Index.clear();

  this->setRowCount(0);
  this->setRowCount((int)(imax*2));

  for (i = 0; i < imax; ++i)
    {
      rowCounter++;
      mIndex2Line[i] = rowCounter;

      // set the stuff that is different for the specific usages
      usage = ri.getUsage(i);
      qUsage = FROM_UTF8(CFunctionParameter::RoleNameDisplay[usage]);

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

          default:
            qUsage = "unknown";
            color = QColor(255, 20, 20);
            break;
        }

      // add first column
      QTableWidgetItem * pItem = new ColorTableItem(color, qUsage);

      if (usage == CFunctionParameter::SUBSTRATE) pItem->setIcon(*pSubstrate);

      if (usage == CFunctionParameter::PRODUCT) pItem->setIcon(*pProduct);

      if (usage == CFunctionParameter::MODIFIER) pItem->setIcon(*pModifier);

      setItem((int) rowCounter, 0, pItem);

      // add second column
      pItem = new ColorTableItem(color, FROM_UTF8(ri.getParameterName(i)));

      if ((usage != CFunctionParameter::PARAMETER)
          && (usage != CFunctionParameter::VOLUME)
          && (usage != CFunctionParameter::TIME))
        {
          if (ri.isLocked(i))
            pItem->setIcon(*pLocked);
          else
            pItem->setIcon(*pUnlocked);
        }

      setItem((int) rowCounter, 1, pItem);

      // add third column
      pItem = new ColorTableItem(color, "");

      if (usage == CFunctionParameter::PARAMETER)
        {
          pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
          pItem->setCheckState(ri.isLocalValue(i) ? Qt::Unchecked : Qt::Checked);
        }

      setItem((int) rowCounter, 2, pItem);

      // add units column
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      pItem = new ColorTableItem(color, FROM_UTF8(" " + units.getDimensions()[i].getDisplayString(pDataModel)));
      setItem((int) rowCounter, 4, pItem);

      // add a line for a metabolite Parameter
      if ((usage == CFunctionParameter::SUBSTRATE)
          || (usage == CFunctionParameter::PRODUCT)
          || (usage == CFunctionParameter::MODIFIER))
        {
          // get the list of possible metabs (for the combo box)
          if (usage == CFunctionParameter::MODIFIER) //get all metabs; modifiers are never locked
            vectorOfStrings2QStringList(getListOfAllMetabNames(model, ri), qsl);
          else //only get the modifiers from the ChemEq
            {
              if (!ri.isLocked(i))
                vectorOfStrings2QStringList(ri.getListOfMetabs(usage), qsl);
            }

          metabNames = &(ri.getMappings(i));

          if (!ri.isVector(i))
            {
              if (ri.isLocked(i))
                {
                  pItem = new ColorTableItem(color, FROM_UTF8((*metabNames)[0]));
                  setItem((int) rowCounter, 3, pItem);
                }
              else
                {
                  QComboBox * pComboBox = new QComboBox();
                  pComboBox->addItems(qsl);
                  pComboBox->setBackgroundColor(color);
                  pComboBox->setCurrentText(FROM_UTF8((*metabNames)[0]));

                  setCellWidget((int) rowCounter, 3, pComboBox);
                }
            }
          else
            {
              if (ri.isLocked(i))
                {
                  pItem = new ColorTableItem(color, "");
                  setItem((int) rowCounter, 3, pItem);
                }
              else // this should not happen
                {
                  QComboBox * pComboBox = new QComboBox();
                  pComboBox->addItems(qsl);
                  pComboBox->setBackgroundColor(color);
                  pComboBox->setCurrentText("add species");

                  setCellWidget((int) rowCounter, 3, pComboBox);
                }

              // add lines for vector parameters
              jmax = metabNames->size();
              setRowCount(rowCount() + (int) jmax);

              for (j = 0; j < jmax; ++j)
                {
                  ++rowCounter;
                  pItem = new ColorTableItem(color, FROM_UTF8((*metabNames)[j]));
                  setItem((int) rowCounter, 3, pItem);
                }
            }
        }
      // add a line for a kinetic parameter
      else if (usage == CFunctionParameter::PARAMETER)
        {
          if (ri.isLocalValue(i))
            {
              pItem = new ColorTableItem(color, QString::number(ri.getLocalValue(i)));
              setItem((int) rowCounter, 3, pItem);
            }
          else //global parameter
            {
              QComboBox * pComboBox = new QComboBox();
              pComboBox->addItems(getListOfAllGlobalParameterNames(model));
              pComboBox->setBackgroundColor(color);
              pComboBox->setCurrentText(FROM_UTF8(ri.getMapping(i)));

              setCellWidget((int) rowCounter, 3, pComboBox);
            }
        }
      // add a line for a kinetic parameter
      else if (usage == CFunctionParameter::VOLUME)
        {
          QComboBox * pComboBox = new QComboBox();
          pComboBox->addItems(getListOfAllCompartmentNames(model));
          pComboBox->setBackgroundColor(color);
          pComboBox->setCurrentText(FROM_UTF8(ri.getMapping(i)));

          setCellWidget((int) rowCounter, 3, pComboBox);
        }
      // add a line for time
      else if (usage == CFunctionParameter::TIME)
        {
          pItem = new ColorTableItem(color, "");
          setItem((int) rowCounter, 3, pItem);
        }
      // add a line for an unknown role
      else
        {
          pItem = new ColorTableItem(color, QString::number(ri.getLocalValue(i)));
          setItem((int) rowCounter, 3, pItem);
        }

      resizeRowToContents((int) rowCounter);

      //mLine2Index

      ++rowCounter;
    }

  this->resizeColumnsToContents();
}

void ParameterTable::handleCurrentCell(int row, int col)
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
  // find the index of the parameter
  size_t i, imax = mIndex2Line.size();

  for (i = imax - 1; i != C_INVALID_INDEX; --i)
    if ((int) mIndex2Line[i] <= row) break;

  //handle the check boxes
  if (col == 2) //only checkboxes is this column
    {
      if (item(row, col)->flags() | Qt::ItemIsUserCheckable)
        {
          emit parameterStatusChanged((int) i, (item(row, col)->checkState() == Qt::Unchecked) ? false : true);

        }

      return;
    }
  else
    {
      emit signalChanged((int) i, row - (int) mIndex2Line[i], item(row, col)->text());
    }
}

//**************************************************************************
#ifdef XXXX
ComboItem::ComboItem(Q3Table *t, EditType et, QColor c, const QStringList & sl)
    : ColorTableItem(t, et, c, "Yes"), cb(0)
{
  // we do not want this item to be replaced
  setReplaceable(false);
  mSL = sl;
}

QWidget *ComboItem::createEditor() const
{
  // create an editor - a combobox in our case
  ((ComboItem*)this)->cb = new QComboBox(false, table()->viewport());
  QObject::connect(cb, SIGNAL(activated(int)), table(), SLOT(doValueChanged()));
  cb->insertStringList(mSL);
  cb->setCurrentText(text());
  return cb;
}

void ComboItem::setContentFromEditor(QWidget *w)
{
  // the user changed the value of the combobox, so synchronize the
  // value of the item (its text), with the value of the combobox
  if (w->inherits("QComboBox"))
    setText(((QComboBox*)w)->currentText());
  else
    Q3TableItem::setContentFromEditor(w);
}

void ComboItem::setText(const QString &s)
{
  Q3TableItem::setText(s);
}
#endif // XXXX
//**********************************************************************

ColorTableItem::ColorTableItem(QColor color, const QString txt) :
    QTableWidgetItem(txt)
{
  setColor(color);
}

ColorTableItem::~ColorTableItem()
{}

void ColorTableItem::setColor(QColor color)
{
  QBrush Brush = this->background();
  Brush.setColor(color);
  setData(Qt::BackgroundRole, Brush);
}

//**********************************************************************
#ifdef XXXX
ColorCheckTableItem::ColorCheckTableItem(Q3Table *t, QColor c, const QString txt)
    : Q3CheckTableItem(t, txt)
{
  color = c;
}

ColorCheckTableItem::~ColorCheckTableItem()
{}

void ColorCheckTableItem::paint(QPainter *p, const QColorGroup &cg,
                                const QRect &cr, bool selected)
{
  QColorGroup g(cg);
  g.setColor(QColorGroup::Base, color);
  Q3CheckTableItem::paint(p, g, cr, selected);
}
#endif // XXXX
