#include <qapplication.h>
#include "copasiui3window.h"

#include "copasi.h"
#include "model/model.h"
#include "function/function.h"
#include "output/output.h"
#include "steadystate/steadystate.h"
#include "trajectory/trajectory.h"
#include "utilities/utilities.h"

int main( int argc, char** argv )
{
	QApplication app( argc, argv );

	CopasiUI3Window window;
	app.setMainWidget(&window);

	window.show();

	return app.exec();
}

