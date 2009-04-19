// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQMiriamWidget.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/04/19 19:05:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QMessageBox>
#include <QHeaderView>

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
  mpDTEDelegate = new CQDateTimeEditDelegate(this);
  mpTblModified->setItemDelegateForColumn(COL_DATE_MODIFIED, mpDTEDelegate);

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

  std::vector<QTableView*>::const_iterator it = mWidgets.begin();
  std::vector<QTableView*>::const_iterator end = mWidgets.end();

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
  pdelete(mpCreatorPDM);
  pdelete(mpReferencePDM);
  pdelete(mpBiologicalDescriptionPDM);
  pdelete(mpModifiedPDM);
  pdelete(mpCreatorDM);
  pdelete(mpReferenceDM);
  pdelete(mpBiologicalDescriptionDM);
  pdelete(mpModifiedDM);
  pdelete(mpDTEDelegate);
  pdelete(mpResourceDelegate1);
  pdelete(mpResourceDelegate2);
  pdelete(mpPredicateDelegate);
  pdelete(mpMIRIAMInfo);
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMiriamWidget::languageChange()
{
  retranslateUi(this);
}

void CQMiriamWidget::slotBtnDeleteClicked()
{
  if (mpTblAuthors->hasFocus())
    {deleteSelectedAuthor();}
  else if (mpTblReferences->hasFocus())
    {deleteSelectedReference();}
  else if (mpTblModified->hasFocus())
    {deleteSelectedModified();}
  else if (mpTblDescription->hasFocus())
    {deleteSelectedBiologicalDescription();}
}

void CQMiriamWidget::deleteSelectedAuthor()
{
  if (!mpTblAuthors->selectionModel()->selectedIndexes().empty())
    {
      int delRow = mpTblAuthors->selectionModel()->selectedIndexes().value(0).row();
      QString givenName = mpTblAuthors->model()->data(mpTblAuthors->selectionModel()->selectedIndexes().value(COL_GIVEN_NAME)).toString();
      QString familyName = mpTblAuthors->model()->data(mpTblAuthors->selectionModel()->selectedIndexes().value(COL_FAMILY_NAME)).toString();
      QString msg = "Do you want to delete author '";

      if (!givenName.isNull())
        {
          msg.append(givenName);
        }

      if (!familyName.isNull())
        {
          msg.append(" ");
          msg.append(familyName);
        }

      msg.append("'?");

      int ret = QMessageBox::question(this, tr("Confirm Delete"), msg,
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {mpCreatorDM->removeRow(delRow);}
    }
}

void CQMiriamWidget::deleteSelectedReference()
{
  if (!mpTblReferences->selectionModel()->selectedIndexes().empty())
    {
      int delRow = mpTblReferences->selectionModel()->selectedIndexes().value(0).row();
      QString resource = mpTblReferences->model()->data(mpTblReferences->selectionModel()->selectedIndexes().value(COL_RESOURCE_REFERENCE)).toString();
      QString Id = mpTblReferences->model()->data(mpTblReferences->selectionModel()->selectedIndexes().value(COL_ID_REFERENCE)).toString();
      QString msg = "Do you want to delete Reference '";

      if (!resource.isNull())
        {
          msg.append(resource);
        }

      if (!Id.isNull())
        {
          msg.append(":");
          msg.append(Id);
        }

      msg.append("'?");

      int ret = QMessageBox::question(this, tr("Confirm Delete"), msg,
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {mpReferenceDM->removeRow(delRow);}
    }
}

void CQMiriamWidget::deleteSelectedBiologicalDescription()
{
  if (!mpTblDescription->selectionModel()->selectedIndexes().empty())
    {
      int delRow = mpTblDescription->selectionModel()->selectedIndexes().value(0).row();
      QString resource = mpTblDescription->model()->data(mpTblDescription->selectionModel()->selectedIndexes().value(COL_RESOURCE_BD)).toString();
      QString Id = mpTblDescription->model()->data(mpTblDescription->selectionModel()->selectedIndexes().value(COL_ID_BD)).toString();
      QString msg = "Do you want to delete Description '";

      if (!resource.isNull())
        {
          msg.append(resource);
        }

      if (!Id.isNull())
        {
          msg.append(":");
          msg.append(Id);
        }

      msg.append("'?");

      int ret = QMessageBox::question(this, tr("Confirm Delete"), msg,
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {mpBiologicalDescriptionDM->removeRow(delRow);}
    }
}

void CQMiriamWidget::deleteSelectedModified()
{
  if (!mpTblModified->selectionModel()->selectedIndexes().empty())
    {
      int delRow = mpTblModified->selectionModel()->selectedIndexes().value(0).row();
      QString dateModified = mpTblModified->model()->data(mpTblReferences->selectionModel()->selectedIndexes().value(COL_DATE_MODIFIED)).toString();
      QString msg = "Do you want to delete Date/Time Modified '";

      if (!dateModified.isNull())
        {
          msg.append(dateModified);
        }

      msg.append("'?");

      int ret = QMessageBox::question(this, tr("Confirm Delete"), msg,
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {mpModifiedDM->removeRow(delRow);}
    }
}

void CQMiriamWidget::slotBtnNewClicked()
{
  std::vector<QTableView*>::const_iterator it = mWidgets.begin();
  std::vector<QTableView*>::const_iterator end = mWidgets.end();

  std::vector<CQBaseDataModel*>::const_iterator itDM = mDMs.begin();
  std::vector<CQBaseDataModel*>::const_iterator endDM = mDMs.end();

  for (; it != end && itDM != endDM; it++, itDM++)
    {
      if ((*it)->hasFocus())
        {
          if (!(*itDM)->isLastDefaultRow() && (*itDM)->insertRow())
            (*it)->resizeColumnsToContents();
        }
    }
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
          mpCreatorDM->insertRow();
        }
    }
  else if (mpTblReferences->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all References?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpReferenceDM->clear();
          mpReferenceDM->insertRow();
        }
    }
  else if (mpTblDescription->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Descriptions?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpBiologicalDescriptionDM->clear();
          mpBiologicalDescriptionDM->insertRow();
        }
    }
  else if (mpTblModified->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Date/Time Modifieds?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          mpModifiedDM->clear();
          mpModifiedDM->insertRow();
        }
    }
}

