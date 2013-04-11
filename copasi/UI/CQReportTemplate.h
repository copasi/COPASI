// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#ifndef CQREPORTDEFINITION_H
#define CQREPORTDEFINITION_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQReportTemplate.h"

class CReportTemplate;

class CQReportTemplate : public CopasiWidget, public Ui::CQReportTemplate
{
  Q_OBJECT

public:
  CQReportTemplate(QWidget* parent = 0, const char* name = 0);
  ~CQReportTemplate();

  virtual bool leave();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool enterProtected();

protected slots:

private:
  bool mAdvanced;
  bool mChanged;
  CReportTemplate * mpReportTemplate;
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
  void btnTextClicked();
  void btnDeleteClicked();
  void btnUpClicked();
  void btnDownClicked();
  void chkTitleClicked();
  void btnDeleteReportClicked();
  void btnNewReportClicked();
  void btnRevertClicked();
  void btnCommitClicked();
};

#endif // CQREPORTDEFINITION_H
