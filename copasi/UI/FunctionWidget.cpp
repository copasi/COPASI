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
  binitialized = true;

  table = new MyTable(0, 2, this, "tblFunctions");
  table->setNumRows(-1);
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
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)),
          this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(this, SIGNAL(name(const QString &)),
          (ListViews*)parent, SLOT(slotFunctionTableChanged(const QString &)));
  connect(table, SIGNAL(selectionChanged ()),
          this, SLOT(slotTableSelectionChanged ()));

  connect(this, SIGNAL(informUpdated()), (ListViews*)parent, SLOT(dataModelUpdated()));
  connect(this, SIGNAL(update()), (ListViews*)parent, SLOT(loadFunction()));
}

void FunctionWidget::loadFunction()
{
  //Emptying the table
  int numberOfRows = table->numRows();
  int i;
  for (i = 0; i < numberOfRows; i++)
    {
      table->removeRow(0);
    }

  //Now filling the table.
  repaint_table();
}

void FunctionWidget::repaint_table()
{
  CCopasiVectorNS< CFunction > & Functions =
    Copasi->pFunctionDB->loadedFunctions();

  C_INT32 noOfFunctionsRows = Functions.size();
  table->setNumRows(noOfFunctionsRows);
  CFunction *funct;
  C_INT32 j;
  for (j = 0; j < noOfFunctionsRows; j++)
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
  if (row == table->numRows() - 1)
    {
      std::string name = "Function";
      CFunction* newFunction = new CFunction(name);
      int i = 0;
      while (Copasi->pFunctionDB->findFunction(name) != NULL)
        {
          i++;
          name = "Function";
          name += "_";
          name += QString::number(i);
        }
      newFunction->setName(name);
      Copasi->pFunctionDB->add(newFunction);
      table->setNumRows(table->numRows());
      table->setText(row, 0, name.c_str());
      x = name.c_str();
      emit update();
      emit informUpdated();
    }
  emit name(x);
}

void FunctionWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      repaint_table();
      if (binitialized)
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
          binitialized = false;
        }
      else
        {
          table->DisableColWidthUpdate();
          int newWidth = re->size().width();
          int i;

          int totalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            totalWidth += table->columnWidth(i);

          int minTotalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            minTotalWidth += table->minColWidth[i];

          //Zoom in
          if (newWidth > re->oldSize().width())
            {
              if (newWidth > totalWidth) // can do expansion
                {
                  if (totalWidth < re->oldSize().width())
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, newWidth*table->columnWidth(i) / re->oldSize().width());
                  else
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, float(newWidth)*float(table->columnWidth(i)) / float(totalWidth));
                }
              else
                for (i = 0; i < table->numCols(); i++) // Do not expand
                  table->setColumnWidth(i, table->columnWidth(i));

              table->EnableColWidthUpdate();
              return;
            }
          //Zoom out
          //calculate total Width
          if (newWidth >= totalWidth)    //will not decrease any column width
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->columnWidth(i));
              table->EnableColWidthUpdate();
              return;
            }
          //will decrease only those larger than the minimum width
          //Less than the user specified total width
          if (newWidth <= minTotalWidth)
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->minColWidth[i]);
              table->EnableColWidthUpdate();
              return;
            }
          //Bigger than the user specified total width
          for (i = 0; i < table->numCols(); i++) // Do Expansion
            table->setColumnWidth(i, (newWidth - minTotalWidth)*(table->columnWidth(i) - table->minColWidth[i]) / (totalWidth - minTotalWidth) + table->minColWidth[i]);
          table->EnableColWidthUpdate();
          return;
        }
    }
}
