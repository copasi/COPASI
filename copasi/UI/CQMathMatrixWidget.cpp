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
#include "function/CExpression.h"

//activate display of test of symbolic derivatives
//#define _DERIV_TEST_

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
  
#ifdef _DERIV_TEST_
  connect(mpDerivButton, SIGNAL(clicked()), this, SLOT(slotDerivButtonPressed()));
#else
  if (mpTabWidget->count())
    mpTabWidget->removeTab(mpTabWidget->count()-1);
#endif

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

#include <qtablewidget.h>

void CQMathMatrixWidget::slotDerivButtonPressed()
{
#ifdef _DERIV_TEST_
  std::cout << "Deriv" << std::endl;
  
  CModel* pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  CEvaluationNode* tmpnode = pModel->prepareElasticity(pModel->getReactions()[0],
                                                       pModel->getMetabolites()[0], false);
  
  CEvaluationNode* tmpnode2 = pModel->prepareElasticity(pModel->getReactions()[0],
                                                       pModel->getMetabolites()[0], true);
  
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
  
  
  QTableWidget * pTable = new QTableWidget(pModel->getReactions().size(),pModel->getMetabolites().size());
  pTable->show();
  
  int i, imax= pModel->getMetabolites().size();
  int j, jmax= pModel->getReactions().size();
  for (i=0; i<imax; ++i)
  for (j=0; j<jmax; ++j)
    {
    //CEvaluationNode* tmpnode = pModel->prepareElasticity(pModel->getReactions()[j],
    //                                                     pModel->getMetabolites()[i], false);
    
    CEvaluationNode* tmpnode2 = pModel->prepareElasticity(pModel->getReactions()[j],
                                                          pModel->getMetabolites()[i], true);
    
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
    tmpmml->setBaseFontPointSize(qApp->font().pointSize()-2);
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


