// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQTableWidget.h"

#include <QDropEvent>

CQTableWidget::CQTableWidget(QWidget* pParent)
  : QTableWidget(pParent)
{
}

void CQTableWidget::dropEvent(QDropEvent* pEvent)
{
  if (pEvent->source() != this)
    return;

  int newRow = this->indexAt(pEvent->pos()).row();

  QTableWidgetItem* selectedItem;
  QList<QTableWidgetItem*> selectedItems = this->selectedItems();

  if (newRow == -1)
    newRow = this->rowCount();

  int i;

  for (i = 0; i < selectedItems.length() / this->columnCount(); ++i)
    {
      this->insertRow(newRow);
    }

  int currentOldRow = -1;
  int currentNewRow = newRow - 1;
  QList<int> deleteRows;
  foreach(selectedItem, selectedItems)
  {
    int column = selectedItem->column();

    if (selectedItem->row() != currentOldRow)
      {
        currentOldRow = selectedItem->row();
        deleteRows.append(currentOldRow);
        ++currentNewRow;
      }

    this->takeItem(currentOldRow, column);
    this->setItem(currentNewRow, column, selectedItem);
  }

  for (i = deleteRows.count() - 1; i >= 0; --i)
    {
      this->removeRow(deleteRows.at(i));
    }

}
