/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/PlotWidget.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 13:47:40 $
   End CVS Header */

#include "PlotWidget.h"

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
#include "report/CReportDefinition.h"
#include "report/CCopasiStaticString.h"
#include "qtUtilities.h"
#include "plot/CPlotSpecVector.h"
#include "DataModelGUI.h"

std::vector<const CCopasiObject*> PlotWidget::getObjects() const
  {
    CCopasiVector<CPlotSpec>* tmp =
      dataModel->getPlotSpecVectorAddr();

    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp->size();
    for (i = 0; i < imax; ++i)
      ret.push_back((*tmp)[i]);

    return ret;
  }

void PlotWidget::init()
{
  mOT = ListViews::PLOT;
  numCols = 3;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Curves");

  //this restricts users from editing the number of curves
  table->setColumnReadOnly (2, true);
}

void PlotWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CPlotSpec* pPl = (const CPlotSpec*)obj;
  table->setText(row, 1, FROM_UTF8(pPl->getObjectName()));
  table->setText(row, 2, QString::number(pPl->getCurves().size()));
}

void PlotWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CPlotSpec* pPl = (CPlotSpec*)obj;
  //pPl->setComment((const char *)table->text(row, 2).utf8());
}

void PlotWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, "");
}

QString PlotWidget::defaultObjectName() const
  {
    return "plot";
  }

CCopasiObject* PlotWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CPlotSpec* pPl;
  while (!(pPl = dataModel->getPlotSpecVectorAddr()->createPlotSpec(nname)))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }

  pPl->createDefaultPlot(dataModel->getModel()); //TODO have an extra button for that

  std::cout << " *** created PlotSpec: " << nname << " : " << pPl->getKey() << std::endl;
  return pPl;
}

void PlotWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dataModel->getModel())
    return;

  if (keys.size() == 0)
    return;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++)
    {
      dataModel->getPlotSpecVectorAddr()->removePlotSpec(keys[i]);
      ListViews::notify(ListViews::PLOT, ListViews::DELETE, keys[i]);
    }
}
