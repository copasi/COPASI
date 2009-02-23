// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CQComboDelegate.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/23 05:12:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QComboBox>

#include "../copasi.h"
#include "CQComboDelegate.h"

CQComboDelegate::CQComboDelegate(const QStringList *pComboItems, QObject *parent)
    : QItemDelegate(parent)
{
  mpComboItems = pComboItems;
}

QWidget *CQComboDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem & C_UNUSED(option),
                                       const QModelIndex & C_UNUSED(index)) const
  {
    QComboBox *editor = new QComboBox(parent);
    editor->addItems(*mpComboItems);
    return editor;
  }

void CQComboDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
  {
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentItem(comboBox->findText(value));
  }

void CQComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
  {
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QVariant value(comboBox->currentText());
    model->setData(index, value, Qt::EditRole);
  }

void CQComboDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex & C_UNUSED(index)) const
  {
    editor->setGeometry(option.rect);
  }
