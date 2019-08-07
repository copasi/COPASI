// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QComboBox>
#include <QSortFilterProxyModel>

#include "CQComboDelegate.h"

#include "copasi/copasi.h"

CQComboDelegate::CQComboDelegate(QObject *parent, const QStringList & comboItems, bool commitOnSelect):
  QItemDelegate(parent),
  mEditorToIndex(),
  mRowToItems(),
  mCommitOnSelect(commitOnSelect)
{
  mRowToItems[-1] = comboItems;
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
      SourceIndex = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(SourceIndex);
      pModel = SourceIndex.model();
    }

  QComboBox *pEditor = new QComboBox(parent);
  mEditorToIndex[pEditor] = SourceIndex;

  pEditor->setAutoFillBackground(true);

  if (!getItems(SourceIndex).empty())
    {
      pEditor->addItems(getItems(SourceIndex));
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

  comboBox->blockSignals(true);
  comboBox->setCurrentIndex(comboBox->findText(value));
  comboBox->blockSignals(false);
}

void CQComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  QVariant value(comboBox->currentText());
  QVariant current = model->data(index, Qt::EditRole);

  if (value != current && model->rowCount() > 0)
    model->setData(index, value, Qt::EditRole);
}

void CQComboDelegate::updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &option,
    const QModelIndex & /* index */) const
{
  QRect Rectangle = option.rect;
  Rectangle.setRight(Rectangle.left() + std::min(Rectangle.width(), std::max(pEditor->sizeHint().width(), Rectangle.height())));
  Rectangle.setBottom(Rectangle.top() + std::max(pEditor->sizeHint().height(), Rectangle.height()));
  pEditor->setGeometry(Rectangle);
}

void CQComboDelegate::setItems(int row, const QStringList & comboItems)
{
  mRowToItems[row] = comboItems;
}

QStringList CQComboDelegate::getItems(const QModelIndex & index) const
{
  if (!mRowToItems[-1].empty())
    {
      return mRowToItems[-1];
    }

  QMap< int, QStringList >::const_iterator found = mRowToItems.find(index.row());

  if (found != mRowToItems.end()) // OK to return found.value() = NULL
    {
      return found.value();
    }

  return index.model()->data(index, Qt::UserRole).toStringList();
}

void CQComboDelegate::slotCurrentIndexChanged(int index)
{
  QComboBox * pEditor = dynamic_cast< QComboBox * >(sender());

  if (pEditor)
    {
      QMap< QWidget * , QModelIndex >::const_iterator found = mEditorToIndex.find(pEditor);

      if (found != mEditorToIndex.end())
        {
          emit currentIndexChanged(found.value().row(), index);

          if (mCommitOnSelect)
            commitData(pEditor);
        }
    }
}

void CQComboDelegate::slotEditorDeleted(QObject * pObject)
{
  mEditorToIndex.remove(static_cast< QWidget * >(pObject));
}

bool CQComboDelegate::isCommitOnSelect() const
{
  return mCommitOnSelect;
}

QSize CQComboDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  QModelIndex  SourceIndex = index;
  const QAbstractItemModel *pModel = index.model();

  while (pModel != NULL && pModel->inherits("QSortFilterProxyModel"))
    {
      SourceIndex = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(SourceIndex);
      pModel = SourceIndex.model();
    }

  QWidget * pEditor = mEditorToIndex.key(SourceIndex, NULL);

  if (pEditor != NULL)
    return pEditor->sizeHint();

  QComboBox *pTmp = new QComboBox();

  pTmp->setAutoFillBackground(true);

  if (!getItems(SourceIndex).empty())
    {
      pTmp->addItems(getItems(SourceIndex));
    }

  QSize SizeHint = pTmp->sizeHint();

  delete pTmp;

  return SizeHint; // QItemDelegate::sizeHint(option, index);
}

void CQComboDelegate::setCommitOnSelect(bool commitOnSelect)
{
  mCommitOnSelect = commitOnSelect;
}

CQIndexComboDelegate::CQIndexComboDelegate(QObject *parent, const QStringList & comboItems, bool commitOnSelect)
  : CQComboDelegate(parent, comboItems, commitOnSelect)
{}

CQIndexComboDelegate::~CQIndexComboDelegate()
{}

void CQIndexComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  QVariant value(comboBox->currentIndex());

  if (model->data(index, Qt::EditRole) != value)
    model->setData(index, value, Qt::EditRole);
}
