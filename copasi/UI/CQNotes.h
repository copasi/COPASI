// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQNotes.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/08/12 15:37:53 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQNotes
#define COPASI_CQNotes

#include <QWidget>
#include <QVariant>

#include "copasi/UI/ui_CQNotes.h"

class CQNotes : public CopasiWidget, public Ui::CQNotes
{
  Q_OBJECT

public:
  CQNotes(QWidget* parent = 0, const char* name = 0);
  ~CQNotes();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:
  void slotToggleMode();

protected:
  virtual bool enterProtected();

private:
  void load();
  void save();

  bool mEditMode;
  bool mChanged;
};

#endif // COPASI_CQNotes
