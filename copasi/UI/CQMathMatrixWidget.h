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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQMathMatrixWidget
#define COPASI_CQMathMatrixWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQMathMatrixWidget.h"
#include "copasi/UI/copasiWidget.h"
#include "copasi/steadystate/CEigen.h"

class CDataArray;
class CMathContainer;

class CQMathMatrixWidget : public CopasiWidget, public Ui::CQMathMatrixWidget
{
  Q_OBJECT

public:
  CQMathMatrixWidget(QWidget* parent = 0);
  ~CQMathMatrixWidget();

protected slots:

  /// This contains code for displaying test results for symbolic differentiation
  void slotDerivButtonPressed();

  /// activated when tab changes
  void slotActiveTabChanged(int);

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  /**
   * loads the matrices (except Jacobian) into the widget
   */
  void loadMatrices();

  /**
   * clears all arrays
   */
  void clearArrays();

  /**
  * updates the Jacobian from the current model in case the Jacobian or reduced
  * Jacobian tab is selected
  */
  void updateJacobianIfTabSelected();

  /**
  * updates the labels of the Jacobian matrices
  */
  void updateJacobianAnnotation(const CModel* pModel);

  /**
   * @brief calculates the current Jacobian and updates the widget with the eigenvalues
   * @param matrix the storage for the Jacobian matrix
   * @param pContainer the math container
   * @param eigenValuesWidget the table widget in which to place the eigenvalues
   * @param reduced boolean indicating whether the full or reduced system ought to be used
   * @param derivationFactor the derivation factor for calculation of the Jacobian
   */
  void calculateJacobian(CMatrix< C_FLOAT64 >& matrix,
                         CMathContainer* pContainer,
                         QTableWidget* eigenValuesWidget,
                         bool reduced,
                         double derivationFactor);

  QLabel* mLabelTitle;

  CMatrix< C_FLOAT64 > mJacobian;
  CMatrix< C_FLOAT64 > mJacobianRed;
  CEigen eigenValues;
  CDataArray* mpJacobianAnn;
  CDataArray* mpJacobianAnnRed;
};

#endif // COPASI_CQMathMatrixWidget
