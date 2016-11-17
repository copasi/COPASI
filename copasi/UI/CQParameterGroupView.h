// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterGroupView
#define COPASI_CQParameterGroupView

#include <QtCore/QVariant>
#include <QtGui/QTreeView>

#include "copasi/utilities/CCopasiParameterGroup.h"

class CQParameterGroupDM;
class CQComboDelegate;
class CQPushButtonDelegate;
class CCopasiParameterGroup;

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

protected slots:

protected slots:
  void slotCreateComboBox(const QModelIndex & index);
  void slotCreatePushButton(const QModelIndex & index);
  void slotCloseEditor(const QModelIndex & index);
  void slotPushButtonClicked(const QModelIndex & index);

protected:
  void modifySelectCNs(CCopasiParameterGroup & group, const CCopasiParameter & cnTemplate);

protected:
  CQParameterGroupDM * mpParameterGroupDM;
  CQComboDelegate * mpComboBoxDelegate;
  CQPushButtonDelegate * mpPushButtonDelegate;
};

#endif // COPASI_CQParameterGroupView
