/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportBody.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:31:47 $
   End CVS Header */

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
    mSeperator(" "),
    mPrintTitle(true)
{}

CReportTable::~CReportTable()
{cleanup();}

void CReportTable::cleanup()
{
  // this pointer is created outsid
  pdelete(mpObjectNameVector);
}
