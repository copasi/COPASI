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
CReportDefinition::CReportDefinition()
{}

CReportDefinition::~CReportDefinition()
{}

//CComment CReportDefinition::getComment()
//{}

void CReportDefinition::setComment(CComment *comment)
{}

//CHeaderFooter CReportDefinition::getHeader()
//{}

void CReportDefinition::setHeader(CHeaderFooter *header)
{}

//CHeaderFooter CReportDefinition::getFooter()
//{}

void CReportDefinition::setFooter(CHeaderFooter *footer)
{}

//CBody CReportDefinition::getBody()
//{}

void CReportDefinition::setBody(CBody *body)
{}

//////////////////////////////////////////////////
//
//class CComment
//
//////////////////////////////////////////////////
CComment::CComment()
{}

CComment::~CComment()
{}

//CComment CComment::getText()
//{}

void CComment::setText(CComment *text)
{}

//////////////////////////////////////////////////
//
//class CHeaderFooter
//
//////////////////////////////////////////////////
CHeaderFooter::CHeaderFooter()
{}

CHeaderFooter::~CHeaderFooter()
{}

//CObject CHeaderFooter::getObject()
//{}

void CHeaderFooter::setObject(CObject *object)
{}

//CComment CHeaderFooter::getText()
//{}

void CHeaderFooter::setText(CComment *text)
{}

//CReport CHeaderFooter::getReport()
//{}

void CHeaderFooter::setReport(CReport *report)
{}

//////////////////////////////////////////////////
//
//class CBody
//
//////////////////////////////////////////////////
CBody::CBody()
{}

CBody::~CBody()
{}

//CReport CBody::getReport()
//{}

void CBody::setReport(CReport *report)
{}

//CTable CBody::getTable()
//{}

void CBody::setTable(CTable *table)
{}

//////////////////////////////////////////////////
//
//class CObject
//
//////////////////////////////////////////////////
CObject::CObject()
{}

CObject::~CObject()
{}
//const std::string CObject::getName()
//{}

void CObject::setName(const std::string * name)
{}

//////////////////////////////////////////////////
//
//class CReport
//
//////////////////////////////////////////////////
CReport::CReport()
{}

CReport::~CReport()
{}

//CReport CReport::getReference()
//{}

void CReport::setReference(CReport *report)
{}

//const std::string CReport::getTarget()
//{}

void CReport::setTarget(const std::string *target)
{}

//bool CReport::append()
//{}

void CReport::setAppend(bool append)
{}

//////////////////////////////////////////////////
//
//class CTable
//
//////////////////////////////////////////////////
CTable::CTable()
{}

CTable::~CTable()
{}

//CObject CTable::getObject()
//{}

void CTable::setObject(CObject *object)
{}

//const std::string CTable::getSeperator()
//{}

void CTable::setSeperator(const std::string *seperator)
{}

//bool CTable::printTitle()
//{}

void CTable::setPrintTitle(bool printTitle)
{}
