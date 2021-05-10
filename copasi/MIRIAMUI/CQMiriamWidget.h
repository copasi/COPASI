// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CQMIRIAMWIDGET_H
#define CQMIRIAMWIDGET_H

#include <QtCore/QVariant>

#include "copasi/MIRIAMUI/ui_CQMiriamWidget.h"

#include "copasi/MIRIAMUI/CQCreatorDM.h"
#include "copasi/MIRIAMUI/CQReferenceDM.h"
#include "copasi/MIRIAMUI/CQBiologicalDescriptionDM.h"
#include "copasi/MIRIAMUI/CQModifiedDM.h"

#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQComboDelegate.h"

class CMIRIAMInfo;
class CAnnotation;

class CQMiriamWidget : public CopasiWidget, public Ui::CQMiriamWidget
{
  Q_OBJECT

public:
  CQMiriamWidget(QWidget* parent = 0, const char* name = 0);
  ~CQMiriamWidget();

  const CMIRIAMInfo & getMIRIAMInfo() const;
  void updateResourcesList();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();
  virtual void showEvent(QShowEvent * event);

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
  CCommonName mObjectCNToCopy;
  CAnnotation * mpAnnotation;
  std::string mMessage;
  int mMessageType;

public slots:
  virtual void slotNotifyChanges(const CUndoData::CChangeSet & changes);

protected slots:
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotBtnBrowseReference(const QModelIndex& index);
  virtual void slotBtnBrowseDescription(const QModelIndex& index);
  virtual void slotCreatedDTChanged(QDateTime newDT);
  virtual void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
  virtual void slotCopyEvent();
  virtual void slotBtnCopy();
  virtual void slotBtnAddMe();
};

#endif // CQMIRIAMWIDGET_H
