// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QStringListModel>

#include "copasi/UI/ui_CQModelWidget.h"

#include <map>

class CModel;

class CQModelWidget : public CopasiWidget, public Ui::CQModelWidget
{
  Q_OBJECT

public:
  CQModelWidget(QWidget* parent = 0, const char* name = 0);
  ~CQModelWidget();

protected slots:
  virtual void slotBtnRevertClicked();
  virtual void slotBtnOKClicked();
  virtual void slotUpdateAvogadro();
  virtual void slotUnitChanged();
  virtual void slotShowCompleter();
  virtual void slotDelayed();

protected:
  virtual bool enterProtected();
  bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn) override;
  virtual bool leaveProtected();

private:
  void load();
  void save();

  // Attributes
  CModel * mpModel;

  QLineEdit * mpFocusUnit;
};

class CQStringListModel : public QStringListModel
{
};

#endif // COPASI_CQModelWidget
