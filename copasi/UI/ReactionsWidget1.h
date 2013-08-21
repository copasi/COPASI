// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
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

#include "UI/copasiWidget.h"
#include "model/CReactionInterface.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ParameterTable;
class MyLineEdit;

class ReactionsWidget1 : public CopasiWidget
{
  Q_OBJECT

public:
  ReactionsWidget1(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~ReactionsWidget1();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);
  void copy();

protected slots:
  virtual void slotBtnNew();
  virtual void slotBtnCopy(){}; //dummy, to bypass warnings from TabWidget connections
  virtual void slotBtnDelete();
  virtual void slotCheckBoxClicked();
  virtual void slotComboBoxSelectionChanged(const QString &);
  virtual void slotLineEditChanged();
  virtual void slotGotoFunction();
  virtual void slotNewFunction();

  //  public slots:
  virtual void slotTableChanged(int index, int sub, QString newValue);
  virtual void slotParameterStatusChanged(int index, bool local);

protected:
  virtual bool enterProtected();
  bool loadFromReaction(const CReaction* reaction);
  bool saveToReaction();
  void FillWidgetFromRI();

  CReactionInterface * mpRi;

  QGridLayout* ReactionsWidget1Layout;
  QHBoxLayout* Layout1;
  QLabel* TextLabel7;
  QLabel* TextLabel8;
  QFrame* Line2;
  QFrame* Line1;
  QFrame* Line3;
  QLabel* TextLabel6;
  MyLineEdit* LineEdit2;
  QComboBox* ComboBox1;
  QFrame* Line4;
  ParameterTable* table;
  QLineEdit* LineEdit3;
  QLabel* TextLabel5;
  QPushButton* newKinetics;
  QCheckBox* CheckBox;
  QCheckBox * mpMultiCompartment;
  QCheckBox * mpFast;
};

#endif // REACTIONSWIDGET1_H
