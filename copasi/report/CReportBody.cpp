#include "CReportBody.h"

//////////////////////////////////////////////////
//
//class CReportBody
//
//////////////////////////////////////////////////
CReportBody::CReportBody():
    //    bTable(new CReportTable),
    //    bReport(new CReport)
    mTable(NULL),
    mReport(NULL)
{}

CReportBody::~CReportBody()
{cleanup();}

void CReportBody::cleanup()
{
  pdelete(bTable);
  pdelete(bReport);
}

CReport* CReportBody::getReport()
{return bReport;}

void CReportBody::setReport(CReport *report)
{bReport = report;}

CReportTable* CReportBody::getTable()
{return bTable;}

void CReportBody::setTable(CReportTable *table)
{bTable = table;}

//////////////////////////////////////////////////
//
//class CReportTable
//
//////////////////////////////////////////////////
CReportTable::CReportTable():
    tObject(new CReportObject),
    tPrintTitle(true)
{}

CReportTable::~CReportTable()
{cleanup();}

void CReportTable::cleanup()
{
  pdelete(tObject);
}
