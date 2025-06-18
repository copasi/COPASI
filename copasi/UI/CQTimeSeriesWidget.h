// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

  virtual bool loadResult(const CCopasiTask * pTask);

  void setFramework(int framework) override;

  virtual void setTitle(const QString &title);

protected:
  bool enterProtected() override;
  bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn) override;
  bool leaveProtected() override;

protected slots:

private slots:
  void slotSave();

private:
  const CTimeSeries * mpTimeSeries;
  CQTimeSeriesDM * mpDataModel;
};

#endif // COPASI_CQTimeSeriesWidget
