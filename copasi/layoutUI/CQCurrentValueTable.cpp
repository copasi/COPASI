// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQCurrentValueTable.h"

#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>

#include <iostream>

#include "copasi/UI/qtUtilities.h"
#include "copasi/layoutUI/CQLayoutMainWindow.h"

CQCurrentValueTable::CQCurrentValueTable(QWidget *parent)
  : QWidget(parent)
{
  init();
  this->show();
}

void CQCurrentValueTable::init()
{
  QVBoxLayout* pLayout = new QVBoxLayout(this);
  this->mpTable = new QTableWidget(this);
  pLayout->addWidget(this->mpTable);
  this->mpTable->setRowCount(1);
  this->mpTable->setColumnCount(2);
  // set default entry
  QHeaderView *header = this->mpTable->horizontalHeader();
  this->mpTable->setHorizontalHeaderLabels(QStringList() << "Metabolite" << "Concentration");
  header = this->verticalHeader();
  header->hide();
  QTableWidgetItem* pItem = new QTableWidgetItem("*** no time series load ***");
  this->mpTable->setItem(0, 0, pItem);
  pItem = new QTableWidgetItem("NaN");
  this->mpTable->setItem(0, 1, pItem);
  this->mpTable->item(0, 0)->setFlags(this->mpTable->item(0, 0)->flags() & ~Qt::ItemIsEditable);
  QHBoxLayout *hLayout = new QHBoxLayout();
  this->mpCheckAllButton = new QPushButton("Check all", this);
  this->mpUncheckAllButton = new QPushButton("Uncheck all", this);
  hLayout->addWidget(mpCheckAllButton);
  hLayout->addWidget(mpUncheckAllButton);
  pLayout->addLayout(hLayout);
  connect(this->mpTable, SIGNAL(cellChanged(int, int)), this, SLOT(tableValueChanged(int, int)));
  connect(this->mpCheckAllButton, SIGNAL(clicked()), this, SLOT(slotCheckAllClicked()));
  connect(this->mpUncheckAllButton, SIGNAL(clicked()), this, SLOT(slotUncheckAllClicked()));
  resize(QSize(202, 153).expandedTo(minimumSizeHint()));
}

CQCurrentValueTable::~CQCurrentValueTable()
{}

// sets complete row: 1. name of reactant 2. concentration (or number of particles) value
void CQCurrentValueTable::setRowInTable(int row, std::string key, std::string s, C_FLOAT64 val)
{
  QTableWidgetItem * pCheckItem = new QTableWidgetItem(FROM_UTF8(s));
  // make the item a check item and make it non editable
  pCheckItem->setFlags((pCheckItem->flags() & ~Qt::ItemIsEditable) | Qt::ItemIsUserCheckable);
  this->mpTable->setItem(row, 0, pCheckItem);
  pCheckItem->setCheckState(Qt::Checked); // initially checked
  pCheckItem = new QTableWidgetItem(convertToQString(val));
  this->mpTable->setItem(row, 1, pCheckItem);
  this->setKeyIndex(key, row); // remember which node key is in which row
}

// changes the value in a given row (value in second column is replaced)
void CQCurrentValueTable::updateRowInTable(int row, C_FLOAT64 val)
{
  if (this->mpTable->item(row, 1) == NULL)
    {
      this->mpTable->setItem(row, 1, new QTableWidgetItem(convertToQString(val)));
    }
  else
    {
      this->mpTable->item(row, 1)->setText(convertToQString(val));
    }
}

// sets (numerical) value as text into the second column of the corresponding reactant (given by row index)
// TODO this method does exactly the same thing as the one above, so we could
// TODO get rid of one of them
void CQCurrentValueTable::setValue(int row, C_FLOAT64 val)
{
  this->updateRowInTable(row, val);
}

void CQCurrentValueTable::setAllBoxesChecked(bool checked)
{
  int i;

  for (i = 0; i < this->mpTable->rowCount(); i++)
    {
      QTableWidgetItem *pCell = this->mpTable->item(i, 0);
      assert(pCell != NULL);

      if (pCell->flags() & Qt::ItemIsUserCheckable)
        {
          // is cell a QCheckTableItem?
          pCell->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
          CQLayoutMainWindow * pTmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
          assert(pTmp);

          if (pTmp)
            {
              if (checked == true)
                {
                  pTmp->addItemInAnimation(this->getKeyForRow(i));
                }
              else
                {
                  pTmp->removeItemInAnimation(this->getKeyForRow(i));
                }
            }
        }
    }
}

void CQCurrentValueTable::setAllBoxesUnchecked()
{
  this->setAllBoxesChecked(false);
}

//store row index for every node key
void CQCurrentValueTable::setKeyIndex(std::string key, int row)
{
  this->mIndexMap.insert(std::pair<int, std::string>
                         (row,
                          key));
}

std::string CQCurrentValueTable::getKeyForRow(int row) const
{
  std::string s = "";

  std::map<int, std::string>::const_iterator itIndexObj = this->mIndexMap.find(row);

  if (itIndexObj != this->mIndexMap.end())
    {
      s = (*itIndexObj).second;
    }

  return s;
}

bool CQCurrentValueTable::getValueForRow(int row) const
{
  QTableWidgetItem *pCell = this->mpTable->item(row, 0);
  assert(pCell != NULL);
  return pCell->checkState() == Qt::Checked;
}

void CQCurrentValueTable::slotCheckAllClicked()
{
  this->setAllBoxesChecked();
}

void CQCurrentValueTable::slotUncheckAllClicked()
{
  this->setAllBoxesUnchecked();
}

void CQCurrentValueTable::setNumRows(int rows)
{
  this->mpTable->setRowCount(rows);
}

void CQCurrentValueTable::setNumCols(int columns)
{
  this->mpTable->setColumnCount(columns);
}

int CQCurrentValueTable::numRows() const
{
  return this->mpTable->rowCount();
}

QHeaderView* CQCurrentValueTable::verticalHeader()
{
  return this->mpTable->verticalHeader();
}

/**
 * This slot is caled whenever a value in the table changes, i.e. whenever
 * a species is activated or deactived by it's checkbox.
 * This information is broadcasted by emitting another signal which contains the row number.
 */
void CQCurrentValueTable::tableValueChanged(int row, int /*column*/)
{
  emit valueChanged(row);
}
