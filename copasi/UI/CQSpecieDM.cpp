// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtCore/QString>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CChemEqInterface.h"
#include "function/CExpression.h"

#include "CQMessageBox.h"
#include "CQSpecieDM.h"
#include "qtUtilities.h"

#ifdef COPASI_UNDO
#include "model/CReaction.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "undoFramework/InsertSpecieRowsCommand.h"
#include "undoFramework/RemoveSpecieRowsCommand.h"
#include "undoFramework/RemoveAllSpecieRowsCommand.h"
#include "undoFramework/SpecieDataChangeCommand.h"
#include "undoFramework/UndoSpecieData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoEventAssignmentData.h"
#endif

CQSpecieDM::CQSpecieDM(QObject *parent):
  CQBaseDataModel(parent),
  mFlagConc(true),
  mpSpecies(NULL),
  mNotify(true)
{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::REACTIONS]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::REACTIONS);
  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
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

int CQSpecieDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (int)(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getMetabolites().size() + 1;
}

int CQSpecieDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
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
      mpSpecies = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getMetabolites()[index.row()];

      if (this->index(index.row(), COL_TYPE_SPECIES).data().toString() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]))
          || !(this->index(index.row(), COL_IEXPRESSION_SPECIES).data().toString().isEmpty()))
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEnabled;
      else
        {
          if (mpSpecies->isInitialConcentrationChangeAllowed())
            return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
          else
            return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled;
        }
    }
  else if (index.column() == COL_INUMBER)
    {
      if (this->index(index.row(), COL_TYPE_SPECIES).data() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]))
          || !(this->index(index.row(), COL_IEXPRESSION_SPECIES).data().toString().isEmpty()))
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable & ~Qt::ItemIsEnabled;
      else
        return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
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
                const CCopasiVector < CCompartment > & compartments =
                  (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments();

                if (compartments.size())
                  return QVariant(QString(FROM_UTF8(compartments[0]->getObjectName())));
                else
                  return QVariant(QString(""));
              }

              case COL_TYPE_SPECIES:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[0]])));

              case COL_ICONCENTRATION:
              {
                if (mFlagConc)
                  return QVariant(QString::number(1.0, 'g', 10));
                else
                  return QVariant(QString(""));
              }

              case COL_INUMBER:
              {
                if (mFlagConc)
                  return QVariant(QString(""));
                else
                  return QVariant(QString::number(100.0, 'g', 10));
              }

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          mpSpecies = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getMetabolites()[index.row()];

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_SPECIES:
                return QVariant(QString(FROM_UTF8(mpSpecies->getObjectName())));

              case COL_COMPARTMENT:
                return QVariant(QString(FROM_UTF8(mpSpecies->getCompartment()->getObjectName())));

              case COL_TYPE_SPECIES:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[mpSpecies->getStatus()])));

              case COL_ICONCENTRATION:
              {
                if (role == Qt::EditRole)
                  return QVariant(QString::number(mpSpecies->getInitialConcentration(), 'g', 10));
                else
                  return QVariant(mpSpecies->getInitialConcentration());
              }

              case COL_INUMBER:
              {
                if (role == Qt::EditRole)
                  return QVariant(QString::number(mpSpecies->getInitialValue(), 'g', 10));
                else
                  return QVariant(mpSpecies->getInitialValue());
              }

              case COL_CONCENTRATION:
                return QVariant(mpSpecies->getConcentration());

              case COL_NUMBER:
                return QVariant(mpSpecies->getValue());

              case COL_CRATE:
                return QVariant(mpSpecies->getConcentrationRate());

              case COL_NRATE:
                return QVariant(mpSpecies->getRate());

              case COL_IEXPRESSION_SPECIES:
              {
                const CExpression * pExpression = NULL;

                if (mpSpecies->getInitialExpression() != "")
                  {
                    pExpression = mpSpecies->getInitialExpressionPtr();

                    if (pExpression != NULL)
                      return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                  }

                return QVariant(QString(""));
              }

              case COL_EXPRESSION_SPECIES:
              {
                const CExpression * pExpression = mpSpecies->getExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant(QString(""));
              }
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

  if (orientation == Qt::Horizontal)
    {
      const CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

      if (pModel == NULL) return QVariant();

      QString ValueUnits, RateUnits, FrequencyUnits, ExpressionUnits;

      if (pModel)
        ValueUnits = FROM_UTF8(pModel->getConcentrationUnitsDisplayString());

      if (!ValueUnits.isEmpty())
        ValueUnits = "\n(" + ValueUnits + ")";

      if (pModel)
        RateUnits = FROM_UTF8(pModel->getConcentrationRateUnitsDisplayString());

      if (!RateUnits.isEmpty())
        RateUnits = "\n(" + RateUnits + ")";

      if (pModel)
        FrequencyUnits = FROM_UTF8(pModel->getFrequencyUnitsDisplayString());

      if (!FrequencyUnits.isEmpty())
        FrequencyUnits = "\n(" + FrequencyUnits + ")";

      if (!ValueUnits.isEmpty() && !RateUnits.isEmpty())
        {
          if (ValueUnits == RateUnits)
            ExpressionUnits = ValueUnits;
          else
            ExpressionUnits = "\n(" + FROM_UTF8(pModel->getConcentrationUnitsDisplayString())
                              + " or " + FROM_UTF8(pModel->getConcentrationRateUnitsDisplayString()) + ")";
        }
      else if (!ValueUnits.isEmpty())
        ExpressionUnits = "\n(" + FROM_UTF8(pModel->getConcentrationUnitsDisplayString()) + " or 1)";
      else if (!RateUnits.isEmpty())
        ExpressionUnits = "\n(1 or " + FROM_UTF8(pModel->getConcentrationRateUnitsDisplayString()) + ")";

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

          case COL_ICONCENTRATION:
            return QVariant("Initial Concentration" + ValueUnits);

          case COL_INUMBER:
            return QVariant(QString("Initial Number"));

          case COL_CONCENTRATION:
            return QVariant("Concentration" + ValueUnits);

          case COL_NUMBER:
            return QVariant(QString("Number"));

          case COL_CRATE:
            return QVariant("Rate" + RateUnits);

          case COL_NRATE:
            return QVariant("Number Rate" + FrequencyUnits);

          case COL_IEXPRESSION_SPECIES:
            return QVariant("Initial Expression" + ValueUnits);

          case COL_EXPRESSION_SPECIES:
            return QVariant("Expression" + ExpressionUnits);

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
#ifdef COPASI_UNDO

  //change is only accepted if the new value is different from the old value and also the old value is not equal to "New Species" for the 'name' column
  if (index.data() == value || index.data() == "New Species")
    return false;
  else
    mpUndoStack->push(new SpecieDataChangeCommand(index, value, role, this));

#else

  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.column() == COL_TYPE_SPECIES)
            {
              if (index.data().toString() == QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
                return false;
            }
          else if (index.column() == COL_COMPARTMENT && value == "")
            {
              return false;
            }
          else if (index.data() == value)
            {
              return false;
            }

          mNotify = false;
          insertRow();
          mNotify = true;
        }
      else
        {
          assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
          mpSpecies = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getMetabolites()[index.row()];
        }

      const CCompartment * pCompartment = NULL;

      if (index.column() == COL_COMPARTMENT ||
          index.column() == COL_ICONCENTRATION ||
          index.column() == COL_INUMBER)
        {
          try
            {
              pCompartment = mpSpecies->getCompartment();
            }
          catch (...) {}
        }

      if (index.column() == COL_NAME_SPECIES)
        mpSpecies->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_COMPARTMENT)
        {
          // This must be set first for setInitialConcentration and
          // setInitialNumber to work correctly.
          std::string Compartment(TO_UTF8(value.toString()));

          if (Compartment != pCompartment->getObjectName())
            {
              std::string CompartmentToRemove = mpSpecies->getCompartment()->getObjectName();
              assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

              if (!(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[Compartment]->addMetabolite(mpSpecies))
                {
                  QString msg;
                  msg = "Unable to move species '" + FROM_UTF8(mpSpecies->getObjectName()) + "'\n"
                        + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + FROM_UTF8(Compartment) + "'\n"
                        + "since a species with that name already exist in the target compartment.";

                  CQMessageBox::information(NULL,
                                            "Unable to move Species",
                                            msg,
                                            QMessageBox::Ok, QMessageBox::Ok);
                  return false;
                }
              else
                {
                  (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(mpSpecies->getObjectName());
                  (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->setCompileFlag();
                  (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->initializeMetabolites();

                  if (mpSpecies && pCompartment)
                    {
                      C_FLOAT64 Factor = 1.0 / pCompartment->getInitialValue();
                      Factor *= pCompartment->getInitialValue();

                      mpSpecies->setInitialValue(Factor * this->index(index.row(), COL_INUMBER).data().toDouble());
                      mpSpecies->setValue(Factor * this->index(index.row(), COL_NUMBER).data().toDouble());
                    }

                  emit notifyGUI(ListViews::METABOLITE, ListViews::CHANGE, mpSpecies->getKey());
                  emit notifyGUI(ListViews::COMPARTMENT, ListViews::CHANGE, pCompartment->getKey());
                }
            }
        }
      else if (index.column() == COL_TYPE_SPECIES)
        mpSpecies->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
      else if (index.column() == COL_ICONCENTRATION)
        {
          if (mFlagConc)
            mpSpecies->setInitialConcentration(value.toDouble());

          if (mpSpecies && pCompartment)
            {
              const C_FLOAT64 initialValue =
                CMetab::convertToNumber(this->index(index.row(), COL_ICONCENTRATION).data().toDouble(),
                                        *pCompartment,
                                        *(*CCopasiRootContainer::getDatamodelList())[0]->getModel());
              mpSpecies->setInitialValue(initialValue);
            }
        }
      else if (index.column() == COL_INUMBER)
        {
          if (!mFlagConc)
            mpSpecies->setInitialValue(value.toDouble());

          if (mpSpecies && pCompartment)
            {
              mpSpecies->setInitialConcentration(
                CMetab::convertToConcentration(this->index(index.row(), COL_INUMBER).data().toDouble(),
                                               *pCompartment,
                                               *(*CCopasiRootContainer::getDatamodelList())[0]->getModel())
              );
            }
        }

      if (defaultRow && this->index(index.row(), COL_NAME_SPECIES).data().toString() == "species")
        mpSpecies->setObjectName(TO_UTF8(createNewName("species", COL_NAME_SPECIES)));

      //Save Key
      std::string key = mpSpecies->getKey();
      emit dataChanged(index, index);

      if (defaultRow)
        {
          emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, key);
        }
      else
        {
          emit notifyGUI(ListViews::METABOLITE, ListViews::CHANGE, key);
        }
    }

#endif

  return true;
}

bool CQSpecieDM::insertRows(int position, int rows, const QModelIndex&)
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new InsertSpecieRowsCommand(position, rows, this, QModelIndex()));
#else
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];

  if (pDataModel->getModel()->getCompartments().size() == 0)
    {
      pDataModel->getModel()->createCompartment("compartment");
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pDataModel->getModel()->getCompartments()[0]->getKey());
    }

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpSpecies =
        pDataModel->getModel()->createMetabolite(TO_UTF8(createNewName("species", COL_NAME_SPECIES)), "", 1.0, CModelEntity::REACTIONS);

      if (mNotify)
        {
          emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, mpSpecies->getKey());
        }
    }

  endInsertRows();

