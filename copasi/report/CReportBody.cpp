/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportBody.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/28 15:26:36 $
   End CVS Header */

#include "copasi.h"
#include "CReportBody.h"

//////////////////////////////////////////////////
//
//class CReportBody
//
//////////////////////////////////////////////////
CReportBody::CReportBody():
    mpReportTable(NULL)
{}

CReportBody::~CReportBody()
{cleanup();}

void CReportBody::cleanup()
{
  mReportObjectName.clear();
  pdelete(mpReportTable);
}

CReportTable* CReportBody::getTable()
{return mpReportTable;}

void CReportBody::setTable(CReportTable *table)
{mpReportTable = table;}

//////////////////////////////////////////////////
//
//class CReportTable
//
//////////////////////////////////////////////////
CReportTable::CReportTable():
    mpObjectNameVector(NULL),
    mSeparator(" "),
    mPrintTitle(true)
{}

CReportTable::~CReportTable()
{cleanup();}

void CReportTable::cleanup()
{
  // this pointer is created outsid
  pdelete(mpObjectNameVector);
}
