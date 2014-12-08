// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtCore/QString>

#include "CQCompartmentDM.h"

#include "CQMessageBox.h"
#include "qtUtilities.h"

#ifdef COPASI_UNDO
#include "model/CReaction.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "model/CEvent.h"
#include "undoFramework/InsertCompartmentRowsCommand.h"
#include "undoFramework/RemoveCompartmentRowsCommand.h"
#include "undoFramework/RemoveAllCompartmentRowsCommand.h"
#include "undoFramework/CompartmentDataChangeCommand.h"
#include "undoFramework/UndoCompartmentData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoSpecieData.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoEventAssignmentData.h"
#endif

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "function/CExpression.h"

CQCompartmentDM::CQCompartmentDM(QObject *parent)
  : CQBaseDataModel(parent)

{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
}

const QStringList& CQCompartmentDM::getTypes()
{
  return mTypes;
}

const std::vector< unsigned C_INT32 >& CQCompartmentDM::getItemToType()
{
  return mItemToType;
}

int CQCompartmentDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (int)(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments().size() + 1;
}
int CQCompartmentDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_COMPARTMENTS;
}

Qt::ItemFlags CQCompartmentDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_COMPARTMENTS || index.column() == COL_TYPE_COMPARTMENTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else if (index.column() == COL_IVOLUME)
    {
      if (this->index(index.row(), COL_TYPE_COMPARTMENTS).data() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT])))
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEnabled;
      else
        return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQCompartmentDM::data(const QModelIndex &index, int role) const
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

              case COL_NAME_COMPARTMENTS:
                return QVariant(QString("New Compartment"));

              case COL_TYPE_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[0]])));

              case COL_IVOLUME:
                return QVariant(QString::number(1.0, 'g', 10));

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CCompartment *pComp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[index.row()];
          const CExpression * pExpression = NULL;

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(pComp->getObjectName())));

              case COL_TYPE_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[pComp->getStatus()])));

              case COL_IVOLUME:

                if (role == Qt::EditRole)
                  return QVariant(QString::number(pComp->getInitialValue(), 'g', 10));
                else
                  return QVariant(pComp->getInitialValue());

              case COL_VOLUME:
                return QVariant(pComp->getValue());

              case COL_RATE_COMPARTMENTS:
                return QVariant(pComp->getRate());

              case COL_IEXPRESSION_COMPARTMENTS:
              {
                pExpression = pComp->getInitialExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant();
              }

              case COL_EXPRESSION_COMPARTMENTS:
              {
                pExpression = pComp->getExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant();
              }
            }
        }
    }

  return QVariant();
}

QVariant CQCompartmentDM::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    {
      QString ValueUnits, RateUnits, ExpressionUnits;
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      const CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

      if (pModel)
        {
          ValueUnits = FROM_UTF8(pModel->getVolumeUnitsDisplayString());

          if (!ValueUnits.isEmpty())
            ValueUnits = "\n(" + ValueUnits + ")";

          RateUnits = FROM_UTF8(pModel->getVolumeRateUnitsDisplayString());

          if (!RateUnits.isEmpty())
            RateUnits = "\n(" + RateUnits + ")";

          if (!ValueUnits.isEmpty() && !RateUnits.isEmpty())
            {
              if (ValueUnits == RateUnits)
                ExpressionUnits = ValueUnits;
              else
                ExpressionUnits = "\n(" + FROM_UTF8(pModel->getVolumeUnitsDisplayString()) + " or " + FROM_UTF8(pModel->getVolumeRateUnitsDisplayString()) + ")";
            }
          else if (!ValueUnits.isEmpty())
            ExpressionUnits = "\n(" + FROM_UTF8(pModel->getVolumeUnitsDisplayString()) + " or 1)";
          else if (!RateUnits.isEmpty())
            ExpressionUnits = "\n(1 or " + FROM_UTF8(pModel->getVolumeRateUnitsDisplayString()) + ")";
        }

      switch (section)
        {
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));

          case COL_NAME_COMPARTMENTS:
            return QVariant(QString("Name"));

          case COL_TYPE_COMPARTMENTS:
            return QVariant(QString("     Type     "));

          case COL_IVOLUME:
            return QVariant("Initial Volume" + ValueUnits);

          case COL_VOLUME:
            return QVariant("Volume" + ValueUnits);

          case COL_RATE_COMPARTMENTS:
            return QVariant("Rate" + RateUnits);

          case COL_IEXPRESSION_COMPARTMENTS:
            return QVariant("Initial Expression" + ValueUnits);

          case COL_EXPRESSION_COMPARTMENTS:
            return QVariant("Expression" + ExpressionUnits);

          default:
            return QVariant();
        }
    }
  else  //Vertical header
    return QString("%1").arg(section + 1);
}

