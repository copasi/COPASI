// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQModelWidget.h
 *
 *  Created on: Aug 13, 2010
 *      Author: shoops
 */

#ifndef COPASI_CQModelWidget
#define COPASI_CQModelWidget

#include <QWidget>
#include <QtCore/QVariant>

#include "copasi/UI/ui_CQModelWidget.h"

class QUndoStack;
#include "copasi/undoFramework/CCopasiUndoCommand.h"

#include <map>

class CModel;

class CQModelWidget : public CopasiWidget, public Ui::CQModelWidget
{
  Q_OBJECT

public:
  CQModelWidget(QWidget* parent = 0, const char* name = 0);
  ~CQModelWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

  bool changeValue(CCopasiUndoCommand::Type type, const QVariant& newValue);

protected slots:
  virtual void slotBtnRevertClicked();
  virtual void slotBtnOKClicked();
  virtual void slotUpdateAvogadro();

protected:
  virtual bool enterProtected();

private:
  void load();
  void save();

  // Attributes
  CModel * mpModel;

  QUndoStack *mpUndoStack;
  void updateUnitComboBoxes();

  std::map<std::string, int> mTimeUnitMap;
  std::map<std::string, int> mQuantityUnitMap;
  std::map<std::string, int> mVolumeUnitMap;
  std::map<std::string, int> mAreaUnitMap;
  std::map<std::string, int> mLengthUnitMap;
};

#endif // COPASI_CQModelWidget
