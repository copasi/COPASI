/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ReactionsWidget.cpp,v $
   $Revision: 1.66 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/25 21:13:34 $
   End CVS Header */

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

  table = new MyTable(this, "tblReactions");
  table->setNumCols(2);
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Reaction");

  btnOK = new QPushButton("&OK", this);
  btnCancel = new QPushButton("&Cancel", this);
  btnDelete = new QPushButton("&Delete", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnDelete);
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
  connect(btnDelete, SIGNAL(clicked ()),
          this, SLOT(slotBtnDeleteClicked()));

  connect(table, SIGNAL(currentChanged(int, int)),
          this, SLOT(CurrentValueChanged(int, int)));

  table -> setVScrollBarMode(QScrollView::AlwaysOn);

  m_SavedRow = 0;
  m_SavedCol = 0;
  prev_row = 0;
  prev_col = 0;
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
  std::string name = "reaction_0";
  int i = 0;
  while (!dataModel->getModel()->addReaction(name))
    {
      i++;
      name = "reaction_";
      name += QString::number(i).latin1();
    }
  table->setText(table->numRows() - 1, 0, name.c_str());
  table->setNumRows(table->numRows());
  //emit updated();
  //emit leaf(mModel);
  ListViews::notify(ListViews::REACTION, ListViews::ADD);
}

void ReactionsWidget::slotTableCurrentChanged(int row,
    int C_UNUSED(col),
    int C_UNUSED(m) ,
    const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;

  if (row == table->numRows() - 1)
    {
      std::cout << "Create new Reaction" << std::endl;
      createNewObject();
    }

  pListView->switchToOtherWidget(mKeys[row]);
}

void ReactionsWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus()) table->setFocus();
}

void ReactionsWidget::CurrentValueChanged(int row, int col)
{
  //  at this point you know old values !
  prev_row = m_SavedRow;
  prev_col = m_SavedCol;

  m_SavedCol = col; // Save for a future use
  m_SavedRow = row; // Save for a future use
}

void ReactionsWidget::slotBtnOKClicked()
{
  if (dataModel->getModel())
    {
      CReaction *obj;
      CCopasiVectorN < CReaction > & objects = dataModel->getModel()->getReactions();
      C_INT32 j, jmax = objects.size();

      int *changed = new int[jmax];

      table->setCurrentCell(jmax, 0);
      for (j = 0; j < jmax; ++j)
        {
          obj = objects[j];
          changed[j] = 0;

          // this loads the reaction into a CReactionInterface object.
          // the gui works on this object and later writes back the changes to the reaction
          mRi.initFromReaction(*(dataModel->getModel()), obj->getKey());

          //first check if new metabolites need to be created
          bool createdMetabs = mRi.createMetabolites(*(dataModel->getModel()));

          //name
          QString name(table->text(j, 0));
          if (name.latin1() != mRi.getReactionName())
            {
              mRi.setReactionName(name.latin1());
              changed[j] = 1;
            }

          //equation
          QString equation(table->text(j, 1));
          if (equation.latin1() != mRi.getChemEqString())
            {
              //first check if the string is a valid equation
              if (!CChemEqInterface::isValidEq(equation.latin1()))
                {
                  std::cout << "Not a valid equation!\n\n";
                  table->setText(j, 1, mRi.getChemEqString().c_str());
                }
              else
                {
                  //tell the reaction interface
                  mRi.setChemEqString(equation.latin1());
                  changed[j] = 1;
                }
            }

          //this writes all changes to the reaction
          mRi.writeBackToReaction(*(dataModel->getModel()));

          //this tells the gui what it needs to know.
          if (createdMetabs) ListViews::notify(ListViews::METABOLITE, ListViews::ADD, "");

          // update the widget
          //table->setText(j, 0, mRi.getReactionName().c_str());
          //table->setText(j, 1, mRi.getChemEqString().c_str());
        }

      for (j = 0; j < jmax; ++j)
        {
          if (changed[j] == 1)
            {
              obj = objects[j];
              ListViews::notify(ListViews::REACTION, ListViews::CHANGE, obj->getKey());
            }
        }

      table->setCurrentCell(prev_row, prev_col);

      delete[] changed;

      return; //TODO: really check
    }
}

void ReactionsWidget::slotBtnCancelClicked()
{
  if (dataModel->getModel())
    fillTable();
}

void ReactionsWidget::slotBtnDeleteClicked()
{
  if (dataModel->getModel())
    {
      unsigned C_INT32 i, imax = table->numRows() - 1;
      std::vector< unsigned C_INT32 > ToBeDeleted;

      for (i = 0; i < imax; i++)
        {
          if (table->isRowSelected(i, true))
            ToBeDeleted.push_back(i);
        }

      if (ToBeDeleted.size() > 0)
        {
          QString reacList = "Are you sure you want to delete listed REACTION(S) ?\n";
          for (i = 0; i < ToBeDeleted.size(); i++)
            {
              reacList.append(table->text(ToBeDeleted[i], 0));
              reacList.append(", ");
            }
          reacList.remove(reacList.length() - 2, 2);

          int choice = QMessageBox::warning(this, "CONFIRM DELETE",
                                            reacList,
                                            "Continue", "Cancel", 0, 0, 1);

          switch (choice)
            {
            case 0:     // Yes or Enter
              {
                for (i = ToBeDeleted.size(); 0 < i;)
                  {
                    i--;

                    dataModel->getModel()->removeReaction(mKeys[ToBeDeleted[i]]);
                    table->removeRow(ToBeDeleted[i]);
                  }

                for (i = 0, imax = ToBeDeleted.size(); i < imax; i++)
                  ListViews::notify(ListViews::REACTION, ListViews::DELETE, mKeys[ToBeDeleted[i]]);

                break;
              }

            default:            // No or Escape
              break;
            }
        }
    }
}

void ReactionsWidget::tableValueChanged(int C_UNUSED(row),
                                        int C_UNUSED(col))
{}

bool ReactionsWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action),
                             const std::string & C_UNUSED(key))
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

bool ReactionsWidget::enter(const std::string & C_UNUSED(key))
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
          w1 = newWidth - w0 - table->verticalScrollBar()->width();
          table->setColumnWidth(0, w0);
          table->setColumnWidth(1, w1);
          binitialized = false;
        }
      /*else
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
        }*/
    }
  CopasiWidget::resizeEvent(re);
}
