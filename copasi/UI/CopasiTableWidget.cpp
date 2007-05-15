// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CopasiTableWidget.cpp,v $
//   $Revision: 1.48 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/05/15 12:36:53 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CopasiTableWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qtable.h>

#include "listviews.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"

CopasiTableWidget::CopasiTableWidget(QWidget *parent, bool ro, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  mRO = ro;

  //here the table is initialized
  table = new QTable(this, "table");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 6);
  vBoxLayout->addWidget(table);

  //table->sortColumn (0, true, true);
  table->setSorting (false);
  table->setFocusPolicy(QWidget::WheelFocus);
  table->setColumnReadOnly(0, true);

  //table->verticalHeader()->setResizeEnabled(false);
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

  //vBoxLayout->addSpacing(5);
  mExtraLayout = new QHBoxLayout(vBoxLayout, 0);
  //vBoxLayout->addSpacing(5);

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

void CopasiTableWidget::handleSBMLId(const CCopasiObject* obj, unsigned C_INT32 row)
{
  QString tmp("");
  bool flag = false;

  const CModelEntity * pEntity = dynamic_cast<const CModelEntity *>(obj);
  if (pEntity)
    {
      tmp = FROM_UTF8(pEntity->getSBMLId());
      flag = true;
    }

  const CFunction * pFunction = dynamic_cast<const CFunction *>(obj);
  if (pFunction)
    {
      tmp = FROM_UTF8(pFunction->getSBMLId());
      flag = true;
    }

  const CReaction * pReaction = dynamic_cast<const CReaction *>(obj);
  if (pReaction)
    {
      tmp = FROM_UTF8(pReaction->getSBMLId());
      flag = true;
    }

  //only set the text if the object has an sbml id
  if (flag) table->setText(row, numCols - 1, tmp);
}

void CopasiTableWidget::fillTable()
{
  std::vector<const CCopasiObject*> objects = getObjects();

  //  const CCopasiVectorN < CCompartment > & objects = CCopasiDataModel::Global->getModel()->getCompartments();
  C_INT32 i, j, jmax = objects.size();

  resizeTable(jmax + 1);

  for (j = 0; j < jmax; ++j)
    {
      mFlagRO[j] = false;
      tableLineFromObject(objects[j], j);
      //handleSBMLId(objects[j], j);
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

  if (!CCopasiDataModel::Global->getModel())
    return;

  mChanged = false;
  bool flagDelete = false;
  std::vector<std::string> delKeys;

  //mIgnoreUpdates = true; //to avoid recursive calls

  C_INT32 j, jmax = table->numRows() - 1;
  for (j = 0; j < jmax; ++j)
    {
      if (mFlagNew[j])
        {
          if (!mFlagDelete[j])
            {
              CCopasiObject* pObj = createNewObject((const char *)table->text(j, 1).utf8());
              if (pObj->getObjectName() != (const char *)table->text(j, 1).utf8())
                {
                  QString msg;
                  msg = "Unable to create object '" + table->text(j, 1)
                        + "' since an object with that name already exists.\n"
                        + "New object renamed to '"
                        + FROM_UTF8(pObj->getObjectName()) + "'.";

                  CQMessageBox::information(this,
                                            "Unable to create",
                                            msg,
                                            QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
                }
              tableLineToObject(j, pObj);
              // ListViews::notify(mOT, ListViews::ADD, pObj->getKey());
              protectedNotify(mOT, ListViews::ADD, pObj->getKey());
              mChanged = true;
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
              protectedNotify(mOT, ListViews::CHANGE, mKeys[j]);
              mChanged = true;
            }
          if (mFlagRenamed[j])
            {
              if (!GlobalKeys.get(mKeys[j])->setObjectName((const char *)table->text(j, 1).utf8()))
                {
                  QString msg;
                  msg = "Unable to rename object '" + FROM_UTF8(GlobalKeys.get(mKeys[j])->getObjectName()) + "'\n"
                        + "to '" + table->text(j, 1)
                        + "' since an object with that name already exists.";

                  CQMessageBox::information(this,
                                            "Unable to rename",
                                            msg,
                                            QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
                  table->setCurrentCell(j, 1);
                }
              else
                {
                  protectedNotify(mOT, ListViews::RENAME, mKeys[j]);
                  mChanged = true;
                }
            }
        }
    }

  if (flagDelete) deleteObjects(delKeys);

  if (mChanged) CCopasiDataModel::Global->changed();

  //mIgnoreUpdates = false;

  return;
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
  fillTable();

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

void CopasiTableWidget::slotCurrentChanged(int C_UNUSED(row), int C_UNUSED(col))
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
      // We need a hook here to call the derived classes to do their work.
      valueChanged(row, col);

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

  if (numRows > 0)
    table->setRowReadOnly(numRows - 1, false);
}

void CopasiTableWidget::updateRow(const C_INT32 row)
{
  //status flags
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
  // Assure that the changes to the current cell get commited.
  btnOK->setFocus();

  saveTable();
  fillTable();
}

void CopasiTableWidget::slotBtnCancelClicked()
{
  if (CCopasiDataModel::Global->getModel())
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

  //this is not strictly necessary if you actually leave the widget
  //but the leave() method is also used to force a commit - even if the widget
  //is still visible afterwards
  fillTable();

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
