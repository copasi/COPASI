
#include "MyTreeAndListWidget.h"
#include "MyCheckListItem.h"
#include <qmessagebox.h>



/* XPM */
 

static const char* folder_closed_xpm[]={
    "16 16 9 1",
    "g c #808080",
    "b c #c0c000",
    "e c #c0c0c0",
    "# c #000000",
    "c c #ffff00",
    ". c None",
    "a c #585858",
    "f c #a0a0a4",
    "d c #ffffff",
    "..###...........",
    ".#abc##.........",
    ".#daabc#####....",
    ".#ddeaabbccc#...",
    ".#dedeeabbbba...",
    ".#edeeeeaaaab#..",
    ".#deeeeeeefe#ba.",
    ".#eeeeeeefef#ba.",
    ".#eeeeeefeff#ba.",
    ".#eeeeefefff#ba.",
    ".##geefeffff#ba.",
    "...##gefffff#ba.",
    ".....##fffff#ba.",
    ".......##fff#b##",
    ".........##f#b##",
    "...........####."};

static const char* folder_open_xpm[]={
    "16 16 11 1",
    "# c #000000",
    "g c #c0c0c0",
    "e c #303030",
    "a c #ffa858",
    "b c #808080",
    "d c #a0a0a4",
    "f c #585858",
    "c c #ffdca8",
    "h c #dcdcdc",
    "i c #ffffff",
    ". c None",
    "....###.........",
    "....#ab##.......",
    "....#acab####...",
    "###.#acccccca#..",
    "#ddefaaaccccca#.",
    "#bdddbaaaacccab#",
    ".eddddbbaaaacab#",
    ".#bddggdbbaaaab#",
    "..edgdggggbbaab#",
    "..#bgggghghdaab#",
    "...ebhggghicfab#",
    "....#edhhiiidab#",
    "......#egiiicfb#",
    "........#egiibb#",
    "..........#egib#",
    "............#ee#"};

static const char * folder_locked[]={
    "16 16 10 1",
    "h c #808080",
    "b c #ffa858",
    "f c #c0c0c0",
    "e c #c05800",
    "# c #000000",
    "c c #ffdca8",
    ". c None",
    "a c #585858",
    "g c #a0a0a4",
    "d c #ffffff",
    "..#a#...........",
    ".#abc####.......",
    ".#daa#eee#......",
    ".#ddf#e##b#.....",
    ".#dfd#e#bcb##...",
    ".#fdccc#daaab#..",
    ".#dfbbbccgfg#ba.",
    ".#ffb#ebbfgg#ba.",
    ".#ffbbe#bggg#ba.",
    ".#fffbbebggg#ba.",
    ".##hf#ebbggg#ba.",
    "...###e#gggg#ba.",
    ".....#e#gggg#ba.",
    "......###ggg#b##",
    ".........##g#b##",
    "...........####."};


QPixmap *folderLocked = 0;
QPixmap *folderClosed = 0;
QPixmap *folderOpen = 0;



/** 
 *  Constructs a widget which has a tree on the left and an area to display
 *  another widget on the right side of a splitter.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param parent The widget which this widget is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Redfer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */

MyTreeAndListWidget::MyTreeAndListWidget( QWidget *parent, const char *name )
    : QSplitter( Qt::Horizontal, parent, name )
{
    try
	{
		CReadConfig inbuf("gps/bakker.gps");
		mModel.load(inbuf);
	}
	catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }

	if ( !name )
	setName( "MyTreeAndListWidget" );
        

    ListView1 = new QListView( this, "ListView1" );
	
	
	folderLocked = new QPixmap( ( const char** )folder_locked );
	folderClosed = new QPixmap( ( const char** )folder_closed_xpm );
	folderOpen = new QPixmap( ( const char** )folder_open_xpm );
	
	QListViewItem *defaultItem = initializeTree();
	this->setResizeMode( ListView1, QSplitter::KeepSize );
	
	// Make  a big widget that will grab all space.
    bigWidget = new QMultiLineEdit( this );
    bigWidget->setText( "This widget will get all the remaining space" );
    bigWidget->setFrameStyle( QFrame::Panel | QFrame::Plain );
	bigWidget->setReadOnly(TRUE);

	//Constructing the Metabolites Widget
	metabolitesWidget = new MetabolitesWidget( &mModel, this );
	metabolitesWidget->hide();


	//Constructing the Reactions Widget
	reactionsWidget = new ReactionsWidget( this );
	reactionsWidget->hide();
	
	   
	// signals and slots connections
    connect( ListView1, SIGNAL( selectionChanged(QListViewItem*) ), this, SLOT( slotTreeSelectionChanged(QListViewItem*) ) );
	
	
	//Selecting up the default item.
	ListView1->setSelected ( defaultItem, TRUE ) ;
		
}


