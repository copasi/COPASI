/*******************************************************************
 **  $ CopasiUI/ReactionsWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data  model about the Reactions----It is 
 ** the First level of Reactions.
 ********************************************************************/

#include "ReactionsWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "model/CModel.h" 
//#include "model/CMetab.h"
//#include "model/CCompartment.h"
#include "model/CReaction.h"
#include "model/CChemEqInterface.h"
#include "listviews.h"
#include "report/CKeyFactory.h"

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
    : CopasiWidget(parent, name, f)
{
  binitialized = true;

  table = new MyTable(0, 2, this, "tblReactions");
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Reaction");

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
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)),
          this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(table, SIGNAL(selectionChanged ()),
          this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()),
          this, SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()),
          this, SLOT(slotBtnCancelClicked()));
}

void ReactionsWidget::fillTable()
{
  const CReaction *obj;
  const CCopasiVectorN < CReaction > & objects = dataModel->getModel()->getReactions();
  C_INT32 j, jmax = objects.size();
  table->setNumRows(jmax);
  mKeys.resize(jmax);

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      table->setText(j, 0, obj->getName().c_str());
      table->setText(j, 1, CChemEqInterface::getChemEqString(dataModel->getModel(), *obj, false).c_str());

      mKeys[j] = obj->getKey();
    }
  table->setText(jmax, 1, "");
}

//**************************************************************************

void ReactionsWidget::createNewObject()
{
  CReaction * reac = new CReaction("New Reaction", &dataModel->getModel()->getReactions());
  dataModel->getModel()->getReactions().add(reac);
  ListViews::notify(ListViews::MODEL, ListViews::CHANGE, "");   //TODO: more specific
}

void ReactionsWidget::slotTableCurrentChanged(int row,
    int C_UNUSED(col),
    int C_UNUSED(m) ,
    const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;

  if (row == table->numRows() - 1)
    {
      //TODO: create a new Object
      std::cout << "Create new Reaction" << std::endl;
      createNewObject();
    }

  pListView->switchToOtherWidget(mKeys[row]);
}

void ReactionsWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus()) table->setFocus();
}

void ReactionsWidget::slotBtnOKClicked()
{}

void ReactionsWidget::slotBtnCancelClicked()
{}

void ReactionsWidget::tableValueChanged(int C_UNUSED(row),
                                        int C_UNUSED(col))
{}

bool ReactionsWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::METABOLITE:
    case ListViews::COMPARTMENT:
    case ListViews::REACTION:
      fillTable();
      break;

    default:
      break;
    }
  return true;
}

bool ReactionsWidget::leave()
{
  //does nothing.
  return true;
}

bool ReactionsWidget::enter(const std::string & key)
{
  //does nothing.
  return true;
}

//*******************************************************************************************

void ReactionsWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      //      repaint_table();
      if (binitialized)
        {
          int newWidth = re->size().width();
          newWidth -= 35; //Accounting for the left (vertical) header width.
          float weight0 = 3.5, weight1 = 6.5;
          float weightSum = weight0 + weight1;
          int w0, w1;
          w0 = newWidth * (weight0 / weightSum);
          w1 = newWidth - w0;
          table->setColumnWidth(0, w0);
          table->setColumnWidth(1, w1);
          binitialized = false;
        }
      else
        {
          table->DisableColWidthUpdate();
          int newWidth = re->size().width();
          int i;

          int totalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            totalWidth += table->columnWidth(i);

          int minTotalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            minTotalWidth += table->minColWidth[i];

          //Zoom in
          if (newWidth > re->oldSize().width())
            {
              if (newWidth > totalWidth) // can do expansion
                {
                  if (totalWidth < re->oldSize().width())
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, newWidth*table->columnWidth(i) / re->oldSize().width());
                  else
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, float(newWidth)*float(table->columnWidth(i)) / float(totalWidth));
                }
              else
                for (i = 0; i < table->numCols(); i++) // Do not expand
                  table->setColumnWidth(i, table->columnWidth(i));

              table->EnableColWidthUpdate();
              return;
            }
          //Zoom out
          //calculate total Width
          if (newWidth >= totalWidth)    //will not decrease any column width
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->columnWidth(i));
              table->EnableColWidthUpdate();
              return;
            }
          //will decrease only those larger than the minimum width
          //Less than the user specified total width
          if (newWidth <= minTotalWidth)
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->minColWidth[i]);
              table->EnableColWidthUpdate();
              return;
            }
          //Bigger than the user specified total width
          for (i = 0; i < table->numCols(); i++) // Do Expansion
            table->setColumnWidth(i, (newWidth - minTotalWidth)*(table->columnWidth(i) - table->minColWidth[i]) / (totalWidth - minTotalWidth) + table->minColWidth[i]);
          table->EnableColWidthUpdate();
          return;
        }
    }
  CopasiWidget::resizeEvent(re);
}
