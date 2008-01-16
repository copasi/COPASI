// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CAuthorsWidget.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/16 20:20:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>

#include "model/CModel.h"
#include "MIRIAM/CAuthor.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"

#include "CAuthorsWidget.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"

#define COL_MARK               0
#define COL_FAMILY_NAME        1
#define COL_GIVEN_NAME         2
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
    CopasiTableWidget::setName("AuthorsWidget");
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
    std::vector<const CCopasiObject*> ret;
#ifdef XXXX
    const CCopasiVector<CAuthor>& tmp = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getAuthors();

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);
#endif // XXXX
    return ret;
  }

void CAuthorsWidget::init()
{
  numCols = 5;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_FAMILY_NAME, "Family Name");
  tableHeader->setLabel(COL_GIVEN_NAME, "Given Name");
  tableHeader->setLabel(COL_EMAIL, "Email");
  tableHeader->setLabel(COL_URL, "URL");
}

void CAuthorsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CAuthor *pAuthor = (const CAuthor*)obj;
  table->setText(row, COL_FAMILY_NAME, FROM_UTF8(pAuthor->getFamilyName()));
  table->setText(row, COL_GIVEN_NAME, FROM_UTF8(pAuthor->getGivenName()));
  table->setText(row, COL_EMAIL, FROM_UTF8(pAuthor->getEmail()));
  table->setText(row, COL_URL, FROM_UTF8(pAuthor->getURL()));
}

void CAuthorsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CAuthor * pAuthor = static_cast< CAuthor * >(obj);

  pAuthor->setFamilyName((const char *) table->text(row, COL_FAMILY_NAME).utf8());
  pAuthor->setGivenName((const char *) table->text(row, COL_GIVEN_NAME).utf8());
  pAuthor->setEmail((const char *) table->text(row, COL_EMAIL).utf8());
  pAuthor->setURL((const char *) table->text(row, COL_URL).utf8());
}

void CAuthorsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_GIVEN_NAME)
    table->clearCell(row, COL_GIVEN_NAME);

  if (exc != COL_EMAIL)
    table->clearCell(row, COL_EMAIL);

  if (exc != COL_URL)
    {
      //table->setText(row, COL_URL, "abcd.com");
      table->clearCell(row, COL_URL);
    }
}

QString CAuthorsWidget::defaultObjectName() const
  {return "New Author";}

CCopasiObject* CAuthorsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CAuthor* pAuthor = NULL;
#ifdef XXXX
  while (!(pAuthor = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().createAuthor(nname)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }
#endif // XXXX
  return pAuthor;
}

void CAuthorsWidget::deleteObjects(const std::vector<std::string> & keys)
{

  QString authorList = "Are you sure you want to delete listed AUTHOR(S) ?\n";
  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CAuthor * pAuthor =
        dynamic_cast< CAuthor *>(GlobalKeys.get(keys[i]));

      authorList.append(FROM_UTF8(pAuthor->getObjectName()));
      authorList.append(", ");
    }

  authorList.remove(authorList.length() - 2, 2);

  QString msg = authorList;

  C_INT32 choice = 0;
  choice = CQMessageBox::question(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  "Continue", "Cancel", 0, 1, 1);

  switch (choice)
    {
    case 0:                                           // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
#ifdef XXXX
            CCopasiDataModel::Global->getModel()->getMIRIAMInfo().removeAuthor(keys[i]);
#endif // XXXX
          }

        //for (i = 0; i < imax; i++)
        //protectedNotify(ListViews::MODEL, ListViews::DELETE, keys[i]);

        mChanged = true;
        break;
      }
    default:                                           // No or Escape
      break;
    }
}
