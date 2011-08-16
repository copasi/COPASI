// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQComboDelegate.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/08/16 18:47:25 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQComboDelegate_H
#define CQComboDelegate_H

#include <QItemDelegate>

class CQComboDelegate : public QItemDelegate
{
  Q_OBJECT

public:
  CQComboDelegate(const QStringList* pComboItems,
                  QObject *parent = NULL);

  virtual ~CQComboDelegate();

  virtual QWidget * createEditor(QWidget * parent,
                                 const QStyleOptionViewItem & option,
                                 const QModelIndex & index) const;

  virtual void setEditorData(QWidget * editor,
                             const QModelIndex & index) const;

  virtual void setModelData(QWidget * editor,
                            QAbstractItemModel * model,
                            const QModelIndex & index) const;

  virtual void updateEditorGeometry(QWidget * editor,
                                    const QStyleOptionViewItem & option,
                                    const QModelIndex & index) const;

private:
  const QStringList* mpComboItems;
};

class CQIndexComboDelegate : public CQComboDelegate
{
public:
  CQIndexComboDelegate(const QStringList *pComboItems,
                       QObject *parent = NULL);

  virtual ~CQIndexComboDelegate();

  virtual void setModelData(QWidget * editor,
                            QAbstractItemModel * model,
                            const QModelIndex & index) const;
};
#endif //CQComboDelegate_H
