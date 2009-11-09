// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMergingData.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/11/09 13:12:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMERGINGDATA_H
#define CQMERGINGDATA_H

#include <qvariant.h>
#include <string>
#include <vector>

//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <QPixmap>
#include <Q3VBoxLayout>

class QSignalMapper;

#include <QtGui/QDialog>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>
#include <QToolButton>

#include "model/CModel.h"

#include "ui_CQMergingData.h"

class CQMergingData : public QDialog, public Ui::CQMergingData
{
  Q_OBJECT

public:
  CQMergingData(QWidget* parent = 0, Qt::WindowFlags fl = 0);
  ~CQMergingData();

  std::vector< std::string > mObjectKey;
  std::vector< std::string > mColumnKey;
  std::vector< std::string > mColumnName;

protected:
  QPixmap mCopasi;
  QSignalMapper * mpBtnMap;
  QSignalMapper * mpComboMap;
  QStringList ColumnTypes;
  CModel* pModel;

protected slots:
  void slotModelObject(int row);
  void slotTypeChanged(int row);

private:
  std::string findMetaboliteKeyByName(std::string name);
//  void init();
  void load();
//  void save();
//  void destroy();
private slots:
  void slotBtnMerge();
  void slotBtnCancel();
};

#endif // CQMERGINGDATA_H
