// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPushButtonDelegate.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/13 17:23:14 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QSortFilterProxyModel>

#include "CQPushButtonDelegate.h"

#include <iostream>

CQPushButtonDelegate::CQPushButtonDelegate(const QIcon & icon,
    const QString & text,
    const ButtonType & buttonType,
    QObject *parent):
    QStyledItemDelegate(parent),
    mIcon(icon),
    mText(text),
    mButtonType(buttonType),
    mEditorToRow()
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

  switch (mButtonType)
    {
      case PushButton:
        pEditor = new QPushButton(mIcon, mText, parent);
        break;

      case ToolButton:
        pEditor = new QToolButton(parent);

        if (mIcon.isNull())
          {
            pEditor->setText(mText);
          }
        else
          {
            pEditor->setIcon(mIcon);
          }

        break;
    }

  mEditorToRow[pEditor] = SourceIndex.row();

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
      QMap< QWidget * , int >::const_iterator found = mEditorToRow.find(pEditor);

      if (found != mEditorToRow.end())
        {
          emit clicked(found.data());
        }
    }
}

void CQPushButtonDelegate::slotEditorDeleted(QObject * pObject)
{
  mEditorToRow.erase(static_cast< QWidget * >(pObject));
}
