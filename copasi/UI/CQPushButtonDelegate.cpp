// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPushButtonDelegate.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:00 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QPushButton>
#include <QtGui/QSortFilterProxyModel>

#include "CQPushButtonDelegate.h"

CQPushButtonDelegate::CQPushButtonDelegate(const QIcon & icon, const QString & text, QObject *parent):
    QStyledItemDelegate(parent),
    mIcon(icon),
    mText(text),
    mRowToEditor()
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

  QMap< int , QWidget * >::iterator it = mRowToEditor.find(SourceIndex.row());

  if (it != mRowToEditor.end()) return  it.data();

  QPushButton * pEditor = new QPushButton(mIcon, mText, parent);

  mRowToEditor[SourceIndex.row()] = pEditor;

  connect(pEditor, SIGNAL(clicked(bool)), this, SLOT(slotButtonClicked()));
  connect(pEditor, SIGNAL(destroyed(QObject *)), this, SLOT(slotButtonDeleted(QObject *)));

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
  QPushButton * pEditor = dynamic_cast< QPushButton *>(sender());

  if (pEditor) emit clicked(mRowToEditor.key(pEditor));
}

void CQPushButtonDelegate::slotButtonDeleted(QObject * pObject)
{
  mRowToEditor.erase(mRowToEditor.key(static_cast<QPushButton *>(pObject)));
}
