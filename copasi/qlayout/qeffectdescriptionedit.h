// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QEFFECT_DESCRIPTION_EDIT_H
#define QEFFECT_DESCRIPTION_EDIT_H

#include <qlayout/ui_qeffectdescriptionedit.h>

class CQEffectDescription;
class CQEffectDescriptionEdit : public QWidget, public Ui::CQEffectDescriptionEdit
{
  Q_OBJECT
public:
  CQEffectDescriptionEdit(QWidget* parent = 0, Qt::WindowFlags f = 0);
  ~CQEffectDescriptionEdit();
  void initFrom(const CQEffectDescription* other, bool multiple = false);
  void saveTo(CQEffectDescription* other, bool multiple = false);
  CQEffectDescription* toDescription() const;

public slots:
  void slotModeChanged();
  void slotScaleEndChanged(QString);
  void slotScaleStartChanged(QString);
  void slotSelectObject();
  void slotSelectColorEnd();
  void slotSelectColorStart();
protected:
  CQEffectDescription* mpCurrent;
};

#endif //QEFFECT_DESCRIPTION_EDIT_H
