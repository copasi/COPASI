/****************************************************************************
 **  $ CopasiUI/CompartmentsWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Compartments Widget, i.e the First level 
 ** of Compartments.
 *****************************************************************************/

#ifndef COMPARTMENTS_WIDGET_H
#define COMPARTMENTS_WIDGET_H

#include <qtable.h> 
//#include <qpushbutton.h>
//#include "MyTable.h"
#include "copasi.h"
#include "copasiWidget.h"

class CModel;
class QPushButton;
class QGridLayout;
class QTable;
class MyTable;

class CompartmentsWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    CModel *mModel;
    MyTable* table;
    QPushButton* btnOK;
    QPushButton* btnCancel;
    QGridLayout* CompartmentsWidgetLayout;
    bool binitialized;

  public:
    CompartmentsWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadCompartments(CModel *model);
    //void mousePressEvent(QMouseEvent * e);
    void resizeEvent(QResizeEvent * re);
    QString *Compartment_Name;
    void repaint_table();

  public slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

  signals:
    void name(const QString &);
    void signal_emitted(const QString &);
    void leaf(CModel*);
    void updated();

  protected slots:
    virtual void slotTableSelectionChanged();
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void tableValueChanged(int, int);

  private:
    void showMessage(QString caption, QString text);
  };

#endif
