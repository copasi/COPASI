/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyTable.cpp,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/08/13 14:58:58 $
   End CVS Header */

#include <iostream>
#include <math.h>
#include "copasi.h"
#include <qmessagebox.h>
#include "MyTable.h" 
//#include "listviews.h"

MyTable::MyTable(QWidget * parent, const char * name)
    : QTable (parent, name), firstTime(true)
{
  setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding, 2, 1));
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
      emit delKeyPressed();
    }
}

void MyTable::showEvent(QShowEvent* e)
{
  int vertHeaderWidth = 0;
  if (this->verticalHeader() && this->verticalHeader()->count() > 0)
    {
      vertHeaderWidth = this->verticalHeader()->sectionRect(0).width();
    }
  int width = this->width() - vertHeaderWidth;

  if (this->firstTime)
    {
      this->firstTime = false;
      int widthOfColumns = 0;
      unsigned int counter, numCols;
      numCols = this->numCols();
      for (counter = 0; counter < numCols; counter++)
        {
          this->adjustColumn(counter);
          this->exactColumnWidth[counter] = (double)this->columnWidth(counter);
          widthOfColumns += this->columnWidth(counter);
        }
      if (widthOfColumns < width)
        {
          double factor = ((double)width) / ((double)widthOfColumns);
          for (counter = 0; counter < numCols; counter++)
            {
              this->exactColumnWidth[counter] = (double)this->columnWidth(counter) * factor;
              this->setColumnWidth(counter, (int)lround(this->exactColumnWidth[counter]));
            }
        }
    }
  QTable::showEvent(e);
}

void MyTable::resizeEvent(QResizeEvent* e)
{
  double vertHeaderWidth = 0.0;
  if (this->verticalHeader() && this->verticalHeader()->count() > 0)
    {
      vertHeaderWidth = (double)(this->verticalHeader()->sectionRect(0).width());
    }
  double oldWidth = (double)(e->oldSize().width() - vertHeaderWidth);
  double width = (double)(e->size().width()) - vertHeaderWidth;
  int numColumns = this->numCols();
  int optSizes[numColumns];
  int counter;
  if (this->contentsWidth() > width && oldWidth < width)
    {
      QTable::resizeEvent(e);
    }
  else
    {
      double factor = width / oldWidth;
      //std::cout << "oldWidth: " << oldWidth << std::endl;
      //std::cout << "width: " << width << std::endl;
      //std::cout << "factor: " << factor << std::endl;
      if (width < oldWidth)
        {
          //int tooSmall=-1;
          for (counter = 0; counter < numColumns; counter++)
            {
              optSizes[counter] = this->getOptimalColumnWidth(counter);
              if ((int)(this->exactColumnWidth[counter]*factor) < optSizes[counter])
                {
                  //tooSmall=counter;
                  //break;
                  return;
                }
            }
          /*
          if(tooSmall!=-1){
           return;
          }
          */
        }
      this->scaleColumns(factor);
    }
}

int MyTable::getOptimalColumnWidth(int index)
{
  int counter;
  int largest = this->horizontalHeader()->sectionSize(index);
  for (counter = 0; counter < this->numRows(); counter++)
    {
      QTableItem* it = this->item(counter, index);
      if (it)
        {
          int width = it->sizeHint().width();
          if (width > largest)
            {
              largest = width;
            }
        }
    }
  return largest;
}

void MyTable::scaleColumns(double factor)
{
  int counter;
  for (counter = 0; counter < this->numCols(); counter++)
    {
      this->exactColumnWidth[counter] = this->exactColumnWidth[counter] * factor;
      this->setColumnWidth(counter, (int)lround(this->exactColumnWidth[counter]));
    }
}

void MyTable::setNumCols(int count)
{
  this->exactColumnWidth.resize(count);
  QTable::setNumCols(count);
}

void MyTable::insertColumns(int index, int count)
{
  this->exactColumnWidth.resize(this->exactColumnWidth.size() + count);
  int counter;
  for (counter = index; counter < index + count; counter++)
    {
      this->exactColumnWidth[counter + count] = this->exactColumnWidth[counter];
    }
  QTable::insertColumns(index, count);
}

void MyTable::removeColumn(int col)
{
  unsigned int counter;
  for (counter = col + 1; counter < this->exactColumnWidth.size(); counter++)
    {
      this->exactColumnWidth[counter - 1] = this->exactColumnWidth[counter];
    }
  this->exactColumnWidth.resize(this->exactColumnWidth.size() - 1);
  QTable::removeColumn(col);
}

void MyTable::removeColumns(const QMemArray<int> & cols)
{
  unsigned int counter1;
  for (counter1 = 0; counter1 < cols.size(); counter1++)
    {
      unsigned int counter2;
      for (counter2 = cols[counter1] + 1; counter2 < this->exactColumnWidth.size() - counter1; counter2++)
        {
          this->exactColumnWidth[counter2 - 1] = this->exactColumnWidth[counter2];
        }
    }
  this->exactColumnWidth.resize(this->exactColumnWidth.size() - cols.size());
  QTable::removeColumns(cols);
}