/**Method used to construct the subtrees in the tree widget. 
 */

QListViewItem* MyTreeAndListWidget::initializeTree()
{
	

	ListView1->addColumn( tr( "Select One" ) );
    ListView1->header()->setLabel( ListView1->header()->count() - 1, *folderLocked, tr( "Select One" ) );
	ListView1->setRootIsDecorated ( TRUE );
	QListViewItem *defaultItem, *after;

	QListViewItem * item_2 = new QListViewItem( ListView1, 0 );
    item_2->setOpen( TRUE );
    QListViewItem * item_3 = new QListViewItem( item_2, 0 );
    item_3->setOpen( TRUE );
    QListViewItem * item = new QListViewItem( item_3, 0 );
    item->setText( 0, tr( "Reactions" ) );
    item->setPixmap( 0, *folderClosed );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "Metabolites" ) );
    item->setPixmap( 0, *folderClosed );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "Compartments" ) );
    item->setPixmap( 0, *folderClosed );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "Moieties" ) );
    item->setPixmap( 0, *folderClosed );
    item_3->setText( 0, tr( "BioChem" ) );
    item_3->setPixmap( 0, *folderClosed );
    item_2->setOpen( TRUE );
    item = new QListViewItem( item_2, item_3 );
    item->setText( 0, tr( "Maths" ) );
    item->setPixmap( 0, *folderClosed );
    item_2->setText( 0, tr( "Model" ) );
    item_2->setPixmap( 0, *folderClosed );
	defaultItem = item_2;

    QListViewItem * item_4 = new QListViewItem( ListView1, item_2 );
    item_4->setOpen( TRUE );
    QListViewItem * item_5 = new QListViewItem( item_4, item_2 );
    item_5->setOpen( TRUE );
    item = new QListViewItem( item_5, item_2 );
    item->setText( 0, tr( "Mass Conservation" ) );
    item->setPixmap( 0, *folderClosed );
    item_5->setOpen( TRUE );
    item = new QListViewItem( item_5, item );
    item->setText( 0, tr( "Elementary Modes" ) );
    item->setPixmap( 0, *folderClosed );
    item_5->setText( 0, tr( "Stoichiometry" ) );
    item_5->setPixmap( 0, *folderClosed );
    item_4->setOpen( TRUE );
    
	after = item_5;
	//QListViewItem * item_6 = new QListViewItem( item_4, item_5 );
	MyCheckListItem * item_6 = new MyCheckListItem( item_4, "TimeCourse", QCheckListItem::CheckBox);
	item_6->moveItem(after);
    item_6->setOpen( TRUE );
	

    item = new QListViewItem( item_6, item_5 );
    item->setText( 0, tr( "Trajectory" ) );
    item->setPixmap( 0, *folderClosed );
    item_6->setOpen( TRUE );
    item = new QListViewItem( item_6, item );
    item->setText( 0, tr( "Phase Plane" ) );
    item->setPixmap( 0, *folderClosed );
    item_6->setOpen( TRUE );
    
		
	item = new QListViewItem( item_6, item );
    item->setText( 0, tr( "MCA" ) );
    item->setPixmap( 0, *folderClosed );
    item_6->setText( 0, tr( "Time Course" ) );
    item_6->setPixmap( 0, *folderClosed );
    item_4->setOpen( TRUE );
    
	//QListViewItem * item_7 = new QListViewItem( item_4, item_6 );
    after = item_6;
	MyCheckListItem * item_7 = new MyCheckListItem( item_4, "SteadyState", QCheckListItem::CheckBox);
	item_7->moveItem(after);
	
	item_7->setOpen( TRUE );
    item = new QListViewItem( item_7, item_6 );
    item->setText( 0, tr( "State" ) );
    item->setPixmap( 0, *folderClosed );
    item_7->setOpen( TRUE );
    item = new QListViewItem( item_7, item );
    item->setText( 0, tr( "MCA" ) );
    item->setPixmap( 0, *folderClosed );
    item_7->setOpen( TRUE );
    item = new QListViewItem( item_7, item );
    item->setText( 0, tr( "Stability" ) );
    item->setPixmap( 0, *folderClosed );
    item_7->setOpen( TRUE );
    
    item = new QListViewItem( item_7, item );
	item->setText( 0, tr( "Bifurcation" ) );
    item->setPixmap( 0, *folderClosed );
    item_7->setText( 0, tr( "Steady - State" ) );
    item_7->setPixmap( 0, *folderClosed );
    item_4->setText( 0, tr( "Tasks" ) );
    item_4->setPixmap( 0, *folderClosed );

    QListViewItem * item_8 = new QListViewItem( ListView1, item_4 );
    item_8->setOpen( TRUE );
    item = new QListViewItem( item_8, item_4 );
    item->setText( 0, tr( "Scan" ) );
    item->setPixmap( 0, *folderClosed );
    item_8->setOpen( TRUE );
    item = new QListViewItem( item_8, item );
    item->setText( 0, tr( "Optimization" ) );
    item->setPixmap( 0, *folderClosed );
    item_8->setText( 0, tr( "Multiple Tasks" ) );
    item_8->setPixmap( 0, *folderClosed );

    QListViewItem * item_9 = new QListViewItem( ListView1, item_8 );
    item_9->setOpen( TRUE );
    item = new QListViewItem( item_9, item_8 );
    item->setText( 0, tr( "Data File" ) );
    item->setPixmap( 0, *folderClosed );
    item_9->setOpen( TRUE );
    item = new QListViewItem( item_9, item );
    item->setText( 0, tr( "Method" ) );
    item->setPixmap( 0, *folderClosed );
    item_9->setText( 0, tr( "Fitting" ) );
    item_9->setPixmap( 0, *folderClosed );

    QListViewItem * item_10 = new QListViewItem( ListView1, item_9 );
    item_10->setOpen( TRUE );
    item = new QListViewItem( item_10, item_9 );
    item->setText( 0, tr( "Plots" ) );
    item->setPixmap( 0, *folderClosed );
    item_10->setOpen( TRUE );
    item = new QListViewItem( item_10, item );
    item->setText( 0, tr( "Pathway" ) );
    item->setPixmap( 0, *folderClosed );
    item_10->setOpen( TRUE );
    item = new QListViewItem( item_10, item );
    item->setText( 0, tr( "Reports" ) );
    item->setPixmap( 0, *folderClosed );
    item_10->setText( 0, tr( "Output" ) );

    item = new QListViewItem( ListView1, item_10 );
    item->setText( 0, tr( "Preferences" ) );
    item->setPixmap( 0, *folderClosed );


	//This prohibits sorting...original order maintained.
	ListView1->setSorting (-1);
	//ListView1->setShowSortIndicator (true);
    ListView1->setGeometry( QRect( 10, 10, 600, 400 ) ); 
	
	//Setting Items under checkbox unselectable. Should be close to the
	//end (after the children have been initialized);
	item_6->stateChange(FALSE);
	item_7->stateChange(FALSE);
	
	return defaultItem;
}

