// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <copasi/qlayout/CQAnimationSettingsEditor.h>
#include <copasi/qlayout/CQCopasiAnimation.h>
#include <copasi/qlayout/CQEffectDescription.h>
#include <copasi/UI/qtUtilities.h>

#include <copasi/UI/CCopasiSelectionDialog.h>
#include <copasi/UI/CQCopasiApplication.h>
#include <copasi/UI/copasiui3window.h>
#include <copasi/UI/listviews.h>
#include <copasi/core/CDataObjectReference.h>
#include <copasi/resourcesUI/CQIconResource.h>

CQAnimationSettingsEditor::CQAnimationSettingsEditor(QWidget *parent, Qt::WindowFlags f)
  : QDialog(parent, f)
{
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
  setupUi(this);
}

CQAnimationSettingsEditor::~CQAnimationSettingsEditor()
{
}

void CQAnimationSettingsEditor::slotScaleModeChanged()
{
}

void CQAnimationSettingsEditor::slotEffectAdded()
{
  // get datamodel
  // open object browser

  std::vector< const CDataObject * > objects =
    CCopasiSelectionDialog::getObjectVector(
      (dynamic_cast< CQCopasiApplication * >(qApp))
      ->getMainWindow()
      ->getMainWidget(),
      CQSimpleSelectionTree::NumericValues);

for (auto * item : objects)
    {
      auto * parent = item->getObjectParent();

      if (parent == NULL)
        continue;

      mEntries.push_back(CQEffectDescription(parent->getCN(), item->getCN()));
    }

  // add effects for selected items
  updateListFromEntries();
}

void CQAnimationSettingsEditor::updateListFromEntries()
{
  listWidget->blockSignals(true);
  listWidget->clearSelection();
  listWidget->clear();

  std::vector< CQEffectDescription >::iterator it = mEntries.begin();

  while (it != mEntries.end())
    {
      CQEffectDescription current = *it;

      QListWidgetItem * item = new QListWidgetItem(FROM_UTF8(current.getDisplayName()));
      item->setData(Qt::UserRole, FROM_UTF8(current.getDataCN()));
      listWidget->addItem(item);
      ++it;
    }

  listWidget->blockSignals(false);
}

CQEffectDescription* CQAnimationSettingsEditor::getEntry(const QString & dataCN)
{
  for (auto it = mEntries.begin(); it != mEntries.end(); ++it)
    {
      if (it->getDataCN() == TO_UTF8(dataCN))
        {
          return &(*it);
        }
    }

  return NULL;
}

void CQAnimationSettingsEditor::removeEntry(const QString& dataCN)
{
  for (auto it = mEntries.begin(); it != mEntries.end(); ++it)
    {
      if (it->getDataCN() == TO_UTF8(dataCN))
        {
          mEntries.erase(it);
          return;
        }
    }
}

void CQAnimationSettingsEditor::slotEffectRemoved()
{

  // fill with new entries
  QList< std::pair<QString, QString>> selected = mLastSelection;

  listWidget->blockSignals(true);

for (auto & entry : selected)
    {
      QList< QListWidgetItem * > items = listWidget->findItems(entry.first, Qt::MatchExactly);

      if (items.size() == 0)
        continue;

      QListWidgetItem * current = items[0];
      listWidget->removeItemWidget(current);
      removeEntry(entry.second);
    }

  updateListFromEntries();

  mLastSelection.clear();

}

void CQAnimationSettingsEditor::saveChanges()
{
  // go through last selection to save changes
  for (int i = 0; i < mLastSelection.size(); ++i)
    {
      QList< QListWidgetItem * > items = listWidget->findItems(mLastSelection[i].first, Qt::MatchExactly);

      if (items.size() == 0)
        continue;

      CQEffectDescription * current = getEntry(mLastSelection[i].second);

      if (current == NULL)
        continue;

      widget->saveTo(current, mLastSelection.size() > 1);
    }
}

void CQAnimationSettingsEditor::slotSelectionChanged()
{
  saveChanges();

  // fill with new entries
  QModelIndexList selected = listWidget->selectionModel()->selectedIndexes();
  mLastSelection = QList<std::pair<QString, QString>>();

  for (int i = 0; i < selected.size(); ++i)
    {
      QListWidgetItem * current = listWidget->item(selected.at(i).row());
      QString dataCN = current->data(Qt::UserRole).toString();
      CQEffectDescription * entry = getEntry(dataCN);

      if (current == NULL)
        continue;

      widget->initFrom(entry, selected.size() > 1);
      mLastSelection.append(std::make_pair(current->text(), dataCN));

    }

}

void CQAnimationSettingsEditor::initFrom(CQCopasiAnimation* other)
{
  if (other->getScaleMode() == CQCopasiAnimation::Global)
    radGlobal->setChecked(true);
  else
    radIndividual->setChecked(true);

  std::vector<CQEffectDescription> entries = other->getEntries();
  std::vector<CQEffectDescription>::iterator it = entries.begin();
  mEntries.clear();
  mLastSelection.clear();

  while (it != entries.end())
    {
      CQEffectDescription current = *it;

      QListWidgetItem* item = new QListWidgetItem(FROM_UTF8(current.getDisplayName()));
      item->setData(Qt::UserRole, FROM_UTF8(current.getDataCN()));
      listWidget->addItem(item);
      mEntries.push_back(current);

      ++it;
    }
}

void CQAnimationSettingsEditor::saveTo(CQCopasiAnimation* target)
{
  saveChanges();

  if (radGlobal->isChecked())
    target->setScaleMode(CQCopasiAnimation::Global);
  else
    target->setScaleMode(CQCopasiAnimation::Individual);

  target->getEntries() = mEntries;
}
