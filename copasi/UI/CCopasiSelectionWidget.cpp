// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>

#include "copasi.h"

#include "CCopasiSelectionWidget.h"
#include "ObjectBrowserWidget.h"
#include "CQSimpleSelectionTree.h"

CCopasiSelectionWidget::CCopasiSelectionWidget(QWidget* parent):
  QStackedWidget(parent),
  mpSimpleTree(NULL),
  mpObjectBrowser(NULL),
  mpOutputVector(NULL),
  mSingleSelect(false),
  mExpertMode(false)
{
  this->mpSimpleTree = new CQSimpleSelectionTree(this);
  this->addWidget(this->mpSimpleTree);
  this->setSingleSelection(false);
  this->setExpertMode(false);
}

CCopasiSelectionWidget::~CCopasiSelectionWidget()
{
  pdelete(mpObjectBrowser);
  delete mpSimpleTree;
}

void CCopasiSelectionWidget::populateTree(const CModel * model,
    const CQSimpleSelectionTree::ObjectClasses & classes)
{
  this->mpSimpleTree->populateTree(model, classes);
}

void CCopasiSelectionWidget::setOutputVector(std::vector< const CCopasiObject * > * outputVector)
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
      this->mpSimpleTree->setSelectionMode(QAbstractItemView::SingleSelection);

      if (this->mpObjectBrowser)
        {
          /* this needs to be implemented first !

             this->mpObjectBrowser->setSingleSelection(true);

           */
        }
    }
  else
    {
      this->mpSimpleTree->setSelectionMode(QAbstractItemView::ExtendedSelection);

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
      this->setCurrentWidget(this->mpObjectBrowser);
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
      this->setCurrentWidget(this->mpSimpleTree);
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
              const CCopasiObject * object = this->mpOutputVector->at(0);
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
