/**
 *  CReportDefinition class.
 *  This class describes the Report Definition
 *
 *  Created for Copasi by Mudita Singhal
 */

#include <string>
#include "copasi.h"
#include <vector>
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

std::vector<CHeaderFooter*> CReportDefinition::getHeader()
{return rHeaderVector;}

void CReportDefinition::setHeader(CHeaderFooter *header)
{rHeader = header;}

std::vector<CHeaderFooter*> CReportDefinition::getFooter()
{return rFooterVector;}

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
    hObject(new CReportObject),
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

CReportObject* CHeaderFooter::getObject()
{return hObject;}

void CHeaderFooter::setObject(CReportObject *object)
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
    bTable(new CReportTable),
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

CReportTable* CBody::getTable()
{return bTable;}

void CBody::setTable(CReportTable *table)
{bTable = table;}

//////////////////////////////////////////////////
//
//class CReportObject
//
//////////////////////////////////////////////////
CReportObject::CReportObject()
{}

CReportObject::~CReportObject()
{}

const std::string* CReportObject::getName()
{return oName;}

void CReportObject::setName(const std::string * name)
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

CReportObject* CReportTable::getObject()
{return tObject;}

void CReportTable::setObject(CReportObject *object)
{tObject = object;}

const std::string* CReportTable::getSeperator()
{return tSeperator;}

void CReportTable::setSeperator(const std::string *seperator)
{tSeperator = seperator;}

bool CReportTable::printTitle()
{return tPrintTitle;}

void CReportTable::setPrintTitle(bool printTitle)
{tPrintTitle = printTitle;}
