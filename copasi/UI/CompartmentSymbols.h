/****************************************************************************
 **  $ CopasiUI/CompartmentSymbols.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Compartment Symbols
 *****************************************************************************/

#ifndef COMPARTMENT_SYMBOLS_H
#define COMPARTMENT_SYMBOLS_H

#include <qtable.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "copasi.h"
#include "copasiwidget.h"
class CMathModel;

class CompartmentSymbols : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CMathModel * mModel;
    MyTable * table;
    QPushButton *btnOK;
    QPushButton *btnCancel;

  signals:
    void name(const QString &);

  public:
    CompartmentSymbols(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadCompartmentSymbols(CMathModel *model);
    void resizeEvent(QResizeEvent * re);

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
