
#include <qmessagebox.h>
#include "MyTable.h"

MyTable::MyTable(QWidget * parent, const char * name)
    : QTable (parent, name)
{
  deleteConfirmation = TRUE;
}

MyTable::MyTable(int numRows, int numCols, QWidget * parent, const char * name)
    : QTable (numRows, numCols, parent, name)
{
  deleteConfirmation = TRUE;
}

/*void MyTable::mousePressEvent(QMouseEvent *mpe)
{
 QMessageBox::information(this, "Application name",
                            "Clicked (mousePress) on table.");
 QTable::mousePressEvent(mpe); 
 setFocus();
}
 
 */
void MyTable::keyPressEvent (QKeyEvent * e)
{
  QTable::keyPressEvent(e);
  Qt::Key k = Qt::Key_Delete;
  //Process Delete Key

  if (e->key() == k)
    {
      int choice = 1;

      if (deleteConfirmation)
        {
          choice = QMessageBox::warning(this, "Confirm Delete",
                                        "Delete Selected Rows?\n"
                                        "Only Fully Selected Rows will be deleted." ,
                                        "Yes", "No", 0, 0, 1);
        }

      switch (choice)
        {
        case 0:  // Yes or Enter
          {
            removeSelectedRows(TRUE);
            //True for Completely selected rows.
            break;
          }

        case 1:  // No or Escape
          {
            // No
            break;
          }
        }
    }
}

void MyTable::setDeleteConfirmation(bool enable)
{
  deleteConfirmation = enable;
}

void MyTable::removeRow(int row)
{
  int I = numRows();

  for (int i = row; i < I - 1 ; i++)
    {
      swapRows(i, i + 1);
    }

  setNumRows(numRows() - 1);
}

void MyTable::removeSelectedRows(bool full)
{
  int I = numRows();
  int noOfRowsDeleted = 0;

  for (int i = 0; i < I; i++)
    {
      if (noOfRowsDeleted > 0)
        {
          swapRows(i, i - noOfRowsDeleted);
        }

      if (isRowSelected (i, full))
        {
          noOfRowsDeleted++;
        }
    }

  setNumRows(numRows() - noOfRowsDeleted);
}

void MyTable::setSorting (bool b, bool wholeRows)
{
  if (wholeRows)
    {
    }
  else
    {
      QTable::setSorting(b);
    }
}
