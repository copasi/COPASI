/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ConstantSymbols.cpp,v $
   $Revision: 1.36 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/11/12 14:52:23 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/ConstantSymbols.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Constant Symbols
 ********************************************************************/
#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>

#include "ConstantSymbols.h"
#include "mathmodel/CMathConstant.h"
#include "mathmodel/CMathModel.h"
#include "listviews.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"

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
ConstantSymbols::ConstantSymbols(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  mModel = NULL;
  table = new QTable(this, "tblConstantSymbols");
  table->setNumCols(4);
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Symbol");
  tableHeader->setLabel(1, "Constant");
  tableHeader->setLabel(2, "Reaction");
  tableHeader->setLabel(3, "Value");

  //btnOK = new QPushButton("&OK", this);
  //btnCancel = new QPushButton("&Cancel", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);
  hBoxLayout->addSpacing(50);
  //hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  //hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);

  table->sortColumn(2, true, true);
  table->setSorting(true);
  table->setFocusPolicy(QWidget::WheelFocus);
  //table->setProtected(true);

  // signals and slots connections
  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  //connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  //connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));

  table -> setVScrollBarMode(QScrollView::AlwaysOn);
}

bool ConstantSymbols::loadConstantSymbols(CMathModel *model)
{
  dataModel->updateMathModel();

  if (model != NULL)
    {
      mModel = model;
      //Emptying the table
      table->setNumRows(0);

      CMathConstantParameter * pConstant;
      std::map< std::string, CMathConstantParameter * > & List =
        mModel->getConstantsList();
      std::map< std::string, CMathConstantParameter * >::iterator it =
        List.begin();
      std::map< std::string, CMathConstantParameter * >::iterator end =
        List.end();

      table->setNumRows(List.size());
      int index = 0;
      for (; it != end; ++it)
        {
          pConstant = it->second;
          table->setText(index, 0, FROM_UTF8(it->first));
          table->setText(index, 1, FROM_UTF8(pConstant->getObject()->getObjectName()));
          table->setText(index, 2, FROM_UTF8(pConstant->getReaction()));
          table->setText(index, 3, QString::number(pConstant->getValue()));
          index++;
        }
      table->sortColumn(2, true, true);
    }

  return true;
}

void ConstantSymbols::slotTableSelectionChanged()
{
  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

void ConstantSymbols::slotBtnOKClicked()
{}

void ConstantSymbols::slotBtnCancelClicked()
{}

void ConstantSymbols::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      int newWidth = re->size().width();

      newWidth -= 35; //Accounting for the left (vertical) header width.
      float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0, weight3 = 3.0;
      float weightSum = weight0 + weight1 + weight2 + weight3;
      int w0, w1, w2, w3;
      w0 = newWidth * (weight0 / weightSum);
      w1 = newWidth * (weight1 / weightSum);
      w2 = newWidth * (weight2 / weightSum);
      w3 = newWidth - w0 - w1 - w2 - table->verticalScrollBar()->width();
      table->setColumnWidth(0, w0);
      table->setColumnWidth(1, w1);
      table->setColumnWidth(2, w2);
      table->setColumnWidth(3, w3);
    }
  CopasiWidget::resizeEvent(re);
}

bool ConstantSymbols::update(ListViews::ObjectType objectType,
                             ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REACTION:
    case ListViews::FUNCTION:
      loadConstantSymbols(dataModel->getMathModel());
      break;

    default:
      break;
    }

  return true;
}

bool ConstantSymbols::enter(const std::string & C_UNUSED(key))
{
  loadConstantSymbols(dataModel->getMathModel());

  return true;
}
