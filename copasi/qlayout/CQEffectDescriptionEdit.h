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

#ifndef QEFFECT_DESCRIPTION_EDIT_H
#define QEFFECT_DESCRIPTION_EDIT_H

#include <copasi/qlayout/ui_CQEffectDescriptionEdit.h>

class CQEffectDescription;
class CQEffectDescriptionEdit : public QWidget, public Ui::CQEffectDescriptionEdit
{
  Q_OBJECT
public:
  CQEffectDescriptionEdit(QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
  ~CQEffectDescriptionEdit();
  void initFrom(const CQEffectDescription* other, bool multiple = false);
  void saveTo(CQEffectDescription* other, bool multiple = false);
  CQEffectDescription* toDescription() const;

public slots:
  void slotModeChanged();
  void slotScaleEndChanged(QString);
  void slotScaleStartChanged(QString);
  void slotSelectObject();
  void slotSelectDataObject();
  void slotSelectColorEnd();
  void slotSelectColorStart();
protected:
  CQEffectDescription* mpCurrent;
};

#endif //QEFFECT_DESCRIPTION_EDIT_H
