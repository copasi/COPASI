// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTimeSeriesWidget
#define COPASI_CQTimeSeriesWidget

#include <QtCore/QVariant>
#include <QtCore/QString>

#include "copasi/UI/ui_CQTimeSeriesWidget.h"

class CQTimeSeriesDM;
class CTimeSeries;
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

  virtual void setTitle(const QString &title);

protected:
  virtual bool enterProtected();

protected slots:

private slots:
  void slotSave();

private:
  const CTimeSeries * mpTimeSeries;
  CQTimeSeriesDM * mpDataModel;
};

#endif // COPASI_CQTimeSeriesWidget
