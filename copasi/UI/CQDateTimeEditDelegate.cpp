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

#include <QDateTimeEdit>
#include <QtCore/QAbstractItemModel>

#include "copasi/copasi.h"
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

void CQDateTimeEditDelegate::updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &option,
    const QModelIndex & /* index */) const
{
  QRect Rectangle = option.rect;
  Rectangle.setRight(Rectangle.left() + std::min(Rectangle.width(), std::max(pEditor->sizeHint().width(), Rectangle.height())));
  pEditor->setGeometry(Rectangle);
}
