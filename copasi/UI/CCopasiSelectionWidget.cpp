/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiSelectionWidget.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/01/19 13:51:21 $
   End CVS Header */

#include <iostream>

#include "CCopasiSelectionWidget.h"
#include "ObjectBrowserWidget.h"
#include "CCopasiSimpleSelectionTree.h"

#include "copasi.h"

CCopasiSelectionWidget::CCopasiSelectionWidget(QWidget* parent , const char* name , WFlags fl): QWidgetStack(parent, name, fl), mpSimpleTree(NULL), mpObjectBrowser(NULL), mpOutputVector(NULL)
{
  this->mpSimpleTree = new CCopasiSimpleSelectionTree(this);
  this->addWidget(this->mpSimpleTree);
  this->setSingleSelection(false);
  this->setExpertMode(false);
}

CCopasiSelectionWidget::~CCopasiSelectionWidget()
{
  pdelete(mpObjectBrowser);
  delete mpSimpleTree;
}

void CCopasiSelectionWidget::populateTree(const CModel * model)
{
  this->mpSimpleTree->populateTree(model);
}

void CCopasiSelectionWidget::setOutputVector(std::vector<CCopasiObject *> * outputVector)
{
  this->mpOutputVector = outputVector;
  if (this->mExpertMode)
    {
      this->mpObjectBrowser->setOutputVector(this->mpOutputVector);
    }
  else
    {
      this->mpSimpleTree->setOutputVector(this->mpOutputVector);
    }
}

void CCopasiSelectionWidget::setSingleSelection(bool singleSelection)
{
  if (this->mSingleSelect == singleSelection) return;
  this->mSingleSelect = singleSelection;
  this->mpSimpleTree->clearSelection();
  if (this->mSingleSelect)
    {
      this->mpSimpleTree->setSelectionMode(QListView::Single);
      if (this->mpObjectBrowser)
        {
          /* this needs to be implemented first !

             this->mpObjectBrowser->setSingleSelection(true);

           */
        }
    }
  else
    {
      this->mpSimpleTree->setSelectionMode(QListView::Extended);
      if (this->mpObjectBrowser)
        {
          /* this needs to be implemented first !

             this->mpObjectBrowser->setSingleSelection(true);

           */
        }
    }
}

bool CCopasiSelectionWidget::isSingleSelection() const
  {
    return this->mSingleSelect;
  }

void CCopasiSelectionWidget::setExpertMode(bool expertMode)
{
  if (this->mExpertMode == expertMode) return;
  this->mExpertMode = expertMode;
  if (this->mExpertMode)
    {
      if (!this->mpObjectBrowser)
        {
          // create the object browser only if needed
          // this saves some time if the model is large
          this->mpObjectBrowser = new ObjectBrowserWidget(this);
          this->addWidget(this->mpObjectBrowser);
        }
      this->mpSimpleTree->commitClicked();
      this->mpSimpleTree->setOutputVector(NULL);
      this->mpObjectBrowser->setOutputVector(this->mpOutputVector);
      this->raiseWidget(this->mpObjectBrowser);
    }
  else
    {
      // activate the SimpleTree and get the selection from the ObjectBrowser if there is one
      if (this->mpObjectBrowser)
        {
          this->mpObjectBrowser->commitClicked();
          this->mpObjectBrowser->setOutputVector(NULL);
        }
      this->mpSimpleTree->setOutputVector(this->mpOutputVector);
      this->raiseWidget(this->mpSimpleTree);
    }
}

bool CCopasiSelectionWidget::expertMode() const
  {
    return this->mExpertMode;
  }

void CCopasiSelectionWidget::commit()
{
  if (this->mpOutputVector)
    {
      if (this->mExpertMode)
        {
          this->mpObjectBrowser->commitClicked();
          if (this->mSingleSelect && this->mpOutputVector->size() > 1)
            {
              CCopasiObject* object = this->mpOutputVector->at(0);
              this->mpOutputVector->clear();
              this->mpOutputVector->push_back(object);
            }
        }
      else
        {
          this->mpSimpleTree->commitClicked();
        }
    }
}
