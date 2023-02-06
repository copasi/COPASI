// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QPushButton>
#include <QCheckBox>
#include <QLayout>
#include <QComboBox>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include "CCopasiSelectionDialog.h"
#include "CCopasiSelectionWidget.h"
#include "listviews.h"

#include "copasi/copasi.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

#include "qtUtilities.h"
#include "copasi/core/CDataArray.h"
#include "copasi/model/CModel.h"
#include "CQMatrixDialog.h"
#include "CQMessageBox.h"

CCopasiSelectionDialog::CCopasiSelectionDialog(QWidget * parent, const char * name, bool modal):
  QDialog(parent),
  mpModeCheckBox(NULL),
  mpButtonBox(NULL),
  mpMainWidget(NULL),
  mpMainLayout(NULL),
  mpTmpVector(new std::vector< const CDataObject * >()),
  mpOutputVector(NULL),
  mExpertMode(false),
  mExpertModeEnabled(true)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setAttribute(Qt::WA_DeleteOnClose);
  setMinimumHeight(480);

  mpMainLayout = new QVBoxLayout(this);

  mpSelectionWidget = new CCopasiSelectionWidget(this);
  mpMainLayout->addWidget(mpSelectionWidget);

  mpButtonBox = new QHBoxLayout();
  mpMainLayout->addLayout(mpButtonBox);

  QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal,  this);
  mpButtonBox->addWidget(box);

  mpModeCheckBox = new QCheckBox("expert mode", this);
  mpModeCheckBox->setObjectName("expertMode");
  mpModeCheckBox->setChecked(false);
  mpButtonBox->addWidget(mpModeCheckBox);

  // this->mpButtonBox->addSpacing(20);
  // this->mpButtonBox->addStretch();

  connect(box, SIGNAL(accepted()), this, SLOT(okButton_clicked()));
  connect(mpSelectionWidget, SIGNAL(selectionCommitted()), this, SLOT(okButton_clicked()));
  connect(box, SIGNAL(rejected()), this, SLOT(cancelButton_clicked()));
  connect(this->mpModeCheckBox, SIGNAL(toggled(bool)), this, SLOT(modeButton_toggled(bool)));

  this->mpSelectionWidget->setOutputVector(NULL);

  this->setTabOrder(this->mpModeCheckBox, this->mpMainWidget);
}

CCopasiSelectionDialog::~CCopasiSelectionDialog()
{
  delete mpTmpVector;
}

void CCopasiSelectionDialog::setFilter(const CQSimpleSelectionTree::ObjectClasses & classes)
{
  CDataModel * pDataModel = ListViews::dataModel(this);
  assert(pDataModel != NULL);

  this->mpSelectionWidget->populateTree(pDataModel->getModel(), classes);
}

void CCopasiSelectionDialog::setValidObjects(const std::vector< const CDataObject * > & objectList)
{
  this->mpSelectionWidget->populateTree(objectList);
}

void CCopasiSelectionDialog::setOutputVector(std::vector< const CDataObject * > * outputVector)
{
  this->mpSelectionWidget->setOutputVector(outputVector);
}

void CCopasiSelectionDialog::okButton_clicked()
{
  // fill outputVector
  this->mpSelectionWidget->commit();
  done(QDialog::Accepted);
}

void CCopasiSelectionDialog::cancelButton_clicked()
{
  done(QDialog::Rejected);
}

void CCopasiSelectionDialog::modeButton_toggled(bool checked)
{
  this->mpSelectionWidget->setExpertMode(checked);
}

void CCopasiSelectionDialog::setSingleSelection(bool singleSelectionMode)
{
  this->mpSelectionWidget->setSingleSelection(singleSelectionMode);
}

void CCopasiSelectionDialog::enableExpertMode(bool enable)
{
  if (enable == this->mExpertModeEnabled) return;

  this->mExpertModeEnabled = enable;

  if (!this->mExpertModeEnabled)
    {
      this->mpModeCheckBox->setChecked(false);
      this->mpModeCheckBox->hide();
    }
  else
    {
      this->mpModeCheckBox->show();
    }
}

void CCopasiSelectionDialog::setAllowExpressions(bool allowExpressions)
{
  mpSelectionWidget->setAllowExpressions(allowExpressions);
}

