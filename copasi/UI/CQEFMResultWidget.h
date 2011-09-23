// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMResultWidget.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/23 18:39:02 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEFMResultWidget_h
#define CQEFMResultWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQEFMResultWidget.h"
#include "copasi/UI/copasiWidget.h"
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

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

  virtual bool loadResult(const CCopasiTask * pTask);

protected:
  virtual bool enterProtected();

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
