// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQPushButtonDelegate
#define COPASI_CQPushButtonDelegate

#include <QStyledItemDelegate>

class QAbstractButton;

class CQPushButtonDelegate: public QStyledItemDelegate
{
  Q_OBJECT

public:
  enum ButtonType {PushButton, ToolButton};

  CQPushButtonDelegate(const ButtonType & buttonType, QObject *parent = 0);

  CQPushButtonDelegate(const QIcon & icon,
                       const QString & text,
                       const ButtonType & buttonType,
                       QObject *parent = 0,
                       const QString& tooltip = "");

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
  mutable QString mTooltip;
  ButtonType mButtonType;

  mutable QMap< QAbstractButton * , QModelIndex > mEditorToIndex;
};

#endif // COPASI_CQPushButtonDelegate
