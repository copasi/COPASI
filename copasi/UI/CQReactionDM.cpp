// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtCore/QString>
#include <QtCore/QList>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CChemEqInterface.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"

#include "CQMessageBox.h"
#include "CQReactionDM.h"
#include "qtUtilities.h"

CQReactionDM::CQReactionDM(QObject *parent):
  CQBaseDataModel(parent),
  mNewEquation()
{}

int CQReactionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (int)(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions().size() + 1;
}
int CQReactionDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_REACTIONS;
}

Qt::ItemFlags CQReactionDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_REACTIONS || index.column() == COL_EQUATION)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQReactionDM::data(const QModelIndex &index, int role) const
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

              case COL_NAME_REACTIONS:
                return QVariant(QString("New Reaction"));

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CReaction *pRea = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions()[index.row()];

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_REACTIONS:
                return QVariant(QString(FROM_UTF8(pRea->getObjectName())));

              case COL_EQUATION:

                if (mNewEquation.isEmpty())
                  {
                    return QVariant(QString(FROM_UTF8(CChemEqInterface::getChemEqString((*CCopasiRootContainer::getDatamodelList())[0]->getModel(), *pRea, false))));
                  }
                else
                  {
                    return QVariant(mNewEquation);
                  }

              case COL_RATE_LAW:

                if (pRea->getFunction())
                  return QVariant(QString(FROM_UTF8(pRea->getFunction()->getObjectName())));
                else
                  return QVariant();

              case COL_FLUX:
                return QVariant(pRea->getFlux());

              case COL_PARTICLE_FLUX:
                return QVariant(pRea->getParticleFlux());
            }
        }
    }

  return QVariant();
}

