/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FunctionSymbols.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: gasingh $ 
   $Date: 2003/12/22 07:12:02 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/FunctionSymbols.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Function Symbols
 *****************************************************************************/

#ifndef FUNCTION_SYMBOLS_H
#define FUNCTION_SYMBOLS_H

#include <qtable.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "copasi.h"
#include "copasiWidget.h"

class CMathModel;

class FunctionSymbols : public CopasiWidget
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
    FunctionSymbols (QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadFunctionSymbols(CMathModel *model);
    void resizeEvent(QResizeEvent * re);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void filltable();
    void showMessage(QString caption, QString text);
  };

#endif
