/****************************************************************************
 **  $ CopasiUI/CompartmentsWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Compartments Widget, i.e the First level 
 ** of Compartments.
 *****************************************************************************/

#ifndef MODES_WIDGET_H
#define MODES_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h"
#include "Structures.h"
#include "elementaryFluxModes/CElementaryFluxModes.h"

class CModel;

class ModesWidget : public QWidget
  {
    Q_OBJECT

  protected:
    CModel *mModel;
    MyTable *table;
    QPushButton *btnOK;
    QPushButton *btnCancel;

  public:
    ModesWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadModes(CModel *model);
    //void mousePressEvent(QMouseEvent * e);
    void resizeEvent(QResizeEvent * re);
    //QString *Compartment_Name;

  public slots:
    //virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

  signals:
    // void name(QString &);
    //void signal_emitted(QString &);

  protected slots:

    virtual void slotTableSelectionChanged();
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    //virtual void tableValueChanged(int, int);

  private:
    void showMessage(QString caption, QString text);
  };

#endif
