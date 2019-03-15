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

#ifndef CQEFMResultWidget_h
#define CQEFMResultWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQEFMResultWidget.h"
#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQFluxModeDM.h"

class CCopasiTask;
class CEFMTask;
class CQEFMReactionDM;
class CQEFMSpeciesDM;
class CQEFMNetReactionDM;

class CQEFMResultWidget : public CopasiWidget, public Ui::CQEFMResultWidget
{
  Q_OBJECT

public:
  CQEFMResultWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQEFMResultWidget();

  virtual bool loadResult(const CCopasiTask * pTask);

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

protected slots:

private slots:
  void slotSave();

private:
  const CEFMTask * mpTask;

  CQSortFilterProxyModel *mpProxyModelReactions;
  CQEFMReactionDM * mpReactionDM;

  CQSortFilterProxyModel *mpProxyModelSpecies;
  CQEFMSpeciesDM * mpSpeciesDM;

  CQSortFilterProxyModel *mpProxyModelNetReactions;
  CQEFMNetReactionDM * mpNetReactionDM;
};

#endif // CQEFMResultWidget_h
