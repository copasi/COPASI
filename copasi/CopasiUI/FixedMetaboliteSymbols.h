/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/FixedMetaboliteSymbols.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: gasingh $ 
   $Date: 2003/12/22 07:12:03 $
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

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void showMessage(QString caption, QString text);
    void filltable();
  };

#endif
