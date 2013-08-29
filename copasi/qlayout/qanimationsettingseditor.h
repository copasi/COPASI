// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QANIMATION_SETTINGS_EDITOR_H
#define QANIMATION_SETTINGS_EDITOR_H

#include <vector>

#include <qdialog.h>
#include <qlayout/ui_qanimationsettingseditor.h>

class CQCopasiAnimation;
class CQEffectDescription;
class CQAnimationSettingsEditor : public QDialog, public Ui::CQAnimationSettingsEditor
{
  Q_OBJECT
public:
  CQAnimationSettingsEditor(QWidget *parent = 0, Qt::WindowFlags f = 0);
  virtual ~CQAnimationSettingsEditor();
  void initFrom(CQCopasiAnimation* other);
  void saveTo(CQCopasiAnimation* target);
  void saveChanges();
public slots:
  void slotScaleModeChanged();
  void slotEffectAdded();
  void slotEffectRemoved();
  void slotSelectionChanged();
protected:
  std::vector<CQEffectDescription*> mEntries;
  QList<QListWidgetItem*> mLastSelection;
};

#endif //QANIMATION_SETTINGS_EDITOR_H
