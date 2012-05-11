// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQBrowserPaneDM.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/11 16:53:05 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "CQBrowserPaneDM.h"
#include "DataModel.txt.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"

#include "utilities/CCopasiTree.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "utilities/CCopasiTask.h"
#include "report/CReportDefinitionVector.h"
#include "plot/COutputDefinitionVector.h"
#include "report/CCopasiRootContainer.h"
#include "function/CFunctionDB.h"
#include "model/CMetabNameInterface.h"

CQBrowserPaneDM::CQBrowserPaneDM(QObject * pParent):
    QAbstractItemModel(pParent),
    mpRoot(NULL),
    mpCopasiDM(NULL),
    mpGuiDM(NULL),
    mEmitDataChanged(true),
    mFlags(CQBrowserPaneDM::Model | CQBrowserPaneDM::Tasks | CQBrowserPaneDM::Output | CQBrowserPaneDM::FunctionDB)
{
  // setSortRole(Qt::EditRole);
  createStaticDM();
}

// virtual
CQBrowserPaneDM::~CQBrowserPaneDM()
{
  pdelete(mpRoot);
}

// virtual
int CQBrowserPaneDM::columnCount(const QModelIndex & /* parent */) const
{
  return 1;
}

// virtual
QVariant CQBrowserPaneDM::data(const QModelIndex & index, int role) const
{
  CNode * pNode = nodeFromIndex(index);

  if (pNode == NULL) return QVariant();

  switch (role)
    {
      case Qt::DisplayRole:

        // We need to add the number of children to some nodes.
        switch (pNode->getId())
          {
            case 5:
            case 42:
            case 43:
            case 111:
            case 112:
            case 114:
            case 115:
            case 116:
              return QVariant(pNode->getDisplayRole() + " (" + QString::number(pNode->getNumChildren()) + ")");
              break;

            default:
              return QVariant(pNode->getDisplayRole());
              break;
          }

        break;

      case Qt::EditRole:
        return QVariant(pNode->getSortRole());
        break;
    }

  return QVariant();
}

// virtual
QModelIndex CQBrowserPaneDM::index(int row, int column, const QModelIndex & parent) const
{
  CNode * pParent = nodeFromIndex(parent);

  if (pParent == NULL) return createIndex(row, column, mpRoot);

  CNode * pNode = static_cast< CNode * >(pParent->getChild(row));

  if (pNode)
    return createIndex(row, column, pNode);
  else
    return QModelIndex();
}

// virtual
QModelIndex CQBrowserPaneDM::parent(const QModelIndex & index) const
{
  CNode * pNode = nodeFromIndex(index);

  if (pNode == NULL || pNode == mpRoot)
    {
      return QModelIndex();
    }

  CNode * pParent = static_cast< CNode * >(pNode->getParent());
  assert(pParent != NULL);

  return createIndex(pParent->getRow(), 0, pParent);
}

QModelIndex CQBrowserPaneDM::index(const size_t & id, const std::string & key) const
{
  CNode * pNode = NULL;

  if (id != C_INVALID_INDEX)
    {
      pNode = findNodeFromId(id);
    }
  else if (key != "")
    {
      pNode = findNodeFromKey(key);
    }

  return index(pNode);
}

// virtual
int CQBrowserPaneDM::rowCount(const QModelIndex & parent) const
{
  if (!parent.isValid())
    return (mpRoot != NULL) ? 1 : 0;

  CNode * pParent = nodeFromIndex(parent);

  return pParent->getNumChildren();
}

// virtual
bool CQBrowserPaneDM::removeRows(int row, int count, const QModelIndex & parent)
{
  CNode * pParent = nodeFromIndex(parent);

  if (pParent == NULL) return false;

  CNode * pNode = static_cast< CNode * >(pParent->getChild(row));

  beginRemoveRows(parent, row, row + count - 1);

  for (int i = 0; i < count && pNode != NULL; i++)
    {
      CNode * pTmp = pNode;
      pNode = static_cast< CNode * >(pNode->getSibling());
      delete pTmp;
    }

  endRemoveRows();

  return true;
}


CQBrowserPaneDM::CNode * CQBrowserPaneDM::findNodeFromId(const size_t & id) const
{
  CCopasiTree< CNode >::iterator it = mpRoot;
  CCopasiTree< CNode >::iterator end;

  for (; it != end; ++it)
    {
      if (it->getData().mId == id)
        {
          return &*it;
        }
    }

  return NULL;
}

