/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MyTable.cpp,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/08/12 16:02:09 $
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
  if (this->firstTime)
    {
      this->firstTime = false;
      unsigned int counter, numCols;
      numCols = this->numCols();
      for (counter = 0; counter < numCols; counter++)
        {
          //this->setColumnStretchable(counter,true);
        }
    }
  QTable::showEvent(e);
}
