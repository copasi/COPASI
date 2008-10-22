// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiSelectionDialog.cpp,v $
//   $Author: ssahle $
//   $Date: 2008/10/22 19:53:48 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "qpushbutton.h"
#include "qcheckbox.h"
#include "qhbox.h"
#include "qvbox.h"
#include "qlayout.h"
#include <qcombobox.h>

#include "CCopasiSelectionDialog.h"
#include "CCopasiSelectionWidget.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"

#include "qtUtilities.h"
#include "utilities/CAnnotatedMatrix.h"
#include "model/CModel.h"
#include "CQMatrixDialog.h"
#include "CQMessageBox.h"

CCopasiSelectionDialog::CCopasiSelectionDialog(QWidget * parent , const char * name , bool modal):
    QDialog(parent, name, modal),
    mpOKButton(NULL),
    mpCancelButton(NULL),
    mpModeCheckBox(NULL),
    mpButtonBox(NULL),
    mpMainWidget(NULL),
    mpMainLayout(NULL),
    mpTmpVector(new std::vector< const CCopasiObject * >()),
    mpOutputVector(NULL),
    mExpertMode(false),
    mExpertModeEnabled(true)
{
  setWFlags(this->getWFlags() | Qt::WDestructiveClose);
  mpMainLayout = new QVBoxLayout(this);

  mpSelectionWidget = new CCopasiSelectionWidget(this);
  mpMainLayout->addWidget(mpSelectionWidget);

  mpButtonBox = new QHBoxLayout(mpMainLayout);

  mpOKButton = new QPushButton(this, "OK");
  mpOKButton->setText("OK");
  mpOKButton->setDefault(true);
  mpOKButton->setAutoDefault(true);
  mpButtonBox->addWidget(mpOKButton);

  mpCancelButton = new QPushButton(this, "Cancel");
  mpCancelButton->setText("Cancel");
  mpButtonBox->addWidget(mpCancelButton);

  mpModeCheckBox = new QCheckBox("expert mode", this, "expertMode");
  mpModeCheckBox->setChecked(false);
  mpButtonBox->addWidget(mpModeCheckBox);

  // this->mpButtonBox->addSpacing(20);
  // this->mpButtonBox->addStretch();

  connect(this->mpOKButton, SIGNAL(clicked()), this, SLOT(okButton_clicked()));
  connect(this->mpCancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));
  connect(this->mpModeCheckBox, SIGNAL(toggled(bool)), this, SLOT(modeButton_toggled(bool)));

  this->mpSelectionWidget->setOutputVector(NULL);

  this->setTabOrder(this->mpOKButton, this->mpCancelButton);
  this->setTabOrder(this->mpCancelButton, this->mpModeCheckBox);
  this->setTabOrder(this->mpModeCheckBox, this->mpMainWidget);
}

CCopasiSelectionDialog::~CCopasiSelectionDialog()
{
  delete mpTmpVector;
}

void CCopasiSelectionDialog::setModel(const CModel* pModel,
                                      const CCopasiSimpleSelectionTree::SelectionFlag & flag)
{
  this->mpSelectionWidget->populateTree(pModel, flag);
}

void CCopasiSelectionDialog::setOutputVector(std::vector< const CCopasiObject * > * outputVector)
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

const CCopasiObject *
CCopasiSelectionDialog::getObjectSingle(QWidget * parent,
                                        const CCopasiSimpleSelectionTree::SelectionFlag & flag,
                                        const CCopasiObject * pCurrentObject)
{
  std::vector< const CCopasiObject * > Selection;

  if (pCurrentObject != NULL)
    Selection.push_back(pCurrentObject);

  CCopasiSelectionDialog * pDialog = new CCopasiSelectionDialog(parent);
  pDialog->setModel(CCopasiDataModel::Global->getModel(), flag);
  pDialog->setSingleSelection(true);
  pDialog->setOutputVector(&Selection);

  //std::cout << "Size = " << Selection.size() << std::endl;
  //std::cout << "parent: " << parent->name() << " - class: " << parent->className() << std::endl;

  int Result = pDialog->exec();

  if (Result == QDialog::Accepted && Selection.size() != 0)
    {
      const CCopasiObject *pObject = Selection[0];
      const CArrayAnnotation * pArray;

      // if the selected object is an array then select firstly one cell of it
      if ((pArray = dynamic_cast< const CArrayAnnotation * >(pObject)))
        {
          //std::cout << "pArray->getCN() = " << pArray->getCN() << std::endl;

          if (flag == CCopasiSimpleSelectionTree::OPTIMIZATION_EXPRESSION ||
              flag == CCopasiSimpleSelectionTree::SENSITIVITY_VARIABLE ||
              flag == CCopasiSimpleSelectionTree::PLOT_OBJECT)
            pObject = chooseCellMatrix(pArray, true, true)[0];

          if (!pObject) return NULL;
        }

      // just only show the object value
      /*
      C_FLOAT64 *pValue = (C_FLOAT64 *) pObject->getValuePointer();
      if (pValue != NULL)
      std::cout << "value = " << *pValue << std::endl;
      */
      return pObject;
    }

  if (Result == QDialog::Rejected && pCurrentObject != NULL)
    return pCurrentObject;

  return NULL;
}

