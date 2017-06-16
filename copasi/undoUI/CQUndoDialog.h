// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CQUndoDialog
#define COPASI_CQUndoDialog

#include "copasi/undoUI/ui_CQUndoDialog.h"

class CDataModel;
class CQUndoDM;

class CQUndoDialog : public QDialog, public Ui::CQUndoDialog
{
  Q_OBJECT

public:
  CQUndoDialog(CDataModel * pDataModel, QWidget *parent = 0, Qt::WindowFlags f = 0);

  virtual ~CQUndoDialog();

private:
  CQUndoDM * mpUndoDM;
};

#endif // COPASI_CQUndoDialog
