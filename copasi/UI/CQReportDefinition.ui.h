/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportDefinition.ui.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/12 12:56:31 $
   End CVS Header */

#include <qmessagebox.h>

#include "CQReportListItem.h"
#include "CCopasiSelectionDialog.h"
#include "CQTextDialog.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"
#include "report/CCopasiStaticString.h"

void CQReportDefinition::nameChanged()
{mChanged = true;}

void CQReportDefinition::taskChanged()
{mChanged = true;}

void CQReportDefinition::commentChanged()
{mChanged = true;}

void CQReportDefinition::separatorChanged()
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
      if (QMessageBox::Ok ==
          QMessageBox::question(NULL, "Report Conversion",
                                "Converting an advanced report to a table may result in loss of customization.\n"
                                "Do you want to proceed?",
                                QMessageBox::Ok,
                                QMessageBox::Cancel | QMessageBox::Default | QMessageBox::Escape,
                                QMessageBox::NoButton))
        {
          // We convert the body without the separators to a table.
          mpTableList->clear();

          unsigned C_INT32 i, imax;
          for (i = 0, imax = mpBodyList->numRows(); i < imax; i++)
            if (static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN().getObjectType()
                != "Separator")
              new CQReportListItem(mpTableList, static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN());

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

      mpReportDefinition = new CReportDefinition();

      // We avoid the renaming signal.
      mpName->setText(FROM_UTF8(mpReportDefinition->getObjectName()));

      mChanged = true;
      save();

      mpReportDefinition->preCompileTable();
      mpReportDefinition->setIsTable(false);

      load();

      delete mpReportDefinition;

      mpReportDefinition = pStore;
      // Reset the name in the display.
      mpName->setText(FROM_UTF8(mpReportDefinition->getObjectName()));
      mChanged = true;
    }
}

void CQReportDefinition::btnItemClicked()
{
  CModel* pModel = CCopasiDataModel::Global->getModel();
  if (!pModel) return;

  CCopasiSelectionDialog* pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(pModel);
  std::vector<CCopasiObject *> SelectedVector;
  pBrowseDialog->setOutputVector(&SelectedVector);

  if (pBrowseDialog->exec () != QDialog::Rejected &&
      SelectedVector.size() != 0)
    {
      QListBox * pList = static_cast<QListBox *>(mpReportSectionTab->currentPage());
      std::vector<CCopasiObject *>::const_iterator it = SelectedVector.begin();
      std::vector<CCopasiObject *>::const_iterator end = SelectedVector.end();

      for (; it != end; ++it)
        new CQReportListItem(pList, *it);

      mChanged = true;
    }

  delete pBrowseDialog;
  return;
}

void CQReportDefinition::btnSeparatorClicked()
{
  CCopasiReportSeparator Separator;
  if (mpTabCheck->isChecked())
    Separator = "\t";
  else
    Separator = (const char *) mpSeparator->text().utf8();

  QListBox * pList = static_cast<QListBox *>(mpReportSectionTab->currentPage());
  new CQReportListItem(pList, Separator.getCN());

  mChanged = true;
  return;
}

void CQReportDefinition::btnTextClicked()
{
  CQTextDialog * pDialog = new CQTextDialog(this);

  if (pDialog->exec() == QDialog::Accepted &&
      pDialog->getText() != "")
    {
      CCopasiStaticString Text((const char *) pDialog->getText().utf8());
      QListBox * pList = static_cast<QListBox *>(mpReportSectionTab->currentPage());
      new CQReportListItem(pList, Text.getCN());
    }

  delete pDialog;

  mChanged = true;
  return;
}

void CQReportDefinition::btnDeleteClicked()
{
  QListBox * pList = static_cast<QListBox *>(mpReportSectionTab->currentPage());
  QListBoxItem * pNewSelection = NULL;
  unsigned C_INT32 i, multipleSelection;

  for (i = pList->count() - 1, multipleSelection = 0; i < ULONG_MAX; i--)
    if (pList->isSelected(i))
      {
        pList->removeItem(i);
        if (!pNewSelection) pNewSelection = pList->item(i); // We select the next.

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
      pList->setCurrentItem(pNewSelection);
      pList->setSelected(pNewSelection, TRUE);
    }

  return;
}

