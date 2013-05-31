// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMergingData.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/15 17:07:53 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMERGINGDATA_H
#define CQMERGINGDATA_H

#include <string>
#include <vector>

#include <QPixmap>

class QSignalMapper;

#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <QToolButton>

#include "model/CModel.h"

#include "ui_CQMergingData.h"

class CQMergingData : public QDialog, public Ui::CQMergingData
{
  Q_OBJECT

public:
  CQMergingData(QWidget* parent = 0, Qt::WindowFlags fl = 0, bool simple = false);
  ~CQMergingData();

  std::map<QTreeWidgetItem*, CModelEntity*> mItemMap1;
  std::map<QTreeWidgetItem*, CModelEntity*> mItemMap2;
  
  std::vector< std::string > mObjectKey;
  std::vector< std::string > mColumnKey;
  std::vector< std::string > mColumnName;

protected:
  QSignalMapper * mpBtnMap;
  QSignalMapper * mpComboMap;
  QStringList ColumnTypes;
  CModel* pModel;

protected slots:
  void slotModelObject(int row);
  void slotTypeChanged(int row);

private:
 
  void fillTree(QTreeWidget* pW, const CModel* pModel, std::map<QTreeWidgetItem*, CModelEntity*>& itemMap);

  
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
