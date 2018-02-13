// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/core/CDataString.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/xml/CCopasiXMLInterface.h"
#include "copasi/CopasiDataModel/CDataModel.h"

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

  for (i = 0; i < CTaskEnum::TaskName.size(); i++)
    {
      TaskNames.append(FROM_UTF8(CTaskEnum::TaskName[i]));
    }

  mpTaskBox->addItems(TaskNames);

  QAction* separator = new QAction("", this);
  separator->setSeparator(true);

  this->mpTableList->addAction(this->mpActAddItem);
  this->mpTableList->addAction(this->mpActAddSeparator);
  this->mpTableList->addAction(this->mpActAddLineBreak);
  this->mpTableList->addAction(this->mpActEditItem);
  this->mpTableList->addAction(this->mpActEditText);
  this->mpTableList->addAction(separator);
  this->mpTableList->addAction(this->mpActDeleteItem);

  this->mpHeaderList->addAction(this->mpActAddItem);
  this->mpHeaderList->addAction(this->mpActAddSeparator);
  this->mpHeaderList->addAction(this->mpActAddLineBreak);
  this->mpHeaderList->addAction(this->mpActEditItem);
  this->mpHeaderList->addAction(this->mpActEditText);
  this->mpHeaderList->addAction(separator);
  this->mpHeaderList->addAction(this->mpActDeleteItem);

  this->mpBodyList->addAction(this->mpActAddItem);
  this->mpBodyList->addAction(this->mpActAddSeparator);
  this->mpBodyList->addAction(this->mpActAddLineBreak);
  this->mpBodyList->addAction(this->mpActEditItem);
  this->mpBodyList->addAction(this->mpActEditText);
  this->mpBodyList->addAction(separator);
  this->mpBodyList->addAction(this->mpActDeleteItem);

  this->mpFooterList->addAction(this->mpActAddItem);
  this->mpFooterList->addAction(this->mpActAddSeparator);
  this->mpFooterList->addAction(this->mpActAddLineBreak);
  this->mpFooterList->addAction(this->mpActEditItem);
  this->mpFooterList->addAction(this->mpActEditText);
  this->mpFooterList->addAction(separator);
  this->mpFooterList->addAction(this->mpActDeleteItem);

  connect(mpTableList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), mpActEditItem, SLOT(trigger()));
  connect(mpTableList->model(), SIGNAL(layoutChanged()), this, SLOT(setDirty()));

  connect(mpHeaderList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), mpActEditItem, SLOT(trigger()));
  connect(mpHeaderList->model(), SIGNAL(layoutChanged()), this, SLOT(setDirty()));

  connect(mpBodyList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), mpActEditItem, SLOT(trigger()));
  connect(mpBodyList->model(), SIGNAL(layoutChanged()), this, SLOT(setDirty()));

  connect(mpFooterList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), mpActEditItem, SLOT(trigger()));
  connect(mpFooterList->model(), SIGNAL(layoutChanged()), this, SLOT(setDirty()));
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

          unsigned C_INT32 i, imax = mpBodyList->count();

          for (i = 0; i < imax; ++i)
            {
              CQReportListItem *current = static_cast<CQReportListItem *>(mpBodyList->item(i));
              const CCommonName& name = current->getCN();

              if (name.getObjectType() != "Separator")
                mpTableList->addItem(new CQReportListItem(name, mpDataModel));
            }

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

      CObjectInterface::ContainerList ListOfContainer;
      ListOfContainer.push_back(mpDataModel);

      mpReportDefinition->preCompileTable(ListOfContainer);
      mpReportDefinition->setIsTable(false);

      load();

      delete mpReportDefinition;

      mpReportDefinition = pStore;

      mChanged = true;
    }
}

