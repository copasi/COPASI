/****************************************************************************
 ** Form implementation generated from reading ui file '.\function2.ui'
 **
 ** Created: Thu May 30 18:47:54 2002
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "FunctionWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include "model/CMetab.h"
#include <qvariant.h>
#include <qtable.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include "utilities/CGlobals.h"
#include "function/function.h" 
/*
 *  Constructs a FunctionWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
FunctionWidget::FunctionWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  mModel = NULL;
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
  connect(table, SIGNAL(clicked (int, int, int, const QPoint &)), this, SLOT(slotTableClicked(int, int, int, const QPoint &)));
  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
}

// ************make changes for function widgets in this function **********

void FunctionWidget::loadFunction(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;

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
          //table->setText(j, 1, QString::number((funct->getType())));
          QString ftype;

          switch (funct->getType())
            {
            case 1:

            case 2:
              ftype = QString("pre-defined");
              //table->setText(j, 1, QString::number((funct->getType())));
              break;

            case 3:
              ftype = QString("user-defined");
              break;
            }

          table->setText(j, 1, ftype);
        }
    }
}

void FunctionWidget::setFocus()
{
  QWidget::setFocus();
  table->setFocus();
}

void FunctionWidget::slotTableClicked(int row, int col, int button, const QPoint & mousePos)
{
  //QMessageBox::information(this, "Application name",
  //"Clicked (mousePress) On Metabolites table.");

  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

void FunctionWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus())
    {
      table->setFocus();
    }
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
