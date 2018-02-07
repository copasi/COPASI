// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtCore/QString>

#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "model/CChemEqInterface.h"
#include "model/CModel.h"
#include "function/CExpression.h"

#include "CQMessageBox.h"
#include "CQSpecieDM.h"
#include "qtUtilities.h"

#include "model/CReaction.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "undoFramework/InsertSpeciesRowsCommand.h"
#include "undoFramework/RemoveSpeciesRowsCommand.h"
#include "undoFramework/RemoveAllSpeciesRowsCommand.h"
#include "undoFramework/SpeciesDataChangeCommand.h"
#include "undoFramework/UndoSpeciesData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoEventAssignmentData.h"

CQSpecieDM::CQSpecieDM(QObject *parent):
  CQBaseDataModel(parent, NULL),
  mFlagConc(true),
  mpMetabolites(NULL),
  mNotify(true)
{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::REACTIONS]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));

  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::REACTIONS));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::FIXED));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ASSIGNMENT));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ODE));

  mUnits.append("?");
  mUnits.append("?");
  mUnits.append("?");
  mUnits.append("?");
}

const QStringList& CQSpecieDM::getTypes()
{
  return mTypes;
}

void CQSpecieDM::setFlagConc(bool flag)
{
  mFlagConc = flag;
}

const std::vector< unsigned C_INT32 >& CQSpecieDM::getItemToType()
{
  return mItemToType;
}

int CQSpecieDM::rowCount(const QModelIndex&) const
{
  return mpMetabolites->size() + 1;
}

int CQSpecieDM::columnCount(const QModelIndex&) const
{
  return TOTAL_COLS_SPECIES;
}

Qt::ItemFlags CQSpecieDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (isDefaultRow(index))
    {
      if (index.column() == COL_NAME_SPECIES || index.column() == COL_COMPARTMENT ||
          index.column() == COL_TYPE_SPECIES || index.column() == COL_ICONCENTRATION ||
          index.column() == COL_INUMBER)
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
      else
        return QAbstractItemModel::flags(index);
    }

  if (index.column() == COL_NAME_SPECIES || index.column() == COL_COMPARTMENT ||
      index.column() == COL_TYPE_SPECIES)
    {
      return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }
  else if (index.column() == COL_ICONCENTRATION)
    {
      CMetab & Species = mpMetabolites->operator[](index.row());

      if (this->index(index.row(), COL_TYPE_SPECIES).data().toString() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]))
          || !(this->index(index.row(), COL_IEXPRESSION_SPECIES).data().toString().isEmpty()))
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEnabled;
      else
        {
          if (Species.isInitialValueChangeAllowed(CCore::Framework::Concentration))
            return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
          else
            return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled;
        }
    }
  else if (index.column() == COL_INUMBER)
    {
      CMetab & Species = mpMetabolites->operator[](index.row());

      if (this->index(index.row(), COL_TYPE_SPECIES).data() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]))
          || !(this->index(index.row(), COL_IEXPRESSION_SPECIES).data().toString().isEmpty()))
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled;
      else
        {
          if (Species.isInitialValueChangeAllowed(CCore::Framework::ParticleNumbers))
            return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
          else
            return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled;
        }
    }
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQSpecieDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (index.column() > 0 && role == Qt::ForegroundRole && !(flags(index) & Qt::ItemIsEditable))
    return QColor(Qt::darkGray);

  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(QString(""));

              case COL_NAME_SPECIES:
                return QVariant(QString("New Species"));

              case COL_COMPARTMENT:
              {
                const CDataVector < CCompartment > & compartments =
                  pModel->getCompartments();

                if (compartments.size())
                  return QVariant(QString(FROM_UTF8(compartments[0].getObjectName())));
                else
                  return QVariant(QString(""));
              }

              case COL_TYPE_SPECIES:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[0]])));

              case COL_UNIT_SPECIES:
                return QVariant(mUnits[3]); //default to use volume-based

              case COL_ICONCENTRATION:
              {
                if (mFlagConc)
                  return QVariant(convertToQString(1.0));
                else
                  return QVariant(QString(""));
              }

              case COL_INUMBER:
              {
                if (mFlagConc)
                  return QVariant(QString(""));
                else
                  return QVariant(convertToQString(100.0));
              }

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CMetab & Species = mpMetabolites->operator[](index.row());

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_SPECIES:
                return QVariant(QString(FROM_UTF8(Species.getObjectName())));

              case COL_COMPARTMENT:
                return QVariant(QString(FROM_UTF8(Species.getCompartment()->getObjectName())));

              case COL_TYPE_SPECIES:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[Species.getStatus()])));

              case COL_UNIT_SPECIES:
                return QVariant(mUnits[Species.getCompartment()->getDimensionality()]);

              case COL_ICONCENTRATION:
              {
                if (role == Qt::EditRole)
                  return QVariant(convertToQString(Species.getInitialConcentration()));
                else
                  return QVariant(Species.getInitialConcentration());
              }

              case COL_INUMBER:
              {
                if (role == Qt::EditRole)
                  return QVariant(convertToQString(Species.getInitialValue()));
                else
                  return QVariant(Species.getInitialValue());
              }

              case COL_CONCENTRATION:
                return QVariant(Species.getConcentration());

              case COL_NUMBER:
                return QVariant(Species.getValue());

              case COL_CRATE:
                return QVariant(Species.getConcentrationRate());

              case COL_NRATE:
                return QVariant(Species.getRate());

              case COL_IEXPRESSION_SPECIES:
              {
                const CExpression * pExpression = NULL;

                if (Species.getInitialExpression() != "")
                  {
                    pExpression = Species.getInitialExpressionPtr();

                    if (pExpression != NULL)
                      return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                  }

                return QVariant(QString(""));
              }

              case COL_EXPRESSION_SPECIES:
              {
                const CExpression * pExpression = Species.getExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant(QString(""));
              }

