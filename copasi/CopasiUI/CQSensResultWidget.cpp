/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQSensResultWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/18 13:06:03 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include <qpushbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qtable.h>

#include "copasi.h"

#include "CQSensResultWidget.h"
//#include "StateSubwidget.h"
//#include "CTimeSeriesTable.h"
#include "qtUtilities.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"
//#include "report/CKeyFactory.h"
//#include "model/CModel.h"

ArrayAnnotationsWidget::ArrayAnnotationsWidget(QWidget* parent, const char* name, WFlags fl)
    : QVBox(parent, name, fl)
{
  mpSelectionTable = new QTable(this);
  mpContentTable = new QTable(this);
  //set read only
}

ArrayAnnotationsWidget::~ArrayAnnotationsWidget()
{}

void ArrayAnnotationsWidget::setArrayAnnotation(const CArrayAnnotation * pArray)
{
  mpArray = pArray;

  if (!mpArray)
    {
      clearWidget();
      return;
    }

  CCopasiAbstractArray::index_type index; index.resize(mpArray->dimensionality());

  if (mpArray->dimensionality() == 0)
  {}
  else if (mpArray->dimensionality() == 1)
    {
      fillTable(0, index);
    }
  else if (mpArray->dimensionality() == 2)
    {
      fillTable(0, 1, index);
    }
  else
    {
      fillTable(0, 1, index);
    }
}

void ArrayAnnotationsWidget::clearWidget()
{
  //mpSelectionTable->setNumCols(2);
  mpSelectionTable->setNumRows(0);
  mpContentTable->setNumCols(0);
  mpContentTable->setNumRows(0);
}

void ArrayAnnotationsWidget::fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
                                       CCopasiAbstractArray::index_type & index)
{
  if (!mpArray) return;
  assert(rowIndex < index.size());
  assert(colIndex < index.size());

  mpContentTable->setNumCols(mpArray->size()[colIndex]);
  mpContentTable->setNumRows(mpArray->size()[rowIndex]);

  std::vector<std::string> rowdescr = mpArray->getAnnotationsDisplay(rowIndex);
  std::vector<std::string> coldescr = mpArray->getAnnotationsDisplay(colIndex);

  unsigned C_INT32 i, imax = mpArray->size()[rowIndex];
  unsigned C_INT32 j, jmax = mpArray->size()[colIndex];
  for (i = 0; i < imax; ++i)
    for (j = 0; j < jmax; ++j)
      {
        index[rowIndex] = i;
        index[colIndex] = j;
        mpContentTable->setText(i, j, QString::number((*mpArray->array())[index]));
      }
}

void ArrayAnnotationsWidget::fillTable(unsigned C_INT32 rowIndex,
                                       CCopasiAbstractArray::index_type & index)
{
  if (!mpArray) return;
  assert(rowIndex < index.size());

  mpContentTable->setNumCols(1);
  mpContentTable->setNumRows(mpArray->size()[rowIndex]);

  std::vector<std::string> rowdescr = mpArray->getAnnotationsDisplay(rowIndex);

  unsigned C_INT32 i, imax = mpArray->size()[rowIndex];
  for (i = 0; i < imax; ++i)
    {
      index[rowIndex] = i;
      mpContentTable->verticalHeader()->setLabel(i, rowdescr[i]);
      mpContentTable->setText(i, 0, QString::number((*mpArray->array())[index]));
    }
}

//*******************************************************************************************

/*
 *  Constructs a CQSensResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQSensResultWidget::CQSensResultWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    mpResult(NULL)
{
  if (!name)
    setName("CQSensResultWidget");
  setCaption("CQSensResultWidget");

  mWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "CQSensResultWidgetLayout");

  // **********  Exponents **************
  mLabelTitle = new QLabel(this, "SensLabel");
  mLabelTitle->setText("Sensitivities");
  mLabelTitle->setAlignment(int(QLabel::AlignVCenter
                                | QLabel::AlignRight));
  mWidgetLayout->addWidget(mLabelTitle, 0, 0);

  mArrayWidget = new ArrayAnnotationsWidget(this, "ArrayWidget");
  mWidgetLayout->addMultiCellWidget(mArrayWidget, 1, 2, 1, 2);

  /*  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mWidgetLayout->addItem(spacer, 5, 0);


    mTableExponents = new QTable(this, "mTableExponents");
    mWidgetLayout->addMultiCellWidget(mTableExponents, 4, 5, 1, 2);
    mTableExponents->setNumRows(0);
    mTableExponents->setNumCols(1);
    QHeader *colHeader = mTableExponents->horizontalHeader();
    colHeader->setLabel(0, tr("Exponent"));
    mTableExponents->setColumnStretchable(0, true);
    mTableExponents->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);




    // ************* comment ******************
    mLabelComment = new QLabel(this, "mLabelComment");
    mLabelComment->setAlignment(int(QLabel::WordBreak));
    mLabelComment->setText("");


    mWidgetLayout->addWidget(mLabelComment, 8, 1);


    spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mWidgetLayout->addItem(spacer, 9, 0);*/
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSensResultWidget::~CQSensResultWidget()
{}

void CQSensResultWidget::newResult()
{
  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*CCopasiDataModel::Global->getTaskList())["Sensitivities"]);
  if (!pTask)
    {
      mArrayWidget->setArrayAnnotation(NULL);
      return;
    }

  CSensProblem * pProblem = dynamic_cast< CSensProblem * >(pTask->getProblem());
  if (!pProblem)
    {
      mArrayWidget->setArrayAnnotation(NULL);
      return;
    }

  mpResult = pProblem->getResultAnnotated();

  mArrayWidget->setArrayAnnotation(mpResult);
}

bool CQSensResultWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                C_UNUSED(action), const std::string & C_UNUSED(key))
{
  /*  if (this->isShown())
      return loadFromBackend();
    else
      return true;*/
  return true;
}

bool CQSensResultWidget::leave()
{
  return true;
}

bool CQSensResultWidget::enter(const std::string & C_UNUSED(key))
{
  //clear the widget if the pointer to the result has changed
  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*CCopasiDataModel::Global->getTaskList())["Sensitivities"]);
  if (!pTask)
    {
      mArrayWidget->setArrayAnnotation(NULL);
      return false;
    }

  CSensProblem * pProblem = dynamic_cast< CSensProblem * >(pTask->getProblem());
  if (!pProblem)
    {
      mArrayWidget->setArrayAnnotation(NULL);
      return false;
    }

  if (mpResult != pProblem->getResultAnnotated())
    {
      mArrayWidget->setArrayAnnotation(NULL);
      return false;
    }

  return true;
}
