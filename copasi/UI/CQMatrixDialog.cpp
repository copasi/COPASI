// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include <QtCore/QVariant>

#include "CQMatrixDialog.h"

#include "copasi/copasi.h"
#include "qtUtilities.h"

#include "copasi/core/CDataArray.h"

/*
 *  Constructs a CQMatrixDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQMatrixDialog::CQMatrixDialog(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
  : QDialog(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMatrixDialog::~CQMatrixDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQMatrixDialog::setArray(const CDataArray *tmp, bool single)
{
  size_t i;

  mpLabelRow->setText("Rows : " + FROM_UTF8(tmp->getDimensionDescription(0)));
  size_t nRows = tmp->size()[0];

  if (!single)
    mpCBRow->insertItem(mpCBRow->count(), "ALL");

  if (FROM_UTF8(tmp->getObjectName()).contains("Eigenvalues"))
    {
      for (i = 0; i < nRows; i++)
        mpCBRow->insertItem(mpCBRow->count(), QString::number(i + 1));
    }
  else
    {
      const std::vector<std::string> & Items = tmp->getAnnotationsString(0, true);

      for (i = 0; i < nRows; i++)
        mpCBRow->insertItem(mpCBRow->count(), FROM_UTF8(Items[i]));
    }

  mpLabelColumn->hide();
  mpCBColumn->hide();

  mpLabelDim3->hide();
  mpCBDim3->hide();

  if (tmp->dimensionality() > 1)
    {
      mpLabelColumn->show();
      mpCBColumn->show();

      mpLabelColumn->setText("Columns : " + FROM_UTF8(tmp->getDimensionDescription(1)));
      size_t nCols = tmp->size()[1];

      if (!single)
        mpCBColumn->insertItem(mpCBColumn->count(), "ALL");

      if (FROM_UTF8(tmp->getObjectName()).contains("Eigenvalues"))
        {
          mpCBColumn->insertItem(mpCBColumn->count(), "Real part");
          mpCBColumn->insertItem(mpCBColumn->count(), "Imaginary part");
        }
      else
        {
          const std::vector<std::string> & Items = tmp->getAnnotationsString(1, true);

          for (i = 0; i < nCols; i++)
            mpCBColumn->insertItem(mpCBColumn->count(), FROM_UTF8(Items[i]));
        }

      if (tmp->dimensionality() == 3)
        {
          mpLabelDim3->show();
          mpCBDim3->show();

          mpLabelDim3->setText("Dimension : " + FROM_UTF8(tmp->getDimensionDescription(2)));
          size_t nDims = tmp->size()[2];

          if (!single)
            mpCBDim3->insertItem(mpCBDim3->count(), "ALL");

          const std::vector<std::string> & Items = tmp->getAnnotationsString(2, true);

          for (i = 0; i < nDims; i++)
            mpCBDim3->insertItem(mpCBDim3->count(), FROM_UTF8(Items[i]));
        }
    }
}