void CQReportDefinition::btnUpClicked()
{
  QListBox * pList = static_cast<QListBox *>(mpReportSectionTab->currentPage());
  unsigned C_INT32 i, multipleSelection;

  QListBoxItem * pAfter;
  QListBoxItem * pMove;

  for (i = pList->count() - 1, multipleSelection = 0; i < ULONG_MAX; i--)
    if (pList->isSelected(i))
      {
        if (multipleSelection == 0) pAfter = pList->item(i);
        multipleSelection++;
      }
    else if (multipleSelection > 0)
      {
        pMove = pList->item(i);

        if (pMove)
          {
            pList->takeItem(pMove);
            pList->insertItem(pMove, pAfter);

            multipleSelection = 0;
            mChanged = true;
          }
      }

  // Unselect things we can not move.
  for (i = 0; i < multipleSelection; i++)
    pList->setSelected(i, false);

  return;
}

void CQReportDefinition::btnDownClicked()
{
  QListBox * pList = static_cast<QListBox *>(mpReportSectionTab->currentPage());
  unsigned C_INT32 i, imax, multipleSelection, before;

  QListBoxItem * pMove;

  // Find the index of the first selected item.
  for (i = 0, imax = pList->count(), multipleSelection = 0; i < imax; i++)
    if (pList->isSelected(i))
      {
        if (multipleSelection == 0) before = i;
        multipleSelection++;
      }
    else if (multipleSelection > 0)
      {
        pMove = pList->item(i);

        if (pMove)
          {
            pList->takeItem(pMove);
            pList->insertItem(pMove, pList->item(before - 1));

            multipleSelection = 0;
            mChanged = true;
          }
      }

  // Unselect things we can not move.
  for (i = pList->count() - multipleSelection, imax = pList->count(); i < imax; i++)
    pList->setSelected(i, false);

  return;
}

void CQReportDefinition::chkTitleClicked()
{mChanged = true;}

void CQReportDefinition::btnDeleteReportClicked()
{
  unsigned C_INT32 Index, Size;

  Index = CCopasiDataModel::Global->getReportDefinitionList()->CCopasiVector<CReportDefinition>::getIndex(mpReportDefinition);
  CCopasiDataModel::Global->getReportDefinitionList()->removeReportDefinition(mKey);

  Size = CCopasiDataModel::Global->getReportDefinitionList()->size();

  if (Size > 0)
    enter((*CCopasiDataModel::Global->getReportDefinitionList())[std::min(Index, Size - 1)]->getKey());

  protectedNotify(ListViews::REPORT, ListViews::DELETE, mKey);
}

void CQReportDefinition::btnNewReportClicked()
{
  std::string Name = "report";

  int i = 0;
  CReportDefinition* pRep;
  while (!(pRep = CCopasiDataModel::Global->getReportDefinitionList()->createReportDefinition(Name, "")))
    {
      i++;
      Name = "report_";
      Name += (const char *) QString::number(i).utf8();
    }

  protectedNotify(ListViews::REPORT, ListViews::ADD);
  enter(pRep->getKey());
}

void CQReportDefinition::btnRevertClicked()
{load();}

void CQReportDefinition::btnCommitClicked()
{save();}

void CQReportDefinition::init()
{
  mKey = "";
  mpReportDefinition = NULL;

  // We start with the table since this is simpler.
  setAdvancedMode(false);

  unsigned C_INT32 i;
  for (i = 0; CCopasiTask::TypeName[i] != ""; i++)
    mpTaskBox->insertItem(FROM_UTF8(CCopasiTask::TypeName[i]));

  mpHeaderList->setSelectionMode(QListBox::Multi);
  mpBodyList->setSelectionMode(QListBox::Multi);
  mpFooterList->setSelectionMode(QListBox::Multi);
  mpTableList->setSelectionMode(QListBox::Multi);
}

void CQReportDefinition::destroy()
{}

bool CQReportDefinition::update(ListViews::ObjectType objectType,
                                ListViews::Action action,
                                const std::string & key)
{
  if (key != mKey) return true;
  return load();
}

