#include <qlayout.h>
#include <qwidget.h>


#include "Model/CMetab.h"

#include "MetabolitesWidget.h"
#include "MyTreeAndListWidget.h"

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
MetabolitesWidget::MetabolitesWidget(CModel *model, QWidget *parent, const char * name, WFlags f)
						: QWidget(parent, name, f)
{
	
	this->mModel = model;
	vector < CMetab * > metabolites = mModel->getMetabolites();
	C_INT32 noOfRows = metabolites.size();
		
	table = new QTable(noOfRows, 4, this);
	QVBoxLayout *vBoxLayout = new QVBoxLayout( this, 0 );
	vBoxLayout->addWidget(table);

	QHeader *tableHeader = table->horizontalHeader();
	tableHeader->setLabel(0, "Name");
	tableHeader->setLabel(1, "Number");
	tableHeader->setLabel(2, "Status");
	tableHeader->setLabel(3, "Concentration");


	//Setting Column Widths
	table->setColumnWidth ( 0, 100 );
	table->setColumnWidth ( 1, 75 ); 
	table->setColumnWidth ( 2, 75 );
	table->setColumnWidth ( 3, 75 );

	CMetab *metab;
	for (int i = 0; i < noOfRows; i++)
	{
		metab = metabolites[i];
		table->setText(i, 0, metab->getName().c_str());
		table->setText(i, 1, QString::number(metab->getNumber()));
		table->setText(i, 2, QString::number(metab->getStatus()));
		table->setText(i, 3, QString::number(*(metab->getConcentration())));
	}
	table->sortColumn (0, TRUE, TRUE);
	
}

