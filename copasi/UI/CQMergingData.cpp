// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <map>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CModelExpansion.h"
#include "copasi/model/CChemEqInterface.h"

//#include "copasi/core/CRootContainer.h"

#include "copasi/UI/qtUtilities.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "CQMergingData.h"

class CMetab;
class CModelEntity;

/*
 *  Constructs a CQMergingData which is a child of 'parent', with the
 *  name 'name'.'
 */

CQMergingData::CQMergingData(QWidget* parent, CModel * pModel, Qt::WindowFlags fl)
  : QDialog(parent, fl)
{
  setupUi(this);
  connect(mpTree1, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(treeSelectionChanged()));
  connect(mpTree2, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(treeSelectionChanged()));

  mpModel = pModel;

  load();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMergingData::~CQMergingData()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQMergingData::fillTree(QTreeWidget* pW, const CModel* pModel, std::map< QTreeWidgetItem *, const CDataObject * > & itemMap,
                             bool flagGlobalQuantities, bool flagReactions,
                             const std::set< const CDataObject * > & added,
                             bool highlightInvolved)
{
  itemMap.clear();
  pW->clear();
  CModelExpansion mex(const_cast<CModel*>(pModel));

  //create an italic font for highlighting new model elements
  QFont tmpFont = pW->font();
  tmpFont.setItalic(true);

  //add the compartments
  size_t i, imax = pModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      const CDataObject * pObj = &pModel->getCompartments()[i];
      QTreeWidgetItem * pItem = new QTreeWidgetItem((QTreeWidget*)NULL, 1000);
      pItem->setText(0,  FROM_UTF8(pObj->getObjectName()));

      //highlight new objects
      std::set<const CDataObject * >::const_iterator it = added.find(pObj);

      if (it != added.end())
        {
          pItem->setFont(0, tmpFont);
          //pItem->setBackground(0, QColor(200,200,250));
        }

      //highlight objects that are referred to by others
      if (highlightInvolved)
        {
          if (!mex.existDependentEntities(pObj))
            pItem->setForeground(0, QColor(130, 130, 130));
        }

      itemMap[pItem] = pObj;
      pW->addTopLevelItem(pItem);
      pItem->setFirstColumnSpanned(true);

      //add species
      //QTreeWidgetItem * pChild;
      size_t j, jmax = pModel->getCompartments()[i].getMetabolites().size();

      for (j = 0; j < jmax; ++j)
        {
          pObj = &pModel->getCompartments()[i].getMetabolites()[j];
          QTreeWidgetItem * pChild = new QTreeWidgetItem(pItem, 1001);
          pChild->setText(0,  FROM_UTF8(pObj->getObjectName()));
          pChild->setFirstColumnSpanned(true);

          //highlight new objects
          std::set< const CDataObject * >::const_iterator it = added.find(pObj);

          if (it != added.end())
            {
              pChild->setFont(0, tmpFont);
              //pChild->setBackground(0, QColor(200,200,250));
            }

          //highlight objects that are referred to by others
          if (highlightInvolved)
            {
              if (!mex.existDependentEntities(pObj))
                pChild->setForeground(0, QColor(130, 130, 130));
            }

          itemMap[pChild] = pObj;
        }

      pItem->setExpanded(true);
    }

  if (flagGlobalQuantities && pModel->getModelValues().size())
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem((QTreeWidget*)NULL, 1000);
      pItem->setText(0, "Global Quantities");
      pW->addTopLevelItem(pItem);
      pItem->setFirstColumnSpanned(true);

      //QTreeWidgetItem * pChild;
      size_t j, jmax = pModel->getModelValues().size();

      for (j = 0; j < jmax; ++j)
        {
          const CDataObject * pObj = &pModel->getModelValues()[j];
          QTreeWidgetItem * pChild = new QTreeWidgetItem(pItem, 1001);
          pChild->setText(0,  FROM_UTF8(pObj->getObjectName()));
          pChild->setFirstColumnSpanned(true);

          //highlight new objects
          std::set< const CDataObject * >::const_iterator it = added.find(pObj);

          if (it != added.end())
            {
              pChild->setFont(0, tmpFont);
              //pChild->setBackground(0, QColor(200,200,250));
            }

          //highlight objects that are referred to by others
          if (highlightInvolved)
            {
              if (!mex.existDependentEntities(pObj))
                pChild->setForeground(0, QColor(130, 130, 130));
            }

          itemMap[pChild] = pObj;
        }
    }

  if (flagReactions && pModel->getReactions().size())
    {
      pW->setColumnCount(2);

      QTreeWidgetItem * pItem = new QTreeWidgetItem((QTreeWidget*)NULL, 1000);
      pItem->setText(0, "Reactions");
      pW->addTopLevelItem(pItem);
      pItem->setFirstColumnSpanned(true);

      QFont tmpFontSmall = pItem->font(0);
      tmpFontSmall.setPointSize(tmpFontSmall.pointSize() - 2);

      //QTreeWidgetItem * pChild;
      size_t j, jmax = pModel->getReactions().size();

      for (j = 0; j < jmax; ++j)
        {
          const CDataObject * pObj = &pModel->getReactions()[j];
          QTreeWidgetItem * pChild = new QTreeWidgetItem(pItem, 1001);
          pChild->setText(0,  FROM_UTF8(pObj->getObjectName()));
          pChild->setFirstColumnSpanned(false);

          //add the chemical equation (with a smaller font)
          const CReaction * pReaction = dynamic_cast<const CReaction*>(pObj);

          if (pReaction)
            pChild->setText(1, FROM_UTF8(CChemEqInterface::getChemEqString(*pReaction, false)));

          pChild->setFont(1, tmpFontSmall);

          //highlight new objects
          std::set< const CDataObject * >::const_iterator it = added.find(pObj);

          if (it != added.end())
            {
              pChild->setFont(0, tmpFont);
              //pChild->setBackground(0, QColor(200,200,250));
            }

          //highlight objects that are referred to by others
          if (highlightInvolved)
            {
              if (!mex.existDependentEntities(pObj))
                pChild->setForeground(0, QColor(130, 130, 130));

              pChild->setForeground(1, QColor(130, 130, 130));
            }

          itemMap[pChild] = pObj;
        }

      //pW->setCo
    }
}

