// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CQUndoDialog
#define COPASI_CQUndoDialog

#include "copasi/undoUI/ui_CQUndoDialog.h"

#include "copasi/core/CCore.h"
#include "copasi/undo/CUndoStack.h"

class CDataModel;
class CQUndoDM;

class CQUndoDialog : public QDialog, public Ui::CQUndoDialog
{
  Q_OBJECT

public:
  CQUndoDialog(CDataModel * pDataModel, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~CQUndoDialog();

  const CUndoData::CChangeSet & getChangeSet() const;

public slots:
  void accept();

private:
  CDataModel *mpDataModel;
  CQUndoDM * mpUndoDM;
  CUndoData::CChangeSet mChangeSet;
};

#endif // COPASI_CQUndoDialog
