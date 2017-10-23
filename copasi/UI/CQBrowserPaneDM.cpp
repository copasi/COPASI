// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "CQBrowserPaneDM.h"
#include "DataModel.txt.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"
#include <QMessageBox>
#include <QCommonStyle>

#include "utilities/CCopasiTree.h"
#include "CopasiDataModel/CDataModel.h"
#include "model/CModel.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CUnit.h"
#include "report/CReportDefinitionVector.h"
#include "plot/COutputDefinitionVector.h"
#include "copasi/core/CRootContainer.h"
#include "commandline/CConfigurationFile.h"
#include "function/CFunctionDB.h"
#include "model/CMetabNameInterface.h"
#include "resourcesUI/CQIconResource.h"
#include "UI/copasiui3window.h"

CQBrowserPaneDM::CQBrowserPaneDM(QObject * pParent):
  QAbstractItemModel(pParent),
  mpRoot(NULL),
  mpCopasiDM(NULL),
  mpGuiDM(NULL),
  mEmitDataChanged(true),
  mFlags(CQBrowserPaneDM::Model | CQBrowserPaneDM::Tasks | CQBrowserPaneDM::Output | CQBrowserPaneDM::FunctionDB | CQBrowserPaneDM::Units),
  mSeverityFilter(), // All flags should be off,
  mKindFilter()      // with default constructor
{
  createStaticDM();

  connect(dynamic_cast<CopasiUI3Window *>(CopasiUI3Window::getMainWindow()), SIGNAL(signalPreferenceUpdated()), this, SLOT(slotRefreshValidityFilters()));
  slotRefreshValidityFilters();
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
      case Qt::DecorationRole:
        if (mKindFilter != mKindFilter.None)
          return getObjectIssueIcon(pNode);

        break;

      case Qt::ToolTipRole:
        if (mKindFilter != mKindFilter.None)
          return getObjectIssueMessages(pNode);

        break;

      case Qt::DisplayRole:

        // We need to add the number of children to some nodes.
        switch (pNode->getId())
          {
            case 5:
            case 6:
            case 42:
            case 43:
            case 111:
            case 112:
            case 114:
            case 115:
            case 116:
            case 119:
              return QVariant(pNode->getDisplayRole() + " [" + QString::number(pNode->getNumChildren()) + "]");
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

  // if there is nothing to delete, don't
  if (row + count - 1 < row) return false;

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
    }

  if (mEmitDataChanged)
    {
      QModelIndex Index = index(pNode);
      emit dataChanged(Index, Index);

      Index = index(static_cast< CNode * >(pNode->getParent()));
      emit dataChanged(Index, Index);
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
  CNode * pNode = new CNode(id, key, displayRole, pParent);
  endInsertRows();

  if (mEmitDataChanged)
    {
      QModelIndex Index = index(pNode);
      emit dataChanged(Index, Index);

      Index = index(static_cast< CNode * >(pNode->getParent()));
      emit dataChanged(Index, Index);
    }
}

void CQBrowserPaneDM::setCopasiDM(const CDataModel * pDataModel)
{
  mpCopasiDM = pDataModel;

  mEmitDataChanged = false;

  clear();
  load();

  dataChanged(index(0, 0), index(0, 0));

  mEmitDataChanged = true;
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

  // Still setting keys in here, rather than setObject(), for now because they may still be needed
  // where keys are in use (e.g. listviews slotFolderChanged()

  findNodeFromId(118)->setKey(mpCopasiDM->getModel()->getActiveModelParameterSet().getKey()); // Parameter Set
  load(119); // Model Parameter Sets

  findNodeFromId(21)->setKey(mpCopasiDM->getTaskList()->operator[]("Steady-State").getKey());
  findNodeFromId(221)->setKey(mpCopasiDM->getTaskList()->operator[]("Elementary Flux Modes").getKey());
  findNodeFromId(222)->setKey(mpCopasiDM->getTaskList()->operator[]("Moieties").getKey());
  findNodeFromId(2221)->setKey(mpCopasiDM->getTaskList()->operator[]("Moieties").getKey());
  findNodeFromId(23)->setKey(mpCopasiDM->getTaskList()->operator[]("Time-Course").getKey());
  findNodeFromId(24)->setKey(mpCopasiDM->getTaskList()->operator[]("Metabolic Control Analysis").getKey());
  findNodeFromId(27)->setKey(mpCopasiDM->getTaskList()->operator[]("Time Scale Separation Analysis").getKey());
  findNodeFromId(26)->setKey(mpCopasiDM->getTaskList()->operator[]("Lyapunov Exponents").getKey());
  findNodeFromId(28)->setKey(mpCopasiDM->getTaskList()->operator[]("Cross Section").getKey());

#ifdef WITH_ANALYTICS
  findNodeFromId(29)->setKey(mpCopasiDM->getTaskList()->operator[]("Analytics").getKey());
#endif // WITH_ANALYTICS

  findNodeFromId(31)->setKey(mpCopasiDM->getTaskList()->operator[]("Scan").getKey());
  findNodeFromId(32)->setKey(mpCopasiDM->getTaskList()->operator[]("Optimization").getKey());
  findNodeFromId(33)->setKey(mpCopasiDM->getTaskList()->operator[]("Parameter Estimation").getKey());
  findNodeFromId(34)->setKey(mpCopasiDM->getTaskList()->operator[]("Sensitivities").getKey());
  findNodeFromId(35)->setKey(mpCopasiDM->getTaskList()->operator[]("Linear Noise Approximation").getKey());

  findNodeFromId(42)->setKey(mpCopasiDM->getPlotDefinitionList()->getKey());
  load(42); // Plot Specifications

  findNodeFromId(43)->setKey(mpCopasiDM->getReportDefinitionList()->getKey());
  load(43); // Report Specifications

  load(5); // Functions

  load(6); //Units

  dataChanged(index(0, 0), index(0, 0));
}

void CQBrowserPaneDM::load(const size_t & id)
{
  bool isSpecies = false;
  const CModel * pModel = mpCopasiDM->getModel();
  const CDataVector< CDataObject > * pVector = NULL;

  switch (id)
    {
      case 111: // Compartment
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getCompartments());
        break;

      case 112: // Species
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getMetabolites());
        isSpecies = true;
        break;

      case 114: // Reactions
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getReactions());
        break;

      case 115: // Global Quantities
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getModelValues());
        break;

      case 116: // Events
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getEvents());
        break;

      case 119: // Parameter Sets
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getModelParameterSets());
        break;

      case 42: // Plot Specifications
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(mpCopasiDM->getPlotDefinitionList());
        break;

      case 43: // Report Specifications
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(mpCopasiDM->getReportDefinitionList());
        break;

      case 5: // Functions
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&CRootContainer::getFunctionList()->loadedFunctions());
        break;

      case 6: // Units
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(CRootContainer::getUnitList());
        break;

      default:
        return;
        break;
    }

  // We need to compare the existing nodes with the COPASI data model objects.
  CNode * pParent = findNodeFromId(id);
  pParent->setObject(pVector);
  CCopasiNode< CQBrowserPaneDM::SData > * pChildData = pParent->CCopasiNode< CQBrowserPaneDM::SData >::getChild();
  CDataVector< CDataObject >::const_iterator it = pVector->begin();
  CDataVector< CDataObject >::const_iterator end = pVector->end();

  bool changed = false;

  for (; pChildData != NULL && it != end; pChildData = pChildData->getSibling(), ++it)
    {
      CNode * pChild = static_cast< CNode *>(pChildData);

      pChild->setKey(it->getKey()); //Some things may currently still use key (e.g. listviews slotFolderChanged)
      pChild->setObject(it);

      QString DisplayRole;

      if (isSpecies)
        {
          DisplayRole = FROM_UTF8(CMetabNameInterface::getDisplayName(pModel, *static_cast<const CMetab * >(static_cast<const CDataObject * >(it)), false));
        }
      else
        {
          DisplayRole = FROM_UTF8(it->getObjectName());
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
      size_t current = pVector->getIndex(it);
      int last = first + (pVector->size() - current) - 1;
      // used to be
      //int last = first + (end - it) - 1;

      beginInsertRows(index(pParent), first, last);

      for (; it != end; ++it)
        {
          QString DisplayRole;

          if (isSpecies)
            {
              DisplayRole = FROM_UTF8(CMetabNameInterface::getDisplayName(pModel, *static_cast<const CMetab * >(static_cast<const CDataObject * >(it)), false));
            }
          else
            {
              DisplayRole = FROM_UTF8(it->getObjectName());
            }

          new CNode(C_INVALID_INDEX, it->getKey(), DisplayRole, pParent);
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

  const CDataObject * pObject = CRootContainer::getKeyFactory()->get(key);

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
            case ListViews::MODELPARAMETERSET:
            case ListViews::UNIT:
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
            case ListViews::MODELPARAMETERSET:
            case ListViews::UNIT:
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

            case ListViews::MODELPARAMETERSET:
              add(C_INVALID_INDEX, key, DisplayRole, 119);
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

            case ListViews::UNIT:
              add(C_INVALID_INDEX, key, DisplayRole, 6);
              break;

            default:
              break;
          }
      }
      break;
    }

  return true;
}

