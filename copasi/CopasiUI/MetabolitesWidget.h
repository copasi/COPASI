/****************************************************************************
 **  $ CopasiUI/MetabolitesWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Metabolites Widget, i.e the First level 
 ** of Metabolites.
 *****************************************************************************/

#ifndef METABOLITES_WIDGET_H
#define METABOLITES_WIDGET_H

#include "MyTable.h"
#include "copasi.h"
#include "model/model.h"
#include <qtable.h>
#include <qpushbutton.h>
#include "copasiwidget.h"

class MetabolitesWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CModel * mModel;
    MyTable * table;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    bool binitialized;

  public slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

  signals:
    void name(const QString &);
    void leaf(CModel*);
    void updated();

  public:
    MetabolitesWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadMetabolites(CModel *model);
    void resizeEvent(QResizeEvent * re);
    void repaint_table();

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
