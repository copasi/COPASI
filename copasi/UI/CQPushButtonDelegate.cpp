// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QSortFilterProxyModel>

#include "CQPushButtonDelegate.h"

#include <iostream>

CQPushButtonDelegate::CQPushButtonDelegate(const ButtonType & buttonType,
    QObject *parent):
  QStyledItemDelegate(parent),
  mIcon(),
  mText(),
  mButtonType(buttonType),
  mEditorToIndex()
{}

CQPushButtonDelegate::CQPushButtonDelegate(const QIcon & icon,
    const QString & text,
    const ButtonType & buttonType,
    QObject *parent):
  QStyledItemDelegate(parent),
  mIcon(icon),
  mText(text),
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

  Data = SourceIndex.model()->data(SourceIndex, Qt::DecorationRole);

  if (Data.type() == QVariant::Icon)
    {
      mIcon = Data.value< QIcon >();
    }

  switch (mButtonType)
    {
      case PushButton:
        pEditor = new QPushButton(mIcon, mText, parent);
        break;

      case ToolButton:
        pEditor = new QToolButton(parent);

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
  QPushButton * pButton = static_cast< QPushButton * >(pEditor);

  if (pButton->icon().isNull())
    {
      pButton->setText(value);
    }
}

// We do not do anything since the signal clicked of the editor is reemited with the correct row index.
void CQPushButtonDelegate::setModelData(QWidget * /* pEditor */,
                                        QAbstractItemModel * /* pModel */,
                                        const QModelIndex & /* index */) const
{}

void CQPushButtonDelegate::updateEditorGeometry(QWidget * pEditor,
    const QStyleOptionViewItem & option,
    const QModelIndex & /* index */) const
{
  pEditor->setGeometry(option.rect);
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
      mEditorToIndex.erase(pEditor);
    }
}