CQBrowserPaneDM::CNode * CQBrowserPaneDM::findNodeFromKey(const std::string & key) const
{
  CCopasiTree< CNode >::iterator it = mpRoot;
  CCopasiTree< CNode >::iterator end;

  for (; it != end; ++it)
    {
      if (it->getData().mKey == key)
        {
          return &*it;
        }
    }

  return NULL;
}

size_t CQBrowserPaneDM::getIdFromIndex(const QModelIndex & index) const
{
  CNode * pNode = nodeFromIndex(index);

  if (pNode == NULL) return C_INVALID_INDEX;

  return pNode->getId();
}

std::string CQBrowserPaneDM::getKeyFromIndex(const QModelIndex & index) const
{
  CNode * pNode = nodeFromIndex(index);

  if (pNode == NULL) return "";

  return pNode->getKey();
}


void CQBrowserPaneDM::remove(const std::string & key)
{
  CNode * pNode = findNodeFromKey(key);

  if (pNode == NULL || pNode->getParent() == NULL)
    {
      return;
    }

  QModelIndex Parent = index(static_cast< CNode * >(pNode->getParent()));

  removeRows(pNode->getRow(), 1, Parent);
}

void CQBrowserPaneDM::rename(const std::string & key, const QString & displayRole)
{
  CNode * pNode = findNodeFromKey(key);

  if (pNode == NULL) return;

  if (pNode->getDisplayRole() != displayRole)
    {
      pNode->setDisplayRole(displayRole);

      QModelIndex Index = index(pNode);

      if (mEmitDataChanged)
        {
          emit dataChanged(Index, Index);
        }
    }
}

void CQBrowserPaneDM::add(const size_t & id,
                          const std::string & key,
                          const QString & displayRole,
                          const size_t & parentId)
{
  CNode * pParent = findNodeFromId(parentId);
  int row = 0;

  if (pParent != NULL)
    {
      row = pParent->getNumChildren();
    }

  beginInsertRows(index(pParent), row, row);
  new CNode(id, key, displayRole, pParent);
  endInsertRows();
}

void CQBrowserPaneDM::setCopasiDM(const CCopasiDataModel * pDataModel)
{
  if (mpCopasiDM != pDataModel)
    {
      mpCopasiDM = pDataModel;

      mEmitDataChanged = false;

      clear();
      load();

      dataChanged(index(0, 0), index(0, 0));

      mEmitDataChanged = true;
    }
}

void CQBrowserPaneDM::setGuiDM(const DataModelGUI * pDataModel)
{
  if (mpGuiDM)
    {
      disconnect(mpGuiDM, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, std::string)),
                 this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const std::string &)));
    }

  mpGuiDM = pDataModel;

  if (mpGuiDM)
    {
      connect(mpGuiDM, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, std::string)),
              this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, std::string)));
    }
}


void CQBrowserPaneDM::load()
{
  findNodeFromId(1)->setKey(mpCopasiDM->getModel()->getKey());

  load(111); // Compartment
  load(112); // Species
  load(114); // Reactions
  load(115); // Global Quantities
  load(116); // Events

  findNodeFromId(117)->setKey(mpCopasiDM->getModel()->getKey()); // Parameter Overview

#ifdef COPASI_PARAMETER_SETS
  findNodeFromId(118)->setKey(mpCopasiDM->getModel()->getActiveParameterSetKey()); // Parameter Set
#endif // COPASI_PARAMETER_SETS

  findNodeFromId(21)->setKey((*mpCopasiDM->getTaskList())["Steady-State"]->getKey());
  findNodeFromId(221)->setKey((*mpCopasiDM->getTaskList())["Elementary Flux Modes"]->getKey());
  findNodeFromId(222)->setKey((*mpCopasiDM->getTaskList())["Moieties"]->getKey());
  findNodeFromId(2221)->setKey((*mpCopasiDM->getTaskList())["Moieties"]->getKey());
  findNodeFromId(23)->setKey((*mpCopasiDM->getTaskList())["Time-Course"]->getKey());
  findNodeFromId(24)->setKey((*mpCopasiDM->getTaskList())["Metabolic Control Analysis"]->getKey());

  findNodeFromId(27)->setKey((*mpCopasiDM->getTaskList())["Time Scale Separation Analysis"]->getKey());
  findNodeFromId(26)->setKey((*mpCopasiDM->getTaskList())["Lyapunov Exponents"]->getKey());

#ifdef COPASI_NONLIN_DYN
  findNodeFromId(28)->setKey((*mpCopasiDM->getTaskList())["Cross Section"]->getKey());
#endif

  findNodeFromId(31)->setKey((*mpCopasiDM->getTaskList())["Scan"]->getKey());
  findNodeFromId(32)->setKey((*mpCopasiDM->getTaskList())["Optimization"]->getKey());
  findNodeFromId(33)->setKey((*mpCopasiDM->getTaskList())["Parameter Estimation"]->getKey());
  findNodeFromId(34)->setKey((*mpCopasiDM->getTaskList())["Sensitivities"]->getKey());
  findNodeFromId(35)->setKey((*mpCopasiDM->getTaskList())["Linear Noise Approximation"]->getKey());


  findNodeFromId(42)->setKey(mpCopasiDM->getPlotDefinitionList()->getKey());
  load(42); // Plot Specifications

  findNodeFromId(43)->setKey(mpCopasiDM->getReportDefinitionList()->getKey());
  load(43); // Report Specifications

  load(5); // Functions

  dataChanged(index(0, 0), index(0, 0));
}

