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

#include <QtCore/QString>
#include <QIntValidator>
#include "CQExpandModelData.h"
#include "listviews.h"

#include "copasi/copasi.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModelExpansion.h"
#include "copasi/core/CRootContainer.h"

#include "copasi/UI/qtUtilities.h"
#include "copasi/model/CModel.h"

CQExpandModelData::CQExpandModelData(QWidget* parent, CModel* pModel)
  : QDialog(parent)
{
  setupUi(this);

  mpModel = pModel;

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
  //CDataModel* pDataModel = ListViews::dataModel(parent());
  //assert(pDataModel != NULL);

  //pModel = pDataModel->getModel();

  size_t i, imax = mpModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem((QTreeWidget*)NULL, 1000);
      pItem->setText(0,  FROM_UTF8(mpModel->getCompartments()[i].getObjectName()));
      pItem->setCheckState(0, Qt::Unchecked);
      mItemCompartmentMap[pItem] = &mpModel->getCompartments()[i];
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

      for (i = 0; i < imax; ++i)
        {
          QTreeWidgetItem * pChild = new QTreeWidgetItem(pItem, 1001);
          pChild->setText(0,  FROM_UTF8(pComp->getMetabolites()[i].getObjectName()));
          pChild->setCheckState(1, Qt::Unchecked);
          mItemMetabMap[pChild] = &pComp->getMetabolites()[i];
        }

      pItem->setExpanded(true);
    }

  //unchecked
  if (pItem->checkState(0) == Qt::Unchecked)
    {
      //remove children
      size_t i, imax = pItem->childCount();

      for (i = 0; i < imax; ++i)
        {
          pItem->removeChild(pItem->child(0));
        }
    }
}

void CQExpandModelData::slotOK()
{
  CModelExpansion::SetOfModelElements modelelements;
  std::set< const CDataObject * > Species;

  std::map<QTreeWidgetItem*, const CCompartment*>::const_iterator it;

  for (it = mItemCompartmentMap.begin(); it != mItemCompartmentMap.end(); ++it)
    {
      if (it->first->checkState(0) == Qt::Checked)
        {
          //the compartment is included
          modelelements.addCompartment(it->second);

          //check whether diffusion is requested for the metabolites inside
          size_t i;

          for (i = 0; i < (size_t)it->first->childCount(); ++i)
            {
              if (it->first->child(i)->checkState(1) == Qt::Checked)
                {
                  std::map<QTreeWidgetItem*, const CMetab*>::const_iterator itMetab = mItemMetabMap.find(it->first->child(i));
                  //const CMetab* pMetab = NULL;

                  if (itMetab != mItemMetabMap.end())
                    Species.insert(itMetab->second);
                }
            }
        }
    }

  CModelExpansion me(mpModel);
  modelelements.fillDependencies(mpModel);

  int multx, multy;
  multx = mpLineEditSizeX->text().toInt();
  multy = mpLineEditSizeY->text().toInt();

  if (mpRadioButtonLin->isChecked())
    me.createLinearArray(modelelements, multx, Species);
  else if (mpRadioButtonRec->isChecked())
    me.createRectangularArray(modelelements, multx, multy, Species);

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