#endif

  return true;
}

bool CQSpecieDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CCopasiVector< CMetab >::const_iterator itRow = pModel->getMetabolites().begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = (*itRow)->getKey();
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

bool CQSpecieDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new RemoveSpecieRowsCommand(rows, this, QModelIndex()));
#else

  if (rows.isEmpty())
    return false;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CMetab *> pSpecies;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pModel->getMetabolites()[(*i).row()])
        pSpecies.append(pModel->getMetabolites()[(*i).row()]);
    }

  QList <CMetab *>::const_iterator j;

  for (j = pSpecies.begin(); j != pSpecies.end(); ++j)
    {
      CMetab * pSpecie = *j;

      size_t delRow =
        pModel->getMetabolites().CCopasiVector< CMetab >::getIndex(pSpecie);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "species",
                                        FROM_UTF8(pSpecie->getObjectName()),
                                        pSpecie->getDeletedObjects());

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

#endif

  return true;
}

#ifdef COPASI_UNDO

bool CQSpecieDM::specieDataChange(const QModelIndex &index, const QVariant &value, int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.column() == COL_TYPE_SPECIES)
            {
              if (index.data().toString() == QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
                return false;
            }
          else if (index.column() == COL_COMPARTMENT && value == "")
            {
              return false;
            }
          else if (index.data() == value)
            {
              return false;
            }

          mNotify = false;

          insertRow();
          mNotify = true;
        }
      else
        {
          assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
          mpSpecies = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getMetabolites()[index.row()];
        }

      const CCompartment * pCompartment = NULL;

      if (index.column() == COL_COMPARTMENT ||
          index.column() == COL_ICONCENTRATION ||
          index.column() == COL_INUMBER)
        {
          try
            {
              pCompartment = mpSpecies->getCompartment();
            }
          catch (...) {}
        }

      if (index.column() == COL_NAME_SPECIES)
        mpSpecies->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_COMPARTMENT)
        {
          // This must be set first for setInitialConcentration and
          // setInitialNumber to work correctly.
          std::string Compartment(TO_UTF8(value.toString()));

          if (Compartment != pCompartment->getObjectName())
            {
              std::string CompartmentToRemove = mpSpecies->getCompartment()->getObjectName();
              assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

              if (!(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[Compartment]->addMetabolite(mpSpecies))
                {
                  QString msg;
                  msg = "Unable to move species '" + FROM_UTF8(mpSpecies->getObjectName()) + "'\n"
                        + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + FROM_UTF8(Compartment) + "'\n"
                        + "since a species with that name already exist in the target compartment.";

                  CQMessageBox::information(NULL,
                                            "Unable to move Species",
                                            msg,
                                            QMessageBox::Ok, QMessageBox::Ok);
                  return false;
                }
              else
                {
                  (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(mpSpecies->getObjectName());
                  (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->setCompileFlag();
                  (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->initializeMetabolites();

                  if (mpSpecies && pCompartment)
                    {
                      C_FLOAT64 Factor = 1.0 / pCompartment->getInitialValue();
                      Factor *= pCompartment->getInitialValue();

                      mpSpecies->setInitialValue(Factor * this->index(index.row(), COL_INUMBER).data().toDouble());
                      mpSpecies->setValue(Factor * this->index(index.row(), COL_NUMBER).data().toDouble());
                    }

                  emit notifyGUI(ListViews::METABOLITE, ListViews::CHANGE, mpSpecies->getKey());
                  emit notifyGUI(ListViews::COMPARTMENT, ListViews::CHANGE, pCompartment->getKey());
                }
            }
        }
      else if (index.column() == COL_TYPE_SPECIES)
        mpSpecies->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
      else if (index.column() == COL_ICONCENTRATION)
        {
          if (mFlagConc)
            mpSpecies->setInitialConcentration(value.toDouble());

          if (mpSpecies && pCompartment)
            {
              const C_FLOAT64 initialValue =
                CMetab::convertToNumber(this->index(index.row(), COL_ICONCENTRATION).data().toDouble(),
                                        *pCompartment,
                                        *(*CCopasiRootContainer::getDatamodelList())[0]->getModel());
              mpSpecies->setInitialValue(initialValue);
            }
        }
      else if (index.column() == COL_INUMBER)
        {
          if (!mFlagConc)
            mpSpecies->setInitialValue(value.toDouble());

          if (mpSpecies && pCompartment)
            {
              mpSpecies->setInitialConcentration(
                CMetab::convertToConcentration(this->index(index.row(), COL_INUMBER).data().toDouble(),
                                               *pCompartment,
                                               *(*CCopasiRootContainer::getDatamodelList())[0]->getModel())
              );
            }
        }

      if (defaultRow && this->index(index.row(), COL_NAME_SPECIES).data().toString() == "species")
        mpSpecies->setObjectName(TO_UTF8(createNewName("species", COL_NAME_SPECIES)));

      //Save Key
      std::string key = mpSpecies->getKey();
      emit dataChanged(index, index);

      if (defaultRow)
        {

          emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, key);
        }
      else
        {
          emit notifyGUI(ListViews::METABOLITE, ListViews::CHANGE, key);
        }
    }

  emit changeWidget(112);

  return true;
}

void CQSpecieDM::insertNewSpecieRow(int position, int rows, const QModelIndex&)
{
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];

  if (pDataModel->getModel()->getCompartments().size() == 0)
    {
      pDataModel->getModel()->createCompartment("compartment");
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pDataModel->getModel()->getCompartments()[0]->getKey());
    }

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpSpecies =
        pDataModel->getModel()->createMetabolite(TO_UTF8(createNewName("species", COL_NAME_SPECIES)), "", 1.0, CModelEntity::REACTIONS);

      if (mNotify)
        {
          emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, mpSpecies->getKey());
        }
    }

  endInsertRows();
}

