/****************************************************************************
** 
**
** 
**
** 
** 
**
*****************************************************************************/

#include <qapplication.h>

#define COPASI_MAIN
#include "copasiui3window.h"
#include "utilities/CGlobals.h"

int main( int argc, char **argv )
{
  Copasi = new CGlobals;
    QApplication a( argc, argv );
	
	CopasiUI3Window window;
	a.setMainWidget(&window);

	window.resize(800, 600);
	window.show();
	
	return a.exec();
	 
	 
}
