/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ConstantSymbols.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:48 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/ConstantSymbols.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Constant Symbols
 *****************************************************************************/

#ifndef CONSTANT_SYMBOLS_H
#define CONSTANT_SYMBOLS_H

#include <qtable.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "copasi.h"
#include "copasiWidget.h"
class CMathModel;

class ConstantSymbols : public CopasiWidget
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
    ConstantSymbols(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadConstantSymbols(CMathModel *model);
    void resizeEvent(QResizeEvent * re);

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
