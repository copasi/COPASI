// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
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

  void setLabel(const QString& label);

  const QStringList & getSelection() const;

  static QStringList getSelection(QWidget * parent, const QString & title, const QString & label, const QStringList & strings, const QStringList * currentSelection = nullptr, bool * ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

protected slots:
  virtual void accept();

private:
  QStringList mSelection;
};

#endif // COPASI_CQMultipleSelectionDialog
