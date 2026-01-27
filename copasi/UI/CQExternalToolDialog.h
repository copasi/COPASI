// Copyright (C) 2024 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQ_EXTERNAL_TOOL_DIALOG_H
#define CQ_EXTERNAL_TOOL_DIALOG_H

#include <QDialog>

#include "copasi/UI/ui_CQExternalToolDialog.h"

#include "CQExternalTools.h"

class CQExternalToolDialog : public QDialog
  , public Ui_CQExternalToolDialog
{
  Q_OBJECT

public:
  CQExternalToolDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQExternalToolDialog();

  void init(CQExternalTools * tools);

  /**
   * serializes the tools to the ini files
   *
   * @param deleteExisting if true, deletes existing ini files before saving
   */
  void saveTools(bool deleteExisting);

  /**
   * loads the given tool to gui
   */
  void loadTool(CQExternalTool & tool);

  /**
   * saves gui settings to the given tool
   */
  void saveTool(CQExternalTool & tool);

  void saveCurrent();

  void loadCurrent(int index);

  void selectItem(int index);

  /**
   * clears the dialog
   */
  void clear();

public slots:
  void slotAddTool();
  void slotDeleteTool();
  void slotMoveUp();
  void slotMoveDown();
  void slotBrowseCommand();
  void slotShowArgs();
  void slotBrowseInitialDir();
  void slotItemChanged();
  void slotUpdateSelected();

private:
  QList< CQExternalTool > mTools;

  CQExternalTool mCurrentTool;
  size_t mCurrentIndex;
};

#endif // CQ_EXTERNAL_TOOL_DIALOG_H
