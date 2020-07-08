// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 **  $ CopasiUI/ReactionsWidget1.h
 **  $ Author  : Mudita Singhal
 **
 ** This is the header file for the Reactions Widget, i.e the second level
 ** of Reactions.
 **
 *****************************************************************************/

#ifndef REACTIONS_WIDGET1_H
#define REACTIONS_WIDGET1_H

#include "copasi/UI/ui_ReactionsWidget1.h"

#include "copasi/UI/copasiWidget.h"

class CReactionInterface;
class ParameterTable;
class MyLineEdit;

class ReactionsWidget1 : public CopasiWidget, public Ui::ReactionsWidget1
{
  Q_OBJECT

  friend class DeleteReactionCommand;
  friend class CreateNewReactionCommand;

public:
  ReactionsWidget1(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~ReactionsWidget1();

  virtual void setFramework(int framework);
  void copy();

protected slots:
  virtual void slotBtnNew();
  virtual void slotBtnCopy(); //dummy, to bypass warnings from TabWidget connections
  virtual void slotBtnDelete();
  virtual void slotCheckBoxClicked();
  virtual void slotComboBoxSelectionChanged(const QString &);
  virtual void slotLineEditChanged();
  virtual void slotGotoFunction();
  virtual void slotNewFunction();
  virtual void slotAddNoiseChanged(bool hasNoise);
  virtual void slotDefaultUnitChecked(const bool & checked);
  virtual void slotConcentrationUnitChecked(const bool & checked);
  virtual void slotAmountUnitChecked(const bool & checked);
  virtual void slotCompartmentSelectionChanged(const QString &);

  //  public slots:
  virtual void slotTableChanged(int index, int sub, QString newValue);
  virtual void slotParameterStatusChanged(int index, bool local);

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  bool loadFromReaction(const CReaction* reaction);
  bool saveToReaction();
  void FillWidgetFromRI();

  CReactionInterface * mpRi;
};

#endif // REACTIONSWIDGET1_H
