// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQNameSelectionDialog
#define COPASI_CQNameSelectionDialog

#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtGui/QDialog>

#include "copasi/UI/ui_CQNameSelectionDialog.h"

class CQNameSelectionDialog: public QDialog, public Ui::CQNameSelectionDialog
{
  Q_OBJECT

public:
  CQNameSelectionDialog(QWidget * parent = 0, Qt::WindowFlags f = 0);
  virtual ~CQNameSelectionDialog();

  void setSelectionList(const QStringList &selectionList);
  const QString & getSelection() const;

protected slots:
  virtual void accept();

private:
  QString mSelection;
};

#endif // COPASI_CQNameSelectionDialog
