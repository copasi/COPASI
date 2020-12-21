// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

void _addItem(QTableWidget* pList, QTableWidgetItem* item)
{
  int row = pList->rowCount();
  pList->insertRow(row);
  pList->setItem(row, 0, item);
}

void _insertItem(QTableWidget* pList, int row, QTableWidgetItem* item)
{
  pList->insertRow(row);
  pList->setItem(row, 0, item);
}

void
CQReportDefinition::_setup(QTableWidget* pList)
{
  pList->setColumnCount(1);
  pList->horizontalHeader()->setVisible(false);
  pList->horizontalHeader()->setStretchLastSection(true);

  pList->setDragDropOverwriteMode(false);
  pList->setDragDropMode(QAbstractItemView::InternalMove);
  pList->setDefaultDropAction(Qt::TargetMoveAction);
  pList->setSelectionMode(QAbstractItemView::ContiguousSelection);

  pList->addAction(mpActAddItem);
  pList->addAction(mpActAddSeparator);
  pList->addAction(mpActAddLineBreak);
  pList->addAction(mpActEditItem);
  pList->addAction(mpActEditText);
  pList->addAction(mpActSeparator);
  pList->addAction(mpActDeleteItem);

  connect(pList, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), mpActEditItem, SLOT(trigger()));
  connect(pList->model(), SIGNAL(layoutChanged()), this, SLOT(setDirty()));
}

/*
 *  Constructs a CQReportDefinition which is a child of 'parent', with the
 *  name 'name'.'
 */