bool CQMiriamWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & key)
{
  if (getIgnoreUpdates())
    return true;

  if (objectType != ListViews::MIRIAM)
    return true;

  if (key != mpMIRIAMInfo->getKey())
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

bool CQMiriamWidget::enter(const std::string & key)
{
  mpMIRIAMInfo->load(key);

  //Set Models for the 4 TableViews
  std::vector<QTableView*>::const_iterator it = mWidgets.begin();
  std::vector<QTableView*>::const_iterator end = mWidgets.end();

  std::vector<CQBaseDataModel*>::const_iterator itDM = mDMs.begin();
  std::vector<CQBaseDataModel*>::const_iterator endDM = mDMs.end();

  std::vector<CQSortFilterProxyModel*>::const_iterator itPDM = mProxyDMs.begin();
  std::vector<CQSortFilterProxyModel*>::const_iterator endPDM = mProxyDMs.end();

  for (; it != end && itDM != endDM && itPDM != endPDM; it++, itDM++, itPDM++)
    {
      (*itPDM)->setSourceModel(*itDM);
      (*it)->setModel(NULL);
      (*it)->setModel(*itPDM);
      (*itDM)->insertRow();
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
  std::vector<QTableView*>::const_iterator it = mWidgets.begin();
  std::vector<QTableView*>::const_iterator end = mWidgets.end();

  std::vector<CQBaseDataModel*>::const_iterator itDM = mDMs.begin();
  std::vector<CQBaseDataModel*>::const_iterator endDM = mDMs.end();

  for (; it != end && itDM != endDM; it++, itDM++)
    {
      (*itDM)->removeLastRowIfEmpty();
    }

  mpMIRIAMInfo->save();
  protectedNotify(ListViews::MIRIAM, ListViews::CHANGE, mpMIRIAMInfo->getKey());
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

  unsigned C_INT32 i, imax = pResource->getResourceList().size();

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
}

void CQMiriamWidget::dataChanged(const QModelIndex& topLeft, const QModelIndex& C_UNUSED(bottomRight))
{
  std::vector<QTableView*>::const_iterator it = mWidgets.begin();
  std::vector<QTableView*>::const_iterator end = mWidgets.end();

  std::vector<CQBaseDataModel*>::const_iterator itDM = mDMs.begin();
  std::vector<CQBaseDataModel*>::const_iterator endDM = mDMs.end();

  for (; it != end && itDM != endDM; it++, itDM++)
    {
      if ((*itDM) == topLeft.model())
        {
          if (topLeft.row() == ((*itDM)->rowCount() - 1))
            //If edit was done on last row, insert a new empty row.
            {
              if (!(*itDM)->isLastDefaultRow() && (*itDM)->insertRow())
                (*it)->resizeColumnsToContents();
            }
        }
    }
}
