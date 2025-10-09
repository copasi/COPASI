#ifndef CQProfileWizard_H__
#define CQProfileWizard_H__

#include <QDialog>
#include "copasi/UI/ui_CQProfileWizard.h"
#include <copasi/utilities/CProfileSettings.h>

class QAction;
class QPushButton;


class CQProfileWizard : public QDialog
  , public Ui::CQProfileWizard
{

  Q_OBJECT

private:
  CProfileSettings mSettings;
  int mCurrentPage;

  void loadPage(int index);
  void savePage(int index);

public:
  CQProfileWizard(QWidget * parent = 0, const CProfileSettings * pSettings = 0);


public slots: 

   virtual void open();
   virtual void onTabChanged(int index);

};

#endif // CQProfileWizard_H__
