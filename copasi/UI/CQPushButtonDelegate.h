// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPushButtonDelegate.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/15 17:07:54 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQPushButtonDelegate
#define COPASI_CQPushButtonDelegate

#include <QtGui/QStyledItemDelegate>

class CQPushButtonDelegate: public QStyledItemDelegate
{
  Q_OBJECT

public:
  enum ButtonType {PushButton, ToolButton};

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
  void clicked(int);

private:
  const QIcon & mIcon;
  QString mText;
  ButtonType mButtonType;

  mutable QMap< QWidget * , int > mEditorToRow;
};

#endif // COPASI_CQPushButtonDelegate
