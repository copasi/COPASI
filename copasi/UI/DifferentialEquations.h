/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DifferentialEquations.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:49 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/DifferentialEquations.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Differential Equations
 *****************************************************************************/

#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H
#include <qpushbutton.h>
#include <qtextbrowser.h>

#include "copasi.h"
#include "copasiWidget.h"
class CMathModel;

class DifferentialEquations : public CopasiWidget
  {
    Q_OBJECT

  protected:
    QTextBrowser *textBrowser;
    QPushButton *btnOK;
    QPushButton *btnCancel;

  public:
    DifferentialEquations(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadDifferentialEquations(CMathModel * mathModel);

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
