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

#ifndef CLNAResultWidget_H__
#define CLNAResultWidget_H__

#include "copasi/UI/copasiWidget.h"
#include <QGridLayout>

class CLNAResultSubwidget;

class CLNAResultWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CLNAResultWidget(QWidget *parent = 0, const char *name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CLNAResultWidget();

  bool loadFromBackend();

protected slots:

protected:
  virtual bool enterProtected();
  bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CRegisteredCommonName & cn) override;
  virtual bool leaveProtected();

  bool saveToBackend();

  QGridLayout *mWidgetLayout;

  CLNAResultSubwidget *mCentralWidget;
};

#endif
