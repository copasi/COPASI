/****************************************************************************
 **  $ CopasiUI/FunctionWidget.h               
 **  $ Author  : Mrinmayee  Kulkarni
 **  
 ** This is the header file for the Function Widget, i.e the First level 
 ** widget which shows the table of function names and types
 *****************************************************************************/
#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H
#include <qvariant.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h"
#include "model/model.h"
#include "utilities/CGlobals.h"
#include "function/function.h"
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTable;
class CModel;
class CGlobals;

class FunctionWidget : public QWidget
  {
    Q_OBJECT
  protected:
    MyTable *table;

  public:
    FunctionWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadFunction();
    void setFocus();
    void resizeEvent(QResizeEvent * re);

  public slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

  protected slots:
    virtual void slotTableSelectionChanged();

  signals:
    void name(QString &);
  };

#endif
