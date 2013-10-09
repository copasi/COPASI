// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtGui/QDateTimeEdit>
#include <QtCore/QAbstractItemModel>

#include "../copasi.h"
#include "CQDateTimeEditDelegate.h"

CQDateTimeEditDelegate::CQDateTimeEditDelegate(QObject *parent)
  : QItemDelegate(parent)
{}

QWidget *CQDateTimeEditDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem & C_UNUSED(option),
    const QModelIndex & C_UNUSED(index)) const
{
  QDateTimeEdit *editor = new QDateTimeEdit(QDateTime::currentDateTime(), parent);
  return editor;
}

void CQDateTimeEditDelegate::setEditorData(QWidget *editor,
    const QModelIndex &index) const
{
  QString dtStr = index.model()->data(index, Qt::EditRole).toString();
  QDateTimeEdit *dtEdit = static_cast<QDateTimeEdit*>(editor);

  dtEdit->setDateTime(QDateTime::fromString(dtStr, Qt::ISODate));
}

void CQDateTimeEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
  QDateTimeEdit *dtEdit = static_cast<QDateTimeEdit*>(editor);
  QVariant value(dtEdit->dateTime().toString(Qt::ISODate));
  model->setData(index, value, Qt::EditRole);
}

void CQDateTimeEditDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex & C_UNUSED(index)) const
{
  editor->setGeometry(option.rect);
}
