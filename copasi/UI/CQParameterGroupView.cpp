// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QSortFilterProxyModel>

#include "copasi/UI/CQParameterGroupView.h"
#include "copasi/UI/CQComboDelegate.h"
#include "copasi/UI/CQPushButtonDelegate.h"
#include "copasi/UI/CCopasiSelectionDialog.h"
#include "copasi/resourcesUI/CQIconResource.h"
#include "copasi/UI/copasiui3window.h"

#include "copasi/copasi.h"
#include "copasi/UI/qtUtilities.h"

#include "copasi/utilities/CCopasiParameterGroup.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/UI/CQParameterGroupDM.h"
#include "copasi/model/CObjectLists.h"
#include "copasi/utilities/utility.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

CQParameterGroupView::CQParameterGroupView(QWidget* parent):
  QTreeView(parent),
  mpParameterGroupDM(NULL),
  mpSortFilterDM(NULL),
  mpComboBoxDelegate(NULL),
  mpPushButtonDelegate(NULL)
{
  // create a new QListview to be displayed on the screen..and set its property
  mpParameterGroupDM = new CQParameterGroupDM(this);

  mpSortFilterDM = new QSortFilterProxyModel(this);
  mpSortFilterDM->setFilterKeyColumn(0);
  mpSortFilterDM->setFilterRole(Qt::UserRole + 1);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
  mpSortFilterDM->setFilterRegExp(CRootContainer::getConfiguration()->enableAdditionalOptimizationParameters() ? "" : "basic");
#else
  mpSortFilterDM->setFilterRegularExpression(CRootContainer::getConfiguration()->enableAdditionalOptimizationParameters() ? "" : "basic");
#endif
  mpSortFilterDM->setSourceModel(mpParameterGroupDM);
  mpSortFilterDM->setSortRole(Qt::UserRole + 2);
  mpSortFilterDM->sort(0, Qt::DescendingOrder);

  setSortingEnabled(true);
  setModel(mpSortFilterDM);

  mpComboBoxDelegate = new CQComboDelegate(this);
  mpPushButtonDelegate = new CQPushButtonDelegate(CQIconResource::icon(CQIconResource::copasi), QString(),
      CQPushButtonDelegate::ToolButton, this);

  connect(mpParameterGroupDM, SIGNAL(signalCreateComboBox(const QModelIndex &)), this, SLOT(slotCreateComboBox(const QModelIndex &)));
  connect(mpParameterGroupDM, SIGNAL(signalCreatePushButton(const QModelIndex &)), this, SLOT(slotCreatePushButton(const QModelIndex &)));
  connect(mpParameterGroupDM, SIGNAL(signalCloseEditor(const QModelIndex &)), this, SLOT(slotCloseEditor(const QModelIndex &)));
  connect(mpPushButtonDelegate, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotPushButtonClicked(const QModelIndex &)));
  connect(dynamic_cast<CopasiUI3Window *>(CopasiUI3Window::getMainWindow()), SIGNAL(signalPreferenceUpdated()), this, SLOT(slotPreferenceUpdated()));
}

CQParameterGroupView::~CQParameterGroupView()
{}

void CQParameterGroupView::setAdvanced(const bool & advanced)
{
  mpParameterGroupDM->setAdvanced(advanced);
}

void CQParameterGroupView::pushGroup(CCopasiParameterGroup * pGroup)
{
  mpParameterGroupDM->pushGroup(pGroup);

  this->expandAll();
  this->resizeColumnToContents(0);
}

void CQParameterGroupView::popGroup(CCopasiParameterGroup * pGroup)
{
  mpParameterGroupDM->popGroup(pGroup);

  this->expandAll();
  this->resizeColumnToContents(0);
}

void CQParameterGroupView::clearGroups()
{
  // We need to remove/reset all custom delegates
  QAbstractItemDelegate * pDefault = this->itemDelegate();

  for (int i = 0; i < mpParameterGroupDM->rowCount(); ++i)
    {
      this->setItemDelegateForRow(i, pDefault);
    }

  mpParameterGroupDM->clearGroups();
}

