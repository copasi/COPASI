// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQUndoHistoryDialog.h
 *
 *  Created on: 10 Dec 2014
 *      Author: dada
 */

#ifndef CQUNDOHISTORYDIALOG_H_
#define CQUNDOHISTORYDIALOG_H_

//#include <QtCore/QVariant>

#include "ui_CQUndoHistoryDialog.h"

class QStandardItemModel;
class QUndoStack;

class CQUndoHistoryDialog : public QDialog, public Ui::CQUndoHistoryDialog
{
  Q_OBJECT

public:
  CQUndoHistoryDialog(QWidget* parent = 0, QUndoStack *undoStack = NULL, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  /*
   *  Generate undo history data and attache it to model
   */
  void generateUndoData(QUndoStack *undoStack, int commandCount, int nCol);

  /*
   *  Destroys the object and frees any allocated resources
   */
  ~CQUndoHistoryDialog();

public slots:
  void closeButtonClicked();
  void undoButtonClicked();

private:
  QStandardItemModel *mpModel;
  QUndoStack *mpUndoStack;
  int mNCol;
  int mSelectedIndex;
};

#endif /* CQUNDOHISTORYDIALOG_H_ */
