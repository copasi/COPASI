#ifndef CQPLGenerateWidget_H__
#define CQPLGenerateWidget_H__
#  include <QWidget>
#include "copasi/UI/ui_CQPLGenerateWidget.h"
#include <copasi/UI/CQProfileWidget.h>

class QAction;
class QPushButton;
class CProfileSettings;
class COptTask;

class CQPLGenerateWidget : public QWidget
  , public Ui::CQPLGenerateWidget
  , public CQProfileWidget
{

  Q_OBJECT
private:
  COptTask * mpOptTask;

public:
  CQPLGenerateWidget(QWidget * parent = 0);
  virtual ~CQPLGenerateWidget();

  virtual void loadSettings(const CProfileSettings * pSettings);
  virtual void saveSettings(CProfileSettings * pSettings);

public slots:
  /**
   * browses for a directory to generate files in
   */
  virtual void browseDirectory();

  /**
   * generates the files in the selected directory
   */
  virtual void generateFiles();
};

#endif // CQPLGenerateWidget_H__
