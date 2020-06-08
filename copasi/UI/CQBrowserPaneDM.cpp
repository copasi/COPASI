// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>

#include "copasi/copasi.h"

#include "CQBrowserPaneDM.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"
#include <QMessageBox>
#include <QCommonStyle>

#include "copasi/utilities/CCopasiTree.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/resourcesUI/CQIconResource.h"
#include "copasi/UI/copasiui3window.h"

// static
const CQBrowserPaneDM::sNodeInfo CQBrowserPaneDM::TreeInfo[] =
{
  // ParentWidget, Widget, WidgtName
  {ListViews::WidgetType::COPASI, ListViews::WidgetType::Model, "Model"},
  {ListViews::WidgetType::Model, ListViews::WidgetType::Biochemical, "Biochemical"},
  {ListViews::WidgetType::Biochemical, ListViews::WidgetType::Compartments, "Compartments"},
  {ListViews::WidgetType::Biochemical, ListViews::WidgetType::Species, "Species"},
  {ListViews::WidgetType::Biochemical, ListViews::WidgetType::Reactions, "Reactions"},
  {ListViews::WidgetType::Biochemical, ListViews::WidgetType::GlobalQuantities, "Global Quantities"},
  {ListViews::WidgetType::Biochemical, ListViews::WidgetType::Events, "Events"},
  {ListViews::WidgetType::Biochemical, ListViews::WidgetType::ParameterOverview, "Parameter Overview"},
  {ListViews::WidgetType::Biochemical, ListViews::WidgetType::ParameterSets, "Parameter Sets"},
  {ListViews::WidgetType::Model, ListViews::WidgetType::Mathematical, "Mathematical"},
#ifdef HAVE_MML
  {ListViews::WidgetType::Mathematical, ListViews::WidgetType::DifferentialEquations, "Differential Equations"},
#endif // HAVE_MML
  {ListViews::WidgetType::Mathematical, ListViews::WidgetType::Matrices, "Matrices"},
#ifdef COPASI_DEBUG
  {ListViews::WidgetType::Mathematical, ListViews::WidgetType::UpdateOrder, "Update Order"},
#endif // COPASI_DEBUG
  {ListViews::WidgetType::Model, ListViews::WidgetType::Diagrams, "Diagrams"},
  {ListViews::WidgetType::COPASI, ListViews::WidgetType::Tasks, "Tasks"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::SteadyState, "Steady-State"},
  {ListViews::WidgetType::SteadyState, ListViews::WidgetType::SteadyStateResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::StoichiometricAnalysis, "Stoichiometric Analysis"},
  {ListViews::WidgetType::StoichiometricAnalysis, ListViews::WidgetType::ElementaryModes, "Elementary Modes"},
  {ListViews::WidgetType::ElementaryModes, ListViews::WidgetType::ElementaryModesResult, "Result"},
  {ListViews::WidgetType::StoichiometricAnalysis, ListViews::WidgetType::MassConservation, "Mass Conservation"},
  {ListViews::WidgetType::MassConservation, ListViews::WidgetType::MassConservationResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::TimeCourse, "Time Course"},
  {ListViews::WidgetType::TimeCourse, ListViews::WidgetType::TimeCourseResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::MetabolicControlAnalysis, "Metabolic Control Analysis"},
  {ListViews::WidgetType::MetabolicControlAnalysis, ListViews::WidgetType::MetabolicControlAnalysisResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::LyapunovExponents, "Lyapunov Exponents"},
  {ListViews::WidgetType::LyapunovExponents, ListViews::WidgetType::LyapunovExponentsResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::TimeScaleSeparationAnalysis, "Time Scale Separation Analysis"},
  {ListViews::WidgetType::TimeScaleSeparationAnalysis, ListViews::WidgetType::TimeScaleSeparationAnalysisResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::CrossSection, "Cross Section"},
  {ListViews::WidgetType::CrossSection, ListViews::WidgetType::CrossSectionResult, "Result"},
#ifdef WITH_ANALYTICS
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::Analytics, "Analytics"},
  {ListViews::WidgetType::Analytics, ListViews::WidgetType::AnalyticsResult, "Result"},
