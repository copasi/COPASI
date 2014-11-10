// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQMathMatrixWidget.h"

#include "copasi.h"

#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"

/**
 *  Constructs a CQMathMatrixWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQMathMatrixWidget::CQMathMatrixWidget(QWidget* parent)
  : CopasiWidget(parent)
{
  setupUi(this);

  CColorScaleSimple * tcs = new CColorScaleSimple();
  mpArrayWidget1->setColorCoding(tcs);
  tcs->setMinMax(-1.5, 1.5);
  mpArrayWidget1->setColorScalingAutomatic(false);

  tcs = new CColorScaleSimple();
  mpArrayWidget2->setColorCoding(tcs);
  tcs->setMinMax(-1.5, 1.5);
  mpArrayWidget2->setColorScalingAutomatic(false);

  tcs = new CColorScaleSimple();
  mpArrayWidget3->setColorCoding(tcs);
  tcs->setMinMax(-1.5, 1.5);
  mpArrayWidget3->setColorScalingAutomatic(false);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMathMatrixWidget::~CQMathMatrixWidget()
{}

void CQMathMatrixWidget::loadMatrices()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CModel* pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  const CArrayAnnotation * tmp;

  tmp = dynamic_cast<const CArrayAnnotation *>
        (pModel->getObject(CCopasiObjectName("Array=Stoichiometry(ann)")));
  mpArrayWidget1->setArrayAnnotation(tmp);

  tmp = dynamic_cast<const CArrayAnnotation *>
        (pModel->getObject(CCopasiObjectName("Array=Reduced stoichiometry(ann)")));
  mpArrayWidget2->setArrayAnnotation(tmp);

  tmp = dynamic_cast<const CArrayAnnotation *>
        (pModel->getObject(CCopasiObjectName("Array=Link matrix(ann)")));
  mpArrayWidget3->setArrayAnnotation(tmp);
}

void CQMathMatrixWidget::clearArrays()
{
  mpArrayWidget1->setArrayAnnotation(NULL);
  mpArrayWidget2->setArrayAnnotation(NULL);
  mpArrayWidget3->setArrayAnnotation(NULL);
}

//*************************************

bool CQMathMatrixWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                C_UNUSED(action), const std::string & C_UNUSED(key))
{
  clearArrays();
  return true;
}

bool CQMathMatrixWidget::leave()
{
  return true;
}

bool CQMathMatrixWidget::enterProtected()
{
  loadMatrices();

  return true;
}
