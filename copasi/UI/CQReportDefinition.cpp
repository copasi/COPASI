// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQReportDefinition.h"

#include "CCopasiSelectionDialog.h"
#include "CQTextDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CQReportListItem.h"

#include "report/CKeyFactory.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"
#include "report/CCopasiStaticString.h"
#include "report/CCopasiRootContainer.h"
#include "xml/CCopasiXMLInterface.h"

/*
 *  Constructs a CQReportDefinition which is a child of 'parent', with the
 *  name 'name'.'
 */
CQReportDefinition::CQReportDefinition(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

  mKey = "";
  mpReportDefinition = NULL;

  // We start with the table since this is simpler.
  setAdvancedMode(false);

  unsigned C_INT32 i;

  QStringList TaskNames;

  for (i = 0; CCopasiTask::TypeName[i] != ""; i++)
    {
      TaskNames.append(FROM_UTF8(CCopasiTask::TypeName[i]));
    }

  mpTaskBox->addItems(TaskNames);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQReportDefinition::~CQReportDefinition()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

void CQReportDefinition::nameChanged(const QString & /* string */)
{mChanged = true;}

void CQReportDefinition::taskChanged(const QString & /* string */)
{mChanged = true;}

void CQReportDefinition::commentChanged()
{mChanged = true;}

void CQReportDefinition::separatorChanged(const QString & /* string */)
{mChanged = true;}

void CQReportDefinition::precisionChanged(const QString & /* string */)
{mChanged = true;}

void CQReportDefinition::chkTabClicked()
{
  mChanged = true;

  if (mpTabCheck->isChecked())
    mpSeparator->setEnabled(false);
  else
    mpSeparator->setEnabled(true);
}

void CQReportDefinition::btnAdvancedClicked()
{
  if (mAdvanced)
    {
      if (CQMessageBox::question(NULL, "Report Conversion",
                                 "Converting an advanced report to a table may result in loss of customization.\n"
                                 "Do you want to proceed?",
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Cancel) == QMessageBox::Ok)
        {
          // We convert the body without the separators to a table.
          mpTableList->clear();

          unsigned C_INT32 i, imax;

          for (i = 0, imax = mpBodyList->count(); i < imax; i++)
            if (static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN().getObjectType()
                != "Separator")
              new CQReportListItem(static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN());

          mpHeaderList->clear();
          mpBodyList->clear();
          mpFooterList->clear();

          setAdvancedMode(false);

          mChanged = true;
        }
    }
  else
    {
      // To achieve the same result as with the table we use the preCompileTable
      // method of CReportDefinition. Since we must not change the existing report,
      // which may only be done by btnCommitClicked or leave, we create a temporary
      // copy.
      CReportDefinition * pStore = mpReportDefinition;

      // We avoid the renaming signal.
      mpReportDefinition = new CReportDefinition(TO_UTF8(mpName->text()), mpDataModel);

      mChanged = true;
      save();

      mpReportDefinition->preCompileTable();
      mpReportDefinition->setIsTable(false);

      load();

      delete mpReportDefinition;

      mpReportDefinition = pStore;

      mChanged = true;
    }
}

void CQReportDefinition::btnItemClicked()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel* pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (!pModel) return;

  std::vector< const CCopasiObject * > SelectedVector =
    //    CCopasiSelectionDialog::getObjectVector(this, CQSimpleSelectionTree::NO_RESTRICTION);
    CCopasiSelectionDialog::getObjectVector(this, CQSimpleSelectionTree::AnyObject);

  CQReportListItem * pItem;

  if (SelectedVector.size() != 0)
    {
      QListWidget * pList = static_cast< QListWidget * >(mpReportSectionTab->currentWidget());
      std::vector< const CCopasiObject * >::const_iterator it = SelectedVector.begin();
      std::vector< const CCopasiObject * >::const_iterator end = SelectedVector.end();

      for (; it != end; ++it)
        {
          pItem = new CQReportListItem(*it);
          pList->addItem(pItem);
        }

      mChanged = true;
    }

  return;
}

void CQReportDefinition::btnSeparatorClicked()
{
  CCopasiReportSeparator Separator;

  if (mpTabCheck->isChecked())
    Separator = "\t";
  else
    Separator = TO_UTF8(mpSeparator->text());

  static_cast<QListWidget *>(mpReportSectionTab->currentWidget())->addItem(new CQReportListItem(Separator.getCN()));

  mChanged = true;

  return;
}

