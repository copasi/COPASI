/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/main.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:32:39 $
   End CVS Header */

// a dummy for testing the plots
#include <qapplication.h>
#include "plotwidget1.h"

int main(int argc, char **argv)
{
  QApplication a(argc, argv);

  PlotWidget1 plotWidget;

  a.setMainWidget(&plotWidget);
  //plotWidget.resize(600, 360);
  plotWidget.show();

  return a.exec();
}
