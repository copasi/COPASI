// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CQEFMListWidget
#define COPASI_CQEFMListWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQEFMListWidget.h"
#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQFluxModeDM.h"

class CEFMTask;

class CQEFMListWidget : public QWidget, public Ui::CQEFMListWidget
{
  Q_OBJECT

public:
  CQEFMListWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQEFMListWidget();

  bool loadResult(const CEFMTask * pTask);

signals:
  void initFilter();

protected slots:
  virtual void slotFilterChanged();

private:
  const CEFMTask * mpTask;
  CQSortFilterProxyModel *mpProxyModel;
  CQFluxModeDM * mpFluxModeDM;
};

#endif // COPASI_CQEFMListWidget
