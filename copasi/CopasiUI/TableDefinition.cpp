/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TableDefinition.cpp,v $
   $Revision: 1.49 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/02 15:55:36 $
   End CVS Header */

#include "TableDefinition.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

//#include "MyTable.h"
#include "model/CModel.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinitionVector.h"
#include "report/CCopasiStaticString.h"
#include "qtUtilities.h"

#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "scan/CScanTask.h"

std::vector<const CCopasiObject*> TableDefinition::getObjects() const
  {
    CCopasiVector< CReportDefinition >* tmp =
      dataModel->getReportDefinitionVectorAddr();

    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp->size();
    for (i = 0; i < imax; ++i)
      ret.push_back((*tmp)[i]);

    return ret;
  }

void TableDefinition::init()
{
  mOT = ListViews::REPORT;
  numCols = 3;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Comment");
}

void TableDefinition::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CReportDefinition* pRep = (const CReportDefinition*)obj;
  table->setText(row, 1, FROM_UTF8(pRep->getObjectName()));
  table->setText(row, 2, FROM_UTF8(pRep->getComment()));
}

void TableDefinition::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CReportDefinition* pRep = (CReportDefinition*)obj;
  pRep->setComment((const char *)table->text(row, 2).utf8());
}

void TableDefinition::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, "");
}

QString TableDefinition::defaultObjectName() const
  {
    return "report";
  }

CCopasiObject* TableDefinition::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CReportDefinition* pRep;
  while (!(pRep = dataModel->getReportDefinitionVectorAddr()->createReportDefinition(nname, "")))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }
  std::cout << " *** created ReportDefinition: " << nname << " : " << pRep->getKey() << std::endl;
  return pRep;
}

void TableDefinition::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dataModel->getModel())
    return;

  if (keys.size() == 0)
    return;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++)
    {
      //check where the report is used...
      CReportDefinition* rd = dynamic_cast< CReportDefinition * >(GlobalKeys.get(keys[i]));
      if (!rd) break;

      if (dataModel->getTrajectoryTask()->getReport().getReportDefinition() == rd)
        dataModel->getTrajectoryTask()->getReport().setReportDefinition(NULL);

      if (dataModel->getSteadyStateTask()->getReport().getReportDefinition() == rd)
        dataModel->getSteadyStateTask()->getReport().setReportDefinition(NULL);

      if (dataModel->getMCATask()->getReport().getReportDefinition() == rd)
        dataModel->getMCATask()->getReport().setReportDefinition(NULL);

      if (dataModel->getScanTask()->getReport().getReportDefinition() == rd)
        dataModel->getScanTask()->getReport().setReportDefinition(NULL);

      //TODO: add other tasks...

      //remove the report
      dataModel->getReportDefinitionVectorAddr()->removeReportDefinition(keys[i]);
      ListViews::notify(ListViews::REPORT, ListViews::DELETE, keys[i]);
    }
}
