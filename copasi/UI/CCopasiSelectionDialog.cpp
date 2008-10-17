// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiSelectionDialog.cpp,v $
//   $Revision: 1.14.4.6 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/17 17:13:41 $
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

  std::cout << "Size = " << Selection.size() << std::endl;

  int Result = pDialog->exec();

  if (Result == QDialog::Accepted && Selection.size() != 0)
    {
      const CCopasiObject *pObject = Selection[0];;
      const CArrayAnnotation * pArray;

      if ((pArray = dynamic_cast< const CArrayAnnotation * >(pObject)))
        pObject = chooseCellMatrix(pArray, true, true)[0];

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

  if (pDialog->exec() == QDialog::Rejected && pCurrentSelection)
    return *pCurrentSelection; // TO DO: What is different between *pCurrentSelection and Selection ??
  else
    //    return Selection;
    {

      std::vector<const CCopasiObject *> newSelection;

      std::vector< const CCopasiObject * >::iterator itSelection = Selection.begin();
      for (; itSelection != Selection.end(); ++itSelection)
        {
          const CArrayAnnotation * pArray;
          if ((pArray = dynamic_cast< const CArrayAnnotation * >(*itSelection)))
            {
              std::vector<const CCopasiObject *> tmp = chooseCellMatrix(pArray, true, true); //TODO value flag
              std::vector<const CCopasiObject *>::const_iterator tmpit, tmpitEnd = tmp.end();
              for (tmpit = tmp.begin(); tmpit != tmpitEnd; ++tmpit)
                newSelection.push_back(*tmpit);
            }
          else
            {
              newSelection.push_back(*itSelection);
            }
        }

      return newSelection;
    }
}

std::vector<const CCopasiObject*>
CCopasiSelectionDialog::chooseCellMatrix(const CArrayAnnotation * pArrayAnnotation, bool single, bool value)
{
  CQMatrixDialog * pDialog = new CQMatrixDialog();

  pDialog->setCaption(tr("Cell Selection of " + FROM_UTF8(pArrayAnnotation->getDescription())));
  pDialog->setArray(pArrayAnnotation, single);

  std::vector<const CCopasiObject*> returnvector;
  returnvector.resize(1);

  int Result = pDialog->exec();

  if (Result == QDialog::Accepted)
    {
      CCopasiAbstractArray::index_type index;
      index.resize(pArrayAnnotation->dimensionality());
      index[0] = pDialog->mpCBRow->currentItem() - 1; // "-1 since ALL is always indexed 0 on the combo box
      index[1] = pDialog->mpCBColumn->currentItem() - 1; // "-1 since ALL is always indexed 0 on the combo box

      returnvector[0] = pArrayAnnotation->addElementReference(index);

      return returnvector; //pArrayAnnotation->addElementReference(index);
    }

  return returnvector;
}
