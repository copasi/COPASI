/***********************************************************************
**  $ CopasiUI/MetabolitesWidget.cpp                 
**  $ Author  : Mudita Singhal
**
** This file is used to create the GUI FrontPage for the  information
** obtained from the data model about the Metabolites----It is 
** Basically the First level of Metabolites.
************************************************************************/
#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include "MetabolitesWidget.h"
#include "Model/CMetab.h"

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
	
	 mModel=NULL;
	table = new MyTable(0, 5, this, "tblMetabolites");
	QVBoxLayout *vBoxLayout = new QVBoxLayout( this, 0 );
	vBoxLayout->addWidget(table);

	QHeader *tableHeader = table->horizontalHeader();
	tableHeader->setLabel(0, "Name");
	tableHeader->setLabel(1, "Concentration");
	tableHeader->setLabel(2, "Number");
	tableHeader->setLabel(3, "Status");
	tableHeader->setLabel(4, "Compartment");	
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
	table->setNumRows(noOfMetabolitesRows);
		
		//Now filling the table.
		CMetab *metab;
		for (C_INT32  j = 0; j < noOfMetabolitesRows; j++)
		{
			metab = metabolites[j];
			table->setText(j, 0, metab->getName().c_str());

/*double m=(*(metab->getConcentration()));
QString *m1;
//QString ms = m1.setNum( m,'g',6 );
   m1=  QString::setNum(m,'g',6);            
table->setText(j, 1,*m1);

//table->setText(j, 1,ms);*/
			table->setText(j, 1, QString::number(*(metab->getConcentration())));

			table->setText(j, 2, QString::number(metab->getNumber()));
			if(QString::number(metab->getStatus())=="0")
			{
			table->setText(j, 3, "defineda");
			}
			else if(QString::number(metab->getStatus())=="1")
			{
				table->setText(j, 3, "definedb");
			}
			else if(QString::number(metab->getStatus())=="2")
			{
				table->setText(j, 3, "definedc");
			}
			//table->setText(j, 3, QString::number(metab->getStatus()));
			table->setText(j, 4, (metab->getCompartment())->getName().c_str());
		}

		//table->sortColumn(0,true,true);
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
		float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0, weight3 = 3.0 ,weight4 = 3.0;
		float weightSum = weight0 + weight1 + weight2 + weight3 + weight4;
		int w0, w1, w2, w3 , w4;
		w0 = newWidth * (weight0 / weightSum);
		w1 = newWidth * (weight1 / weightSum);
		w2 = newWidth * (weight2 / weightSum);
		w3 = newWidth * (weight3 / weightSum);
		w4 = newWidth - w0 - w1 - w2 - w3;
		table->setColumnWidth(0, w0);
		table->setColumnWidth(1, w1);
		table->setColumnWidth(2, w2);
		table->setColumnWidth(3, w3);
		table->setColumnWidth(4, w4);
	}
		
}