bool CQCompartmentDM::setData(const QModelIndex &index, const QVariant &value,
                              int role)
{
#ifdef COPASI_UNDO

  if (index.data() == value)
    return false;
  else
    mpUndoStack->push(new CompartmentDataChangeCommand(index, value, role, this));

#else

  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.column() == COL_TYPE_COMPARTMENTS)
            {
              if (index.data().toString() != QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
                insertRow();
              else
                return false;
            }
          else if (index.data() != value)
            insertRow();
          else
            return false;
        }

      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCompartment *pComp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[index.row()];

      if (index.column() == COL_NAME_COMPARTMENTS)
        pComp->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_TYPE_COMPARTMENTS)
        pComp->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
      else if (index.column() == COL_IVOLUME)
        pComp->setInitialValue(value.toDouble());

      if (defaultRow && this->index(index.row(), COL_NAME_COMPARTMENTS).data().toString() == "compartment")
        pComp->setObjectName(TO_UTF8(createNewName("compartment", COL_NAME_COMPARTMENTS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::CHANGE, pComp->getKey());
    }

#endif

  return true;
}

bool CQCompartmentDM::insertRows(int position, int rows, const QModelIndex&)
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new InsertCompartmentRowsCommand(position, rows, this, QModelIndex()));
#else
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CCompartment * pComp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createCompartment(TO_UTF8(createNewName("compartment", COL_NAME_COMPARTMENTS)));
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pComp->getKey());
    }

  endInsertRows();
#endif

  return true;
}

bool CQCompartmentDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CCopasiVector< CCompartment >::const_iterator itRow = pModel->getCompartments().begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = (*itRow)->getKey();
    }

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->removeCompartment(*itDeletedKey);
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::DELETE, *itDeletedKey);
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::DELETE, "");
      emit notifyGUI(ListViews::METABOLITE, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
    }

  endRemoveRows();

  return true;
}

bool CQCompartmentDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
#ifdef COPASI_UNDO
  mpUndoStack->push(new RemoveCompartmentRowsCommand(rows, this, QModelIndex()));
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
  QList <CCompartment *> pCompartments;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pModel->getCompartments()[(*i).row()])
        pCompartments.append(pModel->getCompartments()[(*i).row()]);
    }

  QList <CCompartment *>::const_iterator j;

  for (j = pCompartments.begin(); j != pCompartments.end(); ++j)
    {
      CCompartment * pCompartment = *j;

      size_t delRow =
        pModel->getCompartments().CCopasiVector< CCompartment >::getIndex(pCompartment);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "compartment",
                                        FROM_UTF8(pCompartment->getObjectName()),
                                        pCompartment->getDeletedObjects());

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

#endif

  return true;
}

#ifdef COPASI_UNDO

bool CQCompartmentDM::compartmentDataChange(const QModelIndex &index, const QVariant &value, int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.column() == COL_TYPE_COMPARTMENTS)
            {
              if (index.data().toString() != QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
                insertRow();
              else
                return false;
            }
          else if (index.data() != value)
            insertRow();
          else
            return false;
        }

      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCompartment *pComp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[index.row()];

      if (index.column() == COL_NAME_COMPARTMENTS)
        pComp->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_TYPE_COMPARTMENTS)
        pComp->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
      else if (index.column() == COL_IVOLUME)
        pComp->setInitialValue(value.toDouble());

      if (defaultRow && this->index(index.row(), COL_NAME_COMPARTMENTS).data().toString() == "compartment")
        pComp->setObjectName(TO_UTF8(createNewName("compartment", COL_NAME_COMPARTMENTS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::CHANGE, pComp->getKey());
    }

  emit changeWidget(111);

  return true;
}