#endif // WITH_ANALYTICS
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::ParameterScan, "Parameter Scan"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::Optimization, "Optimization"},
  {ListViews::WidgetType::Optimization, ListViews::WidgetType::OptimizationResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::ParameterEstimation, "Parameter Estimation"},
  {ListViews::WidgetType::ParameterEstimation, ListViews::WidgetType::ParameterEstimationResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::Sensitivities, "Sensitivities"},
  {ListViews::WidgetType::Sensitivities, ListViews::WidgetType::SensitivitiesResult, "Result"},
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::LinearNoiseApproximation, "Linear Noise Approximation"},
  {ListViews::WidgetType::LinearNoiseApproximation, ListViews::WidgetType::LinearNoiseApproximationResult, "Result"},
#ifdef COPASI_NONLIN_DYN_OSCILLATION
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::Oscillation, "Oscillation "},
#endif
#ifdef WITH_TIME_SENS
  {ListViews::WidgetType::Tasks, ListViews::WidgetType::TimeCourseSensitivities, "Time Course Sensitivities"},
  {ListViews::WidgetType::TimeCourseSensitivities, ListViews::WidgetType::TimeCourseSensitivitiesResult, "Result"},
#endif // WITH_TIME_SENS
  {ListViews::WidgetType::COPASI, ListViews::WidgetType::OutputSpecifications, "Output Specifications"},
  {ListViews::WidgetType::OutputSpecifications, ListViews::WidgetType::Plots, "Plots"},
  {ListViews::WidgetType::OutputSpecifications, ListViews::WidgetType::ReportTemplates, "Report Templates"},
  {ListViews::WidgetType::COPASI, ListViews::WidgetType::Functions, "Functions"},
  {ListViews::WidgetType::COPASI, ListViews::WidgetType::Units, "Units"},
  {ListViews::WidgetType::NotFound, ListViews::WidgetType::NotFound, ""}
};

