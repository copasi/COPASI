// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
class CQComboDelegate;

class CQParameterOverviewWidget : public CopasiWidget, public Ui::CQParameterOverviewWidget
{
  Q_OBJECT

public:
  CQParameterOverviewWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQParameterOverviewWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);
  /**
  * This method returns the data model from all the overview widgets.
  * @return data model of this widget (or NULL if it does not have one)
  */
  virtual CQBaseDataModel* getCqDataModel();

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

  void saveParameterSet(CModelParameterSet * pParameterSet);

  void slotOpenEditor(const QModelIndex & index);
  void slotCloseEditor(const QModelIndex & index);
  void slotResolve(const QModelIndex & index);

private:
  CModelParameterSet * mpParameterSet;

  CModelParameterSet * mpParameterSetCopy;

  CQParameterOverviewDM * mpParameterSetDM;

  QSortFilterProxyModel * mpParameterSetSortDM;

  CQComboDelegate * mpComboDelegate;

  QStringList mGlobalQuantities;
};

#endif // COPASI_CQParameterOverviewWidget
