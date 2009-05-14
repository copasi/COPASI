// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionDM.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/05/14 18:48:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QString>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CChemEqInterface.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"

#include "CQMessageBox.h"
#include "CQReactionDM.h"
#include "qtUtilities.h"

CQReactionDM::CQReactionDM(QObject *parent)
    : CQBaseDataModel(parent)

{
}

int CQReactionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions().size() + 1;
}
int CQReactionDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_REACTIONS;
}

Qt::ItemFlags CQReactionDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME || index.column() == COL_EQUATION)
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

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);
              case COL_NAME:
                return QVariant(QString("No Name"));
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

              case COL_NAME:
                return QVariant(QString(FROM_UTF8(pRea->getObjectName())));

              case COL_EQUATION:
                return QVariant(QString(FROM_UTF8(CChemEqInterface::getChemEqString((*CCopasiRootContainer::getDatamodelList())[0]->getModel(), *pRea, false))));

              case COL_RATE_LAW:

                if (pRea->getFunction())
                  return QVariant(QString(FROM_UTF8(pRea->getFunction()->getObjectName())));

              case COL_FLUX:
                return QVariant(QString::number(pRea->getFlux()));

              case COL_PARTICLE_FLUX:
                return QVariant(QString::number(pRea->getParticleFlux()));
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
          case COL_NAME:
            return QVariant(QString("Name"));
          case COL_EQUATION:
            return QVariant(QString("Equation"));
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

      if (index.column() == COL_NAME)
        pRea->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_EQUATION)
        setEquation(pRea, index, value);

      if (defaultRow && this->index(index.row(), COL_NAME).data().toString() == "No Name")
        pRea->setObjectName(TO_UTF8(createNewName("Reaction", COL_NAME)));

      emit dataChanged(index, index);
    }

  return true;
}

void CQReactionDM::setEquation(const CReaction *pRea, const QModelIndex& index, const QVariant &value)
{
  std::string objKey = pRea->getKey();
  QString equation = value.toString();

  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel == NULL) return;

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to ri;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CReactionInterface ri((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
  ri.initFromReaction(objKey);

  if (TO_UTF8(equation) != ri.getChemEqString())
    {
      //first check if the string is a valid equation
      if (!CChemEqInterface::isValidEq(TO_UTF8(equation)))
        {
          return;
        }
      else
        {
          //tell the reaction interface
          ri.setChemEqString(TO_UTF8(equation), "");
        }
    }

  // Before we save any changes we must check whether any local reaction parameters,
  // which are used in any mathematical expression in the model are removed.
  // If that is the case the user must have option to cancel the changes or remove the
  // affected expressions.
  std::set< const CCopasiObject * > DeletedParameters = ri.getDeletedParameters();

  if (DeletedParameters.size() != 0)
    {
      QString ObjectType = "parameter(s) of reaction " + this->index(index.row(), COL_NAME).data().toString();
      QString Objects;

      std::set< const CCopasiObject * >::const_iterator itParameter, endParameter = DeletedParameters.end();
      std::set< const CCopasiObject * > DeletedObjects;

      for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
        {
          Objects.append(FROM_UTF8((*itParameter)->getObjectName()) + ", ");
          DeletedObjects.insert((*itParameter)->getObject(CCopasiObjectName("Reference=Value")));
        }

      Objects.remove(Objects.length() - 2, 2);

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, pModel, ObjectType,
                                    Objects, DeletedObjects);

      switch (choice)
        {
          case QMessageBox::Ok:

            for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
              pModel->removeLocalReactionParameter((*itParameter)->getKey());

            break;

          default:
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
      return;
    }

  //first check if new metabolites need to be created
  bool createdMetabs = ri.createMetabolites();
  bool createdObjects = ri.createOtherObjects();
  //this writes all changes to the reaction
  ri.writeBackToReaction(NULL);

  //(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->compile();
  //this tells the gui what it needs to know.
  if (createdObjects)
    emit notifyGUI(ListViews::MODEL, ListViews::CHANGE, "");
  else
    {
      if (createdMetabs) emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, "");

      emit notifyGUI(ListViews::REACTION, ListViews::CHANGE, "");
    }
}

bool CQReactionDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createReaction("");
    }

  endInsertRows();
  return true;
}

bool CQReactionDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->removeReaction(position);
    }

  endRemoveRows();
  return true;
}