void CQBrowserPaneDM::slotRefreshValidityFilters()
{
  mSeverityFilter.reset();

  CCopasiParameterGroup::index_iterator it =
    CRootContainer::getConfiguration()->getGroup("Display Issue Severity")->beginIndex();
  CCopasiParameterGroup::index_iterator end =
    CRootContainer::getConfiguration()->getGroup("Display Issue Severity")->endIndex();

  for (; it != end; it++) //skip the "success" flag
    {
      if ((*it)->getValue< bool >())
        mSeverityFilter |= CIssue::severityNames.toEnum((*it)->getObjectName(), CIssue::eSeverity::__SIZE);
    }

  mKindFilter.reset();

  it = CRootContainer::getConfiguration()->getGroup("Display Issue Kinds")->beginIndex();
  end = CRootContainer::getConfiguration()->getGroup("Display Issue Kinds")->endIndex();

  for (; it != end; it++)
    {
      if ((*it)->getValue< bool >())
        mKindFilter |= CIssue::kindNames.toEnum((*it)->getObjectName(), CIssue::eKind::__SIZE);
    }
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

              case 6:
                pParent = (mFlags & Units) ? mpRoot : NULL;
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
  static const size_t NodeIndex[] = {111, 112, 114, 115, 116, 119, 42, 43, 5, 6, C_INVALID_INDEX};

  for (const size_t * pNodeIndex = NodeIndex; *pNodeIndex != C_INVALID_INDEX; ++pNodeIndex)
    {
      CNode * pNode = findNodeFromId(*pNodeIndex);

      removeRows(0, pNode->getNumChildren(), index(pNode));
      pNode->setObject(NULL);
    }
}

