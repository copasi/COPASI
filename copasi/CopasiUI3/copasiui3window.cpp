#include "copasiui3window.h"
#include "MyTreeAndListWidget.h"

#include <qlayout.h>

  
/** 
 *  Constructs a CopasiUI window which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.  
 *  @param parent The widget which this window is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Redfer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */
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

