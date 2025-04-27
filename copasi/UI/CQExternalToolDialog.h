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

  void saveTools(bool deleteExisting);

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
