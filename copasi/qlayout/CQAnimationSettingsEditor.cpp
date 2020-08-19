// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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
      item->setData(Qt::UserRole, listWidget->count());
      listWidget->addItem(item);
      ++it;
    }

  listWidget->blockSignals(false);
}

void CQAnimationSettingsEditor::slotEffectRemoved()
{

  // fill with new entries
  QList< QListWidgetItem * > selected = mLastSelection;

  listWidget->blockSignals(true);

  for (int i = selected.size(); i != 0; --i)
    {
      QListWidgetItem * current = selected[i - 1];
      int index = current->data(Qt::UserRole).toInt();
      mEntries.erase(mEntries.begin() + index);
      listWidget->removeItemWidget(current);
    }

  updateListFromEntries();

  mLastSelection.clear();

}

void CQAnimationSettingsEditor::saveChanges()
{
  // go through last selection to save changes
  for (int i = 0; i < mLastSelection.size(); ++i)
    {
      QListWidgetItem* current = mLastSelection[i];
      int index = current->data(Qt::UserRole).toInt();
      widget->saveTo(&mEntries[index], mLastSelection.size() > 1);
    }
}

void CQAnimationSettingsEditor::slotSelectionChanged()
{
  saveChanges();

  // fill with new entries
  QList<QListWidgetItem*> selected = listWidget->selectedItems();

  for (int i = 0; i < selected.size(); ++i)
    {
      QListWidgetItem* current = selected[i];
      int index = current->data(Qt::UserRole).toInt();
      widget->initFrom(&mEntries[index], selected.size() > 1);
    }

  mLastSelection = selected;
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

  while (it != entries.end())
    {
      CQEffectDescription current = *it;

      QListWidgetItem* item = new QListWidgetItem(FROM_UTF8(current.getDisplayName()));
      item->setData(Qt::UserRole, (int)mEntries.size());
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
