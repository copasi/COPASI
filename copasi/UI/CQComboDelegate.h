// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
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
  CQComboDelegate(QObject *parent = NULL,
                  const QStringList & comboItems = QStringList(),
                  bool commitOnSelect = true);

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

  virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

  void setItems(int row, const QStringList & comboItems);

  QStringList getItems(const QModelIndex & index) const;

  bool isCommitOnSelect() const;
  void setCommitOnSelect(bool commitOnSelect);

protected slots:
  void slotCurrentIndexChanged(int index);
  void slotEditorDeleted(QObject * pObject);

signals:
  void currentIndexChanged(int, int);

private:
  mutable QMap< QWidget * , QModelIndex > mEditorToIndex;
  mutable QMap< int, QStringList > mRowToItems;

  bool mCommitOnSelect;
};

class CQIndexComboDelegate : public CQComboDelegate
{
public:
  CQIndexComboDelegate(QObject *parent = NULL,
                       const QStringList & comboItems = QStringList(),
                       bool commitOnSelect = true);

  virtual ~CQIndexComboDelegate();

  virtual void setModelData(QWidget * editor,
                            QAbstractItemModel * model,
                            const QModelIndex & index) const;
};
#endif // CQComboDelegate_H
