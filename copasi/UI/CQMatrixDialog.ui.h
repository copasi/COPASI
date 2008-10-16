// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMatrixDialog.ui.h,v $
//   $Revision: 1.1.4.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/10/16 08:35:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include "qtUtilities.h"

void CQMatrixDialog::setArray(const CArrayAnnotation *tmp)
{
  int i;

  mpLabelRow->setText("Rows : " + FROM_UTF8(tmp->getDimensionDescription(0)));
  int nRows = tmp->size()[0];

  mpCBRow->insertItem("ALL");
  for (i = 0; i < nRows; i++)
    mpCBRow->insertItem(FROM_UTF8(tmp->getAnnotationsString(0, true)[i]));

  mpLabelColumn->hide();
  mpCBColumn->hide();

  mpLabelDim3->hide();
  mpCBDim3->hide();

  if (tmp->dimensionality() > 1)
    {
      mpLabelColumn->show();
      mpCBColumn->show();

      mpLabelColumn->setText("Columns : " + FROM_UTF8(tmp->getDimensionDescription(1)));
      int nCols = tmp->size()[1];

      mpCBColumn->insertItem("ALL");
      for (i = 0; i < nCols; i++)
        mpCBColumn->insertItem(FROM_UTF8(tmp->getAnnotationsString(1, true)[i]));

      if (tmp->dimensionality() == 3)
        {
          mpLabelDim3->show();
          mpCBDim3->show();

          mpLabelDim3->setText("Dimension : " + FROM_UTF8(tmp->getDimensionDescription(2)));
          int nDims = tmp->size()[2];

          for (i = 0; i < nDims; i++)
            mpCBDim3->insertItem(FROM_UTF8(tmp->getAnnotationsString(2, true)[i]));
        }
    }
}
