// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMOIETIESTASKRESULT_H
#define CQMOIETIESTASKRESULT_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQMoietiesTaskResult.h"

class QSignalMapper;
class CMoietiesTask;

class CQMoietiesTaskResult : public CopasiWidget, public Ui::CQMoietiesTaskResult
{
  Q_OBJECT

public:
  CQMoietiesTaskResult(QWidget* parent = 0, const char* name = 0);
  ~CQMoietiesTaskResult();

  void clear();
  virtual bool leave();
  virtual void setFramework(int framework);
  void load();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool enterProtected();

  CMoietiesTask * mpMoietiesTask;

protected slots:

private:
  void init();

private slots:
  void slotSave(void);
  void slotCreateGlobalQuantity(const QModelIndex & index);
};

#endif // CQMOIETIESTASKRESULT_H
