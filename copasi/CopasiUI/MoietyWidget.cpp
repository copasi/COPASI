/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MoietyWidget.cpp,v $
   $Revision: 1.54 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/07 08:59:26 $
   End CVS Header */

#include "MoietyWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "model/CMoiety.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

std::vector<const CCopasiObject*> MoietyWidget::getObjects() const
  {
    const CCopasiVectorN<CMoiety>& tmp = dataModel->getModel()->getMoieties();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void MoietyWidget::init()
{
  btnRun = new QPushButton("&Recalculate", this);
  mHLayout->addWidget(btnRun);
  connect(btnRun, SIGNAL(clicked ()), this,
          SLOT(slotBtnRunClicked()));

  numCols = 4;
  table->setNumCols(numCols);
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  table->hideColumn(0);
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Equation");
  tableHeader->setLabel(3, "Number");
}

void MoietyWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CMoiety* pMoi = (const CMoiety*)obj;
  table->setText(row, 1, FROM_UTF8(pMoi->getObjectName()));
  table->setText(row, 2, FROM_UTF8(pMoi->getDescription(dataModel->getModel())));
  table->setText(row, 3, QString::number(pMoi->getNumber()));
}

void MoietyWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{}

void MoietyWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{}

QString MoietyWidget::defaultObjectName() const
  {return "";}

CCopasiObject* MoietyWidget::createNewObject(const std::string & name)
{return NULL;}

void MoietyWidget::deleteObjects(const std::vector<std::string> & keys)
{}

void MoietyWidget::slotBtnRunClicked()
{
  dataModel->getModel()->compile();
  fillTable();

  mIgnoreUpdates = true; //to avoid recursive calls
  ListViews::notify(ListViews::MODEL, ListViews::CHANGE);
  mIgnoreUpdates = false; //to avoid recursive calls
}
