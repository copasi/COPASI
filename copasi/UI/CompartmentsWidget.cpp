/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CompartmentsWidget.cpp,v $
   $Revision: 1.88 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/19 10:07:44 $
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
#include <qaction.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

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
  //here the table is initialized
  binitialized = true;
  table = new MyTable(this, "table");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  table->sortColumn (0, true, true);
  table->setSorting (true);
  table->setFocusPolicy(QWidget::WheelFocus);
  table->setColumnReadOnly(0, true);
  table->setColumnWidth(0, 20);

  //here the buttons are defined
  btnOK = new QPushButton("Commit", this);
  btnCancel = new QPushButton("Revert", this);
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
  table->setVScrollBarMode(QScrollView::AlwaysOn);

  // signals and slots connections
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)),
          this, SLOT(slotDoubleClicked(int, int, int, const QPoint &)));
  connect(table, SIGNAL(selectionChanged ()),
          this, SLOT(slotTableSelectionChanged ()));
  connect(table, SIGNAL(valueChanged(int , int)),
          this, SLOT(slotValueChanged(int, int)));
  connect(table, SIGNAL(currentChanged(int, int)),
          this, SLOT(slotCurrentChanged(int, int)));

  connect(btnOK, SIGNAL(clicked ()), this,
          SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this,
          SLOT(slotBtnCancelClicked()));
  connect(btnDelete, SIGNAL(clicked ()), this,
          SLOT(slotBtnDeleteClicked()));

  mIgnoreUpdates = false;

  m_SavedRow = 0;
  m_SavedCol = 0;
  prev_row = 0;
  prev_col = 0;

  //call the specific initializations
  init();
}

//specific
void CompartmentsWidget::init()
{
  numCols = 3;
  table->setNumCols(numCols);
  table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Volume");
}

void CompartmentsWidget::fillTable()
{
  const CCopasiVectorN < CCompartment > & objects = dataModel->getModel()->getCompartments();
  C_INT32 i, j, jmax = objects.size();

  table->QTable::setNumRows(jmax + 1);
  mKeys.resize(jmax);
  mFlagChanged.resize(jmax);
  mFlagDelete.resize(jmax);
  mFlagNew.resize(jmax);
  mFlagRenamed.resize(jmax);

  std::vector<QString> list;
  list.resize(numCols);
  for (j = 0; j < jmax; ++j)
    {
      tableLineFromObject(objects[j], list);
      for (i = 1; i < numCols; ++i)
        table->setText(j, i, list[i]);
      mKeys[j] = objects[j]->getKey();
      mFlagChanged[j] = false;
      mFlagDelete[j] = false;
      mFlagNew[j] = false;
      mFlagRenamed[j] = false;
      updateRow(j);
    }
  for (i = 0; i < numCols; ++i)
    table->setText(jmax, i, "");
  btnOK->setEnabled(false);
  btnCancel->setEnabled(false);
}

void CompartmentsWidget::saveTable()
{
  if (!dataModel->getModel())
    return;

  bool flagDelete = false;
  std::vector<std::string> delKeys;

  mIgnoreUpdates = true; //to avoid recursive calls

  C_INT32 j, jmax = table->numRows();
  for (j = 0; j < jmax; ++j)
    {
      if (mFlagNew[j])
        {
          CCopasiObject* pObj = createNewObject((const char *)table->text(j, 1).utf8());
          tableLineToObject(j, pObj);
          ListViews::notify(ListViews::COMPARTMENT, ListViews::ADD, pObj->getKey());
        }
      else if (mFlagDelete[j])
        {
          flagDelete = true;
          delKeys.push_back(mKeys[j]);
        }
      else
        {
          if (mFlagChanged[j])
            {
              tableLineToObject(j, GlobalKeys.get(mKeys[j]));
              ListViews::notify(ListViews::COMPARTMENT, ListViews::CHANGE, mKeys[j]);
            }
          if (mFlagRenamed[j])
            {
              GlobalKeys.get(mKeys[j])->setObjectName((const char *)table->text(j, 1).utf8());
              ListViews::notify(ListViews::COMPARTMENT, ListViews::RENAME, mKeys[j]);
            }
        }
    }

  if (flagDelete) deleteObjects(delKeys);

  mIgnoreUpdates = false;
}

