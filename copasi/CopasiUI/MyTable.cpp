/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyTable.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/08/12 21:02:22 $
   End CVS Header */

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
  /*
      if (this->firstTime)
      {
        this->firstTime = false;
        unsigned int widthOfColumns=0;
        unsigned int counter, numCols;
        numCols = this->numCols();
        for (counter = 0; counter < numCols; counter++)
          {
            this->adjustColumn(counter);
            widthOfColumns+=this->columnWidth(counter);
          }
        if(widthOfColumns<this->width()){
            double factor=this->width()/widthOfColumns; 
            for (counter = 0; counter < numCols; counter++)
            {
                this->setColumnWidth(counter,(int)((double)this->columnWidth(counter)*factor));
            }
        }
      }
    QTable::showEvent(e);
    */
}

void MyTable::resizeEvent(QResizeEvent* e)
{
  /*
      double oldWidth=(double)(e->oldSize().width());
      double width=(double)(e->size().width());
      if(width>oldWidth){
          double factor=width/oldWidth;
          int counter;
          for(counter = 0; counter < this->numCols(); counter++){
              this->setColumnWidth(counter,(int)(this->columnWidth(counter)*factor));
          }
      }
      else{
          double factor=width/oldWidth;
          int sizes[this->numCols()];
          int optSizes[this->numCols()];
          int counter;
          int tooSmall=-1;
          for(counter = 0; counter < this->numCols(); counter++){
              sizes[counter]=this->columnWidth(counter);
              int newSize=(int)((double)sizes[counter]*factor);
              this->adjustColumn(counter);
              optSizes[counter]=this->columnWidth(counter);
              if(newSize<optSizes[counter]){
                  tooSmall=counter;
                  break;
              }
              else{
                  this->setColumnWidth(counter,newSize);
              }
          }
          if(tooSmall!=-1){
              for(counter=0; counter<tooSmall+1; counter++){
                  this->setColumnWidth(counter,sizes[counter]);
              }
          }
          
      }
  */
}
