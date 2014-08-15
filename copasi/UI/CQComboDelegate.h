// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQComboDelegate_H
#define CQComboDelegate_H

#include <QtGui/QItemDelegate>

class CQComboDelegate : public QItemDelegate
{
  Q_OBJECT

public:
  CQComboDelegate(const QStringList* pComboItems,
                  QObject *parent = NULL, bool commitOnSelect = true);

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

  void setItems(int row, const QStringList* pComboItems);

  const QStringList *getItems(int row) const;

  bool isCommitOnSelect() const;
  void setCommitOnSelect(bool commitOnSelect);

protected slots:
  void slotCurrentIndexChanged(int index);
  void slotEditorDeleted(QObject * pObject);

signals:
  void currentIndexChanged(int, int);

private:
  const QStringList* mpComboItems;

  mutable QMap< QWidget * , QModelIndex > mEditorToIndex;
  mutable QMap< int, const QStringList * > mRowToItems;

  bool mCommitOnSelect;
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