CQBrowserPaneDM::CQBrowserPaneDM(QObject * pParent):
  QAbstractItemModel(pParent),
  mpRoot(NULL),
  mpCopasiDM(NULL),
  mpGuiDM(NULL),
  mEmitDataChanged(true),
  mFlags(CQBrowserPaneDM::Model | CQBrowserPaneDM::Tasks | CQBrowserPaneDM::Output | CQBrowserPaneDM::FunctionDB | CQBrowserPaneDM::Units),
  mSeverityFilter(),
  mKindFilter(),
  mCN2Node(),
  mId2Node(),
  mpRenameHandler(NULL)
{
  createStaticDM();

  ListViews * pListView = NULL;

  while (pParent != NULL &&
         (pListView = dynamic_cast< ListViews * >(pParent)) == NULL)
    {
      pParent = pParent->parent();
    }

  if (pListView)
    {
      connect(pListView, SIGNAL(signalNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
              this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
    }

  connect(dynamic_cast<CopasiUI3Window *>(CopasiUI3Window::getMainWindow()), SIGNAL(signalPreferenceUpdated()), this, SLOT(slotRefreshValidityFilters()));

  slotRefreshValidityFilters();

  mpRenameHandler = new CRegisteredCommonName::ClassMemberRename< CQBrowserPaneDM >(this, &CQBrowserPaneDM::rename);
  CRegisteredCommonName::registerHandler(mpRenameHandler);
}

// virtual
CQBrowserPaneDM::~CQBrowserPaneDM()
{
  pdelete(mpRoot);

  CRegisteredCommonName::deregisterHandler(mpRenameHandler);
  pdelete(mpRenameHandler);
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
            case ListViews::WidgetType::Functions:
            case ListViews::WidgetType::Units:
            case ListViews::WidgetType::Plots:
            case ListViews::WidgetType::ReportTemplates:
            case ListViews::WidgetType::Compartments:
            case ListViews::WidgetType::Species:
            case ListViews::WidgetType::Reactions:
            case ListViews::WidgetType::GlobalQuantities:
            case ListViews::WidgetType::Events:
            case ListViews::WidgetType::ParameterSets:
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

QModelIndex CQBrowserPaneDM::index(const ListViews::WidgetType & id, const CCommonName & cn) const
{
  CNode * pNode = NULL;

  switch (id)
    {
      case ListViews::WidgetType::NotFound:
      case ListViews::WidgetType::FunctionDetail:
      case ListViews::WidgetType::UnitDetail:
      case ListViews::WidgetType::PlotDetail:
      case ListViews::WidgetType::ReportTemplateDetail:
      case ListViews::WidgetType::CompartmentDetail:
      case ListViews::WidgetType::SpeciesDetail:
      case ListViews::WidgetType::ReactionDetail:
      case ListViews::WidgetType::GlobalQuantityDetail:
      case ListViews::WidgetType::EventDetail:
      case ListViews::WidgetType::ParameterSetDetail:
        if (!cn.empty())
          {
            pNode = findNodeFromCN(cn);
          }

        break;

      default:
        pNode = findNodeFromId(id);
        break;
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

      destroyNode(pTmp);
    }

  endRemoveRows();

  return true;
}

CQBrowserPaneDM::CNode * CQBrowserPaneDM::findNodeFromId(const ListViews::WidgetType & id) const
{
  std::map< ListViews::WidgetType, CNode * >::const_iterator found = mId2Node.find(id);

  if (found != mId2Node.end())
    {
      return found->second;
    }

  return NULL;
}

CQBrowserPaneDM::CNode * CQBrowserPaneDM::findNodeFromCN(const CCommonName & cn) const
{
  std::map< std::string, CNode * >::const_iterator found = mCN2Node.find(cn);

  if (found != mCN2Node.end())
    {
      return found->second;
    }

  CCopasiTree< CNode >::iterator it = mpRoot;
  CCopasiTree< CNode >::iterator end;

  for (; it != end; ++it)
    {
      if (it->getData().mCN == cn)
        {
          return &*it;
        }
    }

  return NULL;
}

ListViews::WidgetType CQBrowserPaneDM::getIdFromIndex(const QModelIndex & index) const
{
  CNode * pNode = nodeFromIndex(index);

  if (pNode == NULL) return ListViews::WidgetType::NotFound;

  return pNode->getId();
}

const CCommonName & CQBrowserPaneDM::getCNFromIndex(const QModelIndex & index) const
{
  static CCommonName EmptyCN;
  CNode * pNode = nodeFromIndex(index);

  if (pNode == NULL) return EmptyCN;

  return pNode->getCN();
}

void CQBrowserPaneDM::remove(CNode * pNode)
{
  if (pNode == NULL || pNode->getParent() == NULL)
    {
      return;
    }

  QModelIndex Parent = index(static_cast< CNode * >(pNode->getParent()));

  removeRows(pNode->getRow(), 1, Parent);
}

void CQBrowserPaneDM::add(const ListViews::WidgetType & id,
                          const CCommonName & cn,
                          const QString & displayRole,
                          const ListViews::WidgetType & parentId)
{
  CNode * pParent = findNodeFromId(parentId);
  int row = 0;

  if (pParent != NULL)
    {
      row = pParent->getNumChildren();
    }

  beginInsertRows(index(pParent), row, row);
  CNode * pNode = createNode(id, cn, displayRole, 0, pParent);
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
  /*
  if (mpGuiDM)
    {
      disconnect(mpGuiDM, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
                 this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
    }

  mpGuiDM = pDataModel;

  if (mpGuiDM)
    {
      connect(mpGuiDM, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
              this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
    }
  */
}

void CQBrowserPaneDM::load()
{
  updateNode(findNodeFromId(ListViews::WidgetType::Model), mpCopasiDM->getModel()->getCN());

  load(ListViews::WidgetType::Compartments); // Compartment
  load(ListViews::WidgetType::Species); // Species
  load(ListViews::WidgetType::Reactions); // Reactions
  load(ListViews::WidgetType::GlobalQuantities); // Global Quantities
  load(ListViews::WidgetType::Events); // Events

  // Still setting CNs in here, rather than setObject(), for now because they may still be needed
  // where CNs are in use (e.g. listviews slotFolderChanged()

  updateNode(findNodeFromId(ListViews::WidgetType::ParameterOverview), mpCopasiDM->getModel()->getActiveModelParameterSet().CDataObject::getCN()); // Parameter Set
  load(ListViews::WidgetType::ParameterSets); // Model Parameter Sets

  updateNode(findNodeFromId(ListViews::WidgetType::SteadyState), mpCopasiDM->getTaskList()->operator[]("Steady-State").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::ElementaryModes), mpCopasiDM->getTaskList()->operator[]("Elementary Flux Modes").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::MassConservation), mpCopasiDM->getTaskList()->operator[]("Moieties").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::MassConservationResult), mpCopasiDM->getTaskList()->operator[]("Moieties").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::TimeCourse), mpCopasiDM->getTaskList()->operator[]("Time-Course").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::MetabolicControlAnalysis), mpCopasiDM->getTaskList()->operator[]("Metabolic Control Analysis").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::TimeScaleSeparationAnalysis), mpCopasiDM->getTaskList()->operator[]("Time Scale Separation Analysis").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::LyapunovExponents), mpCopasiDM->getTaskList()->operator[]("Lyapunov Exponents").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::CrossSection), mpCopasiDM->getTaskList()->operator[]("Cross Section").getCN());

