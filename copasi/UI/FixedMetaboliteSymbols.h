/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FixedMetaboliteSymbols.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:49 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/FixedMetaboliteSymbols.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Fixed Metabolite Symbols
 *****************************************************************************/

#ifndef FIXED_METABOLITE_SYMBOLS_H
#define FIXED_METABOLITE_SYMBOLS_H

#include <qtable.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "copasi.h"
#include "copasiWidget.h"

class CMathModel;
class CMathConstant;
class CMathConstantMetab;

class FixedMetaboliteSymbols : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CMathModel * mModel;
    CMathConstantMetab *metablist;
    MyTable * table;
    QPushButton *btnOK;
    QPushButton *btnCancel;

  signals:
    void name(const QString &);

  public:
    FixedMetaboliteSymbols(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadFixedMetaboliteSymbols(CMathModel *model);
    void resizeEvent(QResizeEvent * re);

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
