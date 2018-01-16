// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQMathMatrixWidget.h"

#include "copasi.h"

#include "qtUtilities.h"

#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CArray.h"
#include "copasi/math/CMathContainer.h"
#include "model/CModel.h"
#include "function/CExpression.h"

//activate display of test of symbolic derivatives
//#define _DERIV_TEST_

/**
 *  Constructs a CQMathMatrixWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQMathMatrixWidget::CQMathMatrixWidget(QWidget* parent)
  : CopasiWidget(parent)
  , mLabelTitle(NULL)
  , mJacobian()
  , mJacobianRed()
  , eigenValues()
  , mpJacobianAnn(NULL)
  , mpJacobianAnnRed(NULL)
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

#ifdef _DERIV_TEST_
  connect(mpDerivButton, SIGNAL(clicked()), this, SLOT(slotDerivButtonPressed()));
#else

  if (mpTabWidget->count())
    mpTabWidget->removeTab(mpTabWidget->count() - 1);

#endif


  mpJacobianAnn = new CDataArray("Jacobian (complete system)", NULL,
                                 new CMatrixInterface<CMatrix<C_FLOAT64> >(&mJacobian), true);
  mpJacobianAnn->setMode(CDataArray::Mode::Objects);
  mpJacobianAnn->setDescription("");
  mpJacobianAnn->setDimensionDescription(0, "Variables of the system, including dependent species");
  mpJacobianAnn->setDimensionDescription(1, "Variables of the system, including dependent species");

  mpJacobianAnnotationWidget->setColorCoding(new CColorScaleBiLog());
  mpJacobianAnnotationWidget->setColorScalingAutomatic(true);
  mpJacobianAnnotationWidget->setLegendEnabled(false);

  mpJacobianAnnRed = new CDataArray("Jacobian (reduced system)", NULL,
                                    new CMatrixInterface<CMatrix<C_FLOAT64> >(&mJacobianRed), true);
  mpJacobianAnnRed->setMode(CDataArray::Mode::Objects);
  mpJacobianAnnRed->setDescription("");
  mpJacobianAnnRed->setDimensionDescription(0, "Independent variables of the system");
  mpJacobianAnnRed->setDimensionDescription(1, "Independent variables of the system");

  mpRedJacobianAnnotationWidget->setColorCoding(new CColorScaleBiLog());
  mpRedJacobianAnnotationWidget->setColorScalingAutomatic(true);
  mpRedJacobianAnnotationWidget->setLegendEnabled(false);

}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMathMatrixWidget::~CQMathMatrixWidget()
{
  pdelete(mpJacobianAnn);
  pdelete(mpJacobianAnnRed);
}

void CQMathMatrixWidget::loadMatrices()
{

  assert(mpDataModel != NULL);
  const CModel* pModel = mpDataModel->getModel();

  const CDataArray * tmp;

  tmp = dynamic_cast<const CDataArray *>
        (pModel->getObject(CCommonName("Array=Stoichiometry(ann)")));
  mpArrayWidget1->setArrayAnnotation(tmp);

  tmp = dynamic_cast<const CDataArray *>
        (pModel->getObject(CCommonName("Array=Reduced stoichiometry(ann)")));
  mpArrayWidget2->setArrayAnnotation(tmp);

  tmp = dynamic_cast<const CDataArray *>
        (pModel->getObject(CCommonName("Array=Link matrix(ann)")));
  mpArrayWidget3->setArrayAnnotation(tmp);

}

void CQMathMatrixWidget::updateJacobianAnnotation(const CModel* pModel)
{
  const CMathContainer& container = pModel->getMathContainer();


  size_t sizeReduced = container.getState(true).size() - container.getCountFixedEventTargets() - 1;
  mJacobianRed.resize(sizeReduced, sizeReduced);
  mJacobianRed = std::numeric_limits<double>::quiet_NaN();
  size_t size = container.getState(false).size() - container.getCountFixedEventTargets() - 1;
  mJacobian.resize(size, size);
  mJacobian = std::numeric_limits<double>::quiet_NaN();

  mpJacobianAnn->resize();
  mpJacobianAnn->setObjectParent(mpDataModel);
  mpJacobianAnnRed->resize();
  mpJacobianAnnRed->setObjectParent(mpDataModel);

  const CMathObject * pObject = container.getMathObject(container.getState(false).array() + container.getCountFixedEventTargets() + 1);
  const CMathObject * pObjectEnd = pObject + sizeReduced;

  size_t i;

  for (i = 0; pObject != pObjectEnd; ++pObject, ++i)
    {
      const CDataObject * pDatabject = pObject->getDataObject()->getObjectParent();

      mpJacobianAnn->setAnnotation(0, i, pDatabject);
      mpJacobianAnn->setAnnotation(1, i, pDatabject);

      mpJacobianAnnRed->setAnnotation(0, i, pDatabject);
      mpJacobianAnnRed->setAnnotation(1, i, pDatabject);
    }

  pObjectEnd += size - sizeReduced;

  for (; pObject != pObjectEnd; ++pObject, ++i)
    {
      const CDataObject * pDataObject = pObject->getDataObject()->getObjectParent();

      mpJacobianAnn->setAnnotation(0, i, pDataObject);
      mpJacobianAnn->setAnnotation(1, i, pDataObject);
    }
}

void CQMathMatrixWidget::clearArrays()
{
  mpArrayWidget1->setArrayAnnotation(NULL);
  mpArrayWidget2->setArrayAnnotation(NULL);
  mpArrayWidget3->setArrayAnnotation(NULL);
  mpJacobianAnnotationWidget->setArrayAnnotation(NULL);
  mpRedJacobianAnnotationWidget->setArrayAnnotation(NULL);
}

//*************************************

bool CQMathMatrixWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                C_UNUSED(action), const std::string & C_UNUSED(key))
{
  clearArrays();
  updateJacobianIfTabSelected();
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

#include <qtablewidget.h>

void CQMathMatrixWidget::slotDerivButtonPressed()
{
#ifdef _DERIV_TEST_
  std::cout << "Deriv" << std::endl;

  assert(mpDataModel != NULL);
  CModel* pModel = mpDataModel->getModel();
  CEvaluationNode* tmpnode = pModel->prepareElasticity(&pModel->getReactions()[0],
                             &pModel->getMetabolites()[0], false);

  CEvaluationNode* tmpnode2 = pModel->prepareElasticity(&pModel->getReactions()[0],
                              &pModel->getMetabolites()[0], true);

  //create empty environment. Variable nodes should not occur in an expression
  std::vector<std::vector<std::string> > env;

  std::string tmpstring = tmpnode->buildMMLString(false, env);
  std::string tmpstring2 = tmpnode2->buildMMLString(false, env);

  mpMML->setBaseFontPointSize(qApp->font().pointSize());
  mpMML->setFontName(QtMmlWidget::NormalFont, qApp->font().family());

  mpMML->setContent(tmpstring.c_str());

  mpMML2->setBaseFontPointSize(qApp->font().pointSize());
  mpMML2->setFontName(QtMmlWidget::NormalFont, qApp->font().family());

  mpMML2->setContent(tmpstring2.c_str());

  QTableWidget * pTable = new QTableWidget(pModel->getReactions().size(), pModel->getMetabolites().size());
  pTable->show();

  int i, imax = pModel->getMetabolites().size();
  int j, jmax = pModel->getReactions().size();

  for (i = 0; i < imax; ++i)
    for (j = 0; j < jmax; ++j)
      {
        //CEvaluationNode* tmpnode = pModel->prepareElasticity(pModel->getReactions()[j],
        //                                                     pModel->getMetabolites()[i], false);

        CEvaluationNode* tmpnode2 = pModel->prepareElasticity(&pModel->getReactions()[j],
                                    &pModel->getMetabolites()[i], true);

        //evaluate
        CExpression * tmpExp = new CExpression("tmp expr", pModel);
        tmpExp->setRoot(tmpnode2);
        tmpExp->compile();
        std::cout << tmpExp->calcValue() << std::endl;

        //create empty environment. Variable nodes should not occur in an expression
        std::vector<std::vector<std::string> > env;

        //std::string tmpstring = tmpnode->buildMMLString(false, env);
        std::string tmpstring2 = tmpnode2->buildMMLString(false, env);

        QtMmlWidget* tmpmml = new QtMmlWidget();
        tmpmml->setBaseFontPointSize(qApp->font().pointSize() - 2);
        tmpmml->setFontName(QtMmlWidget::NormalFont, qApp->font().family());
        tmpmml->setContent(tmpstring2.c_str());
        pTable->setCellWidget(j, i, tmpmml);

        //tmpmml = new QtMmlWidget();
        //tmpmml->setBaseFontPointSize(qApp->font().pointSize()-2);
        //tmpmml->setFontName(QtMmlWidget::NormalFont, qApp->font().family());
        //tmpmml->setContent(tmpstring.c_str());
        //pTable->setCellWidget(i, 1, tmpmml);
      }

  pTable->resizeColumnsToContents();
  pTable->resizeRowsToContents();
#endif
}

void CQMathMatrixWidget::slotActiveTabChanged(int index)
{
  updateJacobianIfTabSelected();
}

void CQMathMatrixWidget::updateJacobianIfTabSelected()
{
  if (mpDataModel == NULL)
    return;

  CModel* pModel = mpDataModel->getModel();

  if (pModel == NULL)
    return;

  updateJacobianAnnotation(pModel);

  CMathContainer& container = pModel->getMathContainer();

  if (mpTabWidget->currentWidget() == mpTabWidgetJac)
    {
      calculateJacobian(mJacobian, &container, tableEigenValues, false, 1e-6);
      mpJacobianAnnotationWidget->setArrayAnnotation(mpJacobianAnn);
    }
  else if (mpTabWidget->currentWidget() == mpTabWidgetJacRed)
    {
      calculateJacobian(mJacobianRed, &container, tableEigenValuesRed, true, 1e-6);
      mpRedJacobianAnnotationWidget->setArrayAnnotation(mpJacobianAnnRed);
    }
}

void CQMathMatrixWidget::calculateJacobian(CMatrix< C_FLOAT64 >& matrix,
    CMathContainer* pContainer,
    QTableWidget* eigenValuesWidget,
    bool reduced,
    C_FLOAT64 derivationFactor)
{
  QTableWidgetItem * pItem;

  //Eigenvalues...
  pContainer->calculateJacobian(matrix, derivationFactor, reduced);

  eigenValues.calcEigenValues(matrix);
  const CVector< C_FLOAT64 > & eigen_r = eigenValues.getR();
  const CVector< C_FLOAT64 > & eigen_i = eigenValues.getI();

  eigenValuesWidget->clearContents();
  eigenValuesWidget->setSortingEnabled(reduced);

  size_t i, imax = eigen_i.size();
  eigenValuesWidget->setRowCount((int)imax);

  for (i = 0; i < imax; ++i)
    {
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, eigen_r[i]);
      eigenValuesWidget->setItem((int)i, 0, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, eigen_i[i]);
      eigenValuesWidget->setItem((int)i, 1, pItem);
    }

  eigenValuesWidget->resizeColumnsToContents();
  eigenValuesWidget->resizeRowsToContents();
  eigenValuesWidget->setSortingEnabled(true);
}

