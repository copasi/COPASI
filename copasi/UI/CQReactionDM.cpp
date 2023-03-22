// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtCore/QString>
#include <QtCore/QList>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CChemEqInterface.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/model/CModel.h"

#include "CQMessageBox.h"
#include "CQReactionDM.h"
#include "qtUtilities.h"

CQReactionDM::CQReactionDM(QObject *parent, CDataModel * pDataModel)
  : CQBaseDataModel(parent, pDataModel)
  , mpReactions(NULL)
{
}

size_t CQReactionDM::size() const
{
  if (mpReactions != NULL)
    return mpReactions->size();

  return 0;
}

int CQReactionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
}

int CQReactionDM::columnCount(const QModelIndex&) const
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
      if (isDefaultRow(index) || index.row() >= (int) mpReactions->size())
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
          CReaction & Reaction = mpReactions->operator[](index.row());

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);
                break;

              case COL_NAME_REACTIONS:
                return QVariant(QString(FROM_UTF8(Reaction.getObjectName())));
                break;

              case COL_EQUATION:
                return QVariant(QString(FROM_UTF8(CChemEqInterface::getChemEqString(Reaction, false))));
                break;

              case COL_RATE_LAW:
                return QVariant(QString(FROM_UTF8(Reaction.getFunction()->getObjectName())));
                break;

              case COL_FLUX:
                return QVariant(Reaction.getFlux());
                break;

              case COL_PARTICLE_FLUX:
                return QVariant(Reaction.getParticleFlux());
                break;

              case COL_NOISE_EXPRESSION:
                return QVariant(QString(FROM_UTF8(Reaction.getNoiseExpression())));
                break;
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
            const CModel * pModel = mpDataModel->getModel();

            if (pModel == NULL) return QVariant();

            QString RateUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint(pModel->getQuantityUnit() + "/(" + pModel->getTimeUnit() + ")")) + "]";

            return QVariant("Flux" + RateUnits);
          }

          case COL_PARTICLE_FLUX:
          {
            const CModel * pModel = mpDataModel->getModel();

            if (pModel == NULL) return QVariant();

            QString FrequencyUnits = "\n[" + FROM_UTF8("1/(" + pModel->getTimeUnit() + ")") + "]";

            return QVariant("Number Flux" + FrequencyUnits);
          }

          case COL_NOISE_EXPRESSION:
            return QVariant("Noise Expression");

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
  if (index.data() == value)
    return false;

  if (isDefaultRow(index))
    {
      insertNewRows(rowCount(), 1, index.column(), value);
    }
  else if (role == Qt::EditRole)
    {
      CReaction & Reaction = mpReactions->operator [](index.row());
      CUndoData UndoData(CUndoData::Type::CHANGE, Reaction.toData());
      bool changed = false;

      switch (index.column())
        {
          case COL_NAME_REACTIONS:
            if (mpReactions->getIndex(TO_UTF8(value.toString())) == C_INVALID_INDEX)
              {
                changed |= UndoData.addProperty(CData::OBJECT_NAME,
                                                Reaction.getObjectName(),
                                                TO_UTF8(value.toString()));
              }

            break;

          case COL_EQUATION:
            changed |= setEquation(Reaction, value, UndoData);
            break;
        }

      if (changed)
        {
          ListViews::addUndoMetaData(this, UndoData);
          emit signalNotifyChanges(mpDataModel->applyData(UndoData));
        }
    }

  return true;
}

bool CQReactionDM::setEquation(const CReaction & reaction, const QVariant & value, CUndoData & data)
{
  std::string NewEquation = TO_UTF8(value.toString());

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to ri;
  CReactionInterface ri;
  ri.init(reaction);

  if (NewEquation == ri.getChemEqString() ||
      !CChemEqInterface::isValidEq(NewEquation))
    {
      return false;
    }

  ri.setChemEqString(NewEquation, "");

  data = ri.createUndoData((CCore::Framework) mFramework);

  return true;
}

// virtual
void CQReactionDM::resetCacheProtected()
{
  mpReactions = dynamic_cast< CDataVectorNS < CReaction > * >(&mpDataModel->getModel()->getReactions());
  assert(mpReactions != NULL);
}

bool CQReactionDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  insertNewRows(position, rows);

  return true;
}

bool CQReactionDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  std::vector< CCommonName > ToBeDeleted;
  ToBeDeleted.resize(rows);

  std::vector< CCommonName >::iterator it = ToBeDeleted.begin();
  std::vector< CCommonName >::iterator end = ToBeDeleted.end();

  CDataVectorNS< CReaction >::const_iterator itRow = mpReactions->begin() + position;

  for (; it != end; ++it, ++itRow)
    {
      *it = itRow->getCN();
    }

  for (it = ToBeDeleted.begin(); it != end; ++it)
    {
      if (mFetched > 0)
        --mFetched;

      const CReaction * pObj = dynamic_cast< const CReaction * >(mpDataModel->getObject(*it));

      if (!pObj)
        continue;

      CUndoData UndoData;
      pObj->createUndoData(UndoData, CUndoData::Type::REMOVE);
      ListViews::addUndoMetaData(this, UndoData);

      emit signalNotifyChanges(mpDataModel->applyData(UndoData));
    }

  endRemoveRows();

  return true;
}

bool CQReactionDM::removeRows(QModelIndexList rows, const QModelIndex& index)
{
  if (rows.isEmpty())
    return false;

  //Build the list of pointers to items to be deleted
  //before actually deleting any item.
  QList< CReaction * > Reactions;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (i->isValid()
          && !isDefaultRow(*i))
        Reactions.append(&mpReactions->operator[](i->row()));
    }

  QList< CReaction * >::const_iterator j;

  for (j = Reactions.begin(); j != Reactions.end(); ++j)
    {
      CReaction * pReaction = *j;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(ListViews::ancestor(this), "reaction",
                                    FROM_UTF8(pReaction->getObjectName()),
                                    pReaction);

      if (choice == QMessageBox::Ok)
        {
          removeRows(mpReactions->CDataVector< CReaction >::getIndex(pReaction), 1);
        }
    }

  return true;
}

void CQReactionDM::insertNewRows(int position, int rows, int column, const QVariant & value)
{
  CModel * pModel = mpDataModel->getModel();

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(column == COL_NAME_REACTIONS ? value.toString() : "reaction", COL_NAME_REACTIONS);

      CReaction *pRea = pModel->createReaction(TO_UTF8(name));

      if (pRea == NULL) continue;

      ++mFetched;

      CUndoData UndoData(CUndoData::Type::INSERT, pRea);

      if (column == COL_EQUATION)
        {
          CUndoData EquationChangeData;

          if (setEquation(*pRea, value, EquationChangeData))
            {
              UndoData.appendData(EquationChangeData.getNewData());

              UndoData.addPreProcessData(EquationChangeData.getPreProcessData());
              UndoData.addPostProcessData(EquationChangeData.getPostProcessData());
            }
        }

      delete pRea;

      ListViews::addUndoMetaData(this, UndoData);
      emit signalNotifyChanges(mpDataModel->applyData(UndoData));
    }

  endInsertRows();
}