CQReportDefinition::CQReportDefinition(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

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

  mpActSeparator = new QAction("", this);
  mpActSeparator->setSeparator(true);

  _setup(mpTableList);
  _setup(mpHeaderList);
  _setup(mpBodyList);
  _setup(mpFooterList);
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
      if (CQMessageBox::question(this, "Report Conversion",
                                 "Converting an advanced report to a table may result in loss of customization.\n"
                                 "Do you want to proceed?",
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Cancel) == QMessageBox::Ok)
        {
          // We convert the body without the separators to a table.
          mpTableList->clear();
          mpTableList->setRowCount(0);

          unsigned C_INT32 i, imax = mpBodyList->rowCount();

          for (i = 0; i < imax; ++i)
            {
              CQReportListItem *current = static_cast<CQReportListItem *>(mpBodyList->item(i, 0));
              const CCommonName& name = current->getCN();

              if (name.getObjectType() != "Separator")
                _addItem(mpTableList, new CQReportListItem(name, mpDataModel));
            }

          mpHeaderList->clear();
          mpHeaderList->setRowCount(0);
          mpBodyList->clear();
          mpBodyList->setRowCount(0);
          mpFooterList->clear();
          mpFooterList->setRowCount(0);

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
      QTableWidget * pList = static_cast< QTableWidget * >(mpReportSectionTab->currentWidget());
      std::vector< const CDataObject * >::const_iterator it = SelectedVector.begin();
      std::vector< const CDataObject * >::const_iterator end = SelectedVector.end();

      for (; it != end; ++it)
        {
          pItem = new CQReportListItem(*it);
          _addItem(pList, pItem);
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

  _addItem(static_cast<QTableWidget*>(mpReportSectionTab->currentWidget()), new CQReportListItem(Separator.getCN(), mpDataModel));

  mChanged = true;

  return;
}

void CQReportDefinition::btnLineBreakClicked()
{
  _addItem(static_cast<QTableWidget*>(mpReportSectionTab->currentWidget()), new CQReportListItem(CDataString("\n").getCN(), mpDataModel));
}

void CQReportDefinition::btnTextClicked()
{
  CQTextDialog * pDialog = new CQTextDialog(this);

  if (pDialog->exec() == QDialog::Accepted &&
      pDialog->getText() != "")
    {
      CDataString Text(TO_UTF8(pDialog->getText()));

      _addItem(static_cast<QTableWidget*>(mpReportSectionTab->currentWidget()), new CQReportListItem(Text.getCN(), mpDataModel));
    }

  delete pDialog;

  mChanged = true;

  return;
}

void CQReportDefinition::btnDeleteClicked()
{
  QTableWidget * pList = static_cast< QTableWidget * >(mpReportSectionTab->currentWidget());

  QTableWidgetItem * pNewSelection = NULL;

  int i, multipleSelection;

  for (i = pList->rowCount() - 1, multipleSelection = 0; 0 <= i; i--)
    {
      QTableWidgetItem * pCurrItem = pList->item(i, 0);

      if (!pCurrItem)
        continue;

      if (pCurrItem->isSelected())
        {
          delete pList->takeItem(i, 0);
          pList->removeRow(i);

          if (!pNewSelection && i < pList->rowCount())
            {
              pNewSelection = pList->item(i, 0); // We select the next.
            }

          multipleSelection++;
        }
    }

  if (multipleSelection == 0) return; // Nothing selected,

  mChanged = true;
  pList->clearSelection();

  if (multipleSelection > 1) return;

  // Only one item was select and we move the selection to the next
  if (!pNewSelection && pList->rowCount()) // We have removed item at the end.
    pNewSelection = pList->item(pList->rowCount() - 1, 0);

  // pNewSelection is NULL if the list is empty
  if (pNewSelection)
    {
      pNewSelection->setSelected(true);
    }

  return;
}

void CQReportDefinition::btnUpClicked()
{
  QTableWidget * pList = static_cast< QTableWidget * >(mpReportSectionTab->currentWidget());
  int i, to, multipleSelection;

  QTableWidgetItem * pMove;

  for (i = pList->rowCount() - 1, to = -1, multipleSelection = 0; i >= 0; i--)
    {
      QTableWidgetItem * pCurrItem = pList->item(i, 0);

      if (!pCurrItem)
        continue;

      if (pCurrItem->isSelected())
        {
          if (multipleSelection == 0)
            {
              to = i;
            }

          multipleSelection++;
        }
      else if (multipleSelection > 0)
        {
          pMove = pList->takeItem(i, 0);
          pList->removeRow(i);

          if (pMove)
            {
              _insertItem(pList, to, pMove);

              multipleSelection = 0;
              mChanged = true;
            }
        }
    }

  // Unselect things we can not move.
  for (i = 0; i < multipleSelection; i++)
    pList->item(i, 0)->setSelected(false);

  return;
}

void CQReportDefinition::btnDownClicked()
{
  QTableWidget * pList = static_cast< QTableWidget * >(mpReportSectionTab->currentWidget());
  int i, imax, to, multipleSelection;

  QTableWidgetItem * pMove;

  // Find the index of the first selected item.
  for (i = 0, imax = pList->rowCount(), to = -1, multipleSelection = 0; i < imax; i++)
    {
      QTableWidgetItem * pCurrItem = pList->item(i, 0);

      if (!pCurrItem)
        continue;

      if (pCurrItem->isSelected())
        {
          if (multipleSelection == 0)
            to = i;

          multipleSelection++;
        }
      else if (multipleSelection > 0)
        {
          pMove = pList->takeItem(i, 0);
          pList->removeRow(i);

          if (pMove)
            {
              _insertItem(pList, to, pMove);

              multipleSelection = 0;
              mChanged = true;
            }
        }
    }

  // Unselect things we can not move.
  for (i = pList->rowCount() - multipleSelection, imax = pList->rowCount(); i < imax; i++)
    pList->item(i, 0)->setSelected(false);

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
        std::string DeletedObjectCN = mObjectCN;

        pReportList->remove(Index);

        size_t Size = pReportList->size();

        if (Size > 0)
          enter((*pReportList)[std::min(Index, Size - 1)].getKey());
        else
          enter(std::string());

        protectedNotify(ListViews::ObjectType::REPORT, ListViews::DELETE, DeletedObjectCN);
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

  CCommonName CN = pRep->getCN();
  protectedNotify(ListViews::ObjectType::REPORT, ListViews::ADD, CN);
  enter(CN);
  mpListView->switchToOtherWidget(ListViews::WidgetType::ReportTemplateDetail, CN);
}

void CQReportDefinition::btnCopyReportClicked()
{
  btnCommitClicked();

  CDataModel* pDataModel = mpObject->getObjectDataModel();

  if (pDataModel == NULL) return;

  CReportDefinition * pRep = new CReportDefinition(*dynamic_cast<CReportDefinition*>(mpObject), NO_PARENT);

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

  CCommonName CN = pRep->getCN();
  protectedNotify(ListViews::ObjectType::REPORT, ListViews::ADD, CN);
  enter(CN);
  mpListView->switchToOtherWidget(ListViews::WidgetType::ReportTemplateDetail, CN);
}

void CQReportDefinition::btnRevertClicked()
{load();}

void CQReportDefinition::btnCommitClicked()
{save();}

void CQReportDefinition::slotDeleteCurrentItem()
{
  QTableWidget * current = static_cast<QTableWidget *>(mpReportSectionTab->currentWidget());
  QList<QTableWidgetItem*> selected = current->selectedItems();

  if (selected.empty())
    {
      return;
    }

  auto it = selected.begin();
  auto end = selected.end();

  while (it != end)
    {
      QTableWidgetItem* item = *it;
      int row = item->row();
      current->removeRow(row);
      ++it;
    }

  setDirty();
}

void CQReportDefinition::slotEditCurrentItem()
{
  assert(mpDataModel != NULL);
  CModel* pModel = mpDataModel->getModel();

  if (!pModel) return;

  QTableWidget * pList = static_cast<QTableWidget *>(mpReportSectionTab->currentWidget());
  QList<QTableWidgetItem*> selectedItems = pList->selectedItems();

  foreach (QTableWidgetItem * item, selectedItems)
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

  QTableWidget * pList = static_cast<QTableWidget *>(mpReportSectionTab->currentWidget());
  QList<QTableWidgetItem*> selectedItems = pList->selectedItems();

  CQTextDialog * pDialog = new CQTextDialog(this);

  foreach (QTableWidgetItem * item, selectedItems)
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

  QTableWidget * current = static_cast<QTableWidget *>(mpReportSectionTab->currentWidget());

  QList<QTableWidgetItem*> selected = current->selectedItems();

  if (selected.empty())
    {
      _addItem(current, new CQReportListItem(Separator.getCN(), mpDataModel));
    }
  else
    {
      _insertItem(current, current->row(selected.first()), new CQReportListItem(Separator.getCN(), mpDataModel));
    }

  mChanged = true;

  return;
}

void CQReportDefinition::slotAddLineBreak()
{
  QTableWidget * current = static_cast<QTableWidget *>(mpReportSectionTab->currentWidget());

  QList<QTableWidgetItem*> selected = current->selectedItems();

  if (selected.empty())
    {
      _addItem(current, new CQReportListItem(CDataString("\n").getCN(), mpDataModel));
    }
  else
    {
      _insertItem(current, current->row(selected.first()), new CQReportListItem(CDataString("\n").getCN(), mpDataModel));
    }

  mChanged = true;

  return;
}

void CQReportDefinition::slotAddItem()
{
  QTableWidget * current = static_cast<QTableWidget *>(mpReportSectionTab->currentWidget());

  QList<QTableWidgetItem*> selected = current->selectedItems();

  std::vector< const CDataObject * > SelectedVector =
    //    CCopasiSelectionDialog::getObjectVector(this, CQSimpleSelectionTree::NO_RESTRICTION);
    CCopasiSelectionDialog::getObjectVector(this, CQSimpleSelectionTree::AnyObject);

  CQReportListItem * pItem;

  if (SelectedVector.size() != 0)
    {
      QTableWidget * pList = static_cast<QTableWidget *>(mpReportSectionTab->currentWidget());
      std::vector< const CDataObject * >::const_iterator it = SelectedVector.begin();
      std::vector< const CDataObject * >::const_iterator end = SelectedVector.end();

      for (; it != end; ++it)
        {
          pItem = new CQReportListItem(*it);

          if (selected.empty())
            {
              _addItem(pList, pItem);
            }
          else
            {
              _insertItem(current, current->row(selected.first()), pItem);
            }
        }

      mChanged = true;
    }
}

void CQReportDefinition::setDirty()
{
  mChanged = true;
}

bool CQReportDefinition::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  mpReportDefinition = dynamic_cast< CReportDefinition * >(mpObject);

  // If the model is deleted or a new model is loaded the existing pointer
  // becomes invalid.
  if (objectType == ListViews::ObjectType::MODEL &&
      (action == ListViews::DELETE ||
       action == ListViews::ADD))
    {
      mpReportDefinition = NULL;
      return true;
    }

  if (mIgnoreUpdates ||
      objectType != ListViews::ObjectType::REPORT ||
      cn != mObjectCN ||
      action == ListViews::DELETE)
    return true;

  return load();
}

bool CQReportDefinition::leaveProtected()
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
      mpListView->switchToOtherWidget(ListViews::WidgetType::ReportTemplates, std::string());
      return false;
    }

  load();

  mpNotes->enter(mObjectCN);

  return true;
}

