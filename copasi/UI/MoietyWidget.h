/****************************************************************************
 **  $ CopasiUI/MoietyWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Moiety Widget, i.e the First level 
 ** of Moieties.
 *****************************************************************************/

#ifndef MOIETY_WIDGET_H
#define MOIETY_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h"
#include "model/model.h"

class CModel;

class MoietyWidget : public QWidget
  {
    Q_OBJECT

  protected:
    CModel *mModel;
    MyTable *table;
    bool binitialized;

  public:
    MoietyWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadMoieties(CModel *model);
    void resizeEvent(QResizeEvent * re);

  public slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

  signals:
    void name(const QString &);

  protected slots:

    virtual void slotTableSelectionChanged();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
