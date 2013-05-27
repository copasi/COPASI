// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpandModelData.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/16 18:13:47 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModelExpansion.h"
#include "report/CCopasiRootContainer.h"
//#include "UI/CCopasiSelectionDialog.h"

#include "UI/qtUtilities.h"

#include <QString>
#include <QIntValidator>
#include "CQExpandModelData.h"

CQExpandModelData::CQExpandModelData(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);
  
  mpLineEditSizeX->setValidator(new QIntValidator(1, 10000, this));
  mpLineEditSizeY->setValidator(new QIntValidator(1, 10000, this));

  load();
}

CQExpandModelData::~CQExpandModelData()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQExpandModelData::load()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  size_t i, imax = pModel->getCompartments().size();
  for(i=0; i<imax; ++i)
    {
    QTreeWidgetItem * pItem = new QTreeWidgetItem((QTreeWidget*)NULL, 1000);
    pItem->setText(0,  FROM_UTF8(pModel->getCompartments()[i]->getObjectName()));
    pItem->setCheckState(0, Qt::Unchecked);
    mItemCompartmentMap[pItem] = pModel->getCompartments()[i];
    mpTreeWidget->addTopLevelItem(pItem);
    }
  
  connect(mpTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(slotCompartmentActivated(QTreeWidgetItem*, int)));
  
  connect(mpRadioButtonLin, SIGNAL(toggled(bool)), this, SLOT(slotMode()));
  connect(mpRadioButtonRec, SIGNAL(toggled(bool)), this, SLOT(slotMode()));
}

void CQExpandModelData::slotCompartmentActivated(QTreeWidgetItem* pItem, int col)
{
  //only do something if a checkbox in the first column is clicked
  if (col != 0)
    return;
  
  const CCompartment* pComp = NULL;
  std::map<QTreeWidgetItem*, const CCompartment*>::const_iterator it = mItemCompartmentMap.find(pItem);
  if (it != mItemCompartmentMap.end())
    pComp = it->second;
  if (!pComp)
    return;
  
  //checked
  if (pItem->checkState(0) == Qt::Checked)
  {
    size_t i, imax = pComp->getMetabolites().size();
    for(i=0; i<imax; ++i)
    {
      QTreeWidgetItem * pChild = new QTreeWidgetItem(pItem, 1001);
      pChild->setText(0,  FROM_UTF8(pComp->getMetabolites()[i]->getObjectName()));
      pChild->setCheckState(1, Qt::Unchecked);
      mItemMetabMap[pChild]=pComp->getMetabolites()[i];
    }
    pItem->setExpanded(true);
  }
  
  //unchecked
  if (pItem->checkState(0) == Qt::Unchecked)
  {
    //remove children
    size_t i, imax = pItem->childCount();
    for (i=0; i<imax; ++i)
    {
      pItem->removeChild(pItem->child(0));
    }
  }
}


void CQExpandModelData::slotOK()
{
  CModelExpansion::SetOfModelElements modelelements;
  std::set<std::string> metabkeys;
  
  std::map<QTreeWidgetItem*, const CCompartment*>::const_iterator it;
  for (it=mItemCompartmentMap.begin(); it != mItemCompartmentMap.end(); ++it)
  {
    if (it->first->checkState(0)==Qt::Checked)
    { //the compartment is included
      modelelements.addCompartment(it->second);
      
      //check whether diffusion is requested for the metabolites inside
      size_t i;
      for (i=0; i<it->first->childCount(); ++i)
      {
        if (it->first->child(i)->checkState(1)==Qt::Checked)
        {
          std::map<QTreeWidgetItem*, const CMetab*>::const_iterator itMetab = mItemMetabMap.find(it->first->child(i));
          const CMetab* pMetab=NULL;
          if (itMetab != mItemMetabMap.end())
            metabkeys.insert(itMetab->second->getKey());
        }
        
      }
      
      
    }
  }

  CModelExpansion me(pModel);
  modelelements.fillDependencies(pModel);
  
  int multx, multy;
  multx=mpLineEditSizeX->text().toInt();
  multy=mpLineEditSizeY->text().toInt();
  
  if (mpRadioButtonLin->isChecked())
    me.createLinearArray(modelelements, multx, metabkeys);
  else if (mpRadioButtonRec->isChecked())
    me.createRectangularArray(modelelements, multx, multy, metabkeys);
  
  accept();

  
  // std::string name =  static_cast<std::string >(mpBoxCompartmentName->currentText().toUtf8());     //toStdString();

}

void CQExpandModelData::slotCancel()
{
  reject();
}

void CQExpandModelData::slotMode()
{
  if (mpRadioButtonLin->isChecked())
    {
    mpLabelCross->setEnabled(false);
    mpLineEditSizeY->setEnabled(false);
    }
  else if (mpRadioButtonRec->isChecked())
    {
    mpLabelCross->setEnabled(true);
    mpLineEditSizeY->setEnabled(true);
    }
}