void CQSpecieDM::deleteSpecieRow(UndoSpecieData *pSpecieData)
{
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  size_t index = pModel->findMetabByName(pSpecieData->getName());
  removeRow((int) index);
  emit changeWidget(112);
}

void CQSpecieDM::addSpecieRow(UndoSpecieData *pSpecieData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  beginInsertRows(QModelIndex(), 1, 1);
  CMetab *specie = pDataModel->getModel()->createMetabolite(pSpecieData->getName(), pSpecieData->getCompartment(), pSpecieData->getIConc(), CModelEntity::REACTIONS);
  std::string key = specie->getKey();
  emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, key);
  endInsertRows();
}

bool CQSpecieDM::removeSpecieRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CMetab *> pSpecies;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pModel->getMetabolites()[(*i).row()])
        pSpecies.append(pModel->getMetabolites()[(*i).row()]);
    }

  QList <CMetab *>::const_iterator j;

  for (j = pSpecies.begin(); j != pSpecies.end(); ++j)
    {
      CMetab * pSpecie = *j;

      size_t delRow =
        pModel->getMetabolites().CCopasiVector< CMetab >::getIndex(pSpecie);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "species",
                                        FROM_UTF8(pSpecie->getObjectName()),
                                        pSpecie->getDeletedObjects());

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  emit changeWidget(112);

  return true;
}

