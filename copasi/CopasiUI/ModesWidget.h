/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ModesWidget.h,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:54 $
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

#include <qtable.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h"
#include "copasiWidget.h"

class CModel;

class ModesWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CModel *mModel;
    MyTable *table;
    QPushButton *btnCalculate;
    bool binitialized;

  public:
    ModesWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadModes(CModel *model);
    void resizeEvent(QResizeEvent * re);

  signals:
    void signal_emitted(const QString &);
    void name(const QString&);

  protected slots:

    virtual void slotTableSelectionChanged();
    virtual void slotBtnCalculateClicked();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
