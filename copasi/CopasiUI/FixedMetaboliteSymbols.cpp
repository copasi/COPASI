#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include "FixedMetaboliteSymbols.h"
#include "listviews.h"
#include "mathmodel/CMathModel.h"
#include "mathmodel/CMathConstant.h"
#include <qfont.h>

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
FixedMetaboliteSymbols::FixedMetaboliteSymbols(QWidget *parent, const char * name, WFlags f)
    : QWidget(parent, name, f)
{
  mModel = NULL;
  table = new MyTable(0, 5, this, "tblFixedMetaboliteSymbols");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Symbol");
  tableHeader->setLabel(1, "Fixed Metabolite");
  tableHeader->setLabel(2, "Concentration");
  tableHeader->setLabel(3, "Particle No.");
  tableHeader->setLabel(4, "Compartment");

  btnOK = new QPushButton("&OK", this);
  btnCancel = new QPushButton("&Cancel", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);

  table->sortColumn (0, true, true);
  table->setSorting (true);
  table->setFocusPolicy(QWidget::WheelFocus);

  // signals and slots connections
  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));
}

void FixedMetaboliteSymbols::loadFixedMetaboliteSymbols(CModel *model)
{
  if (model != NULL)
    {
      int i;
      mModel = model;
      //Emptying the table
      int numberOfRows = table->numRows();
      for (i = 0; i < numberOfRows; i++)
        {
          table->removeRow(0);
        }

      /* CMathModel *mathmodel=new CMathModel();
      mathmodel->setModel(mModel);
       const CModel *nModel=mathmodel->getModel();*/

      //unsigned C_INT32 k= mModel->getIntMetab();
      CCopasiVectorN< CMetab > metabolite(mModel->getMetabolitesX());
      C_INT32 noOfMetaboliteRows = metabolite.size();
      table->setNumRows(noOfMetaboliteRows);
      CMetab *metab;

      for (i = 0; i < noOfMetaboliteRows; i++)
        {
          //CMathConstantMetab *metablist=new CMathConstantMetab(metabolite);
          //metablist = mathmodel->getFixedMetabList();
          //C_INT32 noOfMetabElements = metablist->size();

          metab = metabolite[i];
          table->setText(i, 0, metab->getName().c_str());
          //table->setText(i, 1, QString::number(metab->getObject()->getName()));
          //table->setText(i, 2, QString::number(metab->getConcentration()));
          //table->setText(i, 3, QString::number(metab->getParticleNumber()));
          //table->setText(i, 4, QString::number(metab->getCompartment->getName()));

          /*double m=(*(metab->getConcentration()));
          QString *m1;
          //QString ms = m1.setNum(m,'g',6);
             m1=  QString::setNum(m,'g',6);            
          table->setText(j, 1,*m1);
           
          //table->setText(j, 1,ms); */
          /*table->setText(j, 1, QString::number(metab->getConcentration()));

          table->setText(j, 2, QString::number(metab->getNumberDbl()));

          table->setText(j, 3, CMetab::StatusName[metab->getStatus()].c_str());

          #ifdef XXXX
          if (QString::number(metab->getStatus()) == "0")
            {
              table->setText(j, 3, "defineda");
            }
          else if (QString::number(metab->getStatus()) == "1")
            {
              table->setText(j, 3, "definedb");
            }
          else if (QString::number(metab->getStatus()) == "2")
            {
              table->setText(j, 3, "definedc");
            }
          #endif // XXXX
          table->setText(j, 4, metab->getCompartment()->getName().c_str());
          }

          //table->sortColumn(0,true,true);*/
        }
    }
}

void FixedMetaboliteSymbols::slotTableSelectionChanged()
{
  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

/***********ListViews::showMessage(QString caption,QString text)------------------------>
 **
 ** Parameters:- 1. QString :- The Title that needs to be displayed in message box
 **              2. QString :_ The Text that needs to be displayed in the message box
 ** Returns  :-  void(Nothing)
 ** Description:- This method is used to show the message box on the screen
 ****************************************************************************************/

void FixedMetaboliteSymbols::slotBtnOKClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to commit changes");
}

void FixedMetaboliteSymbols::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to cancel changes");
}

void FixedMetaboliteSymbols::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      int newWidth = re->size().width();

      newWidth -= 35; //Accounting for the left (vertical) header width.
      float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0, weight3 = 3.0 , weight4 = 3.0;
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
