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

  load();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMergingData::~CQMergingData()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQMergingData::fillTree(QTreeWidget* pW, const CModel* pModel, std::map<QTreeWidgetItem*, CModelEntity*> & itemMap)
{
  itemMap.clear();
  pW->clear();
  size_t i, imax = pModel->getCompartments().size();
  for(i=0; i<imax; ++i)
    {
    QTreeWidgetItem * pItem = new QTreeWidgetItem((QTreeWidget*)NULL, 1000);
    pItem->setText(0,  FROM_UTF8(pModel->getCompartments()[i]->getObjectName()));
    //pItem->setCheckState(0, Qt::Unchecked);
    itemMap[pItem] = pModel->getCompartments()[i];
    pW->addTopLevelItem(pItem);
    
    QTreeWidgetItem * pChild;
    size_t j, jmax = pModel->getCompartments()[i]->getMetabolites().size();
    for(j=0; j<jmax; ++j)
      {
      QTreeWidgetItem * pChild = new QTreeWidgetItem(pItem, 1001);
      pChild->setText(0,  FROM_UTF8(pModel->getCompartments()[i]->getMetabolites()[j]->getObjectName()));
      //pChild->setCheckState(0, Qt::Unchecked);
      itemMap[pChild]=pModel->getCompartments()[i]->getMetabolites()[j];
      }
    pItem->setExpanded(true);

    }

}

void CQMergingData::load()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);


  mpModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  
  fillTree(mpTree1, mpModel, mItemMap1);
  fillTree(mpTree2, mpModel, mItemMap2);
  
 }

void CQMergingData::slotBtnMerge()
{
  //simple, preliminary
  CModelEntity* p1=NULL;
  CModelEntity* p2=NULL;
  
  std::map<QTreeWidgetItem*, CModelEntity*>::const_iterator it;
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

