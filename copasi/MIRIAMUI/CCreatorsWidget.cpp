// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CCreatorsWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/25 20:37:26 $
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
#include "MIRIAM/CCreator.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"

#include "CCreatorsWidget.h"

#define COL_MARK               0
#define COL_FAMILY_NAME        1
#define COL_GIVEN_NAME         2
#define COL_EMAIL              3
#define COL_ORG                4

/*
 *  Constructs a CCreatorsWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CCreatorsWidget::CCreatorsWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiTableWidget(parent, false, name, f, false)
{
  if (!name)
    CopasiTableWidget::setName("CreatorsWidget");
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CCreatorsWidget::~CCreatorsWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

std::vector<const CCopasiObject*> CCreatorsWidget::getObjects() const
  {
    std::vector<const CCopasiObject*> ret;

    const CCopasiVector<CCreator>& tmp = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getCreators();

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void CCreatorsWidget::init()
{
  numCols = 5;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_FAMILY_NAME, "Family Name");
  tableHeader->setLabel(COL_GIVEN_NAME, "Given Name");
  tableHeader->setLabel(COL_EMAIL, "Email");
  tableHeader->setLabel(COL_ORG, "Organization");
}

void CCreatorsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CCreator *pCreator = (const CCreator*)obj;
  table->setText(row, COL_FAMILY_NAME, FROM_UTF8(pCreator->getFamilyName()));
  table->setText(row, COL_GIVEN_NAME, FROM_UTF8(pCreator->getGivenName()));
  table->setText(row, COL_EMAIL, FROM_UTF8(pCreator->getEmail()));
  table->setText(row, COL_ORG, FROM_UTF8(pCreator->getORG()));
}

void CCreatorsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CCreator * pCreator = static_cast< CCreator * >(obj);

  pCreator->setFamilyName((const char *) table->text(row, COL_FAMILY_NAME).utf8());
  pCreator->setGivenName((const char *) table->text(row, COL_GIVEN_NAME).utf8());
  pCreator->setEmail((const char *) table->text(row, COL_EMAIL).utf8());
  pCreator->setORG((const char *) table->text(row, COL_ORG).utf8());
}

void CCreatorsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_GIVEN_NAME)
    table->clearCell(row, COL_GIVEN_NAME);

  if (exc != COL_EMAIL)
    table->clearCell(row, COL_EMAIL);

  if (exc != COL_ORG)
  {table->clearCell(row, COL_ORG);}
}

QString CCreatorsWidget::defaultObjectName() const
  {return "";}

CCopasiObject* CCreatorsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CCreator* pCreator = NULL;

  while (!(pCreator = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().createCreator(name)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }

  return pCreator;
}

void CCreatorsWidget::deleteObjects(const std::vector<std::string> & keys)
{

  QString authorList = "Are you sure you want to delete listed AUTHOR(S) ?\n";
  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CCreator * pCreator =
        dynamic_cast< CCreator *>(GlobalKeys.get(keys[i]));

      authorList.append(FROM_UTF8(pCreator->getObjectName()));
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
            CCopasiDataModel::Global->getModel()->getMIRIAMInfo().removeCreator(keys[i]);
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