#ifdef WITH_ANALYTICS
  updateNode(findNodeFromId(ListViews::WidgetType::Analytics), mpCopasiDM->getTaskList()->operator[]("Analytics").getCN());
#endif // WITH_ANALYTICS

#ifdef WITH_TIME_SENS
  updateNode(findNodeFromId(ListViews::WidgetType::TimeCourseSensitivities), mpCopasiDM->getTaskList()->operator[]("Time-Course Sensitivities").getCN());
#endif // WITH_TIME_SENS

  updateNode(findNodeFromId(ListViews::WidgetType::ParameterScan), mpCopasiDM->getTaskList()->operator[]("Scan").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::Optimization), mpCopasiDM->getTaskList()->operator[]("Optimization").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::ParameterEstimation), mpCopasiDM->getTaskList()->operator[]("Parameter Estimation").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::Sensitivities), mpCopasiDM->getTaskList()->operator[]("Sensitivities").getCN());
  updateNode(findNodeFromId(ListViews::WidgetType::LinearNoiseApproximation), mpCopasiDM->getTaskList()->operator[]("Linear Noise Approximation").getCN());

  updateNode(findNodeFromId(ListViews::WidgetType::Plots), mpCopasiDM->getPlotDefinitionList()->getCN());
  load(ListViews::WidgetType::Plots); // Plot Specifications

  updateNode(findNodeFromId(ListViews::WidgetType::ReportTemplates), mpCopasiDM->getReportDefinitionList()->getCN());
  load(ListViews::WidgetType::ReportTemplates); // Report Specifications

  load(ListViews::WidgetType::Functions); // Functions

  load(ListViews::WidgetType::Units); //Units

  dataChanged(index(0, 0), index(0, 0));
}

