/***********************************************************************
 **  $ CopasiUI/FunctionWidget.cpp                 
 **  $ Author  : Mrinmayee Kulkarni
 **
 ** This file creates the GUI which displays information obtained 
 ** from the function database. The name and type of functions are  
 ** displayes in tablular form. This is the first level widget for functions
 ************************************************************************/
#include "FunctionWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include "model/CMetab.h"
#include <qvariant.h>
#include <qtable.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include "utilities/CGlobals.h"
#include "function/function.h"
#include "listviews.h" 
/**
 *  Constructs a Widget for the Functions subsection of the tree for 
 *  displaying the functions.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param parent The widget which this widget is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Refer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */

FunctionWidget::FunctionWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  table = new MyTable(0, 2, this, "tblFunctions");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Type");
  setFocusPolicy(QWidget::WheelFocus);
  setFocusProxy (table);
  table->setFocusPolicy(QWidget::WheelFocus);

  // signals and slots connections
  /*** for connecting first and second level function widget ****/
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)), this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(this, SIGNAL(name(QString &)), (ListViews*)parent, SLOT(slotFunctionTableChanged(QString &)));
  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
}

void FunctionWidget::loadFunction()
{
  //Emptying the table
  int numberOfRows = table->numRows();
  for (int i = 0; i < numberOfRows; i++)
    {
      table->removeRow(0);
    }

  CCopasiVectorNS< CFunction > & Functions =
    Copasi->FunctionDB.loadedFunctions();

  C_INT32 noOfFunctionsRows = Functions.size();
  table->setNumRows(noOfFunctionsRows);

  //Now filling the table.

  CFunction *funct;
  for (C_INT32 j = 0; j < noOfFunctionsRows; j++)
    {
      funct = Functions[j];
      table->setText(j, 0, funct->getName().c_str());
      QString ftype;
      switch (funct->getType())
        {
        case 1:
        case 2:
          ftype = QString("pre-defined");
          break;
        case 3:
          ftype = QString("user-defined");
          break;
        }
      table->setText(j, 1, ftype);
    }
}

void FunctionWidget::setFocus()
{
  QWidget::setFocus();
  table->setFocus();
}

void FunctionWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

void FunctionWidget::slotTableCurrentChanged(int row, int col, int m , const QPoint & n)
{
  QString x = table->text(row, col);
  emit name(x);
}

void FunctionWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      int newWidth = re->size().width();

      newWidth -= 35; //Accounting for the left (vertical) header width.
      float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0, weight3 = 3.0 , weight4 = 3.0;
      float weightSum = weight0 + weight1 + weight2 + weight3 + weight4;
      int w0, w1, w2, w3 , w4;
      w0 = newWidth * (weight0 / weightSum);
      w1 = newWidth * (weight1 / weightSum);
      w2 = newWidth * (weight2 / weightSum);
      w3 = newWidth * (weight3 / weightSum);
      w4 = newWidth - w0 - w1 - w2 - w3;
      table->setColumnWidth(0, w0);
      table->setColumnWidth(1, w1);
      table->setColumnWidth(2, w2);
      table->setColumnWidth(3, w3);
      table->setColumnWidth(4, w4);
    }
}
