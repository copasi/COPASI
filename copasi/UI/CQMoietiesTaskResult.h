// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
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
  virtual void setFramework(int framework);
  void load();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn) override;
  virtual bool leaveProtected();

  CMoietiesTask * mpMoietiesTask;

protected slots:

private:
  void init();

private slots:
  void slotSave(void);
  void slotCreateGlobalQuantity(const QModelIndex & index);
};

#endif // CQMOIETIESTASKRESULT_H
