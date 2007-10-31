// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CAuthorsWidget.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/31 23:24:26 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>

#include "model/CModel.h"
#include "MIRIAM/CAuthor.h"
#include "utilities/CCopasiVector.h"
#include "report/CCopasiObject.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#include "CAuthorsWidget.h"
#include "qtUtilities.h"

#define COL_MARK               0
#define COL_GIVEN_NAME         1
#define COL_FAMILY_NAME        2
#define COL_EMAIL              3
#define COL_URL                4

/*
 *  Constructs a CAuthorsWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CAuthorsWidget::CAuthorsWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiTableWidget(parent, false, name, f, false)
{
  if (!name)
    CopasiTableWidget::setName("CAuthorsWidget");
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CAuthorsWidget::~CAuthorsWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

std::vector<const CCopasiObject*> CAuthorsWidget::getObjects() const
  {
    std::vector<CAuthor>& tmp = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getAuthors();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(&tmp[i]);

    return ret;
  }

void CAuthorsWidget::init()
{
  numCols = 5;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_GIVEN_NAME, "Given Name");
  tableHeader->setLabel(COL_FAMILY_NAME, "Family Name");
  tableHeader->setLabel(COL_EMAIL, "Email");
  tableHeader->setLabel(COL_URL, "URL");
}

void CAuthorsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CAuthor *pAuthor = (const CAuthor*)obj;
  table->setText(row, COL_GIVEN_NAME, FROM_UTF8(pAuthor->getGivenName()));
  table->setText(row, COL_FAMILY_NAME, FROM_UTF8(pAuthor->getFamilyName()));
  table->setText(row, COL_EMAIL, FROM_UTF8(pAuthor->getEmail()));
  table->setText(row, COL_URL, FROM_UTF8(pAuthor->getURL()));
}

void CAuthorsWidget::tableLineToObject(unsigned C_INT32 C_UNUSED(row), CCopasiObject* C_UNUSED(obj))
{}

void CAuthorsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->clearCell(row, 2);

  if (exc != 3)
    table->clearCell(row, 3);
}

QString CAuthorsWidget::defaultObjectName() const
{return "";}

CCopasiObject* CAuthorsWidget::createNewObject(const std::string & C_UNUSED(name))
{return NULL;}

void CAuthorsWidget::deleteObjects(const std::vector<std::string> & C_UNUSED(keys))
{}
