/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MyTable.cpp,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/08/10 13:58:14 $
   End CVS Header */

#include "copasi.h"
#include <qmessagebox.h>
#include "MyTable.h" 
//#include "listviews.h"

MyTable::MyTable(QWidget * parent, const char * name)
    : QTable (parent, name)
{}

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
