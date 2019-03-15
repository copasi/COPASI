// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QPushButton>
#include <QToolButton>
#include <QSortFilterProxyModel>

#include "CQPushButtonDelegate.h"

#include <iostream>

CQPushButtonDelegate::CQPushButtonDelegate(const ButtonType & buttonType,
    QObject *parent):
  QStyledItemDelegate(parent),
  mIcon(),
  mText(),
  mTooltip(),
  mButtonType(buttonType),
  mEditorToIndex()
{}

CQPushButtonDelegate::CQPushButtonDelegate(const QIcon & icon,
    const QString & text,
    const ButtonType & buttonType,
    QObject *parent,
    const QString& tooltip):
  QStyledItemDelegate(parent),
  mIcon(icon),
  mText(text),
  mTooltip(tooltip),
  mButtonType(buttonType),
  mEditorToIndex()
{}

CQPushButtonDelegate::~CQPushButtonDelegate()
{}

QWidget * CQPushButtonDelegate::createEditor(QWidget * parent,
    const QStyleOptionViewItem & /* option */,
    const QModelIndex & index) const
{
  QModelIndex  SourceIndex = index;
  const QAbstractItemModel *pModel = index.model();

  while (pModel->inherits("QSortFilterProxyModel"))
    {
      SourceIndex = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(index);
      pModel = SourceIndex.model();
    }

  QAbstractButton * pEditor;
  QVariant Data;

  Data = SourceIndex.model()->data(SourceIndex, Qt::UserRole);

  if (Data.type() == QVariant::Icon)
    {
      mIcon = Data.value< QIcon >();
    }

  switch (mButtonType)
    {
      case PushButton:
        pEditor = new QPushButton(mIcon, mText, parent);
        pEditor->setToolTip(mTooltip);
        break;

      case ToolButton:
        pEditor = new QToolButton(parent);
        pEditor->setToolTip(mTooltip);

        if (mIcon.isNull())
          {
            Data = SourceIndex.model()->data(SourceIndex, Qt::DisplayRole);

            if (Data.type() == QVariant::String)
              {
                mText = Data.toString();
              }

            pEditor->setText(mText);
          }
        else
          {
            pEditor->setIcon(mIcon);
          }

        break;
    }

  mEditorToIndex[pEditor] = SourceIndex;

  connect(pEditor, SIGNAL(clicked(bool)), this, SLOT(slotButtonClicked()));
  connect(pEditor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDeleted(QObject *)));

  return pEditor;
}

void CQPushButtonDelegate::setEditorData(QWidget * pEditor, const QModelIndex & index) const
{
  QString value = index.model()->data(index, Qt::EditRole).toString();
  QAbstractButton * pButton = static_cast< QAbstractButton * >(pEditor);

  if (pButton->icon().isNull())
    {
      pButton->setText(value);
    }
}

void CQPushButtonDelegate::setModelData(QWidget * /* pEditor */,
                                        QAbstractItemModel * /* pModel */,
                                        const QModelIndex & /* index */) const
{
  // We do not do anything since the signal clicked of the editor is used to perform an action
  // and is re-emitted with the correct row index.
}

void CQPushButtonDelegate::updateEditorGeometry(QWidget * pEditor, const QStyleOptionViewItem & option,
    const QModelIndex & /* index */) const
{
  QRect Rectangle = option.rect;
  Rectangle.setRight(Rectangle.left() + std::min(Rectangle.width(), std::max(pEditor->sizeHint().width(), Rectangle.height())));
  pEditor->setGeometry(Rectangle);
}

void CQPushButtonDelegate::slotButtonClicked()
{
  QAbstractButton * pEditor = dynamic_cast< QAbstractButton *>(sender());

  if (pEditor)
    {
      QMap< QAbstractButton *, QModelIndex >::const_iterator found = mEditorToIndex.find(pEditor);

      if (found != mEditorToIndex.end())
        {
          emit clicked(found.value());
        }
    }
}

void CQPushButtonDelegate::slotEditorDeleted(QObject * /* pObject */)
{
  QAbstractButton * pEditor = dynamic_cast< QAbstractButton *>(sender());

  if (pEditor)
    {
      mEditorToIndex.remove(pEditor);
    }
}
