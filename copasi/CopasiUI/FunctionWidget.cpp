/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/FunctionWidget.cpp,v $
   $Revision: 1.44 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/25 19:00:00 $
   End CVS Header */

/***********************************************************************
 **  $ CopasiUI/FunctionWidget.cpp                 
 **  $ Author  : Mrinmayee Kulkarni
 **
 ** This file creates the GUI which displays information obtained 
 ** from the function database. The name and type of functions are  
 ** displayes in tablular form. This is the first level widget for functions
 ************************************************************************/
#include "FunctionWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "listviews.h"
#include "report/CKeyFactory.h"

/**
 *  Constructs a Widget for the Functions subsection of the tree for 
 *  displaying the functions.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param parent The widget which this widget is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Refer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */

FunctionWidget::FunctionWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  binitialized = true;

  table = new MyTable(this, "tblFunctions");
  table->setNumCols(2);
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

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

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Type");
  table->setFocusPolicy(QWidget::WheelFocus);
  table->setColumnReadOnly(1, TRUE);

  // signals and slots connections
  // signals and slots connections
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)),
          this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(table, SIGNAL(selectionChanged ()),
          this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()), this,
          SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this,
          SLOT(slotBtnCancelClicked()));
  connect(btnDelete, SIGNAL(clicked ()), this,
          SLOT(slotBtnDeleteClicked()));
  connect(table, SIGNAL(currentChanged(int, int)),
          this, SLOT(CurrentValueChanged(int, int)));
}

void FunctionWidget::fillTable()
{
  const CFunction *obj;
  const CCopasiVectorN < CFunction > & objects = Copasi->pFunctionDB->loadedFunctions();
  C_INT32 j, jmax = objects.size();
  table->setNumRows(jmax);
  mKeys.resize(jmax);

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      table->setText(j, 0, obj->getName().c_str());

      QString ftype;
      switch (obj->getType())
        {
        case 1:
        case 2:
          ftype = QString("pre-defined");
          break;
        case 3:
          ftype = QString("user-defined");
          break;
        }
      table->setText(j, 1, ftype);

      mKeys[j] = obj->getKey();
    }
  table->setText(jmax, 1, "");
}

//**************************************************************************

void FunctionWidget::CurrentValueChanged(int row, int col) //By G
{
  //Save old values !
  prev_row = m_SavedRow;
  prev_col = m_SavedCol;

  //Save for a future use
  m_SavedCol = col;
  m_SavedRow = row;
}

void FunctionWidget::slotBtnOKClicked() //By G
{
  CFunction *obj;
  CCopasiVectorN < CFunction > & objects = Copasi->pFunctionDB->loadedFunctions();
  C_INT32 j, jmax = objects.size();

  int *renamed = new int[jmax];

  table->setCurrentCell(jmax, 0);
  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      renamed[j] = 0;

      //Allow change in name if type is 'user-defined'.
      QString name(table->text(j, 0));
      if (name.latin1() != obj->getName())
        {
          QString type(table->text(j, 1));
          if (type == "user-defined")
            {
              obj->setName(name.latin1());
              renamed[j] = 1;
            }
          else
            table->setText(j, 0, obj->getName().c_str());
        }
    }

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];

      if (renamed[j] == 1)
        ListViews::notify(ListViews::FUNCTION, ListViews::RENAME, obj->getKey());
    }
  table->setCurrentCell(prev_row, prev_col);

  delete[] renamed;
  return; //TODO: really check
}

void FunctionWidget::slotBtnCancelClicked()
{
  fillTable();
}

