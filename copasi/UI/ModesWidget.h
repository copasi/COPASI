/****************************************************************************
 **  $ CopasiUI/ModesWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Elementary Modes Widget
 *****************************************************************************/

#ifndef MODES_WIDGET_H
#define MODES_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h"
#include "elementaryFluxModes/CElementaryFluxModes.h"
#include "copasiwidget.h"

class CModel;

class ModesWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CModel *mModel;
    MyTable *table;
    QPushButton *btnCalculate;
    bool binitialized;

  public:
    ModesWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadModes(CModel *model);
    void resizeEvent(QResizeEvent * re);

  signals:
    void signal_emitted(const QString &);
    void name(const QString&);

  protected slots:

    virtual void slotTableSelectionChanged();
    virtual void slotBtnCalculateClicked();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