bool CQReportDefinition::leave()
{return save();}

bool CQReportDefinition::enter(const std::string & key)
{
  mKey = key;
  mpReportDefinition = dynamic_cast<CReportDefinition *>(GlobalKeys.get(mKey));

  return load();
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
  mpTaskBox->setCurrentItem(mpReportDefinition->getTaskType());
  mpCommentEdit->setText(FROM_UTF8(mpReportDefinition->getComment()));

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
        new CQReportListItem(mpTableList, *it);
    }
  else
    {
      setAdvancedMode(true);

      pList = mpReportDefinition->getHeaderAddr();
      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        new CQReportListItem(mpHeaderList, *it);

      pList = mpReportDefinition->getBodyAddr();
      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        new CQReportListItem(mpBodyList, *it);

      pList = mpReportDefinition->getFooterAddr();
      for (it = pList->begin(), end = pList->end(); it != end; ++it)
        new CQReportListItem(mpFooterList, *it);
    }

  mChanged = false;
  return true;
}

bool CQReportDefinition::save()
{
  if (!mChanged) return true;
  if (!mpReportDefinition) return false;

  if (mpReportDefinition->getObjectName() != (const char*) mpName->text().utf8())
    {
      mpReportDefinition->setObjectName((const char*) mpName->text().utf8());
      protectedNotify(ListViews::REPORT, ListViews::RENAME, mKey);
    }

  mpReportDefinition->setTaskType((CCopasiTask::Type) mpTaskBox->currentItem());
  mpReportDefinition->setComment((const char*) mpCommentEdit->text().utf8());

  CCopasiReportSeparator Separator;
  if (mpTabCheck->isChecked())
    Separator = "\t";
  else
    Separator = (const char *) mpSeparator->text().utf8();
  mpReportDefinition->setSeparator(Separator);

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
      for (i = 0, imax = mpHeaderList->numRows(); i < imax; i++)
        if (static_cast<CQReportListItem *>(mpHeaderList->item(i))->getCN().getObjectType()
            == "Separator")
          pList->push_back(Separator.getCN());
        else
          pList->push_back(static_cast<CQReportListItem *>(mpHeaderList->item(i))->getCN());

      pList = mpReportDefinition->getBodyAddr();
      for (i = 0, imax = mpBodyList->numRows(); i < imax; i++)
        if (static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN().getObjectType()
            == "Separator")
          pList->push_back(Separator.getCN());
        else
          pList->push_back(static_cast<CQReportListItem *>(mpBodyList->item(i))->getCN());

      pList = mpReportDefinition->getFooterAddr();
      for (i = 0, imax = mpFooterList->numRows(); i < imax; i++)
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
      for (i = 0, imax = mpTableList->numRows(); i < imax; i++)
        pList->push_back(static_cast<CQReportListItem *>(mpTableList->item(i))->getCN());
    }

  mChanged = false;
  return false;
}

bool CQReportDefinition::setAdvancedMode(const bool & advanced)
{
  if (advanced)
    {
      mAdvanced = true;

      mpBtnAdvanced->setText("Advanced <<");
      mpReportSectionTab->setTabEnabled(mpTableList, false);
      mpReportSectionTab->setTabEnabled(mpHeaderList, true);
      mpReportSectionTab->setTabEnabled(mpBodyList, true);
      mpReportSectionTab->setTabEnabled(mpFooterList, true);
      mpReportSectionTab->setCurrentPage(2);
      mpBtnSeparator->show();
      mpBtnText->show();
      mpTitleCheck->hide();
    }
  else
    {
      mAdvanced = false;

      mpBtnAdvanced->setText("Advanced >>");
      mpReportSectionTab->setTabEnabled(mpTableList, true);
      mpReportSectionTab->setTabEnabled(mpHeaderList, false);
      mpReportSectionTab->setTabEnabled(mpBodyList, false);
      mpReportSectionTab->setTabEnabled(mpFooterList, false);
      mpReportSectionTab->setCurrentPage(0);
      mpBtnSeparator->hide();
      mpBtnText->hide();
      mpTitleCheck->show();
    }

  return true;
}
