// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/plotwidget1.cpp,v $
//   $Revision: 1.53.6.5 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/22 11:01:20 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'plotwidget1.ui'
 **
 ** Created: Fri Sep 26 16:01:29 2003
 **      by: The User Interface Compiler ($Id: plotwidget1.cpp,v 1.53.6.5 2008/10/22 11:01:20 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "plotwidget1.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qframe.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qtoolbutton.h>
#include <qlayout.h>

//#include <qtooltip.h>
//#include <qwhatsthis.h>

#include "curve2dwidget.h"
#include "HistoWidget.h"
#include "plotwindow.h"
#include "plot/CPlotSpecification.h"
#include "plot/COutputDefinitionVector.h"
#include "report/CKeyFactory.h"
#include "utilities/CAnnotatedMatrix.h"
#include "UI/CCopasiPlotSelectionDialog.h"
#include "model/CMetabNameInterface.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "UI/DataModelGUI.h"

//temporary
#include "mathematics.h"

#include "UI/CCopasiSelectionDialog.h"

//-----------------------------------------------------------------------------

/*
 *  Constructs a PlotWidget1 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
PlotWidget1::PlotWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("PlotWidget1");

  PlotWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "PlotWidget1Layout");

  //********** title ********************

  labelTitle = new QLabel(this, "labelTitle");
  labelTitle->setText(tr("Plot title"));
  labelTitle->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));
  PlotWidget1Layout->addWidget(labelTitle, 0, 0);

  layoutTitle = new QHBoxLayout(0, 0, 6, "layoutTitle");

  titleLineEdit = new QLineEdit(this, "titleLineEdit");
  layoutTitle->addWidget(titleLineEdit);

  activeCheckBox = new QCheckBox(this, "activeCheckBox");
  activeCheckBox->setText(tr("active?"));
  layoutTitle->addWidget(activeCheckBox);

  PlotWidget1Layout->addLayout(layoutTitle, 0, 1);

  //********** type **********************

  labelType = new QLabel(this, "labelType");
  labelType->setText(tr("Type"));
  labelType->setEnabled(TRUE);
  labelType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));
  PlotWidget1Layout->addWidget(labelType, 1, 0);

  comboType = new QComboBox(FALSE, this, "comboType");
  comboType->clear();
  comboType->insertItem(tr("2D Plot"));
  comboType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, comboType->sizePolicy().hasHeightForWidth()));
  PlotWidget1Layout->addWidget(comboType, 1, 1);

  //************ scales ******************

  labelScale = new QLabel(this, "lableScale");
  labelScale->setText(tr("Axis scales"));
  //labelScale->setEnabled(FALSE);
  labelScale->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));
  PlotWidget1Layout->addWidget(labelScale, 2, 0);

  checkLogX = new QCheckBox(this, "checkLogX");
  checkLogX->setText(tr("log X-axis"));
  //checkLogX->setEnabled(FALSE);
  PlotWidget1Layout->addWidget(checkLogX, 2, 1);

  checkLogY = new QCheckBox(this, "checkLogY");
  checkLogY->setText(tr("log Y-axis"));
  //checkLogY->setEnabled(FALSE);
  PlotWidget1Layout->addWidget(checkLogY, 3, 1);

  //*********** line *******************

  line1 = new QFrame(this, "line1");
  line1->setFrameShape(QFrame::HLine);
  line1->setFrameShadow(QFrame::Sunken);
  line1->setFrameShape(QFrame::HLine);
  PlotWidget1Layout->addMultiCellWidget(line1, 4, 4, 0, 1);

  //************ curves ***************

  labelCurves = new QLabel(this, "lableCurves");
  labelCurves->setText(tr("Curve specifications"));
  labelCurves->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));
  PlotWidget1Layout->addWidget(labelCurves, 5, 0);

  layoutCurves = new QHBoxLayout(0, 0, 6, "layoutCurves");
  spacerCurves = new QSpacerItem(257, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutCurves->addItem(spacerCurves);

  addCurveButton = new QToolButton(this, "addCurveButton");
  addCurveButton->setText(tr("New curve..."));
  layoutCurves->addWidget(addCurveButton);

  addHistoButton = new QToolButton(this, "addCurveButton");
  addHistoButton->setText(tr("New histogram"));
  layoutCurves->addWidget(addHistoButton);

  deleteCurveButton = new QToolButton(this, "deleteCurveButton");
  deleteCurveButton->setText(tr("Delete"));
  layoutCurves->addWidget(deleteCurveButton);

  PlotWidget1Layout->addLayout(layoutCurves, 5, 1);

  //************** tabs *****************

  tabs = new QTabWidget(this, "tabs");
  tabs->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)2, (QSizePolicy::SizeType)3, 0, 0, tabs->sizePolicy().hasHeightForWidth()));
  tabs->setTabPosition(QTabWidget::Top);
  tabs->setTabShape(QTabWidget::Rounded);
  PlotWidget1Layout->addMultiCellWidget(tabs, 6, 6, 0, 1);

  //********** line *************************

  lineButtons = new QFrame(this, "lineButtons");
  lineButtons->setFrameShape(QFrame::HLine);
  lineButtons->setFrameShadow(QFrame::Sunken);
  lineButtons->setFrameShape(QFrame::HLine);
  PlotWidget1Layout->addMultiCellWidget(lineButtons, 7, 7, 0, 1);

  //*********** buttons *****************

  layoutButtons = new QHBoxLayout(0, 0, 2, "layoutButtons");

  startPlotButton = new QPushButton(this, "Commit");
  startPlotButton->setText(tr("Commit"));
  layoutButtons->addWidget(startPlotButton);

  resetButton = new QPushButton(this, "Revert");
  resetButton->setText(tr("Revert"));
  layoutButtons->addWidget(resetButton);

  addPlotButton = new QPushButton(this, "addPlotButton");
  addPlotButton->setText(tr("New Plot"));
  layoutButtons->addWidget(addPlotButton);

  deletePlotButton = new QPushButton(this, "deletePlotButton");
  deletePlotButton->setText(tr("Delete Plot"));
  layoutButtons->addWidget(deletePlotButton);

  PlotWidget1Layout->addMultiCellLayout(layoutButtons, 8, 8, 0, 1);

  //resize(QSize(508, 505).expandedTo(minimumSizeHint()));

  //TODO: adjust tab order? - mostly fine

  // signals and slots connections
  connect(addCurveButton, SIGNAL(clicked()), this, SLOT(addCurveSlot()));
  connect(addHistoButton, SIGNAL(clicked()), this, SLOT(addHistoSlot()));
  connect(deleteCurveButton, SIGNAL(clicked()), this, SLOT(removeCurve()));
  connect(startPlotButton, SIGNAL(clicked()), this, SLOT(startPlot()));
  connect(deletePlotButton, SIGNAL(clicked()), this, SLOT(deletePlot()));
  connect(addPlotButton, SIGNAL(clicked()), this, SLOT(addPlot()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(resetPlot()));
  connect(comboType, SIGNAL(activated(int)), this, SLOT(typeChanged()));

  //mpPlotSpec = new CPlotSpecification;
}

//-----------------------------------------------------------------------------
/*
 *  Destroys the object and frees any allocated resources
 */
PlotWidget1::~PlotWidget1()
{}

//-----------------------------------------------------------------------------

//the slot...
void PlotWidget1::addCurveSlot()
{
  if (mType == CPlotItem::plot2d)
    addCurve2D();
}

void PlotWidget1::addHistoSlot()
{
  if (mType == CPlotItem::plot2d)
    addHisto1D();
}

void PlotWidget1::addCurveTab(const std::string & title,
                              const CPlotDataChannelSpec & x,
                              const CPlotDataChannelSpec & y)
{
  CPlotItem* item = new CPlotItem(title, NULL, CPlotItem::curve2d);
  item->addChannel(x);
  item->addChannel(y);

  Curve2DWidget * curveWidget = new Curve2DWidget(tabs);
  curveWidget->setModel(CCopasiDataModel::Global->getModel());
  curveWidget->LoadFromCurveSpec(item);
  tabs->addTab(curveWidget, item->getTitle().c_str());

  delete item;
}

void PlotWidget1::addCurve2D()
{
  CCopasiPlotSelectionDialog* pBrowser = new CCopasiPlotSelectionDialog();
  std::vector< const CCopasiObject * > vector1;
  std::vector< const CCopasiObject * > vector2;
  pBrowser->setOutputVectors(&vector1, &vector2);
  pBrowser->setModel(CCopasiDataModel::Global->getModel(), CCopasiSimpleSelectionTree::PLOT_OBJECT);

  if (pBrowser->exec () == QDialog::Rejected)
    {
      return;
    }

  //this assumes that the vector is empty if nothing was chosen
  if (vector1.size() == 0 || vector2.size() == 0)
    {
      return;
    }

  std::vector<CCopasiObjectName> objects1, objects2;
  unsigned C_INT32 i;
  std::vector<CCopasiObjectName>::const_iterator sit;
  const CArrayAnnotation *pArray;

  // 1. enable user to choose either a cell, an entire row/column, or even the objects themselves, if they are arrays.
  // 2. translate to CNs and remove duplicates

  // x-axis is set for single cell selection
  //  std::cout << "pVector1->size() = " << pVector1->size() << std::endl;
  std::string cn;
  for (i = 0; i < vector1.size(); i++)
    {
      if (vector1[i])  // the object is not empty
        {
          // is it an array annotation?
          if ((pArray = dynamic_cast< const CArrayAnnotation * >(vector1[i])))
            {
              // second argument is true as only single cell here is allowed. In this case we
              //can assume that the size of the return vector is 1.
              const CCopasiObject * pObject = CCopasiSelectionDialog::chooseCellMatrix(pArray, true, true)[0];
              if (!pObject) continue;
              //std::cout << "object1 : " << pObject->getObjectType() << " - " << pObject->getObjectName() << std::endl;

              cn = pObject->getCN();
            }
          else
            cn = vector1[i]->getCN();

          //std::cout << "cn : " << cn << std::endl;
          //std::cout << "object: " << (*pVector1)[i]->getObjectType() << " - " << (*pVector1)[i]->getObjectName() << std::endl;

          // check whether cn is already on objects1
          for (sit = objects1.begin(); sit != objects1.end(); ++sit)
            {
              if (*sit == cn) break;
            }

          // if not exist, input cn into objects1
          if (sit == objects1.end())
            {
              objects1.push_back(cn);
              //std::cout << "***" << cn << std::endl;
            }
        }
    }

  // y-axis is set for multi cells selection
  // Multi cells selection is done by calling single cell one multi times.
  //std::cout << "pVector2->size() = " << pVector2->size() << std::endl;
  //  std::vector<std::string> cnVector;
  for (i = 0; i < vector2.size(); i++)
    {
      if (vector2[i])
        {
          // is it an array annotation?
          if ((pArray = dynamic_cast< const CArrayAnnotation * >(vector2[i])))
            {
              // second argument is set false for multi selection
              std::vector<const CCopasiObject*> vvv = CCopasiSelectionDialog::chooseCellMatrix(pArray, false, true);
              std::vector<const CCopasiObject*>::const_iterator it;
              for (it = vvv.begin(); it != vvv.end(); ++it)
                {
                  if (!*it) continue;
                  cn = (*it)->getCN();

                  //check if the CN already is in the list, if not add it.
                  for (sit = objects2.begin(); sit != objects2.end(); ++sit)
                    if (*sit == cn) break;
                  if (sit == objects2.end())
                    objects2.push_back(cn);
                }
            }
          else
            {
              cn = vector2[i]->getCN();

              //check if the CN already is in the list, if not add it.
              for (sit = objects2.begin(); sit != objects2.end(); ++sit)
                if (*sit == cn) break;
              if (sit == objects2.end())
                objects2.push_back(cn);
            }
        }
    }

  //CPlotSpec* pspec = dynamic_cast< CPlotSpec * >(GlobalKeys.get(objKey));
  //if (!pspec) return;

  C_INT32 storeTab = tabs->count();

  if (objects1.size() == 1)
    {
      for (i = 0; i < objects2.size(); ++i)
        {
          addCurveTab(CCopasiContainer::ObjectFromName(objects2[i])->getObjectDisplayName()
                      + "|"
                      + CCopasiContainer::ObjectFromName(objects1[0])->getObjectDisplayName(),
                      objects1[0], objects2[i]);
        }
    }
  else if (objects2.size() == 1)
    {
      for (i = 0; i < objects1.size(); ++i)
        {
          addCurveTab(CCopasiContainer::ObjectFromName(objects2[0])->getObjectDisplayName()
                      + "|"
                      + CCopasiContainer::ObjectFromName(objects1[i])->getObjectDisplayName(),
                      objects1[i], objects2[0]);
        }
    }
  else
    {
      unsigned C_INT32 imax;
      if (objects1.size() > objects2.size())
        imax = objects2.size();
      else
        imax = objects1.size();

      for (i = 0; i < imax; ++i)
        {
          addCurveTab(CCopasiContainer::ObjectFromName(objects2[i])->getObjectDisplayName()
                      + "|"
                      + CCopasiContainer::ObjectFromName(objects1[i])->getObjectDisplayName() ,
                      objects1[i], objects2[i]);
        }
    }

  tabs->setCurrentPage(storeTab);
}

void PlotWidget1::addHisto1DTab(const std::string & title,
                                const CPlotDataChannelSpec & x)
{
  CPlotItem* item = new CPlotItem(title, NULL, CPlotItem::histoItem1d);
  item->addChannel(x);

  HistoWidget * curveWidget = new HistoWidget(tabs);
  curveWidget->setModel(CCopasiDataModel::Global->getModel());
  curveWidget->LoadFromCurveSpec(item);
  tabs->addTab(curveWidget, item->getTitle().c_str());

  delete item;
}

void PlotWidget1::addHisto1D()
{
  C_INT32 storeTab = tabs->count();
  addHisto1DTab("Histogram", CPlotDataChannelSpec(CCopasiObjectName("")));
  tabs->setCurrentPage(storeTab);
}

//-----------------------------------------------------------------------------

void PlotWidget1::removeCurve()
{
  delete tabs->currentPage();
}

//-----------------------------------------------------------------------------

void PlotWidget1::startPlot()
{
  saveToPlotSpec();

  loadFromPlotSpec(dynamic_cast<CPlotSpecification*>(GlobalKeys.get(objKey)));

  //commented for testing
  //startPlotButton->setEnabled(false);
  /*    deletePlotButton->setEnabled(false);
      addCurveButton->setEnabled(false);
      deleteCurveButton->setEnabled(false);
      titleLineEdit->setEnabled(false);
      scrollView->setEnabled(false);
    */
}

//-----------------------------------------------------------------------------

void PlotWidget1::deletePlot()
{
  unsigned C_INT32 Index, Size;

  if (!CCopasiDataModel::Global->getModel())
    return;

  CPlotSpecification * pspec = dynamic_cast< CPlotSpecification * >(GlobalKeys.get(objKey));
  if (!pspec) return;

  Index =
    CCopasiDataModel::Global->getPlotDefinitionList()->CCopasiVector<CPlotSpecification>::getIndex(pspec);
  CCopasiDataModel::Global->getPlotDefinitionList()->removePlotSpec(objKey);

  Size = CCopasiDataModel::Global->getPlotDefinitionList()->size();

  if (Size > 0)
    enter((*CCopasiDataModel::Global->getPlotDefinitionList())[std::min(Index, Size - 1)]->CCopasiParameter::getKey());
  else
    enter("");

  //ListViews::
  protectedNotify(ListViews::PLOT, ListViews::DELETE, objKey);
}

//-----------------------------------------------------------------------------

void PlotWidget1::addPlot()
{
  leave();

  std::string name = "plot_";
  int i = 0;
  CPlotSpecification* pPl = NULL;
  name += (const char *)QString::number(i).utf8();

  while (!(pPl = CCopasiDataModel::Global->getPlotDefinitionList()->createPlotSpec(name, CPlotItem::plot2d)))
    {
      i++;
      name = "plot_";
      name += (const char *)QString::number(i).utf8();
    }

  protectedNotify(ListViews::PLOT, ListViews::ADD);

  enter(pPl->CCopasiParameter::getKey());
}

//-----------------------------------------------------------------------------

void PlotWidget1::resetPlot()
{
  loadFromPlotSpec(dynamic_cast<CPlotSpecification*>(GlobalKeys.get(objKey)));
}

//-----------------------------------------------------------------------------

// not properly used for now
void PlotWidget1::plotFinished()
{
  startPlotButton->setEnabled(true);
  // ...and enable all other input fields
}

void PlotWidget1::typeChanged()
{
  CPlotItem::Type newType;

  switch (comboType->currentItem())
    {
    case 0:
      newType = CPlotItem::plot2d;
      break;
    default :
      fatalError();
    }

  if (mType == newType)
    return; //do nothing

  mType = newType;

  //clear tabWidget
  while (tabs->currentPage()) delete tabs->currentPage();

  //TODO: perhaps create empty tab
}

//-----------------------------------------------------------------------------

bool PlotWidget1::loadFromPlotSpec(const CPlotSpecification *pspec)
{
  if (!pspec) return false;

  //title
  titleLineEdit->setText(pspec->getTitle().c_str());

  //active?
  activeCheckBox->setChecked(pspec->isActive());

  //type
  mType = pspec->getType();
  switch (mType)
    {
    case CPlotItem::plot2d:
      comboType->setCurrentItem(0);
      checkLogX->setChecked(pspec->isLogX());
      checkLogY->setChecked(pspec->isLogY());
      break;
      break;
    default:
      fatalError();
    }

  C_INT32 oldIndex = tabs->currentPageIndex();

  //clear tabWidget
  while (tabs->currentPage()) delete tabs->currentPage();

  //reconstruct tabWidget from curve specs
  const CCopasiVector<CPlotItem> & curves = pspec->getItems();
  unsigned C_INT32 i, imax = curves.size();
  for (i = 0; i < imax; ++i)
    {
      if (curves[i]->getType() == CPlotItem::curve2d)
        {
          Curve2DWidget* curve = new Curve2DWidget(tabs);
          curve->setModel(CCopasiDataModel::Global->getModel());
          curve->LoadFromCurveSpec(curves[i]);
          tabs->addTab(curve, curves[i]->getTitle().c_str());
        }

      if (curves[i]->getType() == CPlotItem::histoItem1d)
        {
          HistoWidget* histo = new HistoWidget(tabs);
          histo->setModel(CCopasiDataModel::Global->getModel());
          histo->LoadFromCurveSpec(curves[i]);
          tabs->addTab(histo, curves[i]->getTitle().c_str());
        }
    }

  tabs->setCurrentPage(oldIndex);

  return true; //TODO really check
}

bool PlotWidget1::saveToPlotSpec()
{
  CPlotSpecification* pspec = dynamic_cast< CPlotSpecification * >(GlobalKeys.get(objKey));
  if (!pspec) return true;

  pspec->cleanup();

  //title
  if (pspec->getTitle() != (const char*)titleLineEdit->text().utf8())
    {
      pspec->setTitle((const char*)titleLineEdit->text().utf8());
      protectedNotify(ListViews::PLOT, ListViews::RENAME, objKey);
    }

  //active?
  pspec->setActive(activeCheckBox->isChecked());

  //scales
  pspec->setLogX(checkLogX->isChecked());
  pspec->setLogY(checkLogY->isChecked());

  //curves
  CPlotItem* item;
  unsigned C_INT32 i, imax;
  imax = tabs->count();
  for (i = 0; i < imax; ++i)
    {
      Curve2DWidget* tmpCurve2D = dynamic_cast<Curve2DWidget*>(tabs->page(i));
      if (tmpCurve2D)
        {
          item = pspec->createItem("dummyname", CPlotItem::curve2d);
          tmpCurve2D->SaveToCurveSpec(item);
        }

      HistoWidget* tmpHisto = dynamic_cast<HistoWidget*>(tabs->page(i));
      if (tmpHisto)
        {
          item = pspec->createItem("dummyname", CPlotItem::histoItem1d);
          tmpHisto->SaveToCurveSpec(item);
        }
    }

  //TODO: CopasiParameters

  return true;
}

//-----------------------------------------------------------------------------

//TODO:  save a copy!

bool PlotWidget1::enter(const std::string & key)
{
  objKey = key;
  CPlotSpecification* pspec = dynamic_cast< CPlotSpecification * >(GlobalKeys.get(key));

  if (!pspec)
    {
      mpListView->switchToOtherWidget(42, "");
      return false;
    }

  return loadFromPlotSpec(pspec);
}

//-----------------------------------------------------------------------------

bool PlotWidget1::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {//TODO: check list:
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REPORT:
    case ListViews::PLOT:
      return loadFromPlotSpec(dynamic_cast< CPlotSpecification * >(GlobalKeys.get(objKey)));
      break;

    default:
      break;
    }
  return true;
}

//-----------------------------------------------------------------------------

bool PlotWidget1::leave()
{
  return saveToPlotSpec();
}