bool CQReportDefinition::load()
{
  if (!mpReportDefinition) return false;

  // Reset everything.
  mpHeaderList->clear();
  mpHeaderList->setRowCount(0);
  mpBodyList->clear();
  mpBodyList->setRowCount(0);
  mpFooterList->clear();
  mpFooterList->setRowCount(0);
  mpTableList->clear();
  mpTableList->setRowCount(0);

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
        _addItem(mpTableList, new CQReportListItem(*it, mpDataModel));
    }
  else
    {
      setAdvancedMode(true);

      pList = mpReportDefinition->getHeaderAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        _addItem(mpHeaderList, new CQReportListItem(*it, mpDataModel));

      pList = mpReportDefinition->getBodyAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        _addItem(mpBodyList, new CQReportListItem(*it, mpDataModel));

      pList = mpReportDefinition->getFooterAddr();

      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        _addItem(mpFooterList, new CQReportListItem(*it, mpDataModel));
    }

  mChanged = false;
  return true;
}

bool CQReportDefinition::save()
{
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
        protectedNotify(ListViews::ObjectType::REPORT, ListViews::RENAME, mObjectCN);
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

      for (i = 0, imax = mpHeaderList->rowCount(); i < imax; i++)
        {
          CQReportListItem* item = dynamic_cast<CQReportListItem*>(mpHeaderList->item(i, 0));

          if (item == NULL) continue;

          if (item->getCN().getObjectType()
              == "Separator")
            pList->push_back(mpReportDefinition->getSeparator().getCN());
          else
            pList->push_back(item->getCN());
        }

      pList = mpReportDefinition->getBodyAddr();

      for (i = 0, imax = mpBodyList->rowCount(); i < imax; i++)
        {
          CQReportListItem* item = dynamic_cast<CQReportListItem*>(mpBodyList->item(i, 0));

          if (item == NULL) continue;

          if (item->getCN().getObjectType()
              == "Separator")
            pList->push_back(mpReportDefinition->getSeparator().getCN());
          else
            pList->push_back(item->getCN());
        }

      pList = mpReportDefinition->getFooterAddr();

      for (i = 0, imax = mpFooterList->rowCount(); i < imax; i++)
        {
          CQReportListItem* item = dynamic_cast<CQReportListItem*>(mpFooterList->item(i, 0));

          if (item == NULL) continue;

          if (item->getCN().getObjectType()
              == "Separator")
            pList->push_back(mpReportDefinition->getSeparator().getCN());
          else
            pList->push_back(static_cast<CQReportListItem*>(mpFooterList->item(i, 0))->getCN());
        }
    }
  else
    {
      mpReportDefinition->setIsTable(true);

      mpReportDefinition->setTitle(mpTitleCheck->isChecked());

      pList = mpReportDefinition->getTableAddr();

      for (i = 0, imax = mpTableList->rowCount(); i < imax; i++)
        {
          CQReportListItem* item = dynamic_cast<CQReportListItem*>(mpTableList->item(i, 0));

          if (item == NULL)
            continue;

          pList->push_back(item->getCN());
        }
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