void CQBrowserPaneDM::load(const ListViews::WidgetType & id)
{
  const CModel * pModel = mpCopasiDM->getModel();
  const CDataVector< CDataObject > * pVector = NULL;
  ListViews::WidgetType ChildId = ListViews::WidgetType::Model;

  switch (id)
    {
      case ListViews::WidgetType::Compartments: // Compartment
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getCompartments());
        ChildId = ListViews::WidgetType::CompartmentDetail;
        break;

      case ListViews::WidgetType::Species: // Species
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getMetabolites());
        ChildId = ListViews::WidgetType::SpeciesDetail;
        break;

      case ListViews::WidgetType::Reactions: // Reactions
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getReactions());
        ChildId = ListViews::WidgetType::ReactionDetail;
        break;

      case ListViews::WidgetType::GlobalQuantities: // Global Quantities
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getModelValues());
        ChildId = ListViews::WidgetType::GlobalQuantityDetail;
        break;

      case ListViews::WidgetType::Events: // Events
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getEvents());
        ChildId = ListViews::WidgetType::EventDetail;
        break;

      case ListViews::WidgetType::ParameterSets: // Parameter Sets
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&pModel->getModelParameterSets());
        ChildId = ListViews::WidgetType::ParameterSetDetail;
        break;

      case ListViews::WidgetType::Plots: // Plot Specifications
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(mpCopasiDM->getPlotDefinitionList());
        ChildId = ListViews::WidgetType::PlotDetail;
        break;

      case ListViews::WidgetType::ReportTemplates: // Report Specifications
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(mpCopasiDM->getReportDefinitionList());
        ChildId = ListViews::WidgetType::ReportTemplateDetail;
        break;

      case ListViews::WidgetType::Functions: // Functions
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(&CRootContainer::getFunctionList()->loadedFunctions());
        ChildId = ListViews::WidgetType::FunctionDetail;
        break;

      case ListViews::WidgetType::Units: // Units
        pVector = reinterpret_cast< const CDataVector< CDataObject > * >(CRootContainer::getUnitList());
        ChildId = ListViews::WidgetType::UnitDetail;
        break;

      default:
        return;
        break;
    }

  // We need to compare the existing nodes with the COPASI data model objects.
  CNode * pParent = findNodeFromId(id);
  updateNode(pParent, pVector->getCN());

  CCopasiNode< CQBrowserPaneDM::SData > * pChildData = pParent->CCopasiNode< CQBrowserPaneDM::SData >::getChild();
  CDataVector< CDataObject >::const_iterator it = pVector->begin();
  CDataVector< CDataObject >::const_iterator end = pVector->end();

  bool changed = false;

  for (; pChildData != NULL && it != end; pChildData = pChildData->getSibling(), ++it)
    {
      CNode * pChild = static_cast< CNode *>(pChildData);
      updateNode(pChild, it->getCN()); //Some things may currently still use key (e.g. listviews slotFolderChanged)

      QString DisplayRole;

      if (ChildId == ListViews::WidgetType::SpeciesDetail)
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

          if (ChildId == ListViews::WidgetType::SpeciesDetail)
            {
              DisplayRole = FROM_UTF8(CMetabNameInterface::getDisplayName(pModel, *static_cast<const CMetab * >(static_cast<const CDataObject * >(it)), false));
            }
          else
            {
              DisplayRole = FROM_UTF8(it->getObjectName());
            }

          createNode(ChildId, it->getCN(), DisplayRole, 0, pParent);
        }

      endInsertRows();
    }

  if (changed && mEmitDataChanged)
    {
      QModelIndex Parent = index(pParent);

      emit dataChanged(Parent, Parent);
    }
}