void CQBrowserPaneDM::load(const size_t & id)
{
  bool isSpecies = false;
  const CModel * pModel = mpCopasiDM->getModel();
  const CCopasiVector< CCopasiObject > * pVector = NULL;

  switch (id)
    {
      case 111: // Compartment
        pVector = reinterpret_cast< const CCopasiVector< CCopasiObject > * >(&pModel->getCompartments());
        break;

      case 112: // Species
        pVector = reinterpret_cast< const CCopasiVector< CCopasiObject > * >(&pModel->getMetabolites());
        isSpecies = true;
        break;

      case 114: // Reactions
        pVector = reinterpret_cast< const CCopasiVector< CCopasiObject > * >(&pModel->getReactions());
        break;

      case 115: // Global Quantities
        pVector = reinterpret_cast< const CCopasiVector< CCopasiObject > * >(&pModel->getModelValues());
        break;

      case 116: // Events
        pVector = reinterpret_cast< const CCopasiVector< CCopasiObject > * >(&pModel->getEvents());
        break;

      case 42: // Plot Specifications
        pVector = reinterpret_cast< const CCopasiVector< CCopasiObject > * >(mpCopasiDM->getPlotDefinitionList());
        break;

      case 43: // Report Specifications
        pVector = reinterpret_cast< const CCopasiVector< CCopasiObject > * >(mpCopasiDM->getReportDefinitionList());
        break;

      case 5: // Functions
        pVector = reinterpret_cast< const CCopasiVector< CCopasiObject > * >(&CCopasiRootContainer::getFunctionList()->loadedFunctions());
        break;

      default:
        return;
        break;
    }

  // We need to compare the existing nodes with the COPASI data model objects.
  CNode * pParent = findNodeFromId(id);
  CCopasiNode< CQBrowserPaneDM::SData > * pChildData = pParent->CCopasiNode< CQBrowserPaneDM::SData >::getChild();
  CCopasiVector< CCopasiObject >::const_iterator it = pVector->begin();
  CCopasiVector< CCopasiObject >::const_iterator end = pVector->end();

  bool changed = false;

  for (; pChildData != NULL && it != end; pChildData = pChildData->getSibling(), ++it)
    {
      CNode * pChild = static_cast< CNode *>(pChildData);

      pChild->setKey((*it)->getKey());

      QString DisplayRole;

      if (isSpecies)
        {
          DisplayRole = FROM_UTF8(CMetabNameInterface::getDisplayName(pModel, *static_cast<const CMetab *>(*it), false));
        }
      else
        {
          DisplayRole = FROM_UTF8((*it)->getObjectName());
        }

      if (pChild->getDisplayRole() != DisplayRole)
        {
          pChild->setDisplayRole(DisplayRole);
          changed = true;
        }
    }

  // Remove excess nodes
  if (pChildData != NULL)
    {
      int row = static_cast< CNode *>(pChildData)->getRow();
      int count = 0;

      while (pChildData != NULL)
        {
          count++;
          pChildData = pChildData->getSibling();
        }

      removeRows(row, count, index(pParent));
    }

  // Add missing nodes
  if (it != end)
    {
      int first = pParent->getNumChildren();
      int last = first + (end - it) - 1;

      beginInsertRows(index(pParent), first, last);

      for (; it != end; ++it)
        {
          QString DisplayRole;

          if (isSpecies)
            {
              DisplayRole = FROM_UTF8(CMetabNameInterface::getDisplayName(pModel, *static_cast<const CMetab *>(*it), false));
            }
          else
            {
              DisplayRole = FROM_UTF8((*it)->getObjectName());
            }

          new CNode(C_INVALID_INDEX, (*it)->getKey(), DisplayRole, pParent);
        }

      endInsertRows();
    }

  if (changed && mEmitDataChanged)
    {
      QModelIndex Parent = index(pParent);

      emit dataChanged(Parent, Parent);
    }
}

