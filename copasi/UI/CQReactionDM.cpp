// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionDM.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/21 16:20:31 $
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

#include "CQReactionDM.h"
#include "qtUtilities.h"

CQReactionDM::CQReactionDM(QObject *parent)
    : CQBaseDataModel(parent)

{
}

int CQReactionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions().size();
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
      CReaction *pRea = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions()[index.row()];

      switch (index.column())
        {
          case COL_NAME:
            return QVariant(QString(FROM_UTF8(pRea->getObjectName())));
          case COL_EQUATION:
            return QVariant(QString(FROM_UTF8(CChemEqInterface::getChemEqString((*CCopasiRootContainer::getDatamodelList())[0]->getModel(), *pRea, false))));
          case COL_RATE_LAW:

            if (pRea->getFunction())
              return QVariant(QString(FROM_UTF8(pRea->getFunction()->getObjectName())));

          case COL_FLUX:
            return QVariant(QString::number(pRea->getFlux()));
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
          case COL_NAME:
            return QVariant(QString("Name"));
          case COL_EQUATION:
            return QVariant(QString("Equation"));
          case COL_RATE_LAW:
            return QVariant(QString("Rate Law"));
          case COL_FLUX:
          {
            QString header = "Flux";
            // TODO: Fix unit display see CReactionWidget.cpp
            // QString units = FROM_UTF8((*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getQuantityRateUnitName());

            // if (!units.isNull())
            //  {
            //    header += " (";
            //    header += units;
            //    header += ")";
            //}

            return QVariant(header);
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
      // this loads the reaction into a CReactionInterface object.
      // the gui works on this object and later writes back the changes to ri;
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CReactionInterface ri((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
      CReaction *pRea = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions()[index.row()];

      if (index.column() == COL_NAME)
        pRea->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_EQUATION)
        {

          ri.initFromReaction(pRea->getKey());

          QString equation = value.toString();

          if (TO_UTF8(equation) != ri.getChemEqString())
            {
              //first check if the string is a valid equation
              if (!CChemEqInterface::isValidEq(TO_UTF8(equation)))
                {
                  return false;
                }
              else
                {
                  //tell the reaction interface
                  ri.setChemEqString(TO_UTF8(equation), "");
                }
            }

          //this writes all changes to the reaction
          ri.writeBackToReaction(NULL);
        }

      emit dataChanged(index, index);
    }

  return true;
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
  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->removeReaction(position);
    }

  endRemoveRows();
  return true;
}

bool CQReactionDM::isDefaultRow(const QModelIndex& i) const
{
  if (!i.isValid())
    {return false;}

  bool rowDefault = true;

  for (int j = 0; j < columnCount(); j++)
    {
      QModelIndex ind = index(i.row(), j);
      QString value = ind.data().toString();

      if (!value.isEmpty())
        {
          switch (j)
            {
              case COL_NAME:

                if (value != "No Name")
                  rowDefault = false;

                break;
              case COL_RATE_LAW:

                if (value != "undefined")
                  rowDefault = false;

                break;
              case COL_FLUX:

                if (value != "0")
                  rowDefault = false;

                break;
              default:
                rowDefault = false;
                break;
            }
        }
    }

  return rowDefault;
}
