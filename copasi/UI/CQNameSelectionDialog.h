// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQNameSelectionDialog
#define COPASI_CQNameSelectionDialog

#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QDialog>

#include "copasi/UI/ui_CQNameSelectionDialog.h"

class CQNameSelectionDialog: public QDialog, public Ui::CQNameSelectionDialog
{
  Q_OBJECT

public:
  CQNameSelectionDialog(QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
  virtual ~CQNameSelectionDialog();

  void setSelectionList(const QStringList &selectionList);
  const QString & getSelection() const;

protected slots:
  virtual void accept();

private:
  QString mSelection;
};

#endif // COPASI_CQNameSelectionDialog