void CQBrowserPaneDM::rename(const std::string & oldCN, const std::string & newCN)
{
  if (oldCN == newCN) return;

  std::map< std::string, CNode * >::iterator found = mCN2Node.find(oldCN);

  if (found == mCN2Node.end()) return;

  CNode * pNode = found->second;
  mCN2Node.erase(found);

  if (pNode == NULL) return;

  mCN2Node[newCN] = pNode;

  switch (pNode->getId())
    {
      case ListViews::WidgetType::CompartmentDetail:
      case ListViews::WidgetType::SpeciesDetail:
      case ListViews::WidgetType::ReactionDetail:
      case ListViews::WidgetType::GlobalQuantityDetail:
      case ListViews::WidgetType::EventDetail:
      case ListViews::WidgetType::ParameterSetDetail:
      case ListViews::WidgetType::PlotDetail:
      case ListViews::WidgetType::ReportTemplateDetail:
      case ListViews::WidgetType::FunctionDetail:
      case ListViews::WidgetType::UnitDetail:
        break;

      default:
        // No modification of the display role allowed.
        return;
        break;
    }

  // Fetch the object by it's CN
  CObjectInterface::ContainerList List;
  List.push_back(mpCopasiDM);
  const CDataObject * pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, pNode->getCN()));

  if (pObject == NULL) return;

  // We have an object CN we can therefore determine the display role.
  QString DisplayRole = FROM_UTF8(pObject->getObjectName());

  const CMetab * pMetab = dynamic_cast< const CMetab * >(pObject);

  if (pMetab != NULL)
    {
      const CModel * pModel = pMetab->getModel();

      if (pModel != NULL)
        {
          DisplayRole = FROM_UTF8(CMetabNameInterface::getDisplayName(pModel, *pMetab, false));
        }
    }

  if (DisplayRole != pNode->getDisplayRole())
    {
      pNode->setDisplayRole(DisplayRole);

      if (mEmitDataChanged)
        {
          QModelIndex Index = index(pNode);
          emit dataChanged(Index, Index);

          Index = index(static_cast< CNode * >(pNode->getParent()));
          emit dataChanged(Index, Index);
        }
    }
}

