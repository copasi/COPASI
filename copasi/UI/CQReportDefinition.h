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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQREPORTDEFINITION_H
#define CQREPORTDEFINITION_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQReportDefinition.h"

class CReportDefinition;
class QAction;

class CQReportDefinition : public CopasiWidget, public Ui::CQReportDefinition
{
  Q_OBJECT

public:
  CQReportDefinition(QWidget* parent = 0, const char* name = 0);
  virtual ~CQReportDefinition();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

protected slots:

private:
  bool mAdvanced;
  bool mChanged;
  CReportDefinition * mpReportDefinition;
  QString mOldComment;

  bool load();
  bool save();
  bool setAdvancedMode(const bool & advanced);

private slots:
  void nameChanged(const QString & string);
  void taskChanged(const QString & string);
  void commentChanged();
  void separatorChanged(const QString & string);
  void precisionChanged(const QString & string);
  void chkTabClicked();
  void btnAdvancedClicked();
  void btnItemClicked();
  void btnSeparatorClicked();
  void btnLineBreakClicked();
  void btnTextClicked();
  void btnDeleteClicked();
  void btnUpClicked();
  void btnDownClicked();
  void chkTitleClicked();
  void btnDeleteReportClicked();
  void btnNewReportClicked();
  void btnCopyReportClicked();
  void btnRevertClicked();
  void btnCommitClicked();
  void slotDeleteCurrentItem();
  void slotEditCurrentItem();
  void slotEditCurrentItemText();
  void slotAddSeparator();
  void slotAddLineBreak();
  void slotAddItem();
  void setDirty();

private:

  void _setup(QTableWidget* pList);

  QAction* mpActSeparator;
};

#endif // CQREPORTDEFINITION_H
