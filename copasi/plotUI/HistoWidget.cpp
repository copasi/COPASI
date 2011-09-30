// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/HistoWidget.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:36:41 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QVariant>

#include "HistoWidget.h"
#include "PlotSubwidget.h"

#include "UI/CCopasiSelectionDialog.h"
#include "UI/qtUtilities.h"

#include "plot/CPlotItem.h"
#include "report/CCopasiRootContainer.h"

HistoWidget::HistoWidget(QWidget* parent, const char* /* name */, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
  setupUi(this);

  const QIcon icon = qt_get_icon(image0_ID);
  mpBtnVariable->setIcon(icon);
}

HistoWidget::~HistoWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void HistoWidget::buttonPressedX()
{
  if (!mpModel) return;

  //  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this, CQSimpleSelectionTree::NUMERIC, mpObjectX);
  //mpObjectX = CCopasiSelectionDialog::getObjectSingle(this, CQSimpleSelectionTree::PLOT_OBJECT, mpObjectX);

  std::vector< const CCopasiObject * > oldSelection;

  if (mpObjectX)
    oldSelection.push_back(mpObjectX);

  std::vector< const CCopasiObject * > objects =
    CCopasiSelectionDialog::getObjectVector(this,
                                            CQSimpleSelectionTree::NumericValues,
                                            &oldSelection);

  if (objects.size() && objects[0])
    {
      mpObjectX = objects[0];
      mpEditVariable->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
      mpEditTitle->setText("Histogram: " + FROM_UTF8(mpObjectX->getObjectDisplayName()));
    }
  else
    {
      mpObjectX = NULL;
      mpEditVariable->setText("");
      mpEditTitle->setText("Histogram");
    }

  //check if more than one object was selected...
  if (objects.size() > 1)
    {
      PlotSubwidget* pParent;
      QObject* tmp = this;

      while (!(pParent = dynamic_cast<PlotSubwidget *>(tmp)) && this)
        tmp = tmp->parent();

      if (pParent) //tell the parent to create the remaining histogram descriptions.
        pParent->createHistograms(objects, mpEditIncrement->text().toDouble());
    }
}

bool HistoWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve) return false;

  if (curve->getType() != CPlotItem::histoItem1d) return false;

  if (curve->getChannels().size() != 1) return false;

  //title
  mpEditTitle->setText(FROM_UTF8(curve->getTitle()));

  //variable
  mpObjectX = NULL;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (curve->getChannels().size() >= 1)
    mpObjectX = pDataModel->getDataObject(curve->getChannels()[0]);

  if (mpObjectX == pDataModel)
    {
      mpObjectX = NULL;
    }

  if (mpObjectX != NULL)
    mpEditVariable->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  else
    mpEditVariable->setText("");

  //other parameters:
  const void* tmp;

  if (!(tmp = curve->getValue("increment").pVOID)) return false;

  mpEditIncrement->setText(QString::number(*(const C_FLOAT64*)tmp));

  mpCheckBefore->setChecked(curve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(curve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(curve->getActivity() & COutputInterface::AFTER);

  return true; //TODO
}

bool HistoWidget::SaveToCurveSpec(CPlotItem * curve) const
{
  //title
  curve->setTitle(TO_UTF8(mpEditTitle->text()));

  //channels
  curve->getChannels().clear();
  curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectX ? mpObjectX->getCN() : CCopasiObjectName("")));

  //other parameters: TODO
  curve->setValue("increment", mpEditIncrement->text().toDouble());

  C_INT32 Activity = 0;

  if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;

  if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;

  if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;

  curve->setActivity((COutputInterface::Activity) Activity);

  return true;
}

void HistoWidget::setModel(const CModel * model)
{
  mpModel = model;
}
