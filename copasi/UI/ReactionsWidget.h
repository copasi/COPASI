/****************************************************************************
 **  $ CopasiUI/ReactionsWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Reactions Widget, i.e the First level 
 ** of Reactions.
 **
 *****************************************************************************/ 
/*
 resizeEvent functions modified 
 Goal: to memorize the user change and expand according
 comments: Liang Xu 
 */
#ifndef REACTIONS_WIDGET_H
#define REACTIONS_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h" 
//#include "model/model.h"
#include "copasiWidget.h"

class CModel;

class ReactionsWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CModel *mModel;
    MyTable *table;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    bool binitialized;

  public:
    ReactionsWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadReactions(CModel *model);
    //void mousePressEvent(QMouseEvent * e);
    void resizeEvent(QResizeEvent * re);
    void repaint_table();
    unsigned int numTableRows();

  signals:
    void name(const QString &);
    void leaf(CModel*);
    void updated();

  public slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

  protected slots:
    virtual void slotTableSelectionChanged();
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
