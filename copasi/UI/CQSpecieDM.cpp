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
#include "copasi/undo/CUndoData.h"

CQSpecieDM::CQSpecieDM(QObject *parent):
  CQBaseDataModel(parent, NULL),
  mpMetabolites(NULL),
  mNotify(true)
{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::REACTIONS]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));

  mUnits.append("?");
  mUnits.append("?");
  mUnits.append("?");
  mUnits.append("?");
}

const QStringList& CQSpecieDM::getTypes()
{
  return mTypes;
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
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::REACTIONS])));

              case COL_UNIT_SPECIES:
                return QVariant(mUnits[3]); //default to use volume-based

              case COL_ICONCENTRATION:
                switch (mFramework)
                  {
                    case 0:
                      return QVariant(convertToQString(1.0));
                      break;

                    case 1:
                      return QVariant(QString(""));
                      break;
                  }

                break;

              case COL_INUMBER:
                switch (mFramework)
                  {
                    case 0:
                      return QVariant(QString(""));
                      break;

                    case 1:
                      return QVariant(convertToQString(100.0));
                      break;
                  }

                break;

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

  if (index.column() == COL_COMPARTMENT && value == "")
    return false;

  if (isDefaultRow(index))
    {
      insertNewRows(rowCount(), 1, index.column(), value);
    }
  else if (role == Qt::EditRole)
    {
      CMetab & Species = mpMetabolites->operator[](index.row());
      CData OldData(Species.toData());

      switch (index.column())
        {
          case COL_NAME_SPECIES:
            if (static_cast< CDataVectorN< CMetab > *>(Species.getObjectParent())->getIndex(TO_UTF8(value.toString())) == C_INVALID_INDEX)
              {
                Species.setObjectName(TO_UTF8(value.toString()));
              }

            break;

          case COL_COMPARTMENT:
          {
            CModel * pModel = mpDataModel->getModel();
            CCompartment & Compartment = pModel->getCompartments()[TO_UTF8(value.toString())];

            if (Compartment.getMetabolites().getIndex(Species.getObjectName()) == C_INVALID_INDEX)
              {
                Species.setObjectParent(&Compartment.getMetabolites());
              }
          }
          break;

          case COL_TYPE_SPECIES:
            Species.setStatus(CModelEntity::StatusName.toEnum(TO_UTF8(value.toString())));
            break;

          case COL_INUMBER:
            Species.setInitialValue(value.toDouble());
            Species.setInitialConcentration(CMetab::convertToConcentration(value.toDouble(), *Species.getCompartment()));
            break;

          case COL_ICONCENTRATION:
            Species.setInitialConcentration(value.toDouble());
            Species.setInitialValue(CMetab::convertToNumber(value.toDouble(), *Species.getCompartment()));
            break;
        }

      CUndoData UndoData;
      Species.createUndoData(UndoData, CUndoData::Type::CHANGE, OldData);

      if (!UndoData.empty())
        {
          emit signalNotifyChanges(mpDataModel->recordData(UndoData));
        }
    }

  return true;
}

// virtual
void CQSpecieDM::resetCacheProtected()
{
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

bool CQSpecieDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  insertNewRows(position, rows);

  return true;
}

bool CQSpecieDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, position + rows - 1);

  std::vector< const CMetab * > ToBeDeleted;
  ToBeDeleted.resize(rows);

  std::vector< const CMetab * >::iterator it = ToBeDeleted.begin();
  std::vector< const CMetab * >::iterator end = ToBeDeleted.end();

  CDataVector< CMetab >::const_iterator itRow = mpMetabolites->begin() + position;

  for (; it != end; ++it, ++itRow)
    {
      *it = &*itRow;
    }

  for (it = ToBeDeleted.begin(); it != end; ++it)
    {
      CUndoData UndoData;
      (*it)->createUndoData(UndoData, CUndoData::Type::REMOVE);

      emit signalNotifyChanges(mpDataModel->applyData(UndoData));
    }

  endRemoveRows();

  return true;
}

void CQSpecieDM::insertNewRows(int position, int rows, int column, const QVariant & value)
{
  CModel * pModel = mpDataModel->getModel();

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CCompartment * pComp = NULL;

      if (pModel->getCompartments().size() == 0)
        {
          pComp = pModel->createCompartment("compartment");
        }

      QString name = createNewName(column == COL_NAME_SPECIES ? value.toString() : "species", COL_NAME_SPECIES);

      QString compartment = column == COL_COMPARTMENT ? value.toString() : "";

      double initial = column == COL_ICONCENTRATION ? value.toDouble() : 1.0;

      CModelEntity::Status status = column == COL_TYPE_SPECIES ?
                                    CModelEntity::StatusName.toEnum(TO_UTF8(value.toString())) : CModelEntity::Status::REACTIONS;

      CMetab * pSpecies =
        pModel->createMetabolite(TO_UTF8(name), TO_UTF8(compartment), initial, status);

      if (pSpecies == NULL)
        {
          if (pComp != NULL)
            {
              delete pComp;
            }

          continue;
        }

      CUndoData Data(CUndoData::Type::INSERT, pSpecies);

      if (pComp != NULL)
        {
          Data.addPreProcessData(CUndoData(CUndoData::Type::INSERT, pComp));
        }

      emit signalNotifyChanges(mpDataModel->recordData(Data));
    }

  endInsertRows();
}

bool CQSpecieDM::removeRows(QModelIndexList rows, const QModelIndex & parent)
{
  if (rows.isEmpty())
    return false;

  //Build the list of pointers to items to be deleted
  //before actually deleting any item.
  QList <CMetab *> Species;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) &&
          &mpMetabolites->operator[](i->row()) != NULL)
        Species.append(&mpMetabolites->operator[](i->row()));
    }

  QList< CMetab * >::const_iterator j;

  for (j = Species.begin(); j != Species.end(); ++j)
    {
      CMetab * pSpecies = *j;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, "species",
                                    FROM_UTF8(pSpecies->getObjectName()),
                                    pSpecies);

      if (choice == QMessageBox::Ok)
        {
          removeRows(mpMetabolites->getIndex(pSpecies), 1);
        }
    }

  return true;
}

bool CQSpecieDM::clear()
{
  QModelIndexList rows;

  for (int i = 0; i < mpMetabolites->size(); i++)
    {
      rows.append(index(i, 0));
    }

  return removeRows(rows);
}
