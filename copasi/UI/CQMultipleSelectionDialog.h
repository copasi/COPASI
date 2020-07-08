// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CQMultipleSelectionDialog
#define COPASI_CQMultipleSelectionDialog

#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QDialog>

#include "copasi/UI/ui_CQMultipleSelectionDialog.h"

class CQMultipleSelectionDialog: public QDialog, public Ui::CQMultipleSelectionDialog
{
  Q_OBJECT

public:
  CQMultipleSelectionDialog(QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
  virtual ~CQMultipleSelectionDialog();

  void setSelectionList(const QStringList &selectionList);

  void setCurrentSelection(const QStringList &list);

  const QStringList & getSelection() const;

protected slots:
  virtual void accept();

private:
  QStringList mSelection;
};

#endif // COPASI_CQMultipleSelectionDialog
