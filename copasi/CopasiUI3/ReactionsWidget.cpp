#include <qlayout.h>
#include <qwidget.h>

#include "ReactionsWidget.h"
#include "MyTreeAndListWidget.h"



/** 
 *  Constructs a Widget for the Metabolites subsection of the tree.
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
ReactionsWidget::ReactionsWidget(QWidget *parent, const char * name, WFlags f)
						: QWidget(parent, name, f)
{
			
	table = new QTable(20, 2, this);
	QVBoxLayout *vBoxLayout = new QVBoxLayout( this, 0 );
	vBoxLayout->addWidget(table);

	//Setting table headers
	QHeader *tableHeader = table->horizontalHeader();
	tableHeader->setLabel(0, "Name");
	tableHeader->setLabel(1, "Reaction");

	//Setting Column Widths
	table->setColumnWidth ( 0, 100 );
	table->setColumnWidth ( 1, 300 ); 

	btnOK = new QPushButton("&OK", this);
	btnCancel = new QPushButton("&Cancel", this);

	QHBoxLayout *hBoxLayout = new QHBoxLayout( vBoxLayout, 0 );
	
	//To match the Table left Vertical Header Column Width.
	hBoxLayout->addSpacing( 32 );
	
	hBoxLayout->addSpacing( 50 );
	hBoxLayout->addWidget(btnOK);
	hBoxLayout->addSpacing( 5 );
	hBoxLayout->addWidget(btnCancel);
	hBoxLayout->addSpacing( 50 );
	
	


	table->sortColumn (0, TRUE, TRUE);
	
}

