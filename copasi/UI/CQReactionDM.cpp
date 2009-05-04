// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionDM.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/04 15:24:00 $
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
              RateUnits = FROM_UTF8(pModel->getQuantityRateUnits());

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
              FrequencyUnits = FROM_UTF8(pModel->getFrequencyUnits());

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
      QString parameterList = "Are you sure you want to delete listed PARAMETERS of reaction " + this->index(index.row(), COL_NAME).data().toString() + "?\n";
      QString affectedCompartmentList = "Following COMPARTMENT(S) reference above PARAMETERS and will be deleted -\n";
      QString affectedMetabList = "Following METABOLITE(S) reference above PARAMETERS and will be deleted -\n";
      QString affectedReacList = "Following REACTION(S) reference above PARAMETERS and will be deleted -\n";
      QString affectedValueList = "Following MODEL VALUE(S) reference above PARAMETERS and will be deleted -\n";

      bool compartmentFound = false;
      bool metabFound = false;
      bool reacFound = false;
      bool valueFound = false;

      std::set< const CCopasiObject * >::const_iterator itParameter, endParameter = DeletedParameters.end();

      for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
        {
          parameterList.append(FROM_UTF8((*itParameter)->getObjectName()));
          parameterList.append(", ");

          std::set< const CCopasiObject * > DeletedObjects;
          DeletedObjects.insert((*itParameter)->getObject(CCopasiObjectName("Reference=Value")));

          std::set< const CCopasiObject * > Reactions;
          std::set< const CCopasiObject * > Metabolites;
          std::set< const CCopasiObject * > Values;
          std::set< const CCopasiObject * > Compartments;

          pModel->appendDependentModelObjects(DeletedObjects,
                                              Reactions, Metabolites, Compartments, Values);

          if (Reactions.size() > 0)
            {
              reacFound = true;
              std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();

              for (it = Reactions.begin(); it != itEnd; ++it)
                {
                  affectedReacList.append(FROM_UTF8((*it)->getObjectName()));
                  affectedReacList.append(", ");
                }

              affectedReacList.remove(affectedReacList.length() - 2, 2);
              affectedReacList.append("  ---> ");
              affectedReacList.append(FROM_UTF8((*itParameter)->getObjectName()));
              affectedReacList.append("\n");
            }

          if (Metabolites.size() > 0)
            {
              metabFound = true;
              std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();

              for (it = Metabolites.begin(); it != itEnd; ++it)
                {
                  affectedMetabList.append(FROM_UTF8((*it)->getObjectName()));
                  affectedMetabList.append(", ");
                }

              affectedMetabList.remove(affectedMetabList.length() - 2, 2);
              affectedMetabList.append("  ---> ");
              affectedMetabList.append(FROM_UTF8((*itParameter)->getObjectName()));
              affectedMetabList.append("\n");
            }

          if (Values.size() > 0)
            {
              valueFound = true;
              std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();

              for (it = Values.begin(); it != itEnd; ++it)
                {
                  affectedValueList.append(FROM_UTF8((*it)->getObjectName()));
                  affectedValueList.append(", ");
                }

              affectedValueList.remove(affectedValueList.length() - 2, 2);
              affectedValueList.append("  ---> ");
              affectedValueList.append(FROM_UTF8((*itParameter)->getObjectName()));
              affectedValueList.append("\n");
            }

          if (Compartments.size() > 0)
            {
              compartmentFound = true;
              std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();

              for (it = Compartments.begin(); it != itEnd; ++it)
                {
                  affectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
                  affectedCompartmentList.append(", ");
                }

              affectedCompartmentList.remove(affectedCompartmentList.length() - 2, 2);
              affectedCompartmentList.append("  ---> ");
              affectedCompartmentList.append(FROM_UTF8((*itParameter)->getObjectName()));
              affectedCompartmentList.append("\n");
            }
        }

      parameterList.remove(parameterList.length() - 2, 2);

      QString msg = parameterList;

      if (compartmentFound)
        {
          msg.append("\n \n");
          msg.append(affectedCompartmentList);
        }

      if (metabFound)
        {
          msg.append("\n \n");
          msg.append(affectedMetabList);
        }

      if (reacFound)
        {
          msg.append("\n \n");
          msg.append(affectedReacList);
        }

      if (valueFound)
        {
          msg.append("\n \n");
          msg.append(affectedValueList);
        }

      C_INT32 choice = 0;

      if (metabFound || reacFound || valueFound || compartmentFound)
        choice = CQMessageBox::question(NULL,
                                        "CONFIRM DELETE",
                                        msg,
                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      switch (choice)
        {
            // Yes or Enter
          case QMessageBox::Yes:

            for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
              pModel->removeLocalReactionParameter((*itParameter)->getKey());

            break;

            // No or Escape
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