void CQReportDefinition::btnItemClicked()
{
  assert(mpDataModel != NULL);
  CModel* pModel = mpDataModel->getModel();

  if (!pModel) return;

  std::vector< const CDataObject * > SelectedVector =
    //    CCopasiSelectionDialog::getObjectVector(this, CQSimpleSelectionTree::NO_RESTRICTION);
    CCopasiSelectionDialog::getObjectVector(this, CQSimpleSelectionTree::AnyObject);

  CQReportListItem * pItem;

  if (SelectedVector.size() != 0)
    {
      QListWidget * pList = static_cast< QListWidget * >(mpReportSectionTab->currentWidget());
      std::vector< const CDataObject * >::const_iterator it = SelectedVector.begin();
      std::vector< const CDataObject * >::const_iterator end = SelectedVector.end();

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
    Separator = TO_UTF8_UNTRIMMED(mpSeparator->text());

  static_cast<QListWidget *>(mpReportSectionTab->currentWidget())->addItem(new CQReportListItem(Separator.getCN(), mpDataModel));

  mChanged = true;

  return;
}

void CQReportDefinition::btnLineBreakClicked()
{
  static_cast<QListWidget *>(mpReportSectionTab->currentWidget())->addItem(new CQReportListItem(CDataString("\n").getCN(), mpDataModel));
}

void CQReportDefinition::btnTextClicked()
{
  CQTextDialog * pDialog = new CQTextDialog(this);

  if (pDialog->exec() == QDialog::Accepted &&
      pDialog->getText() != "")
    {
      CDataString Text(TO_UTF8(pDialog->getText()));

      static_cast<QListWidget *>(mpReportSectionTab->currentWidget())->addItem(new CQReportListItem(Text.getCN(), mpDataModel));
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

  CDataObject::DataObjectSet Tasks;
  CDataObject::ObjectSet DeletedObjects;
  DeletedObjects.insert(mpObject);

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "report",
                                FROM_UTF8(mpObject->getObjectName()),
                                dynamic_cast< const CDataContainer * >(mpObject));

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        CDataVector< CReportDefinition > * pReportList = mpDataModel->getReportDefinitionList();

        if (pReportList == NULL)
          return;

        if (mpDataModel->appendDependentTasks(DeletedObjects, Tasks))
          {
            std::set< const CDataObject * >::iterator it = Tasks.begin();
            std::set< const CDataObject * >::iterator end = Tasks.end();

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
          enter((*pReportList)[std::min(Index, Size - 1)].getKey());
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
  assert(CRootContainer::getDatamodelList()->size() > 0);

  while (!(pRep = mpDataModel->getReportDefinitionList()->createReportDefinition(Name, "")))
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

  CDataModel* pDataModel = mpObject->getObjectDataModel();

  if (pDataModel == NULL) return;

  CReportDefinition * pRep = new CReportDefinition(*dynamic_cast<CReportDefinition*>(CRootContainer::getKeyFactory()->get(mKey)), NO_PARENT);

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

void CQReportDefinition::slotDeleteCurrentItem()
{
  QListWidget * current = static_cast<QListWidget *>(mpReportSectionTab->currentWidget());
  QList<QListWidgetItem*> selected = current->selectedItems();

  if (selected.empty())
    {
      return;
    }

  qDeleteAll(selected);
  setDirty();
}

void CQReportDefinition::slotEditCurrentItem()
{
  assert(mpDataModel != NULL);
  CModel* pModel = mpDataModel->getModel();

  if (!pModel) return;

  QListWidget * pList = static_cast<QListWidget *>(mpReportSectionTab->currentWidget());
  QList<QListWidgetItem*> selectedItems = pList->selectedItems();

  foreach (QListWidgetItem * item, selectedItems)
    {
      CQReportListItem* current = dynamic_cast<CQReportListItem*>(item);
      const CCommonName & name = current->getCN();

      if (name.getObjectType() == "Separator")
        continue;

      const CDataObject* pObject = dynamic_cast<const CDataObject*>(mpDataModel->getObject(name));

      if (pObject == NULL)
        {
          continue;
        }

      const CDataObject* pNewObject =
        CCopasiSelectionDialog::getObjectSingle(this, CQSimpleSelectionTree::AnyObject, pObject);

      if (pNewObject == NULL || pNewObject == pObject) continue;

      current->setObject(pNewObject);
      mChanged = true;
    }
}

void CQReportDefinition::slotEditCurrentItemText()
{
  assert(mpDataModel != NULL);
  CModel* pModel = mpDataModel->getModel();

  if (!pModel) return;

  QListWidget * pList = static_cast<QListWidget *>(mpReportSectionTab->currentWidget());
  QList<QListWidgetItem*> selectedItems = pList->selectedItems();

  CQTextDialog * pDialog = new CQTextDialog(this);

  foreach (QListWidgetItem * item, selectedItems)
    {
      CQReportListItem* current = dynamic_cast<CQReportListItem*>(item);
      const CCommonName & name = current->getCN();

      std::string objectType = name.getObjectType();

      if (objectType == "Separator")
        continue;

      if (objectType == "String")
        pDialog->setText(FROM_UTF8(name.getObjectName()));
      else
        pDialog->setText(FROM_UTF8(name));

      if (pDialog->exec() == QDialog::Accepted &&
          pDialog->getText() != "")
        {
          std::string newText = TO_UTF8(pDialog->getText());

          if (name != newText)
            {
              const CDataObject* pObject = dynamic_cast<const CDataObject*>(mpDataModel->getObject(newText));

              if (pObject != NULL)
                {
                  current->setObject(pObject);
                }
              else
                {
                  CDataString Text(newText);
                  current->setObject(&Text);
                }

              mChanged = true;
            }
        }
    }

  delete pDialog;
}

void CQReportDefinition::slotAddSeparator()
{
  CCopasiReportSeparator Separator;

  if (mpTabCheck->isChecked())
    Separator = "\t";
  else
    Separator = TO_UTF8_UNTRIMMED(mpSeparator->text());

  QListWidget * current = static_cast<QListWidget *>(mpReportSectionTab->currentWidget());

  QList<QListWidgetItem*> selected = current->selectedItems();

  if (selected.empty())
    {
      current->addItem(new CQReportListItem(Separator.getCN(), mpDataModel));
    }
  else
    {
      current->insertItem(current->row(selected.first()), new CQReportListItem(Separator.getCN(), mpDataModel));
    }

  mChanged = true;

  return;
}

void CQReportDefinition::slotAddLineBreak()
{
  QListWidget * current = static_cast<QListWidget *>(mpReportSectionTab->currentWidget());

  QList<QListWidgetItem*> selected = current->selectedItems();

  if (selected.empty())
    {
      current->addItem(new CQReportListItem(CDataString("\n").getCN(), mpDataModel));
    }
  else
    {
      current->insertItem(current->row(selected.first()), new CQReportListItem(CDataString("\n").getCN(), mpDataModel));
    }

  mChanged = true;

  return;
}

void CQReportDefinition::slotAddItem()
{
  QListWidget * current = static_cast<QListWidget *>(mpReportSectionTab->currentWidget());

  QList<QListWidgetItem*> selected = current->selectedItems();

  std::vector< const CDataObject * > SelectedVector =
    //    CCopasiSelectionDialog::getObjectVector(this, CQSimpleSelectionTree::NO_RESTRICTION);
    CCopasiSelectionDialog::getObjectVector(this, CQSimpleSelectionTree::AnyObject);

  CQReportListItem * pItem;

  if (SelectedVector.size() != 0)
    {
      QListWidget * pList = static_cast<QListWidget *>(mpReportSectionTab->currentWidget());
      std::vector< const CDataObject * >::const_iterator it = SelectedVector.begin();
      std::vector< const CDataObject * >::const_iterator end = SelectedVector.end();

      for (; it != end; ++it)
        {
          pItem = new CQReportListItem(*it);

          if (selected.empty())
            {
              pList->addItem(pItem);
            }
          else
            {
              current->insertItem(current->row(selected.first()), pItem);
            }
        }

      mChanged = true;
    }
}

void CQReportDefinition::setDirty()
{
  mChanged = true;
}

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
  //mpBtnCommit->setFocus();

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
  mpTaskBox->setCurrentIndex(static_cast<size_t>(mpReportDefinition->getTaskType()));

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

  mpPrecision->setText(convertToQString(mpReportDefinition->getPrecision()));

  std::vector< CRegisteredCommonName > * pList = NULL;
  std::vector< CRegisteredCommonName >::const_iterator it;
  std::vector< CRegisteredCommonName >::const_iterator end;

  // Toggle the display mode.
  if (mpReportDefinition->isTable())
    {
      setAdvancedMode(false);

      mpTitleCheck->setChecked(mpReportDefinition->getTitle());

      pList = mpReportDefinition->getTableAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        mpTableList->addItem(new CQReportListItem(*it, mpDataModel));
    }
  else
    {
      setAdvancedMode(true);

      pList = mpReportDefinition->getHeaderAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        mpHeaderList->addItem(new CQReportListItem(*it, mpDataModel));

      pList = mpReportDefinition->getBodyAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        mpBodyList->addItem(new CQReportListItem(*it, mpDataModel));

      pList = mpReportDefinition->getFooterAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        mpFooterList->addItem(new CQReportListItem(*it, mpDataModel));
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

  mpReportDefinition->setTaskType((CTaskEnum::Task) mpTaskBox->currentIndex());

  std::string Separator;

  if (mpTabCheck->isChecked())
    Separator = "\t";
  else
    Separator = TO_UTF8_UNTRIMMED(mpSeparator->text());

  mpReportDefinition->setSeparator(Separator);

  mpReportDefinition->setPrecision(mpPrecision->text().toULong());

  mpReportDefinition->getHeaderAddr()->clear();
  mpReportDefinition->getBodyAddr()->clear();
  mpReportDefinition->getFooterAddr()->clear();
  mpReportDefinition->getTableAddr()->clear();

  std::vector< CRegisteredCommonName > * pList = NULL;
  unsigned C_INT32 i, imax;

  if (mAdvanced)
    {
      mpReportDefinition->setIsTable(false);

      pList = mpReportDefinition->getHeaderAddr();

      for (i = 0, imax = mpHeaderList->count(); i < imax; i++)
        if (static_cast<CQReportListItem *>(mpHeaderList->item(i))->getCN().getObjectType()
            == "Separator")
          pList->push_back(mpReportDefinition->getSeparator().getCN());
        else
          pList->push_back(static_cast<CQReportListItem *>(mpHeaderList->item(i))->getCN());

      pList = mpReportDefinition->getBodyAddr();

      for (i = 0, imax = mpBodyList->count(); i < imax; i++)
        if (static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN().getObjectType()
            == "Separator")
          pList->push_back(mpReportDefinition->getSeparator().getCN());
        else
          pList->push_back(static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN());

      pList = mpReportDefinition->getFooterAddr();

      for (i = 0, imax = mpFooterList->count(); i < imax; i++)
        if (static_cast<CQReportListItem *>(mpFooterList->item(i))->getCN().getObjectType()
            == "Separator")
          pList->push_back(mpReportDefinition->getSeparator().getCN());
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

  assert(mpDataModel != NULL);
  mpDataModel->changed();

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
