// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQTabWidget.h
 *
 *  Created on: May 8, 2012
 *      Author: shoops
 */

#ifndef COPASI_CQTabWidget
#define COPASI_CQTabWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTabWidget.h"

#include <vector>

class CQTabWidget: public CopasiWidget, public Ui::CQTabWidget
{
  Q_OBJECT

public:
  CQTabWidget(const ListViews::ObjectType & objectType, CopasiWidget * pCopasiWidget,
              QWidget * parent = 0, Qt::WindowFlags f = 0);
  virtual ~CQTabWidget();

  virtual bool leave();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  void selectTab(int index) const;

protected:
  virtual bool enterProtected();

  void load();

  bool save();

private slots:
  void slotBtnCommit();
  void slotBtnRevert();
  void slotBtnDelete();
  void slotBtnNew();

signals:
  void deleteClicked();
  void newClicked();

private:
  std::vector< CopasiWidget * > mPages;
  ListViews::ObjectType mObjectType;
  bool mIgnoreLeave;
};

#endif // COPASI_CQTabWidget
