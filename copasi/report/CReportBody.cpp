/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportBody.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:31:10 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
