/****************************************************************************
 ** Form interface generated from reading ui file '.\function2.ui'
 **
 ** Created: Thu May 30 18:47:54 2002
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H
#include <qvariant.h>
#include <qwidget.h>
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
/*class FunctionWidget : public QWidget
{ 
    Q_OBJECT
 
public:
    FunctionWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~FunctionWidget();
 
    QTable* Table1;
 
 
};
 
#endif // FunctionWidget_H */

// make changes for

class FunctionWidget : public QWidget
  {
    Q_OBJECT

  protected:
    MyTable *table;
    CModel *mModel;
    //CFunction *fFunction;

  public:
    FunctionWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadFunction(CModel *model);
    void setFocus();
    void resizeEvent(QResizeEvent * re);

  protected slots:
    virtual void slotTableClicked(int row, int col, int button, const QPoint & mousePos);
    virtual void slotTableSelectionChanged();
  };

#endif