std::vector< const CCopasiObject * > CCopasiSelectionDialog::getObjectVector(QWidget * parent,
    const CCopasiSimpleSelectionTree::SelectionFlag & flag,
    const std::vector< const CCopasiObject * > * pCurrentSelection)
{
  std::vector< const CCopasiObject * > Selection;
  if (pCurrentSelection)
    Selection = *pCurrentSelection;

  CCopasiSelectionDialog * pDialog = new CCopasiSelectionDialog(parent);
  pDialog->setModel(CCopasiDataModel::Global->getModel(), flag);
  pDialog->setSingleSelection(false);
  pDialog->setOutputVector(&Selection);

  //std::cout << "Parent widget = " << parent->className() << " - " << parent->name() << std::endl;

  if (pDialog->exec() == QDialog::Rejected && pCurrentSelection)
    return *pCurrentSelection;
  else
    //    return Selection;
    {
      if (flag == CCopasiSimpleSelectionTree::REPORT_ITEM)
        {
          std::vector<const CCopasiObject *> newSelection;

          std::vector< const CCopasiObject * >::iterator itSelection = Selection.begin();
          for (; itSelection != Selection.end(); ++itSelection)
            {
              // if the current object is an array then select firstly one cell of it
              const CArrayAnnotation * pArray;
              if ((pArray = dynamic_cast< const CArrayAnnotation * >(*itSelection)))
                {
                  // second parameter is false in order 'ALL' options on the matrix dialog to appear
                  std::vector<const CCopasiObject *> tmp = chooseCellMatrix(pArray, false, true); //TODO value flag
                  std::vector<const CCopasiObject *>::const_iterator tmpit, tmpitEnd = tmp.end();
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
      return Selection;
    }

  //  return Selection;
}

std::vector<const CCopasiObject*>
CCopasiSelectionDialog::chooseCellMatrix(const CArrayAnnotation * pArrayAnnotation, bool single, bool value, std::string caption)
{
  CQMatrixDialog * pDialog = new CQMatrixDialog();

  pDialog->setCaption(tr(FROM_UTF8(caption) + "Cell Selection of " + FROM_UTF8(pArrayAnnotation->getObjectName())));
  pDialog->setArray(pArrayAnnotation, single);

  std::vector< const CCopasiObject* > returnVector;
  if (single)
    returnVector.resize(1);
  else
    returnVector.resize(0);

  int Result = pDialog->exec();

  if (Result == QDialog::Accepted)
    {
      CCopasiAbstractArray::index_type index;
      index.resize(pArrayAnnotation->dimensionality());
      if (index.size() > 2)
        CQMessageBox::warning(0, "Dimensionality Problem", "Need more handle for high dimension of array",
                              QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

      if (single)
        {
          // single cell selection
          if (value)
            {
              index[0] = pDialog->mpCBRow->currentItem();
              index[1] = pDialog->mpCBColumn->currentItem();
              /*
                  C_FLOAT64 value = (*pArrayAnnotation->array())[index];
                  std::cout << "its value = " << value << std::endl;
              */
              returnVector[0] = pArrayAnnotation->addElementReference(index);
            }

          return returnVector;
        }

      // multi cell selection

      //if "All" is selected for both rows and columns, and an object with numerical value
      //is not requested,, return the array annotation as such
      if (pDialog->mpCBRow->currentItem() == 0 && pDialog->mpCBColumn->currentItem() == 0
          && !value)
        {
          // whole matrix should be chosen -> the object itself will be returned
          //std::cout << "whole matrix should be chosen" << std::endl;
          returnVector.resize(1);
          returnVector[0] = (CCopasiObject *) pArrayAnnotation;
          return returnVector;
        }

      int minRows, maxRows, minCols, maxCols;
      int i, j;

      if (pDialog->mpCBRow->currentItem())
        {
          // not ALL option
          minRows = pDialog->mpCBRow->currentItem() - 1;
          maxRows = minRows + 1;
        }
      else
        {
          // ALL option
          minRows = 0;
          maxRows = pArrayAnnotation->size()[0];
        }

      if (pDialog->mpCBColumn->currentItem())
        {
          // not ALL option
          minCols = pDialog->mpCBColumn->currentItem() - 1;
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
              returnVector.push_back(pArrayAnnotation->addElementReference(i, j));
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
