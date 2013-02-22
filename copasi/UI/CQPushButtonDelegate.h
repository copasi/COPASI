// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQPushButtonDelegate
#define COPASI_CQPushButtonDelegate

#include <QtGui/QStyledItemDelegate>

class QAbstractButton;

class CQPushButtonDelegate: public QStyledItemDelegate
{
  Q_OBJECT

public:
  enum ButtonType {PushButton, ToolButton};

  CQPushButtonDelegate(const ButtonType & buttonType, QObject *parent = 0);
  CQPushButtonDelegate(const QIcon & icon, const QString & text, const ButtonType & buttonType, QObject *parent = 0);
  virtual ~CQPushButtonDelegate();

  virtual QWidget *createEditor(QWidget * parent,
                                const QStyleOptionViewItem & option,
                                const QModelIndex & index) const;

  virtual void setEditorData(QWidget * pEditor, const QModelIndex & index) const;

  virtual void setModelData(QWidget * pEditor,
                            QAbstractItemModel * pModel,
                            const QModelIndex & index) const;

  virtual void updateEditorGeometry(QWidget * pEditor,
                                    const QStyleOptionViewItem & option,
                                    const QModelIndex & index) const;

protected slots:
  void slotButtonClicked();
  void slotEditorDeleted(QObject * pObject);

signals:
  void clicked(const QModelIndex &);

private:
  mutable QIcon mIcon;
  mutable QString mText;
  ButtonType mButtonType;

  mutable QMap< QAbstractButton * , QModelIndex > mEditorToIndex;
};

#endif // COPASI_CQPushButtonDelegate
