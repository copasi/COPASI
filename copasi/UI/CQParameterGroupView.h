// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterGroupView
#define COPASI_CQParameterGroupView

#include <QtCore/QVariant>
#include <QTreeView>

class CQParameterGroupDM;
class CQComboDelegate;
class CQPushButtonDelegate;
class CCopasiParameter;
class CCopasiParameterGroup;
class QSortFilterProxyModel;

class CQParameterGroupView: public QTreeView
{
  Q_OBJECT

public:
  CQParameterGroupView(QWidget* parent = 0);

  virtual ~CQParameterGroupView();

  void setAdvanced(const bool & advanced);

  void pushGroup(CCopasiParameterGroup * pGroup);
  void popGroup(CCopasiParameterGroup * pGroup);
  void clearGroups();

public slots:
  void slotPreferenceUpdated();

protected slots:
  void slotCreateComboBox(const QModelIndex & index);
  void slotCreatePushButton(const QModelIndex & index);
  void slotCloseEditor(const QModelIndex & index);
  void slotPushButtonClicked(const QModelIndex & index);

protected:
  void modifySelectCNs(CCopasiParameterGroup & group, const CCopasiParameter & cnTemplate);

protected:
  CQParameterGroupDM * mpParameterGroupDM;
  QSortFilterProxyModel * mpSortFilterDM;

  CQComboDelegate * mpComboBoxDelegate;
  CQPushButtonDelegate * mpPushButtonDelegate;
};

#endif // COPASI_CQParameterGroupView
