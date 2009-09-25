// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.h,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/09/25 08:31:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMODELVALUE_H
#define CQMODELVALUE_H

/*
#include <qvariant.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <Q3Frame>
#include <QPixmap>
#include <QLabel>
 */

class CQExpressionWidget;
class CModelValue;
class CExpression;

/*
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
 */

#include "ui_CQModelValue.h"

#include <string>

#include "CQExpressionMmlWidget.h"
//#include "CQExpressionMmlStackedWidget.h"
#include "copasiWidget.h"

class CQModelValue : public CopasiWidget, public Ui::CQModelValue
{
  Q_OBJECT

public:
  CQModelValue(QWidget* parent = 0, const char* name = 0);
  ~CQModelValue();

  virtual bool leave();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();

private:
  std::vector< int > mItemToType;
  CModelValue * mpModelValue;
  bool mChanged;
  bool mExpressionValid;
  bool mInitialExpressionValid;

  void init();
  void destroy();
  void load();
  void save();

private slots:
  void slotBtnCommit();
  void slotBtnRevert();
  void slotBtnNew();
  void slotBtnDelete();
  void slotTypeChanged(int type);
  void slotExpressionValid(bool valid);
  void slotInitialExpressionValid(bool valid);
  void slotNameLostFocus();
  void slotInitialTypeChanged(bool useInitialAssignment);
};

#endif // CQMODELVALUE_H