#ifdef WITH_SDE_SUPPORT

              case COL_NEXPRESSION_SPECIES:
              {
                const CExpression * pExpression = Species.getNoiseExpressionPtr();

                if (Species.hasNoise() && pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant(QString(""));
              }

#endif
            }
        }
    }

  return QVariant();
}

QVariant CQSpecieDM::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  std::string tmp = CUnit::prettyPrint("1/(" + mpDataModel->getModel()->getTimeUnit() + ")");

  QString ValueUnit = "[Unit]";
  QString RateUnit = (tmp != "?") ? "[Unit" + FROM_UTF8(tmp.substr(1)) + "]" : "[?]";
  QString NRateUnit = (tmp != "?") ? "[#" + FROM_UTF8(tmp.substr(1)) + "]" : "[?]";

  if (orientation == Qt::Horizontal)
    {
      const CModel * pModel = mpDataModel->getModel();

      if (pModel == NULL) return QVariant();

      switch (section)
        {
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));

          case COL_NAME_SPECIES:
            return QVariant(QString("Name"));

          case COL_COMPARTMENT:
            return QVariant(QString("Compartment"));

          case COL_TYPE_SPECIES:
            return QVariant(QString("     Type     "));

          case COL_UNIT_SPECIES:
            return QVariant(QString("Unit"));

          case COL_ICONCENTRATION:
            return QVariant("Initial Concentration\n" + ValueUnit);

          case COL_INUMBER:
            return QVariant(QString("Initial Number"));

          case COL_CONCENTRATION:
            return QVariant("Concentration\n" + ValueUnit);

          case COL_NUMBER:
            return QVariant(QString("Number"));

          case COL_CRATE:
            return QVariant("Rate\n" + RateUnit);

          case COL_NRATE:
            return QVariant("Number Rate\n" + NRateUnit);

          case COL_IEXPRESSION_SPECIES:
            return QVariant("Initial Expression\n" + ValueUnit);

          case COL_EXPRESSION_SPECIES:
            if (ValueUnit == RateUnit)
              return QVariant("Expression\n" + ValueUnit);
            else
              return QVariant("Expression\n" + ValueUnit + " or " + RateUnit);

#ifdef WITH_SDE_SUPPORT

          case COL_NEXPRESSION_SPECIES:
            return QVariant("Noise Expression");