void CQCompartmentDM::insertNewCompartmentRow(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CCompartment * pComp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createCompartment(TO_UTF8(createNewName("compartment", COL_NAME_COMPARTMENTS)));
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pComp->getKey());
    }

  endInsertRows();
}

void CQCompartmentDM::deleteCompartmentRow(UndoCompartmentData *pCompartmentData)
{
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  CCompartment * pCompartment = pModel->getCompartments()[pCompartmentData->getName()];
  size_t index = pModel->getCompartments().CCopasiVector< CCompartment >::getIndex(pCompartment);
  removeRow((int) index);

  emit changeWidget(111);
}

void CQCompartmentDM::addCompartmentRow(UndoCompartmentData *pCompartmentData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  beginInsertRows(QModelIndex(), 1, 1);
  CCompartment *pCompartment = pDataModel->getModel()->createCompartment(pCompartmentData->getName());
  pCompartment->setStatus(pCompartmentData->getStatus());
  std::string key = pCompartment->getKey();
  emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, key);
  endInsertRows();
}

bool CQCompartmentDM::removeCompartmentRows(QModelIndexList rows, const QModelIndex&)
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
  QList <CCompartment *> pCompartments;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pModel->getCompartments()[(*i).row()])
        pCompartments.append(pModel->getCompartments()[(*i).row()]);
    }

  QList <CCompartment *>::const_iterator j;

  for (j = pCompartments.begin(); j != pCompartments.end(); ++j)
    {
      CCompartment * pCompartment = *j;

      size_t delRow =
        pModel->getCompartments().CCopasiVector< CCompartment >::getIndex(pCompartment);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "compartment",
                                        FROM_UTF8(pCompartment->getObjectName()),
                                        pCompartment->getDeletedObjects());

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  emit changeWidget(111);

  return true;
}

