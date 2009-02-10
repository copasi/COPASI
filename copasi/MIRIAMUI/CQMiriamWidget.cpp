// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQMiriamWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/10 21:40:10 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QMessageBox>

#include "CQMiriamWidget.h"
#include "copasi.h"
#include "UI/qtUtilities.h"
#include "MIRIAM/CModelMIRIAMInfo.h"
#include "CopasiDataModel/CCopasiDataModel.h"
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
  mpModifiedDM = new CQModifiedDM(mpMIRIAMInfo, this);

  //Create Required Delegates
  mpDTEDelegate = new CQDateTimeEditDelegate(this);
  mpTblModified->setItemDelegateForColumn(COL_DATE_MODIFIED, mpDTEDelegate);

  // Connect the table widgets
  //mWidgets.push_back(mpTblAuthors);
  connect(mpTblAuthors, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  //mWidgets.push_back(mpTblReferences);
  connect(mpTblReferences, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  //mWidgets.push_back(mpTblDescription);
  connect(mpTblDescription, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

  //mWidgets.push_back(mpTblModified);
  connect(mpTblModified, SIGNAL(delKeyPressed()), this, SLOT(slotBtnDeleteClicked()));

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

  // Build the list of known resources
  updateResourcesList();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMiriamWidget::~CQMiriamWidget()
{
  pdelete(mpCreatorDM);
  pdelete(mpReferenceDM);
  pdelete(mpModifiedDM);
  pdelete(mpDTEDelegate);
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

void CQMiriamWidget::slotBtnOKClicked()
{
  // This forces that changes to the current table cell are committed.

  leave();
  enter(mpMIRIAMInfo->getKey());
}

void CQMiriamWidget::slotBtnCancelClicked()
{
  enter(mpMIRIAMInfo->getKey());
}

void CQMiriamWidget::slotBtnDeleteClicked()
{
  if (mpTblAuthors->hasFocus())
  {deleteSelectedAuthor();}
  else if (mpTblReferences->hasFocus())
  {deleteSelectedReference();}
  else if (mpTblModified->hasFocus())
  {deleteSelectedModified();}
  /*std::vector<QTableView*>::const_iterator it = mWidgets.begin();
  std::vector<QTableView*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    if ((*it)->hasFocus())
      (*it)->slotBtnDeleteClicked();
   */
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
      QString resource = mpTblReferences->model()->data(mpTblReferences->selectionModel()->selectedIndexes().value(COL_RESOURCE)).toString();
      QString Id = mpTblReferences->model()->data(mpTblReferences->selectionModel()->selectedIndexes().value(COL_ID)).toString();
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
  if (mpTblAuthors->hasFocus())
    mpCreatorDM->insertRow();
  else if (mpTblReferences->hasFocus())
    mpReferenceDM->insertRow();
  else if (mpTblModified->hasFocus())
    mpModifiedDM->insertRow();

  /*std::vector<QTableView*>::const_iterator it = mWidgets.begin();
  std::vector<QTableView*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    if ((*it)->hasFocus())
      (*it)->slotBtnNewClicked();
   */
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
      {mpCreatorDM->clear();}
    }
  else if (mpTblReferences->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all References?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
      if (ret == QMessageBox::Yes)
      {mpReferenceDM->clear();}
    }
  else if (mpTblModified->hasFocus())
    {
      int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Date/Time Modifieds?",
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
      if (ret == QMessageBox::Yes)
      {mpModifiedDM->clear();}
    }

  /*std::vector<QTableView*>::const_iterator it = mWidgets.begin();
  std::vector<QTableView*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    if ((*it)->hasFocus())
      (*it)->slotBtnClearClicked();
   */
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

bool CQMiriamWidget::leave()
{
  mpMIRIAMInfo->save();
  protectedNotify(ListViews::MIRIAM, ListViews::CHANGE, mpMIRIAMInfo->getKey());
  return true;
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
  mpTblAuthors->setModel(NULL);
  mpTblAuthors->setModel(mpCreatorDM);
  mpTblAuthors->resizeRowsToContents();
  mpTblAuthors->resizeColumnsToContents();

  mpTblReferences->setModel(NULL);
  mpTblReferences->setModel(mpReferenceDM);
  mpTblReferences->resizeRowsToContents();
  mpTblReferences->resizeColumnsToContents();

  mpTblModified->setModel(NULL);
  mpTblModified->setModel(mpModifiedDM);
  mpTblModified->resizeRowsToContents();
  mpTblModified->resizeColumnsToContents();

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

const CMIRIAMInfo & CQMiriamWidget::getMIRIAMInfo() const
  {return *mpMIRIAMInfo;}

void CQMiriamWidget::updateResourcesList()
{
  mResources.clear();
  // Build the list of known resources
  const CMIRIAMResources * pResource = &CCopasiDataModel::Global->getConfiguration()->getRecentMIRIAMResources();
  mResources.push_back("-- select --");

  unsigned C_INT32 i, imax = pResource->getResourceList().size();
  for (i = 0; i < imax; i++)
    if (pResource->getMIRIAMResource(i).getMIRIAMCitation())
      mResources.push_back(FROM_UTF8(pResource->getMIRIAMResource(i).getMIRIAMDisplayName()));

  /*// We need to update each currently shown ComboBox
  Q3ComboTableItem * pComboBox = NULL;
  imax = table->numCols();
  for (i = 0; i < imax; i++)
    if ((pComboBox = dynamic_cast<Q3ComboTableItem *>(table->item(i, COL_RESOURCE))) != NULL)
      delete pComboBox;
   */
}

const CQCreatorDM* CQMiriamWidget::getCreatorDM() const
  {
    return mpCreatorDM;
  }