void FunctionWidget::slotBtnDeleteClicked()
{
  unsigned C_INT32 i, imax = table->numRows() - 1;
  std::vector< unsigned C_INT32 > ToBeDeleted;

  for (i = 0; i < imax; i++)
    if (table->isRowSelected(i, true))
      {
        if (table->text(i, 1) == "user-defined")
          ToBeDeleted.push_back(i);
      }

  imax = ToBeDeleted.size();
  if (imax > 0)
    {
      const CCopasiVectorN < CReaction > * pReactions = NULL;
      unsigned C_INT32 k, kmax = 0;

      if (Copasi->pModel)
        {
          pReactions = &Copasi->pModel->getReactions();
          kmax = pReactions->size();
        }

      QString msg1 = "Cannot delete Function(s). ";
      msg1.append("Following dependencies with listed Reaction(s) exist:\n");
      QString msg2 = "Are you sure to delete listed Functions?\n";
      int msg1Empty = 1;
      int msg2Empty = 1;
      int *reacFound = new int[imax];

      for (i = 0; i < imax; i++)
        {
          reacFound[i] = 0;

          /* Check if Reactions are dependent on Functions to be deleted */
          if (kmax > 0)
            {
              const CFunction* func =
                dynamic_cast< CFunction * >(CKeyFactory::get(mKeys[ToBeDeleted[i]]));

              for (k = 0; k < kmax; k++)
                {
                  const CFunction *reacFunc = &((*pReactions)[k]->getFunction());
                  if (func == reacFunc)
                    {
                      reacFound[i] = 1;
                      msg1.append((*pReactions)[k]->getName().c_str());
                      msg1.append(" ---> ");
                      msg1.append(table->text(ToBeDeleted[i], 0));
                      msg1.append("\n");
                      msg1Empty = 0;
                      break;
                    }
                }
            }

          /* Make a list of Functions on which no Reaction is dependent */
          if (reacFound[i] == 0)
            {
              msg2.append(table->text(ToBeDeleted[i], 0));
              msg2.append("\n");
              msg2Empty = 0;
            }
        }

      if (msg1Empty == 0)
        {
          QMessageBox::warning(this, "Sorry, Cannot Delete",
                               msg1,
                               "OK", 0, 0, 0, 1);
        }

      if (msg2Empty == 0)
        {
          int choice = QMessageBox::warning(this,
                                            "CONFIRM DELETE",
                                            msg2,
                                            "Continue", "Cancel", 0, 0, 1);

          /* Check if user chooses to deleted Functions */
          switch (choice)
            {
            case 0:   // Yes or Enter
              {
                /* Delete the Functions on which no Reactions are dependent */
                for (i = 0; i < imax; i++)
                  {
                    if (reacFound[i] == 0)
                      {
                        Copasi->pFunctionDB->removeFunction(mKeys[ToBeDeleted[i]]);
                        table->removeRow(ToBeDeleted[i]);
                      }
                  }

                /* Send notifications for Functions which have been deleted */
                for (i = 0; i < imax; i++)
                  {
                    if (reacFound[i] == 0)
                      ListViews::notify(ListViews::FUNCTION, ListViews::DELETE, mKeys[ToBeDeleted[i]]);
                  }
                break;
              }
            case 1:   // No or Escape
              break;
            }
        }

      delete[] reacFound;
    }
}

void FunctionWidget::createNewObject()
{
  std::string name = "function_0";
  int i = 0;
  while (!Copasi->pFunctionDB->addFunction(name, CFunction::UserDefined))
    //while (!Copasi->pFunctionDB->addFunction(name))
    {
      i++;
      name = "function_";
      name += QString::number(i).latin1();
    }
  table->setText(table->numRows() - 1, 0, name.c_str());
  table->setNumRows(table->numRows());
  //emit updated();
  //emit leaf(mModel);
  ListViews::notify(ListViews::FUNCTION, ListViews::ADD);
}

void FunctionWidget::slotTableCurrentChanged(int row,
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

void FunctionWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus()) table->setFocus();
}

void FunctionWidget::tableValueChanged(int C_UNUSED(row),
                                       int C_UNUSED(col))
{}

bool FunctionWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::FUNCTION:
    case ListViews::MODEL:
      fillTable();
      break;

    default:
      break;
    }
  return true;
}

bool FunctionWidget::leave()
{
  //does nothing.
  return true;
}

bool FunctionWidget::enter(const std::string & key)
{
  //does nothing.
  return true;
}

//*******************************************************************************************

void FunctionWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      //      repaint_table();
      if (binitialized)
        {
          int newWidth = re->size().width();
          newWidth -= 35; //Accounting for the left (vertical) header width.
          float weight0 = 4, weight1 = 5;
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
