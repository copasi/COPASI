#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>

#include "MetabolitesWidget.h"
#include "MyTreeAndListWidget.h"

#include "model/CMetab.h"

/** 
 *  Constructs a Widget for the Metabolites subsection of the tree for 
 *  displaying the Metabolites in model 'model'.
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
MetabolitesWidget::MetabolitesWidget(QWidget *parent, const char * name, WFlags f)
						: QWidget(parent, name, f)
{
	
		
	table = new MyTable(0, 4, this, "tblMetabolites");
	QVBoxLayout *vBoxLayout = new QVBoxLayout( this, 0 );
	vBoxLayout->addWidget(table);

	QHeader *tableHeader = table->horizontalHeader();
	tableHeader->setLabel(0, "Name");
	tableHeader->setLabel(1, "Concentration");
	tableHeader->setLabel(2, "Number");
	tableHeader->setLabel(3, "Status");
		
	//table->sortColumn (0, TRUE, TRUE);
	
	setFocusPolicy(QWidget::WheelFocus);
	setFocusProxy ( table );
	table->setFocusPolicy(QWidget::WheelFocus);

	// signals and slots connections
	connect( table, SIGNAL( clicked ( int, int, int, const QPoint &) ), this, SLOT( slotTableClicked( int, int, int, const QPoint &) ) );
	connect( table, SIGNAL( selectionChanged () ), this, SLOT( slotTableSelectionChanged () ) );
	
}

void MetabolitesWidget::loadMetabolites(CModel *model)
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
		
		vector < CMetab * > metabolites = mModel->getMetabolites();
		C_INT32 noOfMetabolitesRows = metabolites.size();
		table->insertRows (0, noOfMetabolitesRows);
		
		//Now filling the table.
		CMetab *metab;
		for (C_INT32  j = 0; j < noOfMetabolitesRows; j++)
		{
			metab = metabolites[j];
			table->setText(j, 0, metab->getName().c_str());
			table->setText(j, 1, QString::number(*(metab->getConcentration())));
			table->setText(j, 2, QString::number(metab->getNumber()));
			table->setText(j, 3, QString::number(metab->getStatus()));
		}
	}

}



void MetabolitesWidget::setFocus()
{
	QWidget::setFocus();
	table->setFocus();
}


void MetabolitesWidget::slotTableClicked( int row, int col, int button, const QPoint & mousePos )
{
	//QMessageBox::information( this, "Application name",
			//"Clicked (mousePress) On Metabolites table." );	
	
	if (!table->hasFocus())
	{
		table->setFocus();
	}

}

void MetabolitesWidget::slotTableSelectionChanged() 
{
	if (!table->hasFocus())
	{
		table->setFocus();
	}
}

void MetabolitesWidget::resizeEvent( QResizeEvent * re)
{
	if (isVisible())
	{
		int newWidth = re->size().width();
		
		newWidth -= 35;	//Accounting for the left (vertical) header width.
		float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0, weight3 = 3.0;
		float weightSum = weight0 + weight1 + weight2 + weight3 ;
		int w0, w1, w2, w3;
		w0 = static_cast<int> (newWidth * (weight0 / weightSum));
		w1 = static_cast<int> (newWidth * (weight1 / weightSum));
		w2 = static_cast<int> (newWidth * (weight2 / weightSum));
		w3 = static_cast<int> (newWidth - w0 - w1 - w2);
		table->setColumnWidth(0, w0);
		table->setColumnWidth(1, w1);
		table->setColumnWidth(2, w2);
		table->setColumnWidth(3, w3);
	}
		
}