const CDataObject *
CCopasiSelectionDialog::getObjectSingle(QWidget * parent,
                                        const CQSimpleSelectionTree::ObjectClasses & classes,
                                        const CDataObject * pCurrentObject,
                                        bool allowExpressions)
{
  std::vector< const CDataObject * > Selection;

  if (pCurrentObject != NULL)
    Selection.push_back(pCurrentObject);

  CCopasiSelectionDialog * pDialog = new CCopasiSelectionDialog(parent);
  pDialog->setWindowTitle("Select Item");
  pDialog->setFilter(classes);
  pDialog->setSingleSelection(true);
  pDialog->setOutputVector(&Selection);
  pDialog->setAllowExpressions(allowExpressions);

  int Result = pDialog->exec();

  if (Result == QDialog::Accepted && Selection.size() != 0)
    {
      const CDataObject *pObject = Selection[0];
      const CDataArray * pArray;

      // if the selected object is an array then select firstly one cell of it
      if ((pArray = dynamic_cast< const CDataArray * >(pObject)))
        {
          pObject = chooseCellMatrix(pArray, true, true)[0];

          if (!pObject) return NULL;
        }

      return pObject;
    }

  if (Result == QDialog::Rejected && pCurrentObject != NULL)
    return pCurrentObject;

  return NULL;
}

std::vector< const CDataObject * > CCopasiSelectionDialog::getObjectVector(QWidget * parent,
    const CQSimpleSelectionTree::ObjectClasses & classes,
    const std::vector< const CDataObject * > * pCurrentSelection)
{
  std::vector< const CDataObject * > Selection;

  if (pCurrentSelection)
    Selection = *pCurrentSelection;

  CCopasiSelectionDialog * pDialog = new CCopasiSelectionDialog(parent);
  pDialog->setWindowTitle("Select Items");
  pDialog->setToolTip("Select multiple items by holding down the Ctrl or Shift (or equivalent) key.");
  pDialog->setFilter(classes);
  pDialog->setSingleSelection(false);
  pDialog->setOutputVector(&Selection);

  if (pDialog->exec() == QDialog::Rejected && pCurrentSelection)
    return *pCurrentSelection;
  else
    //    return Selection;
    {
      std::vector<const CDataObject *> newSelection;

      std::vector< const CDataObject * >::iterator itSelection = Selection.begin();

      for (; itSelection != Selection.end(); ++itSelection)
        {
          // if the current object is an array then select firstly one cell of it
          const CDataArray * pArray;

          if ((pArray = dynamic_cast< const CDataArray * >(*itSelection)))
            {
              // second parameter is false in order 'ALL' options on the matrix dialog to appear
              std::vector<const CDataObject *> tmp = chooseCellMatrix(pArray, false, true); //TODO value flag
              std::vector<const CDataObject *>::const_iterator tmpit, tmpitEnd = tmp.end();

              for (tmpit = tmp.begin(); tmpit != tmpitEnd; ++tmpit)
                newSelection.push_back(*tmpit);
            }
          // otherwise, just put it into newSelection
          else
            {
              newSelection.push_back(*itSelection);
            }
        }

      return newSelection;
    }

  //  return Selection;
}

std::vector< const CDataObject * > CCopasiSelectionDialog::getObjectVector(QWidget * parent,
    const std::vector< const CDataObject * > & objectList,
    const std::vector< const CDataObject * > * pCurrentSelection)
{
  std::vector< const CDataObject * > Selection;

  if (pCurrentSelection)
    Selection = *pCurrentSelection;

  CCopasiSelectionDialog * pDialog = new CCopasiSelectionDialog(parent);
  pDialog->setWindowTitle("Select Items");
  pDialog->setToolTip("Select multiple items by holding down the Ctrl or Shift (or equivalent) key.");
  assert(CRootContainer::getDatamodelList()->size() > 0);
  pDialog->enableExpertMode(false);
  pDialog->setValidObjects(objectList);
  pDialog->setSingleSelection(false);
  pDialog->setOutputVector(&Selection);

  if (pDialog->exec() == QDialog::Rejected)
    {
      return Selection;
    }

  std::vector<const CDataObject *> newSelection;
  std::vector< const CDataObject * >::iterator itSelection = Selection.begin();
  std::vector< const CDataObject * >::iterator endSelection = Selection.end();

  for (; itSelection != endSelection; ++itSelection)
    {
      // if the current object is an array then select firstly one cell of it
      const CDataArray * pArray;

      if ((pArray = dynamic_cast< const CDataArray * >(*itSelection)))
        {
          // second parameter is false in order 'ALL' options on the matrix dialog to appear
          std::vector<const CDataObject *> tmp = chooseCellMatrix(pArray, false, true); //TODO value flag
          std::vector<const CDataObject *>::const_iterator tmpit, tmpitEnd = tmp.end();

          for (tmpit = tmp.begin(); tmpit != tmpitEnd; ++tmpit)
            newSelection.push_back(*tmpit);
        }
      // otherwise, just put it into newSelection
      else
        {
          newSelection.push_back(*itSelection);
        }
    }

  return newSelection;
}

