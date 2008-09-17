// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CBiologicalDescriptionsWidget.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: aruff $
//   $Date: 2008/09/17 17:25:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>
#include <sstream>

#include "copasi.h"

#include "CQMiriamWidget.h"
#include "CBiologicalDescriptionsWidget.h"

#include "MIRIAM/CModelMIRIAMInfo.h"

#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObject.h"
#include "report/CKeyFactory.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"
#include "MIRIAM/CMIRIAMResource.h"
#include "utilities/CCopasiParameterGroup.h"

#define COL_MARK               0
#define COL_DUMMY              1
#define COL_RELATIONSHIP       2
#define COL_RESOURCE           3
#define COL_ID                 4

/*
 *  Constructs a CBiologicalDescriptionsWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CBiologicalDescriptionsWidget::CBiologicalDescriptionsWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiTableWidget(parent, false, name, f, false)
{
  if (!name)
    CopasiTableWidget::setName("BiologicalDescriptionsWidget");
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CBiologicalDescriptionsWidget::~CBiologicalDescriptionsWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

std::vector<const CCopasiObject*> CBiologicalDescriptionsWidget::getObjects() const
  {
    std::vector<const CCopasiObject*> ret;

    if (dynamic_cast <CQMiriamWidget*> (parentWidget()))
      {
        const CCopasiVector<CBiologicalDescription>& tmp = dynamic_cast <CQMiriamWidget*> (parentWidget())->getMIRIAMInfo().getBiologicalDescriptions();

        C_INT32 i, imax = tmp.size();
        for (i = 0; i < imax; ++i)
          ret.push_back(tmp[i]);
      }

    return ret;
  }

void CBiologicalDescriptionsWidget::init()
{
  mOT = ListViews::MIRIAM;
  //flagtoAdjust = false;
  mShowNewObjectWarning = false;
  numCols = 5;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_DUMMY, "Dummy");
  tableHeader->setLabel(COL_RELATIONSHIP, "Relationship");
  tableHeader->setLabel(COL_RESOURCE, "Resource");
  tableHeader->setLabel(COL_ID, "ID");
  table->hideColumn(COL_DUMMY);

  //table->setColumnWidth(COL_ID, 200);
  // Build the list of supported predicates
  mPredicates.push_back("-- select --");
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_encodes)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_hasPart)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_hasVersion)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_is)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isEncodedBy)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isHomologTo)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isPartOf)));
  mPredicates.push_back(FROM_UTF8(CRDFPredicate::getDisplayName(CRDFPredicate::copasi_isVersionOf)));

  // Build the list of known resources
  updateResourcesList();
}

void CBiologicalDescriptionsWidget::updateResourcesList()
{
  mResources.clear();
  // Build the list of known resources
  const CMIRIAMResources * pResource = &CCopasiDataModel::Global->getConfiguration()->getRecentMIRIAMResources();
  mResources.push_back("-- select --");

  CCopasiParameterGroup::index_iterator it = pResource->getResourceList().beginIndex();
  CCopasiParameterGroup::index_iterator end = pResource->getResourceList().endIndex();
  unsigned C_INT32 Index = 0;
  for (; it != end; ++it)
    {
      mResources.push_back(FROM_UTF8(pResource->getMIRIAMResource(Index).getMIRIAMDisplayName()));
      Index++;
    }
}

void CBiologicalDescriptionsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CBiologicalDescription *pBiologicalDescription = (const CBiologicalDescription*)obj;

  table->setText(row, COL_DUMMY, QString::number(row));

  QComboTableItem * pComboBox = NULL;
  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP)))
    {
      pComboBox = static_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP));
      pComboBox->setCurrentItem(FROM_UTF8(pBiologicalDescription->getPredicate()));
    }
  else
    {
      pComboBox = new QComboTableItem(table, mPredicates);
      pComboBox->setCurrentItem(FROM_UTF8(pBiologicalDescription->getPredicate()));
      table->setItem(row, COL_RELATIONSHIP, pComboBox);
    }

  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RESOURCE)))
    {
      pComboBox = static_cast<QComboTableItem *>(table->item(row, COL_RESOURCE));
      pComboBox->setCurrentItem(FROM_UTF8(pBiologicalDescription->getResource()));
    }
  else
    {
      pComboBox = new QComboTableItem(table, mResources);
      pComboBox->setCurrentItem(FROM_UTF8(pBiologicalDescription->getResource()));
      table->setItem(row, COL_RESOURCE, pComboBox);
    }

  table->setText(row, COL_ID, FROM_UTF8(pBiologicalDescription->getId()));
}

void CBiologicalDescriptionsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CBiologicalDescription * pBiologicalDescription = static_cast< CBiologicalDescription * >(obj);

  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP)))
    {
      const std::string relationship = (const char *) static_cast<QComboTableItem *>(table->item(row, COL_RELATIONSHIP))->currentText().utf8();
      pBiologicalDescription->setPredicate(relationship);
    }

  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_RESOURCE)))
    {
      QString resource = static_cast<QComboTableItem *>(table->item(row, COL_RESOURCE))->currentText();
      pBiologicalDescription->setResource((const char *) resource.utf8());
    }

  QString ID = table->text(row, COL_ID);
  pBiologicalDescription->setId((const char *) ID.utf8());
}

void CBiologicalDescriptionsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_RELATIONSHIP)
    {
      QComboTableItem * pComboBox = new QComboTableItem(table, mPredicates);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_RELATIONSHIP, pComboBox);
    }

  if (exc != COL_RESOURCE)
    {
      QComboTableItem * pComboBox = new QComboTableItem(table, mResources);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_RESOURCE, pComboBox);
    }

  if (exc != COL_ID)
    table->clearCell(row, COL_ID);
}

QString CBiologicalDescriptionsWidget::defaultObjectName() const
{return "";}

CCopasiObject* CBiologicalDescriptionsWidget::createNewObject(const std::string & /* name */)
{
  if (!dynamic_cast <CQMiriamWidget*> (parentWidget()))
    return NULL;

  CBiologicalDescription* pBiologicalDescription = NULL;
  pBiologicalDescription = dynamic_cast <CQMiriamWidget*> (parentWidget())->getMIRIAMInfo().createBiologicalDescription();

  return pBiologicalDescription;
}

void CBiologicalDescriptionsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  CQMiriamWidget * pMiriamWidget = dynamic_cast <CQMiriamWidget*> (parentWidget());
  if (pMiriamWidget == NULL)
    return;

  unsigned C_INT32 i, imax = keys.size();

  for (i = 0; i < imax; i++)
    pMiriamWidget->getMIRIAMInfo().removeBiologicalDescription(keys[i]);

  for (i = 0; i < imax; i++)
    protectedNotify(mOT, ListViews::DELETE, keys[i]);

  mChanged = true;
}

void CBiologicalDescriptionsWidget::slotDoubleClicked(int C_UNUSED(row), int C_UNUSED(col),
    int C_UNUSED(m), const QPoint & C_UNUSED(n))
{}

void CBiologicalDescriptionsWidget::slotValueChanged(int row, int col)
{
  if (col == COL_RELATIONSHIP || col == COL_RESOURCE)
    {
      int selectedItem = -1;
      if (row == table->numRows() - 1) //new Object
        {
          if (dynamic_cast<QComboTableItem *>(table->item(row, col)))
            {
              selectedItem = static_cast<QComboTableItem *>(table->item(row, col))->currentItem();
            }
        }
      CopasiTableWidget::slotValueChanged(row, col);
      if (selectedItem > -1)
      {static_cast<QComboTableItem *>(table->item(row, col))->setCurrentItem(selectedItem);}
    }
  else
  {CopasiTableWidget::slotValueChanged(row, col);}
}
