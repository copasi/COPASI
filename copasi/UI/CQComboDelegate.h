// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQComboDelegate.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/07 11:55:21 $
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

protected slots:
  void slotCurrentIndexChanged(int index);
  void slotEditorDeleted(QObject * pObject);

signals:
  void currentIndexChanged(int, int);


private:
  const QStringList* mpComboItems;

  mutable QMap< int , QWidget * > mRowToEditor;

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
