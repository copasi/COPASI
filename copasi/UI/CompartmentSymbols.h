/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CompartmentSymbols.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:44 $
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

//#include "MyTable.h"
#include "copasi.h"
#include "copasiWidget.h"
class CMathModel;

class CompartmentSymbols : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CMathModel * mModel;
    QTable * table;
    //QPushButton *btnOK;
    //QPushButton *btnCancel;

  signals:
    void name(const QString &);

  public:
    CompartmentSymbols(QWidget *parent, const char * name = 0, WFlags f = 0);
    void resizeEvent(QResizeEvent * re);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void loadCompartmentSymbols(CMathModel *model);
  };

#endif
