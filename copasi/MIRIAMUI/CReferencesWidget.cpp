// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CReferencesWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/25 20:37:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>

#include "model/CModel.h"
#include "MIRIAM/CReference.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"

#include "CReferencesWidget.h"

#define COL_MARK               0
#define COL_URL                1

/*
 *  Constructs a CReferencesWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CReferencesWidget::CReferencesWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiTableWidget(parent, false, name, f, false)
{
  if (!name)
    CopasiTableWidget::setName("ReferencesWidget");
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CReferencesWidget::~CReferencesWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

std::vector<const CCopasiObject*> CReferencesWidget::getObjects() const
  {
    std::vector<const CCopasiObject*> ret;

    const CCopasiVector<CReference>& tmp = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getReferences();

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void CReferencesWidget::init()
{
  numCols = 2;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_URL, "URL");
}

void CReferencesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CReference *pReference = (const CReference*)obj;
  table->setText(row, COL_URL, FROM_UTF8(pReference->getURL()));
}

void CReferencesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CReference * pReference = static_cast< CReference * >(obj);

  pReference->setURL((const char *) table->text(row, COL_URL).utf8());
}

void CReferencesWidget::defaultTableLineContent(unsigned C_INT32 C_UNUSED(row), unsigned C_INT32 C_UNUSED(exc))
{}

QString CReferencesWidget::defaultObjectName() const
  {return "";}

CCopasiObject* CReferencesWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CReference* pReference = NULL;

  while (!(pReference = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().createReference(name)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }

  return pReference;
}

void CReferencesWidget::deleteObjects(const std::vector<std::string> & keys)
{

  QString ReferenceList = "Are you sure you want to delete listed PUBLICATION(S) ?\n";
  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CReference * pReference =
        dynamic_cast< CReference *>(GlobalKeys.get(keys[i]));

      ReferenceList.append(FROM_UTF8(pReference->getObjectName()));
      ReferenceList.append(", ");
    }

  ReferenceList.remove(ReferenceList.length() - 2, 2);

  QString msg = ReferenceList;

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
            CCopasiDataModel::Global->getModel()->getMIRIAMInfo().removeReference(keys[i]);
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
