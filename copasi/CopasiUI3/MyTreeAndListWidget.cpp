
#include "MyTreeAndListWidget.h"
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


/*
static const char* const folder_locked[] = { 
"24 22 4 1",
"# c #000000",
"b c #808080",
". c #c0c0c0",
//". c None",
"a c #ffffff",
".######################.",
"#aaaaaaaaaaaaaaaaaaaaab#",
"#a...................bb#",
"#a...................bb#",
"#a......#######......bb#",
"#a....##aaaaaaa##....bb#",
"#a...#aaaaaaaaaaa#...bb#",
"#a..#aaaaaaaaaaaaa#..bb#",
"#a..#aaaaaaaaaaaaa#..bb#",
"#a..#aaaaaaaaaaaaa#..bb#",
"#a..#aaaaaaaaaaaaa#..bb#",
"#a...#aaaaaaaaaaa#...bb#",
"#a....##aaaaaaa##....bb#",
"#a......#aa####......bb#",
"#a......#a#..........bb#",
"#a......##...........bb#",
"#a......#............bb#",
"#a...................bb#",
"#a...................bb#",
"#abbbbbbbbbbbbbbbbbbbbb#",
"#bbbbbbbbbbbbbbbbbbbbbb#",
".######################."};
*/




  
/* 
 *  Constructs a CopasiUI2DialogBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */

MyTreeAndListWidget::MyTreeAndListWidget( QWidget *parent, const char *name )
    : QSplitter( Qt::Horizontal, parent, name )
{

    if ( !name )
	setName( "MyTreeAndListWidget" );
    //resize( 838, 518 ); 
    //setProperty( "caption", tr( "CopasiUI2" ) );
    //setProperty( "sizeGripEnabled", QVariant( TRUE, 0 ) );

    ListView1 = new MyListView( this, "ListView1" );
	
	
	folderLocked = new QPixmap( ( const char** )folder_locked );
	folderClosed = new QPixmap( ( const char** )folder_closed_xpm );
	folderOpen = new QPixmap( ( const char** )folder_open_xpm );
	
	QListViewItem *defaultItem = initializeTree();
	this->setResizeMode( ListView1, QSplitter::KeepSize );
	
	// Make  a big widget that will grab all space.
    bigWidget = new QMultiLineEdit( this );
    bigWidget->setText( "This widget will get all the remaining space" );
    bigWidget->setFrameStyle( QFrame::Panel | QFrame::Plain );

	bigWidget2 = new QLineEdit(this);
	bigWidget2->setText( "This is the second widget." );
	bigWidget2->hide();
   
	// signals and slots connections
    connect( ListView1, SIGNAL( selectionChanged(QListViewItem*) ), this, SLOT( slotTreeSelectionChanged(QListViewItem*) ) );
	
	
	//Selecting up the default item.
	ListView1->setSelected ( defaultItem, TRUE ) ;
	
}



QListViewItem* MyTreeAndListWidget::initializeTree()
{
	
	/*QPixmap folderLocked( ( const char** ) folder_locked );
	QPixmap folderLocked( ( const char** ) folder_open_xpm );
	QPixmap folderClosed( ( const char** ) folder_closed_xpm );
	*/

	ListView1->addColumn( tr( "Select One" ) );
    ListView1->header()->setLabel( ListView1->header()->count() - 1, *folderLocked, tr( "Select One" ) );
	ListView1->setRootIsDecorated ( TRUE );
    QListViewItem * item_2 = new QListViewItem( ListView1, 0 );
    item_2->setOpen( TRUE );
    QListViewItem * item = new QListViewItem( item_2, 0 );
    item->setText( 0, tr( "Reactions" ) );
    item->setPixmap( 0, *folderClosed );
    item_2->setOpen( TRUE );
    item = new QListViewItem( item_2, item );
    item->setText( 0, tr( "Metabolites" ) );
    item->setPixmap( 0, *folderClosed );
    item_2->setOpen( TRUE );
    item = new QListViewItem( item_2, item );
    item->setText( 0, tr( "Compartments" ) );
    item->setPixmap( 0, *folderClosed );
    item_2->setOpen( TRUE );
    item = new QListViewItem( item_2, item );
    item->setText( 0, tr( "Moieties" ) );
    item->setPixmap( 0, *folderClosed );
    item_2->setText( 0, tr( "Model" ) );
    item_2->setPixmap( 0, *folderClosed );
	QListViewItem *defaultItem = item_2;

    item = new QListViewItem( ListView1, item_2 );
    item->setText( 0, tr( "ODEs" ) );
    item->setPixmap( 0, *folderClosed );

    QListViewItem * item_3 = new QListViewItem( ListView1, item );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "Time - Course" ) );
    item->setPixmap( 0, *folderClosed );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "Steady State" ) );
    item->setPixmap( 0, *folderClosed );
    item_3->setText( 0, tr( "Tasks" ) );
    item_3->setPixmap( 0, *folderClosed );

    item = new QListViewItem( ListView1, item_3 );
    item->setText( 0, tr( "Simulation" ) );
    item->setPixmap( 0, *folderClosed );

    QListViewItem * item_4 = new QListViewItem( ListView1, item );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "Dynamics" ) );
    item->setPixmap( 0, *folderClosed );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "MCA" ) );
    item->setPixmap( 0, *folderClosed );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "Stability" ) );
    item->setPixmap( 0, *folderClosed );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "Structure" ) );
    item->setPixmap( 0, *folderClosed );
    item_4->setText( 0, tr( "Analysis" ) );
    item_4->setPixmap( 0, *folderClosed );

    item = new QListViewItem( ListView1, item_4 );
    item->setText( 0, tr( "Preferences" ) );
    item->setPixmap( 0, *folderClosed );

	//This prohibits sorting...original order maintained.
	ListView1->setSorting (-1);
	//ListView1->setShowSortIndicator (true);
    ListView1->setGeometry( QRect( 10, 10, 200, 400 ) ); 
	
	return defaultItem;
}


void MyTreeAndListWidget::slotTreeSelectionChanged(QListViewItem* item)
{
    
	static QListViewItem* lastSelection = NULL;
	
	
	//qWarning( "CopasiUI2DialogBase::slotTreeSelectionChanged(QListViewItem*): Not implemented yet!" );
	
	/*QMessageBox::information( this, "CopasiUI Application",
                              "Hi!!\n"
                              "I am inside MyTreeAndListWidget::slotTreeSelectionChanged.\n"
							  "You clicked: " + item->text(0));*/
	bigWidget->setText("You Clicked On: " + item->text(0));
	
	item->setPixmap( 0, *folderOpen );
	if (lastSelection)
	{
		lastSelection->setPixmap( 0, *folderClosed );
	}
	lastSelection = item;

	/*
	switch(item->text(0))
	{
		case "ODEs":
		{
			bigWidget->hide();
			bigWidget2->show();

		}
		case default:
		{
			bigWidget->show();
			bigWidget2->hide();
		}
	}
	*/

}







/*********************************
Class MyListViewItem
**********************************
*/


MyListView::MyListView(QWidget * parent, const char * name):QListView(parent, name)
{
}

void MyListView::setOpen(QListViewItem * item, bool open )
{
	/*
	if (open)
	{
		item->setPixmap( 0, *folderClosed );
	}
	else
	{
		item->setPixmap( 0, *folderOpen );
	}*/
	QListView::setOpen(item, open);
}





		
	
