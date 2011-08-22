// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQMiriamWidget.cpp,v $
//   $Revision: 1.21 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/08/22 21:40:24 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QMessageBox>
#include <QHeaderView>
#include <QClipboard>

#include "CQMiriamWidget.h"
#include "copasi.h"
#include "UI/qtUtilities.h"
#include "MIRIAM/CModelMIRIAMInfo.h"
#include "report/CCopasiRootContainer.h"
#include "commandline/CConfigurationFile.h"

/*
 *  Constructs a CQMiriamWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMiriamWidget::CQMiriamWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  // Create the MIRIAM Info
  mpMIRIAMInfo = new CMIRIAMInfo();

  //Create Data Models for the 4 tables
  mpCreatorDM = new CQCreatorDM(mpMIRIAMInfo, this);
  mpReferenceDM = new CQReferenceDM(mpMIRIAMInfo, this);
  mpBiologicalDescriptionDM = new CQBiologicalDescriptionDM(mpMIRIAMInfo, this);
  mpModifiedDM = new CQModifiedDM(mpMIRIAMInfo, this);

  //Create Proxy Data Models for the 4 tables
  mpCreatorPDM = new CQSortFilterProxyModel();
  mpReferencePDM = new CQSortFilterProxyModel();
  mpBiologicalDescriptionPDM = new CQSortFilterProxyModel();
  mpModifiedPDM = new CQSortFilterProxyModel();

  //Create Required Delegates
  mpResourceDelegate1 = new CQComboDelegate(&mResources, this);
  mpTblReferences->setItemDelegateForColumn(COL_RESOURCE_REFERENCE, mpResourceDelegate1);

  mpResourceDelegate2 = new CQComboDelegate(&mReferences, this);
  mpTblDescription->setItemDelegateForColumn(COL_RESOURCE_BD, mpResourceDelegate2);

  mpPredicateDelegate = new CQComboDelegate(&mPredicates, this);
  mpTblDescription->setItemDelegateForColumn(COL_RELATIONSHIP, mpPredicateDelegate);

  mWidgets.push_back(mpTblAuthors); mDMs.push_back(mpCreatorDM); mProxyDMs.push_back(mpCreatorPDM);
  mWidgets.push_back(mpTblReferences); mDMs.push_back(mpReferenceDM); mProxyDMs.push_back(mpReferencePDM);
  mWidgets.push_back(mpTblDescription); mDMs.push_back(mpBiologicalDescriptionDM); mProxyDMs.push_back(mpBiologicalDescriptionPDM);
  mWidgets.push_back(mpTblModified); mDMs.push_back(mpModifiedDM); mProxyDMs.push_back(mpModifiedPDM);

  // Build the list of supported predicates
  mPredicates.push_back("-- select --");
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_encodes)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_hasPart)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_hasVersion)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_is)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isEncodedBy)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isHomologTo)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isPartOf)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isVersionOf)));

  std::vector<CQTableView*>::const_iterator it = mWidgets.begin();
  std::vector<CQTableView*>::const_iterator end = mWidgets.end();

  std::vector<CQBaseDataModel*>::const_iterator itDM = mDMs.begin();
  std::vector<CQBaseDataModel*>::const_iterator endDM = mDMs.end();

  std::vector<CQSortFilterProxyModel*>::const_iterator itPDM = mProxyDMs.begin();
  std::vector<CQSortFilterProxyModel*>::const_iterator endPDM = mProxyDMs.end();

  for (; it != end && itDM != endDM && itPDM != endPDM; it++, itDM++, itPDM++)
    {
      //Set Proxy Data Model properties
      (*itPDM)->setDynamicSortFilter(true);
      (*itPDM)->setSortCaseSensitivity(Qt::CaseInsensitive);

      (*it)->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
      (*it)->verticalHeader()->hide();
      (*it)->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

      connect((*itDM), SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
              this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
      connect((*itDM), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
              this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
    }

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

void CQMiriamWidget::slotBtnDeleteClicked()
{
  if (mpTblAuthors->hasFocus())
    {deleteSelectedAuthors();}
  else if (mpTblReferences->hasFocus())
    {deleteSelectedReferences();}
  else if (mpTblModified->hasFocus())
    {deleteSelectedModifieds();}
  else if (mpTblDescription->hasFocus())
    {deleteSelectedBiologicalDescriptions();}
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

void CQMiriamWidget::slotBtnClearClicked()
{
  if (mpDTCreated->hasFocus())
    {
      mpDTCreated->setDateTime(QDateTime::currentDateTime());
      return;
    }

  if (mpTblAuthors->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Creators?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpCreatorDM->clear();
        }
    }
  else if (mpTblReferences->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all References?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpReferenceDM->clear();
        }
    }
  else if (mpTblDescription->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Descriptions?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpBiologicalDescriptionDM->clear();
        }
    }
  else if (mpTblModified->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Date/Time Modifieds?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpModifiedDM->clear();
        }
    }
}

bool CQMiriamWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & key)
{
  if (getIgnoreUpdates())
    return true;

  if (objectType != ListViews::MIRIAM)
    return true;

  if (key == "" || key != mpMIRIAMInfo->getKey())
    return true;

  bool success = true;
  mpMIRIAMInfo->load(key);

  if (mpMIRIAMInfo->getCreatedDT() != "")
    mpDTCreated->setDateTime(QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getCreatedDT()), Qt::ISODate));

  return success;
}

void CQMiriamWidget::slotCreatedDTChanged(QDateTime newDT)
{
  //Now update.
  // Created at
  std::string DT = "";

  if (newDT.isValid())
    {
      DT = TO_UTF8(newDT.toString(Qt::ISODate));
      DT += "Z";

      if (DT != mpMIRIAMInfo->getCreatedDT())
        {
          mpMIRIAMInfo->setCreatedDT(DT);
        }
    }
}

bool CQMiriamWidget::enterProtected()
{
  if (mKey == "")
    return false;

  mpMIRIAMInfo->load(mKey);

  //Set Models for the 4 TableViews
  std::vector<CQTableView*>::const_iterator it = mWidgets.begin();
  std::vector<CQTableView*>::const_iterator end = mWidgets.end();

  std::vector<CQBaseDataModel*>::const_iterator itDM = mDMs.begin();
  std::vector<CQBaseDataModel*>::const_iterator endDM = mDMs.end();

  std::vector<CQSortFilterProxyModel*>::const_iterator itPDM = mProxyDMs.begin();
  std::vector<CQSortFilterProxyModel*>::const_iterator endPDM = mProxyDMs.end();

  for (; it != end && itDM != endDM && itPDM != endPDM; it++, itDM++, itPDM++)
    {
      (*itPDM)->setSourceModel(*itDM);
      (*it)->setModel(NULL);
      (*it)->setModel(*itPDM);
      (*it)->resizeColumnsToContents();
    }

  QDateTime DTCreated;

  if (mpMIRIAMInfo->getCreatedDT() != "")
    DTCreated = QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getCreatedDT()), Qt::ISODate);

  if (DTCreated.isValid())
    mpDTCreated->setDateTime(DTCreated);
  else
    {
      mpDTCreated->setDateTime(QDateTime::currentDateTime());
    }

  return true;
}

bool CQMiriamWidget::leave()
{
  mpMIRIAMInfo->save();
  return true;
}

const CMIRIAMInfo & CQMiriamWidget::getMIRIAMInfo() const
{return *mpMIRIAMInfo;}

void CQMiriamWidget::updateResourcesList()
{
  mResources.clear();
  mReferences.clear();
  // Build the list of known resources
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CMIRIAMResources * pResource = &CCopasiRootContainer::getConfiguration()->getRecentMIRIAMResources();
  mResources.push_back("-- select --");
  mReferences.push_back("-- select --");

  size_t i, imax = pResource->getResourceList().size();

  for (i = 0; i < imax; i++)
    if (pResource->getMIRIAMResource(i).getMIRIAMCitation())
      mResources.push_back(FROM_UTF8(pResource->getMIRIAMResource(i).getMIRIAMDisplayName()));
    else
      mReferences.push_back(FROM_UTF8(pResource->getMIRIAMResource(i).getMIRIAMDisplayName()));
}

void CQMiriamWidget::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C &&
           (ev->modifiers() & Qt::ControlModifier))
    slotCopyEvent();
}

void CQMiriamWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft), const QModelIndex& C_UNUSED(bottomRight))
{
  std::vector<CQTableView*>::const_iterator it = mWidgets.begin();
  std::vector<CQTableView*>::const_iterator end = mWidgets.end();

  for (; it != end; it++)
    (*it)->resizeColumnsToContents();
}

void CQMiriamWidget::slotCopyEvent()
{
  CQSortFilterProxyModel* pProxyModel = NULL;
  CQBaseDataModel* pBaseDM = NULL;
  CQTableView* pTbl = NULL;

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