bool CQBrowserPaneDM::slotNotify(ListViews::ObjectType objectType, ListViews::Action action, std::string key)
{
  if (key == "")
    {
      // Load is only reporting actual changes.
      load();
      return true;
    }

  const CCopasiObject * pObject = CCopasiRootContainer::getKeyFactory()->get(key);

  if (pObject == NULL &&
      action != ListViews::DELETE)
    {
      return false;
    }

  QString DisplayRole;

  if (pObject != NULL)
    {
      // We have a key we can there fore determine the display role.
      DisplayRole = FROM_UTF8(pObject->getObjectName());

      // Species need to be handled differently
      const CMetab * pMetab = dynamic_cast< const CMetab *>(pObject);

      if (pMetab != NULL)
        {
          const CModel * pModel = pMetab->getModel();

          if (pModel != NULL)
            {
              DisplayRole = FROM_UTF8(CMetabNameInterface::getDisplayName(pModel, *pMetab, false));
            }
        }
    }

  switch (action)
    {
      case ListViews::RENAME:
      case ListViews::CHANGE:

        switch (objectType)
          {
            case ListViews::COMPARTMENT:
            case ListViews::METABOLITE:
            case ListViews::REACTION:
            case ListViews::MODELVALUE:
            case ListViews::EVENT:
            case ListViews::PLOT:
            case ListViews::REPORT:
            case ListViews::FUNCTION:
            case ListViews::LAYOUT:
            case ListViews::PARAMETERSET:
              rename(key, DisplayRole);
              break;

            default:
              break;
          }

        break;

      case ListViews::DELETE:

        // TODO CRITICAL We need to be smarter when deleting objects
        switch (objectType)
          {
            case ListViews::COMPARTMENT:
            case ListViews::METABOLITE:
            case ListViews::REACTION:
            case ListViews::MODELVALUE:
            case ListViews::EVENT:
            case ListViews::PLOT:
            case ListViews::REPORT:
            case ListViews::FUNCTION:
            case ListViews::LAYOUT:
            case ListViews::PARAMETERSET:
              remove(key);
              break;


            default:
              break;
          }

        break;

      case ListViews::ADD:
      {
        switch (objectType)
          {
            case ListViews::MODEL:
              load();
              break;

            case ListViews::COMPARTMENT:
              add(C_INVALID_INDEX, key, DisplayRole, 111);
              break;

            case ListViews::METABOLITE:
              add(C_INVALID_INDEX, key, DisplayRole, 112);
              break;

            case ListViews::REACTION:
              add(C_INVALID_INDEX, key, DisplayRole, 114);
              break;

            case ListViews::MODELVALUE:
              add(C_INVALID_INDEX, key, DisplayRole, 115);
              break;

            case ListViews::EVENT:
              add(C_INVALID_INDEX, key, DisplayRole, 116);
              break;

            case ListViews::PLOT:
              add(C_INVALID_INDEX, key, DisplayRole, 42);
              break;

            case ListViews::REPORT:
              add(C_INVALID_INDEX, key, DisplayRole, 43);
              break;

            case ListViews::FUNCTION:
              add(C_INVALID_INDEX, key, DisplayRole, 5);
              break;

            default:
              break;
          }
      }
      break;
    }

  return true;
}


QModelIndex CQBrowserPaneDM::index(CQBrowserPaneDM::CNode * pNode) const
{
  if (pNode == NULL)
    {
      return QModelIndex();
    }

  if (pNode == mpRoot)
    {
      return index(0, 0, QModelIndex());
    }

  QModelIndex Parent = index(static_cast< CNode * >(pNode->getParent()));

  return index(pNode->getRow(), 0, Parent);
}

CQBrowserPaneDM::CNode * CQBrowserPaneDM::nodeFromIndex(const QModelIndex & index)
{
  if (!index.isValid()) return NULL;

  QModelIndex Tmp = index;
  const QAbstractItemModel *pModel = Tmp.model();

  while (pModel->inherits("QSortFilterProxyModel"))
    {
      Tmp = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(index);
      pModel = Tmp.model();
    }

  return static_cast< CNode * >(Tmp.internalPointer());
}