QVariant CQReactionDM::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    {
      switch (section)
        {
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));

          case COL_NAME_REACTIONS:
            return QVariant(QString("Name"));

          case COL_EQUATION:
            return QVariant(QString("Reaction"));

          case COL_RATE_LAW:
            return QVariant(QString("Rate Law"));

          case COL_FLUX:
          {
            const CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

            if (pModel == NULL) return QVariant();

            QString RateUnits;

            if (pModel)
              RateUnits = FROM_UTF8(pModel->getQuantityRateUnitsDisplayString());

            if (!RateUnits.isEmpty())
              RateUnits = "\n(" + RateUnits + ")";

            return QVariant("Flux" + RateUnits);
          }

          case COL_PARTICLE_FLUX:
          {
            const CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

            if (pModel == NULL) return QVariant();

            QString FrequencyUnits;

            if (pModel)
              FrequencyUnits = FROM_UTF8(pModel->getFrequencyUnitsDisplayString());

            if (!FrequencyUnits.isEmpty())
              FrequencyUnits = "\n(" + FrequencyUnits + ")";

            return QVariant("Flux" + FrequencyUnits);
          }

          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQReactionDM::setData(const QModelIndex &index, const QVariant &value,
                           int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.data() != value)
            insertRow();
          else
            return false;
        }

      // this loads the reaction into a CReactionInterface object.
      // the gui works on this object and later writes back the changes to ri;
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CReactionInterface ri((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
      CReaction *pRea = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions()[index.row()];

      if (index.column() == COL_NAME_REACTIONS)
        pRea->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_EQUATION)
        setEquation(pRea, index, value);

      if (defaultRow && this->index(index.row(), COL_NAME_REACTIONS).data().toString() == "reaction")
        pRea->setObjectName(TO_UTF8(createNewName("reaction", COL_NAME_REACTIONS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::REACTION, ListViews::CHANGE, pRea->getKey());
    }

  return true;
}

void CQReactionDM::setEquation(const CReaction *pRea, const QModelIndex& index, const QVariant &value)
{
  std::string objKey = pRea->getKey();
  mNewEquation = value.toString();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to ri;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CReactionInterface ri((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
  ri.initFromReaction(objKey);

  if (TO_UTF8(mNewEquation) != ri.getChemEqString())
    {
      //first check if the string is a valid equation
      if (!CChemEqInterface::isValidEq(TO_UTF8(mNewEquation)))
        {
          mNewEquation = "";
          return;
        }
      else
        {
          //tell the reaction interface
          ri.setChemEqString(TO_UTF8(mNewEquation), "");
        }
    }

  // Before we save any changes we must check whether any local reaction parameters,
  // which are used in any mathematical expression in the model are removed.
  // If that is the case the user must have option to cancel the changes or remove the
  // affected expressions.
  std::set< const CCopasiObject * > DeletedParameters = ri.getDeletedParameters();

  if (DeletedParameters.size() != 0)
    {
      QString ObjectType = "parameter(s) of reaction " + this->index(index.row(), COL_NAME_REACTIONS).data().toString();
      QString Objects;

      std::set< const CCopasiObject * >::const_iterator itParameter, endParameter = DeletedParameters.end();
      std::set< const CCopasiObject * > DeletedObjects;

      for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
        {
          Objects.append(FROM_UTF8((*itParameter)->getObjectName()) + ", ");
          DeletedObjects.insert(static_cast< const CCopasiObject * >((*itParameter)->getObject(CCopasiObjectName("Reference=Value"))));
        }

      Objects.remove(Objects.length() - 2, 2);

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, ObjectType,
                                    Objects, DeletedObjects);

      switch (choice)
        {
          case QMessageBox::Ok:

            for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
              pModel->removeLocalReactionParameter((*itParameter)->getKey());

            break;

          default:
            mNewEquation = "";
            return;
            break;
        }
    }

  // We need to check whether the current reaction still exists, since it is possible that
  // removing a local reaction parameter triggers its deletion.
  CReaction * reac = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(objKey));

  if (reac == NULL)
    {
      ri.setFunctionWithEmptyMapping("");
      emit notifyGUI(ListViews::REACTION, ListViews::DELETE, objKey);
      emit notifyGUI(ListViews::REACTION, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
      mNewEquation = "";
      return;
    }

  //first check if new metabolites need to be created
  bool createdMetabs = ri.createMetabolites();
  bool createdObjects = ri.createOtherObjects();
  //this writes all changes to the reaction
  ri.writeBackToReaction(NULL);

  //(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->compile();
  //this tells the gui what it needs to know.
  if (createdObjects ||
      DeletedParameters.size() != 0)
    {
      emit notifyGUI(ListViews::MODEL, ListViews::CHANGE, "");
    }
  else if (createdMetabs)
    {
      emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, "");
    }

  mNewEquation = "";
}

bool CQReactionDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CReaction *pRea = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createReaction(TO_UTF8(createNewName("reaction", COL_NAME_REACTIONS)));
      emit notifyGUI(ListViews::REACTION, ListViews::ADD, pRea->getKey());
    }

  endInsertRows();

  return true;
}

bool CQReactionDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CCopasiVector< CReaction >::const_iterator itRow = pModel->getReactions().begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = (*itRow)->getKey();
    }

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey)
    {
      pModel->removeReaction(*itDeletedKey);
      emit notifyGUI(ListViews::REACTION, ListViews::DELETE, *itDeletedKey);
      emit notifyGUI(ListViews::REACTION, ListViews::DELETE, "");//Refresh all as there may be dependencies.
    }

  endRemoveRows();

  return true;
}

bool CQReactionDM::removeRows(QModelIndexList rows, const QModelIndex&)
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
  QList <CReaction *> pReactions;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pModel->getReactions()[(*i).row()])
        pReactions.append(pModel->getReactions()[(*i).row()]);
    }

  QList <CReaction *>::const_iterator j;

  for (j = pReactions.begin(); j != pReactions.end(); ++j)
    {
      CReaction * pReaction = *j;

      size_t delRow =
        pModel->getReactions().CCopasiVector< CReaction >::getIndex(pReaction);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "reaction",
                                        FROM_UTF8(pReaction->getObjectName()),
                                        pReaction->getDeletedObjects());

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}
