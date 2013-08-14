#ifndef QANIMATION_SETTINGS_EDITOR_H
#define QANIMATION_SETTINGS_EDITOR_H

#include <vector>

#include <qdialog.h>
#include <qlayout/ui_qanimationsettingseditor.h>

class QCopasiAnimation;
class QEffectDescription;
class QAnimationSettingsEditor : public QDialog, public Ui::QAnimationSettingsEditor
{
  Q_OBJECT
public: 
  QAnimationSettingsEditor(QWidget *parent = 0, Qt::WindowFlags f = 0);
  virtual ~QAnimationSettingsEditor();
  void initFrom(QCopasiAnimation* other);
  void saveTo(QCopasiAnimation* target);
  void saveChanges();
public slots:
  void slotScaleModeChanged();
  void slotEffectAdded();
  void slotEffectRemoved();
  void slotSelectionChanged();
protected:
  std::vector<QEffectDescription*> mEntries;
  QList<QListWidgetItem*> mLastSelection;
};

#endif //QANIMATION_SETTINGS_EDITOR_H