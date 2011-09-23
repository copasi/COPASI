// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTimeSeriesWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/23 18:39:01 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTimeSeriesWidget
#define COPASI_CQTimeSeriesWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTimeSeriesWidget.h"

class CQTimeSeriesDM;
class CTrajectoryTask;
class CCopasiTask;

class CQTimeSeriesWidget: public CopasiWidget, public Ui::CQTimeSeriesWidget
{
  Q_OBJECT

public:
  CQTimeSeriesWidget(QWidget* parent = 0);

  virtual ~CQTimeSeriesWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  virtual bool leave();

  virtual bool loadResult(const CCopasiTask * pTask);

  virtual void setFramework(int framework);

protected:
  virtual bool enterProtected();

protected slots:

private slots:
  void slotSave();

private:
  const CTrajectoryTask * mpTask;
  CQTimeSeriesDM * mpDataModel;
};

#endif // COPASI_CQTimeSeriesWidget
