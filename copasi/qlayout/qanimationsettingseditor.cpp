#include <qlayout/qanimationsettingseditor.h>
#include <qlayout/qcopasianimation.h>
#include <qlayout/qeffectdescription.h>

QAnimationSettingsEditor::QAnimationSettingsEditor(QWidget *parent, Qt::WindowFlags f )
  : QDialog(parent, f)
{
  setupUi(this);
}

QAnimationSettingsEditor::~QAnimationSettingsEditor()
{
}

void QAnimationSettingsEditor::slotScaleModeChanged()
{
}

void QAnimationSettingsEditor::slotEffectAdded()
{
}

void QAnimationSettingsEditor::slotEffectRemoved()
{
}

void QAnimationSettingsEditor::saveChanges()
{
  // go through last selection to save changes
  for (int i = 0; i < mLastSelection.size();++i)
  {
    QListWidgetItem* current = mLastSelection[i];
    int index = current->data(Qt::UserRole).toInt();
    widget->saveTo(mEntries[index], mLastSelection.size() > 1);
  }

}

void QAnimationSettingsEditor::slotSelectionChanged() 
{
  saveChanges();

  // fill with new entries
  QList<QListWidgetItem*> selected = listWidget->selectedItems();
  for (int i = 0; i < selected.size();++i)
  {
    QListWidgetItem* current = selected[i];
    int index = current->data(Qt::UserRole).toInt();
    widget->initFrom(mEntries[index], selected.size() > 1);
  }

  mLastSelection = selected;

}

void QAnimationSettingsEditor::initFrom(QCopasiAnimation* other)
{
  if (other->getScaleMode() == QCopasiAnimation::Global)
    radGlobal->setChecked(true);
  else
    radIndividual->setChecked(true);

  std::vector<QEffectDescription*> entries = other->getEntries();
  std::vector<QEffectDescription*>::iterator it = entries.begin();
  mEntries.clear();
  while(it != entries.end())
  {
    QEffectDescription* current = *it;

    QListWidgetItem* item = new QListWidgetItem(current->getCN().c_str());
    item->setData(Qt::UserRole, (int)mEntries.size());
    listWidget->addItem(item);
    mEntries.push_back(current);

    ++it;
  }
  

}

void QAnimationSettingsEditor::saveTo(QCopasiAnimation* target)
{
  saveChanges();

  if (radGlobal->isChecked())
    target->setScaleMode(QCopasiAnimation::Global);
  else 
    target->setScaleMode(QCopasiAnimation::Individual);

}
