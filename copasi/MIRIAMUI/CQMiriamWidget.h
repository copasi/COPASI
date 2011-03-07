// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQMiriamWidget.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:30:18 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMIRIAMWIDGET_H
#define CQMIRIAMWIDGET_H

#include <QWidget>
#include <QVariant>

#include "UI/CQSortFilterProxyModel.h"
#include "UI/CQComboDelegate.h"

#include "ui_CQMiriamWidget.h"
#include "CQCreatorDM.h"
#include "CQReferenceDM.h"
#include "CQBiologicalDescriptionDM.h"
#include "CQModifiedDM.h"

class CMIRIAMInfo;

class CQMiriamWidget : public CopasiWidget, public Ui::CQMiriamWidget
{
  Q_OBJECT

public:
  CQMiriamWidget(QWidget* parent = 0, const char* name = 0);
  ~CQMiriamWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  const CMIRIAMInfo & getMIRIAMInfo() const;
  void updateResourcesList();

protected:
  virtual bool enterProtected();

private:
  CMIRIAMInfo* mpMIRIAMInfo;
  CQCreatorDM* mpCreatorDM;
  CQReferenceDM* mpReferenceDM;
  CQBiologicalDescriptionDM* mpBiologicalDescriptionDM;
  CQModifiedDM* mpModifiedDM;
  CQSortFilterProxyModel* mpCreatorPDM;
  CQSortFilterProxyModel* mpReferencePDM;
  CQSortFilterProxyModel* mpBiologicalDescriptionPDM;
  CQSortFilterProxyModel* mpModifiedPDM;
  CQComboDelegate* mpResourceDelegate1;
  CQComboDelegate* mpResourceDelegate2;
  CQComboDelegate* mpPredicateDelegate;
  QStringList mPredicates;
  QStringList mResources;
  QStringList mReferences;
  std::vector< CQTableView * > mWidgets;
  std::vector< CQBaseDataModel * > mDMs;
  std::vector< CQSortFilterProxyModel * > mProxyDMs;
  void deleteSelectedAuthors();
  void deleteSelectedReferences();
  void deleteSelectedBiologicalDescriptions();
  void deleteSelectedModifieds();
  void keyPressEvent(QKeyEvent* ev);

protected slots:
  virtual void languageChange();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotCreatedDTChanged(QDateTime newDT);
  virtual void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
  virtual void slotCopyEvent();
};

#endif // CQMIRIAMWIDGET_H