void CQReportDefinition::btnTextClicked()
{
  CQTextDialog * pDialog = new CQTextDialog(this);

  if (pDialog->exec() == QDialog::Accepted &&
      pDialog->getText() != "")
    {
      CCopasiStaticString Text(TO_UTF8(pDialog->getText()));

      static_cast<QListWidget *>(mpReportSectionTab->currentWidget())->addItem(new CQReportListItem(Text.getCN()));
    }

  delete pDialog;

  mChanged = true;

  return;
}

void CQReportDefinition::btnDeleteClicked()
{
  QListWidget * pList = static_cast< QListWidget * >(mpReportSectionTab->currentWidget());

  QListWidgetItem * pNewSelection = NULL;

  int i, multipleSelection;

  for (i = pList->count() - 1, multipleSelection = 0; 0 <= i; i--)
    if (pList->item(i)->isSelected())
      {
        delete pList->takeItem(i);

        if (!pNewSelection && i < pList->count())
          {
            pNewSelection = pList->item(i); // We select the next.
          }

        multipleSelection++;
      }

  if (multipleSelection == 0) return; // Nothing selected,

  mChanged = true;
  pList->clearSelection();

  if (multipleSelection > 1) return;

  // Only one item was select and we move the selection to the next
  if (!pNewSelection && pList->count()) // We have removed item at the end.
    pNewSelection = pList->item(pList->count() - 1);

  // pNewSelection is NULL if the list is empty
  if (pNewSelection)
    {
      pNewSelection->setSelected(true);
    }

  return;
}

void CQReportDefinition::btnUpClicked()
{
  QListWidget * pList = static_cast< QListWidget * >(mpReportSectionTab->currentWidget());
  int i, to, multipleSelection;

  QListWidgetItem * pMove;

  for (i = pList->count() - 1, to = -1, multipleSelection = 0; i >= 0; i--)
    if (pList->item(i)->isSelected())
      {
        if (multipleSelection == 0)
          {
            to = i;
          }

        multipleSelection++;
      }
    else if (multipleSelection > 0)
      {
        pMove = pList->takeItem(i);

        if (pMove)
          {
            pList->insertItem(to, pMove);

            multipleSelection = 0;
            mChanged = true;
          }
      }

  // Unselect things we can not move.
  for (i = 0; i < multipleSelection; i++)
    pList->item(i)->setSelected(false);

  return;
}

void CQReportDefinition::btnDownClicked()
{
  QListWidget * pList = static_cast< QListWidget * >(mpReportSectionTab->currentWidget());
  int i, imax, to, multipleSelection;

  QListWidgetItem * pMove;

  // Find the index of the first selected item.
  for (i = 0, imax = pList->count(), to = -1, multipleSelection = 0; i < imax; i++)
    if (pList->item(i)->isSelected())
      {
        if (multipleSelection == 0) to = i;

        multipleSelection++;
      }
    else if (multipleSelection > 0)
      {
        pMove = pList->takeItem(i);

        if (pMove)
          {
            pList->insertItem(to, pMove);

            multipleSelection = 0;
            mChanged = true;
          }
      }

  // Unselect things we can not move.
  for (i = pList->count() - multipleSelection, imax = pList->count(); i < imax; i++)
    pList->item(i)->setSelected(false);

  return;
}

void CQReportDefinition::chkTitleClicked()
{mChanged = true;}

void CQReportDefinition::btnDeleteReportClicked()
{
  if (mpDataModel == NULL)
    return;

  std::set< const CCopasiObject * > Tasks;
  std::set< const CCopasiObject * > DeletedObjects;
  DeletedObjects.insert(mpObject);

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "report",
                                FROM_UTF8(mpObject->getObjectName()),
                                DeletedObjects);

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        CCopasiVector< CReportDefinition > * pReportList = mpDataModel->getReportDefinitionList();

        if (pReportList == NULL)
          return;

        if (mpDataModel->appendDependentTasks(DeletedObjects, Tasks))
          {
            std::set< const CCopasiObject * >::iterator it = Tasks.begin();
            std::set< const CCopasiObject * >::iterator end = Tasks.end();

            for (; it != end; ++it)
              {
                const CCopasiTask * pTask = static_cast< const CCopasiTask *>(*it);
                const_cast< CCopasiTask * >(pTask)->getReport().setReportDefinition(NULL);
              }
          }

        size_t Index = pReportList->getIndex(mpObject);
        std::string DeletedKey = mpObject->getKey();

        pReportList->remove(Index);

        size_t Size = pReportList->size();

        if (Size > 0)
          enter((*pReportList)[std::min(Index, Size - 1)]->getKey());
        else
          enter("");

        protectedNotify(ListViews::REPORT, ListViews::DELETE, DeletedKey);
        break;
      }

      default:
        break;
    }
}

