// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CPublicationsWidget.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/20 19:06:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>

#include "model/CModel.h"
#include "MIRIAM/CPublication.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"

#include "CPublicationsWidget.h"

#define COL_MARK               0
#define COL_URL                1

/*
 *  Constructs a CPublicationsWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CPublicationsWidget::CPublicationsWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiTableWidget(parent, false, name, f, false)
{
  if (!name)
    CopasiTableWidget::setName("PublicationsWidget");
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CPublicationsWidget::~CPublicationsWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

std::vector<const CCopasiObject*> CPublicationsWidget::getObjects() const
  {
    std::vector<const CCopasiObject*> ret;

    const CCopasiVector<CPublication>& tmp = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getPublications();

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void CPublicationsWidget::init()
{
  numCols = 2;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_URL, "URL");
}

void CPublicationsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CPublication *pPublication = (const CPublication*)obj;
  table->setText(row, COL_URL, FROM_UTF8(pPublication->getURL()));
}

void CPublicationsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CPublication * pPublication = static_cast< CPublication * >(obj);

  pPublication->setURL((const char *) table->text(row, COL_URL).utf8());
}

void CPublicationsWidget::defaultTableLineContent(unsigned C_INT32 C_UNUSED(row), unsigned C_INT32 C_UNUSED(exc))
{}

QString CPublicationsWidget::defaultObjectName() const
  {return "Publication";}

CCopasiObject* CPublicationsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CPublication* pPublication = NULL;

  while (!(pPublication = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().createPublication(name)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }

  return pPublication;
}

void CPublicationsWidget::deleteObjects(const std::vector<std::string> & keys)
{

  QString PublicationList = "Are you sure you want to delete listed PUBLICATION(S) ?\n";
  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CPublication * pPublication =
        dynamic_cast< CPublication *>(GlobalKeys.get(keys[i]));

      PublicationList.append(FROM_UTF8(pPublication->getObjectName()));
      PublicationList.append(", ");
    }

  PublicationList.remove(PublicationList.length() - 2, 2);

  QString msg = PublicationList;

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
            CCopasiDataModel::Global->getModel()->getMIRIAMInfo().removePublication(keys[i]);
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
