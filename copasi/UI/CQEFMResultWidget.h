// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMResultWidget.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/29 16:35:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEFMResultWidget_h
#define CQEFMResultWidget_h

#include <qvariant.h>

#include "copasi/UI/ui_CQEFMResultWidget.h"
#include "copasi/UI/copasiWidget.h"
#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQFluxModeDM.h"

class CCopasiTask;
class CEFMTask;

class CQEFMResultWidget : public CopasiWidget, public Ui::CQEFMResultWidget
{
  Q_OBJECT

public:
  CQEFMResultWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQEFMResultWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

  virtual bool loadResult(const CCopasiTask * pTask);

protected:
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();

private slots:
  void slotSave();

private:
  const CEFMTask * mpTask;
};

#endif // CQEFMResultWidget_h
