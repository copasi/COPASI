// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQMiriamWidget.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/04 15:19:36 $
// End CVS Header

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
#include "UI/CQDateTimeEditDelegate.h"

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
  virtual bool enter(const std::string & key = "");
  const CMIRIAMInfo & getMIRIAMInfo() const;
  void updateResourcesList();

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
  CQDateTimeEditDelegate* mpDTEDelegate;
  CQComboDelegate* mpResourceDelegate1;
  CQComboDelegate* mpResourceDelegate2;
  CQComboDelegate* mpPredicateDelegate;
  QStringList mPredicates;
  QStringList mResources;
  QStringList mReferences;
  std::vector< QTableView * > mWidgets;
  std::vector< CQBaseDataModel * > mDMs;
  std::vector< CQSortFilterProxyModel * > mProxyDMs;
  void deleteSelectedAuthor();
  void deleteSelectedReference();
  void deleteSelectedBiologicalDescription();
  void deleteSelectedModified();
  void keyPressEvent(QKeyEvent* ev);

protected slots:
  virtual void languageChange();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotCreatedDTChanged(QDateTime newDT);
  virtual void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
};

#endif // CQMIRIAMWIDGET_H
