/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiTableWidget.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/27 11:40:36 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/CopasiTableWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Compartments----It is Basically the First level of Compartments
 ********************************************************************/
#include "CopasiTableWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

CopasiTableWidget::CopasiTableWidget(QWidget *parent, bool ro, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  mRO = ro;

  //here the table is initialized
  table = new MyTable(this, "table");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //table->sortColumn (0, true, true);
  table->setSorting (false);
  table->setFocusPolicy(QWidget::WheelFocus);
  table->setColumnReadOnly(0, true);
  table->setColumnWidth(0, 20);
  table->verticalHeader()->setResizeEnabled(false);
  //table->setSelectionMode(QTable::MultiRow);
  //table->setVScrollBarMode(QScrollView::AlwaysOn);
  if (mRO)
    table->setReadOnly(true);
  resizeTable(1);

  //here the buttons are defined
  if (!mRO)
    {
      btnOK = new QPushButton("Commit", this);
      btnCancel = new QPushButton("Revert", this);
      btnDelete = new QPushButton("Delete/Undelete", this);
    }

  mHLayout = new QHBoxLayout(vBoxLayout, 0);
  if (!mRO)
    {
      mHLayout->addSpacing(32);
      mHLayout->addSpacing(50);
      mHLayout->addWidget(btnOK);
      mHLayout->addSpacing(5);
      mHLayout->addWidget(btnCancel);
      mHLayout->addSpacing(30);
      mHLayout->addWidget(btnDelete);
      mHLayout->addSpacing(50);
    }

  // signals and slots connections
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)),
          this, SLOT(slotDoubleClicked(int, int, int, const QPoint &)));
  //connect(table, SIGNAL(selectionChanged ()),
  //        this, SLOT(slotTableSelectionChanged ()));
  connect(table, SIGNAL(valueChanged(int , int)),
          this, SLOT(slotValueChanged(int, int)));
  //connect(table, SIGNAL(currentChanged(int, int)),
  //        this, SLOT(slotCurrentChanged(int, int)));
  connect(table, SIGNAL(delKeyPressed()), this, SLOT(slotTableDelKey()));

  if (!mRO)
    {
      connect(btnOK, SIGNAL(clicked ()), this,
              SLOT(slotBtnOKClicked()));
      connect(btnCancel, SIGNAL(clicked ()), this,
              SLOT(slotBtnCancelClicked()));
      connect(btnDelete, SIGNAL(clicked ()), this,
              SLOT(slotBtnDeleteClicked()));
    }
  mIgnoreUpdates = false;

  //call the specific initializations
  //this->init(); //this has to be done by the constructor of the derived classes
}

void CopasiTableWidget::fillTable()
{
  std::vector<const CCopasiObject*> objects = getObjects();

  //  const CCopasiVectorN < CCompartment > & objects = dataModel->getModel()->getCompartments();
  C_INT32 i, j, jmax = objects.size();

  resizeTable(jmax + 1);

  for (j = 0; j < jmax; ++j)
    {
      mFlagRO[j] = false;
      tableLineFromObject(objects[j], j);
      mKeys[j] = objects[j]->getKey();
      mFlagChanged[j] = false;
      mFlagDelete[j] = false;
      mFlagNew[j] = false;
      mFlagRenamed[j] = false;
      updateRow(j);
    }
  for (i = 0; i < numCols; ++i)
    table->clearCell(jmax, i);

  if (!mRO)
    {
      btnOK->setEnabled(false);
      btnCancel->setEnabled(false);
    }
}

void CopasiTableWidget::saveTable()
{
  if (mRO) return;

  if (!dataModel->getModel())
    return;

  bool flagDelete = false;
  std::vector<std::string> delKeys;

  mIgnoreUpdates = true; //to avoid recursive calls

  C_INT32 j, jmax = table->numRows() - 1;
  for (j = 0; j < jmax; ++j)
    {
      if (mFlagNew[j])
        {
          CCopasiObject* pObj = createNewObject((const char *)table->text(j, 1).utf8());
          tableLineToObject(j, pObj);
          ListViews::notify(mOT, ListViews::ADD, pObj->getKey());
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
              ListViews::notify(mOT, ListViews::CHANGE, mKeys[j]);
            }
          if (mFlagRenamed[j])
            {
              GlobalKeys.get(mKeys[j])->setObjectName((const char *)table->text(j, 1).utf8());
              ListViews::notify(mOT, ListViews::RENAME, mKeys[j]);
            }
        }
    }

  if (flagDelete) deleteObjects(delKeys);

  mIgnoreUpdates = false;
}

//  ***** Slots for table signals ********

