#include <qlayout.h>
#include <qwidget.h>

#include "MetabolitesWidget.h"
#include "MyTreeAndListWidget.h"
#include "Model/CModel.h"
#include "Model/CMetab.h"

MetabolitesWidget::MetabolitesWidget(QWidget *parent, const char * name, WFlags f)
						: QWidget(parent, name, f)
{
	myParent = (MyTreeAndListWidget*) parent;
	CModel *mModel = myParent->getModel();
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

	CMetab *metab;
	for (int i = 0; i < noOfRows; i++)
	{
		metab = metabolites[i];
		table->setText(i, 0, metab->getName().c_str());
		table->setText(i, 1, QString::number(metab->getNumber()));
		table->setText(i, 2, QString::number(metab->getStatus()));
		table->setText(i, 3, QString::number(*(metab->getConcentration())));
		

	}
	
}









