/**
 *  CReportDefinition class.
 *  This class describes the Report Definition
 *
 *  Created for Copasi by Mudita Singhal
 */

#include <string>
#include "copasi.h"
#include "model/CModel.h"
#include "utilities/CGlobals.h"
#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "CReportDefinition.h"
#include "utilities/CMethodParameter.h"

//////////////////////////////////////////////////
//
//class CReportDefinition
//
//////////////////////////////////////////////////
CReportDefinition::CReportDefinition():
    rComment(new CComment),
    rHeader(new CHeaderFooter),
    rFooter(new CHeaderFooter),
    rBody(new CBody)
{}

CReportDefinition::~CReportDefinition()
{cleanup();}

void CReportDefinition::cleanup()
{
  pdelete(rComment);
  pdelete(rHeader);
  pdelete(rFooter);
  pdelete(rBody);
}

CComment* CReportDefinition::getComment()
{return rComment;}

void CReportDefinition::setComment(CComment *comment)
{rComment = comment;}

CHeaderFooter* CReportDefinition::getHeader()
{return rHeader;}

void CReportDefinition::setHeader(CHeaderFooter *header)
{rHeader = header;}

CHeaderFooter* CReportDefinition::getFooter()
{return rFooter;}

void CReportDefinition::setFooter(CHeaderFooter *footer)
{rFooter = footer;}

CBody* CReportDefinition::getBody()
{return rBody;}

void CReportDefinition::setBody(CBody *body)
{rBody = body;}

//////////////////////////////////////////////////
//
//class CComment
//
//////////////////////////////////////////////////
CComment::CComment():
    cText(new CComment)
{}

CComment::~CComment()
{cleanup();}

void CComment::cleanup()
{
  pdelete(cText);
}

CComment* CComment::getText()
{return cText;}

void CComment::setText(CComment *text)
{cText = text;}

//////////////////////////////////////////////////
//
//class CHeaderFooter
//
//////////////////////////////////////////////////
CHeaderFooter::CHeaderFooter():
    hObject(new CObject),
    hText(new CComment),
    hReport(new CReport)
{}

CHeaderFooter::~CHeaderFooter()
{cleanup();}

void CHeaderFooter::cleanup()
{
  pdelete(hObject);
  pdelete(hText);
  pdelete(hReport);
}

CObject* CHeaderFooter::getObject()
{return hObject;}

void CHeaderFooter::setObject(CObject *object)
{hObject = object;}

CComment* CHeaderFooter::getText()
{return hText;}

void CHeaderFooter::setText(CComment *text)
{hText = text;}

CReport* CHeaderFooter::getReport()
{return hReport;}

void CHeaderFooter::setReport(CReport *report)
{hReport = report;}

//////////////////////////////////////////////////
//
//class CBody
//
//////////////////////////////////////////////////
CBody::CBody():
    bTable(new CTable),
    bReport(new CReport)
{}

CBody::~CBody()
{cleanup();}

void CBody::cleanup()
{
  pdelete(bTable);
  pdelete(bReport);
}

CReport* CBody::getReport()
{return bReport;}

void CBody::setReport(CReport *report)
{bReport = report;}

CTable* CBody::getTable()
{return bTable;}

void CBody::setTable(CTable *table)
{bTable = table;}

//////////////////////////////////////////////////
//
//class CObject
//
//////////////////////////////////////////////////
CObject::CObject()
{}

CObject::~CObject()
{}

const std::string* CObject::getName()
{return oName;}

void CObject::setName(const std::string * name)
{oName = name;}

//////////////////////////////////////////////////
//
//class CReport
//
//////////////////////////////////////////////////
CReport::CReport():
    rReport(new CReport),
    rAppend(true)
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  pdelete(rReport);
}

CReport* CReport::getReference()
{return rReport;}

void CReport::setReference(CReport *report)
{rReport = report;}

const std::string* CReport::getTarget()
{return rTarget;}

void CReport::setTarget(const std::string *target)
{rTarget = target;}

bool CReport::append()
{return rAppend;}

void CReport::setAppend(bool append)
{rAppend = append;}

//////////////////////////////////////////////////
//
//class CTable
//
//////////////////////////////////////////////////
CTable::CTable():
    tObject(new CObject),
    tPrintTitle(true)
{}

CTable::~CTable()
{cleanup();}

void CTable::cleanup()
{
  pdelete(tObject);
}

CObject* CTable::getObject()
{return tObject;}

void CTable::setObject(CObject *object)
{tObject = object;}

const std::string* CTable::getSeperator()
{return tSeperator;}

void CTable::setSeperator(const std::string *seperator)
{tSeperator = seperator;}

bool CTable::printTitle()
{return tPrintTitle;}

void CTable::setPrintTitle(bool printTitle)
{tPrintTitle = printTitle;}
