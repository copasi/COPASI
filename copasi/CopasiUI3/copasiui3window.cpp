#include "copasiui3window.h"
#include "MyTreeAndListWidget.h"

#include <qlayout.h>

CopasiUI3Window::CopasiUI3Window( QWidget* parent, const char* name, WFlags f )
	: QMainWindow( parent, name, f )
{
	setCaption("Copasi Tree Front-End");
	
	// Make the top-level layout; a vertical box to contain all widgets
    // and sub-layouts.
    QBoxLayout *topLayout = new QVBoxLayout( this, 5 );
	
	mtlw = new MyTreeAndListWidget(this);
	topLayout->addWidget(mtlw);
	

	resize(666, 400);
	

}

