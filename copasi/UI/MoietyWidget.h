/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MoietyWidget.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:54 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/MoietyWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Moiety Widget, i.e the First level 
 ** of Moieties.
 *****************************************************************************/ 
/*
 resizeEvent functions modified 
 Goal: to memorize the user change and expand according
 comments: Liang Xu 
 */
#ifndef MOIETY_WIDGET_H
#define MOIETY_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h" 
//#include "model/model.h"
#include "copasiWidget.h"

class CModel;

class MoietyWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CModel *mModel;
    MyTable *table;
    bool binitialized;

    std::vector<std::string> mKeys; //By G

  public:
    MoietyWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadMoieties(CModel *model);
    void resizeEvent(QResizeEvent * re);
    void repaint_table();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key); //By G

  public slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

  signals:
    void name(const QString &);
    void leaf(CModel*);
    void updated();

  protected slots:

    virtual void slotTableSelectionChanged();

  private:
    void fillTable(); //By G
    void showMessage(QString caption, QString text);

    int pixelsWide0;
    int pixelsWide1;
    int pixelsWide2;
  };

#endif