void CopasiTableWidget::slotDoubleClicked(int row, int C_UNUSED(col),
    int C_UNUSED(m), const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;
  if (mRO && (row == table->numRows() - 1)) return;

  std::string key = mKeys[row];
  bool flagNew = false;

  if (row == table->numRows() - 1) //new Object
    {
      flagNew = true;
      resizeTable(table->numRows() + 1);
      mFlagNew[row] = true;
      table->setText(row, 1, createNewName(defaultObjectName()));
      defaultTableLineContent(row, 0);
    }

  saveTable(); //TODO: should we warn the user here? Propably not.

  if (flagNew)
    {
      fillTable();
      key = mKeys[table->numRows() - 2];
    }

  if (GlobalKeys.get(key))
    pListView->switchToOtherWidget(key);
}

void CopasiTableWidget::slotTableSelectionChanged()
{
  std::cout << "Table..selectionChanged " << std::endl;
  if (!table->hasFocus()) table->setFocus();
}

void CopasiTableWidget::slotCurrentChanged(int row, int col)
{
  std::cout << "Table..currentChanged " << row << "  " << col << std::endl;
}

void CopasiTableWidget::slotValueChanged(int row, int col)
{
  if (mRO) return;
  std::cout << "Table..valueChanged " << row << "  " << col << std::endl;
  btnOK->setEnabled(true);
  btnCancel->setEnabled(true);

  if (row == table->numRows() - 1) //new Object
    {
      resizeTable(table->numRows() + 1);
      mFlagNew[row] = true;

      if (col == 1) //name entered
        {
          defaultTableLineContent(row, 0);
        }
      else //some value entered
        {
          table->setText(row, 1, createNewName(defaultObjectName()));
          defaultTableLineContent(row, col);
        }
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

void CopasiTableWidget::slotTableDelKey()
{
  //std::cout << "**del**" << std::endl;
  //pressing del does exactly the same thing as hitting the delete button
  if (!mRO)
    slotBtnDeleteClicked();
}

void CopasiTableWidget::resizeTable(const unsigned C_INT32 numRows)
{
  table->QTable::setNumRows(numRows);
  mKeys.resize(numRows);
  mFlagChanged.resize(numRows);
  mFlagDelete.resize(numRows);
  mFlagNew.resize(numRows);
  mFlagRenamed.resize(numRows);
  mFlagRO.resize(numRows);
}

void CopasiTableWidget::updateRow(const C_INT32 row)
{
  QString tmp;
  if (mFlagChanged[row]) tmp += "* ";
  if (mFlagDelete[row]) tmp += "del ";
  if (mFlagNew[row]) tmp += "new ";
  if (mFlagRenamed[row]) tmp += "ren ";
  if (mFlagRO[row]) tmp += "ro ";

  table->setText(row, 0, tmp);

  if (mFlagDelete[row])
    table->setRowReadOnly(row, true);
  else
    table->setRowReadOnly(row, mFlagRO[row]);
}

QString CopasiTableWidget::createNewName(const QString name)
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

void CopasiTableWidget::slotBtnOKClicked()
{
  saveTable();
  fillTable();
  //TODO save current cell
}

void CopasiTableWidget::slotBtnCancelClicked()
{
  if (dataModel->getModel())
    fillTable();
}

void CopasiTableWidget::slotBtnDeleteClicked()
{
  bool flagFirstFound = false;
  bool flagNewDelState;

  unsigned C_INT32 i, imax = table->numRows() - 1;
  for (i = 0; i < imax; i++)
    {
      if (table->isRowSelected(i, false))
        {
          if (!flagFirstFound)
            {
              flagFirstFound = true;
              flagNewDelState = !mFlagDelete[i];
            }

          mFlagDelete[i] = flagNewDelState;
          if (mFlagRO[i]) mFlagDelete[i] = false;
          updateRow(i);
        }
    }
  if (flagFirstFound)
    {
      btnOK->setEnabled(true);
      btnCancel->setEnabled(true);
    }
}

//*********** Standard Interface to Copasi Widgets ******************

bool CopasiTableWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
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

bool CopasiTableWidget::leave()
{
  saveTable();
  return true;
}

bool CopasiTableWidget::enter(const std::string & C_UNUSED(key))
{
  fillTable(); //TODO perhaps not necessary?
  return true;
}

/*void CopasiTableWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      //      repaint_table();
      if (true)
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
    }
  CopasiWidget::resizeEvent(re);
}*/

void CopasiTableWidget::init()
{std::cout << "**** init: method of CopasiTableWidget should never be called ****" << std::endl;}
// std::vector<const CCopasiObject*> CopasiTableWidget::getObjects() const
//  {std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
void CopasiTableWidget::tableLineFromObject(const CCopasiObject* , unsigned C_INT32)
{std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
void CopasiTableWidget::tableLineToObject(unsigned C_INT32, CCopasiObject*)
{std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
// CCopasiObject* CopasiTableWidget::createNewObject(const std::string &)
//  {std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
void CopasiTableWidget::deleteObjects(const std::vector<std::string> &)
{std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
void CopasiTableWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
// QString CopasiTableWidget::defaultObjectName() const
//  {std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
