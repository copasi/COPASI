/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CopasiTableWidget.cpp,v $
   $Revision: 1.30 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2004/11/17 21:43:01 $
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
#include <qtable.h>

#include "model/CModel.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

CopasiTableWidget::CopasiTableWidget(QWidget *parent, bool ro, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  mRO = ro;

  //here the table is initialized
  table = new QTable(this, "table");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //table->sortColumn (0, true, true);
  table->setSorting (false);
  table->setFocusPolicy(QWidget::WheelFocus);
  table->setColumnReadOnly(0, true);

  table->verticalHeader()->setResizeEnabled(false);
  //table->setSelectionMode(QTable::MultiRow);
  //table->setVScrollBarMode(QScrollView::AlwaysOn);
  if (mRO)
    {
      table->setReadOnly(true);
      table->hideColumn(0);
    }
  resizeTable(1);
  flagtoAdjust = true;

  //here the buttons are defined
  if (!mRO)
    {
      btnOK = new QPushButton("Commit", this);
      btnCancel = new QPushButton("Revert", this);
      btnDelete = new QPushButton("Delete/Undelete", this);
      btnNew = new QPushButton("New", this);
      btnClear = new QPushButton("Clear", this);
    }

  vBoxLayout->addSpacing(5);
  mExtraLayout = new QHBoxLayout(vBoxLayout, 0);
  vBoxLayout->addSpacing(5);

  QHBoxLayout* mHLayout = new QHBoxLayout(vBoxLayout, 0);
  if (!mRO)
    {
      //mHLayout->addSpacing(32);
      //mHLayout->addSpacing(50);
      mHLayout->addWidget(btnOK);
      mHLayout->addSpacing(5);
      mHLayout->addWidget(btnCancel);
      mHLayout->addStretch();
      mHLayout->addWidget(btnClear);
      mHLayout->addSpacing(5);
      mHLayout->addWidget(btnDelete);
      mHLayout->addSpacing(5);
      mHLayout->addWidget(btnNew);
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

  // <update_comment>

  /** The connect with slotTableDelKey has been replaced by the scheme
   ** where CopasiTableWidget catches delKeyEvent itself (overriding keyPressEvent). This, along with
   ** removal of MyTable, is being done because CopasiTableWidget was the
   ** class which connected a slot to delKeyEvent */

  //connect(table, SIGNAL(delKeyPressed()), this, SLOT(slotTableDelKey()));
  //<update_comment>

  if (!mRO)
    {
      connect(btnOK, SIGNAL(clicked ()), this,
              SLOT(slotBtnOKClicked()));
      connect(btnCancel, SIGNAL(clicked ()), this,
              SLOT(slotBtnCancelClicked()));
      connect(btnDelete, SIGNAL(clicked ()), this,
              SLOT(slotBtnDeleteClicked()));
      connect(btnClear, SIGNAL(clicked ()), this,
              SLOT(slotBtnClearClicked()));
      connect(btnNew, SIGNAL(clicked ()), this,
              SLOT(slotBtnNewClicked()));
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

  //clear last line and adjust column width of the table
  for (i = 0; i < numCols; ++i)
    {
      table->clearCell(jmax, i);

      /* the logic for not adjusting in a certain cases
       * is implemented here */

      if (flagtoAdjust == true)
        {
          table->adjustColumn(i);
        }
    }

  /* The following logic ensures that width is justified on basis of
   * first feed of the equation either through manual entry or file load 
   */
  if (table->numRows() > 2)
    flagtoAdjust = false;

  mFlagRO[jmax] = false;
  mKeys[jmax] = "";
  mFlagChanged[jmax] = false;
  mFlagDelete[jmax] = false;
  mFlagNew[jmax] = false;
  mFlagRenamed[jmax] = false;
  updateRow(jmax);

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
          if (!mFlagDelete[j])
            {
              CCopasiObject* pObj = createNewObject((const char *)table->text(j, 1).utf8());
              tableLineToObject(j, pObj);
              ListViews::notify(mOT, ListViews::ADD, pObj->getKey());
            }
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

  if (mFlagNew[row])
    {
      saveTable();
      fillTable();
      return;
      //TODO: When double clicking on a new object the object should be created.
    }

  if (mFlagDelete[row])
    {
      return;
    }

  if (row == table->numRows() - 1) //new Object
    {
      flagNew = true;
      resizeTable(table->numRows() + 1);
      mFlagNew[row] = true;
      table->setText(row, 1, createNewName(defaultObjectName()));
      defaultTableLineContent(row, 0);
    }

  saveTable();

  if (flagNew)
    {
      fillTable();
      key = mKeys[table->numRows() - 2];
    }

  if (GlobalKeys.get(key))
    pListView->switchToOtherWidget(0, key);
}

void CopasiTableWidget::slotTableSelectionChanged()
{
  //std::cout << "Table..selectionChanged " << std::endl;
  if (!table->hasFocus()) table->setFocus();
}

void CopasiTableWidget::slotCurrentChanged(int row, int col)
{
  //std::cout << "Table..currentChanged " << row << "  " << col << std::endl;
}

void CopasiTableWidget::slotValueChanged(int row, int col)
{
  if (mRO) return;
  //std::cout << "Table..valueChanged " << row << "  " << col << std::endl;
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
  table->setNumRows(numRows);
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
  if (mFlagChanged[row]) tmp += "changed ";
  if (mFlagDelete[row]) tmp += "delete ";
  if (mFlagNew[row]) tmp += "new ";
  if (mFlagRenamed[row]) tmp += "renamed ";
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

void CopasiTableWidget::slotBtnClearClicked()
{
  int rowCount = table->numRows() - 1;
  for (int i = 0; i < rowCount; i++)
    {
      table->selectRow(i);
    }
  CopasiTableWidget::slotBtnDeleteClicked();
}

void CopasiTableWidget::slotBtnDeleteClicked()
{
  //std::cout << "slotBtnDeleteClicked()" << std::endl;

  bool flagFirstFound = false;
  bool flagNewDelState;

  C_INT32 i, imax = table->numRows() - 1;
  for (i = 0; i < imax; i++)
    {
      if ((table->isRowSelected(i, false)) || (i == table->currentRow()))
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

void CopasiTableWidget::slotBtnNewClicked()
{
  C_INT32 row = table->numRows() - 1;
  resizeTable(table->numRows() + 1);
  mFlagNew[row] = true;

  table->setText(row, 1, createNewName(defaultObjectName()));
  defaultTableLineContent(row, 0);

  updateRow(row);

  table->ensureCellVisible(row, 0);

  btnOK->setEnabled(true);
  btnCancel->setEnabled(true);
}

//*********** Standard Interface to Copasi Widgets ******************

bool CopasiTableWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  //this avoids recursive calls
  if (mIgnoreUpdates) return true;

  fillTable();
  return true;
}

bool CopasiTableWidget::leave()
{
  saveTable();
  return true;
}

bool CopasiTableWidget::enter(const std::string & C_UNUSED(key))
{
  fillTable();
  return true;
}

void CopasiTableWidget::keyPressEvent (QKeyEvent * e)
{
  Qt::Key k = Qt::Key_Delete;
  //Process Delete Key

  if (e->key() == k)
    {
      slotTableDelKey();
    }
}

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
void CopasiTableWidget::defaultTableLineContent(unsigned C_INT32, unsigned C_INT32)
{std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
// QString CopasiTableWidget::defaultObjectName() const
//  {std::cout << "**** method of CopasiTableWidget should never be called ****" << std::endl;}
