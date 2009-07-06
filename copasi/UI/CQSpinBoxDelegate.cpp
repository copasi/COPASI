// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSpinBoxDelegate.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/07/06 12:12:14 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QSpinBox>
#include <QSortFilterProxyModel>

#include "../copasi.h"
#include "CQSpinBoxDelegate.h"
#include "CQBaseDataModel.h"

CQSpinBoxDelegate::CQSpinBoxDelegate(QObject *parent)
    : QItemDelegate(parent)
{}

QWidget *CQSpinBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem & C_UNUSED(option),
    const QModelIndex & index) const
{
  QSpinBox *editor = new QSpinBox(parent);
  editor->setMinimum(1);
  unsigned C_INT32 max = 1;

  const QSortFilterProxyModel *pProxyDM = dynamic_cast<const QSortFilterProxyModel *>(index.model());
  QModelIndex BDMIndex;
  const CQBaseDataModel *pBDM;

  if (pProxyDM)
    {
      pBDM = dynamic_cast<const CQBaseDataModel *>(pProxyDM->sourceModel());
      BDMIndex = pProxyDM->mapToSource(index);
    }
  else
    {
      pBDM = dynamic_cast<const CQBaseDataModel *>(index.model());
      BDMIndex = index;
    }

  if (pBDM)
    {
      if (pBDM->isDefaultRow(BDMIndex))
        max = pBDM->rowCount();
      else
        max = pBDM->rowCount() - 1;
    }

  editor->setMaximum(max);
  return editor;
}

void CQSpinBoxDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
  QSpinBox *pSpinBox = static_cast<QSpinBox*>(editor);
  unsigned C_INT32 value = index.model()->data(index, Qt::EditRole).toUInt();
  pSpinBox->setValue(value);
}

void CQSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
  QSpinBox *pSpinBox = static_cast<QSpinBox*>(editor);
  pSpinBox->interpretText();
  unsigned C_INT32 value = pSpinBox->value();

  model->setData(index, value, Qt::EditRole);
}

void CQSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex & C_UNUSED(index)) const
{
  editor->setGeometry(option.rect);
}
