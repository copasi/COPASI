// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ReactionsWidget1.h,v $
//   $Revision: 1.50 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/16 15:47:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QCheckBox;
class QComboBox;
class Q3Frame;
class QLabel;
class QLineEdit;
class QPushButton;
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

protected slots:
  virtual void slotBtnCancelClicked();
  virtual void slotBtnOKClicked();
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked();
  virtual void slotCheckBoxClicked();
  virtual void slotComboBoxSelectionChanged(const QString &);
  virtual void slotLineEditChanged();
  virtual void slotNewFunction();
  virtual void slotNameChanged();

  //  public slots:
  virtual void slotTableChanged(int index, int sub, QString newValue);
  virtual void slotParameterStatusChanged(int index, bool local);

protected:
  virtual bool enterProtected();
  bool loadFromReaction(const CReaction* reaction);
  bool saveToReaction();
  void FillWidgetFromRI();

  CReactionInterface * mpRi;

  Q3GridLayout* ReactionsWidget1Layout;
  Q3HBoxLayout* Layout1;
  QLabel* TextLabel4;
  QLabel* TextLabel7;
  QPushButton* commitChanges;
  QPushButton* cancelChanges;
  QPushButton* newReaction;
  QPushButton* deleteReaction;
  QLabel* TextLabel8;
  Q3Frame* Line2;
  Q3Frame* Line1;
  Q3Frame* Line3;
  QLabel* TextLabel6;
  QLineEdit* LineEdit1;
  MyLineEdit* LineEdit2;
  QComboBox* ComboBox1;
  Q3Frame* Line4;
  ParameterTable* table;
  QLineEdit* LineEdit3;
  QLabel* TextLabel5;
  QPushButton* newKinetics;
  QCheckBox* CheckBox;
  QCheckBox * mpMultiCompartment;

  //QString name;
};

#endif // REACTIONSWIDGET1_H