void CQBrowserPaneDM::createStaticDM()
{
  mpRoot = new CNode(0, "", "COPASI", NULL);

  std::stringstream in;
  in.str(DataModeltxt);

  std::string str1;
  std::string delimiter("\x0a\x0d");
  char c;

  while (!in.eof())
    {
      str1 = "";

      while (!in.fail())
        {
          in.get(c);

          if (delimiter.find(c) != std::string::npos) break;

          str1 += c;
        }

      if (str1 == "") break;

      QString data(FROM_UTF8(str1));

      int first = data.indexOf(':');
      int second = data.indexOf(':', first + 1);
      int parentId = data.mid(0, first).toInt();
      int myId = data.mid(first + 1, second - first - 1).toInt();
      QString str = data.mid(second + 1, data.length() - second - 1);

      CNode * pParent = NULL;

      if (parentId == 0)
        {
          switch (myId)
            {
              case 1:
                pParent = (mFlags & Model) ? mpRoot : NULL;
                break;

              case 2:
                pParent = (mFlags & Tasks) ? mpRoot : NULL;
                break;

              case 4:
                pParent = (mFlags & Output) ? mpRoot : NULL;
                break;

              case 5:
                pParent = (mFlags & FunctionDB) ? mpRoot : NULL;
                break;
            }
        }
      else
        {
          pParent = this->findNodeFromId(parentId);
        }

      if (pParent != NULL)
        {
          new CNode(myId, "", str, pParent);
        }
    }
}

void CQBrowserPaneDM::clear()
{
  findNodeFromId(111)->deleteChildren(); // Compartment
  findNodeFromId(112)->deleteChildren(); // Species
  findNodeFromId(114)->deleteChildren(); // Reactions
  findNodeFromId(115)->deleteChildren(); // Global Quantities
  findNodeFromId(116)->deleteChildren(); // Events
  findNodeFromId(42)->deleteChildren(); // Plot Specifications
  findNodeFromId(43)->deleteChildren(); // Report Specifications
  findNodeFromId(5)->deleteChildren(); // Functions
}


CQBrowserPaneDM::CNode::CNode():
    CCopasiNode< CQBrowserPaneDM::SData >()
{}

CQBrowserPaneDM::CNode::CNode(const size_t & id,
                              const std::string & key,
                              const QString & displayRole,
                              CNode * pParent):
    CCopasiNode< CQBrowserPaneDM::SData >(pParent)
{
  mData.mId = id;
  mData.mKey = key;
  mData.mDisplayRole = displayRole;

  if (pParent != NULL)
    {
      pParent->addChild(this);
    }
}

CQBrowserPaneDM::CNode::~CNode()
{}

const size_t & CQBrowserPaneDM::CNode::getId() const
{
  return mData.mId;
}

void CQBrowserPaneDM::CNode::setDisplayRole(const QString & displayRole)
{
  mData.mDisplayRole = displayRole;
}

const QString & CQBrowserPaneDM::CNode::getDisplayRole() const
{
  return mData.mDisplayRole;
}

QString CQBrowserPaneDM::CNode::getSortRole() const
{
  if (mData.mId == C_INVALID_INDEX)
    {
      return mData.mDisplayRole;
    }

  return QString::number(mData.mId);
}

void CQBrowserPaneDM::CNode::setKey(const std::string & key)
{
  mData.mKey = key;
}

const std::string & CQBrowserPaneDM::CNode::getKey() const
{
  return mData.mKey;
}

int CQBrowserPaneDM::CNode::getRow() const
{
  int count = 0;

  const CCopasiNode< CQBrowserPaneDM::SData > * pParent = getParent();

  if (pParent == NULL)
    {
      return 0;
    }

  const CCopasiNode< CQBrowserPaneDM::SData > * pChild = pParent->getChild();

  while (pChild != NULL && pChild != this)
    {
      count++;
      pChild = pChild->getSibling();
    }

  return (pChild != NULL) ? count : -1;
}

std::ostream & operator<<(std::ostream &os, const CQBrowserPaneDM::CNode & n)
{
  os << "CQBrowserPaneDM::CNode:" << std::endl;
  //os << "   mChemicalEquation:          " << d.getChemicalEquation() << std::endl;
  //os << "   mChemicalEquationConverted: " << d.getChemicalEquationConverted() << std::endl;

  os << "   mId:          " << n.mData.mId << std::endl;
  os << "   mKey:         " << n.mData.mKey << std::endl;
  os << "   mDisplayRole: " << TO_UTF8(n.mData.mDisplayRole) << std::endl;
  return os;
}