#endif

          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQSpecieDM::setData(const QModelIndex &index, const QVariant &value,
                         int role)
{
  //change is only accepted if the new value is different from the old value and also the old value is not equal to "New Species" for the 'name' column
  // in that case no new species will be created!
  if (index.data() == value)
    return false;

  if (index.column() == COL_TYPE_SPECIES &&
      index.data().toString() == QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
    return false;

  if (index.column() == COL_COMPARTMENT && value == "")
    return false;

  bool defaultRow = isDefaultRow(index);

  if (defaultRow)
    {
      mpUndoStack->push(new InsertSpecieRowsCommand(rowCount(), 1, this, index, value));
    }
  else
    {
      CMetab * Species = &mpMetabolites->operator[](index.row());
      mpUndoStack->push(new SpecieDataChangeCommand(Species, value, index.data(), index.column(), this));
    }

  return true;
}

// virtual
void CQSpecieDM::resetCache()
{
  assert(mpDataModel != NULL);

  mpMetabolites = dynamic_cast< CDataVector < CMetab > * >(&mpDataModel->getModel()->getMetabolites());
  assert(mpMetabolites != NULL);

  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  std::string QuantityUnit = "(" + pModel->getQuantityUnit() + ")";

  mUnits[0] = FROM_UTF8(CUnit::prettyPrint(QuantityUnit));
  mUnits[1] = FROM_UTF8(CUnit::prettyPrint(QuantityUnit + "/(" + pModel->getLengthUnit() + ")"));
  mUnits[2] = FROM_UTF8(CUnit::prettyPrint(QuantityUnit + "/(" + pModel->getAreaUnit() + ")"));
  mUnits[3] = FROM_UTF8(CUnit::prettyPrint(QuantityUnit + "/(" + pModel->getVolumeUnit() + ")"));
}

bool CQSpecieDM::insertRows(int position, int rows, const QModelIndex&)
{
  mpUndoStack->push(new InsertSpecieRowsCommand(position, rows, this));

  return true;
}

bool CQSpecieDM::removeRows(int position, int rows)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  CModel * pModel = mpDataModel->getModel();

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CDataVector< CMetab >::const_iterator itRow = mpMetabolites->begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = itRow->getKey();
    }

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey)
    {
      pModel->removeMetabolite(*itDeletedKey);
      emit notifyGUI(ListViews::METABOLITE, ListViews::DELETE, *itDeletedKey);
      emit notifyGUI(ListViews::METABOLITE, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
    }

  endRemoveRows();

  return true;
}

bool CQSpecieDM::removeRows(QModelIndexList rows, const QModelIndex&index)
{
  removeSpecieRows(rows, index);
  return true;
}

