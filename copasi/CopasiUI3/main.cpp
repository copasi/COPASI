#include <qapplication.h>

#define COPASI_MAIN
#include "copasi.h"

#include "copasiui3window.h"

#include "model/model.h"
#include "function/function.h"
#include "output/output.h"
#include "steadystate/steadystate.h"
#include "trajectory/trajectory.h"
#include "utilities/utilities.h"
#include "utilities/CGlobals.h"

/**The main function for the COPASI UI.
*/
int main( int argc, char** argv )
{
  Copasi = new CGlobals;
  Copasi->setArguments(argc, argv);

  QApplication app( argc, argv );

	CopasiUI3Window window;
	app.setMainWidget(&window);

	window.resize(800, 600);
	window.show();
	
	return app.exec();
}

