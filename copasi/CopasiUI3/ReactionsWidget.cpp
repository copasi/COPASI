#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>

#include "ReactionsWidget.h"
#include "MyTreeAndListWidget.h"



/** 
 *  Constructs a Widget for the Metabolites subsection of the tree.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param model The CModel class which contains the metabolites 
 *  to be displayed.
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
			
	table = new MyTable(0, 2, this, "tblReactions");
	QVBoxLayout *vBoxLayout = new QVBoxLayout( this, 0 );
	vBoxLayout->addWidget(table);

	//Setting table headers
	QHeader *tableHeader = table->horizontalHeader();
	tableHeader->setLabel(0, "Name");
	tableHeader->setLabel(1, "Reaction");

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
	table->setSorting ( TRUE );
	table->setFocusPolicy(QWidget::WheelFocus);

	
	// signals and slots connections
    connect( table, SIGNAL( clicked( int, int, int, const QPoint &) ), this, SLOT( slotTableClicked( int, int, int, const QPoint &) ) );
	connect( table, SIGNAL( currentChanged ( int, int ) ), this, SLOT( slotTableCurrentChanged( int, int ) ) );
	connect( table, SIGNAL( selectionChanged () ), this, SLOT( slotTableSelectionChanged () ) );
	connect( btnOK, SIGNAL( clicked () ), this, SLOT( slotBtnOKClicked() ) );
	connect( btnCancel, SIGNAL( clicked () ), this, SLOT( slotBtnCancelClicked() ) );

}

void ReactionsWidget::loadReactions(CModel *model)
{
	if (model != NULL)
	{
		mModel = model;
		//Emptying the table
		int numberOfRows = table->numRows();
		for(int i = 0; i < numberOfRows; i++)
		{
			table->removeRow(0);
		}
		
		CCopasiVectorS < CReaction > & reactions = mModel->getReactions();
		C_INT32 noOfReactionsRows = reactions.size();
		table->insertRows (0, noOfReactionsRows);
		
		//Now filling the table.
		CReaction *reactn;
		CChemEq chemEq;
		for (C_INT32 j = 0; j < noOfReactionsRows; j++)
		{
			reactn = reactions[j];
			table->setText(j, 0, reactn->getName().c_str());
			chemEq = reactn->getChemEq();
			table->setText(j, 1, chemEq.getChemicalEquation().c_str());
					
		}
	}
}


void ReactionsWidget::mousePressEvent ( QMouseEvent * e )
{
	QMessageBox::information( this, "Application name",
                            "Clicked (mousePress) On Reactions Widget." );

	QWidget::mousePressEvent(e);
	table->setFocus();

}


void ReactionsWidget::slotTableClicked( int row, int col, int button, const QPoint & mousePos )
{
	//QMessageBox::information( this, "Application name",
		//"Clicked (Inside ReactionsWidget::slotTableClicked) On Reactions table." );	

}

void ReactionsWidget::slotBtnOKClicked()
{
	QMessageBox::information( this, "Reactions Widget",
		"Clicked Ok button On Reactions widget.(Inside ReactionsWidget::slotBtnOKClicked())" );	
}

void ReactionsWidget::slotBtnCancelClicked()
{
	QMessageBox::information( this, "Reactions Widget",
		"Clicked Ok button On Reactions widget.(Inside ReactionsWidget::slotBtnCancelClicked())" );	
}

void ReactionsWidget::slotTableCurrentChanged( int row, int col )
{
	//QMessageBox::information( this, "Reactions Widget",
		//"Current Changed.(Inside ReactionsWidget::slotTableCurrentChanged())" );	
}

void ReactionsWidget::slotTableSelectionChanged() 
{
	if (!table->hasFocus())
	{
		table->setFocus();
	}
}


void ReactionsWidget::resizeEvent( QResizeEvent * re)
{
	if (isVisible())
	{
		int newWidth = re->size().width();
		
		newWidth -= 35;	//Accounting for the left (vertical) header width.
		float weight0 = 3.5, weight1 = 6.5;
		float weightSum = weight0 + weight1;
		int w0, w1;
		w0 = newWidth * (weight0 / weightSum);
		w1 = newWidth - w0;
		table->setColumnWidth(0, w0);
		table->setColumnWidth(1, w1);
	}
		
}