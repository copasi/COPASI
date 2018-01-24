// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
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
  CQMultipleSelectionDialog(QWidget * parent = 0, Qt::WindowFlags f = 0);
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
