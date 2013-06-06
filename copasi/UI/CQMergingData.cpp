// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMergingData.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/15 17:07:54 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <map>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CMetab.h"
#include "model/CModelValue.h"
#include "model/CModelExpansion.h"
#include "report/CCopasiRootContainer.h"

#include "UI/qtUtilities.h"
#include "resourcesUI/CQIconResource.h"


#include "CQMergingData.h"

class CMetab;
class CModelEntity;


/*
 *  Constructs a CQMergingData which is a child of 'parent', with the
 *  name 'name'.'
 */

CQMergingData::CQMergingData(QWidget* parent, Qt::WindowFlags fl, bool simple)
    : QDialog(parent, fl)
{
    setupUi(this);
    connect(mpTree1, SIGNAL(currentItemChanged(QTreeWidgetItem * , QTreeWidgetItem *)), this, SLOT(treeSelectionChanged()));
    connect(mpTree2, SIGNAL(currentItemChanged(QTreeWidgetItem * , QTreeWidgetItem *)), this, SLOT(treeSelectionChanged()));

    load();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMergingData::~CQMergingData()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQMergingData::fillTree(QTreeWidget* pW, const CModel* pModel, std::map<QTreeWidgetItem*, CCopasiObject*> & itemMap,
                             const std::set<CCopasiObject*> & added,
                             bool highlightInvolved)
{
    itemMap.clear();
    pW->clear();
    CModelExpansion mex(const_cast<CModel*>(pModel));
    size_t i, imax = pModel->getCompartments().size();
    for(i=0; i<imax; ++i)
      {
        CCopasiObject * pObj = pModel->getCompartments()[i];
        QTreeWidgetItem * pItem = new QTreeWidgetItem((QTreeWidget*)NULL, 1000);
        pItem->setText(0,  FROM_UTF8(pObj->getObjectName()));
        //pItem->setCheckState(0, Qt::Unchecked);
        
        //highlight new objects
        std::set<CCopasiObject*>::const_iterator it = added.find(pObj);
        if (it != added.end())
            pItem->setBackgroundColor(0, QColor(200,200,250));
        
        //highlight objects that are referred to by others
        if (highlightInvolved)
          {
            if (!mex.existDependentEntities(pObj))
                pItem->setTextColor(0, QColor(130,130,130));
          }
        
        itemMap[pItem] = pObj;
        pW->addTopLevelItem(pItem);
        
        QTreeWidgetItem * pChild;
        size_t j, jmax = pModel->getCompartments()[i]->getMetabolites().size();
        for(j=0; j<jmax; ++j)
          {
            pObj = pModel->getCompartments()[i]->getMetabolites()[j];
            QTreeWidgetItem * pChild = new QTreeWidgetItem(pItem, 1001);
            pChild->setText(0,  FROM_UTF8(pObj->getObjectName()));
            //pChild->setCheckState(0, Qt::Unchecked);
            
            //highlight new objects
            std::set<CCopasiObject*>::const_iterator it = added.find(pObj);
            if (it != added.end())
                pChild->setBackgroundColor(0, QColor(200,200,250));

            //highlight objects that are referred to by others
            if (highlightInvolved)
              {
                if (!mex.existDependentEntities(pObj))
                    pChild->setTextColor(0, QColor(130,130,130));
              }
            
            itemMap[pChild]=pObj;
          }
        pItem->setExpanded(true);
        
      }
    
    
}

void CQMergingData::treeSelectionChanged()
{
    // only enable the merging button if the selected items match and are not identical
    CCopasiObject* p1=NULL;
    CCopasiObject* p2=NULL;
    std::map<QTreeWidgetItem*, CCopasiObject*>::const_iterator it;
    it = mItemMap1.find(mpTree1->currentItem());
    if (it != mItemMap1.end())
        p1 = it->second;
    it = mItemMap2.find(mpTree2->currentItem());
    if (it != mItemMap2.end())
        p2 = it->second;
    if (!p1 || !p2 || p1->getObjectType()!=p2->getObjectType() || p1==p2)
        mpBtnMerge->setEnabled(false);
    else
        mpBtnMerge->setEnabled(true);
}

void CQMergingData::load()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);


  mpModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  
  fillTree(mpTree1, mpModel, mItemMap1, (*CCopasiRootContainer::getDatamodelList())[0]->mLastAddedObjects, true);
  fillTree(mpTree2, mpModel, mItemMap2, (*CCopasiRootContainer::getDatamodelList())[0]->mLastAddedObjects, false);
  
    treeSelectionChanged();
 }

void CQMergingData::slotBtnMerge()
{
  //simple, preliminary
  CCopasiObject* p1=NULL;
  CCopasiObject* p2=NULL;
  
  std::map<QTreeWidgetItem*, CCopasiObject*>::const_iterator it;
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
  if (!p1 || !p2 || p1->getObjectType()!=p2->getObjectType())
    return;
  //TODO it would be better to check this constantly and disable the merge button accordingly
  
  //pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
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

