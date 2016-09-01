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

#include <QtGui/QWidget>
#include <QtCore/QVariant>

#include "copasi/UI/ui_CQModelWidget.h"

class QUndoStack;
#include "copasi/undoFramework/CCopasiUndoCommand.h"

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

protected:
  virtual bool enterProtected();

private:
  void load();
  void save();

  // Attributes
  CModel * mpModel;

  QUndoStack *mpUndoStack;
  void updateUnitComboBoxes();
};

#endif // COPASI_CQModelWidget