//specific
void CompartmentsWidget::tableLineFromObject(const CCopasiObject* obj, std::vector<QString>& list)
{
  if (!obj) return;
  const CCompartment* pComp = (const CCompartment*)obj;
  list[1] = FROM_UTF8(pComp->getObjectName());
  list[2] = QString::number(pComp->getVolume());
}

void CompartmentsWidget::tableLineToObject(const C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CCompartment* pComp = (CCompartment*)obj;
  pComp->setInitialVolume(table->text(row, 2).toDouble());
}

void CompartmentsWidget::defaultTableLineContent(std::vector<QString>& list)
{
  list[2] = QString::number(1.0);
}

QString CompartmentsWidget::defaultObjectName()
{
  return "compartment";
}

//specific
/*void CompartmentsWidget::createNewObject()
{
  std::string name = "compartment_0";
  int i = 0;
  while (!dataModel->getModel()->createCompartment(name))
    {
      i++;
      name = "compartment_";
      name += (const char *)QString::number(i).utf8();
    }
  table->setText(table->numRows() - 1, 1, FROM_UTF8(name));
  table->setNumRows(table->numRows());
  ListViews::notify(ListViews::COMPARTMENT, ListViews::ADD);
}*/

//specific
CCopasiObject* CompartmentsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CCompartment* pCom;
  while (!(pCom = dataModel->getModel()->createCompartment(nname)))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }
  std::cout << " *** created Compartment: " << nname << " : " << pCom->getKey() << std::endl;
  return pCom;
}

//  ***** Slots for table signals ********

void CompartmentsWidget::slotDoubleClicked(int row, int C_UNUSED(col),
    int C_UNUSED(m), const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;

  if (row == table->numRows() - 1)
    {
      //TODO: create a new Object
      //createNewObject();
    }

  pListView->switchToOtherWidget(mKeys[row]);
}

void CompartmentsWidget::slotTableSelectionChanged()
{
  std::cout << "Table..selectionChanged " << std::endl;

  if (!table->hasFocus()) table->setFocus();
}

void CompartmentsWidget::slotCurrentChanged(int row, int col)
{
  std::cout << "Table..currentChanged " << row << "  " << col << std::endl;

  //  at this point you know old values !
  prev_row = m_SavedRow;
  prev_col = m_SavedCol;

  m_SavedCol = col; // Save for a future use
  m_SavedRow = row; // Save for a future use
}

void CompartmentsWidget::resizeTable(const unsigned C_INT32 numRows)
{
  table->QTable::setNumRows(numRows);
  mKeys.resize(numRows);
  mFlagChanged.resize(numRows);
  mFlagDelete.resize(numRows);
  mFlagNew.resize(numRows);
  mFlagRenamed.resize(numRows);
}

void CompartmentsWidget::slotValueChanged(int row, int col)
{
  std::cout << "Table..valueChanged " << row << "  " << col << std::endl;
  btnOK->setEnabled(true);
  btnCancel->setEnabled(true);

  if (row == table->numRows() - 1) //new Object
    {
      resizeTable(table->numRows() + 1);
      mFlagNew[row] = true;

      if (col == 1) //name entered
        {
          //table->setText(row, 1, createNewName(table->text(row,1)));

          std::vector<QString>tmp;
          tmp.resize(numCols);
          defaultTableLineContent(tmp);

          C_INT32 j;
          for (j = 2; j < numCols; ++j)
            table->setText(row, j, tmp[j]);
        }
      else //some value entered
        table->setText(row, 1, createNewName(defaultObjectName()));
    }
  else
    {
      if (col == 1)
        mFlagRenamed[row] = true;
      else
        mFlagChanged[row] = true;
    }
  updateRow(row);
}

void CompartmentsWidget::updateRow(const C_INT32 row)
{
  QString tmp;
  if (mFlagChanged[row]) tmp += "* ";
  if (mFlagDelete[row]) tmp += "del ";
  if (mFlagNew[row]) tmp += "new ";
  if (mFlagRenamed[row]) tmp += "ren ";

  table->setText(row, 0, tmp);
}