bool CQSpecieDM::insertSpecieRows(QList <UndoSpecieData *> pData)
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return false;

  //reinsert all the species
  QList <UndoSpecieData *>::const_iterator i;

  for (i = pData.begin(); i != pData.end(); ++i)
    {
      UndoSpecieData * data = *i;
      CCompartment * pCompartment = pModel->getCompartments()[data->getCompartment()];

      if (pCompartment->getMetabolites().getIndex(data->getName()) == C_INVALID_INDEX)
        {
          beginInsertRows(QModelIndex(), 1, 1);

          CMetab *pSpecie =  pModel->createMetabolite(data->getName(), data->getCompartment(), 1.0, data->getStatus());

          if (data->getStatus() != CModelEntity::ASSIGNMENT)
            {
              pSpecie->setInitialConcentration(data->getIConc());
            }

          if (data->getStatus() == CModelEntity::ODE || data->getStatus() == CModelEntity::ASSIGNMENT)
            {
              pSpecie->setExpression(data->getExpression());
              pSpecie->getExpressionPtr()->compile();
            }

          // set initial expression
          if (data->getStatus() != CModelEntity::ASSIGNMENT)
            {
              pSpecie->setInitialExpression(data->getInitialExpression());
              pSpecie->getInitialExpressionPtr()->compile();
            }

          emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, pSpecie->getKey());
          endInsertRows();
        }
    }

  //restore the reactions
  QList <UndoSpecieData *>::const_iterator k;

  for (k = pData.begin(); k != pData.end(); ++k)
    {
      UndoSpecieData * data = *k;

      //reinsert the dependency global quantity
      QList <UndoGlobalQuantityData *> *pGlobalQuantityData = data->getGlobalQuantityDependencyObjects();

      if (!pGlobalQuantityData->empty())
        {
          QList <UndoGlobalQuantityData *>::const_iterator g;

          for (g = pGlobalQuantityData->begin(); g != pGlobalQuantityData->end(); ++g)
            {
              UndoGlobalQuantityData * gData = *g;

              if (pModel->getModelValues().getIndex(gData->getName()) == C_INVALID_INDEX)
                {
                  CModelValue *pGlobalQuantity =  pModel->createModelValue(gData->getName()); //, gData->getInitialValue());

                  if (pGlobalQuantity)
                    {
                      pGlobalQuantity->setStatus(gData->getStatus());

                      if (gData->getStatus() != CModelEntity::ASSIGNMENT)
                        {
                          pGlobalQuantity->setInitialValue(gData->getInitialValue());
                        }

                      if (gData->getStatus() != CModelEntity::FIXED)
                        {
                          pGlobalQuantity->setExpression(gData->getExpression());
                          pGlobalQuantity->getExpressionPtr()->compile();
                        }

                      // set initial expression
                      if (gData->getStatus() != CModelEntity::ASSIGNMENT)
                        {
                          pGlobalQuantity->setInitialExpression(gData->getInitialExpression());
                          pGlobalQuantity->getInitialExpressionPtr()->compile();
                        }

                      emit notifyGUI(ListViews::MODELVALUE, ListViews::ADD, pGlobalQuantity->getKey());
                    }
                }
            }
        }

      QList <UndoReactionData *> *reactionData = data->getReactionDependencyObjects();

      if (!reactionData->empty())
        {
          QList <UndoReactionData *>::const_iterator j;

          for (j = reactionData->begin(); j != reactionData->end(); ++j)
            {

              UndoReactionData * rData = *j;

              //need to make sure reaction doesn't exist in the model already
              if (pModel->getReactions().getIndex(rData->getName()) == C_INVALID_INDEX)
                {
                  CReaction *pRea =  pModel->createReaction(rData->getName());
                  CChemEqInterface *chem = new CChemEqInterface(pModel);
                  chem->setChemEqString(rData->getRi()->getChemEqString());
                  chem->writeToChemEq(pRea->getChemEq());
                  rData->getRi()->createMetabolites();
                  rData->getRi()->createOtherObjects();
                  rData->getRi()->writeBackToReaction(pRea);
                  //std::string name = rData->getRi()->getFunctionName();
                  //pRea->setFunction((const)rData->getRi()->getFunction());

                  emit notifyGUI(ListViews::REACTION, ListViews::ADD, pRea->getKey());
                  //  endInsertRows();
                }
            }
        }

      //reinsert the dependency events
      QList <UndoEventData *> *pEventData = data->getEventDependencyObjects();

      if (!pEventData->empty())
        {
          QList <UndoEventData *>::const_iterator ev;

          for (ev = pEventData->begin(); ev != pEventData->end(); ++ev)
            {
              UndoEventData * eData = *ev;

              if (pModel->getEvents().getIndex(eData->getName()) == C_INVALID_INDEX)
                {
                  CEvent *pEvent =  pModel->createEvent(eData->getName());

                  if (pEvent)
                    {
                      std::string key = pEvent->getKey();
                      //set the expressions
                      pEvent->setTriggerExpression(eData->getTriggerExpression());
                      pEvent->setDelayExpression(eData->getDelayExpression());
                      pEvent->setPriorityExpression(eData->getPriorityExpression());

                      QList <UndoEventAssignmentData *> *assignmentData = eData->getEventAssignmentData();
                      QList <UndoEventAssignmentData *>::const_iterator i;

                      for (i = assignmentData->begin(); i != assignmentData->end(); ++i)
                        {
                          UndoEventAssignmentData * assignData = *i;

                          if (pEvent->getAssignments().getIndex(assignData->getTargetKey()) == C_INVALID_INDEX)
                            {
                              CEventAssignment *eventAssign = new CEventAssignment(assignData->getTargetKey(), pEvent->getObjectParent());
                              eventAssign->setExpression(assignData->getExpression());
                              eventAssign->getExpressionPtr()->compile();
                              pEvent->getAssignments().add(eventAssign);
                            }
                        }

                      emit notifyGUI(ListViews::EVENT, ListViews::ADD, key);
                    }
                }
            }
        }
    }

  emit changeWidget(112);

  return true;
}

void CQSpecieDM::deleteSpecieRows(QList <UndoSpecieData *> pData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  QList <UndoSpecieData *>::const_iterator j;

  for (j = pData.begin(); j != pData.end(); ++j)
    {
      UndoSpecieData * data = *j;

      size_t index = pModel->findMetabByName(data->getName());
      removeRow((int) index);
    }

  emit changeWidget(112);
}

bool CQSpecieDM::clear()
{
  mpUndoStack->push(new RemoveAllSpecieRowsCommand(this, QModelIndex()));
  return true;
}

bool CQSpecieDM::removeAllSpecieRows()
{
  return removeRows(0, rowCount() - 1);
}
#endif