QString CQBrowserPaneDM::getObjectIssueMessages(const CNode * pNode) const
{
  QString objectIssueMessages;

  const CDataObject * pObject = (pNode->getKey().empty()) ? pNode->getObject() : CRootContainer::getKeyFactory()->get(pNode->getKey());

  if (pObject == NULL)
    return objectIssueMessages;

  CValidity validity = pObject->getValidity();;

  if (mKindFilter != mKindFilter.None)
    objectIssueMessages = QString(FROM_UTF8(validity.getIssueMessages(mSeverityFilter, mKindFilter)));

  return objectIssueMessages;
}

QIcon CQBrowserPaneDM::getObjectIssueIcon(const CNode * pNode) const
{
  QIcon highestSeveryityIcon;

  const CDataObject * pObject = (pNode->getKey().empty()) ? pNode->getObject() : CRootContainer::getKeyFactory()->get(pNode->getKey());

  if (pObject == NULL)
    return highestSeveryityIcon;

  const CValidity & validity = pObject->getValidity();

  CIssue::eSeverity highestSeverity = validity.getHighestSeverity(mSeverityFilter, mKindFilter);

  QCommonStyle * tmpStyle = new QCommonStyle;

  switch (highestSeverity)
    {
      case CIssue::eSeverity::Error:
        if (mSeverityFilter.isSet(CIssue::eSeverity::Error))
          highestSeveryityIcon = tmpStyle->standardIcon(QStyle::SP_MessageBoxCritical);

        break;

      case CIssue::eSeverity::Warning:
        if (mSeverityFilter.isSet(CIssue::eSeverity::Warning))
          highestSeveryityIcon = tmpStyle->standardIcon(QStyle::SP_MessageBoxWarning);

        break;

      case CIssue::eSeverity::Information:
        if (mSeverityFilter.isSet(CIssue::eSeverity::Information))
          highestSeveryityIcon = tmpStyle->standardIcon(QStyle::SP_MessageBoxInformation);

        break;

      default:
        break;
    }

  delete tmpStyle;

  return highestSeveryityIcon;
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

void CQBrowserPaneDM::CNode::setObject(const CDataObject * pObject)
{
  mData.mpObject = pObject;
}

const std::string & CQBrowserPaneDM::CNode::getKey() const
{
  return mData.mKey;
}

const CDataObject * CQBrowserPaneDM::CNode::getObject() const
{
  return mData.mpObject;
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
