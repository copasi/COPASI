/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModesWidget.h,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/26 21:51:51 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/ModesWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Elementary Modes Widget
 *****************************************************************************/ 
/*
 resizeEvent functions modified 
 Goal: to memorize the user change and expand according
 comments: Liang Xu 
 */
#ifndef MODES_WIDGET_H
#define MODES_WIDGET_H

//#include <qtable.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h"
#include "copasiWidget.h"
#include "elementaryFluxModes/CElementaryFluxModes.h"

class CModel;

class ModesWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    //CModel *mModel;
    CElementaryFluxModes *modes;
    QListView *listView;
    QPushButton *btnCalculate;
    bool binitialized;

  public:
    ModesWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadModes();
    void resizeEvent(QResizeEvent * re);

    virtual bool enter(const std::string & key = "");
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  signals:
    //void signal_emitted(const QString &);
    //void name(const QString&);

  protected slots:

    virtual void slotTableSelectionChanged();
    virtual void slotBtnCalculateClicked();
  };

#endif