bool CQBrowserPaneDM::slotNotify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (mpCopasiDM == NULL)
    {
      return false;
    }

  if (cn == "")
    {
      // Load is only reporting actual changes.
      load();
      return true;
    }

  // Assure that the object still exists
  CObjectInterface::ContainerList List;
  List.push_back(mpCopasiDM);

  CNode * pNode = NULL;

  if (action != ListViews::ADD)
    {
      // The CN might point to the old name (before rename or move). The new CN can be retrieved from the corresponding node
      pNode = findNodeFromCN(cn);
    }

  std::string NewCN = pNode != NULL ? pNode->getCN() : cn;

  if (cn != NewCN)
    {
      mCN2Node.erase(cn);
      mCN2Node[NewCN] = pNode;
    }

  // This will check the current data model and the root container for the object;
  const CDataObject * pObject = const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, NewCN)));

  if (pObject == NULL &&
      action != ListViews::DELETE)
    {
      return false;
    }

  QString DisplayRole;

  if (pObject != NULL)
    {
      // We have a CN we can therefore determine the display role.
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
        break;

      case ListViews::DELETE:

        // TODO CRITICAL We need to be smarter when deleting objects
        switch (objectType)
          {
            case ListViews::ObjectType::COMPARTMENT:
            case ListViews::ObjectType::METABOLITE:
            case ListViews::ObjectType::REACTION:
            case ListViews::ObjectType::MODELVALUE:
            case ListViews::ObjectType::EVENT:
            case ListViews::ObjectType::PLOT:
            case ListViews::ObjectType::REPORT:
            case ListViews::ObjectType::FUNCTION:
            case ListViews::ObjectType::LAYOUT:
            case ListViews::ObjectType::MODELPARAMETERSET:
            case ListViews::ObjectType::UNIT:
              remove(pNode);
              break;

            default:
              break;
          }

        break;

      case ListViews::ADD:
      {
        switch (objectType)
          {
            case ListViews::ObjectType::MODEL:
              load();
              break;

            case ListViews::ObjectType::COMPARTMENT:
              add(ListViews::WidgetType::CompartmentDetail, cn, DisplayRole, ListViews::WidgetType::Compartments);
              break;

            case ListViews::ObjectType::METABOLITE:
              add(ListViews::WidgetType::SpeciesDetail, cn, DisplayRole, ListViews::WidgetType::Species);
              break;

            case ListViews::ObjectType::REACTION:
              add(ListViews::WidgetType::ReactionDetail, cn, DisplayRole, ListViews::WidgetType::Reactions);
              break;

            case ListViews::ObjectType::MODELVALUE:
              add(ListViews::WidgetType::GlobalQuantityDetail, cn, DisplayRole, ListViews::WidgetType::GlobalQuantities);
              break;

            case ListViews::ObjectType::EVENT:
              add(ListViews::WidgetType::EventDetail, cn, DisplayRole, ListViews::WidgetType::Events);
              break;

            case ListViews::ObjectType::MODELPARAMETERSET:
              add(ListViews::WidgetType::ParameterSetDetail, cn, DisplayRole, ListViews::WidgetType::ParameterSets);
              break;

            case ListViews::ObjectType::PLOT:
              add(ListViews::WidgetType::PlotDetail, cn, DisplayRole, ListViews::WidgetType::Plots);
              break;

            case ListViews::ObjectType::REPORT:
              add(ListViews::WidgetType::ReportTemplateDetail, cn, DisplayRole, ListViews::WidgetType::ReportTemplates);
              break;

            case ListViews::ObjectType::FUNCTION:
              add(ListViews::WidgetType::FunctionDetail, cn, DisplayRole, ListViews::WidgetType::Functions);
              break;

            case ListViews::ObjectType::UNIT:
              add(ListViews::WidgetType::UnitDetail, cn, DisplayRole, ListViews::WidgetType::Units);
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

// static
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

CQBrowserPaneDM::CNode * CQBrowserPaneDM::createNode(const ListViews::WidgetType & id,
    const CCommonName & cn,
    const QString & displayRole,
    const size_t & sortOrder,
    CNode * pParent)
{
  CNode * pNode = new CNode(id, cn, displayRole, sortOrder, pParent);

  if (!cn.empty())
    {
      mCN2Node[cn] = pNode;
    }

  mId2Node[id] = pNode;

  return pNode;
}

void CQBrowserPaneDM::updateNode(CNode * pNode, const CCommonName & CN)
{
  if (pNode != NULL &&
      pNode->getCN() != CN)
    {
      mCN2Node.erase(pNode->getCN());
      mCN2Node[CN] = pNode;
      pNode->setCN(CN);
    }
}

void CQBrowserPaneDM::destroyNode(CNode * pNode)
{
  if (!pNode->getCN().empty())
    {
      std::map< std::string, CNode * >::iterator found = mCN2Node.find(pNode->getCN());

      if (found != mCN2Node.end() &&
          found->second == pNode)
        {
          mCN2Node.erase(found);
        }
    }

  std::map< ListViews::WidgetType, CNode * >::iterator found = mId2Node.find(pNode->getId());

  if (found != mId2Node.end() &&
      found->second == pNode)
    {
      mId2Node.erase(found);
    }

  delete pNode;
}

void CQBrowserPaneDM::createStaticDM()
{
  size_t SortKey = 0;
  mpRoot = createNode(ListViews::WidgetType::COPASI, std::string(), "COPASI", SortKey++, NULL);

  for (const sNodeInfo * pNodeInfo = TreeInfo; pNodeInfo->parent != ListViews::WidgetType::NotFound; ++pNodeInfo)
    {
      CNode * pParent = NULL;

      if (pNodeInfo->parent == ListViews::WidgetType::COPASI)
        {
          switch (pNodeInfo->node)
            {
              case ListViews::WidgetType::Model:
                pParent = (mFlags & Model) ? mpRoot : NULL;
                break;

              case ListViews::WidgetType::Tasks:
                pParent = (mFlags & Tasks) ? mpRoot : NULL;
                break;

              case ListViews::WidgetType::OutputSpecifications:
                pParent = (mFlags & Output) ? mpRoot : NULL;
                break;

              case ListViews::WidgetType::Functions:
                pParent = (mFlags & FunctionDB) ? mpRoot : NULL;
                break;

              case ListViews::WidgetType::Units:
                pParent = (mFlags & Units) ? mpRoot : NULL;
                break;
            }
        }
      else
        {
          pParent = this->findNodeFromId(pNodeInfo->parent);
        }

      if (pParent != NULL)
        {
          createNode(pNodeInfo->node, std::string(), FROM_UTF8(pNodeInfo->title), SortKey++, pParent);
        }
    }
}

void CQBrowserPaneDM::clear()
{
  static const ListViews::WidgetType NodeIndex[] =
  {
    ListViews::WidgetType::Compartments,
    ListViews::WidgetType::Species,
    ListViews::WidgetType::Reactions,
    ListViews::WidgetType::GlobalQuantities,
    ListViews::WidgetType::Events,
    ListViews::WidgetType::ParameterSets,
    ListViews::WidgetType::Plots,
    ListViews::WidgetType::ReportTemplates,
    ListViews::WidgetType::Functions,
    ListViews::WidgetType::Units,
    ListViews::WidgetType::COPASI
  };

  for (const ListViews::WidgetType * pNodeIndex = NodeIndex; *pNodeIndex != ListViews::WidgetType::COPASI; ++pNodeIndex)
    {
      CNode * pNode = findNodeFromId(*pNodeIndex);
      removeRows(0, pNode->getNumChildren(), index(pNode));
    }
}

QString CQBrowserPaneDM::getObjectIssueMessages(const CNode * pNode) const
{
  QString objectIssueMessages;

  const CDataObject * pObject = pNode->getObject(mpCopasiDM);

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

  const CDataObject * pObject = pNode->getObject(mpCopasiDM);

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

CQBrowserPaneDM::CNode::CNode(const ListViews::WidgetType & id,
                              const CCommonName & cn,
                              const QString & displayRole,
                              const size_t & sortOrder,
                              CNode * pParent):
  CCopasiNode< CQBrowserPaneDM::SData >(pParent)
{
  mData.mId = id;
  mData.mCN = cn;
  mData.mDisplayRole = displayRole;
  mData.mSortOrder = sortOrder;

  if (pParent != NULL)
    {
      pParent->addChild(this);
    }
}

CQBrowserPaneDM::CNode::~CNode()
{}

const ListViews::WidgetType & CQBrowserPaneDM::CNode::getId() const
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
  QString tmp("%1");

  switch (mData.mId)
    {
      case ListViews::WidgetType::FunctionDetail:
      case ListViews::WidgetType::UnitDetail:
      case ListViews::WidgetType::PlotDetail:
      case ListViews::WidgetType::ReportTemplateDetail:
      case ListViews::WidgetType::CompartmentDetail:
      case ListViews::WidgetType::SpeciesDetail:
      case ListViews::WidgetType::ReactionDetail:
      case ListViews::WidgetType::GlobalQuantityDetail:
      case ListViews::WidgetType::EventDetail:
      case ListViews::WidgetType::ParameterSetDetail:
        return mData.mDisplayRole;
        break;

      default:
        return QString("%1").arg(mData.mSortOrder, 4, 10, QChar('0'));
        break;
    }

  return QString();
}

void CQBrowserPaneDM::CNode::setCN(const CCommonName & cn)
{
  mData.mCN = cn;
}

const CCommonName & CQBrowserPaneDM::CNode::getCN() const
{
  return mData.mCN;
}

const CDataObject * CQBrowserPaneDM::CNode::getObject(const CDataModel * pDataModel) const
{
  CObjectInterface::ContainerList List;
  List.push_back(pDataModel);

  // This will check the current data model and the root container for the object;
  return CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, mData.mCN));
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

  os << "   mId:          " << (size_t) n.mData.mId << std::endl;
  os << "   mCN:          " << n.mData.mCN << std::endl;
  os << "   mDisplayRole: " << TO_UTF8(n.mData.mDisplayRole) << std::endl;
  return os;
}