std::vector<const CDataObject*>
CCopasiSelectionDialog::chooseCellMatrix(const CDataArray * pArrayAnnotation, bool single, bool value, std::string caption)
{
  std::vector< const CDataObject* > returnVector;

  if (single)
    {returnVector.resize(1); returnVector[0] = NULL;}
  else
    returnVector.resize(0);

  if (!pArrayAnnotation) return returnVector;

  //handle zero-dimensional array
  if (pArrayAnnotation->size().size() == 0)
    {
      CArrayInterface::index_type index;
      index.resize(0);
      returnVector.resize(1);
      returnVector[0] = static_cast< const CDataObject * >(pArrayAnnotation->addElementReference(index));
      return returnVector;
    }

  CQMatrixDialog * pDialog = new CQMatrixDialog();

  pDialog->setWindowTitle(tr(TO_UTF8(FROM_UTF8(caption) + "Cell Selection of " + FROM_UTF8(pArrayAnnotation->getObjectName()))));
  pDialog->setArray(pArrayAnnotation, single);

  int Result = pDialog->exec();

  if (Result == QDialog::Accepted)
    {
      CArrayInterface::index_type index;
      index.resize(pArrayAnnotation->dimensionality());

      if (index.size() > 2)
        CQMessageBox::warning(0, "Dimensionality Problem", "Need more handle for high dimension of array",
                              QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

      if (single)
        {
          // single cell selection
          if (value)
            {
              index[0] = pDialog->mpCBRow->currentIndex();

              if (index.size() > 1)
                index[1] = pDialog->mpCBColumn->currentIndex();

              returnVector[0] = static_cast< const CDataObject * >(pArrayAnnotation->addElementReference(index));
            }

          return returnVector;
        }

      // multi cell selection

      //if "All" is selected for both rows and columns, and an object with numerical value
      //is not requested, return the array annotation as such
      if (pDialog->mpCBRow->currentIndex() == 0 && pDialog->mpCBColumn->currentIndex() == 0
          && !value)
        {
          // whole matrix should be chosen -> the object itself will be returned
          returnVector.resize(1);
          returnVector[0] = (CDataObject *) pArrayAnnotation;
          return returnVector;
        }

      size_t minRows, maxRows, minCols, maxCols;
      size_t i, j;

      if (pDialog->mpCBRow->currentIndex())
        {
          // not ALL option
          minRows = pDialog->mpCBRow->currentIndex() - 1;
          maxRows = minRows + 1;
        }
      else
        {
          // ALL option
          minRows = 0;
          maxRows = pArrayAnnotation->size()[0];
        }

      if (index.size() == 2)
        {
          if (pDialog->mpCBColumn->currentIndex())
            {
              // not ALL option
              minCols = pDialog->mpCBColumn->currentIndex() - 1;
              maxCols = minCols + 1;
            }
          else
            {
              // ALL option
              minCols = 0;
              maxCols = pArrayAnnotation->size()[1];
            }

          for (i = minRows; i < maxRows; ++i)
            {
              for (j = minCols; j < maxCols; ++j)
                {
                  returnVector.push_back(static_cast< const CDataObject * >(pArrayAnnotation->addElementReference((int) i, (int) j)));
                }
            }
        }

      if (index.size() == 1)
        {
          for (i = minRows; i < maxRows; ++i)
            {
              returnVector.push_back(static_cast< const CDataObject * >(pArrayAnnotation->addElementReference((int) i)));
            }
        }

      return returnVector;
    }

  else
    {
      // Rejected case
      if (single)
        returnVector[0] = NULL;

      return returnVector;
    }
}
