/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CompartmentSymbols.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:46 $
   End CVS Header */

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
#include "copasiWidget.h"
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