QString CompartmentsWidget::createNewName(const QString name)
{
  QString nname = name;
  unsigned C_INT32 j, jmax = mKeys.size();
  unsigned C_INT32 i = 1;

  for (;;++i)
    {
      for (j = 0; j < jmax; ++j)
        if (table->text(j, 1) == nname) break;
      if (j == jmax) break;
      nname = name + "_" + QString::number(i);
    }
  return nname;
}

//********* Slots for Buttons ************

void CompartmentsWidget::slotBtnOKClicked()
{
  saveTable();
  fillTable();
  //TODO save current cell
}

void CompartmentsWidget::slotBtnCancelClicked()
{
  if (dataModel->getModel())
    fillTable();
}

void CompartmentsWidget::slotBtnDeleteClicked()
{
  //TODO that is not elegant
  unsigned C_INT32 i, imax = table->numRows() - 1;
  for (i = 0; i < imax; i++)
    {
      if (table->isRowSelected(i, true))
        {
          mFlagDelete[i] = true;
          updateRow(i);
          btnOK->setEnabled(true);
          btnCancel->setEnabled(true);
        }
    }
}

//specific
void CompartmentsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dataModel->getModel())
    return;

  if (keys.size() == 0)
    return;

  QString compartmentList = "Are you sure you want to delete listed COMPARTMENT(S) ?\n";
  QString effectedMetabList = "Following METABOLITE(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above METABOLITE(S) and will be deleted -\n";
  int metabFound = 0;
  int reacFound = 0;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      compartmentList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
      compartmentList.append(", ");

      CCompartment* comp =
        dynamic_cast< CCompartment *>(GlobalKeys.get(keys[i]));

      const CCopasiVectorNS < CMetab > & Metabs = comp->getMetabolites();
      unsigned C_INT32 noOfMetabs = Metabs.size();

      if (noOfMetabs > 0)
        {
          metabFound = 1;
          unsigned C_INT32 k;
          for (k = 0; k < noOfMetabs; k++)
            {
              effectedMetabList.append(FROM_UTF8(Metabs[k]->getObjectName()));
              effectedMetabList.append(", ");
            }

          effectedMetabList.remove(effectedMetabList.length() - 2, 2);
          effectedMetabList.append("  ---> ");
          effectedMetabList.append(FROM_UTF8(comp->getObjectName()));
          effectedMetabList.append("\n");

          std::set<std::string> effectedReacKeys = dataModel->getModel()->listReactionsDependentOnCompartment(keys[i]);
          if (effectedReacKeys.size() > 0)
            {
              reacFound = 1;
              std::set<std::string>::const_iterator it, itEnd = effectedReacKeys.end();
              for (it = effectedReacKeys.begin(); it != itEnd; ++it)
                {
                  effectedReacList.append(FROM_UTF8(GlobalKeys.get(*it)->getObjectName()));
                  effectedReacList.append(", ");
                }

              effectedReacList.remove(effectedReacList.length() - 2, 2);
              effectedReacList.append("  ---> ");
              effectedReacList.append(FROM_UTF8(comp->getObjectName()));
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

  C_INT32 choice;
  if (metabFound == 1)
    choice = QMessageBox::warning(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  "Continue", "Cancel", 0, 0, 1);
  else
    choice = 0;

  switch (choice)
    {
    case 0:             // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            dataModel->getModel()->removeCompartment(keys[i]);
          }

        for (i = 0; i < imax; i++)
          ListViews::notify(ListViews::COMPARTMENT, ListViews::DELETE, keys[i]);
        //TODO notify about metabs and reactions
        break;
      }
    case 1:             // No or Escape
      break;
    }
}

bool CompartmentsWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  //this avoids recursive calls
  if (mIgnoreUpdates) return true;

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
  saveTable();
  return true;
}

bool CompartmentsWidget::enter(const std::string & C_UNUSED(key))
{
  fillTable(); //TODO perhaps not necessary?
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
