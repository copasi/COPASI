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
