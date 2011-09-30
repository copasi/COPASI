// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMathMatrixWidget.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 17:52:38 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include <qpushbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <q3table.h>
//Added by qt3to4:
#include <Q3GridLayout>

#include "copasi.h"

#include "CQMathMatrixWidget.h"
#include "qtUtilities.h"
//#include "sensitivities/CSensTask.h"
//#include "sensitivities/CSensProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
//#include "utilities/CCopasiVector.h"

#include "model/CModel.h"

#include <qtabwidget.h>

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
