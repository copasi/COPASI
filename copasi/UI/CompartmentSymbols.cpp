/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CompartmentSymbols.cpp,v $
   $Revision: 1.23 $
   $Name:  $
   $Author: gasingh $ 
   $Date: 2004/01/08 22:04:36 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/CompartmentSymbols.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Compartment Symbols
 ********************************************************************/
#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>

#include "CompartmentSymbols.h"
#include "mathmodel/CMathModel.h"
#include "mathmodel/CMathConstant.h"
#include "model/CCompartment.h"
#include "listviews.h"

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
CompartmentSymbols::CompartmentSymbols(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  mModel = NULL;
  table = new MyTable(this, "tblComapartmentSymbols");
  table->setNumCols(5);
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Symbol");
  tableHeader->setLabel(1, "Compartment");
  tableHeader->setLabel(2, "Initial Volume");
  tableHeader->setLabel(3, "Volume");
  tableHeader->setLabel(4, "Metabolite Symbols");

  //btnOK = new QPushButton("&OK", this);
  //btnCancel = new QPushButton("&Cancel", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  /*hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);*/

  table->sortColumn (0, true, true);
  table->setSorting (true);
  table->setFocusPolicy(QWidget::WheelFocus);
  table->setProtected(true);

  // signals and slots connections
  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  //connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  //connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));
}

void CompartmentSymbols::loadCompartmentSymbols(CMathModel *model)
{
  dataModel->updateMathModel();

  if (model != NULL)
    {
      mModel = model;

      //Emptying the table
      int numberOfRows = table->numRows();

      for (int i = 1; i < numberOfRows; i++)
        {
          table->removeRow(0);
        }

      std::map< std::string, CMathConstantCompartment * > compartList =
        mModel->getCompartmentList();
      std::map<std::string, CMathConstantCompartment * >::iterator it;
      CMathConstantCompartment * constantCompart;

      table->setNumRows(compartList.size());
      int index = 0;
      for (it = compartList.begin(); it != compartList.end();++it)
        {
          QStringList comboEntries1, comboEntries2;
          constantCompart = it->second;
          table->setText(index, 0, it->first.c_str());

#ifdef XXXX
          const CCopasiVectorNS < CCompartment > &list1 = mModel->getModel()->getCompartments();
          for (int m = 0; m < list1.size(); m++)
            {
              const std::string &name1 = list1[m]->getName();
              comboEntries2.push_back(name1.c_str());
            }
          QComboTableItem * item1 = new QComboTableItem(table, comboEntries2, false);
          item1->setCurrentItem(constantCompart->getObject()->getName().c_str());
          table->setItem(index, 1, item1);
#endif // XXXX
          table->setText(index, 1,
                         constantCompart->getObject()->getName().c_str());
          table->setText(index, 2, QString::number(constantCompart->getValue()));

          table->setText(index, 3, QString::number(constantCompart->getTransientValue()));

          const std::vector< CMathSymbol * > &list = constantCompart->getMetaboliteList();
          for (int l = 0; l < list.size(); l++)
            {
              const std::string &name = list[l]->getName();
              comboEntries1.push_back(name.c_str());
            }
          QComboTableItem * item = new QComboTableItem(table, comboEntries1, false);
          table->setItem(index, 4, item);

          index++;
        }
    }
}

void CompartmentSymbols::slotTableSelectionChanged()
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

void CompartmentSymbols::slotBtnOKClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to commit changes");
}

void CompartmentSymbols::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to cancel changes");
}

void CompartmentSymbols::resizeEvent(QResizeEvent * re)
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
  CopasiWidget::resizeEvent(re);
}

bool CompartmentSymbols::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REACTION:
      dataModel->scheduleMathModelUpdate();
      if (isShown())
        loadCompartmentSymbols(dataModel->getMathModel());
      break;

    default:
      break;
    }
  return true;
}

bool CompartmentSymbols::enter(const std::string & C_UNUSED(key))
{
  loadCompartmentSymbols(dataModel->getMathModel());
  return true;
}
