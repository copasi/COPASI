// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/08/16 18:43:07 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QVariant>

#include "copasi/UI/ui_CQModelWidget.h"

class CModel;

class CQModelWidget : public CopasiWidget, public Ui::CQModelWidget
{
  Q_OBJECT

public:
  CQModelWidget(QWidget* parent = 0, const char* name = 0);
  ~CQModelWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

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
};

#endif // COPASI_CQModelWidget