bool CQSpecieDM::specieDataChange(
  UndoSpeciesData *pUndoSpeciesData,
  const QVariant &value,
  int column)
{
  switchToWidget(CCopasiUndoCommand::SPECIES);

  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  CMetab * pSpecies =
    dynamic_cast<CMetab*>(pUndoSpeciesData->getObject(pModel));

  if (pSpecies == NULL)
    return false;

  const CCompartment * pCompartment = NULL;

  if (column == COL_COMPARTMENT ||
      column == COL_ICONCENTRATION ||
      column == COL_INUMBER)
    {
      try
        {
          pCompartment = pSpecies->getCompartment();
        }
      catch (...) {}
    }

  if (column == COL_NAME_SPECIES)
    {
      pSpecies->setObjectName(TO_UTF8(value.toString()));
      pUndoSpeciesData->setCN(pSpecies->getCN());
    }
  else if (column == COL_COMPARTMENT)
    {
      // This must be set first for setInitialConcentration and
      // setInitialNumber to work correctly.
      std::string Compartment(TO_UTF8(value.toString()));

      if (pCompartment != NULL &&
          Compartment != pCompartment->getObjectName())
        {
          CCompartment & NewCompartment = pModel->getCompartments()[Compartment];

          if (!(NewCompartment.addMetabolite(pSpecies)))
            {
              QString msg;
              msg = "Unable to move species '" + FROM_UTF8(pSpecies->getObjectName()) + "'\n"
                    + "from compartment '" + FROM_UTF8(pCompartment->getObjectName()) + "' to compartment '" + FROM_UTF8(Compartment) + "'\n"
                    + "since a species with that name already exist in the target compartment.";

              CQMessageBox::information(NULL,
                                        "Unable to move Species",
                                        msg,
                                        QMessageBox::Ok, QMessageBox::Ok);
              return false;
            }
          else
            {
              const_cast< CCompartment * >(pCompartment)->getMetabolites().remove(pSpecies->getObjectName());
              pModel->setCompileFlag();
              pModel->initializeMetabolites();

              // We need to update the initial value if the framework is concentration
              if (mFlagConc)
                {
                  C_FLOAT64 Factor = NewCompartment.getInitialValue() / pCompartment->getInitialValue();
                  pSpecies->setInitialValue(Factor * pUndoSpeciesData->getINumber());
                  pSpecies->setValue(Factor * pSpecies->getValue());
                }

              emit notifyGUI(ListViews::METABOLITE, ListViews::CHANGE, pSpecies->getKey());
              emit notifyGUI(ListViews::COMPARTMENT, ListViews::CHANGE, pCompartment->getKey());
            }
        }
    }
  else if (column == COL_TYPE_SPECIES)
    pSpecies->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
  else if (column == COL_ICONCENTRATION)
    {
      if (mFlagConc)
        pSpecies->setInitialConcentration(value.toDouble());

      if (pSpecies && pCompartment)
        {
          const C_FLOAT64 initialValue =
            CMetab::convertToNumber(pUndoSpeciesData->getIConc(),
                                    *pCompartment,
                                    *pModel);
          pSpecies->setInitialValue(initialValue);
        }
    }
  else if (column == COL_INUMBER)
    {
      if (!mFlagConc)
        pSpecies->setInitialValue(value.toDouble());

      if (pSpecies && pCompartment)
        {
          pSpecies->setInitialConcentration(
            CMetab::convertToConcentration(pUndoSpeciesData->getINumber(),
                                           *pCompartment,
                                           *pModel)
          );
        }
    }

  //Save Key
  std::string key = pSpecies->getKey();

  // ask for refresh this may change the key!
  QModelIndex index = getIndexFor(pSpecies, column);
  emit dataChanged(index, index);

  if (column == COL_NAME_SPECIES)
    {
      emit notifyGUI(ListViews::METABOLITE, ListViews::RENAME, key);
    }
  else
    {
      emit notifyGUI(ListViews::METABOLITE, ListViews::CHANGE, key);
    }

  return true;
}

QList <UndoSpeciesData *> CQSpecieDM::insertNewSpecieRow(int position, int rows, const QModelIndex&index, const QVariant& value)
{
  QList <UndoSpeciesData *> result;
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  bool createdCompartment = false;

  if (pModel->getCompartments().size() == 0)
    {
      CCompartment* pComp = pModel->createCompartment("compartment");
      createdCompartment = true;

      if (mNotify)
        {
          emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pComp->getKey());
        }
    }

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  int column = index.column();

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(index.isValid() && column == COL_NAME_SPECIES ? value.toString() : "species", COL_NAME_SPECIES);

      QString compartment = index.isValid() && column == COL_COMPARTMENT ? value.toString() : "";

      double initial = index.isValid() && column == COL_ICONCENTRATION ? value.toDouble() : 1.0;

      CModelEntity::Status status = index.isValid() && column == COL_TYPE_SPECIES ?
                                    (CModelEntity::Status) mItemToType[value.toInt()] : CModelEntity::Status::REACTIONS;

      CMetab * pSpecies =
        pModel->createMetabolite(TO_UTF8(name), TO_UTF8(compartment), initial, status);

      if (pSpecies == NULL)
        continue;

      if (mNotify)
        {
          emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, pSpecies->getKey());
        }

      UndoSpeciesData* data = new UndoSpeciesData(pSpecies);
      data->setCreatedCompartment(row == 0 && createdCompartment);
      result.append(data);
    }

  endInsertRows();
  return result;
}

