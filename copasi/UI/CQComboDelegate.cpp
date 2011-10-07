// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQComboDelegate.cpp,v $
//   $Revision: 1.4 $
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

#include <QComboBox>
#include <QtGui/QSortFilterProxyModel>

#include "CQComboDelegate.h"

#include "copasi.h"

CQComboDelegate::CQComboDelegate(const QStringList *pComboItems, QObject *parent)
    : QItemDelegate(parent)
{
  mpComboItems = pComboItems;
}

CQComboDelegate::~CQComboDelegate()
{}

QWidget *CQComboDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem & C_UNUSED(option),
                                       const QModelIndex & index) const
{
  QModelIndex  SourceIndex = index;
  const QAbstractItemModel *pModel = index.model();

  while (pModel->inherits("QSortFilterProxyModel"))
    {
      SourceIndex = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(index);
      pModel = SourceIndex.model();
    }

  QMap< int , QWidget * >::iterator it = mRowToEditor.find(SourceIndex.row());

  if (it != mRowToEditor.end()) return  it.data();

  QComboBox *pEditor = new QComboBox(parent);

  mRowToEditor[SourceIndex.row()] = pEditor;

  if (mpComboItems != NULL)
    {
      pEditor->addItems(*mpComboItems);
    }
  else
    {
      QStringList Items = index.model()->data(index, Qt::EditRole).toStringList();
      pEditor->addItems(Items);
    }

  connect(pEditor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
  connect(pEditor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDeleted(QObject *)));

  return pEditor;
}

void CQComboDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
  QString value = index.model()->data(index, Qt::DisplayRole).toString();
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  comboBox->setCurrentIndex(comboBox->findText(value));
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

void CQComboDelegate::slotCurrentIndexChanged(int index)
{
  QComboBox * pEditor = dynamic_cast< QComboBox * >(sender());

  if (pEditor) emit currentIndexChanged(mRowToEditor.key(pEditor), index);
}

void CQComboDelegate::slotEditorDeleted(QObject * pObject)
{
  mRowToEditor.erase(mRowToEditor.key(static_cast<QComboBox *>(pObject)));
}

CQIndexComboDelegate::CQIndexComboDelegate(const QStringList *pComboItems, QObject *parent)
    : CQComboDelegate(pComboItems, parent)
{}

CQIndexComboDelegate::~CQIndexComboDelegate()
{}

void CQIndexComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  QVariant value(comboBox->currentIndex());
  model->setData(index, value, Qt::EditRole);
}