/**Called when user clicks on a new item on the tree. Changes that are to be 
 * done as a result of clicking a new folder in the tree are to be done here. 
 */
void MyTreeAndListWidget::slotTreeSelectionChanged(QListViewItem* item)
{
    
	/**Maintains static
	* variables to remember the last item clicked. The last item has
	* to be remembered so that it may be modified (for example 
	* to change back their icon etc).
	*/
	static QListViewItem* lastSelection = NULL;
	static QWidget* lastWidget = NULL;
	static QWidget* currentWidget = bigWidget;
	
	
	//qWarning( "CopasiUI2DialogBase::slotTreeSelectionChanged(QListViewItem*): Not implemented yet!" );
	
	/*QMessageBox::information( this, "CopasiUI Application",
                              "Hi!!\n"
                              "I am inside MyTreeAndListWidget::slotTreeSelectionChanged.\n"
							  "You clicked: " + item->text(0));*/
		
	item->setPixmap( 0, *folderOpen );
	if (lastSelection)
	{
		lastSelection->setPixmap( 0, *folderClosed );
	}
	lastSelection = item;

	
	QString selectedItem = item->text(0);
	if (selectedItem == "Metabolites")
	{
		lastWidget->hide();
		currentWidget = metabolitesWidget;
	}
	else if  (selectedItem == "Reactions")
	{
		lastWidget->hide();
		currentWidget = reactionsWidget;
	}
	else if  (selectedItem == "ODEs")
	{
		//Carry on this way for other Items
		bigWidget->setText("You Clicked On: " + selectedItem);
	}
	else
	{
		bigWidget->setText("You Clicked On: " + selectedItem);
		currentWidget = bigWidget;
	}


	if (lastWidget)
	{
		lastWidget->hide();
	}
	if (currentWidget)	
	{
		currentWidget->show();
	}
	lastWidget = currentWidget;
		
}


	