void CQSpecieDM::deleteSpecieRow(UndoSpeciesData *pSpecieData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  switchToWidget(CCopasiUndoCommand::SPECIES);

  CMetab * pSpecies = dynamic_cast< CMetab * >(pSpecieData->getObject(pModel));

  if (pSpecies == NULL) return;

  size_t Index = mpMetabolites->getIndex(pSpecies);

  removeRow((int) Index);

  if (!pSpecieData->getCreatedCompartment()) return;

  Index = pModel->getCompartments().getIndex(pSpecieData->getCompartment());

  if (Index == C_INVALID_INDEX) return;

  CCompartment* pComp = &pModel->getCompartments()[Index];

  if (pComp == NULL) return;

  std::string key = pComp->getKey();
  pModel->removeCompartment(Index);
  emit notifyGUI(ListViews::COMPARTMENT, ListViews::DELETE, key);
}

void CQSpecieDM::addSpecieRow(UndoSpeciesData *pSpecieData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  switchToWidget(CCopasiUndoCommand::SPECIES);

  CDataObject *species =  pSpecieData->restoreObjectIn(pModel);

  if (species == NULL)
    return;

  beginInsertRows(QModelIndex(), 1, 1);
  emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, species->getKey());
  endInsertRows();
}

bool CQSpecieDM::removeSpecieRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  switchToWidget(CCopasiUndoCommand::SPECIES);

  //Build the list of pointers to items to be deleted
  //before actually deleting any item.
  QList <CMetab *> pSpecies;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && &pModel->getMetabolites()[i->row()])
        pSpecies.append(&pModel->getMetabolites()[i->row()]);
    }

  QList <CMetab *>::const_iterator j;

  QModelIndexList lst;

  for (j = pSpecies.begin(); j != pSpecies.end(); ++j)
    {
      CMetab * pSpecie = *j;

      size_t delRow =
        pModel->getMetabolites().CDataVector< CMetab >::getIndex(pSpecie);

      if (delRow == C_INVALID_INDEX)
        continue;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, "species",
                                    FROM_UTF8(pSpecie->getObjectName()),
                                    pSpecie);

      if (choice == QMessageBox::Ok)
        {
          lst.append(index((int)delRow, 0));
          //removeRow((int)delRow);
        }
    }

  if (!lst.empty())
    {
      mpUndoStack->push(new RemoveSpecieRowsCommand(lst, this));
    }

  return true;
}

bool CQSpecieDM::insertSpecieRows(QList <UndoSpeciesData *>& pData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  //reinsert all the species
  QList <UndoSpeciesData *>::const_iterator i;

  for (i = pData.begin(); i != pData.end(); ++i)
    {
      UndoSpeciesData * data = *i;
      CDataObject *pSpecies = data->restoreObjectIn(pModel);

      if (pSpecies == NULL)
        continue;

      if (data->getCreatedCompartment())
        {
          emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, static_cast< CMetab * >(pSpecies)->getCompartment()->getKey());
        }

      beginInsertRows(QModelIndex(), 1, 1);
      emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, pSpecies->getKey());
      endInsertRows();
    }

  switchToWidget(CCopasiUndoCommand::SPECIES);

  return true;
}

void CQSpecieDM::deleteSpecieRows(QList <UndoSpeciesData *>& pData)
{
  switchToWidget(CCopasiUndoCommand::SPECIES);

  QList <UndoSpeciesData *>::const_iterator j;

  for (j = pData.begin(); j != pData.end(); ++j)
    {
      deleteSpecieRow(*j);
    }
}

bool CQSpecieDM::clear()
{
  mpUndoStack->push(new RemoveAllSpecieRowsCommand(this, QModelIndex()));
  return true;
}

QModelIndex CQSpecieDM::getIndexFor(const CMetab *pMetab, int column) const
{
  int max = rowCount();

  CDataVector< CMetab >::const_iterator it = mpDataModel->getModel()->getMetabolites().begin();

  for (int i = 0; i < max; ++i, ++it)
    {
      if (&*it == pMetab)
        return index(i, column);
    }

  return QModelIndex();
}

bool CQSpecieDM::removeAllSpecieRows()
{
  return removeRows(0, rowCount() - 1);
}
