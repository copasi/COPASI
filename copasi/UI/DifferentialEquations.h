/****************************************************************************
 **  $ CopasiUI/MetabolitesWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Metabolites Widget, i.e the First level 
 ** of Metabolites.
 *****************************************************************************/

#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H
#include <qpushbutton.h>
#include "copasi.h"
#include <qtextbrowser.h>

class DifferentialEquations : public QWidget
  {
    Q_OBJECT

  protected:
    QTextBrowser *textBrowser;
    QPushButton *btnOK;
    QPushButton *btnCancel;

  public:
    DifferentialEquations(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadDifferentialEquations();

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
