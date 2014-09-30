// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterOverviewWidget
#define COPASI_CQParameterOverviewWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQParameterOverviewWidget.h"

class CModelParameterSet;
class CQParameterOverviewDM;
class QSortFilterProxyModel;

class CQParameterOverviewWidget : public CopasiWidget, public Ui::CQParameterOverviewWidget
{
  Q_OBJECT

public:
  CQParameterOverviewWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQParameterOverviewWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);

private:
  virtual bool enterProtected();
  void buildSelectionList();
protected:

protected slots:
  virtual void slotBtnRevert();
  virtual void slotBtnCommit();
  virtual void slotBtnNew();
  virtual void slotBtnCopy();
  virtual void slotBtnDelete();
  virtual void slotBtnSaveToFile();
  virtual void slotBtnSaveAs();
  void slotOpenEditor(const QModelIndex & index);
  void slotCloseEditor(const QModelIndex & index);
  void slotResolve(const QModelIndex & index);

#ifdef COPASI_UNDO
  virtual void slotChangeWidget(const size_t & id);
#endif

private:
  CModelParameterSet * mpParameterSet;

  CModelParameterSet * mpParameterSetCopy;

  CQParameterOverviewDM * mpParameterSetDM;

  QSortFilterProxyModel * mpParameterSetSortDM;

  QStringList mGlobalQuantities;
};

#endif // COPASI_CQParameterOverviewWidget
