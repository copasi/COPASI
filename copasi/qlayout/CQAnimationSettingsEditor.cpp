// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qlayout/CQAnimationSettingsEditor.h>
#include <qlayout/CQCopasiAnimation.h>
#include <qlayout/CQEffectDescription.h>

CQAnimationSettingsEditor::CQAnimationSettingsEditor(QWidget *parent, Qt::WindowFlags f)
  : QDialog(parent, f)
{
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
}

void CQAnimationSettingsEditor::slotEffectRemoved()
{
}

void CQAnimationSettingsEditor::saveChanges()
{
  // go through last selection to save changes
  for (int i = 0; i < mLastSelection.size(); ++i)
    {
      QListWidgetItem* current = mLastSelection[i];
      int index = current->data(Qt::UserRole).toInt();
      widget->saveTo(mEntries[index], mLastSelection.size() > 1);
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
      widget->initFrom(mEntries[index], selected.size() > 1);
    }

  mLastSelection = selected;
}

void CQAnimationSettingsEditor::initFrom(CQCopasiAnimation* other)
{
  if (other->getScaleMode() == CQCopasiAnimation::Global)
    radGlobal->setChecked(true);
  else
    radIndividual->setChecked(true);

  std::vector<CQEffectDescription*> entries = other->getEntries();
  std::vector<CQEffectDescription*>::iterator it = entries.begin();
  mEntries.clear();

  while (it != entries.end())
    {
      CQEffectDescription* current = *it;

      QListWidgetItem* item = new QListWidgetItem(current->getCN().c_str());
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
}