bool CQCompartmentDM::insertCompartmentRows(QList <UndoCompartmentData *> pData)
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return false;

  //reinsert all the Compartments
  /*QList <UndoCompartmentData *>::const_iterator i;
  for (i = pData.begin(); i != pData.end(); ++i)
  {
    UndoCompartmentData * data = *i;
    beginInsertRows(QModelIndex(), 1, 1);
    CCompartment *pCompartment =  pModel->createCompartment(data->getName());
    pCompartment->setInitialValue(data->getInitialValue());
    pCompartment->setStatus(data->getStatus());
    emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pCompartment->getKey());
    endInsertRows();
  }*/

  //restore all the dependencies
  QList <UndoCompartmentData *>::const_iterator k;

  for (k = pData.begin(); k != pData.end(); ++k)
    {
      UndoCompartmentData * data = *k;

      beginInsertRows(QModelIndex(), 1, 1);
      CCompartment *pCompartment =  pModel->createCompartment(data->getName());
      pCompartment->setInitialValue(data->getInitialValue());
      pCompartment->setStatus(data->getStatus());
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pCompartment->getKey());

      //reinsert all the species
      QList <UndoSpecieData *> *pSpecieData = data->getSpecieDependencyObjects();

      if (!pSpecieData->empty())
        {
          QList <UndoSpecieData *>::const_iterator i;

          for (i = pSpecieData->begin(); i != pSpecieData->end(); ++i)
            {
              UndoSpecieData * sData = *i;

              //  beginInsertRows(QModelIndex(), 1, 1);
              if (pCompartment->getMetabolites().getIndex(sData->getName()) == C_INVALID_INDEX)
                {
                  CMetab *pSpecie =  pModel->createMetabolite(sData->getName(), sData->getCompartment(), sData->getIConc(), sData->getStatus());

                  if (pSpecie)
                    {
                      if (sData->getStatus() != CModelEntity::ASSIGNMENT)
                        {
                          pSpecie->setInitialConcentration(sData->getIConc());
                        }

                      if (sData->getStatus() == CModelEntity::ODE || sData->getStatus() == CModelEntity::ASSIGNMENT)
                        {
                          pSpecie->setExpression(sData->getExpression());
                          pSpecie->getExpressionPtr()->compile();
                        }

                      // set initial expression
                      if (sData->getStatus() != CModelEntity::ASSIGNMENT)
                        {
                          pSpecie->setInitialExpression(sData->getInitialExpression());
                          pSpecie->getInitialExpressionPtr()->compile();
                        }

                      emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, pSpecie->getKey());
                      //endInsertRows();
                    }
                }
            }
        }

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
                  CModelValue *pGlobalQuantity =  pModel->createModelValue(gData->getName());

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

      //reinsert the dependency reaction
      QList <UndoReactionData *> *pReactionData = data->getReactionDependencyObjects();

      if (!pReactionData->empty())
        {
          QList <UndoReactionData *>::const_iterator j;

          for (j = pReactionData->begin(); j != pReactionData->end(); ++j)
            {
              UndoReactionData * rData = *j;

              //need to make sure reaction doesn't exist in the model already

              if (pModel->getReactions().getIndex(rData->getName()) == C_INVALID_INDEX)
                {
                  emit notifyGUI(ListViews::METABOLITE, ListViews::ADD, ""); //Refresh all dependency species.
                  CReaction *pRea =  pModel->createReaction(rData->getName());
                  CChemEqInterface *chem = new CChemEqInterface(pModel);
                  chem->setChemEqString(rData->getRi()->getChemEqString());
                  chem->writeToChemEq(pRea->getChemEq());
                  rData->getRi()->createMetabolites();
                  rData->getRi()->createOtherObjects();
                  rData->getRi()->writeBackToReaction(pRea);

                  emit notifyGUI(ListViews::REACTION, ListViews::ADD, pRea->getKey());
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

              //  pModel->getEvents().getIndex(eData-getName())

              CEvent *pEvent =  pModel->createEvent(eData->getName());
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

              /*        QList <CEventAssignment *> *assignments = eData->getAssignments();
                      QList <CEventAssignment *>::const_iterator i;

                      for (i = assignments->begin(); i != assignments->end(); ++i)
                        {
                          CEventAssignment * assign = *i;

                          if (pEvent->getAssignments().getIndex(assign->getObjectName()) == C_INVALID_INDEX)
                            {
                              CEventAssignment *eventAssign = new CEventAssignment(assign->getTargetKey(), pEvent->getObjectParent());
                              eventAssign->setExpression(assign->getExpression());
                              //  eventAssign->getExpressionPtr()->compile();
                              pEvent->getAssignments().add(eventAssign);
                            }*/

              /*    if (pEvent->getAssignments().getIndex(assign->getObjectName()) == C_INVALID_INDEX)
              {
                CEventAssignment *eventAssign = assign; // new CEventAssignment(assign->getTargetKey(), pEvent->getObjectParent());
              //  CEventAssignment *eventAssign = new CEventAssignment(pEvent->getObjectParent()->getKey());
              //    eventAssign->setExpression(assign->getExpression());
              //    eventAssign->getExpressionPtr()->compile();
                pEvent->getAssignments().add(eventAssign);
              }*/
              //}

              emit notifyGUI(ListViews::EVENT, ListViews::ADD, key);
            }
        }

      endInsertRows();
    }

  emit changeWidget(111);

  return true;
}

void CQCompartmentDM::deleteCompartmentRows(QList <UndoCompartmentData *> pData)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  QList <UndoCompartmentData *>::const_iterator j;

  for (j = pData.begin(); j != pData.end(); ++j)
    {
      UndoCompartmentData * data = *j;
      CCompartment * pCompartment = pModel->getCompartments()[data->getName()];
      size_t index = pModel->getCompartments().CCopasiVector< CCompartment >::getIndex(pCompartment);

      if (index != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "compartment",
                                        FROM_UTF8(pCompartment->getObjectName()),
                                        pCompartment->getDeletedObjects());

          if (choice == QMessageBox::Ok)
            removeRow((int) index);
        }

      //removeRow((int) index);
    }

  emit changeWidget(111);
}

bool CQCompartmentDM::clear()
{
  mpUndoStack->push(new RemoveAllCompartmentRowsCommand(this, QModelIndex()));
  return true;
}

bool CQCompartmentDM::removeAllCompartmentRows()
{
  return removeRows(0, rowCount() - 1);
}
#endif
