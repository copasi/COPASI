#include "copasiui3window.h"
#include "MyTreeAndListWidget.h"

#include <qlayout.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qfiledialog.h>


#include "./icons/fileopen.xpm"
#include "./icons/filesave.xpm"
#include "./icons/fileprint.xpm"

  
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
    // Set the window caption/title
    setCaption("Copasi Tree Front-End");

    // create a toolbar
    tbMain = new QToolBar( this, "MainToolBar" );

    // put something in it
    QPixmap openIcon( fileopen );
    QToolButton * toolb = new QToolButton( openIcon, "Open",
					   "Open a new file for simulation", this, 
					   SLOT(slotFileOpen()),tbMain, "OpenFile" );
    QWhatsThis::add( toolb, 
				"Click to <b>open a gps</b> file for simulation.");

    QPixmap saveIcon( filesave );
    toolb = new QToolButton( saveIcon, "Save", "Save into a file",
			     this, SLOT(slotFileSave()),
			     tbMain, "SaveFile" );
    QWhatsThis::add( toolb, "Click to <b>save</b> a file." );

    QPixmap  printIcon( fileprint );
    toolb = new QToolButton( printIcon, "Print", QString::null,
			     this, SLOT(slotFilePrint()),
			     tbMain, "print file" );
    QWhatsThis::add( toolb, "Click to <b>print</b>.");

    toolb = QWhatsThis::whatsThisButton( tbMain );
    QWhatsThis::add( toolb, "This is a <b>What's This</b> button "
		     "It enables the user to ask for help "
		     "about widgets on the screen.");
	

	
	// Make the top-level layout; a vertical box to contain all widgets
    // and sub-layouts.
    QBoxLayout *topLayout = new QVBoxLayout( this, 5 );
		
	mtlw = new MyTreeAndListWidget(this);
	//make a central widget to contain the other widgets
    setCentralWidget( mtlw );
		
	topLayout->addWidget(mtlw);
	
	//Resize the main application window
	resize(666, 400);


}

void CopasiUI3Window::slotFileOpen()
{
	QString gpsFile = QFileDialog::getOpenFileName(
                   QString::null, "GPS Files (*.gps)",
                    this, "open file dialog",
                    "Choose a file" );
	try
	{
		//CReadConfig inbuf("gps/bakker.gps");
		CReadConfig inbuf((const char *)gpsFile.utf8());
                mModel.load(inbuf);
	}
	catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }
	mtlw->loadNodes(&mModel);
}

void CopasiUI3Window::slotFileSave()
{
}

void CopasiUI3Window::slotFilePrint()
{
}