void CQReportDefinition::btnNewReportClicked()
{
  btnCommitClicked();

  std::string Name = "report";

  int i = 0;
  CReportDefinition* pRep;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(pRep = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->createReportDefinition(Name, "")))
    {
      i++;
      Name = "report_";
      Name += TO_UTF8(QString::number(i));
    }

  std::string key = pRep->getKey();
  protectedNotify(ListViews::REPORT, ListViews::ADD, key);
  enter(key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQReportDefinition::btnCopyReportClicked()
{
  btnCommitClicked();

  CCopasiDataModel* pDataModel = mpObject->getObjectDataModel();

  if (pDataModel == NULL) return;

  CReportDefinition * pRep = new CReportDefinition(*dynamic_cast<CReportDefinition*>(CCopasiRootContainer::getKeyFactory()->get(mKey)));

  std::string baseName = pRep->getObjectName() + "_copy";
  std::string name = baseName;

  int i = 1;

  while (pDataModel->getReportDefinitionList()->getIndex(name) != C_INVALID_INDEX)
    {
      i++;
      name = baseName + TO_UTF8(QString::number(i));
    }

  pRep->setObjectName(name);

  pDataModel->getReportDefinitionList()->add(pRep, true);

  std::string key = pRep->getKey();
  protectedNotify(ListViews::REPORT, ListViews::ADD, key);
  enter(key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQReportDefinition::btnRevertClicked()
{load();}

void CQReportDefinition::btnCommitClicked()
{save();}

bool CQReportDefinition::update(ListViews::ObjectType objectType,
                                ListViews::Action action,
                                const std::string & key)
{
  // If the model is deleted or a new model is loaded the existing pointer
  // becomes invalid.
  if (objectType == ListViews::MODEL &&
      (action == ListViews::DELETE ||
       action == ListViews::ADD))
    {
      mpReportDefinition = NULL;
      return true;
    }

  if (mIgnoreUpdates ||
      objectType != ListViews::REPORT ||
      key != mKey ||
      action == ListViews::DELETE)
    return true;

  return load();
}

bool CQReportDefinition::leave()
{
  mpBtnCommit->setFocus();

  save();

  mpNotes->leave();

  return true;
}

bool CQReportDefinition::enterProtected()
{
  mpReportDefinition = dynamic_cast<CReportDefinition *>(mpObject);

  if (!mpReportDefinition)
    {
      mpListView->switchToOtherWidget(43, "");
      return false;
    }

  load();

  mpNotes->enter(mKey);

  return true;
}

bool CQReportDefinition::load()
{
  if (!mpReportDefinition) return false;

  // Reset everything.
  mpHeaderList->clear();
  mpBodyList->clear();
  mpFooterList->clear();
  mpTableList->clear();

  mpName->setText(FROM_UTF8(mpReportDefinition->getObjectName()));
  mpTaskBox->setCurrentIndex(mpReportDefinition->getTaskType());

  //separator
  if (mpReportDefinition->getSeparator().getStaticString() == "\t")
    {
      mpSeparator->setEnabled(false);
      mpTabCheck->setChecked(true);
    }
  else
    {
      mpSeparator->setEnabled(true);
      mpTabCheck->setChecked(false);
      mpSeparator->setText(FROM_UTF8(mpReportDefinition->getSeparator().getStaticString()));
    }

  mpPrecision->setText(QString::number(mpReportDefinition->getPrecision()));

  std::vector< CRegisteredObjectName > * pList = NULL;
  std::vector< CRegisteredObjectName >::const_iterator it;
  std::vector< CRegisteredObjectName >::const_iterator end;

  // Toggle the display mode.
  if (mpReportDefinition->isTable())
    {
      setAdvancedMode(false);

      mpTitleCheck->setChecked(mpReportDefinition->getTitle());

      pList = mpReportDefinition->getTableAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        mpTableList->addItem(new CQReportListItem(*it));
    }
  else
    {
      setAdvancedMode(true);

      pList = mpReportDefinition->getHeaderAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        mpHeaderList->addItem(new CQReportListItem(*it));

      pList = mpReportDefinition->getBodyAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        mpBodyList->addItem(new CQReportListItem(*it));

      pList = mpReportDefinition->getFooterAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        mpFooterList->addItem(new CQReportListItem(*it));
    }

  mChanged = false;
  return true;
}

bool CQReportDefinition::save()
{
  if (!mChanged) return true;

  if (!mpReportDefinition) return false;

  if (mpReportDefinition->getObjectName() != TO_UTF8(mpName->text()))
    {
      if (!mpReportDefinition->setObjectName(TO_UTF8(mpName->text())))
        {
          QString msg;
          msg = "Unable to rename report '" + FROM_UTF8(mpReportDefinition->getObjectName()) + "'\n"
                + "to '" + mpName->text() + "' since a report with that name already exists.";

          CQMessageBox::information(this,
                                    "Unable to rename Report",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);

          mpName->setText(FROM_UTF8(mpReportDefinition->getObjectName()));
        }
      else
        protectedNotify(ListViews::REPORT, ListViews::RENAME, mKey);
    }

  mpReportDefinition->setTaskType((CCopasiTask::Type) mpTaskBox->currentIndex());

  CCopasiReportSeparator Separator;

  if (mpTabCheck->isChecked())
    Separator = "\t";
  else
    Separator = TO_UTF8(mpSeparator->text());

  mpReportDefinition->setSeparator(Separator);

  mpReportDefinition->setPrecision(mpPrecision->text().toULong());

  mpReportDefinition->getHeaderAddr()->clear();
  mpReportDefinition->getBodyAddr()->clear();
  mpReportDefinition->getFooterAddr()->clear();
  mpReportDefinition->getTableAddr()->clear();

  std::vector< CRegisteredObjectName > * pList = NULL;
  unsigned C_INT32 i, imax;

  if (mAdvanced)
    {
      mpReportDefinition->setIsTable(false);

      pList = mpReportDefinition->getHeaderAddr();

      for (i = 0, imax = mpHeaderList->count(); i < imax; i++)
        if (static_cast<CQReportListItem *>(mpHeaderList->item(i))->getCN().getObjectType()
            == "Separator")
          pList->push_back(Separator.getCN());
        else
          pList->push_back(static_cast<CQReportListItem *>(mpHeaderList->item(i))->getCN());

      pList = mpReportDefinition->getBodyAddr();

      for (i = 0, imax = mpBodyList->count(); i < imax; i++)
        if (static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN().getObjectType()
            == "Separator")
          pList->push_back(Separator.getCN());
        else
          pList->push_back(static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN());

      pList = mpReportDefinition->getFooterAddr();

      for (i = 0, imax = mpFooterList->count(); i < imax; i++)
        if (static_cast<CQReportListItem *>(mpFooterList->item(i))->getCN().getObjectType()
            == "Separator")
          pList->push_back(Separator.getCN());
        else
          pList->push_back(static_cast<CQReportListItem *>(mpFooterList->item(i))->getCN());
    }
  else
    {
      mpReportDefinition->setIsTable(true);

      mpReportDefinition->setTitle(mpTitleCheck->isChecked());

      pList = mpReportDefinition->getTableAddr();

      for (i = 0, imax = mpTableList->count(); i < imax; i++)
        pList->push_back(static_cast<CQReportListItem *>(mpTableList->item(i))->getCN());
    }

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  (*CCopasiRootContainer::getDatamodelList())[0]->changed();

  mChanged = false;
  return false;
}

bool CQReportDefinition::setAdvancedMode(const bool & advanced)
{
  if (advanced)
    {
      mAdvanced = true;

      mpBtnAdvanced->setText("Advanced <<");
      mpReportSectionTab->setTabEnabled(mpReportSectionTab->indexOf(mpTableList), false);
      mpReportSectionTab->setTabEnabled(mpReportSectionTab->indexOf(mpHeaderList), true);
      mpReportSectionTab->setTabEnabled(mpReportSectionTab->indexOf(mpBodyList), true);
      mpReportSectionTab->setTabEnabled(mpReportSectionTab->indexOf(mpFooterList), true);
      mpReportSectionTab->setCurrentIndex(2);
      mpBtnSeparator->show();
      mpBtnText->show();
      mpTitleCheck->hide();
    }
  else
    {
      mAdvanced = false;

      mpBtnAdvanced->setText("Advanced >>");
      mpReportSectionTab->setTabEnabled(mpReportSectionTab->indexOf(mpTableList), true);
      mpReportSectionTab->setTabEnabled(mpReportSectionTab->indexOf(mpHeaderList), false);
      mpReportSectionTab->setTabEnabled(mpReportSectionTab->indexOf(mpBodyList), false);
      mpReportSectionTab->setTabEnabled(mpReportSectionTab->indexOf(mpFooterList), false);
      mpReportSectionTab->setCurrentIndex(0);
      mpBtnSeparator->hide();
      mpBtnText->hide();
      mpTitleCheck->show();
    }

  return true;
}
