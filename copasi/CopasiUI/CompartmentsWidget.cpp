/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CompartmentsWidget.cpp,v $
   $Revision: 1.83 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/19 08:33:44 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/CompartmentsWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Compartments----It is Basically the First level of Compartments
 ********************************************************************/
#include "CompartmentsWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "listviews.h"
#include "report/CKeyFactory.h"

/**
 *  Constructs a Widget for the Compartments subsection of the tree.
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
CompartmentsWidget::CompartmentsWidget(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)

{
  binitialized = true;
  table = new MyTable(this, "tblCompartments");
  table->setNumCols(2);
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Volume");

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
  connect(btnOK, SIGNAL(clicked ()), this,
          SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this,
          SLOT(slotBtnCancelClicked()));
  connect(btnDelete, SIGNAL(clicked ()), this,
          SLOT(slotBtnDeleteClicked()));
  connect(table, SIGNAL(valueChanged(int , int)),
          this, SLOT(tableValueChanged(int, int)));
  connect(table, SIGNAL(currentChanged(int, int)),
          this, SLOT(CurrentValueChanged(int, int)));

  table -> setVScrollBarMode(QScrollView::AlwaysOn);

  m_SavedRow = 0;
  m_SavedCol = 0;
  prev_row = 0;
  prev_col = 0;
}

void CompartmentsWidget::fillTable()
{
  const CCompartment *obj;
  const CCopasiVectorN < CCompartment > & objects = dataModel->getModel()->getCompartments();
  C_INT32 j, jmax = objects.size();
  table->setNumRows(jmax);
  mKeys.resize(jmax);

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      table->setText(j, 0, obj->getName().c_str());
      table->setText(j, 1, QString::number(obj->getVolume()));
      mKeys[j] = obj->getKey();
    }
  table->setText(jmax, 1, "");
}

void CompartmentsWidget::createNewObject()
{
  std::string name = "compartment_0";
  int i = 0;
  while (!dataModel->getModel()->addCompartment(name))
    {
      i++;
      name = "compartment_";
      name += QString::number(i).latin1();
    }
  table->setText(table->numRows() - 1, 0, name.c_str());
  table->setNumRows(table->numRows());
  //emit updated();
  //emit leaf(mModel);
  ListViews::notify(ListViews::COMPARTMENT, ListViews::ADD);
}

void CompartmentsWidget::slotTableCurrentChanged(int row,
    int C_UNUSED(col),
    int C_UNUSED(m) ,
    const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;

  if (row == table->numRows() - 1)
    {
      //TODO: create a new Object
      createNewObject();
    }

  pListView->switchToOtherWidget(mKeys[row]);
}

void CompartmentsWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus()) table->setFocus();
}

void CompartmentsWidget::CurrentValueChanged(int row, int col)
{
  //  at this point you know old values !
  prev_row = m_SavedRow;
  prev_col = m_SavedCol;

  m_SavedCol = col; // Save for a future use
  m_SavedRow = row; // Save for a future use
}

void CompartmentsWidget::slotBtnOKClicked()
{
  if (dataModel->getModel())
    {
      CCompartment *obj;
      CCopasiVectorN < CCompartment > & objects = dataModel->getModel()->getCompartments();
      C_INT32 j, jmax = objects.size();

      int *changed = new int[jmax];

      table->setCurrentCell(jmax, 0);
      for (j = 0; j < jmax; ++j)
        {
          obj = objects[j];
          changed[j] = 0;

          //name
          QString name(table->text(j, 0));
          if (name.latin1() != obj->getName())
            {
              obj->setName(name.latin1());
              changed[j] = 1;
            }

          //volume
          QString volumeSave = QString::number(obj->getVolume());
          QString volume(table->text(j, 1));
          if (volume != volumeSave)
            {
              double m1;
              m1 = volume.toDouble();
              obj->setInitialVolume(m1);
              changed[j] = 1;
            }
        }

      for (j = 0; j < jmax; ++j)
        {
          if (changed[j] == 1)
            {
              obj = objects[j];
              ListViews::notify(ListViews::COMPARTMENT, ListViews::CHANGE, obj->getKey());
            }
        }
      table->setCurrentCell(prev_row, prev_col);

      delete[] changed;
      return; //TODO: really check
    }
}

void CompartmentsWidget::slotBtnCancelClicked()
{
  if (dataModel->getModel())
    fillTable();
}

void CompartmentsWidget::slotBtnDeleteClicked()
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

      imax = ToBeDeleted.size();
      if (imax > 0)
        {
          QString compartmentList = "Are you sure you want to delete listed COMPARTMENT(S) ?\n";
          QString effectedMetabList = "Following METABOLITE(S) reference above COMPARTMENT(S) and will be deleted -\n";
          QString effectedReacList = "Following REACTION(S) reference above METABOLITE(S) and will be deleted -\n";
          int metabFound = 0;
          int reacFound = 0;

          for (i = 0; i < imax; i++)
            {
              compartmentList.append(table->text(ToBeDeleted[i], 0));
              compartmentList.append(", ");

              CCompartment* comp =
                dynamic_cast< CCompartment *>(GlobalKeys.get(mKeys[ToBeDeleted[i]]));

              const CCopasiVectorNS < CMetab > & Metabs = comp->getMetabolites();
              unsigned C_INT32 noOfMetabs = Metabs.size();

              if (noOfMetabs > 0)
                {
                  metabFound = 1;
                  unsigned C_INT32 k;
                  for (k = 0; k < noOfMetabs; k++)
                    {
                      effectedMetabList.append(Metabs[k]->getName().c_str());
                      effectedMetabList.append(", ");
                    }

                  effectedMetabList.remove(effectedMetabList.length() - 2, 2);
                  effectedMetabList.append("  ---> ");
                  effectedMetabList.append(table->text(ToBeDeleted[i], 0));
                  effectedMetabList.append("\n");

                  std::vector<std::string> effectedReacKeys = dataModel->getModel()->removeCompReacKeys(mKeys[ToBeDeleted[i]]);
                  if (effectedReacKeys.size() > 0)
                    {
                      reacFound = 1;
                      unsigned C_INT32 k;
                      for (k = 0; k < effectedReacKeys.size(); k++)
                        {
                          CReaction* reac =
                            dynamic_cast< CReaction *>(GlobalKeys.get(effectedReacKeys[k]));
                          effectedReacList.append(reac->getName().c_str());
                          effectedReacList.append(", ");
                        }

                      effectedReacList.remove(effectedReacList.length() - 2, 2);
                      effectedReacList.append("  ---> ");
                      effectedReacList.append(table->text(ToBeDeleted[i], 0));
                      effectedReacList.append("\n");
                    }
                }
            }

          compartmentList.remove(compartmentList.length() - 2, 2);

          QString msg = compartmentList;
          if (metabFound == 1)
            {
              msg.append("\n \n");
              msg.append(effectedMetabList);
              if (reacFound == 1)
                {
                  msg.append("\n \n");
                  msg.append(effectedReacList);
                }
            }

          int choice = QMessageBox::warning(this,
                                            "CONFIRM DELETE",
                                            msg,
                                            "Continue", "Cancel", 0, 0, 1);

          switch (choice)
            {
            case 0:        // Yes or Enter
              {
                for (i = 0; i < imax; i++)
                  {
                    table->removeRow(ToBeDeleted[i]);
                    dataModel->getModel()->removeCompartment(mKeys[ToBeDeleted[i]]);
                  }

                for (i = 0; i < imax; i++)
                  ListViews::notify(ListViews::COMPARTMENT, ListViews::DELETE, mKeys[ToBeDeleted[i]]);

                break;
              }
            case 1:        // No or Escape
              break;
            }
        }
    }
}

void CompartmentsWidget::tableValueChanged(int C_UNUSED(row),
    int C_UNUSED(col))
{}

bool CompartmentsWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::METABOLITE:
    case ListViews::COMPARTMENT:
      fillTable();
      break;

    default:
      break;
    }
  return true;
}

bool CompartmentsWidget::leave()
{
  //does nothing.
  return true;
}

bool CompartmentsWidget::enter(const std::string & C_UNUSED(key))
{
  //does nothing.
  //fillTable();
  return true;
}

void CompartmentsWidget::resizeEvent(QResizeEvent * re)
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
          w0 = (int)(newWidth * (weight0 / weightSum));
          w1 = newWidth - w0 - table->verticalScrollBar()->width();
          table->setColumnWidth(0, w0);
          table->setColumnWidth(1, w1);
          binitialized = false;
        }
      /* else
         {
           table->DisableColWidthUpdate();
           int newWidth = re->size().width() - 35;
           int i;

           int totalWidth = 0;
           for (i = 0; i < table->numCols(); i++)
             totalWidth += table->columnWidth(i);

           int minTotalWidth = 0;
           for (i = 0; i < table->numCols(); i++)
             minTotalWidth += table->minColWidth[i];

           //Zoom in
           if (newWidth > (re->oldSize().width() - 35))
             {
               if (newWidth > totalWidth) // can do expansion
                 {
                   if (totalWidth < (re->oldSize().width() - 35))
                     for (i = 0; i < table->numCols(); i++) // Do expansion
                       table->setColumnWidth(i, newWidth*table->columnWidth(i) / (re->oldSize().width() - 35));
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
