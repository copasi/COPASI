// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "CQMiriamWidget.h"

#include <QHeaderView>
#include <QClipboard>
#include <QKeyEvent>
#include <QDesktopServices>
#include <QtCore/QUrl>

#include "copasi/copasi.h"

#include "copasi/UI/qtUtilities.h"
#include "copasi/UI/CQMessageBox.h"

#include "copasi/MIRIAM/CModelMIRIAMInfo.h"
#include "copasi/function/CFunction.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/UI/DataModelGUI.h"

/*
 *  Constructs a CQMiriamWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMiriamWidget::CQMiriamWidget(QWidget *parent, const char *name)
  : CopasiWidget(parent, name),
    mObjectCNToCopy(""),
    mpAnnotation(NULL),
    mMessage(""),
    mMessageType(-1)
{
  setupUi(this);
  // Create the MIRIAM Info
  mpMIRIAMInfo = NULL;
  //Create Data Models for the 4 tables
  mpCreatorDM = new CQCreatorDM(this);
  mpReferenceDM = new CQReferenceDM(this);
  mpBiologicalDescriptionDM = new CQBiologicalDescriptionDM(this);
  mpModifiedDM = new CQModifiedDM(this);
  //Create Proxy Data Models for the 4 tables
  mpCreatorPDM = new CQSortFilterProxyModel(this);
  mpReferencePDM = new CQSortFilterProxyModel(this);
  mpBiologicalDescriptionPDM = new CQSortFilterProxyModel(this);
  mpModifiedPDM = new CQSortFilterProxyModel(this);
  //Create Required Delegates
  mpResourceDelegate1 = new CQComboDelegate(this, mReferences, false);
  mpTblReferences->setItemDelegateForColumn(COL_RESOURCE_REFERENCE, mpResourceDelegate1);
  mpResourceDelegate2 = new CQComboDelegate(this, mResources, false);
  mpTblDescription->setItemDelegateForColumn(COL_RESOURCE_BD, mpResourceDelegate2);
  mpPredicateDelegate = new CQComboDelegate(this, mPredicates, false);
  mpTblDescription->setItemDelegateForColumn(COL_RELATIONSHIP, mpPredicateDelegate);
  mWidgets.push_back(mpTblAuthors); mDMs.push_back(mpCreatorDM); mProxyDMs.push_back(mpCreatorPDM);
  mWidgets.push_back(mpTblReferences); mDMs.push_back(mpReferenceDM); mProxyDMs.push_back(mpReferencePDM);
  mWidgets.push_back(mpTblDescription); mDMs.push_back(mpBiologicalDescriptionDM); mProxyDMs.push_back(mpBiologicalDescriptionPDM);
  mWidgets.push_back(mpTblModified); mDMs.push_back(mpModifiedDM); mProxyDMs.push_back(mpModifiedPDM);
  // Build the list of supported predicates
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::unknown)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_encodes)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::bqmodel_hasInstance)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_hasPart)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::bqbiol_hasProperty)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::bqbiol_hasTaxon)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_hasVersion)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_is)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::bqmodel_isDerivedFrom))),
                        mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isEncodedBy)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::bqmodel_isInstanceOf)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isHomologTo)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isPartOf)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::bqbiol_isPropertyOf)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isVersionOf)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_occursIn)));

  mpPredicateDelegate->setItems(-1, mPredicates);

  std::vector<CQTableView *>::const_iterator it = mWidgets.begin();
  std::vector<CQTableView *>::const_iterator end = mWidgets.end();

  std::vector<CQBaseDataModel *>::const_iterator itDM = mDMs.begin();
  std::vector<CQBaseDataModel *>::const_iterator endDM = mDMs.end();

  std::vector<CQSortFilterProxyModel *>::const_iterator itPDM = mProxyDMs.begin();
  std::vector<CQSortFilterProxyModel *>::const_iterator endPDM = mProxyDMs.end();

  for (; it != end && itDM != endDM && itPDM != endPDM; it++, itDM++, itPDM++)
    {
      //Set Proxy Data Model properties
      (*itPDM)->setDynamicSortFilter(true);
      (*itPDM)->setSortCaseSensitivity(Qt::CaseInsensitive);
      (*itPDM)->setSourceModel(*itDM);
      (*it)->setModel(*itPDM);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      (*it)->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      (*it)->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
      (*it)->verticalHeader()->hide();
      (*it)->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

      connect((*itDM), SIGNAL(signalNotifyChanges(const CUndoData::CChangeSet &)),
              this, SLOT(slotNotifyChanges(const CUndoData::CChangeSet &)));
      connect((*itDM), SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
              this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
      connect((*itDM), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
              this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
    }

  connect(mpTblDescription, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(slotBtnBrowseDescription(const QModelIndex &)));
  connect(mpTblReferences, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(slotBtnBrowseReference(const QModelIndex &)));
  // Build the list of known resources
  updateResourcesList();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMiriamWidget::~CQMiriamWidget()
{
  // no need to delete child widgets or objects, Qt does it all for us
  pdelete(mpMIRIAMInfo);
}

// virtual
void CQMiriamWidget::slotNotifyChanges(const CUndoData::CChangeSet & changes)
{
  if (changes.empty())
    {
      return;
    }

  mIgnoreUpdates = true;
  mpMIRIAMInfo->save();
  mpListView->getDataModelGUI()->notifyChanges(changes);
  mIgnoreUpdates = false;
}

void CQMiriamWidget::slotBtnDeleteClicked()
{
  if (mpTblAuthors->hasFocus())
    deleteSelectedAuthors();
  else if (mpTblReferences->hasFocus())
    deleteSelectedReferences();
  else if (mpTblModified->hasFocus())
    deleteSelectedModifieds();
  else if (mpTblDescription->hasFocus())
    deleteSelectedBiologicalDescriptions();
}

void CQMiriamWidget::deleteSelectedAuthors()
{
  QModelIndexList selRows = mpTblAuthors->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QModelIndexList mappedSelRows;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {mappedSelRows.append(mpCreatorPDM->mapToSource(*i));}

  mpCreatorDM->removeRows(mappedSelRows);
}

void CQMiriamWidget::deleteSelectedReferences()
{
  QModelIndexList selRows = mpTblReferences->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QModelIndexList mappedSelRows;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {mappedSelRows.append(mpReferencePDM->mapToSource(*i));}

  mpReferenceDM->removeRows(mappedSelRows);
}

void CQMiriamWidget::deleteSelectedBiologicalDescriptions()
{
  QModelIndexList selRows = mpTblDescription->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QModelIndexList mappedSelRows;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {mappedSelRows.append(mpBiologicalDescriptionPDM->mapToSource(*i));}

  mpBiologicalDescriptionDM->removeRows(mappedSelRows);
}

void CQMiriamWidget::deleteSelectedModifieds()
{
  QModelIndexList selRows = mpTblModified->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QModelIndexList mappedSelRows;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {mappedSelRows.append(mpModifiedPDM->mapToSource(*i));}

  mpModifiedDM->removeRows(mappedSelRows);
}

void openMiriamReference(const std::string &reference)
{
  if (reference == "" || reference.length() < 7)
    return;

  QDesktopServices::openUrl(QUrl(reference.c_str()));
}

void CQMiriamWidget::slotBtnBrowseReference(const QModelIndex &index)
{
  if (mpMIRIAMInfo == NULL ||
      index.column() > 1 ||
      index.row() < 0 ||
      index.row() >= (int)mpMIRIAMInfo->getReferences().size())
    return;

  const CReference *pRef = &mpMIRIAMInfo->getReferences()[index.row()];
  openMiriamReference(pRef->getMIRIAMResourceObject().getIdentifiersOrgURL() + "?profile=most_reliable");
}

void CQMiriamWidget::slotBtnBrowseDescription(const QModelIndex &index)
{
  if (mpMIRIAMInfo == NULL ||
      index.column() > 1 ||
      index.row() < 0 ||
      index.row() >= (int)mpMIRIAMInfo->getBiologicalDescriptions().size())
    return;

  const CBiologicalDescription *pRef = &mpMIRIAMInfo->getBiologicalDescriptions()[index.row()];
  openMiriamReference(pRef->getMIRIAMResourceObject().getIdentifiersOrgURL() + "?profile=most_reliable");
}

void CQMiriamWidget::slotBtnClearClicked()
{
  if (mpDTCreated->hasFocus())
    {
      mpDTCreated->setDateTime(QDateTime::currentDateTime());
      return;
    }

  if (mpTblAuthors->hasFocus())
    {
      int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Creators?",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpCreatorDM->clear();
        }
    }
  else if (mpTblReferences->hasFocus())
    {
      int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all References?",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpReferenceDM->clear();
        }
    }
  else if (mpTblDescription->hasFocus())
    {
      int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Descriptions?",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpBiologicalDescriptionDM->clear();
        }
    }
  else if (mpTblModified->hasFocus())
    {
      int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Date/Time Modifieds?",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpModifiedDM->clear();
        }
    }
}

bool CQMiriamWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  // Assure that the pointer is still valid;
  mpAnnotation = CAnnotation::castObject(mpObject);

  if (action == ListViews::DELETE && objectType == ListViews::ObjectType::MODEL)
    {
      // We can no longer trust that the info still exists
      mpCreatorDM->setMIRIAMInfo(NULL);
      mpReferenceDM->setMIRIAMInfo(NULL);
      mpBiologicalDescriptionDM->setMIRIAMInfo(NULL);
      mpModifiedDM->setMIRIAMInfo(NULL);

      mpMIRIAMInfo = NULL;
      mObjectCN = CCommonName("");

      return true;
    }

  if (!mIgnoreUpdates &&
      cn == mObjectCN)
    {
      if (action != ListViews::DELETE || objectType == ListViews::ObjectType::MIRIAM)
        {
          return enterProtected();
        }
      else
        {
          // We can no longer trust that the info still exists
          mpCreatorDM->setMIRIAMInfo(NULL);
          mpReferenceDM->setMIRIAMInfo(NULL);
          mpBiologicalDescriptionDM->setMIRIAMInfo(NULL);
          mpModifiedDM->setMIRIAMInfo(NULL);

          mpMIRIAMInfo = NULL;
        }
    }

  return true;
}

void CQMiriamWidget::slotCreatedDTChanged(QDateTime newDT)
{
  if (isVisible() &&
      newDT.isValid())
    {

      std::string DT = TO_UTF8(newDT.toUTC().toString(Qt::ISODate));

      if (DT != mpMIRIAMInfo->getCreatedDT())
        {
          CData OldData = mpMIRIAMInfo->toData();

          mpMIRIAMInfo->setCreatedDT(DT);

          CUndoData UndoData;
          mpMIRIAMInfo->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData);
          ListViews::addUndoMetaData(this, UndoData);

          slotNotifyChanges(mpDataModel->recordData(UndoData));
        }
    }
}

bool CQMiriamWidget::enterProtected()
{
  if (mpObject == NULL) return false;

  mpAnnotation = CAnnotation::castObject(mpObject);

  if (mpAnnotation == NULL) return false;

  CCopasiMessage::clearDeque();

  if (mObjectCNToCopy != "")
    {
      CObjectInterface::ContainerList List;
      List.push_back(mpDataModel);

      // This will check the current data model and the root container for the object;
      const CDataObject * pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, mObjectCNToCopy));
      const CAnnotation *pAnnotation = CAnnotation::castObject(pObject);

      if (pAnnotation != NULL)
        {
          std::string pMiriamAnnotation = pAnnotation->getMiriamAnnotation();
          mpAnnotation->setMiriamAnnotation(pMiriamAnnotation, mpObject->getKey(), pObject->getKey());
          mpMIRIAMInfo = CAnnotation::allocateMiriamInfo(dynamic_cast< CDataContainer * >(mpObject));

          // TODO Update Creation Date and Author
        }

      mObjectCNToCopy.clear();
    }

  CMIRIAMInfo * pOldMIRIAMInfo = mpMIRIAMInfo;

  mpMIRIAMInfo = CAnnotation::allocateMiriamInfo(dynamic_cast< CDataContainer * >(mpObject));

  mpCreatorDM->setMIRIAMInfo(mpMIRIAMInfo);
  mpReferenceDM->setMIRIAMInfo(mpMIRIAMInfo);
  mpBiologicalDescriptionDM->setMIRIAMInfo(mpMIRIAMInfo);
  mpModifiedDM->setMIRIAMInfo(mpMIRIAMInfo);

  if (pOldMIRIAMInfo != mpMIRIAMInfo &&
      pOldMIRIAMInfo != NULL)
    delete pOldMIRIAMInfo;

  //Set Models for the 4 TableViews
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      std::vector<CQTableView*>::const_iterator it = mWidgets.begin();
      std::vector<CQTableView*>::const_iterator end = mWidgets.end();

      for (; it != end; it++)
        (*it)->resizeColumnsToContents();
    }

  QDateTime DTCreated;

  if (mpMIRIAMInfo->getCreatedDT() != "")
    DTCreated = QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getCreatedDT()), Qt::ISODate).toLocalTime();

  mpDTCreated->setDateTime(DTCreated);

  if (CCopasiMessage::size() > 0)
    {
      mMessageType = CCopasiMessage::getHighestSeverity();
      mMessage = CCopasiMessage::getAllMessageText();
      CCopasiMessage::clearDeque();
      showEvent(NULL);
    }
  else
    {
      mMessageType = -1;
      mMessage = "";
    }

  return true;
}

bool CQMiriamWidget::leaveProtected()
{
  if (mpMIRIAMInfo != NULL)
    {
      mpMIRIAMInfo->save();

      if (!isVisible())
        {
          mpCreatorDM->setMIRIAMInfo(NULL);
          mpReferenceDM->setMIRIAMInfo(NULL);
          mpBiologicalDescriptionDM->setMIRIAMInfo(NULL);
          mpModifiedDM->setMIRIAMInfo(NULL);

          delete mpMIRIAMInfo;
          mpMIRIAMInfo = NULL;
        }
    }

  return true;
}

// virtual
void CQMiriamWidget::showEvent(QShowEvent *event)
{
  if (!isVisible()) return;

  switch ((CCopasiMessage::Type) mMessageType)
    {
      case CCopasiMessage::ERROR:
      case CCopasiMessage::EXCEPTION:
        CQMessageBox::critical(this, "Error", FROM_UTF8(mMessage));
        break;

      default:
        break;
    }

  mMessageType = -1;
  mMessage = "";

  if (event != NULL)
    enterProtected();
}

const CMIRIAMInfo &CQMiriamWidget::getMIRIAMInfo() const
{return *mpMIRIAMInfo;}

void CQMiriamWidget::updateResourcesList()
{
  // Build the list of known resources
  assert(CRootContainer::getDatamodelList()->size() > 0);
  const CMIRIAMResources *pResource = &CRootContainer::getConfiguration()->getRecentMIRIAMResources();
  QMap< QString, QString > ResourceMap;
  QMap< QString, QString > ReferenceMap;
  size_t i, imax = pResource->getResourceList().size();

  for (i = 0; i < imax; i++)
    if (pResource->getMIRIAMResource(i).getMIRIAMCitation())
      {
        QString Name = FROM_UTF8(pResource->getMIRIAMResource(i).getMIRIAMDisplayName());
        ReferenceMap.insert(Name.toLower(), Name);
      }
    else
      {
        QString Name = FROM_UTF8(pResource->getMIRIAMResource(i).getMIRIAMDisplayName());
        ResourceMap.insert(Name.toLower(), Name);
      }

  mResources.clear();
  mResources.push_back("-- select --");
  QMap< QString, QString >::const_iterator it = ResourceMap.begin();
  QMap< QString, QString >::const_iterator end = ResourceMap.end();

  for (; it != end; ++it)
    {
      mResources.push_back(it.value());
    }

  mReferences.clear();
  mReferences.push_back("-- select --");
  it = ReferenceMap.begin();
  end = ReferenceMap.end();

  for (; it != end; ++it)
    {
      mReferences.push_back(it.value());
    }

  mpResourceDelegate1->setItems(-1, mReferences);
  mpResourceDelegate2->setItems(-1, mResources);
}

void CQMiriamWidget::keyPressEvent(QKeyEvent *ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C &&
           (ev->modifiers() & Qt::ControlModifier))
    slotCopyEvent();
}

void CQMiriamWidget::dataChanged(const QModelIndex &topLeft, const QModelIndex &C_UNUSED(bottomRight))
{
  std::vector<CQTableView *>::const_iterator it = mWidgets.begin();
  std::vector<CQTableView *>::const_iterator end = mWidgets.end();

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      for (; it != end; it++)
        (*it)->resizeColumnsToContents();
    }

  if (mpTblAuthors->hasFocus())
    mpTblAuthors->selectionModel()->select(topLeft, QItemSelectionModel::Select);
}

void CQMiriamWidget::slotCopyEvent()
{
  CQSortFilterProxyModel *pProxyModel = NULL;
  CQBaseDataModel *pBaseDM = NULL;
  CQTableView *pTbl = NULL;

  if (mpTblAuthors->hasFocus())
    {
      pProxyModel = mpCreatorPDM;
      pBaseDM = mpCreatorDM;
      pTbl = mpTblAuthors;
    }
  else if (mpTblReferences->hasFocus())
    {
      pProxyModel = mpReferencePDM;
      pBaseDM = mpReferenceDM;
      pTbl = mpTblReferences;
    }
  else if (mpTblModified->hasFocus())
    {
      pProxyModel = mpModifiedPDM;
      pBaseDM = mpModifiedDM;
      pTbl = mpTblModified;
    }
  else if (mpTblDescription->hasFocus())
    {
      pProxyModel = mpBiologicalDescriptionPDM;
      pBaseDM = mpBiologicalDescriptionDM;
      pTbl = mpTblDescription;
    }
  else
    return;

  QModelIndexList selRows = pTbl->selectionModel()->selectedRows(0);

  if (selRows.empty())
    {return;}

  QString str;
  QModelIndexList::const_iterator i;

  for (i = selRows.begin(); i != selRows.end(); ++i)
    {
      for (int x = 0; x < pBaseDM->columnCount(); ++x)
        {
          if (!pTbl->isColumnHidden(x))
            {
              if (!str.isEmpty())
                str += "\t";

              str += pBaseDM->index(pProxyModel->mapToSource(*i).row(), x).data().toString();
            }
        }

      str += "\n";
    }

  QApplication::clipboard()->setText(str);
}

void CQMiriamWidget::slotBtnCopy()
{
  mObjectCNToCopy = mObjectCN;
}

// virtual
void CQMiriamWidget::slotBtnAddMe()
{
  mpCreatorDM->appendDefaultCreator();
}