void CQParameterGroupView::slotPreferenceUpdated()
{
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
  mpSortFilterDM->setFilterRegExp(CRootContainer::getConfiguration()->enableAdditionalOptimizationParameters() ? "" : "basic");
#else
  mpSortFilterDM->setFilterRegularExpression(CRootContainer::getConfiguration()->enableAdditionalOptimizationParameters() ? "" : "basic");
#endif
}

void CQParameterGroupView::slotCreateComboBox(const QModelIndex & index)
{
  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  this->setItemDelegateForRow(Source.row(), mpComboBoxDelegate);
  this->openPersistentEditor(Source);
  this->expandAll();
}

void CQParameterGroupView::slotCreatePushButton(const QModelIndex & index)
{
  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  this->setItemDelegateForRow(Source.row(), mpPushButtonDelegate);
  this->openPersistentEditor(Source);
  this->expandAll();
}

void CQParameterGroupView::slotCloseEditor(const QModelIndex & index)
{
  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  if (this->itemDelegateForRow(Source.row()) != mpComboBoxDelegate) return;

  this->setItemDelegateForRow(Source.row(), this->itemDelegate());
  this->expandAll();
}

void CQParameterGroupView::slotPushButtonClicked(const QModelIndex & index)
{
  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  if (this->itemDelegateForRow(Source.row()) != mpPushButtonDelegate) return;

  CCopasiParameter * pParameter = CQParameterGroupDM::nodeFromIndex(Source);

  if (pParameter->getType() != CCopasiParameter::Type::GROUP) return;

  CCopasiParameterGroup * pGroup = static_cast< CCopasiParameterGroup * >(pParameter);

  CCopasiParameterGroup::elements::const_iterator it = pGroup->getElementTemplates().beginIndex();
  CCopasiParameterGroup::elements::const_iterator end = pGroup->getElementTemplates().endIndex();

  for (; it != end; ++it)
    {
      switch ((*it)->getType())
        {
          case CCopasiParameter::Type::CN:
            modifySelectCNs(*pGroup, **it);
            break;

          default:
            break;
        }
    }
}

void CQParameterGroupView::modifySelectCNs(CCopasiParameterGroup & group, const CCopasiParameter & cnTemplate)
{
  // OpenSelectionDialog
  std::vector< const CDataObject * > Selection;
  CObjectInterface::ContainerList ContainerList;
  ContainerList.push_back(group.getObjectDataModel());

  // Create the current selection
  CCopasiParameterGroup::elements::iterator it = group.beginIndex();
  CCopasiParameterGroup::elements::iterator end = group.endIndex();

  for (; it != end; ++it)
    {
      const CDataObject * pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(ContainerList, (*it)->getValue< CCommonName >()));

      if (pObject != NULL)
        {
          Selection.push_back(pObject);
        }
    }

  CModel * pModel = group.getObjectDataModel()->getModel();

  std::vector<const CDataObject * > ValidObjects;

  const std::vector< std::pair < CCommonName, CCommonName > > & ValidValues = cnTemplate.getValidValues< CCommonName >();
  std::vector< std::pair < CCommonName, CCommonName > >::const_iterator itValidValues = ValidValues.begin();
  std::vector< std::pair < CCommonName, CCommonName > >::const_iterator endValidValues = ValidValues.end();

  for (; itValidValues != endValidValues; ++itValidValues)
    {
      CObjectLists::ListType ListType = toEnum(itValidValues->first, CObjectLists::ListTypeName, CObjectLists::EMPTY_LIST);
      std::vector<const CDataObject * > Tmp = CObjectLists::getListOfConstObjects(ListType, pModel);
      ValidObjects.insert(ValidObjects.end(), Tmp.begin(), Tmp.end());
    }

  std::vector< const CDataObject * > NewSelection = CCopasiSelectionDialog::getObjectVector(this, ValidObjects, &Selection);

  // Modify group parameters;
  mpParameterGroupDM->beginResetModel();
  group.clear();

  std::vector< const CDataObject * >::const_iterator itNew = NewSelection.begin();
  std::vector< const CDataObject * >::const_iterator endNew = NewSelection.end();

  for (; itNew != endNew; ++itNew)
    {
      group.addParameter("Reaction", CCopasiParameter::Type::CN, (*itNew)->getCN());
    }

  mpParameterGroupDM->endResetModel();
}