void CQMergingData::treeSelectionChanged()
{
  // only enable the merging button if the selected items match and are not identical
  const CDataObject* p1 = NULL;
  const CDataObject* p2 = NULL;
  std::map< QTreeWidgetItem *, const CDataObject * >::const_iterator it;
  it = mItemMap1.find(mpTree1->currentItem());

  if (it != mItemMap1.end())
    p1 = it->second;

  it = mItemMap2.find(mpTree2->currentItem());

  if (it != mItemMap2.end())
    p2 = it->second;

  if (!p1 || !p2 || p1->getObjectType() != p2->getObjectType() || p1 == p2)
    mpBtnMerge->setEnabled(false);
  else
    mpBtnMerge->setEnabled(true);
}

void CQMergingData::load()
{

  assert(mpModel != NULL);
  mpModel->compileIfNecessary(NULL);

  fillTree(mpTree1, mpModel, mItemMap1, true, true, mpModel->getObjectDataModel()->mLastAddedObjects, true);
  fillTree(mpTree2, mpModel, mItemMap2, true, true, mpModel->getObjectDataModel()->mLastAddedObjects, false);

  treeSelectionChanged();
}

void CQMergingData::slotBtnMerge()
{
  //simple, preliminary
  const CDataObject* p1 = NULL;
  const CDataObject* p2 = NULL;

  std::map< QTreeWidgetItem *, const CDataObject * >::const_iterator it;
  it = mItemMap1.find(mpTree1->currentItem());

  if (it != mItemMap1.end())
    p1 = it->second;

  it = mItemMap2.find(mpTree2->currentItem());

  if (it != mItemMap2.end())
    p2 = it->second;

  /*  for (it=mItemMap1.begin(); it != mItemMap1.end(); ++it)
      {
      if (it->first->checkState(0)==Qt::Checked)
        {
        p1=it->second;
        break;
        }
      }
    for (it=mItemMap2.begin(); it != mItemMap2.end(); ++it)
      {
      if (it->first->checkState(0)==Qt::Checked)
        {
        p2=it->second;
        break;
        }
      }*/

  //check if the replacement matches in type
  if (!p1 || !p2 || p1->getObjectType() != p2->getObjectType())
    return;

  //TODO it would be better to check this constantly and disable the merge button accordingly

  CModelExpansion expa(mpModel);
  CModelExpansion::ElementsMap emap;
  emap.add(p1, p2);
  expa.replaceInModel(emap, true); //true means remove replaced items

  //CModelMerging merging(pModel);
  //merging.simpleCall(mColumnKey, mObjectKey);

  load();

  //accept();
}

void CQMergingData::slotBtnCancel()
{
  //this is actually not "Cancel", but "Done"
  accept();
}
